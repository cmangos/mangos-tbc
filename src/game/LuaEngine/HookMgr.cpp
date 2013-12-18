/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 * Copyright (C) 2010 - 2013 Eluna Lua Engine <http://emudevs.com/>
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

#include "HookMgr.h"
#include "Includes.h"

// misc
void HookMgr::OnWorldUpdate(uint32 diff)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnWorldUpdate(diff);
}

void HookMgr::OnLootItem(Player* pPlayer, Item* pItem, uint32 count, uint64 guid)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnLootItem(pPlayer, pItem, count, guid);
}

void HookMgr::OnFirstLogin(Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnFirstLogin(pPlayer);
}

void HookMgr::OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnEquip(pPlayer, pItem, bag, slot);
}

void HookMgr::OnRepop(Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnRepop(pPlayer);
}

void HookMgr::OnResurrect(Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnResurrect(pPlayer);
}

InventoryResult HookMgr::OnCanUseItem(const Player* pPlayer, uint32 itemEntry)
{
    Player* player2 = const_cast<Player*>(pPlayer);
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
    {
        InventoryResult value = (*it)->OnCanUseItem(player2, itemEntry);
        if (value != EQUIP_ERR_OK)
            return value;
    }
    return EQUIP_ERR_OK;
}

void HookMgr::HandleGossipSelectOption(Player* pPlayer, ObjectGuid guid, uint32 sender, uint32 action, std::string code, uint32 menuId)
{
    if (!pPlayer->isAlive() || pPlayer->GetCharmerGuid())
        return;

    if (pPlayer->hasUnitState(UNIT_STAT_DIED))
        pPlayer->RemoveAurasDueToSpell(SPELL_AURA_FEIGN_DEATH);
    pPlayer->PlayerTalkClass->ClearMenus();

    if (guid.IsItem())
    {
        Item* item = pPlayer->GetItemByGuid(guid);
        if (!item)
            return;
        for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
            (*it)->HandleGossipSelectOption(pPlayer, item, sender, action, code);
    }
    else if (guid.IsPlayer())
    {
        if (pPlayer->GetGUIDLow() != guid || pPlayer->PlayerTalkClass->GetGossipMenu().GetMenuId() != menuId)
            return;
        for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
            (*it)->HandleGossipSelectOption(pPlayer, sender, action, code, menuId);
    }
}

void HookMgr::OnEngineRestart()
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnEngineRestart();
}
// item
bool HookMgr::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Item* pTarget)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnDummyEffect(pCaster, spellId, effIndex, pTarget))
            result = true;
    return result;
}

bool HookMgr::OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnQuestAccept(pPlayer, pItem, pQuest))
            result = true;
    return result;
}

bool HookMgr::OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnUse(pPlayer, pItem, targets))
            result = true;
    return result;
}

bool HookMgr::OnExpire(Player* pPlayer, ItemPrototype const* pProto)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnExpire(pPlayer, pProto))
            result = true;
    return result;
}

// creature
bool HookMgr::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Creature* pTarget)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnDummyEffect(pCaster, spellId, effIndex, pTarget))
            result = true;
    return result;
}

bool HookMgr::OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnGossipHello(pPlayer, pCreature))
            result = true;
    return result;
}

bool HookMgr::OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnGossipSelect(pPlayer, pCreature, sender, action))
            result = true;
    return result;
}

bool HookMgr::OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnGossipSelectCode(pPlayer, pCreature, sender, action, code))
            result = true;
    return result;
}

bool HookMgr::OnQuestAccept(Player* player, Creature* creature, Quest const* pQuest)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnQuestAccept(player, creature, pQuest))
            result = true;
    return result;
}

bool HookMgr::OnQuestSelect(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnQuestSelect(pPlayer, pCreature, pQuest))
            result = true;
    return result;
}

bool HookMgr::OnQuestComplete(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnQuestComplete(pPlayer, pCreature, pQuest))
            result = true;
    return result;
}

bool HookMgr::OnQuestReward(Player* player, Creature* pCreature, Quest const* pQuest)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnQuestReward(player, pCreature, pQuest))
            result = true;
    return result;
}

uint32 HookMgr::GetDialogStatus(Player* pPlayer, Creature* pCreature)
{
    uint32 result = 0;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        result = (*it)->GetDialogStatus(pPlayer, pCreature);
    return result;
}
// gameobject
bool HookMgr::OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, GameObject* pTarget)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnDummyEffect(pCaster, spellId, effIndex, pTarget))
            result = true;
    return result;
}

bool HookMgr::OnGossipHello(Player* pPlayer, GameObject* pGameObject)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnGossipHello(pPlayer, pGameObject))
            result = true;
    return result;
}

bool HookMgr::OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnGossipSelect(pPlayer, pGameObject, sender, action))
            result = true;
    return result;
}

bool HookMgr::OnGossipSelectCode(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, const char* code)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnGossipSelectCode(pPlayer, pGameObject, sender, action, code))
            result = true;
    return result;
}

bool HookMgr::OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnQuestAccept(pPlayer, pGameObject, pQuest))
            result = true;
    return result;
}

bool HookMgr::OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnQuestReward(pPlayer, pGameObject, pQuest))
            result = true;
    return result;
}

bool HookMgr::OnGameObjectUse(Player* pPlayer, GameObject* pGameObject)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnGameObjectUse(pPlayer, pGameObject))
            result = true;
    return result;
}

uint32 HookMgr::GetDialogStatus(Player* pPlayer, GameObject* pGameObject)
{
    bool result = 0;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        result = (*it)->GetDialogStatus(pPlayer, pGameObject);
    return result;
}

void HookMgr::OnDestroyed(GameObject* pGameObject, Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnDestroyed(pGameObject, pPlayer);
}

void HookMgr::OnDamaged(GameObject* pGameObject, Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnDamaged(pGameObject, pPlayer);
}

void HookMgr::OnLootStateChanged(GameObject* pGameObject, uint32 state, Unit* pUnit)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnLootStateChanged(pGameObject, state, pUnit);
}

void HookMgr::OnGameObjectStateChanged(GameObject* pGameObject, uint32 state)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnGameObjectStateChanged(pGameObject, state);
}
// Player
void HookMgr::OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnPlayerEnterCombat(pPlayer, pEnemy);
}

void HookMgr::OnPlayerLeaveCombat(Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnPlayerLeaveCombat(pPlayer);
}

void HookMgr::OnPVPKill(Player* pKiller, Player* pKilled)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnPVPKill(pKiller, pKilled);
}

void HookMgr::OnCreatureKill(Player* pKiller, Creature* pKilled)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnCreatureKill(pKiller, pKilled);
}

void HookMgr::OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnPlayerKilledByCreature(pKiller, pKilled);
}

void HookMgr::OnLevelChanged(Player* pPlayer, uint8 oldLevel)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnLevelChanged(pPlayer, oldLevel);
}

void HookMgr::OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnFreeTalentPointsChanged(pPlayer, newPoints);
}

void HookMgr::OnTalentsReset(Player* pPlayer, bool noCost)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnTalentsReset(pPlayer, noCost);
}

void HookMgr::OnMoneyChanged(Player* pPlayer, int32& amount)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnMoneyChanged(pPlayer, amount);
}

void HookMgr::OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnGiveXP(pPlayer, amount, pVictim);
}

void HookMgr::OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnReputationChange(pPlayer, factionID, standing, incremental);
}

void HookMgr::OnDuelRequest(Player* pTarget, Player* pChallenger)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnDuelRequest(pTarget, pChallenger);
}

void HookMgr::OnDuelStart(Player* pStarter, Player* pChallenger)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnDuelStart(pStarter, pChallenger);
}

void HookMgr::OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnDuelEnd(pWinner, pLoser, type);
}

void HookMgr::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnChat(pPlayer, type, lang, msg, pReceiver);
}

bool HookMgr::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg)
{
    bool result = true;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if (!(*it)->OnChat(pPlayer, type, lang, msg))
            result = false;
    return result;
}

bool HookMgr::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup)
{
    bool result = true;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if (!(*it)->OnChat(pPlayer, type, lang, msg, pGroup))
            result = false;
    return result;
}

bool HookMgr::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild)
{
    bool result = true;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if (!(*it)->OnChat(pPlayer, type, lang, msg, pGuild))
            result = false;
    return result;
}

bool HookMgr::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel)
{
    bool result = true;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if (!(*it)->OnChat(pPlayer, type, lang, msg, pChannel))
            result = false;
    return result;
}

void HookMgr::OnEmote(Player* pPlayer, uint32 emote)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnEmote(pPlayer, emote);
}

void HookMgr::OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, uint64 guid)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnTextEmote(pPlayer, textEmote, emoteNum, guid);
}

void HookMgr::OnSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnSpellCast(pPlayer, pSpell, skipCheck);
}

void HookMgr::OnLogin(Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnLogin(pPlayer);
}

void HookMgr::OnLogout(Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnLogout(pPlayer);
}

void HookMgr::OnCreate(Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnCreate(pPlayer);
}

void HookMgr::OnDelete(uint32 lowGuid)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnDelete(lowGuid);
}

void HookMgr::OnSave(Player* pPlayer)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnSave(pPlayer);
}

void HookMgr::OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnBindToInstance(pPlayer, difficulty, mapid, permanent);
}

void HookMgr::OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnUpdateZone(pPlayer, newZone, newArea);
}

void HookMgr::OnMapChanged(Player* pPlayer) // Not Implemented
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnMapChanged(pPlayer);
}
// areatrigger
bool HookMgr::OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger)
{
    bool result = false;
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        if ((*it)->OnAreaTrigger(pPlayer, pTrigger))
            result = true;
    return result;
}
// weather
/*void HookMgr::OnChange(Weather* weather, WeatherState state, float grade)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnChange(weather, state, grade);
}
// transport
void HookMgr::OnAddPassenger(Transport* transport, Player* player)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnAddPassenger(transport, player);
}
void HookMgr::OnAddCreaturePassenger(Transport* transport, Creature* creature)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnAddCreaturePassenger(transport, creature);
}
void HookMgr::OnRemovePassenger(Transport* transport, Player* player)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnRemovePassenger(transport, player);
}
void HookMgr::OnRelocate(Transport* transport, uint32 waypointId, uint32 mapId, float x, float y, float z)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnRelocate(transport, waypointId, mapId, x, y, z);
}*/
// Guild
void HookMgr::OnAddMember(Guild* guild, Player* player, uint32 plRank)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnAddMember(guild, player, plRank);
}

void HookMgr::OnRemoveMember(Guild* guild, Player* player, bool isDisbanding/*, bool isKicked*/) // isKicked not a part of Mangos, implement?
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnRemoveMember(guild, player, isDisbanding/*, isKicked*/);
}

void HookMgr::OnMOTDChanged(Guild* guild, const std::string& newMotd)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnMOTDChanged(guild, newMotd);
}

void HookMgr::OnInfoChanged(Guild* guild, const std::string& newInfo)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnInfoChanged(guild, newInfo);
}

void HookMgr::OnCreate(Guild* guild, Player* leader, const std::string& name)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnCreate(guild, leader, name);
}

void HookMgr::OnDisband(Guild* guild)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnDisband(guild);
}

void HookMgr::OnMemberWitdrawMoney(Guild* guild, Player* player, uint32 &amount/*, bool isRepair*/) // isRepair not a part of Mangos, implement?
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnMemberWitdrawMoney(guild, player, amount/*, isRepair*/);
}

void HookMgr::OnMemberDepositMoney(Guild* guild, Player* player, uint32 &amount)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnMemberDepositMoney(guild, player, amount);
}

void HookMgr::OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId,
            bool isDestBank, uint8 destContainer, uint8 destSlotId)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnItemMove(guild, player, pItem, isSrcBank, srcContainer, srcSlotId,
            isDestBank, destContainer, destSlotId);
}

void HookMgr::OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnEvent(guild, eventType, playerGuid1, playerGuid2, newRank);
}

void HookMgr::OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnBankEvent(guild, eventType, tabId, playerGuid, itemOrMoney, itemStackCount, destTabId);
}
// Group
void HookMgr::OnAddMember(Group* group, uint64 guid)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnAddMember(group, guid);
}

void HookMgr::OnInviteMember(Group* group, uint64 guid)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnInviteMember(group, guid);
}

void HookMgr::OnRemoveMember(Group* group, uint64 guid, uint8 method/*, uint64 kicker, const char* reason*/) // Kicker and Reason not a part of Mangos, implement?
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnRemoveMember(group, guid, method/*, kicker, reason*/);
}

void HookMgr::OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnChangeLeader(group, newLeaderGuid, oldLeaderGuid);
}

void HookMgr::OnDisband(Group* group)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnDisband(group);
}

void HookMgr::OnCreate(Group* group, uint64 leaderGuid, GroupType groupType)
{
    for (HookPointerSet::const_iterator it = hookPointers.begin(); it != hookPointers.end(); ++it)
        (*it)->OnCreate(group, leaderGuid, groupType);
}