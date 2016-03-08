#include "Mail.h"
#include "precompiled.h"
#include "PlayerStartMgr.h"
#include "SpellMgr.h"

enum
{
    NPC_TEXT_LEVELUP_ALREADY_DONE   = 19997,
    NPC_TEXT_LEVELUP_OK             = 19998,
    NPC_TEXT_LEVELUP_RULES          = 19999,
};

enum
{
    NPC_WELCOME_GIVEN_LEVEL         = 60,
};

/*######
## npc_welcome
######*/

bool GossipHello_npc_welcome(Player *player, Creature *_Creature)
{
    if (player->getLevel() >= NPC_WELCOME_GIVEN_LEVEL)
    {
        player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_ALREADY_DONE, _Creature->GetObjectGuid());
        return true;
    }
    player->ADD_GOSSIP_ITEM(0, "I understand these rules and I will respect them.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_RULES, _Creature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_welcome(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if (sender != GOSSIP_SENDER_MAIN)
        return false;
    if (player->getLevel() >= NPC_WELCOME_GIVEN_LEVEL)
    {
        player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_ALREADY_DONE, _Creature->GetObjectGuid());
        return true;
    }

    sPlayerStartMgr.AddSpells(player);
    sPlayerStartMgr.AddItems(player);

    player->CastSpell(player, MOUNT_SPELL, false);
    for (int i = 0; i < 4; ++i)
        player->StoreNewItemInBestSlots(BAG_ADD_ID, 1);

    player->GiveLevel(NPC_WELCOME_GIVEN_LEVEL);

    player->UpdateSkillsToMaxSkillsForLevel();

    // Add fly paths
    if (player->GetTeam() == ALLIANCE)
        player->m_taxi.LoadTaxiMask("3456411898 2148078928 49991 0 0 0 0 0 ");
    else
        player->m_taxi.LoadTaxiMask("561714688 282102432 52408 0 0 0 0 0 ");

    // Give AV reputation
    if (player->GetTeam() == ALLIANCE)
        player->GetReputationMgr().SetReputation(sFactionStore.LookupEntry(730), 21000);
    else
        player->GetReputationMgr().SetReputation(sFactionStore.LookupEntry(729), 21000);

    // Set honor rank rank
    //player->SetStoredHonor(45000);
    //player->UpdateHonor();
    player->ModifyMoney(9000000);

    player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_OK, _Creature->GetObjectGuid());
    return true;
}

void AddSC_npc_welcome()
{
    sPlayerStartMgr.load();
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_welcome";
    newscript->pGossipHello   = &GossipHello_npc_welcome;
    newscript->pGossipSelect  = &GossipSelect_npc_welcome;
    newscript->RegisterSelf();
}
