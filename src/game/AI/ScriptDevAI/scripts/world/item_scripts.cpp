/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
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

/* ScriptData
SDName: Item_Scripts
SD%Complete: 100
SDComment: Items for a range of different items. See content below (in script)
SDCategory: Items
EndScriptData */

/* ContentData
item_arcane_charges                 Prevent use if player is not flying (cannot cast while on ground)
item_flying_machine(i34060,i34061)  Engineering crafted flying machines
item_gor_dreks_ointment(i30175)     Protecting Our Own(q10488)
EndContentData */

#include "AI/ScriptDevAI/include/sc_common.h"
#include "Spells/Spell.h"
#include "Spells/Scripts/SpellScript.h"


/*#####
# item_orb_of_draconic_energy
#####*/

enum
{
    SPELL_DOMINION_SOUL     = 16053,
    NPC_EMBERSTRIFE         = 10321
};

bool ItemUse_item_orb_of_draconic_energy(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    Creature* pEmberstrife = GetClosestCreatureWithEntry(pPlayer, NPC_EMBERSTRIFE, 20.0f);
    if (!pEmberstrife)
        return false;

    // If Emberstrife already mind controled or above 10% HP: force spell cast failure
    if (pEmberstrife->HasAura(SPELL_DOMINION_SOUL) || pEmberstrife->GetHealthPercent() > 10.0f)
    {
        pPlayer->SendEquipError(EQUIP_ERR_NONE, pItem, nullptr);

        if (const SpellEntry* pSpellInfo = GetSpellStore()->LookupEntry<SpellEntry>(SPELL_DOMINION_SOUL))
            Spell::SendCastResult(pPlayer, pSpellInfo, 1, SPELL_FAILED_TARGET_AURASTATE);

        return true;
    }

    return false;
}

/*#####
# item_arcane_charges
#####*/

enum
{
    SPELL_ARCANE_CHARGES    = 45072
};

bool ItemUse_item_arcane_charges(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    if (pPlayer->IsTaxiFlying())
        return false;

    pPlayer->SendEquipError(EQUIP_ERR_NONE, pItem, nullptr);

    if (const SpellEntry* pSpellInfo = GetSpellStore()->LookupEntry<SpellEntry>(SPELL_ARCANE_CHARGES))
        Spell::SendCastResult(pPlayer, pSpellInfo, 1, SPELL_FAILED_ERROR);

    return true;
}

/*#####
# item_flying_machine
#####*/

bool ItemUse_item_flying_machine(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    uint32 itemId = pItem->GetEntry();

    if (itemId == 34060)
        if (pPlayer->GetSkillValueBase(SKILL_RIDING) >= 225)
            return false;

    if (itemId == 34061)
        if (pPlayer->GetSkillValueBase(SKILL_RIDING) == 300)
            return false;

    debug_log("SD2: Player attempt to use item %u, but did not meet riding requirement", itemId);
    pPlayer->SendEquipError(EQUIP_ERR_CANT_EQUIP_SKILL, pItem, nullptr);
    return true;
}

/*#####
# item_gor_dreks_ointment
#####*/

enum
{
    NPC_TH_DIRE_WOLF        = 20748,
    SPELL_GORDREKS_OINTMENT = 32578
};

bool ItemUse_item_gor_dreks_ointment(Player* pPlayer, Item* pItem, const SpellCastTargets& pTargets)
{
    if (pTargets.getUnitTarget() && pTargets.getUnitTarget()->GetTypeId() == TYPEID_UNIT && pTargets.getUnitTarget()->HasAura(SPELL_GORDREKS_OINTMENT))
    {
        pPlayer->SendEquipError(EQUIP_ERR_NONE, pItem, nullptr);

        if (const SpellEntry* pSpellInfo = GetSpellStore()->LookupEntry<SpellEntry>(SPELL_GORDREKS_OINTMENT))
            Spell::SendCastResult(pPlayer, pSpellInfo, 1, SPELL_FAILED_TARGET_AURASTATE);

        return true;
    }

    return false;
}

enum
{
    SPELL_ASHBRINGER_EFFECT_001 = 28442,
};

struct AshbringerItemAura : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const
    {
        if (apply)
        {
            Unit* target = aura->GetTarget();
            int32 basepoints = ReputationRank(REP_FRIENDLY);
            target->CastCustomSpell(nullptr, SPELL_ASHBRINGER_EFFECT_001, &basepoints, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
        }
        else
            aura->GetTarget()->RemoveAurasDueToSpell(SPELL_ASHBRINGER_EFFECT_001);
    }
};

enum
{
    SPELL_PARACHUTE = 37897,
};

struct X52RocketHelmetAura : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const
    {
        if (!apply)
        {
            Unit* target = aura->GetTarget();
            target->CastSpell(target, SPELL_PARACHUTE, TRIGGERED_OLD_TRIGGERED);
        }
    }
};

enum
{
    SPELL_LIMITLESS_POWER = 45044,
};

struct PowerCircleAura : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const
    {
        Unit* target = aura->GetTarget();
        if (apply && target->GetObjectGuid() == aura->GetCasterGuid())
            target->CastSpell(nullptr, SPELL_LIMITLESS_POWER, TRIGGERED_OLD_TRIGGERED);
        else
            target->RemoveAurasDueToSpell(SPELL_LIMITLESS_POWER);
    }
};

enum
{
    SPELL_GDR_PERIODIC_DAMAGE = 13493,
    SPELL_GDR_DAMAGE_HIT      = 13279,
};

struct GDRChannel : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx == EFFECT_INDEX_1)
            spell->GetCaster()->CastSpell(nullptr, SPELL_GDR_PERIODIC_DAMAGE, TRIGGERED_OLD_TRIGGERED);
    }
};

struct GDRPeriodicDamage : public AuraScript
{
    int32 OnAuraValueCalculate(AuraCalcData& /*data*/, int32 /*value*/) const override
    {
        return urand(100, 500);
    }

    void OnApply(Aura* aura, bool apply) const override
    {
        if (!apply && aura->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
        {
            int32 dmg = (int32)aura->GetScriptValue();
            aura->GetTarget()->CastCustomSpell(aura->GetTarget()->GetTarget(), SPELL_GDR_DAMAGE_HIT, &dmg, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
        }
    }
};

struct OgrilaFlasks : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const override
    {
        if (aura->GetEffIndex() != EFFECT_INDEX_0 || apply)
            return;

        SpellEntry const* spellInfo = aura->GetSpellProto();
        for (uint32 i = EFFECT_INDEX_1; i < MAX_EFFECT_INDEX; ++i)
            if (uint32 triggerSpell = spellInfo->EffectTriggerSpell[i])
                aura->GetTarget()->RemoveAurasDueToSpell(triggerSpell);
    }
};

struct Drink : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const override
    {
        if (!apply || aura->GetEffIndex() != EFFECT_INDEX_0)
            return;

        if (!aura->GetTarget()->IsPlayer())
            return;

        if (aura->GetTarget()->GetMap()->IsBattleArena())
            return;

        if (Aura* periodicAura = aura->GetHolder()->GetAuraByEffectIndex((SpellEffectIndex)(aura->GetEffIndex() + 1)))
            aura->GetModifier()->m_amount = periodicAura->GetModifier()->m_amount;
    }

    void OnPeriodicDummy(Aura* aura) const override
    {
        if (aura->GetEffIndex() != EFFECT_INDEX_1)
            return;
        
        if (!aura->GetTarget()->IsPlayer())
            return;

        if (!aura->GetTarget()->GetMap()->IsBattleArena())
            return;

        //if (aura->GetAuraTicks() != 2) // todo: wait for 2nd tick to update regen in Arena only? (needs confirmation)
        //    return;

        aura->ForcePeriodicity(0);

        if (Aura* regenAura = aura->GetHolder()->GetAuraByEffectIndex((SpellEffectIndex)(aura->GetEffIndex() - 1)))
        {
            regenAura->GetModifier()->m_amount = aura->GetModifier()->m_amount;
            ((Player*)aura->GetTarget())->UpdateManaRegen();
        }
    }
};

struct ReducedProcChancePast60 : public AuraScript
{
    void OnHolderInit(SpellAuraHolder* holder, WorldObject* /*caster*/) const override
    {
        holder->SetReducedProcChancePast60();
    }
};

void AddSC_item_scripts()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "item_orb_of_draconic_energy";
    pNewScript->pItemUse = &ItemUse_item_orb_of_draconic_energy;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "item_arcane_charges";
    pNewScript->pItemUse = &ItemUse_item_arcane_charges;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "item_flying_machine";
    pNewScript->pItemUse = &ItemUse_item_flying_machine;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "item_gor_dreks_ointment";
    pNewScript->pItemUse = &ItemUse_item_gor_dreks_ointment;
    pNewScript->RegisterSelf();

    RegisterAuraScript<AshbringerItemAura>("spell_ashbringer_item");
    RegisterAuraScript<X52RocketHelmetAura>("spell_to_infinity_and_above");
    RegisterAuraScript<PowerCircleAura>("spell_power_circle");

    RegisterSpellScript<GDRChannel>("spell_gdr_channel");
    RegisterAuraScript<GDRPeriodicDamage>("spell_gdr_periodic");
    RegisterAuraScript<OgrilaFlasks>("spell_ogrila_flasks");
    RegisterAuraScript<Drink>("spell_drink");
    RegisterAuraScript<ReducedProcChancePast60>("spell_reduced_proc_chance_past60");
}
