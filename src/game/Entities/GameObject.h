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

#ifndef MANGOSSERVER_GAMEOBJECT_H
#define MANGOSSERVER_GAMEOBJECT_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Entities/Object.h"
#include "Util.h"
#include "AI/BaseAI/GameObjectAI.h"
#include "Spells/SpellAuras.h"
#include "Spells/SpellDefines.h"

// GCC have alternative #pragma pack(N) syntax and old gcc version not support pack(push,N), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif



// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

struct GameObjectLocale
{
    std::vector<std::string> Name;
    std::vector<std::string> CastBarCaption;
};

// client side GO show states
enum GOState
{
    GO_STATE_ACTIVE             = 0,                        // show in world as used and not reset (closed door open)
    GO_STATE_READY              = 1,                        // show in world as ready (closed door close)
    GO_STATE_ACTIVE_ALTERNATIVE = 2                         // show in world as used in alt way and not reset (closed door open by cannon fire)
};

#define MAX_GO_STATE              3

// from `gameobject`
struct GameObjectData
{
    uint32 id;                                              // entry in gamobject_template
    uint32 mapid;
    float posX;
    float posY;
    float posZ;
    float orientation;
    float rotation0;
    float rotation1;
    float rotation2;
    float rotation3;
    int32 spawntimesecsmin;
    int32 spawntimesecsmax;
    uint32 animprogress;
    GOState go_state;
    uint8 spawnMask;
    uint16 gameEvent;
    uint16 GuidPoolId;
    uint16 EntryPoolId;
    uint16 OriginalZoneId;

    uint32 GetRandomRespawnTime() const { return urand(uint32(spawntimesecsmin), uint32(spawntimesecsmax)); }

    // return false if it should be handled by GameEventMgr or PoolMgr
    bool IsNotPartOfPoolOrEvent() const { return (!gameEvent && !GuidPoolId && !EntryPoolId); }
};

// For containers:  [GO_NOT_READY]->GO_READY (close)->GO_ACTIVATED (open) ->GO_JUST_DEACTIVATED->GO_READY        -> ...
// For bobber:      GO_NOT_READY  ->GO_READY (close)->GO_ACTIVATED (open) ->GO_JUST_DEACTIVATED-><deleted>
// For door(closed):[GO_NOT_READY]->GO_READY (close)->GO_ACTIVATED (open) ->GO_JUST_DEACTIVATED->GO_READY(close) -> ...
// For door(open):  [GO_NOT_READY]->GO_READY (open) ->GO_ACTIVATED (close)->GO_JUST_DEACTIVATED->GO_READY(open)  -> ...
enum LootState
{
    GO_NOT_READY = 0,
    GO_READY,                                               // can be ready but despawned, and then not possible activate until spawn
    GO_ACTIVATED,
    GO_JUST_DEACTIVATED
};

enum CapturePointState
{
    CAPTURE_STATE_NEUTRAL = 0,
    CAPTURE_STATE_PROGRESS_ALLIANCE,
    CAPTURE_STATE_PROGRESS_HORDE,
    CAPTURE_STATE_CONTEST_ALLIANCE,
    CAPTURE_STATE_CONTEST_HORDE,
    CAPTURE_STATE_WIN_ALLIANCE,
    CAPTURE_STATE_WIN_HORDE
};

enum CapturePointSliderValue
{
    CAPTURE_SLIDER_ALLIANCE         = 100,                  // full alliance
    CAPTURE_SLIDER_HORDE            = 0,                    // full horde
    CAPTURE_SLIDER_MIDDLE           = 50                    // middle
};

enum GameobjectExtraFlags
{
    GAMEOBJECT_EXTRA_FLAG_CUSTOM_ANIM_ON_USE = 0x00000001,    // GO that plays custom animation on usage
    GAMEOBJECT_EXTRA_FLAG_ACTIVE             = 0x00001000,    // Always active
};

class Unit;
class GameObjectModel;
struct GameObjectDisplayInfoEntry;
struct TransportAnimation;
class Item;

struct QuaternionData
{
    float x, y, z, w;

    QuaternionData() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) { }
    QuaternionData(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) { }

    bool isUnit() const;
    void toEulerAnglesZYX(float& Z, float& Y, float& X) const;
    static QuaternionData fromEulerAnglesZYX(float Z, float Y, float X);
};

// 5 sec for bobber catch
#define FISHING_BOBBER_READY_TIME 5

#define GO_ANIMPROGRESS_DEFAULT 100                         // in 3.x 0xFF

class GameObject : public WorldObject
{
    public:
        explicit GameObject();
        ~GameObject();

        static GameObject* CreateGameObject(uint32 entry);

        void AddToWorld() override;
        void RemoveFromWorld() override;

        virtual bool Create(uint32 guidlow, uint32 name_id, Map* map, float x, float y, float z, float ang,
                    float rotation0 = 0.0f, float rotation1 = 0.0f, float rotation2 = 0.0f, float rotation3 = 0.0f, uint32 animprogress = GO_ANIMPROGRESS_DEFAULT, GOState go_state = GO_STATE_READY);
        void Update(const uint32 diff) override;
        GameObjectInfo const* GetGOInfo() const;

        bool IsTransport() const;
        bool IsMoTransport() const;

        bool HasStaticDBSpawnData() const;                  // listed in `gameobject` table and have fixed in DB guid

        void UpdateRotationFields(float rotation2 = 0.0f, float rotation3 = 0.0f);
        QuaternionData GetWorldRotation() const; // compatibility with wotlk
        QuaternionData const GetLocalRotation() const;

        // overwrite WorldObject function for proper name localization
        const char* GetNameForLocaleIdx(int32 loc_idx) const override;

        void SaveToDB() const;
        void SaveToDB(uint32 mapid, uint8 spawnMask) const;
        bool LoadFromDB(uint32 dbGuid, Map* map, uint32 newGuid);
        void DeleteFromDB() const;

        ObjectGuid const& GetOwnerGuid() const override { return GetGuidValue(OBJECT_FIELD_CREATED_BY); }
        void SetOwnerGuid(ObjectGuid guid) override;

        Unit* GetOwner() const;

        void SetSpellId(uint32 id)
        {
            m_spawnedByDefault = false;                     // all summoned object is despawned after delay
            m_spellId = id;
        }
        uint32 GetSpellId() const { return m_spellId;}

        time_t GetRespawnTime() const { return m_respawnTime; }
        time_t GetRespawnTimeEx() const
        {
            time_t now = time(nullptr);
            if (m_respawnTime > now)
                return m_respawnTime;
            return now;
        }

        void SetRespawnTime(time_t respawn)
        {
            m_respawnTime = respawn > 0 ? time(nullptr) + respawn : 0;
            m_respawnDelay = respawn > 0 ? uint32(respawn) : 0;
        }
        void Respawn();
        bool IsSpawned() const
        {
            return m_respawnDelay == 0 ||
                   (m_respawnTime > 0 && !m_spawnedByDefault) ||
                   (m_respawnTime == 0 && m_spawnedByDefault);
        }
        bool IsSpawnedByDefault() const { return m_spawnedByDefault; }
        uint32 GetRespawnDelay() const { return m_respawnDelay; }
        void SetRespawnDelay(uint32 delay, bool once = false) { m_respawnDelay = delay; m_respawnOverriden = true; m_respawnOverrideOnce = once; }
        void SetForcedDespawn() { m_forcedDespawn = true; };
        void Refresh();
        void Delete();

        // Functions spawn/remove gameobject with DB guid in all loaded map copies (if point grid loaded in map)
        static void AddToRemoveListInMaps(uint32 db_guid, GameObjectData const* data);
        static void SpawnInMaps(uint32 db_guid, GameObjectData const* data);

        GameobjectTypes GetGoType() const { return GameobjectTypes(GetUInt32Value(GAMEOBJECT_TYPE_ID)); }
        void SetGoType(GameobjectTypes type) { SetUInt32Value(GAMEOBJECT_TYPE_ID, type); }
        GOState GetGoState() const { return GOState(GetUInt32Value(GAMEOBJECT_STATE)); }
        void SetGoState(GOState state);
        uint32 GetGoArtKit() const { return GetUInt32Value(GAMEOBJECT_ARTKIT); }
        void SetGoArtKit(uint32 artkit) { SetUInt32Value(GAMEOBJECT_ARTKIT, artkit); }
        uint32 GetGoAnimProgress() const { return GetUInt32Value(GAMEOBJECT_ANIMPROGRESS); }
        void SetGoAnimProgress(uint32 animprogress) { SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, animprogress); }
        uint32 GetDisplayId() const { return GetUInt32Value(GAMEOBJECT_DISPLAYID); }
        void SetDisplayId(uint32 modelId);
        uint32 GetLevel() const { return GetUInt32Value(GAMEOBJECT_LEVEL); }

        void Use(Unit* user, SpellEntry const* spellInfo = nullptr);

        LootState GetLootState() const { return m_lootState; }
        void SetLootState(LootState state);

        void AddToSkillupList(Player* player);
        bool IsInSkillupList(Player* player) const;
        void ClearSkillupList() { m_SkillupSet.clear(); }
        void ClearAllUsesData()
        {
            ClearSkillupList();
            m_useTimes = 0;
            m_firstUser.Clear();
            m_UniqueUsers.clear();
        }

        void SetActionTarget(ObjectGuid guid) { m_actionTarget = guid; };
        void AddUniqueUse(Player* player);
        void AddUse() { ++m_useTimes; }
        bool IsInUse() const { return m_isInUse; }
        void SetInUse(bool use);

        uint32 GetUseCount() const { return m_useTimes; }
        uint32 GetUniqueUseCount() const { return m_UniqueUsers.size(); }

        void SaveRespawnTime() override;

        // Loot System
        ObjectGuid GetLootRecipientGuid() const { return m_lootRecipientGuid; }
        uint32 GetLootGroupRecipientId() const { return m_lootGroupRecipientId; }
        Player* GetLootRecipient() const;                   // use group cases as prefered
        Group* GetGroupLootRecipient() const;
        bool HasLootRecipient() const { return m_lootGroupRecipientId || !m_lootRecipientGuid.IsEmpty(); }
        bool IsGroupLootRecipient() const { return m_lootGroupRecipientId != 0; }

        void SetLootRecipient(Unit* pUnit);
        Player* GetOriginalLootRecipient() const;           // ignore group changes/etc, not for looting

        bool HasQuest(uint32 quest_id) const override;
        bool HasInvolvedQuest(uint32 quest_id) const override;
        bool ActivateToQuest(Player* pTarget) const;
        void UseDoorOrButton(uint32 time_to_restore = 0, bool alternative = false);
        // 0 = use `gameobject`.`spawntimesecs`
        void ResetDoorOrButton();

        ReputationRank GetReactionTo(Unit const* unit) const override;

        bool IsEnemy(Unit const* unit) const override;
        bool IsFriend(Unit const* unit) const override;

        bool CanAttackSpell(Unit const* target, SpellEntry const* spellInfo = nullptr, bool isAOE = false) const override;
        bool CanAssistSpell(Unit const* target, SpellEntry const* spellInfo = nullptr) const override;

        GameObject* SummonLinkedTrapIfAny() const;
        void TriggerLinkedGameObject(Unit* target) const;
        GameObject* GetLinkedTrap();
        void SetLinkedTrap(GameObject* linkedTrap) { m_linkedTrap = linkedTrap->GetObjectGuid(); }

        bool isVisibleForInState(Player const* u, WorldObject const* viewPoint, bool inVisibleList) const override;

        bool IsCollisionEnabled() const;                    // Check if a go should collide. Like if a door is closed

        GameObject* LookupFishingHoleAround(float range) const;

        void SetCapturePointSlider(float value, bool isLocked);
        float GetCapturePointSliderValue() const { return m_captureSlider; }

        float GetInteractionDistance() const;
        float GetCollisionHeight() const override { return 1.f; } // to get away with ground collision

        GridReference<GameObject>& GetGridRef() { return m_gridRef; }

        uint32 GetScriptId() const;
        void AIM_Initialize();
        void OnEventHappened(uint16 eventId, bool activate, bool resume) override { return AI()->OnEventHappened(eventId, activate, resume); }
        GameObjectAI* AI() const { return m_AI.get(); }

        GameObjectModel* m_model;
        void AddModelToMap();
        void RemoveModelFromMap();
        void UpdateModelPosition();

        bool _IsWithinDist(WorldObject const* obj, float dist2compare, bool is3D) const override;

        bool IsAtInteractDistance(Position const& pos, float radius, bool is3D = true) const;
        bool IsAtInteractDistance(Player const* player, uint32 maxRange = 0) const;

        SpellEntry const* GetSpellForLock(Player const* player) const;

        float GetStationaryX() const { if (GetGOInfo()->type != GAMEOBJECT_TYPE_MO_TRANSPORT) return m_stationaryPosition.GetPositionX(); return 0.f; }
        float GetStationaryY() const { if (GetGOInfo()->type != GAMEOBJECT_TYPE_MO_TRANSPORT) return m_stationaryPosition.GetPositionY(); return 0.f; }
        float GetStationaryZ() const { if (GetGOInfo()->type != GAMEOBJECT_TYPE_MO_TRANSPORT) return m_stationaryPosition.GetPositionZ(); return 0.f; }
        float GetStationaryO() const { if (GetGOInfo()->type != GAMEOBJECT_TYPE_MO_TRANSPORT) return m_stationaryPosition.GetPositionO(); return GetOrientation(); }

        SpellCastResult CastSpell(Unit* temporaryCaster, Unit* Victim, uint32 spellId, uint32 triggeredFlags, Item* castItem = nullptr, Aura* triggeredByAura = nullptr, ObjectGuid originalCaster = ObjectGuid(), SpellEntry const* triggeredBy = nullptr);

        SpellCastResult CastSpell(Unit* temporaryCaster, Unit* Victim, uint32 spellId, TriggerCastFlags triggeredFlags, Item* castItem = nullptr, Aura* triggeredByAura = nullptr, ObjectGuid originalCaster = ObjectGuid(), SpellEntry const* triggeredBy = nullptr)
        {
            return CastSpell(temporaryCaster, Victim, spellId, uint32(triggeredFlags), castItem, triggeredByAura, originalCaster, triggeredBy);
        }

        SpellCastResult CastSpell(Unit* temporaryCaster, Unit* Victim, SpellEntry const* spellInfo, uint32 triggeredFlags, Item* castItem = nullptr, Aura* triggeredByAura = nullptr, ObjectGuid originalCaster = ObjectGuid(), SpellEntry const* triggeredBy = nullptr);

    protected:
        uint32      m_spellId;
        time_t      m_respawnTime;                          // (secs) time of next respawn (or despawn if GO have owner()),
        uint32      m_respawnDelay;                         // (secs) if 0 then current GO state no dependent from timer
        bool        m_respawnOverriden;
        bool        m_respawnOverrideOnce;
        bool        m_forcedDespawn;
        LootState   m_lootState;
        bool        m_spawnedByDefault;
        time_t      m_cooldownTime;                         // used as internal reaction delay time store (not state change reaction).
        // For traps/goober this: spell casting cooldown, for doors/buttons: reset time.

        uint32      m_captureTimer;                         // (msecs) timer used for capture points
        float       m_captureSlider;                        // capture point slider value in range of [0..100]
        CapturePointState m_captureState;

        GuidSet m_SkillupSet;                               // players that already have skill-up at GO use

        uint32 m_useTimes;                                  // amount uses/charges triggered

        // collected only for GAMEOBJECT_TYPE_SUMMONING_RITUAL
        ObjectGuid m_firstUser;                             // first GO user, in most used cases owner, but in some cases no, for example non-summoned multi-use GAMEOBJECT_TYPE_SUMMONING_RITUAL
        GuidSet m_UniqueUsers;                              // all players who use item, some items activated after specific amount unique uses

        GameObjectInfo const* m_goInfo;
        GameObjectDisplayInfoEntry const* m_displayInfo;

        Position m_stationaryPosition;

        // Loot System
        ObjectGuid m_lootRecipientGuid;                     // player who will have rights for looting if m_lootGroupRecipient==0 or group disbanded
        uint32 m_lootGroupRecipientId;                      // group who will have rights for looting if set and exist

        // Used for trap type
        time_t m_rearmTimer;                                // timer to rearm the trap once disarmed

        // Used for chest type
        bool m_isInUse;                                     // only one player at time are allowed to open chest
        time_t m_reStockTimer;                              // timer to refill the chest
        time_t m_despawnTimer;                              // timer to despawn the chest if something changed in it

        void TriggerSummoningRitual();
        void TriggerDelayedAction();

        uint32 m_delayedActionTimer;                        // used for delayed GO actions

        ObjectGuid m_actionTarget;                          // used for setting target of Summoning rituals

        ObjectGuid m_linkedTrap;

        std::unique_ptr<GameObjectAI> m_AI;

        uint32 m_dbGuid;

    private:
        void SwitchDoorOrButton(bool activate, bool alternative = false);
        void TickCapturePoint();
        void UpdateModel();                                 // updates model in case displayId were changed
        void UpdateCollisionState() const;                  // updates state in Map's dynamic collision tree

        GridReference<GameObject> m_gridRef;
};

#endif
