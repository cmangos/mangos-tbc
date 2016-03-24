#include "Mail.h"
#include "precompiled.h"
#include "PlayerStartMgr.h"
#include "SpellMgr.h"

enum Texts
{
    NPC_TEXT_LEVELUP_ALREADY_DONE   = 19997,
    NPC_TEXT_LEVELUP_OK             = 19998,
    NPC_TEXT_LEVELUP_RULES          = 19999,
    NPC_TEXT_TELEPORT_GOSSIP        = 20000,
    NPC_TEXT_LEVELUP_SUB            = 20001,
    NPC_TEXT_LEVELUP_MAX_PROF       = 20002,
};

enum Levels
{
    NPC_WELCOME_GIVEN_LEVEL_60         = 60,
    NPC_WELCOME_GIVEN_LEVEL_65         = 65,
    NPC_WELCOME_GIVEN_LEVEL_70         = 70
};

// helpers
void LearnAllRecipes(Player* player, uint32 skillEntry)
{
    SkillLineEntry const* skillInfo = sSkillLineStore.LookupEntry(skillEntry);
    if (!skillInfo)
        return;

    uint32 classmask = player->getClassMask();

    for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
    {
        SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
        if (!skillLine)
            continue;

        // wrong skill
        if (skillLine->skillId != skillEntry)
            continue;

        // not high rank
        if (skillLine->forward_spellid)
            continue;

        // skip racial skills
        if (skillLine->racemask != 0)
            continue;

        // skip wrong class skills
        if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
            continue;

        SpellEntry const* spellInfo = sSpellStore.LookupEntry(skillLine->spellId);
        if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
            continue;

        player->learnSpell(skillLine->spellId, false);
    }

    uint16 maxLevel = player->GetPureMaxSkillValue(skillInfo->id);
    player->SetSkill(skillInfo->id, maxLevel, maxLevel);
}

/*######
## npc_welcome
######*/

bool GossipHello_npc_welcome(Player *player, Creature *_Creature)
{
    // max level reached - offer professions
    if (player->getLevel() >= NPC_WELCOME_GIVEN_LEVEL_70)
    {
        if (player->GetFreePrimaryProfessionPoints())
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alchemy", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Blacksmithing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enchanting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Engineering", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Jewelcrafting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Leatherworking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tailroing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Herbalism", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mining", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Skinning", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "First Aid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Cooking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Fishing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
            player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_ALREADY_DONE, _Creature->GetObjectGuid());
            return true;
        }

        player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_MAX_PROF, _Creature->GetObjectGuid());
        return true;
    }

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I understand these rules and I will respect them.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_RULES, _Creature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_welcome(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if (sender != GOSSIP_SENDER_MAIN)
        return false;

    if (action == GOSSIP_ACTION_INFO_DEF + 1)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Level up 60.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Level up 65.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Level up 70.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
        player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_SUB, _Creature->GetObjectGuid());
        return true;
    }

    uint32 level = 0;
    switch (action)
    {
        // professions
        case GOSSIP_ACTION_INFO_DEF + 20: // Alchemy
            LearnAllRecipes(player, SKILL_ALCHEMY);
            break;
        case GOSSIP_ACTION_INFO_DEF + 21: // Blacksmithing
            LearnAllRecipes(player, SKILL_ALCHEMY);
            break;
        case GOSSIP_ACTION_INFO_DEF + 22: // Enchanting
            LearnAllRecipes(player, SKILL_ENCHANTING);
            break;
        case GOSSIP_ACTION_INFO_DEF + 23: // Engineering
            LearnAllRecipes(player, SKILL_ENGINEERING);
            break;
        case GOSSIP_ACTION_INFO_DEF + 24: // Jewelcrafting
            LearnAllRecipes(player, SKILL_JEWELCRAFTING);
            break;
        case GOSSIP_ACTION_INFO_DEF + 25: // Leatherworking
            LearnAllRecipes(player, SKILL_LEATHERWORKING);
            break;
        case GOSSIP_ACTION_INFO_DEF + 26: // Tailoring
            LearnAllRecipes(player, SKILL_TAILORING);
            break;
        case GOSSIP_ACTION_INFO_DEF + 27: // Herbalism
            LearnAllRecipes(player, SKILL_HERBALISM);
            break;
        case GOSSIP_ACTION_INFO_DEF + 28: // Mining
            LearnAllRecipes(player, SKILL_MINING);
            break;
        case GOSSIP_ACTION_INFO_DEF + 29: // Skinning
            LearnAllRecipes(player, SKILL_SKINNING);
            break;
        case GOSSIP_ACTION_INFO_DEF + 30: // First Aid
            LearnAllRecipes(player, SKILL_ALCHEMY);
            break;
        case GOSSIP_ACTION_INFO_DEF + 31: // Cooking
            LearnAllRecipes(player, SKILL_COOKING);
            break;
        case GOSSIP_ACTION_INFO_DEF + 32: // Fishing
            LearnAllRecipes(player, SKILL_FISHING);
            break;
        case GOSSIP_ACTION_INFO_DEF + 10: level = NPC_WELCOME_GIVEN_LEVEL_60; break;
        case GOSSIP_ACTION_INFO_DEF + 11: level = NPC_WELCOME_GIVEN_LEVEL_65; break;
        case GOSSIP_ACTION_INFO_DEF + 12: level = NPC_WELCOME_GIVEN_LEVEL_70; break;
        default: level = NPC_WELCOME_GIVEN_LEVEL_60; break;
    }

    // call GiveLevel before AddSpells
    player->GiveLevel(level);
    player->CastSpell(player, MOUNT_SPELL, false);

    player->StoreNewItemInBestSlots(BAG_ADD_ID, 4);

    sPlayerStartMgr.AddSpells(player);
    sPlayerStartMgr.AddItems(player);

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


bool GossipHello_npc_teleport_dark_portal(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport me to the Dark Portal", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->SEND_GOSSIP_MENU(NPC_TEXT_TELEPORT_GOSSIP, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_teleport_dark_portal(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        if (pPlayer->TeleportTo(530, -247.29f, 910.64f, 84.38f, 1.493f))
            if (!pPlayer->isAlive())
            {
                pPlayer->ResurrectPlayer(0.5f, false);
                pPlayer->SpawnCorpseBones();
            }
    }
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

    newscript = new Script;
    newscript->Name = "npc_teleport_dark_portal";
    newscript->pGossipHello =  &GossipHello_npc_teleport_dark_portal;
    newscript->pGossipSelect = &GossipSelect_npc_teleport_dark_portal;
    newscript->RegisterSelf();
}
