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

#ifndef UNITMETHODS_H
#define UNITMETHODS_H

#define TO_PLAYER() Player* player; if (!unit || !unit->IsInWorld() || !(player = unit->ToPlayer())) { return 0; } else (void)0;
#define TO_CREATURE() Creature* creature; if (!unit || !unit->IsInWorld() || !(creature = unit->ToCreature())) { return 0; } else (void)0;

#define TO_PLAYER_BOOL() Player* player; if (!unit || !unit->IsInWorld() || !(player = unit->ToPlayer())) { sEluna.Push(L, false); return 1; } else (void)0;
#define TO_CREATURE_BOOL() Creature* creature; if (!unit || !unit->IsInWorld() || !(creature = unit->ToCreature())) { sEluna.Push(L, false); return 1; } else (void)0;

namespace LuaUnit
{
    int Attack(lua_State* L, Unit* unit)
    {
        Unit* who = sEluna.CHECK_UNIT(L, 1);
        bool meleeAttack = luaL_optbool(L, 2, false);

        if (!who)
            sEluna.Push(L, false);
        else
            sEluna.Push(L, unit->Attack(who, meleeAttack));
        return 1;
    }

    int ClearThreatList(lua_State* L, Unit* unit)
    {
        unit->getThreatManager().clearReferences();
        return 0;
    }

    int SetOwnerGUID(lua_State* L, Unit* unit)
    {
        ObjectGuid guid = unit->GetObjectGuid();

        unit->SetOwnerGuid(guid);
        return 0;
    }

    int GetOwner(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetOwner());
        return 1;
    }

    int GetOwnerGUID(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetOwnerGuid());
        return 1;
    }

    int GetMap(lua_State* L, Unit* unit)
    {
        Map* map = unit->GetMap();
        sEluna.Push(L, map);
        return 1;
    }

    int GetRelativePoint(lua_State* L, Unit* unit)
    {
        float dist = luaL_checknumber(L, 1);
        float rad = luaL_checknumber(L, 2);

        float o = MapManager::NormalizeOrientation(unit->GetOrientation() + rad);
        sEluna.Push(L, unit->GetPositionX() + (dist * cosf(o)));
        sEluna.Push(L, unit->GetPositionY() + (dist * sinf(o)));
        sEluna.Push(L, o);
        return 3;
    }

    int Mount(lua_State* L, Unit* unit)
    {
        uint32 displayId = luaL_checkunsigned(L, 1);

        unit->Mount(displayId);
        return 0;
    }

    int Dismount(lua_State* L, Unit* unit)
    {
        if (unit->IsMounted())
        {
            unit->Unmount();
            unit->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
        }

        return 0;
    }

    int IsMounted(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->IsMounted());
        return 1;
    }

    int IsWithinLoS(lua_State* L, Unit* unit)
    {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = luaL_checknumber(L, 3);

        sEluna.Push(L, unit->IsWithinLOS(x, y, z));
        return 1;
    }

    int IsWithinDistInMap(lua_State* L, Unit* unit)
    {
        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 1);
        if (!obj)
            return 0;
        float radius = luaL_checknumber(L, 2);

        sEluna.Push(L, unit->IsWithinDistInMap(obj, radius));
        return 1;
    }

    int IsInAccessiblePlaceFor(lua_State* L, Unit* unit)
    {
        Creature* creature = sEluna.CHECK_CREATURE(L, 1);
        if (!creature)
            return 0;

        sEluna.Push(L, unit->isInAccessablePlaceFor(creature));
        return 1;
    }

    int IsDamageEnoughForLootingAndReward(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        // sEluna.Push(L, creature->IsDamageEnoughForLootingAndReward());
        return 1;
    }

    int IsReputationGainDisabled(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->IsReputationGainDisabled());
        return 1;
    }

    int SetDisableReputationGain(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        bool disable = luaL_optbool(L, 1, true);

        creature->SetDisableReputationGain(disable);
        return 0;
    }

    int SelectVictim(lua_State* L, Unit* unit)
    {
        TO_CREATURE();
        // sEluna.Push(L, creature->SelectVictim());
        return 1;
    }

    int GetCurrentWaypointId(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        // sEluna.Push(L, creature->GetCurrentWaypointID());
        return 1;
    }

    int GetWaypointPath(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        // sEluna.Push(L, creature->GetWaypointPath());
        return 1;
    }

    int GetTransportHomePosition(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        /*float x,y,z,o;
        creature->GetTransportHomePosition(x,y,z,o);

        sEluna.Push(L, x);
        sEluna.Push(L, y);
        sEluna.Push(L, z);
        sEluna.Push(L, o);*/
        return 4;
    }

    int IsRegeneratingHealth(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->IsRegeneratingHealth());
        return 1;
    }

    int HasInvolvedQuest(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        uint32 quest_id = luaL_checkunsigned(L, 1);

        sEluna.Push(L, creature->HasInvolvedQuest(quest_id));
        return 1;
    }

    int SetInCombatWithZone(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        creature->SetInCombatWithZone();
        return 0;
    }

    int SetRespawnRadius(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        float dist = luaL_checknumber(L, 1);

        creature->SetRespawnRadius(dist);
        return 0;
    }

    int GetRespawnRadius(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetRespawnRadius());
        return 1;
    }

    int Respawn(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        creature->Respawn();
        return 0;
    }

    int SetRespawnDelay(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        uint32 delay = luaL_checkunsigned(L, 1);

        creature->SetRespawnDelay(delay);
        return 0;
    }

    int GetRespawnDelay(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetRespawnDelay());
        return 1;
    }

    int DespawnOrUnsummon(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        uint32 msTimeToDespawn = luaL_optunsigned(L, 1, 0);

        creature->ForcedDespawn(msTimeToDespawn);
        return 0;
    }

    int RemoveCorpse(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        creature->RemoveCorpse();
        return 0;
    }

    int SetDefaultMovementType(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        int32 type = luaL_checkinteger(L, 1);

        creature->SetDefaultMovementType((MovementGeneratorType)type);
        return 0;
    }

    int GetDefaultMovementType(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetDefaultMovementType());
        return 1;
    }

    int IsTargetAcceptable(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        Unit* target = sEluna.CHECK_UNIT(L, 1);

        if (!target)
            sEluna.Push(L, false);
        else
            sEluna.Push(L, creature->isTargetableForAttack(target));
        return 1;
    }

    int CanAssistTo(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        Unit* u = sEluna.CHECK_UNIT(L, 1);
        Unit* enemy = sEluna.CHECK_UNIT(L, 2);
        bool checkfaction = luaL_optbool(L, 3, true);

        if (!u)
            sEluna.Push(L, false);
        if (!enemy)
            sEluna.Push(L, false);
        else
            sEluna.Push(L, creature->CanAssistTo(u, enemy, checkfaction));
        return 1;
    }

    int HasSearchedAssistance(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->HasSearchedAssistance());
        return 1;
    }

    int SetNoSearchAssistance(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        bool val = luaL_optbool(L, 1, true);

        creature->SetNoSearchAssistance(val);
        return 0;
    }

    int SetNoCallAssistance(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        bool val = luaL_optbool(L, 1, true);

        creature->SetNoCallAssistance(val);
        return 0;
    }

    int CallAssistance(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        creature->CallAssistance();
        return 0;
    }

    int CallForHelp(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        float radius = luaL_checknumber(L, 1);

        creature->CallForHelp(radius);
        return 0;
    }

    int FleeToGetAssistance(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        creature->DoFleeToGetAssistance();
        return 0;
    }

    int GetAggroRange(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        Unit* target = sEluna.CHECK_UNIT(L, 1);

        if (!target)
            return 0;
        sEluna.Push(L, creature->GetAttackDistance(target));
        return 1;
    }

    int GetAttackDistance(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        Unit* target = sEluna.CHECK_UNIT(L, 1);

        if (!target)
            return 0;

        sEluna.Push(L, creature->GetAttackDistance(target));
        return 1;
    }

    int CanStartAttack(lua_State* L, Unit* unit) // TODO: Implement core side
    {
        TO_CREATURE_BOOL();

        Unit* target = sEluna.CHECK_UNIT(L, 1);
        bool force = luaL_optbool(L, 2, true);

        if (!target)
            return 0;

        // sEluna.Push(L, creature->CanStartAttack(target, force));
        return 1;
    }

    int ResetLootMode(lua_State* L, Unit* unit) // TODO: Implement LootMode features
    {
        TO_CREATURE();

        // creature->ResetLootMode();
        return 0;
    }

    int RemoveLootMode(lua_State* L, Unit* unit) // TODO: Implement LootMode features
    {
        TO_CREATURE();

        uint16 lootMode = luaL_checkunsigned(L, 1);

        // creature->RemoveLootMode(lootMode);
        return 0;
    }

    int AddLootMode(lua_State* L, Unit* unit) // TODO: Implement LootMode features
    {
        TO_CREATURE();

        uint16 lootMode = luaL_checkunsigned(L, 1);

        // creature->AddLootMode(lootMode);
        return 0;
    }

    int SetLootMode(lua_State* L, Unit* unit) // TODO: Implement LootMode features
    {
        TO_CREATURE();

        uint16 lootMode = luaL_checkunsigned(L, 1);

        // creature->SetLootMode(lootMode);
        return 0;
    }

    int HasLootMode(lua_State* L, Unit* unit) // TODO: Implement LootMode features
    {
        TO_CREATURE_BOOL();

        uint16 lootMode = luaL_checkunsigned(L, 1);

        // sEluna.Push(L, creature->HasLootMode(lootMode));
        return 1;
    }

    int GetLootMode(lua_State* L, Unit* unit) // TODO: Implement LootMode features
    {
        TO_CREATURE();

        // sEluna.Push(L, creature->GetLootMode());
        return 1;
    }

    int IsTappedBy(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        Player* player = sEluna.CHECK_PLAYER(L, 1);

        if (!player)
            sEluna.Push(L, creature->isTappedBy(player));
        else
            sEluna.Push(L, false);
        return 1;
    }

    int HasLootRecipient(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->HasLootRecipient());
        return 1;
    }

    int GetLootRecipientGroup(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetGroupLootRecipient());
        return 1;
    }

    int GetLootRecipient(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetLootRecipient());
        return 1;
    }

    int SetDeathState(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        int32 state = luaL_checkinteger(L, 1);

        creature->SetDeathState((DeathState)state);
        return 0;
    }

    int SetReactState(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        int32 state = luaL_checkinteger(L, 1);

        creature->GetCharmInfo()->SetReactState((ReactStates)state);
        return 0;
    }

    int GetReactState(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetCharmInfo()->GetReactState());
        return 1;
    }

    int HasReactState(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        int32 state = luaL_checkinteger(L, 1);

        sEluna.Push(L, creature->GetCharmInfo()->HasReactState((ReactStates)state));
        return 1;
    }

    int CanFly(lua_State* L, Unit* unit)
    {
        if (Player* player = unit->ToPlayer())
            sEluna.Push(L, player->CanFly());
        else if (Creature* creature = unit->ToCreature())
            sEluna.Push(L, creature->CanFly());
        return 1;
    }

    int CanSwim(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->CanSwim());
        return 1;
    }

    int CanWalk(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->CanWalk());
        return 1;
    }

    int SetDisableGravity(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        bool disable = luaL_optbool(L, 1, true);
        bool packetOnly = luaL_optbool(L, 2, false);

        // sEluna.Push(L, creature->SetDisableGravity(disable, packetOnly));
        return 1;
    }

    int SetHover(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        bool enable = luaL_optbool(L, 1, true);

        // sEluna.Push(L, creature->SetHover(enable));
        return 1;
    }

    int IsInEvadeMode(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->IsInEvadeMode());
        return 1;
    }

    int IsElite(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->IsElite());
        return 1;
    }

    int IsGuard(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->IsGuard());
        return 1;
    }

    int IsTrigger(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        // sEluna.Push(L, creature->isTrigger());
        return 1;
    }

    int IsCivilian(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->IsCivilian());
        return 1;
    }

    int IsRacialLeader(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->IsRacialLeader());
        return 1;
    }

    int HasCategoryCooldown(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        uint32 spell = luaL_checkunsigned(L, 1);

        sEluna.Push(L, creature->HasCategoryCooldown(spell));
        return 1;
    }

    int GetScriptName(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetScriptName());
        return 1;
    }

    int GetAIName(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetAIName());
        return 1;
    }

    int GetScriptId(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetScriptId());
        return 1;
    }

    int GetCreatureSpellCooldownDelay(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        uint32 spell = luaL_checkunsigned(L, 1);

        sEluna.Push(L, creature->GetCreatureSpellCooldownDelay(spell));
        return 1;
    }

    int GetShieldBlockValue(lua_State* L, Unit* unit)
    {
        if (Player* player = unit->ToPlayer())
            sEluna.Push(L, player->GetShieldBlockValue());
        if (Creature* creature = unit->ToCreature())
            sEluna.Push(L, creature->GetShieldBlockValue());
        else
            sEluna.Push(L, unit->GetShieldBlockValue());
        return 1;
    }

    int GetMountId(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetMountID());
        return 1;
    }

    int GetCorpseDelay(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetCorpseDelay());
        return 1;
    }

    int GetHomePosition(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        float x, y, z, o;
        creature->GetRespawnCoord(x, y, z, &o);

        sEluna.Push(L, x);
        sEluna.Push(L, y);
        sEluna.Push(L, z);
        sEluna.Push(L, o);
        return 4;
    }

    int AttackStart(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        Unit* target = sEluna.CHECK_UNIT(L, 1);
        if (!target)
            return 0;

        creature->AI()->AttackStart(target);
        return 0;
    }

    int RewardQuest(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 entry = luaL_checkunsigned(L, 1);

        Quest const* quest = sObjectMgr.GetQuestTemplate(entry);
        if (quest)
            player->RewardQuest(quest, 0, player);
        return 0;
    }

    int HasAura(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 spell = luaL_checkunsigned(L, 1);
        WorldObject* caster = sEluna.CHECK_WORLDOBJECT(L, 2);

        // sEluna.Push(L, player->HasAura(spell, caster ? caster->GetGUIDLow() : 0));
        return 1;
    }

    int IsARecruiter(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->GetSession()->IsARecruiter() || (player->GetSession()->GetRecruiterId() != 0));
        return 1;
    }

    int GetRecruiterId(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, player->GetSession()->GetRecruiterId());
        return 1;
    }

    int GetSelectedPlayer(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, player->GetSelectedPlayer());
        return 1;
    }

    int GetSelectedUnit(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, player->GetSelectedUnit());
        return 1;
    }

    int GetDistance(lua_State* L, Unit* unit)
    {
        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 1);
        if (obj && obj->IsInWorld())
            sEluna.Push(L, unit->GetDistance(obj));
        else
        {
            float X = luaL_checknumber(L, 1);
            float Y = luaL_checknumber(L, 2);
            float Z = luaL_checknumber(L, 3);
            sEluna.Push(L, unit->GetDistance(X, Y, Z));
        }
        return 1;
    }

    int GetLatency(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetSession()->GetLatency());
        return 1;
    }

    int GetCreatorGUID(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->GetCreatGetCreatorGuid());
        return 1;
    }

    int GetMinionGUID(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->GetMinionGuid());
        return 1;
    }

    int GetCharmerGUID(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetCharmerGuid());
        return 1;
    }

    int GetCharmGUID(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetCharmGuid());
        return 1;
    }

    int GetPetGUID(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetPetGuid());
        return 1;
    }

    int GetCritterGUID(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->GetCritterGuid());
        return 1;
    }

    int GetControllerGUID(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetCharmerOrOwnerGuid());
        return 1;
    }

    int GetControllerGUIDS(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetCharmerOrOwnerOrOwnGuid());
        return 1;
    }

    int SendAuctionMenu(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Creature* creature = sEluna.CHECK_CREATURE(L, 1);

        uint64 guid = creature ? creature->GetGUIDLow() : player->GetGUIDLow();
        if (!unit)
            return 0;

        AuctionHouseEntry const* ahEntry = AuctionHouseMgr::GetAuctionHouseEntry(unit);
        if (!ahEntry)
            return 0;

        WorldPacket data(MSG_AUCTION_HELLO, 12);
        data << uint64(guid);
        data << uint32(ahEntry->houseId);
        data << uint8(1);
        player->GetSession()->SendPacket(&data);
        return 0;
    }

    int SendMailMenu(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        GameObject* object = sEluna.CHECK_GAMEOBJECT(L, 1);
        if (!object)
            return 0;

        // WorldPacket data(SMSG_SHOW_MAILBOX, 8);
        // data << uint64(object->GetGUIDLow());
        // player->GetSession()->HandleGetMailList(data);
        return 0;
    }

    int SendTaxiMenu(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Creature* creature = sEluna.CHECK_CREATURE(L, 1);

        if (creature)
            player->GetSession()->SendTaxiMenu(creature);
        return 0;
    }

    int SendSpiritResurrect(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->GetSession()->SendSpiritResurrect();
        return 0;
    }

    int SendTabardVendorActivate(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 1);

        if (obj)
            player->GetSession()->SendTabardVendorActivate(obj->GetObjectGuid());
        return 0;
    }

    int SendShowBank(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 1);

        if (obj)
            player->GetSession()->SendShowBank(obj->GetObjectGuid());
        return 0;
    }

    int SendListInventory(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 1);

        if (obj)
            player->GetSession()->SendListInventory(obj->GetObjectGuid());
        return 0;
    }

    int SendTrainerList(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 1);

        if (obj)
            player->GetSession()->SendTrainerList(obj->GetObjectGuid());
        return 0;
    }

    int SendGuildInvite(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 1);

        if (obj)
            player->GetSession()->SendGuildInvite(sObjectMgr.GetPlayer(obj->GetObjectGuid()));
        return 0;
    }

    int LogoutPlayer(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool save = luaL_optbool(L, 1, true);

        player->GetSession()->LogoutPlayer(save);
        return 0;
    }

    int GetChampioningFaction(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, player->GetChampioningFaction());
        return 1;
    }

    int ResetAchievements(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // player->GetAchievementMgr().Reset();
        return 0;
    }

    int HasAchieved(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 achievementId = luaL_checkunsigned(L, 1);

        // sEluna.Push(L, player->GetAchievementMgr().HasAchievement(achievementId));
        return 1;
    }

    int GetOriginalSubGroup(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetOriginalSubGroup());
        return 1;
    }

    int GetOriginalGroup(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetOriginalGroup());
        return 1;
    }

    int RemoveFromBattlegroundOrBattlefieldRaid(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->RemoveFromBattleGroundRaid();
        return 0;
    }

    int CanUninviteFromGroup(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->CanUninviteFromGroup() == ERR_PARTY_RESULT_OK);
        return 1;
    }

    int GetNextRandomRaidMember(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        float radius = luaL_checknumber(L, 1);

        sEluna.Push(L, player->GetNextRandomRaidMember(radius));
        return 1;
    }

    int GetSubGroup(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetSubGroup());
        return 1;
    }

    int GetGroupInvite(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetGroupInvite());
        return 1;
    }

    int HasPendingBind(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->PendingHasPendingBind());
        return 1;
    }

    int UnbindInstance(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 map = luaL_checkunsigned(L, 1);
        uint32 difficulty = luaL_checkunsigned(L, 2);

        if (difficulty < MAX_DIFFICULTY)
            player->UnbindInstance(map, (Difficulty)difficulty);
        return 0;
    }

    int BindToInstance(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // player->BindToInstance();
        return 0;
    }

    int SetAtLoginFlag(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 flag = luaL_checkunsigned(L, 1);

        player->SetAtLoginFlag((AtLoginFlags)flag);
        return 0;
    }

    int InRandomLfgDungeon(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->inRandomLfgDungeon());
        return 1;
    }

    int IsUsingLfg(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->isUsingLfg());
        return 1;
    }

    int HasAtLoginFlag(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 flag = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->HasAtLoginFlag((AtLoginFlags)flag));
        return 1;
    }

    int IsVisibleForPlayer(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        Player* target = sEluna.CHECK_PLAYER(L, 1);

        if (target)
            sEluna.Push(L, player->IsVisibleGloballyFor(target));
        else
            sEluna.Push(L, false);
        return 1;
    }

    int IsNeverVisible(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->IsNeverVisible());
        return 1;
    }

    int CanFlyInZone(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 mapid = luaL_checkunsigned(L, 1);
        uint32 zone = luaL_checkunsigned(L, 1);

        // sEluna.Push(L, player->IsKnowHowFlyIn(mapid, zone));
        return 1;
    }

    int SetRestTime(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 value = luaL_checkunsigned(L, 1);

        player->SetRestTime(value);
        return 0;
    }

    int GetRestTime(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetRestTime());
        return 1;
    }

    int GetXPRestBonus(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 xp = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetXPRestBonus(xp));
        return 1;
    }

    int CanSpeak(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->CanSpeak());
        return 1;
    }

    int IsImmuneToEnvironmentalDamage(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->IsImmuneToEnvironmentalDamage());
        return 1;
    }

    int IsRested(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->isRested());
        return 1;
    }

    int LeaveBattleground(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool teleToEntryPoint = luaL_optbool(L, 1, true);

        player->LeaveBattleground(teleToEntryPoint);
        return 0;
    }

    int InBattlegroundQueue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->InBattleGroundQueue());
        return 1;
    }

    int GetBattlegroundTypeId(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetBattleGroundTypeId());
        return 1;
    }

    int GetBattlegroundId(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetBattleGroundId());
        return 1;
    }

    int IsOutdoorPvPActive(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->IsOutdoorPvPActive());
        return 1;
    }

    int InArena(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->InArena());
        return 1;
    }

    int InBattleground(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->InBattleGround());
        return 1;
    }

    int CanTameExoticPets(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->CanTameExoticPets());
        return 1;
    }

    int CanTitanGrip(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->CanTitanGrip());
        return 1;
    }

    int CanBlock(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->CanBlock());
        return 1;
    }

    int CanParry(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->CanParry());
        return 1;
    }

    int GetDrunkValue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetDrunkValue());
        return 1;
    }

    int GetStat(lua_State* L, Unit* unit)
    {
        uint32 stat = luaL_checkunsigned(L, 1);

        if (stat >= MAX_STATS)
            return 0;

        sEluna.Push(L, unit->GetStat((Stats)stat));
        return 1;
    }

    int GetBaseSpellPower(lua_State* L, Unit* unit)
    {
        uint32 spellschool = luaL_checkunsigned(L, 1);

        if (spellschool >= MAX_SPELL_SCHOOL)
            return 0;

        sEluna.Push(L, unit->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + spellschool));
        return 1;
    }

    int SetDrunkValue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint8 newDrunkValue = luaL_checkunsigned(L, 1);

        player->SetDrunkValue(newDrunkValue);
        return 0;
    }

    int GetSpellCooldowns(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (SpellCooldowns::const_iterator it = player->GetSpellCooldownMap().begin(); it != player->GetSpellCooldownMap().end(); ++it)
        {
            ++i;
            sEluna.Push(L, it->first);
            sEluna.Push(L, it->second.end);
            lua_settable(L, tbl);
        }

        lua_settop(L, tbl);
        return 1;
    }

    int ModifyArenaPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        int32 amount = luaL_checkunsigned(L, 1);

        player->ModifyArenaPoints(amount);
        return 0;
    }

    int ModifyHonorPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        int32 amount = luaL_checkunsigned(L, 1);

        player->ModifyHonorPoints(amount);
        return 0;
    }

    int GetReputationRank(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 faction = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetReputationRank(faction));
        return 1;
    }

    int IsHonorOrXPTarget(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        Unit* victim = sEluna.CHECK_UNIT(L, 1);

        if (victim)
            sEluna.Push(L, player->isHonorOrXPTarget(victim));
        else
            sEluna.Push(L, false);
        return 1;
    }

    int SetFactionForRace(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint8 race = luaL_checkunsigned(L, 1);

        player->setFactionForRace(race);
        return 0;
    }

    int SetSkill(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint16 id = luaL_checkunsigned(L, 1);
        uint16 step = luaL_checkunsigned(L, 2);
        uint16 currVal = luaL_checkunsigned(L, 3);
        uint16 maxVal = luaL_checkunsigned(L, 4);

        player->SetSkill(id, step, currVal, maxVal);
        return 0;
    }

    int HasSkill(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 skill = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->HasSkill(skill));
        return 1;
    }

    int GetSkillTempBonusValue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 skill = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetSkillTempBonusValue(skill));
        return 1;
    }

    int GetSkillPermBonusValue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 skill = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetSkillPermBonusValue(skill));
        return 1;
    }

    int GetSkillStep(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 skill = luaL_checkunsigned(L, 1);

        // sEluna.Push(L, player->GetSkillStep(skill));
        return 1;
    }

    int GetPureSkillValue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 skill = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetPureSkillValue(skill));
        return 1;
    }

    int GetBaseSkillValue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 skill = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetBaseSkillValue(skill));
        return 1;
    }

    int GetSkillValue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 skill = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetSkillValue(skill));
        return 1;
    }

    int GetPureMaxSkillValue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 skill = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetPureMaxSkillValue(skill));
        return 1;
    }

    int GetMaxSkillValue(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 skill = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetMaxSkillValue(skill));
        return 1;
    }

    int SetMovement(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        int32 pType = luaL_checkinteger(L, 1);

        // player->SetMovement((PlayerMovementType)pType);
        return 0;
    }

    int DurabilityRepair(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint16 position = luaL_checkunsigned(L, 1);
        bool cost = luaL_optbool(L, 2, true);
        float discountMod = luaL_checkinteger(L, 3);
        bool guildBank = luaL_optbool(L, 4, false);

        sEluna.Push(L, player->DurabilityRepair(position, cost, discountMod, guildBank));
        return 1;
    }

    int DurabilityRepairAll(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool cost = luaL_optbool(L, 1, true);
        float discountMod = luaL_checkinteger(L, 2);
        bool guildBank = luaL_optbool(L, 3, false);

        sEluna.Push(L, player->DurabilityRepairAll(cost, discountMod, guildBank));
        return 1;
    }

    int DurabilityPointLossForEquipSlot(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        int32 slot = luaL_checkinteger(L, 1);

        if (slot >= EQUIPMENT_SLOT_START && slot < EQUIPMENT_SLOT_END)
            player->DurabilityPointLossForEquipSlot((EquipmentSlots)slot);
        return 0;
    }

    int DurabilityPointsLossAll(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        int32 points = luaL_checkinteger(L, 1);
        bool inventory = luaL_optbool(L, 2, true);

        player->DurabilityPointsLossAll(points, inventory);
        return 0;
    }

    int DurabilityPointsLoss(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Item* item = sEluna.CHECK_ITEM(L, 1);
        int32 points = luaL_checkinteger(L, 2);

        if (item)
            player->DurabilityPointsLoss(item, points);
        return 0;
    }

    int DurabilityLoss(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Item* item = sEluna.CHECK_ITEM(L, 1);
        double percent = luaL_checknumber(L, 2);

        if (item)
            player->DurabilityLoss(item, percent);
        return 0;
    }

    int DurabilityLossAll(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        double percent = luaL_checknumber(L, 1);
        bool inventory = luaL_optbool(L, 2, true);

        player->DurabilityLossAll(percent, inventory);
        return 0;
    }

    int KillPlayer(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->KillPlayer();
        return 0;
    }

    int GetManaBonusFromIntellect(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetManaBonusFromIntellect());
        return 1;
    }

    int GetHealthBonusFromStamina(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetHealthBonusFromStamina());
        return 1;
    }

    int GetDifficulty(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool isRaid = luaL_optbool(L, 1, true);

        sEluna.Push(L, player->GetDifficulty(/*isRaid*/));
        return 1;
    }

    int GetGuildRank(lua_State* L, Unit* unit) // TODO: Move to Guild Methods
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetRank());
        return 1;
    }

    int SetGuildRank(lua_State* L, Unit* unit) // TODO: Move to Guild Methods
    {
        TO_PLAYER();

        uint8 rank = luaL_checkunsigned(L, 1);

        // if (!player->GetGuild())
        // return 0;

        player->SetRank(rank);
        return 0;
    }

    int RemoveFromGroup(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        if (!player->GetGroup())
            return 0;

        player->RemoveFromGroup();
        return 0;
    }

    int IsGroupVisibleFor(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        Player* target = sEluna.CHECK_PLAYER(L, 1);
        if (!target)
            sEluna.Push(L, false);
        else
            sEluna.Push(L, player->IsGroupVisibleFor(target));
        return 1;
    }

    int IsInSameRaidWith(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        Player* target = sEluna.CHECK_PLAYER(L, 1);
        if (!target)
            sEluna.Push(L, false);
        else
            sEluna.Push(L, player->IsInSameRaidWith(target));
        return 1;
    }

    int IsInSameGroupWith(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        Player* target = sEluna.CHECK_PLAYER(L, 1);
        if (!target)
            sEluna.Push(L, false);
        else
            sEluna.Push(L, player->IsInSameGroupWith(target));
        return 1;
    }

    int SetPvP(lua_State* L, Unit* unit)
    {
        bool apply = luaL_optbool(L, 1, true);

        unit->SetPvP(apply);
        return 0;
    }

    int SetFFA(lua_State* L, Unit* unit)
    {
        bool apply = luaL_optbool(L, 1, true);

        /*if (apply)
            unit->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
        else
            unit->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);*/

        return 0;
    }

    int SetSanctuary(lua_State* L, Unit* unit)
    {
        bool apply = luaL_optbool(L, 1, true);

        /*if (apply)
        {
            unit->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_SANCTUARY);
            unit->CombatStop();
            unit->CombatStopWithPets();
        }
        else
            unit->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_SANCTUARY);*/

        return 0;
    }

    int GetSpellCooldownDelay(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 spellId = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetSpellCooldownDelay(spellId));
        return 1;
    }

    int HasSpellCooldown(lua_State* L, Unit* unit)
    {
        uint32 spellId = luaL_checkunsigned(L, 1);

        if (Player* player = unit->ToPlayer())
            sEluna.Push(L, player->HasSpellCooldown(spellId));
        else if (Creature* creature = unit->ToCreature())
            sEluna.Push(L, creature->HasSpellCooldown(spellId));
        else
            sEluna.Push(L, false);
        return 1;
    }

    int IsAuctioneer(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isAuctioner());
        return 1;
    }

    int HealthBelowPct(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->HealthBelowPct(luaL_checkint(L, 1)));
        return 1;
    }

    int HealthAbovePct(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->HealthAbovePct(luaL_checkint(L, 1)));
        return 1;
    }

    int GetSpecsCount(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, player->GetSpecsCount());
        return 1;
    }

    int GetActiveSpec(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, player->GetActiveSpec());
        return 1;
    }

    int HasTalent(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 spellId = luaL_checkunsigned(L, 1);
        uint8 spec = luaL_checkunsigned(L, 2);
        /*if (spec >= MAX_TALENT_SPECS)
        sEluna.Push(L, false);
        else
        sEluna.Push(L, player->HasTalent(spellId, spec));*/
        return 1;
    }

    int AddTalent(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 spellId = luaL_checkunsigned(L, 1);
        uint8 spec = luaL_checkunsigned(L, 2);
        bool learning = luaL_optbool(L, 3, true);
        /*if (spec >= MAX_TALENT_SPECS)
        sEluna.Push(L, false);
        else
        sEluna.Push(L, player->AddTalent(spellId, spec, learning));*/
        return 1;
    }

    int ResetTalentsCost(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->resetTalentsCost());
        return 1;
    }

    int ResetTalents(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool no_cost = luaL_optbool(L, 1, false);

        player->resetTalents(no_cost);
        // player->SendTalentsInfoData(false);
        return 0;
    }

    int SetFreeTalentPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 points = luaL_checkunsigned(L, 1);

        player->SetFreeTalentPoints(points);
        return 0;
    }

    int GetFreeTalentPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetFreeTalentPoints());
        return 1;
    }

    int GetGuildName(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        if (!player->GetGuildId())
            return 0;
        sEluna.Push(L, sGuildMgr.GetGuildNameById(player->GetGuildId()));
        return 1;
    }

    int GetReputation(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 faction = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetReputationMgr().GetReputation(faction));
        return 1;
    }

    int SetReputation(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 faction = luaL_checkunsigned(L, 1);
        uint32 value = luaL_checkunsigned(L, 2);

        // player->SetReputation(faction, value);
        return 0;
    }

    int RemoveSpell(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);
        bool disabled = luaL_optbool(L, 2, false);
        bool learn_low_rank = luaL_optbool(L, 3, true);

        player->removeSpell(entry, disabled, learn_low_rank);
        return 0;
    }

    int ClearComboPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->ClearComboPoints();
        return 0;
    }

    int GainSpellComboPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        int8 count = luaL_checkinteger(L, 1);

        // player->GainSpellComboPoints(count);
        return 0;
    }

    int AddComboPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Unit* target = sEluna.CHECK_UNIT(L, 1);
        int8 count = luaL_checkinteger(L, 2);
        if (!target)
            return 0;

        player->AddComboPoints(target, count);
        return 0;
    }

    int GetComboTarget(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, sObjectAccessor->FindUnit(player->GetComboTarget()));
        return 1;
    }

    int GetComboPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetComboPoints());
        return 1;
    }

    int HasReceivedQuestReward(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 entry = luaL_checkunsigned(L, 1);

        // sEluna.Push(L, player->IsQuestRewarded(entry));
        return 1;
    }

    int RegenerateHealth(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // player->RegenerateHealth();
        return 0;
    }

    int Regenerate(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 power = luaL_checkunsigned(L, 1);
        if (power >= MAX_POWERS)
            return 0;

        // player->Regenerate((Powers)power);
        return 0;
    }

    int RegenerateAll(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->RegenerateAll();
        return 0;
    }

    int ResetPetTalents(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // player->ResetPetTalents();
        return 0;
    }

    int SaveToDB(lua_State* L, Unit* unit)
    {
        if (Player* player = unit->ToPlayer())
            player->SaveToDB();
        if (Creature* creature = unit->ToCreature())
            creature->SaveToDB();
        return 0;
    }

    int Emote(lua_State* L, Unit* unit)
    {
        unit->HandleEmoteCommand(luaL_checkunsigned(L, 1));
        return 0;
    }

    int CountPctFromCurHealth(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->CountPctFromCurHealth(luaL_checkint(L, 1)));
        return 1;
    }

    int CountPctFromMaxHealth(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->CountPctFromMaxHealth(luaL_checkint(L, 1)));
        return 1;
    }

    int GetInGameTime(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetInGameTime());
        return 1;
    }

    int TalkedToCreature(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);
        Creature* creature = sEluna.CHECK_CREATURE(L, 2);
        if (!creature)
            return 0;

        player->TalkedToCreature(entry, creature->GetObjectGuid());
        return 0;
    }

    int KillGOCredit(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);
        uint64 guid = sEluna.CHECK_ULONG(L, 2);
        // player->KillCreditGO(entry, guid);
        return 0;
    }

    int KilledPlayerCredit(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // player->KilledPlayerCredit();
        return 0;
    }

    int KilledMonsterCredit(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);

        // player->KilledMonsterCredit(entry, 0);
        return 0;
    }

    int GroupEventHappens(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 questId = luaL_checkunsigned(L, 1);
        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 2);
        if (!obj)
            return 0;

        player->GroupEventHappens(questId, obj);
        return 0;
    }

    int AreaExploredOrEventHappens(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 questId = luaL_checkunsigned(L, 1);

        player->AreaExploredOrEventHappens(questId);
        return 0;
    }

    int CanShareQuest(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 entry = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->CanShareQuest(entry));
        return 1;
    }

    int HasQuestForGO(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        int32 entry = luaL_checkinteger(L, 1);

        sEluna.Push(L, player->HasQuestForGO(entry));
        return 1;
    }

    int HasQuestForItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 entry = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->HasQuestForItem(entry));
        return 1;
    }

    int GetReqKillOrCastCurrentCount(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 questId = luaL_checkunsigned(L, 1);
        int32 entry = luaL_checkinteger(L, 2);

        sEluna.Push(L, player->GetReqKillOrCastCurrentCount(questId, entry));
        return 1;
    }

    int RemoveRewardedQuest(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);

        // player->RemoveRewardedQuest(entry);
        return 0;
    }

    int RemoveActiveQuest(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);

        // player->RemoveActiveQuest(entry);
        return 0;
    }

    int SetQuestStatus(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);
        uint32 status = luaL_checkunsigned(L, 2);
        if (status >= MAX_QUEST_STATUS)
            return 0;

        player->SetQuestStatus(entry, (QuestStatus)status);
        return 0;
    }

    int GetQuestStatus(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetQuestStatus(entry));
        return 1;
    }

    int GetQuestRewardStatus(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 questId = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->GetQuestRewardStatus(questId));
        return 1;
    }

    int FailQuest(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);

        player->FailQuest(entry);
        return 0;
    }

    int IncompleteQuest(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);

        player->IncompleteQuest(entry);
        return 0;
    }

    int CompleteQuest(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);

        player->CompleteQuest(entry);
        return 0;
    }

    int IsActiveQuest(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 entry = luaL_checkunsigned(L, 1);

        sEluna.Push(L, player->IsActiveQuest(entry));
        return 1;
    }

    int GetQuestLevel(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Quest* quest = sEluna.CHECK_QUEST(L, 1);
        if (!quest)
            return 0;

        sEluna.Push(L, player->GetQuestLevelForPlayer(quest));
        return 1;
    }

    int GetItemByEntry(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);

        // sEluna.Push(L, player->GetItemByEntry(entry));
        return 1;
    }

    int GetEquippedItemBySlot(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint8 slot = luaL_checkunsigned(L, 1);
        if (slot >= EQUIPMENT_SLOT_END)
            return 0;

        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        sEluna.Push(L, item);
        return 1;
    }

    int SetSheath(lua_State* L, Unit* unit)
    {
        uint32 sheathed = luaL_checkunsigned(L, 1);
        if (sheathed >= MAX_SHEATH_STATE)
            return 0;

        if (Player* player = unit->ToPlayer())
            player->SetSheath((SheathState)sheathed);
        else
            unit->SetSheath((SheathState)sheathed);
        return 0;
    }

    int Whisper(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        std::string text = luaL_checkstring(L, 1);
        uint32 lang = luaL_checkunsigned(L, 2);
        ObjectGuid guid = player->GetObjectGuid();

        player->Whisper(text, lang, guid);
        return 0;
    }

    int TextEmote(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        std::string text = luaL_checkstring(L, 1);

        player->TextEmote(text);
        return 0;
    }

    int Yell(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        std::string text = luaL_checkstring(L, 1);
        uint32 lang = luaL_checkunsigned(L, 2);

        player->Yell(text, lang);
        return 0;
    }

    int Say(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        std::string text = luaL_checkstring(L, 1);
        uint32 lang = luaL_checkunsigned(L, 2);

        player->Say(text, lang);
        return 0;
    }

    int GetPhaseMaskForSpawn(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, player->GetPhaseMaskForSpawn());
        return 1;
    }

    int SummonPet(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 entry = luaL_checkunsigned(L, 1);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        float z = luaL_checknumber(L, 4);
        float o = luaL_checknumber(L, 5);
        uint32 petType = luaL_checkunsigned(L, 6);
        uint32 despwtime = luaL_checkunsigned(L, 7);

        if (petType >= MAX_PET_TYPE)
            return 0;

        // player->SummonPet(entry, x, y, z, o, (PetType)petType, despwtime);
        return 0;
    }

    int RemovePet(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        int mode = luaL_optint(L, 1, PET_SAVE_AS_DELETED);
        bool returnreagent = luaL_optbool(L, 1, false);

        if (!player->GetPet())
            return 0;

        // player->RemovePet(player->GetPet(), (PetSaveMode)mode, returnreagent);
        return 0;
    }

    int GetRestType(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetRestType());
        return 1;
    }

    int SetRestType(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        int type = luaL_checkinteger(L, 1);

        player->SetRestType((RestType)type);
        return 0;
    }

    int SetRestBonus(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        float bonus = luaL_checknumber(L, 1);

        player->SetRestBonus(bonus);
        return 0;
    }

    int GetRestBonus(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetRestBonus());
        return 1;
    }

    int GiveLevel(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint8 level = luaL_checkunsigned(L, 1);

        player->GiveLevel(level);
        return 0;
    }

    int GiveXP(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 xp = luaL_checkunsigned(L, 1);
        Unit* victim = sEluna.CHECK_UNIT(L, 2);
        float group_rate = luaL_optnumber(L, 3, 1.0f);
        bool pureXP = luaL_optbool(L, 4, true);
        bool triggerHook = luaL_optbool(L, 5, true);

        if (xp < 1)
            return 0;
        /*if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN))
        return 0;
        if (victim && victim->GetTypeId() == TYPEID_UNIT && !victim->ToCreature()->hasLootRecipient())
        return 0;

        uint8 level = player->getLevel();

        if (triggerHook)
        sScriptMgr->OnGivePlayerXP(player, xp, victim);

        if (!pureXP)
        {
        // Favored experience increase START
        uint32 zone = player->GetZoneId();
        float favored_exp_mult = 0;
        if ((player->HasAura(32096) || player->HasAura(32098)) && (zone == 3483 || zone == 3562 || zone == 3836 || zone == 3713 || zone == 3714))
        favored_exp_mult = 0.05f; // Thrallmar's Favor and Honor Hold's Favor
        xp = uint32(xp * (1 + favored_exp_mult));
        // Favored experience increase END
        }

        // XP to money conversion processed in Player::RewardQuest
        if (level >= sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
        return 0;

        uint32 bonus_xp = 0;
        bool recruitAFriend = pureXP ? false : player->GetsRecruitAFriendBonus(true);
        if (!pureXP)
        {
        // RaF does NOT stack with rested experience
        if (recruitAFriend)
        bonus_xp = 2 * xp; // xp + bonus_xp must add up to 3 * xp for RaF; calculation for quests done client-side
        else
        bonus_xp = victim ? player->GetXPRestBonus(xp) : 0; // XP resting bonus
        }

        player->SendLogXPGain(xp, victim, bonus_xp, recruitAFriend, group_rate);

        uint32 curXP = player->GetUInt32Value(PLAYER_XP);
        uint32 nextLvlXP = player->GetUInt32Value(PLAYER_NEXT_LEVEL_XP);
        uint32 newXP = curXP + xp + bonus_xp;

        while (newXP >= nextLvlXP && level < sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
        {
        newXP -= nextLvlXP;

        if (level < sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
        player->GiveLevel(level + 1);

        level = player->getLevel();
        nextLvlXP = player->GetUInt32Value(PLAYER_NEXT_LEVEL_XP);
        }

        player->SetUInt32Value(PLAYER_XP, newXP);*/
        return 0;
    }

    int IsGMVisible(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->isGMVisible());
        return 1;
    }

    int IsTaxiCheater(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->isTaxiCheater());
        return 1;
    }

    int IsGMChat(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->isGMChat());
        return 1;
    }

    int IsAcceptingWhispers(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->isAcceptWhispers());
        return 1;
    }

    int SetAcceptWhispers(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool on = luaL_optbool(L, 1, true);

        player->SetAcceptWhispers(on);
        return 0;
    }

    int SetPvPDeath(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool on = luaL_optbool(L, 1, true);

        player->SetPvPDeath(on);
        return 0;
    }

    int SetGMVisible(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool on = luaL_optbool(L, 1, true);

        player->SetGMVisible(on);
        return 0;
    }

    int SetTaxiCheat(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool on = luaL_optbool(L, 1, true);

        player->SetTaxiCheater(on);
        return 0;
    }

    int SetGMChat(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool on = luaL_optbool(L, 1, true);

        player->SetGMChat(on);
        return 0;
    }

    int SetGameMaster(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool on = luaL_optbool(L, 1, true);

        player->SetGameMaster(on);
        return 0;
    }

    int GetChatTag(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetChatTag());
        return 1;
    }

    int IsDND(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->isDND());
        return 1;
    }

    int IsAFK(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->isAFK());
        return 1;
    }

    int ToggleDND(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->ToggleDND();
        return 0;
    }

    int ToggleAFK(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->ToggleAFK();
        return 0;
    }

    int IsFalling(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        // sEluna.Push(L, player->IsFalling());
        return 1;
    }

    int IsUnderWater(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->IsUnderWater());
        return 1;
    }

    int IsInWater(lua_State* L, Unit* unit)
    {
        if (Player* player = unit->ToPlayer())
            sEluna.Push(L, player->IsInWater());
        else
            sEluna.Push(L, unit->IsInWater());
        return 1;
    }

    int GetVictim(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->getVictim());
        return 1;
    }

    int GetNearestTargetInAttackDistance(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        float dist = luaL_optnumber(L, 1, 0.0f);
        // sEluna.Push(L, creature->SelectNearestTargetInAttackDistance(dist));
        return 1;
    }

    int GetNearestTarget(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        float dist = luaL_optnumber(L, 1, 0.0f);
        // sEluna.Push(L, creature->SelectNearestTarget(dist));
        return 1;
    }

    int GetNearestHostileTargetInAggroRange(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        bool checkLOS = luaL_optbool(L, 1, false);
        // sEluna.Push(L, creature->SelectNearestHostileUnitInAggroRange(checkLOS));
        return 1;
    }

    int GetNearbyTarget(lua_State* L, Unit* unit)
    {
        float dist = luaL_optnumber(L, 1, 5.0f);
        Unit* exclude = sEluna.CHECK_UNIT(L, 2);

        // sEluna.Push(L, unit->SelectNearbyTarget(exclude, dist));
        return 1;
    }

    int GetObjectGlobally(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 lowguid = luaL_checkunsigned(L, 1);
        uint32 entry = luaL_checkunsigned(L, 2);

        // sEluna.Push(L, ChatHandler(player->GetSession()).GetObjectGlobalyWithGuidOrNearWithDbGuid(lowguid, entry));
        return 1;
    }

    int GetNearbyGameObject(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, ChatHandler(player->GetSession()).GetNearbyGameObject());
        return 1;
    }

    int SendChatMessageToPlayer(lua_State* L, Unit* unit)
    {
        uint8 type = luaL_checkunsigned(L, 1);
        uint32 lang = luaL_checkunsigned(L, 2);
        const char* msg = luaL_checkstring(L, 3);
        Player* target = sEluna.CHECK_PLAYER(L, 4);
        if (!target || type == CHAT_MSG_CHANNEL)
            return 0;

        WorldPacket* data = new WorldPacket();
        uint32 messageLength = (uint32)strlen(msg) + 1;
        data->Initialize(SMSG_MESSAGECHAT, 100);
        *data << (uint8)type;
        *data << lang;
        *data << unit->GetGUIDLow();
        *data << uint32(0);
        *data << unit->GetGUIDLow();
        *data << messageLength;
        *data << msg;
        if (unit->ToPlayer() && type != CHAT_MSG_WHISPER_INFORM && type != CHAT_MSG_DND && type != CHAT_MSG_AFK)
            *data << uint8(unit->ToPlayer()->GetChatTag());
        else
            *data << uint8(0);
        target->GetSession()->SendPacket(data);
        return 0;
    }

    int GetCurrentSpell(lua_State* L, Unit* unit)
    {
        uint32 type = luaL_checkunsigned(L, 1);
        if (type >= CURRENT_MAX_SPELL)
        {
            luaL_error(L, "Invalid spell type (%d)", type);
            return 0;
        }
        sEluna.Push(L, unit->GetCurrentSpell(type));
        return 1;
    }

    int EquipItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint16 dest = 0;
        Item* item = sEluna.CHECK_ITEM(L, 1);
        uint32 slot = luaL_checkunsigned(L, 2);

        if (slot >= INVENTORY_SLOT_BAG_END)
            return 0;

        if (!item)
        {
            uint32 entry = luaL_checkunsigned(L, 1);
            item = Item::CreateItem(entry, 1, player);
            if (!item)
                return 0;

            InventoryResult result = player->CanEquipItem(slot, dest, item, false);
            if (result != EQUIP_ERR_OK)
            {
                delete item;
                return 0;
            }
            player->ItemAddedQuestCheck(entry, 1);
            // player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_RECEIVE_EPIC_ITEM, entry, 1);
        }
        else
        {
            InventoryResult result = player->CanEquipItem(slot, dest, item, false);
            if (result != EQUIP_ERR_OK)
                return 0;
            player->RemoveItem(item->GetBagSlot(), item->GetSlot(), true);
        }

        sEluna.Push(L, player->EquipItem(dest, item, true));
        return 1;
    }

    int CanEquipItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        Item* item = sEluna.CHECK_ITEM(L, 1);
        uint32 slot = luaL_checkunsigned(L, 2);
        if (slot >= EQUIPMENT_SLOT_END)
        {
            sEluna.Push(L, false);
            return 1;
        }

        if (!item)
        {
            uint32 entry = luaL_checkunsigned(L, 1);
            uint16 dest;
            InventoryResult msg = player->CanEquipNewItem(slot, dest, entry, false);
            if (msg != EQUIP_ERR_OK)
            {
                sEluna.Push(L, false);
                return 1;
            }
        }
        else
        {
            uint16 dest;
            InventoryResult msg = player->CanEquipItem(slot, dest, item, false);
            if (msg != EQUIP_ERR_OK)
            {
                sEluna.Push(L, false);
                return 1;
            }
        }
        sEluna.Push(L, true);
        return 1;
    }

    int GetInventoryItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint8 slot = luaL_checkunsigned(L, 1);
        if (slot >= INVENTORY_SLOT_ITEM_END)
            return 0;

        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        sEluna.Push(L, item);
        return 1;
    }

    int GetBagItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint8 bagslot = luaL_checkunsigned(L, 1);
        uint8 slot = luaL_checkunsigned(L, 2);

        if (bagslot < INVENTORY_SLOT_BAG_START && bagslot >= INVENTORY_SLOT_BAG_END)
            return 0;

        /*Bag* bag = player->GetBagByPos(bagslot);
        if (!bag || slot >= bag->GetBagSize())
        return 0;*/

        Item* item = player->GetItemByPos(bagslot, slot);
        sEluna.Push(L, item);
        return 1;
    }

    int SummonGameObject(lua_State* L, Unit* unit)
    {
        uint32 entry = luaL_checkunsigned(L, 1);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        float z = luaL_checknumber(L, 4);
        float o = luaL_checknumber(L, 5);
        uint32 respawnDelay = luaL_optunsigned(L, 6, 30);
        sEluna.Push(L, unit->SummonGameObject(entry, x, y, z, o, respawnDelay));
        return 1;
    }

    int SpawnCreature(lua_State* L, Unit* unit)
    {
        uint32 entry = luaL_checkunsigned(L, 1);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        float z = luaL_checknumber(L, 4);
        float o = luaL_checknumber(L, 5);
        uint32 spawnType = luaL_optunsigned(L, 6, 0);
        uint32 despawnTimer = luaL_optunsigned(L, 7, 0);

        TempSummonType type;
        switch (spawnType)
        {
        case 1:
            type = TEMPSUMMON_TIMED_OR_DEAD_DESPAWN;
            break;
        case 2:
            type = TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN;
            break;
        case 3:
            type = TEMPSUMMON_TIMED_DESPAWN;
            break;
        case 5:
            type = TEMPSUMMON_CORPSE_DESPAWN;
            break;
        case 6:
            type = TEMPSUMMON_CORPSE_TIMED_DESPAWN;
            break;
        case 7:
            type = TEMPSUMMON_DEAD_DESPAWN;
            break;
        case 8:
            type = TEMPSUMMON_MANUAL_DESPAWN;
            break;
        }
        sEluna.Push(L, unit->SummonCreature(entry, x, y, z, o, type, despawnTimer));
        return 1;
    }

    int DealDamage(lua_State* L, Unit* unit)
    {
        Unit* target = sEluna.CHECK_UNIT(L, 1);
        uint32 amount = luaL_checkunsigned(L, 2);

        /*if (!target)
        unit->DealDamage(unit, amount);
        else
        unit->DealDamage(target, amount);*/
        return 0;
    }

    int Despawn(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        uint32 time = luaL_optunsigned(L, 1, 0);
        // creature->DespawnOrUnsummon(time);
        return 0;
    }

    int GetStandState(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->getStandState());
        return 0;
    }

    int GetArenaPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetArenaPoints());
        return 1;
    }

    int KnockbackFrom(lua_State* L, Unit* unit)
    {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float speedXY = luaL_checknumber(L, 3);
        float speedZ = luaL_checknumber(L, 4);
        // unit->KnockbackFrom(x, y, speedXY, speedZ);
        return 0;
    }

    int JumpTo(lua_State* L, Unit* unit)
    {
        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 1);
        float speedZ = luaL_checknumber(L, 2);
        if (!obj)
            return 0;

        // unit->JumpTo(obj, speedZ);
        return 0;
    }

    int Jump(lua_State* L, Unit* unit)
    {
        float speedXY = luaL_checknumber(L, 1);
        float speedZ = luaL_checknumber(L, 2);
        bool forward = luaL_optbool(L, 3, true);
        // unit->JumpTo(speedXY, speedZ, forward);
        return 0;
    }

    int JumpToCoords(lua_State* L, Unit* unit)
    {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = luaL_checknumber(L, 3);
        float speedXY = luaL_checknumber(L, 4);
        float speedZ = luaL_checknumber(L, 5);
        // unit->GetMotionMaster()->MoveJump(x, y, z, speedXY, speedZ);
        return 0;
    }

    int MoveCharge(lua_State* L, Unit* unit)
    {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = luaL_checknumber(L, 3);
        float speed = luaL_checknumber(L, 4);
        // unit->GetMotionMaster()->MoveCharge(x, y, z, speed);
        return 0;
    }

    int MoveChase(lua_State* L, Unit* unit)
    {
        Unit* target = sEluna.CHECK_UNIT(L, 1);
        float dist = luaL_optnumber(L, 2, 0.0f);
        float angle = luaL_optnumber(L, 3, 0.0f);
        unit->GetMotionMaster()->MoveChase(target, dist, angle);
        return 0;
    }

    int SetName(lua_State* L, Unit* unit)
    {
        const char* name = luaL_checkstring(L, 1);
        if (std::string(name).length() > 0)
            unit->SetName(name);
        return 0;
    }

    int SetStunned(lua_State* L, Unit* unit)
    {
        bool apply = luaL_optbool(L, 1, true);
        // unit->SetControlled(apply, UNIT_STATE_STUNNED);
        return 0;
    }

    int SetRooted(lua_State* L, Unit* unit)
    {
        bool apply = luaL_optbool(L, 1, true);
        // unit->SetControlled(apply, UNIT_STATE_ROOT);
        return 0;
    }

    int SetConfused(lua_State* L, Unit* unit)
    {
        bool apply = luaL_optbool(L, 1, true);
        // unit->SetControlled(apply, UNIT_STATE_CONFUSED);
        return 0;
    }

    int SetFeared(lua_State* L, Unit* unit)
    {
        bool apply = luaL_optbool(L, 1, true);
        // unit->SetControlled(apply, UNIT_STATE_FLEEING);
        return 0;
    }

    int SetGender(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Gender gender;
        uint32 _gender = luaL_checkint(L, 1);

        switch (_gender)
        {
        case 0:
            gender = GENDER_MALE;
            break;
        case 1:
            gender = GENDER_FEMALE;
            break;
        default:
            luaL_error(L, "Invalid gender (%d)", _gender);
            return 0;
        }

        player->SetByteValue(UNIT_FIELD_BYTES_0, 2, gender);
        player->SetByteValue(PLAYER_BYTES_3, 0, gender);
        player->InitDisplayIds();
        return 0;
    }

    int MoveTo(lua_State* L, Unit* unit)
    {
        float id = luaL_checknumber(L, 1);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        float z = luaL_checknumber(L, 4);
        bool generatePath = luaL_optbool(L, 5, true);
        unit->GetMotionMaster()->MovePoint(id, x, y, z, generatePath);
        return 0;
    }

    int MoveFollow(lua_State* L, Unit* unit)
    {
        Unit* target = sEluna.CHECK_UNIT(L, 1);
        float dist = luaL_checknumber(L, 2);
        float angle = luaL_checknumber(L, 3);
        unit->GetMotionMaster()->MoveFollow(target, dist, angle);
        return 0;
    }

    int MoveClear(lua_State* L, Unit* unit)
    {
        unit->GetMotionMaster()->Clear();
        return 0;
    }

    int MoveRandom(lua_State* L, Unit* unit)
    {
        float radius = luaL_checknumber(L, 1);
        float x, y, z;
        unit->GetPosition(x, y, z);
        unit->GetMotionMaster()->MoveRandomAroundPoint(x, y, z, radius);
        return 0;
    }

    int MoveRotate(lua_State* L, Unit* unit)
    {
        uint32 time = luaL_checkunsigned(L, 1);
        bool left = luaL_optbool(L, 2, true);
        // unit->GetMotionMaster()->MoveRotate(time, left ? ROTATE_DIRECTION_LEFT : ROTATE_DIRECTION_RIGHT);
        return 0;
    }

    int SetWalk(lua_State* L, Unit* unit)
    {
        bool enable = luaL_optbool(L, 1, true);
        /*if (Creature* creature = unit->ToCreature())
        sEluna.Push(L, creature->SetWalk(enable));
        else
        sEluna.Push(L, unit->SetWalk(enable));*/
        return 1;
    }

    int SetSpeed(lua_State* L, Unit* unit)
    {
        uint32 type = luaL_checkunsigned(L, 1);
        float rate = luaL_checknumber(L, 2);
        bool forced = luaL_optbool(L, 3, false);
        if (type >= MAX_MOVE_TYPE)
            luaL_error(L, "Invalid movement type (%d)", type);
        else
            unit->SetSpeedRate((UnitMoveType)type, rate, forced);
        return 0;
    }

    int GetHonorPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetHonorPoints());
        return 1;
    }

    int GetGossipTextId(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldObject* obj = sEluna.CHECK_WORLDOBJECT(L, 1);
        if (!obj)
            return 0;
        sEluna.Push(L, player->GetGossipTextId(obj));
        return 1;
    }

    int GetSelection(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, player->GetSelectedUnit());
        return 1;
    }

    int GetGMRank(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetSession()->GetSecurity());
        return 1;
    }

    int GetCoinage(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetMoney());
        return 1;
    }

    int GetDisplayId(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetDisplayId());
        return 1;
    }

    int GetNativeDisplayId(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetNativeDisplayId());
        return 1;
    }

    int GetName(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetName());
        return 1;
    }

    int GetLevel(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->getLevel());
        return 1;
    }

    int GetHealth(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetHealth());
        return 1;
    }

    int GetGuildId(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetGuildId());
        return 1;
    }

    int GetTeam(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetTeamId());
        return 1;
    }

    int GetPower(lua_State* L, Unit* unit)
    {
        int type = luaL_optint(L, 1, -1);
        if (type == -1)
        {

            switch (unit->getClass())
            {
            case 1:
                type = POWER_RAGE;
                break;
            case 4:
                type = POWER_ENERGY;
                break;
            /*case 6:
                type = POWER_RUNIC_POWER;
                break;*/
            case 2:
            case 3:
            case 5:
            case 7:
            case 8:
            case 9:
            case 11:
                type = POWER_MANA;
                break;
            default:
                type = POWER_MANA;
            }
        }
        else if (type >= POWER_ALL)
        {
            luaL_error(L, "Invalid power type (%d)", type);
            return 0;
        }

        sEluna.Push(L, unit->GetPower((Powers) type));
        return 1;
    }

    int GetMaxPower(lua_State* L, Unit* unit)
    {
        int type = luaL_optint(L, 1, -1);
        if (type == -1)
        {

            switch (unit->getClass())
            {
            case 1:
                type = POWER_RAGE;
                break;
            case 4:
                type = POWER_ENERGY;
                break;
            /*case 6:
                type = POWER_RUNIC_POWER;
                break;*/
            case 2:
            case 3:
            case 5:
            case 7:
            case 8:
            case 9:
            case 11:
                type = POWER_MANA;
                break;
            default:
                type = POWER_MANA;
            }
        }
        else if (type < 0 || type >= POWER_ALL)
        {
            luaL_error(L, "Invalid index (%d)", type);
            return 0;
        }

        sEluna.Push(L, unit->GetMaxPower((Powers) type));
        return 1;
    }

    int GetPowerType(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->getPowerType());
        return 1;
    }

    int GetMaxHealth(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetMaxHealth());
        return 1;
    }

    int GetHealthPct(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetHealthPercent());
        return 1;
    }

    int GetPowerPct(lua_State* L, Unit* unit)
    {
        float percent = (unit->GetPower(unit->getPowerType()) / unit->GetMaxPower(unit->getPowerType())) * 100;
        sEluna.Push(L, percent);
        return 1;
    }

    int GetGender(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->getGender());
        return 1;
    }

    int GetRace(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->getRace());
        return 1;
    }

    int GetClass(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->getClass());
        return 1;
    }

    int GetCreatureType(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetCreatureType());
        return 1;
    }

    int GetClassAsString(lua_State* L, Unit* unit)
    {
        const char* str = NULL;
        switch (unit->getClass())
        {
        case 1:
            str = "Warrior";
            break;
        case 2:
            str = "Paladin";
            break;
        case 3:
            str = "Hunter";
            break;
        case 4:
            str = "Rogue";
            break;
        case 5:
            str = "Priest";
            break;
        /*case 6:
            str = "Death Knight";
            break;*/
        case 7:
            str = "Shaman";
            break;
        case 8:
            str = "Mage";
            break;
        case 9:
            str = "Warlock";
            break;
        case 11:
            str = "Druid";
            break;
        default:
            str = "NULL";
            break;
        }

        sEluna.Push(L, str);
        return 1;
    }

    int GetItemCount(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        int id = luaL_checknumber(L, 1);
        bool checkinBank = luaL_optbool(L, 2, false);
        sEluna.Push(L, player->GetItemCount(id, checkinBank));
        return 1;
    }

    int GetLifetimeKills(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 currentKills = player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORBALE_KILLS);
        sEluna.Push(L, currentKills);
        return 1;
    }

    int GetPlayerIP(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetSession()->GetRemoteAddress());
        return 1;
    }

    int GetLevelPlayedTime(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetLevelPlayedTime());
        return 1;
    }

    int GetTotalPlayedTime(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetTotalPlayedTime());
        return 1;
    }

    int GetGuild(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, sGuildMgr.GetGuildById(player->GetGuildId()));
        return 1;
    }

    int GetGroup(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetGroup());
        return 1;
    }

    int GetGearLevel(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        // sEluna.Push(L, player->GetAverageItemLevel());
        return 1;
    }

    int GetFaction(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->getFaction());
        return 1;
    }

    int SetFaction(lua_State* L, Unit* unit)
    {
        uint32 factionId = luaL_checkunsigned(L, 1);
        unit->setFaction(factionId);
        return 0;
    }

    int SetLevel(lua_State* L, Unit* unit)
    {
        uint32 newLevel = luaL_checkunsigned(L, 1);
        unit->SetLevel(newLevel);
        return 0;
    }

    int SetPhaseMask(lua_State* L, Unit* unit)
    {
        uint32 phaseMask = luaL_checkunsigned(L, 1);
        bool Update = luaL_optbool(L, 2, true);
        // unit->SetPhaseMask(phaseMask, Update);
        return 0;
    }

    int SetArenaPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 arenaP = luaL_checkunsigned(L, 1);
        player->SetArenaPoints(arenaP);
        return 0;
    }

    int SetHonorPoints(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 honorP = luaL_checkunsigned(L, 1);
        player->SetHonorPoints(honorP);
        return 0;
    }

    int SetLifetimeKills(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 val = luaL_checkunsigned(L, 1);
        player->SetUInt32Value(PLAYER_FIELD_LIFETIME_HONORBALE_KILLS, val);
        return 0;
    }

    int SetHealth(lua_State* L, Unit* unit)
    {
        uint32 amt = luaL_checkunsigned(L, 1);
        unit->SetHealth(amt);
        return 0;
    }

    int SetMaxHealth(lua_State* L, Unit* unit)
    {
        uint32 amt = luaL_checkunsigned(L, 1);
        unit->SetMaxHealth(amt);
        return 0;
    }

    int SetPower(lua_State* L, Unit* unit)
    {
        int type = luaL_checkinteger(L, 1);
        uint32 amt = luaL_checkunsigned(L, 2);

        switch (type)
        {
        case POWER_MANA:
            unit->SetPower(POWER_MANA, amt);
            break;
        case POWER_RAGE:
            unit->SetPower(POWER_RAGE, amt);
            break;
        case POWER_ENERGY:
            unit->SetPower(POWER_ENERGY, amt);
            break;
        /*case POWER_RUNIC_POWER:
            unit->SetPower(POWER_RUNIC_POWER, amt);
            break;*/
        default:
            luaL_error(L, "Invalid power type (%d)", type);
            break;
        }
        return 0;
    }

    int SetMaxPower(lua_State* L, Unit* unit)
    {
        int type = luaL_checkinteger(L, 1);
        int amt = luaL_checkunsigned(L, 2);

        switch (type)
        {
        case POWER_MANA:
            unit->SetMaxPower(POWER_MANA, amt);
            break;
        case POWER_RAGE:
            unit->SetMaxPower(POWER_RAGE, amt);
            break;
        case POWER_ENERGY:
            unit->SetMaxPower(POWER_ENERGY, amt);
            break;
        /*case POWER_RUNIC_POWER:
            unit->SetMaxPower(POWER_RUNIC_POWER, amt);
            break;*/
        default:
            luaL_error(L, "Invalid power type (%d)", type);
            break;
        }
        return 0;
    }

    int SetDisplayId(lua_State* L, Unit* unit)
    {
        uint32 model = luaL_checkunsigned(L, 1);
        unit->SetDisplayId(model);
        return 0;
    }

    int SetNativeDisplayId(lua_State* L, Unit* unit)
    {
        uint32 model = luaL_checkunsigned(L, 1);
        unit->SetNativeDisplayId(model);
        return 0;
    }

    int SetFacing(lua_State* L, Unit* unit)
    {
        float o = luaL_checknumber(L, 1);
        unit->SetFacingTo(o);
        return 0;
    }

    int SetCoinage(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 amt = luaL_checkunsigned(L, 1);
        player->SetMoney(amt);
        return 0;
    }

    int SetBindPoint(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = luaL_checknumber(L, 3);
        uint32 mapId = luaL_checkunsigned(L, 4);
        uint32 areaId = luaL_checkunsigned(L, 5);

        WorldLocation loc(mapId, x, y, z);
        player->SetHomebindToLocation(loc, areaId);
        return 0;
    }

    int SetBindPointAtPlayerLoc(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldLocation loc;
        /*player->GetPosition(&loc);
        loc.m_mapId = player->GetMapId();
        player->SetHomebind(loc, player->GetAreaId());*/
        return 0;
    }

    int SetKnownTitle(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 id = luaL_checkunsigned(L, 1);
        CharTitlesEntry const* t = sCharTitlesStore.LookupEntry(id);
        if (t)
            player->SetTitle(t, false);
        return 0;
    }

    int UnsetKnownTitle(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 id = luaL_checkunsigned(L, 1);
        CharTitlesEntry const* t = sCharTitlesStore.LookupEntry(id);
        if (t)
            player->SetTitle(t, true);
        return 0;
    }

    int SetCreatorGUID(lua_State* L, Unit* unit)
    {
        ObjectGuid guid = unit->GetObjectGuid();
        unit->SetCreatorGuid(guid);
        return 0;
    }

    int SetMinionGUID(lua_State* L, Unit* unit)
    {
        // ObjectGuid guid = unit->GetObjectGuid();
        // unit->SetMinionGuid(guid);
        return 0;
    }

    int SetCharmerGUID(lua_State* L, Unit* unit)
    {
        ObjectGuid guid = unit->GetObjectGuid();
        unit->SetCharmerGuid(guid);
        return 0;
    }

    int SetPetGUID(lua_State* L, Unit* unit)
    {
        ObjectGuid guid = unit->GetObjectGuid();
        unit->SetPetGuid(guid);
        return 0;
    }

    int SetCritterGUID(lua_State* L, Unit* unit)
    {
        // ObjectGuid guid = unit->GetObjectGuid();
        // unit->SetCritterGuid(guid);
        return 0;
    }

    int AdvanceSkillsToMax(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->UpdateSkillsToMaxSkillsForLevel();
        return 0;
    }

    int AdvanceAllSkills(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 step = luaL_checkunsigned(L, 1);

        if (!step)
            return 0;

        static const uint32 skillsArray[] = { SKILL_BOWS, SKILL_CROSSBOWS, SKILL_DAGGERS, SKILL_DEFENSE, SKILL_UNARMED, SKILL_GUNS, SKILL_AXES, SKILL_MACES, SKILL_SWORDS, SKILL_POLEARMS,
            SKILL_STAVES, SKILL_2H_AXES, SKILL_2H_MACES, SKILL_2H_SWORDS, SKILL_WANDS, SKILL_SHIELD, SKILL_FISHING, SKILL_MINING, SKILL_ENCHANTING, SKILL_BLACKSMITHING,
            SKILL_ALCHEMY, SKILL_HERBALISM, SKILL_ENGINEERING, SKILL_JEWELCRAFTING, SKILL_LEATHERWORKING, SKILL_LOCKPICKING, /*SKILL_INSCRIPTION,*/ SKILL_SKINNING, SKILL_TAILORING
        };
        static const uint32 skillsSize = sizeof(skillsArray) / sizeof(*skillsArray);

        for (int i = 0; i < skillsSize; ++i)
        {
            if (player->HasSkill(skillsArray[i]))
                player->UpdateSkill(skillsArray[i], step);
        }
        return 0;
    }

    int AdvanceSkill(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 _skillId = luaL_checkunsigned(L, 1);
        uint32 _step = luaL_checkunsigned(L, 2);
        if (_skillId && _step)
        {
            if (player->HasSkill(_skillId))
                player->UpdateSkill(_skillId, _step);
        }
        return 0;
    }

    int IsInGroup(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, (player->GetGroup() != NULL));
        return 1;
    }

    int IsInGuild(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, (player->GetGuildId() != 0));
        return 1;
    }

    int IsGM(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, player->isGameMaster());
        return 1;
    }

    int IsAlive(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isAlive());
        return 1;
    }

    int IsDead(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isDead());
        return 1;
    }

    int IsDying(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isDying());
        return 1;
    }

    int IsBanker(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isBanker());
        return 1;
    }

    int IsVendor(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isVendor());
        return 1;
    }

    int IsBattleMaster(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isBattleMaster());
        return 1;
    }

    int IsCharmed(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isCharmed());
        return 1;
    }

    int IsArmorer(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isArmorer());
        return 1;
    }

    int IsAttackingPlayer(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isAttackingPlayer());
        return 1;
    }

    int IsInArenaTeam(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 type = luaL_checkunsigned(L, 1);
        if (type < MAX_ARENA_SLOT && player->GetArenaTeamId(type))
            sEluna.Push(L, true);
        else
            sEluna.Push(L, false);
        return 1;
    }

    int IsInWorld(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->IsInWorld());
        return 1;
    }

    int IsPvPFlagged(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->IsPvP());
        return 1;
    }

    int HasQuest(lua_State* L, Unit* unit)
    {
        uint32 questId = luaL_checkunsigned(L, 1);

        if (Player* player = unit->ToPlayer())
            sEluna.Push(L, player->HasQuest(questId));
        else if (Creature* creature = unit->ToCreature())
            sEluna.Push(L, creature->HasQuest(questId));
        else
            sEluna.Push(L, unit->HasQuest(questId));
        return 1;
    }

    int IsHorde(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, (player->GetTeam() == HORDE));
        return 1;
    }

    int IsAlliance(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        sEluna.Push(L, (player->GetTeam() == ALLIANCE));
        return 1;
    }

    int IsInCombat(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isInCombat());
        return 1;
    }

    int HasTitle(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 id = luaL_checkunsigned(L, 1);
        CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(id);
        if (titleInfo)
            sEluna.Push(L, player->HasTitle(titleInfo));
        else
            sEluna.Push(L, false);
        return 1;
    }

    int HasSpell(lua_State* L, Unit* unit)
    {
        uint32 id = luaL_checkunsigned(L, 1);
        if (Player* player = unit->ToPlayer())
            sEluna.Push(L, player->HasSpell(id));
        else if (Creature* creature = unit->ToCreature())
            sEluna.Push(L, creature->HasSpell(id));
        else
            sEluna.Push(L, unit->HasSpell(id));
        return 1;
    }

    int HasItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 itemId = luaL_checkunsigned(L, 1);
        uint32 count = luaL_optunsigned(L, 2, 1);
        bool check_bank = luaL_optbool(L, 3, false);
        sEluna.Push(L, player->HasItemCount(itemId, count, check_bank));
        return 1;
    }

    int Teleport(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 mapId = luaL_checkunsigned(L, 1);
        float X = luaL_checknumber(L, 2);
        float Y = luaL_checknumber(L, 3);
        float Z = luaL_checknumber(L, 4);
        float O = luaL_checknumber(L, 5);
        if (player->IsTaxiFlying())
        {
            player->GetMotionMaster()->MovementExpired();
            player->m_taxi.ClearTaxiDestinations();
        }
        sEluna.Push(L, player->TeleportTo(mapId, X, Y, Z, O));
        return 1;
    }

    int AddLifetimeKills(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 val = luaL_checkunsigned(L, 1);
        uint32 currentKills = player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORBALE_KILLS);
        player->SetUInt32Value(PLAYER_FIELD_LIFETIME_HONORBALE_KILLS, currentKills + val);
        return 0;
    }

    int AddItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        uint32 itemId = luaL_checkunsigned(L, 1);
        uint32 itemCount = luaL_checkunsigned(L, 2);
        sEluna.Push(L, player->StoreNewItemInInventorySlot(itemId, itemCount));
        return 0;
    }

    int RemoveItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Item* item = sEluna.CHECK_ITEM(L, 1);
        uint32 itemCount = luaL_checkunsigned(L, 2);
        if (!item)
        {
            uint32 itemId = luaL_checkunsigned(L, 1);
            player->DestroyItemCount(itemId, itemCount, true);
        }
        else
            player->DestroyItemCount(item, itemCount, true);
        return 0;
    }

    int RemoveLifetimeKills(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 val = luaL_checkunsigned(L, 1);
        uint32 currentKills = player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORBALE_KILLS);
        if (val > currentKills)
            val = currentKills;
        player->SetUInt32Value(PLAYER_FIELD_LIFETIME_HONORBALE_KILLS, currentKills - val);
        return 0;
    }

    int ResetSpellCooldown(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 spellId = luaL_checkunsigned(L, 1);
        bool update = luaL_optbool(L, 2, true);
        player->RemoveSpellCooldown(spellId, update);
        return 0;
    }

    int ResetTypeCooldowns(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 category = luaL_checkunsigned(L, 1);
        bool update = luaL_optbool(L, 2, true);
        player->RemoveSpellCategoryCooldown(category, update);
        return 0;
    }

    int ResetAllCooldowns(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->RemoveAllSpellCooldown();
        return 0;
    }

    int SendClearCooldowns(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 spellId = luaL_checkunsigned(L, 1);
        Unit* target = sEluna.CHECK_UNIT(L, 2);
        if (!target)
            return 0;

        player->SendClearCooldown(spellId, target);
        return 0;
    }

    int SendBroadcastMessage(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        const char* message = luaL_checkstring(L, 1);
        if (std::string(message).length() > 0)
            ChatHandler(player->GetSession()).SendSysMessage(message);
        return 0;
    }

    int SendAreaTriggerMessage(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        const char* msg = luaL_checkstring(L, 1);
        if (std::string(msg).length() > 0)
            player->GetSession()->SendAreaTriggerMessage(msg);
        return 0;
    }

    int SendNotification(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        const char* msg = luaL_checkstring(L, 1);
        if (std::string(msg).length() > 0)
            player->GetSession()->SendNotification(msg);
        return 0;
    }

    int SendUnitWhisper(lua_State* L, Unit* unit)
    {
        const char* msg = luaL_checkstring(L, 1);
        Unit* receiver = sEluna.CHECK_UNIT(L, 2);
        bool bossWhisper = luaL_optbool(L, 3, false);
        if (receiver && std::string(msg).length() > 0)
            unit->MonsterWhisper(msg, receiver, bossWhisper);
        return 0;
    }

    int SendUnitEmote(lua_State* L, Unit* unit)
    {
        const char* msg = luaL_checkstring(L, 1);
        Unit* receiver = sEluna.CHECK_UNIT(L, 2);
        bool bossEmote = luaL_optbool(L, 3, false);
        if (std::string(msg).length() > 0)
            unit->MonsterTextEmote(msg, receiver ? receiver : 0, bossEmote);
        return 0;
    }

    int SendUnitSay(lua_State* L, Unit* unit)
    {
        const char* msg = luaL_checkstring(L, 1);
        uint32 language = luaL_checknumber(L, 2);
        if (std::string(msg).length() > 0)
            unit->MonsterSay(msg, language, unit);
        return 0;
    }

    int SendUnitYell(lua_State* L, Unit* unit)
    {
        const char* msg = luaL_checkstring(L, 1);
        uint32 language = luaL_checknumber(L, 2);
        if (std::string(msg).length() > 0)
            unit->MonsterYell(msg, language, unit);
        return 0;
    }

    int SendCreatureTalk(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        uint8 id = luaL_checknumber(L, 1);
        uint64 playerGUID = sEluna.CHECK_ULONG(L, 2);
        // creature->AI()->Talk(id, playerGUID);
        return 0;
    }

    int SendPacketToPlayer(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldPacket* data = sEluna.CHECK_PACKET(L, 1);
        if (data)
            player->GetSession()->SendPacket(data);
        return 0;
    }

    int SendPacket(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldPacket* data = sEluna.CHECK_PACKET(L, 1);
        if (data)
            player->SendMessageToSet(data, false);
        return 0;
    }

    int SendPacketToGroup(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldPacket* data = sEluna.CHECK_PACKET(L, 1);
        bool ignorePlayersInBg = luaL_optbool(L, 2, false);
        // if (data && player->GetGroup())
        // player->GetGroup()->BroadcastPacket(data, ignorePlayersInBg, -1, player->GetGUIDLow());
        return 0;
    }

    int SendPacketToGuild(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldPacket* data = sEluna.CHECK_PACKET(L, 1);
        // if (data && player->GetGuild())
        // player->GetGuild()->BroadcastPacket(data);
        return 0;
    }

    int SendPacketToRankedInGuild(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldPacket* data = sEluna.CHECK_PACKET(L, 1);
        uint8 ranked = luaL_checkunsigned(L, 2);
        // if (data && player->GetGuild())
        // player->GetGuild()->BroadcastPacketToRank(data, ranked);
        return 0;
    }

    int SendVendorWindow(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Unit* sendTo = sEluna.CHECK_UNIT(L, 1);
        if (!sendTo)
            return 0;
        player->GetSession()->SendListInventory(sendTo->GetObjectGuid());
        return 0;
    }

    int KickPlayer(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->GetSession()->KickPlayer();
        return 0;
    }

    int ModifyMoney(lua_State* L, Unit* unit)
    {
        TO_PLAYER_BOOL();

        int32 amt = luaL_checkinteger(L, 1);

        player->ModifyMoney(amt); // MaNGOS does not support a bool being sent with an error value like Trinity
        return 1;
    }

    int LearnSpell(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 id = luaL_checkunsigned(L, 1);
        player->learnSpell(id, false);
        return 0;
    }

    int DeMorph(lua_State* L, Unit* unit)
    {
        unit->DeMorph();
        return 0;
    }

    int ResurrectPlayer(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        float percent = luaL_optnumber(L, 1, 100.0f);
        bool sickness = luaL_optbool(L, 2, false);
        player->ResurrectPlayer(percent, sickness);
        player->SpawnCorpseBones();
        return 0;
    }

    int CastSpell(lua_State* L, Unit* unit)
    {
        Unit* target = sEluna.CHECK_UNIT(L, 1);
        if (!target)
            return 0;
        uint32 spell = luaL_checkunsigned(L, 2);
        SpellEntry const* spellEntry = sSpellStore.LookupEntry(spell);
        if (!spellEntry)
            return 0;
        bool triggered = luaL_optbool(L, 3, true);

        unit->CastSpell(target, spellEntry, triggered);
        return 0;
    }

    int CastSpellAoF(lua_State* L, Unit* unit)
    {
        float _x = luaL_checknumber(L, 1);
        float _y = luaL_checknumber(L, 2);
        float _z = luaL_checknumber(L, 3);
        uint32 spell = luaL_checkunsigned(L, 4);
        bool triggered = luaL_optbool(L, 5, true);
        unit->CastSpell(_x, _y, _z, spell, triggered);
        return 0;
    }

    int GetAccountId(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetSession()->GetAccountId());
        return 1;
    }

    int GetAccountName(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        std::string accName;
        if (sAccountMgr.GetName(player->GetSession()->GetAccountId(), accName))
            sEluna.Push(L, accName);
        else
            return 0;
        return 1;
    }

    int GetCorpse(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetCorpse());
        return 1;
    }

    int GetAITarget(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        /*SelectAggroTarget targetType = (SelectAggroTarget)luaL_checkunsigned(L, 1);
        bool playerOnly = luaL_optbool(L, 2, false);
        uint32 position = luaL_optunsigned(L, 3, 0);
        float dist = luaL_optnumber(L, 4, 0.0f);
        int32 aura = luaL_optint(L, 5, 0);

        ;
        ThreatContainer::StorageType const& threatlist = creature->getThreatManager().getThreatList();
        if (position >= threatlist.size())
        {
        sEluna.Push(L, NULL);
        return 1;
        }

        std::list<Unit*> targetList;
        for (ThreatContainer::StorageType::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
        {
        Unit* target = (*itr)->getTarget();
        if (!target)
        continue;
        if (playerOnly && !target->ToPlayer())
        continue;
        if (aura > 0 && !target->HasAura(aura))
        continue;
        else if (aura < 0 && target->HasAura(-aura))
        continue;
        if (dist > 0.0f && !creature->IsWithinDist(target, dist))
        continue;
        targetList.push_back(target);
        }

        if (position >= targetList.size())
        {
        sEluna.Push(L, NULL);
        return 1;
        }

        if (targetType == SELECT_TARGET_NEAREST || targetType == SELECT_TARGET_FARTHEST)
        targetList.sort(Trinity::ObjectDistanceOrderPred(creature));

        switch (targetType)
        {
        case SELECT_TARGET_NEAREST:
        case SELECT_TARGET_TOPAGGRO:
        {
        std::list<Unit*>::const_iterator itr = targetList.begin();
        std::advance(itr, position);
        sEluna.Push(L, *itr);
        return 1;
        }
        case SELECT_TARGET_FARTHEST:
        case SELECT_TARGET_BOTTOMAGGRO:
        {
        std::list<Unit*>::reverse_iterator ritr = targetList.rbegin();
        std::advance(ritr, position);
        sEluna.Push(L, *ritr);
        return 1;
        }
        case SELECT_TARGET_RANDOM:
        {
        std::list<Unit*>::const_iterator itr = targetList.begin();
        std::advance(itr, urand(position, targetList.size() - 1));
        sEluna.Push(L, *itr);
        return 1;
        }
        default:
        break;
        }*/

        sEluna.Push(L, NULL);
        return 1;
    }

    int GetAITargets(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        /*ThreatContainer::StorageType const &threatList = creature->getThreatManager().getThreatList();
        ThreatContainer::StorageType::const_iterator itr;
        for (itr = threatList.begin(); itr != threatList.end(); ++itr)
        {
        Unit* target = (*itr)->getTarget();
        if (!target)
        continue;
        ++i;
        sEluna.Push(L, i);
        sEluna.Push(L, target);
        lua_settable(L, tbl);
        }

        lua_settop(L, tbl);*/
        return 1;
    }

    int GetAITargetsCount(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->getThreatManager().getThreatList().size());
        return 1;
    }

    int IsDungeonBoss(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        // sEluna.Push(L, creature->IsDungeonBoss());
        return 1;
    }

    int IsWorldBoss(lua_State* L, Unit* unit)
    {
        TO_CREATURE_BOOL();

        sEluna.Push(L, creature->IsWorldBoss());
        return 1;
    }

    int GetAura(lua_State* L, Unit* unit)
    {
        uint32 spellID = luaL_checkunsigned(L, 1);
        // sEluna.Push(L, unit->GetAura(spellID));
        return 1;
    }

    int GetCombatTime(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->GetCombatTimer());
        return 1;
    }

    int ClearInCombat(lua_State* L, Unit* unit)
    {
        unit->ClearInCombat();
        return 0;
    }

    int StopSpellCast(lua_State* L, Unit* unit)
    {
        uint32 spellId = luaL_optunsigned(L, 1, 0);
        unit->CastStop(spellId);
        return 0;
    }

    int InterruptSpell(lua_State* L, Unit* unit)
    {
        int spellType = luaL_checkint(L, 1);
        bool delayed = luaL_optbool(L, 2, true);
        bool instant = luaL_optbool(L, 3, true);
        switch (spellType)
        {
        case 0:
            spellType = CURRENT_MELEE_SPELL;
            break;
        case 1:
            spellType = CURRENT_GENERIC_SPELL;
            break;
        case 2:
            spellType = CURRENT_CHANNELED_SPELL;
            break;
        case 3:
            spellType = CURRENT_AUTOREPEAT_SPELL;
            break;
        }
        unit->InterruptSpell((CurrentSpellTypes)spellType, delayed, instant);
        return 0;
    }

    int AddAura(lua_State* L, Unit* unit)
    {
        uint32 spellId = luaL_checkunsigned(L, 1);
        Unit* target = sEluna.CHECK_UNIT(L, 2);
        if (!target)
            return 0;
        // sEluna.Push(L, unit->AddAura(spellId, target));
        return 1;
    }

    int RemoveAura(lua_State* L, Unit* unit)
    {
        uint32 spellId = luaL_checkunsigned(L, 1);
        unit->RemoveAurasDueToSpell(spellId);
        return 0;
    }

    int RemoveAllAuras(lua_State* L, Unit* unit)
    {
        unit->RemoveAllAuras();
        return 0;
    }

    int GossipMenuAddItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 _icon = luaL_checkunsigned(L, 1);
        const char* msg = luaL_checkstring(L, 2);
        uint32 _sender = luaL_checkunsigned(L, 3);
        uint32 _intid = luaL_checkunsigned(L, 4);
        bool _code = luaL_optbool(L, 5, false);
        const char* _promptMsg = luaL_optstring(L, 6, "");
        uint32 _money = luaL_optunsigned(L, 7, 0);
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(_icon, msg, _sender, _intid, _promptMsg, _money, _code);
        return 0;
    }

    int GossipComplete(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->PlayerTalkClass->CloseGossip();
        return 0;
    }

    int GossipSendMenu(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 _npcText = luaL_checkunsigned(L, 1);
        WorldObject* sender = sEluna.CHECK_WORLDOBJECT(L, 2);
        if (sender)
        {
            if (sender->ToPlayer())
            {
                uint32 menu_id = luaL_checkunsigned(L, 3);
                player->PlayerTalkClass->GetGossipMenu().SetMenuId(menu_id);
            }
            player->PlayerTalkClass->SendGossipMenu(_npcText, sender->GetObjectGuid());
        }
        return 0;
    }

    int GossipClearMenu(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->PlayerTalkClass->ClearMenus();
        return 0;
    }

    int PlaySoundToPlayer(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 soundId = luaL_checkunsigned(L, 1);
        SoundEntriesEntry const* soundEntry = sSoundEntriesStore.LookupEntry(soundId);
        if (!soundEntry)
            return 0;

        player->PlayDirectSound(soundId, player);
        return 0;
    }

    int PlayDirectSound(lua_State* L, Unit* unit)
    {
        uint32 soundId = luaL_checkunsigned(L, 1);
        Player* player = sEluna.CHECK_PLAYER(L, 2);
        if (!sSoundEntriesStore.LookupEntry(soundId))
            return 0;

        if (player)
            unit->PlayDirectSound(soundId, player);
        else
            unit->PlayDirectSound(soundId);
        return 0;
    }

    int PlayDistanceSound(lua_State* L, Unit* unit)
    {
        uint32 soundId = luaL_checkunsigned(L, 1);
        Player* player = sEluna.CHECK_PLAYER(L, 2);
        if (!sSoundEntriesStore.LookupEntry(soundId))
            return 0;

        if (player)
            unit->PlayDistanceSound(soundId, player);
        else
            unit->PlayDistanceSound(soundId);
        return 0;
    }

    int Kill(lua_State* L, Unit* unit)
    {
        Unit* target = sEluna.CHECK_UNIT(L, 1);
        bool durLoss = luaL_optbool(L, 2, true);
        // unit->Kill((target ? target : unit), durLoss);
        return 0;
    }

    int RegisterEvent(lua_State* L, Unit* unit)
    {
        luaL_checktype(L, 1, LUA_TFUNCTION);
        uint32 delay = luaL_checkunsigned(L, 2);
        uint32 repeats = luaL_checkunsigned(L, 3);

        lua_settop(L, 1);
        int functionRef = lua_ref(L, true);
        unit->m_Events.AddEvent(new Eluna::LuaEventData(functionRef, delay, repeats, unit), unit->m_Events.CalculateTime(delay));
        sEluna.Push(L, functionRef);
        return 1;
    }

    int RemoveEventById(lua_State* L, Unit* unit)
    {
        int eventID = luaL_checkinteger(L, 1);
        Eluna::LuaEventData::Remove(unit->GetGUIDLow(), eventID);
        return 0;
    }

    int RemoveEvents(lua_State* L, Unit* unit)
    {
        Eluna::LuaEventData::RemoveAll(unit);
        return 0;
    }

    /* Vehicle */

    int IsOnVehicle(lua_State* L, Unit* unit)
    {
        /*if (unit->GetVehicleInfo() || (unit->ToPlayer() && unit->IsVehicle()))
            sEluna.Push(L, true);
        else
            sEluna.Push(L, false);*/
        return 1;
    }

    int DismissVehicle(lua_State* L, Unit* unit)
    {
        // if (Creature* vehicle = unit->GetVehicleCreatureBase())
        // vehicle->DespawnOrUnsummon();
        return 0;
    }

    int AddVehiclePassenger(lua_State* L, Unit* unit)
    {
        Unit* passenger = sEluna.CHECK_UNIT(L, 1);
        int8 seatId = luaL_checkunsigned(L, 2);
        // Vehicle* _vehicle = unit->GetVehicle();
        // if (!_vehicle)
        // return 0;

        //_vehicle->AddPassenger(passenger, seatId);
        return 0;
    }

    /* Not coded in core
    int EjectPassenger(lua_State* L, Unit* unit)
    {
    TO_UNIT();

    Unit* passenger = sEluna.CHECK_UNIT(L, 1);
    Vehicle* _vehicle = unit->GetVehicle();
    if (!_vehicle)
    return 0;

    _vehicle->EjectPassenger(passenger, unit);
    return 0;
    }
    */

    int RemovePassenger(lua_State* L, Unit* unit)
    {
        Unit* passenger = sEluna.CHECK_UNIT(L, 1);
        // Vehicle* _vehicle = unit->GetVehicle();
        // if (!_vehicle)
        // return 0;

        //_vehicle->RemovePassenger(passenger);
        return 0;
    }

    int RemoveAllPassengers(lua_State* L, Unit* unit)
    {
        // Unit* _unit = unit->GetVehicleBase();
        // if (!_unit)
        // return 0;

        //_unit->GetVehicle()->RemoveAllPassengers();
        return 0;
    }

    int GetPassenger(lua_State* L, Unit* unit)
    {
        int8 seatId = luaL_checkunsigned(L, 1);
        // Unit* _unit = unit->GetVehicleBase();
        // if (!_unit)
        // return 0;

        // sEluna.Push(L, _unit->GetVehicle()->GetPassenger(seatId));
        return 1;
    }

    int GetNextEmptySeat(lua_State* L, Unit* unit)
    {
        int8 seatId = luaL_checkunsigned(L, 1);
        // Unit* _unit = unit->GetVehicleBase();
        // if (!_unit)
        // return 0;

        return 0;
    }

    int GetAvailableSeats(lua_State* L, Unit* unit)
    {
        // Unit* _unit = unit->GetVehicleBase();
        // if (!_unit)
        // return 0;

        // sEluna.Push(L, _unit->GetVehicle()->GetAvailableSeatCount());
        return 1;
    }

    int GetVehicleBase(lua_State* L, Unit* unit)
    {
        // Unit* _unit = unit->GetVehicleBase();
        // if (_unit)
        // sEluna.Push(L, _unit);
        // else
        // lua_pushnil(L);
        return 1;
    }

    int HasEmptySeat(lua_State* L, Unit* unit)
    {
        int8 seatId = luaL_checkunsigned(L, 1);
        // Unit* _unit = unit->GetVehicleBase();
        // if (!_unit)
        // return 0;

        // sEluna.Push(L, _unit->GetVehicle()->HasEmptySeat(seatId));
        return 1;
    }

    int StartTaxi(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 pathId = luaL_checkunsigned(L, 1);

        LuaTaxiMgr::StartTaxi(player, pathId);
        return 0;
    }

    int SetPlayerLock(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        bool apply = luaL_optbool(L, 1, true);

        if (apply)
        {
            player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED | UNIT_FLAG_SILENCED);
            player->SetClientControl(player, 0);
        }
        else
        {
            player->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED | UNIT_FLAG_SILENCED);
            player->SetClientControl(player, 1);
        }
        return 0;
    }

    int GetFriendlyUnitsInRange(lua_State* L, Unit* unit)
    {
        float range = luaL_optnumber(L, 1, SIZE_OF_GRIDS);

        /*UnitList list;
        Trinity::AnyFriendlyUnitInObjectRangeCheck checker(unit, unit, range);
        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(unit, list, checker);
        unit->VisitNearbyObject(range, searcher);
        Trinity::ObjectGUIDCheck guidCheck(unit->GetGUID());
        list.remove_if (guidCheck);

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (UnitList::const_iterator it = list.begin(); it != list.end(); ++it)
        {
        sEluna.Push(L, ++i);
        sEluna.Push(L, *it);
        lua_settable(L, tbl);
        }

        lua_settop(L, tbl);*/
        return 1;
    }

    int GetUnfriendlyUnitsInRange(lua_State* L, Unit* unit)
    {
        float range = luaL_optnumber(L, 1, SIZE_OF_GRIDS);

        /*UnitList list;
        Trinity::AnyUnfriendlyUnitInObjectRangeCheck checker(unit, unit, range);
        Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(unit, list, checker);
        unit->VisitNearbyObject(range, searcher);
        Trinity::ObjectGUIDCheck guidCheck(unit->GetGUID());
        list.remove_if (guidCheck);

        lua_newtable(L);
        int tbl = lua_gettop(L);
        uint32 i = 0;

        for (UnitList::const_iterator it = list.begin(); it != list.end(); ++it)
        {
        sEluna.Push(L, ++i);
        sEluna.Push(L, *it);
        lua_settable(L, tbl);
        }

        lua_settop(L, tbl);*/
        return 1;
    }

    int GossipSendPOI(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        uint32 icon = luaL_checkunsigned(L, 3);
        uint32 flags = luaL_checkunsigned(L, 4);
        uint32 data = luaL_checkunsigned(L, 5);
        std::string iconText = luaL_checkstring(L, 6);

        WorldPacket packet(SMSG_GOSSIP_POI, 4 + 4 + 4 + 4 + 4 + 10);
        packet << flags;
        packet << x;
        packet << y;
        packet << icon;
        packet << data;
        packet << iconText;
        player->GetSession()->SendPacket(&packet);
        return 0;
    }

    int GossipAddQuests(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        WorldObject* source = sEluna.CHECK_WORLDOBJECT(L, 1);
        if (!source)
            return 0;

        if (source->GetTypeId() == TYPEID_UNIT)
        {
            if (source->GetUInt32Value(UNIT_NPC_FLAGS) & UNIT_NPC_FLAG_QUESTGIVER)
                player->PrepareQuestMenu(source->GetObjectGuid());
        }
        else if (source->GetTypeId() == TYPEID_GAMEOBJECT)
        {
            if (source->ToGameObject()->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
                player->PrepareQuestMenu(source->GetObjectGuid());
        }
        return 0;
    }

    int AttackStop(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->AttackStop());
        return 1;
    }

    int SetCanFly(lua_State* L, Unit* unit)
    {
        bool apply = luaL_optbool(L, 1, true);
        // unit->SetCanFly(apply);
        return 0;
    }

    int SetVisible(lua_State* L, Unit* unit)
    {
        bool x = luaL_optbool(L, 1, true);
        // unit->SetVisible(x);
        return 0;
    }

    int IsVisible(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->IsVisible());
        return 1;
    }

    int IsMoving(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->isMoving());
        return 1;
    }

    int IsFlying(lua_State* L, Unit* unit)
    {
        // sEluna.Push(L, unit->IsFlying());
        return 1;
    }

    int IsStopped(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->IsStopped());
        return 1;
    }

    int IsQuestGiver(lua_State* L, Unit* unit)
    {
        sEluna.Push(L, unit->isQuestGiver());
        return 1;
    }

    int RestoreDisplayId(lua_State* L, Unit* unit)
    {
        // unit->RestoreDisplayId();
        return 0;
    }

    int RestoreFaction(lua_State* L, Unit* unit)
    {
        // unit->RestoreFaction();
        return 0;
    }

    int RemoveBindSightAuras(lua_State* L, Unit* unit)
    {
        // unit->RemoveBindSightAuras();
        return 0;
    }

    int RemoveCharmAuras(lua_State* L, Unit* unit)
    {
        // unit->RemoveCharmAuras();
        return 0;
    }

    int StopMoving(lua_State* L, Unit* unit)
    {
        unit->StopMoving();
        return 0;
    }

    int AddUnitState(lua_State* L, Unit* unit)
    {
        uint32 state = luaL_checkunsigned(L, 1);

        unit->addUnitState(state);
        return 0;
    }

    int ClearUnitState(lua_State* L, Unit* unit)
    {
        uint32 state = luaL_checkunsigned(L, 1);

        unit->clearUnitState(state);
        return 0;
    }

    int HasUnitState(lua_State* L, Unit* unit)
    {
        uint32 state = luaL_checkunsigned(L, 1);

        sEluna.Push(L, unit->hasUnitState(state));
        return 1;
    }

    int DisableMelee(lua_State* L, Unit* unit)
    {
        bool apply = luaL_optbool(L, 1, true);

        /*if (apply)
        unit->AddUnitState(UNIT_STATE_CANNOT_AUTOATTACK);
        else
        unit->ClearUnitState(UNIT_STATE_CANNOT_AUTOATTACK);*/
        return 0;
    }

    int SummonGuardian(lua_State* L, Unit* unit)
    {
        uint32 entry = luaL_checkunsigned(L, 1);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        float z = luaL_checknumber(L, 4);
        float o = luaL_checknumber(L, 5);
        uint32 desp = luaL_optunsigned(L, 6, 0);

        SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(61);
        if (!properties)
            return 0;
        Position pos;
        /*pos.Relocate(x,y,z,o);
        TempSummon* summon = unit->GetMap()->SummonCreature(entry, pos, properties, desp, unit);

        if (!summon)
        return 0;
        if (summon->HasUnitTypeMask(UNIT_MASK_GUARDIAN))
        ((Guardian*)summon)->InitStatsForLevel(unit->getLevel());
        if (properties && properties->Category == SUMMON_CATEGORY_ALLY)
        summon->setFaction(unit->getFaction());
        if (summon->GetEntry() == 27893)
        {
        if (uint32 weapon = unit->GetUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID))
        {
        summon->SetDisplayId(11686);
        summon->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, weapon);
        }
        else
        summon->SetDisplayId(1126);
        }
        summon->AI()->EnterEvadeMode();

        sEluna.Push(L, summon);*/
        return 1;
    }

    int SendQuestTemplate(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        uint32 questId = luaL_checkunsigned(L, 1);
        bool activeAccept = luaL_optbool(L, 2, true);

        Quest const* quest = sObjectMgr.GetQuestTemplate(questId);
        if (!quest)
            return 0;

        player->PlayerTalkClass->SendQuestGiverQuestDetails(quest, player->GetObjectGuid(), activeAccept);
        return 0;
    }

    int SpawnBones(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        player->SpawnCorpseBones();
        return 0;
    }

    int RemovedInsignia(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Player* looter = sEluna.CHECK_PLAYER(L, 1);
        if (!looter)
            return 0;
        player->RemovedInsignia(looter);
        return 0;
    }

    int GetNPCFlags(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        sEluna.Push(L, creature->GetUInt32Value(UNIT_NPC_FLAGS));
        return 1;
    }

    int SetNPCFlags(lua_State* L, Unit* unit)
    {
        TO_CREATURE();

        uint32 flags = luaL_checkunsigned(L, 1);

        creature->SetUInt32Value(UNIT_NPC_FLAGS, flags);
        return 0;
    }

    int GetDbLocaleIndex(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetSession()->GetSessionDbLocaleIndex());
        return 1;
    }

    int GetDbcLocale(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        sEluna.Push(L, player->GetSession()->GetSessionDbcLocale());
        return 1;
    }

    int CanUseItem(lua_State* L, Unit* unit)
    {
        TO_PLAYER();

        Item* item = sEluna.CHECK_ITEM(L, 1);
        if (item)
            sEluna.Push(L, player->CanUseItem(item));
        else
        {
            uint32 entry = luaL_checkunsigned(L, 1);
            const ItemPrototype* temp = sObjectMgr.GetItemPrototype(entry);
            if (temp)
                sEluna.Push(L, player->CanUseItem(temp));
            else
                sEluna.Push(L, EQUIP_ERR_ITEM_NOT_FOUND);
        }
        return 1;
    }

    int FindNearestGameObject(lua_State* L, Unit* unit)
    {
        uint32 entry = luaL_checkunsigned(L, 1);
        float range = luaL_checknumber(L, 2);

        // sEluna.Push(L, unit->FindNearestGameObject(entry, range));
        return 1;
    }

    int FindNearestCreature(lua_State* L, Unit* unit)
    {
        uint32 entry = luaL_checkunsigned(L, 1);
        float range = luaL_checknumber(L, 2);
        bool alive = luaL_optbool(L, 3, true);

        // sEluna.Push(L, unit->FindNearestCreature(entry, range, alive));
        return 1;
    }
};
#endif
