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
SDName: Bosses_Opera
SD%Complete: 95
SDComment: Oz, Hood, and RAJ event implemented. Spell timers may need adjustments.
Romulo's Poisoned Thrust will now be used less frequently. - Patch_2.1.0
SDCategory: Karazhan
EndScriptData */

#include "AI/ScriptDevAI/include/sc_common.h"
#include "karazhan.h"
#include "AI/ScriptDevAI/base/CombatAI.h"

/***********************************/
/*** OPERA WIZARD OF OZ EVENT *****/
/*********************************/

enum
{
    SAY_DOROTHEE_DEATH          = 15068,
    SAY_DOROTHEE_SUMMON         = 15066,
    SAY_DOROTHEE_TITO_DEATH     = 15069,
    SAY_DOROTHEE_AGGRO          = 15067,

    SAY_ROAR_AGGRO              = 19276,
    SAY_ROAR_DEATH              = 15133,
    SAY_ROAR_SLAY               = 15131,

    SAY_STRAWMAN_AGGRO          = 19277,
    SAY_STRAWMAN_DEATH          = 15135,
    SAY_STRAWMAN_SLAY           = 15136,

    SAY_TINHEAD_AGGRO           = 19278,
    SAY_TINHEAD_DEATH           = 15155,
    SAY_TINHEAD_SLAY            = 15156,
    EMOTE_RUST                  = 14361,

    SAY_CRONE_INTRO             = 15050,
    SAY_CRONE_INTRO2            = 15332,
    SAY_CRONE_DEATH             = 15052,
    SAY_CRONE_SLAY              = 15051,

    /**** Spells ****/
    // Dorothee
    SPELL_WATERBOLT             = 31012,
    SPELL_FRIGHTENEDSCREAM      = 31013,
    SPELL_SUMMONTITO            = 31014,

    // Strawman
    SPELL_BRAIN_BASH            = 31046,
    SPELL_BRAIN_WIPE            = 31069,
    SPELL_CONFLAG_PROC          = 31073,            // procs 31075 on fire damage

    // Tinhead
    SPELL_CLEAVE                = 31043,
    SPELL_RUST                  = 31086,

    // Roar
    SPELL_MANGLE                = 31041,
    SPELL_SHRED                 = 31042,
    SPELL_FRIGHTENED_SCREAM     = 31013,

    // Crone
    SPELL_CHAIN_LIGHTNING       = 32337,
    SPELL_FIERY_BROOM_PROC      = 32339,            // passive spell causing periodic damage

    // Cyclone
    SPELL_CYCLONE               = 32334,
    SPELL_CYCLONE_VISUAL        = 32332,

    /** Creature Entries **/
    NPC_TITO                    = 17548,
    NPC_CYCLONE                 = 18412,
};

enum DorotheeActions // order based on priority
{
    DOROTHEE_ACTION_MAX,
    DOROTHEE_INTRO,
    DOROTHEE_ACTION_SUMMONTITO,
    DOROTHEE_AGGRO,
};

struct boss_dorotheeAI : public CombatAI
{
    boss_dorotheeAI(Creature* creature) : CombatAI(creature, DOROTHEE_ACTION_MAX), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        SetReactState(REACT_PASSIVE);
        AddCustomAction(DOROTHEE_INTRO, 2000u, [&]() { HandleIntro(); });
        AddCustomAction(DOROTHEE_AGGRO, 12000u, [&]() { HandleAggro(); });
        AddCustomAction(DOROTHEE_ACTION_SUMMONTITO, 36500u, [&]() { HandleSummonTito(); }, TIMER_COMBAT_COMBAT);
        SetRangedMode(true, 40.f, TYPE_FULL_CASTER);
    }

    ScriptedInstance* m_instance;

    void Reset() override
    {
        CombatAI::Reset();

        SetCombatMovement(true);
        SetCombatScriptStatus(false);
    }

    void JustReachedHome() override
    {
        if (m_instance)
            m_instance->SetData(TYPE_OPERA, FAIL);

        m_creature->ForcedDespawn();
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoBroadcastText(SAY_DOROTHEE_DEATH, m_creature);
    }

    void JustSummoned(Creature* pSummoned) override
    {        
        if (m_creature->GetVictim())
            pSummoned->AI()->AttackStart(m_creature->GetVictim());
    }

    void SummonedCreatureJustDied(Creature* pSummoned) override
    {
        if (pSummoned->GetEntry() == NPC_TITO)
            DoBroadcastText(SAY_DOROTHEE_TITO_DEATH, m_creature);
    }

    void HandleSummonTito()
    {
        if (DoCastSpellIfCan(m_creature, SPELL_SUMMONTITO) == CAST_OK)        
            DoBroadcastText(SAY_DOROTHEE_SUMMON, m_creature);
    }

    void HandleIntro()
    {
        DoBroadcastText(SAY_DOROTHEE_AGGRO, m_creature);
    }

    void HandleAggro()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
        SetReactState(REACT_AGGRESSIVE);
        m_creature->SetInCombatWithZone();
        AttackClosestEnemy();
        if (!m_creature->IsInCombat())
            JustReachedHome();
    }
};


enum StrawmanActions
{
    STRAWMAN_ACTION_AGGRO,
    STRAWMAN_ACTION_MAX,
};

struct boss_strawmanAI : public CombatAI
{
    boss_strawmanAI(Creature* creature) : CombatAI(creature, STRAWMAN_ACTION_MAX), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        AddCustomAction(STRAWMAN_ACTION_AGGRO, 27000u, [&]() { HandleAggro(); });
        SetReactState(REACT_PASSIVE);
        Reset();
    }

    ScriptedInstance* m_instance;

    void Reset() override
    {
        CombatAI::Reset();
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoCastSpellIfCan(m_creature, SPELL_CONFLAG_PROC);
        DoBroadcastText(SAY_STRAWMAN_AGGRO, m_creature);
    }

    void JustReachedHome() override
    {
        if (m_instance)
            m_instance->SetData(TYPE_OPERA, FAIL);

        m_creature->ForcedDespawn();
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoBroadcastText(SAY_STRAWMAN_DEATH, m_creature);
    }

    void KilledUnit(Unit* /*pVictim*/) override
    {
        DoBroadcastText(SAY_STRAWMAN_SLAY, m_creature);
    }

    void HandleAggro()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
        SetReactState(REACT_AGGRESSIVE);
        m_creature->SetInCombatWithZone();
        AttackClosestEnemy();
        if (!m_creature->IsInCombat())
            JustReachedHome();
    }
};

enum TinheadActions
{
    TINHEAD_ACTION_AGGRO,
    TINHEAD_ACTION_MAX,
};

struct boss_tinheadAI : public CombatAI
{
    boss_tinheadAI(Creature* creature) : CombatAI(creature, TINHEAD_ACTION_MAX), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        AddCustomAction(TINHEAD_ACTION_AGGRO, 37000u, [&]() { HandleAggro(); });
        SetReactState(REACT_PASSIVE);
        Reset();
    }

    ScriptedInstance* m_instance;

    void Reset() override
    {
        CombatAI::Reset();
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoBroadcastText(SAY_TINHEAD_AGGRO, m_creature);
    }

    void JustReachedHome() override
    {
        if (m_instance)
            m_instance->SetData(TYPE_OPERA, FAIL);

        m_creature->ForcedDespawn();
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoBroadcastText(SAY_TINHEAD_DEATH, m_creature);
    }

    void KilledUnit(Unit* /*pVictim*/) override
    {
        DoBroadcastText(SAY_TINHEAD_SLAY, m_creature);
    }

    void OnSpellCast(SpellEntry const* spellInfo, Unit* /*target*/) override
    {
        switch (spellInfo->Id)
        {
            case SPELL_RUST:
                DoBroadcastText(EMOTE_RUST, m_creature);
                break;
        }
    }

    void HandleAggro()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
        SetReactState(REACT_AGGRESSIVE);
        m_creature->SetInCombatWithZone();
        AttackClosestEnemy();
        if (!m_creature->IsInCombat())
            JustReachedHome();
    }
};

enum RoadActions
{
    ROAR_ACTION_AGGRO,
    ROAR_ACTION_MAX,
};

struct boss_roarAI : public CombatAI
{
    boss_roarAI(Creature* creature) : CombatAI(creature, ROAR_ACTION_MAX), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        AddCustomAction(ROAR_ACTION_AGGRO, 17000u, [&]() { HandleAggro(); });
        SetReactState(REACT_PASSIVE);
        Reset();
    }

    ScriptedInstance* m_instance;

    void Reset() override
    {
        CombatAI::Reset();
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoBroadcastText(SAY_ROAR_AGGRO, m_creature);
    }

    void JustReachedHome() override
    {
        if (m_instance)
            m_instance->SetData(TYPE_OPERA, FAIL);

        m_creature->ForcedDespawn();
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoBroadcastText(SAY_ROAR_DEATH, m_creature);
    }

    void KilledUnit(Unit* /*pVictim*/) override
    {
        DoBroadcastText(SAY_ROAR_SLAY, m_creature);
    }

        void HandleAggro()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
        SetReactState(REACT_AGGRESSIVE);
        m_creature->SetInCombatWithZone();
        AttackClosestEnemy();
        if (!m_creature->IsInCombat())
            JustReachedHome();
    }
};

static const float afCycloneSpawnLoc1[4] = { -10908.86f, -1773.627f, 90.55865f, 5.833215f };
static const float afCycloneSpawnLoc2[4] = { -10910.79f, -1771.201f, 90.56122f, 0.3642556f };
static const float afCycloneSpawnLoc3[4] = { -10907.68f, -1778.651f, 90.56018f, 2.44127f };

enum CroneActions
{
    CRONE_ACTION_INTRO,
    CRONE_ACTION_AGGRO,
    CRONE_ACTION_MAX,
};

struct boss_croneAI : public CombatAI
{
    boss_croneAI(Creature* creature) : CombatAI(creature, CRONE_ACTION_MAX), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        AddCustomAction(CRONE_ACTION_INTRO, 6000u, [&]() { HandleIntro(); });
        AddCustomAction(CRONE_ACTION_AGGRO, 9000u, [&]() { HandleAggro(); });
        m_creature->CastSpell(m_creature, SPELL_FIERY_BROOM_PROC, TRIGGERED_OLD_TRIGGERED);
        SetReactState(REACT_PASSIVE);
        Reset();
    }

    ScriptedInstance* m_instance;

    void Reset() override
    {
        CombatAI::Reset();
    }

    void JustReachedHome() override
    {
        if (m_instance)
            m_instance->SetData(TYPE_OPERA, FAIL);

        m_creature->ForcedDespawn();
    }

    void Aggro(Unit* /*pWho*/) override
    {
        // spawn the cyclones on aggro
        if (Creature *cMainCyclone = m_creature->SummonCreature(NPC_CYCLONE, afCycloneSpawnLoc1[0], afCycloneSpawnLoc1[1], afCycloneSpawnLoc1[2], afCycloneSpawnLoc1[3], TEMPSPAWN_DEAD_DESPAWN, 0))
        {
            if (Creature *cFollowCyclone = m_creature->SummonCreature(NPC_CYCLONE, afCycloneSpawnLoc2[0], afCycloneSpawnLoc2[1], afCycloneSpawnLoc2[2], afCycloneSpawnLoc2[3], TEMPSPAWN_DEAD_DESPAWN, 0))
                cFollowCyclone->GetMotionMaster()->MoveFollow(cMainCyclone, cFollowCyclone->GetDistance(cMainCyclone), cFollowCyclone->GetAngle(cMainCyclone));
            if (Creature *cFollowCyclone = m_creature->SummonCreature(NPC_CYCLONE, afCycloneSpawnLoc3[0], afCycloneSpawnLoc3[1], afCycloneSpawnLoc3[2], afCycloneSpawnLoc3[3], TEMPSPAWN_DEAD_DESPAWN, 0))
                cFollowCyclone->GetMotionMaster()->MoveFollow(cMainCyclone, cFollowCyclone->GetDistance(cMainCyclone), cFollowCyclone->GetAngle(cMainCyclone));
        }
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoBroadcastText(SAY_CRONE_DEATH, m_creature);

        if (m_instance)
            m_instance->SetData(TYPE_OPERA, DONE);
    }

    void JustSummoned(Creature* pSummoned) override
    {
        pSummoned->CastSpell(pSummoned, SPELL_CYCLONE, TRIGGERED_OLD_TRIGGERED);
        pSummoned->CastSpell(pSummoned, SPELL_CYCLONE_VISUAL, TRIGGERED_OLD_TRIGGERED);
    }

    void HandleIntro()
    {
        DoBroadcastText(urand(0, 1) ? SAY_CRONE_INTRO : SAY_CRONE_INTRO2, m_creature); // TODO: should be said at player who started event
    }
                
    void HandleAggro()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
        SetReactState(REACT_AGGRESSIVE);
        m_creature->SetInCombatWithZone();
        AttackClosestEnemy();
        if (!m_creature->IsInCombat())
            JustReachedHome();
    }
};

/**************************************/
/**** Opera Red Riding Hood Event ****/
/************************************/

enum
{
    /**** Yells for the Wolf ****/
    SAY_WOLF_SPAWN                  = 14212,
    SAY_WOLF_SLAY                   = 15153,
    SAY_WOLF_RED_RIDING_HOOD        = 14213,
    SOUND_WOLF_DEATH                = 9275,                // Only sound on death, no text.

    /**** Spells For The Wolf ****/
    SPELL_PICK_RED_RIDING_HOOD      = 30769,               // targeting spell - triggers 30768
    SPELL_LITTLE_RED_RIDING_HOOD    = 30768,               // Little Red Riding Hood - triggers 30753
    SPELL_RED_RIDING_HOOD           = 30756,
    SPELL_TERRIFYING_HOWL           = 30752,
    SPELL_WIDE_SWIPE                = 30761,

    GOSSIP_ITEM_GRANDMA_FIRST       = -3532020,
    GOSSIP_ITEM_GRANDMA_SECOND      = -3532021,
    GOSSIP_ITEM_GRANDMA_THIRD       = -3532005,

    TEXT_ID_GRANDMA_FIRST           = 9009,
    TEXT_ID_GRANDMA_SECOND          = 9010,
    TEXT_ID_GRANDMA_THIRD           = 9011,

    GOSSIP_MENU_ID_GRANDMA_FIRST    = 7441,
    GOSSIP_MENU_ID_GRANDMA_SECOND   = 7442,
    GOSSIP_MENU_ID_GRANDMA_THIRD    = 7443,

    TEXT_ID_GRANDMA                 = 8990, // Unk purpose

    /**** The Wolf's Entry ****/
    NPC_BIG_BAD_WOLF                = 17521
};

bool GossipHello_npc_grandmother(Player* pPlayer, Creature* creature)
{
    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GRANDMA_FIRST, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    pPlayer->SET_GOSSIP_MENU_ID(GOSSIP_MENU_ID_GRANDMA_FIRST);
    pPlayer->SEND_GOSSIP_MENU(TEXT_ID_GRANDMA_FIRST, creature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_grandmother(Player* pPlayer, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GRANDMA_SECOND, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SET_GOSSIP_MENU_ID(GOSSIP_MENU_ID_GRANDMA_SECOND);
            pPlayer->SEND_GOSSIP_MENU(TEXT_ID_GRANDMA_SECOND, creature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GRANDMA_THIRD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SET_GOSSIP_MENU_ID(GOSSIP_MENU_ID_GRANDMA_THIRD);
            pPlayer->SEND_GOSSIP_MENU(TEXT_ID_GRANDMA_THIRD, creature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            if (Creature* bigBadWolf = creature->SummonCreature(NPC_BIG_BAD_WOLF, 0, 0, 0, 0, TEMPSPAWN_DEAD_DESPAWN, 0))
            creature->ForcedDespawn();
            break;
    }

    return true;
}

struct npc_grandmotherAI : public ScriptedAI
{
    npc_grandmotherAI(Creature* creature) : ScriptedAI(creature), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        Reset();
    }

    ScriptedInstance* m_instance;

    void Reset() override
    {

    }

    void UpdateAI(const uint32 /*diff*/) override
    {
        if (m_instance)
        {
            if (!m_instance->GetPlayerInMap(true, false))
            {
                if (m_instance)
                    m_instance->SetData(TYPE_OPERA, FAIL);

                m_creature->ForcedDespawn();
            }
        }
    }
};

enum BigBadWolfActions // order based on priority
{
    BIG_BAD_WOLF_MAX,
    BIG_BAD_WOLF_ATTACK_DELAY
};

struct boss_bigbadwolfAI : public CombatAI
{
    boss_bigbadwolfAI(Creature* creature) : CombatAI(creature, BIG_BAD_WOLF_MAX), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        AddCustomAction(BIG_BAD_WOLF_ATTACK_DELAY, 2000u, [&]() { HandleAttackDelay(); });
    }

    ScriptedInstance* m_instance;

    void Reset() override
    {
        CombatAI::Reset();
    }

    void JustReachedHome() override
    {
        if (m_instance)
            m_instance->SetData(TYPE_OPERA, FAIL);

        m_creature->ForcedDespawn();
    }

    void JustRespawned() override
    {
        CombatAI::JustRespawned();
        DoBroadcastText(SAY_WOLF_SPAWN, m_creature);
        SetReactState(REACT_DEFENSIVE);
    }

    void HandleAttackDelay()
    {
        SetReactState(REACT_AGGRESSIVE);
        m_creature->SetInCombatWithZone();
        AttackClosestEnemy();
    }

    void KilledUnit(Unit* victim) override // Move to AddOnKillText with BroadcastText
    {
        if (victim->GetTypeId() != TYPEID_PLAYER)
            return;

        DoBroadcastText(SAY_WOLF_SLAY, m_creature);
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoPlaySoundToSet(m_creature, SOUND_WOLF_DEATH);

        if (m_instance)
            m_instance->SetData(TYPE_OPERA, DONE);
    }

    void OnSpellCast(SpellEntry const* spellInfo, Unit* /*target*/) override
    {
        switch (spellInfo->Id)
        {
            case SPELL_PICK_RED_RIDING_HOOD:
                DoBroadcastText(SAY_WOLF_RED_RIDING_HOOD, m_creature);
                break;
        }
    }
};

/**********************************************/
/******** Opera Romeo and Juliet Event *******/
/********************************************/

enum
{
    /**** Speech *****/
    SAY_JULIANNE_AGGRO              = -1532046,
    SAY_JULIANNE_ENTER              = -1532047,
    SAY_JULIANNE_DEATH01            = -1532048,
    SAY_JULIANNE_DEATH02            = -1532049,
    SAY_JULIANNE_RESURRECT          = -1532050,
    SAY_JULIANNE_SLAY               = -1532051,

    SAY_ROMULO_AGGRO                = -1532052,
    SAY_ROMULO_DEATH                = -1532053,
    SAY_ROMULO_ENTER                = -1532054,
    SAY_ROMULO_RESURRECT            = -1532055,
    SAY_ROMULO_SLAY                 = -1532056,

    /***** Spells For Julianne *****/
    SPELL_BLINDING_PASSION          = 30890,
    SPELL_DEVOTION                  = 30887,
    SPELL_ETERNAL_AFFECTION         = 30878,
    SPELL_POWERFUL_ATTRACTION       = 30889,
    SPELL_DRINK_POISON              = 30907,

    /***** Spells For Romulo ****/
    SPELL_BACKWARD_LUNGE            = 30815,
    SPELL_DARING                    = 30841,
    SPELL_DEADLY_SWATHE             = 30817,
    SPELL_POISON_THRUST             = 30822,

    /**** Other Misc. Spells ****/
    SPELL_FULL_HEALTH               = 43979,                // res effect on Julianne
    SPELL_UNDYING_LOVE              = 30951,                // res effect on Romulo
    SPELL_SUICIDE_WHILE_DEAD        = 30966,                // suicide spell for Julianne and Romulo
};

enum OperaPhase
{
    PHASE_JULIANNE      = 0,
    PHASE_ROMULO        = 1,
    PHASE_BOTH          = 2,
};

static const float afRomuloSpawnLoc[4] = { -10893.62f, -1760.78f, 90.55f, 4.76f};

struct boss_julianneAI : public ScriptedAI
{
    boss_julianneAI(Creature* creature) : ScriptedAI(creature), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        Reset();
    }

    ScriptedInstance* m_instance;

    OperaPhase m_Phase;

    uint32 m_uiBlindingPassionTimer;
    uint32 m_uiDevotionTimer;
    uint32 m_uiEternalAffectionTimer;
    uint32 m_uiPowerfulAttractionTimer;
    uint32 m_uiSummonRomuloTimer;
    uint32 m_uiResurrectSelfTimer;
    uint32 m_uiAggroTimer;

    bool m_bIsFakingDeath;

    void Reset() override
    {
        m_Phase                     = PHASE_JULIANNE;

        m_uiBlindingPassionTimer    = 30000;
        m_uiDevotionTimer           = 15000;
        m_uiEternalAffectionTimer   = 25000;
        m_uiPowerfulAttractionTimer = 5000;
        m_uiSummonRomuloTimer       = 0;
        m_uiResurrectSelfTimer      = 0;

        m_bIsFakingDeath            = false;

        m_uiAggroTimer = 9000;

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoScriptText(SAY_JULIANNE_AGGRO, m_creature);
    }

    void JustReachedHome() override
    {
        if (m_instance)
            m_instance->SetData(TYPE_OPERA, FAIL);

        m_creature->ForcedDespawn();
    }

    void DamageTaken(Unit* /*dealer*/, uint32& damage, DamageEffectType /*damagetype*/, SpellEntry const* /*spellInfo*/) override
    {
        if (damage < m_creature->GetHealth())
            return;

        damage = std::min(damage, m_creature->GetHealth() - 1);

        if (m_bIsFakingDeath)
            return;

        if (m_Phase == PHASE_JULIANNE)
        {
            // Prepare fake death
            if (DoCastSpellIfCan(m_creature, SPELL_DRINK_POISON, CAST_INTERRUPT_PREVIOUS) == CAST_OK)
            {
                m_Phase               = PHASE_BOTH;
                m_bIsFakingDeath      = true;
                m_uiSummonRomuloTimer = 12000;
            }
        }
        else if (m_Phase == PHASE_BOTH)
        {
            // set fake death and allow 10 sec timer to kill Romulos
            DoScriptText(SAY_JULIANNE_DEATH02, m_creature);
            DoSetFakeDeath();
            m_uiResurrectSelfTimer = 10000;
        }
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE);

        if (m_instance)
            m_instance->SetData(TYPE_OPERA, DONE);
    }

    void KilledUnit(Unit* pVictim) override
    {
        if (pVictim->GetTypeId() != TYPEID_PLAYER)
            return;

        DoScriptText(SAY_JULIANNE_SLAY, m_creature);
    }

    void JustSummoned(Creature* pSummoned) override
    {
        if (m_creature->GetVictim())
            pSummoned->AI()->AttackStart(m_creature->GetVictim());
    }

    // Wrapper to set fake death
    void DoSetFakeDeath()
    {
        m_bIsFakingDeath = true;

        m_creature->InterruptNonMeleeSpells(false);
        m_creature->StopMoving();
        m_creature->ClearComboPointHolders();
        m_creature->RemoveAllAurasOnDeath();
        m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_20_PERCENT, false);
        m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_35_PERCENT, false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE);
        m_creature->ClearAllReactives();
        m_creature->SetTarget(nullptr);
        m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
        SetCombatMovement(false);
    }

    // Wrapper to remove fake death
    void DoRemoveFakeDeath()
    {
        m_bIsFakingDeath = false;

        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE);
        DoResetThreat();
        SetCombatMovement(true);
        DoStartMovement(m_creature->GetVictim());
    }

    // Wrapper to start phase 3
    void DoHandleRomuloResurrect()
    {
        m_creature->CastSpell(nullptr, SPELL_FULL_HEALTH, TRIGGERED_NONE);
        DoRemoveFakeDeath();
        DoCastSpellIfCan(m_creature, SPELL_UNDYING_LOVE);
        DoScriptText(SAY_JULIANNE_RESURRECT, m_creature);
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        // spawn Romulo on timer after fake death
        if (m_uiSummonRomuloTimer)
        {
            if (m_uiSummonRomuloTimer <= uiDiff)
            {
                m_creature->SummonCreature(NPC_ROMULO, afRomuloSpawnLoc[0], afRomuloSpawnLoc[1], afRomuloSpawnLoc[2], afRomuloSpawnLoc[3], TEMPSPAWN_DEAD_DESPAWN, 0);
                m_uiSummonRomuloTimer = 0;
            }
            else
                m_uiSummonRomuloTimer -= uiDiff;
        }

        if (m_uiResurrectSelfTimer)
        {
            if (m_uiResurrectSelfTimer <= uiDiff)
            {
                if (m_instance)
                {
                    if (Creature* pRomulo = m_instance->GetSingleCreatureFromStorage(NPC_ROMULO))
                    {
                        // if Romulos is dead, then self kill
                        if (pRomulo->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE))
                        {
                            m_creature->CastSpell(nullptr, SPELL_SUICIDE_WHILE_DEAD, TRIGGERED_OLD_TRIGGERED);
                            pRomulo->CastSpell(nullptr, SPELL_SUICIDE_WHILE_DEAD, TRIGGERED_OLD_TRIGGERED);
                        }
                        else
                        {
                            DoRemoveFakeDeath();
                            DoCastSpellIfCan(m_creature, SPELL_FULL_HEALTH, CAST_TRIGGERED);
                        }
                    }
                }
                m_uiResurrectSelfTimer = 0;
            }
            else
                m_uiResurrectSelfTimer -= uiDiff;
        }

        if (m_uiAggroTimer)
        {
            if (m_uiAggroTimer <= uiDiff)
            {
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
                SetReactState(REACT_AGGRESSIVE);
                m_creature->SetInCombatWithZone();
                AttackClosestEnemy();
                if (!m_creature->IsInCombat())
                    JustReachedHome();
                m_uiAggroTimer = 0;
            }
            else
                m_uiAggroTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        // don't use spells during transition
        if (m_bIsFakingDeath)
            return;

        if (m_uiBlindingPassionTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, nullptr, SELECT_FLAG_PLAYER))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_BLINDING_PASSION) == CAST_OK)
                    m_uiBlindingPassionTimer = urand(30000, 45000);
            }
        }
        else
            m_uiBlindingPassionTimer -= uiDiff;

        if (m_uiDevotionTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_DEVOTION) == CAST_OK)
                m_uiDevotionTimer = urand(15000, 45000);
        }
        else
            m_uiDevotionTimer -= uiDiff;

        if (m_uiPowerfulAttractionTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1, nullptr, SELECT_FLAG_PLAYER))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_POWERFUL_ATTRACTION) == CAST_OK)
                    m_uiPowerfulAttractionTimer = urand(5000, 30000);
            }
        }
        else
            m_uiPowerfulAttractionTimer -= uiDiff;

        if (m_uiEternalAffectionTimer < uiDiff)
        {
            if (Unit* pTarget = DoSelectLowestHpFriendly(30.0f))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_ETERNAL_AFFECTION) == CAST_OK)
                    m_uiEternalAffectionTimer = urand(45000, 60000);
            }
        }
        else
            m_uiEternalAffectionTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

// 30907 - Drink Poison
struct DrinkPoisonJulianne : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex /*effIdx*/) const override
    {
        Unit* target = spell->GetUnitTarget();
        // Set fake death on poison
        if (boss_julianneAI* julianneAI = dynamic_cast<boss_julianneAI*>(target->AI()))
            julianneAI->DoSetFakeDeath();

        DoScriptText(SAY_JULIANNE_DEATH01, target);
    }
};

struct boss_romuloAI : public ScriptedAI
{
    boss_romuloAI(Creature* creature) : ScriptedAI(creature), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        Reset();
    }

    ScriptedInstance* m_instance;

    OperaPhase m_Phase;

    uint32 m_uiBackwardLungeTimer;
    uint32 m_uiDaringTimer;
    uint32 m_uiDeadlySwatheTimer;
    uint32 m_uiPoisonThrustTimer;
    uint32 m_uiResurrectTimer;
    uint32 m_uiResurrectSelfTimer;

    bool m_bIsFakingDeath;

    void Reset() override
    {
        m_Phase                 = PHASE_ROMULO;

        m_uiBackwardLungeTimer  = 15000;
        m_uiDaringTimer         = 20000;
        m_uiDeadlySwatheTimer   = 25000;
        m_uiPoisonThrustTimer   = 10000;
        m_uiResurrectTimer      = 0;
        m_uiResurrectSelfTimer  = 0;

        m_bIsFakingDeath        = false;
    }

    void JustReachedHome() override
    {
        if (m_instance)
            m_instance->SetData(TYPE_OPERA, FAIL);

        m_creature->ForcedDespawn();
    }

    void DamageTaken(Unit* /*dealer*/, uint32& damage, DamageEffectType /*damagetype*/, SpellEntry const* /*spellInfo*/) override
    {
        if (damage < m_creature->GetHealth())
            return;

        damage = std::min(damage, m_creature->GetHealth() - 1);

        if (m_bIsFakingDeath)
            return;

        if (m_Phase == PHASE_ROMULO)
        {
            DoScriptText(SAY_ROMULO_DEATH, m_creature);
            DoSetFakeDeath();
            m_Phase             = PHASE_BOTH;
            m_uiResurrectTimer  = 10000;
        }
        else if (m_Phase == PHASE_BOTH)
        {
            // set fake death and allow 10 sec timer to kill Julianne
            DoSetFakeDeath();
            m_uiResurrectSelfTimer = 10000;
        }
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoScriptText(SAY_ROMULO_AGGRO, m_creature);
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE);

        if (m_instance)
            m_instance->SetData(TYPE_OPERA, DONE);
    }

    void KilledUnit(Unit* pVictim) override
    {
        if (pVictim->GetTypeId() != TYPEID_PLAYER)
            return;

        DoScriptText(SAY_ROMULO_SLAY, m_creature);
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell) override
    {
        // remove fake death on res
        if (pSpell->Id == SPELL_UNDYING_LOVE && pCaster->GetEntry() == NPC_JULIANNE)
            DoRemoveFakeDeath();
    }

    // Wrapper to set fake death
    void DoSetFakeDeath()
    {
        m_bIsFakingDeath = true;

        m_creature->InterruptNonMeleeSpells(false);
        m_creature->StopMoving();
        m_creature->ClearComboPointHolders();
        m_creature->RemoveAllAurasOnDeath();
        m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_20_PERCENT, false);
        m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_35_PERCENT, false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE);
        m_creature->ClearAllReactives();
        m_creature->SetTarget(nullptr);
        m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
        SetCombatMovement(false);
    }

    // Wrapper to remove fake death
    void DoRemoveFakeDeath()
    {
        m_bIsFakingDeath = false;

        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE);
        DoResetThreat();
        SetCombatMovement(true);
        DoStartMovement(m_creature->GetVictim());
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        // Resurrect both of them at the beginning of phase 3
        if (m_uiResurrectTimer)
        {
            if (m_uiResurrectTimer <= uiDiff)
            {
                if (m_instance)
                {
                    if (Creature* pJulianne = m_instance->GetSingleCreatureFromStorage(NPC_JULIANNE))
                    {
                        if (boss_julianneAI* pJulianneAI = dynamic_cast<boss_julianneAI*>(pJulianne->AI()))
                            pJulianneAI->DoHandleRomuloResurrect();
                    }
                }
                m_uiResurrectTimer = 0;
            }
            else
                m_uiResurrectTimer -= uiDiff;
        }

        if (m_uiResurrectSelfTimer)
        {
            if (m_uiResurrectSelfTimer <= uiDiff)
            {
                if (m_instance)
                {
                    if (Creature* pJulianne = m_instance->GetSingleCreatureFromStorage(NPC_JULIANNE))
                    {
                        // if Julianne is dead, then self kill
                        if (pJulianne->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE))
                        {
                            m_creature->CastSpell(nullptr, SPELL_SUICIDE_WHILE_DEAD, TRIGGERED_OLD_TRIGGERED);
                            pJulianne->CastSpell(nullptr, SPELL_SUICIDE_WHILE_DEAD, TRIGGERED_OLD_TRIGGERED);
                        }
                        else
                        {
                            DoRemoveFakeDeath();
                            DoScriptText(SAY_ROMULO_RESURRECT, m_creature);
                            DoCastSpellIfCan(m_creature, SPELL_FULL_HEALTH, CAST_TRIGGERED);
                        }
                    }
                }
                m_uiResurrectSelfTimer = 0;
            }
            else
                m_uiResurrectSelfTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        // don't use spells on fake death
        if (m_bIsFakingDeath)
            return;

        if (m_uiBackwardLungeTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BACKWARD_LUNGE) == CAST_OK)
                m_uiBackwardLungeTimer = urand(15000, 30000);
        }
        else
            m_uiBackwardLungeTimer -= uiDiff;

        if (m_uiDaringTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_DARING) == CAST_OK)
                m_uiDaringTimer = urand(20000, 40000);
        }
        else
            m_uiDaringTimer -= uiDiff;

        if (m_uiDeadlySwatheTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->GetVictim(), SPELL_DEADLY_SWATHE) == CAST_OK)
                m_uiDeadlySwatheTimer = urand(15000, 25000);
        }
        else
            m_uiDeadlySwatheTimer -= uiDiff;

        if (m_uiPoisonThrustTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->GetVictim(), SPELL_POISON_THRUST) == CAST_OK)
#ifdef PRENERF_2_0_3
                m_uiPoisonThrustTimer = urand(8000, 16000);
#else
                m_uiPoisonThrustTimer = urand(10000, 20000);
#endif
        }
        else
            m_uiPoisonThrustTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

struct spell_red_riding_hood_fixate : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const override
    {
        Unit* caster = aura->GetCaster();
        if (!caster || !caster->AI())
            return;
        if (apply)
        {
            caster->FixateTarget(aura->GetTarget());
            //caster->AI()->AttackStart(aura->GetTarget()); // visual change for immediate crosshair update - only safe with fixate
        }
        else
            caster->FixateTarget(nullptr);
    }
};

// 30769
struct spell_pick_red_ridding_hood : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex /*effIdx*/) const override
    {
        Unit* caster = spell->GetCaster();
        if (!caster || !caster->AI())
            return;

        Unit* target = caster->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, uint32(0), SELECT_FLAG_PLAYER);

        if (!target || target->GetTypeId() != TYPEID_PLAYER)
            return;

        // cast Little Red Riding Hood
        caster->CastSpell(target, SPELL_LITTLE_RED_RIDING_HOOD, TRIGGERED_OLD_TRIGGERED);
    }
};

void AddSC_bosses_opera()
{
    // Oz
    Script* pNewScript = new Script;
    pNewScript->Name = "boss_dorothee";
    pNewScript->GetAI = &GetNewAIInstance<boss_dorotheeAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_strawman";
    pNewScript->GetAI = &GetNewAIInstance<boss_strawmanAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_tinhead";
    pNewScript->GetAI = &GetNewAIInstance<boss_tinheadAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_roar";
    pNewScript->GetAI = &GetNewAIInstance<boss_roarAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_crone";
    pNewScript->GetAI = &GetNewAIInstance<boss_croneAI>;
    pNewScript->RegisterSelf();

    // Hood
    pNewScript = new Script;
    pNewScript->Name = "npc_grandmother";
    pNewScript->GetAI = &GetNewAIInstance<npc_grandmotherAI>;
    pNewScript->pGossipHello = &GossipHello_npc_grandmother;
    pNewScript->pGossipSelect = &GossipSelect_npc_grandmother;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_bigbadwolf";
    pNewScript->GetAI = &GetNewAIInstance<boss_bigbadwolfAI>;
    pNewScript->RegisterSelf();

    RegisterSpellScript<spell_red_riding_hood_fixate>("spell_red_riding_hood_fixate");
    RegisterSpellScript<spell_pick_red_ridding_hood>("spell_pick_red_ridding_hood");

    // Romeo And Juliet
    pNewScript = new Script;
    pNewScript->Name = "boss_julianne";
    pNewScript->GetAI = &GetNewAIInstance<boss_julianneAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_romulo";
    pNewScript->GetAI = &GetNewAIInstance<boss_romuloAI>;
    pNewScript->RegisterSelf();

    RegisterSpellScript<DrinkPoisonJulianne>("spell_drink_poison_julianne");
}