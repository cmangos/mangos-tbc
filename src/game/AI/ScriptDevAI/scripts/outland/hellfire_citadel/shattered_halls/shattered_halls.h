/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_SHATTERED_H
#define DEF_SHATTERED_H

enum
{
    MAX_ENCOUNTER               = 5,

    TYPE_NETHEKURSE             = 0,
    TYPE_OMROGG                 = 1,
    TYPE_BLADEFIST              = 2,                        // Note: if players skip Omrogg and go straight to Karagth then Omrogg comes to aid Karagth
    TYPE_EXECUTION              = 3,
    TYPE_GAUNTLET               = 4,
    TYPE_HALLOFFATHERS          = 5,                        // Hall of Fathers Spawn Event 1
    TYPE_HALLOFFATHERS_2        = 6,                        // Hall of Fathers Spawn Event 2

    NPC_NETHEKURSE              = 16807,
    NPC_KARGATH_BLADEFIST       = 16808,
    NPC_EXECUTIONER             = 17301,                    // must be killed for the executioner event

    NPC_SOLDIER_ALLIANCE_1      = 17288,                    // quest giver for 9524
    NPC_SOLDIER_ALLIANCE_2      = 17289,
    NPC_SOLDIER_ALLIANCE_3      = 17292,
    NPC_OFFICER_ALLIANCE        = 17290,                    // quest objective

    NPC_SOLDIER_HORDE_1         = 17294,                    // quest giver for 9525
    NPC_SOLDIER_HORDE_2         = 17295,
    NPC_SOLDIER_HORDE_3         = 17297,
    NPC_OFFICER_HORDE           = 17296,                    // quest objective

    // Halls of Father
    NPC_SENTRY = 16507,
    SENTRY_GUID = 5400054,
    SENTRY_SEC_GUID = 5400055,
    // 3rd legionnaire
    HALLOFFATHER_GUID_1 = 5400070,
    HALLOFFATHER_GUID_2 = 5400075,
    HALLOFFATHER_GUID_3 = 5400079,
    HALLOFFATHER_GUID_4 = 5400080,
    HALLOFFATHER_GUID_5 = 5400132,
    // 4th legionnaire
    HALLOFFATHER_GUID_6 = 5400076,
    HALLOFFATHER_GUID_7 = 5400071,
    HALLOFFATHER_GUID_8 = 5400133,
    HALLOFFATHER_GUID_9 = 5400072,
    HALLOFFATHER_GUID_10 = 5400081,
    // 5th legionnaire
    HALLOFFATHER_GUID_11 = 5400279,
    HALLOFFATHER_GUID_12 = 5400278,
    HALLOFFATHER_GUID_13 = 5400275,
    HALLOFFATHER_GUID_14 = 5400276,
    HALLOFFATHER_GUID_15 = 5400277,
    HALLOFFATHER_GUID_16 = 5400282,

    GO_NETHEKURSE_DOOR          = 182540,
    GO_NETHEKURSE_ENTER_DOOR    = 182539,

    // Gauntlet
    NPC_GAUNTLET_OF_FIRE        = 17692,
    NPC_SHATTERED_HAND_ZEALOT   = 17462,
    NPC_SHATTERED_HAND_ARCHER   = 17427,
    NPC_SCOUT                   = 17693,
    NPC_BLOOD_GUARD             = 17461,
    NPC_PORUNG                  = 20923,

    GO_BLAZE                    = 181915,

    SPELL_FLAMES                = 30979,

    SPELL_KARGATH_EXECUTIONER_1 = 39288,                    // 55 min - first prisoner - officer
    SPELL_KARGATH_EXECUTIONER_2 = 39289,                    // 10 min - second prisoner
    SPELL_KARGATH_EXECUTIONER_3 = 39290,                    // 15 min - last prisoner

    // I'm not sure if these texts are used at the execution but this is most likely they are used to
    SAY_KARGATH_EXECUTE_ALLY    = -1540049,
    SAY_KARGATH_EXECUTE_HORDE   = -1540050,

    // AT_NETHEKURSE               = 4524,                  // Area trigger used for the execution event

    NPC_FLAME_ARROW             = 17687,
};

struct SpawnLocation
{
    uint32 m_uiAllianceEntry, m_uiHordeEntry;
    float m_fX, m_fY, m_fZ, m_fO;
};

const float afExecutionerLoc[4] = {151.443f, -84.439f, 1.938f, 6.283f};

static SpawnLocation aSoldiersLocs[] =
{
    {0,                      NPC_SOLDIER_HORDE_1, 119.609f, 256.127f, -45.254f, 5.133f},
    {NPC_SOLDIER_ALLIANCE_1, 0,                   131.106f, 254.520f, -45.236f, 3.951f},
    {NPC_SOLDIER_ALLIANCE_3, NPC_SOLDIER_HORDE_3, 151.040f, -91.558f, 1.936f, 1.559f},
    {NPC_SOLDIER_ALLIANCE_2, NPC_SOLDIER_HORDE_2, 150.669f, -77.015f, 1.933f, 4.705f},
    {NPC_OFFICER_ALLIANCE,   NPC_OFFICER_HORDE,   138.241f, -84.198f, 1.907f, 0.055f}
};

class instance_shattered_halls : public ScriptedInstance
{
    public:
        instance_shattered_halls(Map* pMap);

        void Initialize() override;

        void OnPlayerEnter(Player* pPlayer) override;

        void OnObjectCreate(GameObject* pGo) override;
        void OnCreatureCreate(Creature* creature) override;
        void OnCreatureRespawn(Creature* creature) override;

        void OnCreatureDeath(Creature* creature) override;
        void OnCreatureEvade(Creature* creature) override;
        void OnCreatureEnterCombat(Creature* creature) override;

        void SetData(uint32 uiType, uint32 uiData) override;
        uint32 GetData(uint32 uiType) const override;

        const char* Save() const override { return m_strInstData.c_str(); }
        void Load(const char* chrIn) override;

        bool CheckConditionCriteriaMeet(Player const* pPlayer, uint32 uiInstanceConditionId, WorldObject const* pConditionSource, uint32 conditionSourceType) const override;

        void Update(const uint32 diff) override;

    private:
        void DoCastGroupDebuff(uint32 uiSpellId);
        void FailGauntlet(Creature* gauntlet);
        void StopGauntlet(Creature* gauntlet);
        void EndGauntlet(Creature* gauntlet);
        void SpawnHallOfFathers(uint32 uiGroup);

        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;

        ObjectGuid m_guidGauntletNPC;
        ObjectGuid m_guid3rdLegionnaireNPC;
        ObjectGuid m_guid4thLegionnaireNPC;

        uint32 m_uiExecutionTimer;
        uint32 m_uiTeam;
        uint8 m_uiExecutionStage;
        uint8 m_uiPrisonersLeft;
        uint32 m_auiSentrys;

        std::vector<ObjectGuid> m_vGauntletPermanentGuids;
        std::vector<ObjectGuid> m_vGauntletTemporaryGuids;
        std::vector<ObjectGuid> m_vGauntletBossGuids;
        std::vector<ObjectGuid> m_vHallOfFatherGuids;
        std::vector<ObjectGuid> m_vHallOfFather2ndGuids;

        std::vector<std::pair<ObjectGuid, uint32>> m_vBlazeTimers;
};

#endif
