/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_SHADOWFANG_H
#define DEF_SHADOWFANG_H

#include "AI/ScriptDevAI/include/sc_instance.h"
#include "AI/ScriptDevAI/base/CombatAI.h"
enum
{
    MAX_ENCOUNTER           = 6,

    TYPE_FREE_NPC           = 1,
    TYPE_RETHILGORE         = 2,
    TYPE_FENRUS             = 3,
    TYPE_NANDOS             = 4,
    TYPE_INTRO              = 5,
    TYPE_VOIDWALKER         = 6,

    SAY_BOSS_DIE_AD         = -1033007,
    SAY_BOSS_DIE_AS         = -1033008,
    YELL_PACK_DEAD          = -1033020,
    SAY_ARUGAL_INTRO_1             = -1033009,
    SAY_ARUGAL_INTRO_2             = -1033010,
    SAY_ARUGAL_INTRO_3             = -1033011,
    SAY_ARUGAL_INTRO_4             = -1033012,

    YELL_FENRUS                     = -1033013,

    SPELL_SPAWN             = 7741,
    SPELL_FIRE              = 6422,

    NPC_ASH                 = 3850,
    NPC_ADA                 = 3849,
    NPC_ARUGAL              = 10000,                        //"Arugal" says intro text
    NPC_ARCHMAGE_ARUGAL     = 4275,                         //"Archmage Arugal" does Fenrus event
    NPC_FENRUS              = 4274,                         // used to summon Arugal in Fenrus event
    NPC_VOIDWALKER          = 4627,
    NPC_VINCENT             = 4444,                         // Vincent should be "dead" is Arugal is done the intro already

    // Wolf Master Nandos intro event
    NPC_MASTER_NANDOS       = 3927,
    NPC_LUPINE_HORROR       = 3863,
    NPC_WOLFGUARD_WORG      = 5058,
    NPC_BLEAK_WORG          = 3861,
    NPC_SLAVERING_WORG      = 3862,

    GO_COURTYARD_DOOR       = 18895,                        // door to open when talking to NPC's
    GO_SORCERER_DOOR        = 18972,                        // door to open when Fenrus the Devourer
    GO_ARUGAL_DOOR          = 18971,                        // door to open when Wolf Master Nandos
    GO_ARUGAL_FOCUS         = 18973,                        // this generates the lightning visual in the Fenrus event
};


enum {
    VINCENT_DEATH = 1,
    ARUGAL_VISIBLE,
    ARUGAL_TELEPORT_IN,
    ARUGAL_EMOTE_POINT,
    ARUGAL_EMOTE_EXCLAMATION,
    ARUGAL_EMOTE_LAUGH,
    ARUGAL_TELEPORT_OUT,
    ARUGAL_INTRO_DONE,
    ARCHMAGE_FIRE,
    ARCHMAGE_LIGHTNING,
    ARCHMAGE_INVIS,
    ARCHMAGE_VOIDWALKERS,
};

struct Waypoint
{
    float fX, fY, fZ;
};

struct SpawnPoint
{
    float fX, fY, fZ, fO;
};

// Cordinates for voidwalker spawns
static const SpawnPoint VWSpawns[] =
{
    // fX        fY         fZ        fO
    { -155.352f, 2172.780f, 128.448f, 4.679f},
    { -147.059f, 2163.193f, 128.696f, 0.128f},
    { -148.869f, 2180.859f, 128.448f, 1.814f},
    { -140.203f, 2175.263f, 128.448f, 0.373f}
};

// Coordinates for Voidwalker home
static const Waypoint voidwalkerHome = { -146.06f,  2172.84f, 127.953f};  // This is the initial location, in the middle of the room


static const Waypoint nandosMovement = {-170.6f, 2182.45f, 151.91f};

class instance_shadowfang_keep : public ScriptedInstance, public DialogueHelper
{
    public:
        instance_shadowfang_keep(Map* pMap);

        void Initialize() override;

        void OnCreatureCreate(Creature* pCreature) override;
        void OnCreatureDeath(Creature* pCreature) override;
        void OnObjectCreate(GameObject* pGo) override;
        void JustDidDialogueStep(int32 iEntry) override;
        void DoSpeech();

        void SetData(uint32 uiType, uint32 uiData) override;
        uint32 GetData(uint32 uiType) const override;

        const char* Save() const override { return m_strInstData.c_str(); }
        void Load(const char* chrIn) override;

        void Update(const uint32 diff) override;

    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;

        GuidList m_lNandosWolvesGuids;
};

struct mob_arugal_voidwalker_baseAI : virtual CombatAI
{
    int8 m_position;           // 0 - leader, 1 - behind-right, 2 - behind, 3 - behind-left
    ObjectGuid m_leaderGuid;

    void SetLeader()
    {
        // No leader found or already dead: set ourselves and start following the waypoints
        m_leaderGuid = m_creature->GetObjectGuid();
        m_position = 0;
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MoveWaypoint(0);
    }

    void SetFollower(ObjectGuid leaderGuid, uint8 position)
    {
        m_leaderGuid = leaderGuid;
        m_position = position;

        // Start following the leader
        if (Creature* leader = m_creature->GetMap()->GetCreature(m_leaderGuid))
            m_creature->GetMotionMaster()->MoveFollow(leader, 1.0f, M_PI / 2 * m_position);
        else
            script_error_log("mob_arugal_voidwalker for %s: tried to follow master but master not found in map.", m_creature->GetGuidStr().c_str());
    }
};

#endif
