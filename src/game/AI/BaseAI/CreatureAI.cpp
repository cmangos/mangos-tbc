/*
* This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "AI/BaseAI/CreatureAI.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"
#include "World/World.h"
#include "Entities/Creature.h"

CreatureAI::CreatureAI(Creature* creature) : CreatureAI(creature, 0) { }

CreatureAI::CreatureAI(Creature* creature, uint32 combatActions) :
    UnitAI(creature, combatActions),
    m_creature(creature),
    m_deathPrevented(false), m_followAngle(0.f), m_followDist(0.f)
{
    m_dismountOnAggro = !(m_creature->GetCreatureInfo()->HasFlag(CreatureTypeFlags::ALLOW_MOUNTED_COMBAT));
    SetMeleeEnabled(!(m_creature->GetSettings().HasFlag(CreatureStaticFlags::NO_MELEE_FLEE)
        || m_creature->GetSettings().HasFlag(CreatureStaticFlags4::NO_MELEE_APPROACH) || m_creature->GetCreatureInfo()->ExtraFlags & CREATURE_EXTRA_FLAG_NO_MELEE));
    if (m_creature->GetSettings().HasFlag(CreatureStaticFlags::SESSILE))
        SetAIImmobilizedState(true);

    if (m_creature->IsNoAggroOnSight())
        SetReactState(REACT_DEFENSIVE);
    if (m_creature->GetSettings().HasFlag(CreatureStaticFlags2::SPAWN_DEFENSIVE))
        SetReactState(REACT_DEFENSIVE);
    else if (m_creature->GetSettings().HasFlag(CreatureStaticFlags::IGNORE_COMBAT))
        m_creature->SetCanEnterCombat(false);
    if (m_creature->IsGuard() || m_unit->GetCharmInfo()) // guards and charmed targets
        m_visibilityDistance = sWorld.getConfig(CONFIG_FLOAT_SIGHT_GUARDER);
}

void CreatureAI::Reset()
{
    m_currentRangedMode = m_rangedMode;
    m_attackDistance = m_chaseDistance;
}

void CreatureAI::EnterCombat(Unit* enemy)
{
    UnitAI::EnterCombat(enemy);
    if (enemy && (m_creature->IsGuard() || m_creature->IsCivilian()))
    {
        // Send Zone Under Attack message to the LocalDefense and WorldDefense Channels
        if (Player* pKiller = enemy->GetBeneficiaryPlayer())
            m_creature->SendZoneUnderAttackMessage(pKiller);
    }
}

void CreatureAI::EnterEvadeMode()
{
    UnitAI::EnterEvadeMode();
    ResetTimersOnEvade();
    Reset();
}

void CreatureAI::AttackStart(Unit* who)
{
    if (m_creature->GetSettings().HasFlag(CreatureStaticFlags::COMBAT_PING))
    {
        if (Player* owner = dynamic_cast<Player*>(m_creature->GetSpawner()))
        {
            WorldPacket data(MSG_MINIMAP_PING, (8 + 4 + 4));
            data << m_creature->GetObjectGuid();
            data << m_creature->GetPositionX();
            data << m_creature->GetPositionY();
            owner->SendDirectMessage(data);
        }
    }

    if (!who || HasReactState(REACT_PASSIVE))
        return;

    bool targetChange = m_unit->GetVictim() != nullptr && m_unit->GetVictim() != who;
    if (m_creature->Attack(who, m_meleeEnabled))
    {
        m_creature->EngageInCombatWith(who);

        // Cast "Spawn Guard" to help Civilian
        if (m_creature->GetSettings().HasFlag(CreatureStaticFlags::CALLS_GUARDS))
            m_creature->CastSpell(nullptr, 43783, TRIGGERED_OLD_TRIGGERED);

        HandleMovementOnAttackStart(who, targetChange);
    }
}

void CreatureAI::DamageTaken(Unit* dealer, uint32& damage, DamageEffectType damageType, SpellEntry const* /*spellInfo*/)
{
    if (m_creature->GetSettings().HasFlag(CreatureStaticFlags::UNKILLABLE) && damageType != INSTAKILL)
    {
        if (m_creature->GetHealth() <= damage) // the damage will be reduced in Unit::DealDamage
        {
            if (!m_deathPrevented)
            {
                m_deathPrevented = true;
                JustPreventedDeath(dealer);
            }
        }        
    }
}

void CreatureAI::JustReachedHome()
{
    if (m_dismountOnAggro)
        if (CreatureInfo const* mountInfo = m_creature->GetMountInfo())
            m_creature->Mount(Creature::ChooseDisplayId(mountInfo));
}

void CreatureAI::JustRespawned()
{
    ResetAllTimers();
    Reset();
}

void CreatureAI::SetDeathPrevention(bool state)
{
    if (state)
        m_creature->GetSettings().SetFlag(CreatureStaticFlags::UNKILLABLE);
    else
        m_creature->GetSettings().RemoveFlag(CreatureStaticFlags::UNKILLABLE);
}

void CreatureAI::DoFakeDeath(uint32 spellId)
{
    m_creature->InterruptNonMeleeSpells(false);
    m_creature->InterruptMoving();
    m_creature->ClearComboPointHolders();
    m_creature->RemoveAllAurasOnDeath();
    m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_20_PERCENT, false);
    m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_35_PERCENT, false);
    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE);
    m_creature->ClearAllReactives();
    m_creature->SetTarget(nullptr);
    m_creature->GetMotionMaster()->Clear();
    m_creature->GetMotionMaster()->MoveIdle();

    if (spellId)
        DoCastSpellIfCan(nullptr, spellId, CAST_INTERRUPT_PREVIOUS);
}

void CreatureAI::RetreatingArrived()
{
    m_creature->SetNoCallAssistance(false);
    m_creature->CallAssistance();
}

void CreatureAI::RetreatingEnded()
{
    if (GetAIOrder() != ORDER_RETREATING)
        return; // prevent stack overflow by cyclic calls - TODO: remove once Motion Master is human again
    SetAIOrder(ORDER_NONE);
    SetCombatScriptStatus(false);
    if (!m_creature->IsAlive())
        return;
    DoStartMovement(m_creature->GetVictim());
}

bool CreatureAI::DoRetreat()
{
    Unit* victim = m_creature->GetVictim();
    if (!victim)
        return false;

    float radius = sWorld.getConfig(CONFIG_FLOAT_CREATURE_FAMILY_FLEE_ASSISTANCE_RADIUS);
    if (radius <= 0)
        return false;

    Creature* ally = nullptr;

    MaNGOS::NearestAssistCreatureInCreatureRangeCheck check(m_creature, victim, radius);
    MaNGOS::CreatureLastSearcher<MaNGOS::NearestAssistCreatureInCreatureRangeCheck> searcher(ally, check);
    Cell::VisitGridObjects(m_creature, searcher, radius);

    // Check if an ally to call for was found
    if (!ally)
        return false;

    uint32 delay = sWorld.getConfig(CONFIG_UINT32_CREATURE_FAMILY_ASSISTANCE_DELAY);

    Position pos;
    ally->GetFirstCollisionPosition(pos, ally->GetCombatReach(), ally->GetAngle(m_creature));
    m_creature->GetMotionMaster()->MoveRetreat(pos.x, pos.y, pos.z, ally->GetAngle(victim), delay);

    SetAIOrder(ORDER_RETREATING);
    SetCombatScriptStatus(true);
    return true;
}

void CreatureAI::DoCallForHelp(float radius)
{
    m_creature->CallForHelp(radius);
}

void CreatureAI::OnCallForHelp(Unit* enemy)
{
    if (FactionTemplateEntry const* factionTemplate = m_creature->GetFactionTemplateEntry())
    {
        if (factionTemplate->factionFlags & FACTION_TEMPLATE_FLEE_FROM_CALL_FOR_HELP)
        {
            if (m_creature->SetInPanic(10000))
                SetAIOrder(ORDER_FLEE_FROM_CALL_FOR_HELP);
            return;
        }
    }
    AttackStart(enemy);
}

void CreatureAI::HandleAssistanceCall(Unit* sender, Unit* invoker)
{
    if (!invoker || m_creature->IsCritter())
        return;
    if (m_creature->CanAssistInCombatAgainst(sender, invoker) && m_creature->CanJoinInAttacking(invoker) && invoker->IsVisibleForOrDetect(m_creature, m_creature, false))
    {
        m_creature->SetNoCallAssistance(true);
        AttackStart(invoker);
    }
}

void CreatureAI::AddUnreachabilityCheck()
{
    m_teleportUnreachable = true;
}

CreatureSpellList const& CreatureAI::GetSpellList() const
{
    return m_creature->GetSpellList();
}

void CreatureAI::TimedFleeingEnded()
{
    UnitAI::TimedFleeingEnded();
    if (GetAIOrder() == ORDER_FLEE_FROM_CALL_FOR_HELP && m_creature->IsAlive())
    {
        if (FactionTemplateEntry const* factionTemplate = m_creature->GetFactionTemplateEntry())
            if (factionTemplate->factionFlags & FACTION_TEMPLATE_FLEE_FROM_CALL_FOR_HELP)
                EnterEvadeMode();
    }
    if (GetAIOrder() == ORDER_CRITTER_FLEE && m_creature->IsAlive())
    {
        SetCombatScriptStatus(false);
        EnterEvadeMode();
    }
    SetAIOrder(ORDER_NONE);
}

void CreatureAI::RequestFollow(Unit* followee)
{
    if (followee->IsPlayer())
    {
        auto data = static_cast<Player*>(followee)->RequestFollowData(m_creature->GetObjectGuid());
        m_followAngle = data.first;
        m_followDist = data.second;
        m_requestedFollower = followee->GetObjectGuid();
    }
    m_creature->GetMotionMaster()->MoveFollow(followee, m_followDist, m_followAngle);
}

void CreatureAI::RelinquishFollow(ObjectGuid follower)
{
    if (m_requestedFollower && (!follower || m_requestedFollower == follower))
        if (Unit* owner = m_creature->GetMap()->GetUnit(m_requestedFollower))
            if (owner->IsPlayer())
                static_cast<Player*>(owner)->RelinquishFollowData(m_creature->GetObjectGuid());
}
