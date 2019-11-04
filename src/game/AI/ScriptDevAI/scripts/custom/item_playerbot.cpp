/**
 *
 * @File : item_dungeon.cpp
 * @Authors : yukozh
 * @Date : 10/06/2019
 *
 **/

#ifdef BUILD_PLAYERBOT
#include "item_playerbot.h"
#include "Pomelo/DBConfigMgr.h"
#include "Pomelo/MultiTalentMgr.h"
#include "Pomelo/CustomCurrencyMgr.h"
#include "AI/ScriptDevAI/include/sc_gossip.h"
#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"
#include "PlayerBot/Base/PlayerbotAI.h"

#define INCREASE_SOLDIER_CAPACITY_ITEM_VENDOR_ID 80034

std::unordered_map<uint32, std::vector<AccountCharacter>> m_accountCharactersMap;

size_t CountHiredCharacters(uint32 account)
{
    size_t count = 0;
    for (size_t i = 0; i < m_accountCharactersMap[account].size(); ++i)
        if (m_accountCharactersMap[account][i].hired)
            ++count;
    return count;
}

void LoadAndCachePlayerBotCharacters(Player* pPlayer)
{
    uint32 account = pPlayer->GetSession()->GetAccountId();
    if (m_accountCharactersMap.find(account) == m_accountCharactersMap.end())
    {
        QueryResult* result = CharacterDatabase.PQuery(
            "SELECT guid, name, race FROM characters "
            "WHERE account = %u", account);
        
        if (result)
        {
            do
            {
                Field* field = result->Fetch();
                AccountCharacter item;
                item.guid = field[0].GetUInt32();
                if (pPlayer->GetGUIDLow() == item.guid) continue;
                item.name = field[1].GetCppString();
                item.race = field[2].GetUInt8();
                item.hired = false;
                m_accountCharactersMap[account].push_back(item);
            } while (result->NextRow());
        }

        delete result;
    }
}

void RemovePlayerBotCachedCharacters(Player* pPlayer)
{
    uint32 account = pPlayer->GetSession()->GetAccountId();
    m_accountCharactersMap.erase(account);
}

void GeneratePlayerBotGossipMenu(Player* pPlayer, ObjectGuid guid)
{
    // Load characters if not cached
    LoadAndCachePlayerBotCharacters(pPlayer);
    uint32 account = pPlayer->GetSession()->GetAccountId();
    pPlayer->PlayerTalkClass->ClearMenus();
    std::string charlist = std::string(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_CHARLIST));
    charlist.append(" (");
    charlist.append(std::to_string(CountHiredCharacters(account)));
    charlist.append("/");
    charlist.append(std::to_string(pPlayer->GetMaxSoldier()));
    charlist.append(")");
    pPlayer->ADD_GOSSIP_ITEM(0, charlist.c_str(), 80009, 0);
    pPlayer->ADD_GOSSIP_ITEM(0, pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_CHARJOB), 80011, 0);
    pPlayer->ADD_GOSSIP_ITEM(0, pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_RECRUIT), 80016, 0);
    pPlayer->SEND_GOSSIP_MENU(100000 - 1021, guid);
}

bool HandlePlayerBotGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action)
{
	if (sender < 80009 || sender > 80016) return false;

    uint32 account = pPlayer->GetSession()->GetAccountId();
    if (action >= m_accountCharactersMap[account].size())
    {
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_PLAYERBOT_NO_CHARACTER);
        pPlayer->PlayerTalkClass->CloseGossip();
        return true;
    }

    // create the playerbot manager if it doesn't already exist
    PlayerbotMgr* mgr = pPlayer->GetPlayerbotMgr();
    if (!mgr)
    {
        mgr = new PlayerbotMgr(pPlayer);
        pPlayer->SetPlayerbotMgr(mgr);
    }

    if (sender == 80009)
    {
        // Clear menu
        pPlayer->PlayerTalkClass->ClearMenus();

        for (uint8 i = 0; i < m_accountCharactersMap[account].size(); ++i)
        {
            auto str = std::string("");
            if (m_accountCharactersMap[account][i].hired)
            {
                str.append(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_RECALL));
            }
            else
            {
                str.append(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_SUMMON));
            }

            str.append(m_accountCharactersMap[account][i].name);

            pPlayer->ADD_GOSSIP_ITEM(0, str.c_str(), 80010, i);
        }
        pPlayer->SEND_GOSSIP_MENU(100000 - 1020, pObj->GetObjectGuid());
        return true;
    }
    else if (sender == 80010)
    {
        AccountCharacter &charr = m_accountCharactersMap[account][action];
        ObjectGuid guid = ObjectGuid(HIGHGUID_PLAYER, charr.guid);

        if (mgr->GetPlayerBot(guid))
        {
            ChatHandler(pPlayer).PSendSysMessage(
                LANG_PLAYERBOT_RECALL_TIP,
                charr.name.c_str());
            mgr->LogoutPlayerBot(guid);
            CharacterDatabase.DirectPExecute("UPDATE characters SET online = 0 WHERE guid = '%u'", guid.GetCounter());
            charr.hired = false;
        }
        else
        {
            if (CountHiredCharacters(account) >= pPlayer->GetMaxSoldier())
            {
                ChatHandler(pPlayer).PSendSysMessage(
                    LANG_PLAYERBOT_HIRE_EXCEED,
                    pPlayer->GetMaxSoldier());

                pPlayer->PlayerTalkClass->CloseGossip();
                return true;
            }

            // Opposing team bot
            Team team = Player::TeamForRace(charr.race);
            if (!sWorld.getConfig(CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_GROUP) && pPlayer->GetTeam() != team)
            {
                ChatHandler(pPlayer).PSendSysMessage(
                    LANG_PLAYERBOT_2SIDE_TEAMING_ERR,
                    charr.name.c_str());
            }
            else
            {
                ChatHandler(pPlayer).PSendSysMessage(
                    LANG_PLAYERBOT_SUMMON_TIP,
                    charr.name.c_str());
                mgr->LoginPlayerBot(guid);
                CharacterDatabase.DirectPExecute("UPDATE characters SET online = 1 WHERE guid = '%u'", guid.GetCounter());
                charr.hired = true;
            }
        }
    }
    else if (sender == 80011)
    {
        // Clear menu
        pPlayer->PlayerTalkClass->ClearMenus();

        for (uint8 i = 0; i < m_accountCharactersMap[account].size(); ++i)
        {
            auto str = std::string("");
            if (!m_accountCharactersMap[account][i].hired)
            {
                continue;
            }
            str.append(m_accountCharactersMap[account][i].name);
            str.append(" - ");
            if (m_accountCharactersMap[account][i].job == JOB_TANK)
            {
                str.append(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_TANK));
            }
            else if (m_accountCharactersMap[account][i].job == JOB_DPS)
            {
                str.append(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_DPS));
            }
            else if (m_accountCharactersMap[account][i].job == JOB_HEAL)
            {
                str.append(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_HEAL));
            }
            else
            {
                str.append(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_UNSPECIFIED));
            }
            pPlayer->ADD_GOSSIP_ITEM(0, str.c_str(), 80012, i);
        }
        pPlayer->SEND_GOSSIP_MENU(100000 - 1020, pObj->GetObjectGuid());
        return true;
    }
    else if (sender == 80012)
    {
        AccountCharacter& charr = m_accountCharactersMap[account][action];
        pPlayer->PlayerTalkClass->ClearMenus();
        std::string menu1 = std::string(charr.name);
        std::string menu2 = std::string(charr.name);
        std::string menu3 = std::string(charr.name);
        menu1.append(" => ");
        menu2.append(" => ");
        menu3.append(" => ");
        menu1.append(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_TANK));
        menu2.append(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_DPS));
        menu3.append(pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_HEAL));
        pPlayer->ADD_GOSSIP_ITEM(0, menu1.c_str(), 80013, action);
        pPlayer->ADD_GOSSIP_ITEM(0, menu2.c_str(), 80014, action);
        pPlayer->ADD_GOSSIP_ITEM(0, menu3.c_str(), 80015, action);
        pPlayer->SEND_GOSSIP_MENU(100000 - 1021, pObj->GetObjectGuid());
        return true;
    }
    else if (sender == 80013)
    {
        AccountCharacter& charr = m_accountCharactersMap[account][action];
        ObjectGuid guid = ObjectGuid(HIGHGUID_PLAYER, charr.guid);
        if (Player * bot = mgr->GetPlayerBot(guid))
        {
            auto AI = bot->GetPlayerbotAI();
            if (AI)
            {
                ChatHandler(pPlayer).PSendSysMessage(
                    LANG_PLAYERBOT_ASSIGNED_JOB,
                    charr.name.c_str(),
                    pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_TANK));
                AI->SetCombatOrder(PlayerbotAI::ORDERS_TANK);
                charr.job = JOB_TANK;
            }
        }
    }
    else if (sender == 80014)
    {
        AccountCharacter& charr = m_accountCharactersMap[account][action];
        ObjectGuid guid = ObjectGuid(HIGHGUID_PLAYER, charr.guid);
        if (Player * bot = mgr->GetPlayerBot(guid))
        {
            auto AI = bot->GetPlayerbotAI();
            if (AI)
            {
                ChatHandler(pPlayer).PSendSysMessage(
                    LANG_PLAYERBOT_ASSIGNED_JOB,
                    charr.name.c_str(),
                    pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_DPS));
                AI->SetCombatOrder(PlayerbotAI::ORDERS_NONE);
                charr.job = JOB_DPS;
            }
        }
    }
    else if (sender == 80015)
    {
        AccountCharacter& charr = m_accountCharactersMap[account][action];
        ObjectGuid guid = ObjectGuid(HIGHGUID_PLAYER, charr.guid);
        if (Player * bot = mgr->GetPlayerBot(guid))
        {
            ChatHandler(pPlayer).PSendSysMessage(
                LANG_PLAYERBOT_ASSIGNED_JOB,
                charr.name.c_str(),
                pPlayer->GetSession()->GetMangosString(LANG_PLAYERBOT_JOB_HEAL));
            auto AI = bot->GetPlayerbotAI();
            if (AI)
            {
                AI->SetCombatOrder(PlayerbotAI::ORDERS_HEAL);
                charr.job = JOB_HEAL;
            }
        }
    }
    else if (sender == 80016)
    {
        Creature* pStoreNpc;
        pStoreNpc = pPlayer->SummonCreature(INCREASE_SOLDIER_CAPACITY_ITEM_VENDOR_ID, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0.0f, TEMPSPAWN_TIMED_OOC_DESPAWN, 60000);
        pPlayer->GetSession()->SendListInventory(pStoreNpc->GetObjectGuid());
     }

	pPlayer->PlayerTalkClass->CloseGossip();
    return true;
}
#endif