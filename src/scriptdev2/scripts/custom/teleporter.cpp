/* ScriptData
SDName: npc_teleporter
SD%Complete: 100
SDComment: City/Dungeon/arena Teleporter
SDCategory: Custom
Authors: Casso & Smrtokvitek
Year: 2010
EndScriptData */

#include "precompiled.h"
#define MAINMENU "|TInterface/ICONS/Ability_Spy:30:30:-18:0|t <= Main Menu"
#define MORE "|TInterface/ICONS/Spell_chargepositive:30:30:-18:0|t More =>"
#define LESS "|TInterface/ICONS/Spell_chargenegative:30:30:-18:0|t <= Back"

bool GossipHello_Teleporter(Player *player, Creature *_Creature)
{ 
	if (player->IsMounted()) {
	player->RemoveAurasDueToSpell(SPELL_AURA_MOUNTED);
	player->Unmount();
	player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
	}
    ////////////////// MAIN MENU ///////////////////////////
    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK, "|TInterface/ICONS/INV_BannerPVP_03:30:30:-18:0|t Cities =>",             GOSSIP_SENDER_MAIN, 1000);
    if(player->getLevel() >= 50) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK, "|TInterface/ICONS/Inv_misc_groupneedmore:30:30:-18:0|t Dungeons & Raids =>", GOSSIP_SENDER_MAIN, 2000);
    if(player->getLevel() >= 60) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK, "|TInterface/ICONS/Ability_DualWield:30:30:-18:0|t Arenas =>",             GOSSIP_SENDER_MAIN, 3000);
    // player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK, "Leveling zones",     GOSSIP_SENDER_MAIN, 4000);
    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK, "|TInterface/ICONS/Inv_misc_shadowegg:30:30:-18:0|t Other",              GOSSIP_SENDER_MAIN, 5000);
	player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK, "-= CLOSE =-",              GOSSIP_SENDER_MAIN, 7000);

	player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
    return true;
}

void SendDefaultMenu_Teleporter(Player *player, Creature *_Creature, uint32 action )
{
    switch(action)
    {
        ////////////////// SUB MENUS ///////////////////////////
    case 1000: // Cities
        // Alliance
        if(player->GetTeam() == ALLIANCE)
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Spell_arcane_teleportstormwind:30:30:-18:0|t Stormwind City",  GOSSIP_SENDER_MAIN, 1001);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Spell_arcane_teleportironforge:30:30:-18:0|t Ironforge",       GOSSIP_SENDER_MAIN, 1002);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Spell_arcane_teleportdarnassus:30:30:-18:0|t Darnassus",       GOSSIP_SENDER_MAIN, 1003);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Spell_arcane_teleportexodar:30:30:-18:0|t Exodar",          GOSSIP_SENDER_MAIN, 1004);
            if(player->getLevel() >= 58) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_misc_shadowegg:30:30:-18:0|t Honor Hold",      GOSSIP_SENDER_MAIN, 1005);
        }
        // Horde
        else if(player->GetTeam() == HORDE)
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Spell_arcane_teleportorgrimmar:30:30:-18:0|t Orgrimmar",       GOSSIP_SENDER_MAIN, 1006);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Spell_arcane_teleportthunderbluff:30:30:-18:0|t Thunder Bluff",   GOSSIP_SENDER_MAIN, 1007);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Spell_arcane_teleportundercity:30:30:-18:0|t Undercity",       GOSSIP_SENDER_MAIN, 1008);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Spell_arcane_teleportsilvermoon:30:30:-18:0|t Silvermoon City", GOSSIP_SENDER_MAIN, 1009);
            if(player->getLevel() >= 58) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_misc_shadowegg:30:30:-18:0|t Thrallmar",       GOSSIP_SENDER_MAIN, 1010);
        }

		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,      MORE,     GOSSIP_SENDER_MAIN, 1020);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,   MAINMENU,  GOSSIP_SENDER_MAIN, 6000);

        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
        break;

	case 1020: // 
		// Neutral
        if(player->getLevel() >= 60) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Spell_arcane_teleportshattrath:30:30:-18:0|t Shattrath City",  GOSSIP_SENDER_MAIN, 1011);
        if(player->getLevel() >= 60) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_jewelry_frostwolftrinket_01:30:30:-18:0|t Area 52",         GOSSIP_SENDER_MAIN, 1012);
        if(player->getLevel() >= 30) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_jewelry_frostwolftrinket_02:30:30:-18:0|t Gadgetzan",       GOSSIP_SENDER_MAIN, 1013);
        if(player->getLevel() >= 30) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_jewelry_frostwolftrinket_03:30:30:-18:0|t Booty Bay",       GOSSIP_SENDER_MAIN, 1014);
        if(player->getLevel() >= 30) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_jewelry_frostwolftrinket_04:30:30:-18:0|t Ratchet",         GOSSIP_SENDER_MAIN, 1016);
        if(player->getLevel() >= 40) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "|TInterface/ICONS/Inv_jewelry_frostwolftrinket_01:30:30:-18:0|t Everlook",        GOSSIP_SENDER_MAIN, 1015);
		
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,      LESS,     GOSSIP_SENDER_MAIN, 1000);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,   MAINMENU,  GOSSIP_SENDER_MAIN, 7000);

        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		break;

    case 2000: // Dungeons And Raids
               
            // D3
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_green:30:30:-18:0|t Auchindoun",         GOSSIP_SENDER_MAIN, 2010);
            // T3
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_green:30:30:-18:0|t Naxxramas",          GOSSIP_SENDER_MAIN, 2011);
            // T2/T1
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_red:30:30:-18:0|t Onyxia's Lair",      GOSSIP_SENDER_MAIN, 2012);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_red:30:30:-18:0|t Blackrock Mountain", GOSSIP_SENDER_MAIN, 2013);
            // Other 60lvl
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_01:30:30:-18:0|t Ahn' Qiraj",         GOSSIP_SENDER_MAIN, 2014);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_01:30:30:-18:0|t Zul'Gurub",          GOSSIP_SENDER_MAIN, 2015);

        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,      MORE,     GOSSIP_SENDER_MAIN, 2020);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,      MAINMENU,     GOSSIP_SENDER_MAIN, 6000);

       player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
        break;

	case 2020: // 
		// T6+/T6
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_01:30:30:-18:0|t Sunwell Plateau",    GOSSIP_SENDER_MAIN, 2001);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_01:30:30:-18:0|t Black Temple",       GOSSIP_SENDER_MAIN, 2002);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_01:30:30:-18:0|t Hyjal Summit",       GOSSIP_SENDER_MAIN, 2003);
            // T5
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_black:30:30:-18:0|t Tempest Keep",       GOSSIP_SENDER_MAIN, 2004);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_black:30:30:-18:0|t Coilfang Reservoir", GOSSIP_SENDER_MAIN, 2005);
            // T5/T4
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_black:30:30:-18:0|t Gruul's Lair",       GOSSIP_SENDER_MAIN, 2006);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_blue:30:30:-18:0|t Zul' Aman",          GOSSIP_SENDER_MAIN, 2007);
            // T4
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_blue:30:30:-18:0|t Karazhan",           GOSSIP_SENDER_MAIN, 2008);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Inv_misc_head_dragon_blue:30:30:-18:0|t Hellfire Citadel",   GOSSIP_SENDER_MAIN, 2009);

		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,      LESS,     GOSSIP_SENDER_MAIN, 2000);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,      MAINMENU,     GOSSIP_SENDER_MAIN, 6000);

        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		break;

    case 3000: // Arenas
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Ability_DualWield:30:30:-18:0|t  Gurubashi Arena",       GOSSIP_SENDER_MAIN, 3001);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Ability_DualWield:30:30:-18:0|t  Nagrand Arena",         GOSSIP_SENDER_MAIN, 3002);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Ability_DualWield:30:30:-18:0|t  Blade's Edge Arena",    GOSSIP_SENDER_MAIN, 3003);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Ability_DualWield:30:30:-18:0|t  Orgrimmar Arena",       GOSSIP_SENDER_MAIN, 3004);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Ability_DualWield:30:30:-18:0|t  Dire Maul Arena",       GOSSIP_SENDER_MAIN, 3005);

        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,   MAINMENU,               GOSSIP_SENDER_MAIN, 6000);

        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
        break;

/*    case 4000: // Leveling
        // Alliance
        if(player->GetTeam() == ALLIANCE)
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "1-50 level",  GOSSIP_SENDER_MAIN, 4001);
            if(player->getLevel() >= 45) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "50-70 level", GOSSIP_SENDER_MAIN, 4002);
        }
        // Horde
        else if(player->GetTeam() == HORDE)
        {
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "1-50 level",  GOSSIP_SENDER_MAIN, 4003);
            if(player->getLevel() >= 45) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "50-70 level", GOSSIP_SENDER_MAIN, 4004);
        }

        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,     MAINMENU,        GOSSIP_SENDER_MAIN, 6000);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_Creature->GetGUID());
        break;

		// Leveling areas 

    case 4001: // 1-50 alliance
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == ALLIANCE)
            player->TeleportTo(0, -4137.6f, -1058.59f, 178.638f, 4.791f);
        break;

    case 4002: // 50-70 alliance
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == ALLIANCE)
            player->TeleportTo(0, -3916.91f, -1457.46f, 147.31f, 5.150f);
        break;

    case 4003: // 1-50 horde
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == HORDE)
            player->TeleportTo(1, 5295.17f, -1937.22f, 1331.34f, 5.314f);
        break;

    case 4004: // 50-70 horde
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == HORDE)
            player->TeleportTo(1, 4584.91f, -2032.06f, 1148.02f, 1.438f);
        break;

*/
	case 7000:
		player->CLOSE_GOSSIP_MENU();
		break;

    case 5000: // Other
        if(player->getLevel() >= 60)
        {
            // Horde
            if(player->GetTeam() == HORDE)
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Ability_DualWield:30:30:-18:0|t Attack on Stormwind", GOSSIP_SENDER_MAIN, 5001);

            // Alliance
            if(player->GetTeam() == ALLIANCE)
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Ability_DualWield:30:30:-18:0|t Attack on Orgrimmar", GOSSIP_SENDER_MAIN, 5002);

            // Neutral
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TAXI,    "|TInterface/ICONS/Inv_misc_shadowegg:30:30:-18:0|t Dark Portal",         GOSSIP_SENDER_MAIN, 5003);
        }
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TAXI,    "|TInterface/ICONS/Inv_banner_01:30:30:-18:0|t Mysteria Centrum",    GOSSIP_SENDER_MAIN, 5004);

        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TABARD, "|TInterface/ICONS/INV_BannerPVP_03:30:30:-18:0|t Guild House",      GOSSIP_SENDER_MAIN, 5005);

        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,    MAINMENU,             GOSSIP_SENDER_MAIN, 6000);

        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
        break;

    case 6000: //<- Back ( <= Main Menu)
        GossipHello_Teleporter(player,_Creature);
        break;


        ////////////////// TELEPORTATIONS ///////////////////////////

        // Cities

    case 1001: // Stormwind City
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == ALLIANCE)
            player->TeleportTo(0, -8832.59f, 621.7f, 93.59f, 3.944f);
        break;

    case 1002: // Ironforge
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == ALLIANCE)
            player->TeleportTo(0, -4981.25f, -881.542f, 501.66f, 5.416f);
        break;    

    case 1003: // Darnassus
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == ALLIANCE)
            player->TeleportTo(1, 9948.55f, 2413.59f, 1327.23f, 1.619f);
        break;    

    case 1004: // Exodar
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == ALLIANCE)
            player->TeleportTo(530, -3902.58f, -11748.74f, -107.72f, 5.221f);
        break;    

    case 1005: // Honor Hold
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == ALLIANCE)
            player->TeleportTo(530, -705.713f, 2681.38f, 93.887f, 6.068f);
        break;

    case 1006: // Orgrimmar
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == HORDE)
            player->TeleportTo(1, 1586.07f, -4401.07f, 5.15365f, 0.570f);
        break;

    case 1007: // Thunder Bluff
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == HORDE)
            player->TeleportTo(1, -1273.01f, 122.61f, 131.17f, 5.137f);
        break;

    case 1008: // Undercity
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == HORDE)
            player->TeleportTo(0, 1568.29f, 241.27f, -44.30f, 0.00f);
        break;

    case 1009: // Silvermoon City
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == HORDE)
            player->TeleportTo(530, 9912.12f, -7149.29f, 45.607f,    4.010f);
        break;

    case 1010: // Thrallmar
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == HORDE)
            player->TeleportTo(530, 139.167f, 2672.55f, 85.441f, 3.545f);
        break;

    case 1011: // Shattrath City
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -1886.71f, 5422.01f, -12.42f, 0.327f);
        break;

    case 1012: // Area 52
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 3049.57f, 3686.92f, 142.34f, 0.522f);
        break;    

    case 1013: // Gadgetzan
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -7170.16f, -3785.36f, 8.3698f, 0.000f);
        break;

    case 1014: // Booty Bay
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -14293.5f, 533.7f, 8.79f, 4.294f);
        break;

    case 1015: // Everlook
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 6727.00f, -4643.06f, 721.40f, 4.76f);
        break;

    case 1016: // Ratchet
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -956.66f, -3754.70f, 5.34f, 0.99f);
        break;

        // Dungeons and Raids

    case 2001: // Sunwell Plateau
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 12574.6f, -6774.81f, 15.09f, 3.120f);
        break;

    case 2002: // Black Temple
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -3640.55f, 315.48f, 35.1f, 3.060f);
        break;

    case 2003: // Hyjal Summit
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -8177.18f, -4179.92f, -167.18f, 1.050f);
        break;

    case 2004: // Tempest Keep
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 3099.65f, 1526.38f, 190.3f, 4.660f);
        break;

    case 2005: // Coilfang Reservoir
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 787.28f, 6867.18f, -65.35f, 0.094f);
        break;

    case 2006: // Gruul's Lair
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 3527.78f, 5155.82f, -1.3f, 4.720f);
        break;

    case 2007: // Zul' Aman
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 6851.29f, -7952.01f, 170.03f, 4.820f);
        break;

    case 2008: // Karazhan
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -11127.9f, -2018.67f, 47.3f, 0.688f);
        break;

    case 2009: // Hellfire Citadel
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -268.3f, 3109.79f, 31.66f, 2.162f);
        break;

    case 2010: // Auchindoun
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -3325.73f, 4947.9f, -101.395f, 4.414f);
        break;

    case 2011: // Naxxramas
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, 3108.88f, -3717.06f, 133.6f, 5.730f);
        break;        

    case 2012: // Onyxia's Lair
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -4708.14f, -3727.58f, 54.57f, 3.811f);
        break;

    case 2013: // Blackrock Mountain
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -7493.71f, -1115.18f, 265.86f, 3.200f);
        break;

    case 2014: // Ahn' Qiraj
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -8414.69f, 1503.07f, 30.54f, 2.754f);
        break;

    case 2015: // Zul' Gurub
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -11916.2f, -1205.27f, 92.28f, 4.732f);
        break;

        // Arenas

    case 3001: // Gurubashi arena (Stranglethorn vale)
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -13226.1f, 233.839f, 33.359f, 1.139f);
        break;

    case 3002: // Ring of Trials (Nagrand)
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, -2039.32f, 6658.62f, 13.05f, 5.273f);
        break;

    case 3003: // Circle of blood (Bladesedge mountains)
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(530, 2838.74f, 5928.16f, 11.06f, 2.419f);
        break;

    case 3004: // Ring of Valor (Orgrimmar)
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 2179.908f, -4767.31f, 54.9f, 2.62f);
        break;

	 case 3005: // Dire Maul 
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, -3737.899f, 1098.239f, 131.968f, 6.019f);
        break;

        // Other

    case 5001: // Attack to Stormwind City
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == HORDE)
            player->TeleportTo(0, -9553.17f, -1372.71f, 51.29f, 0.0f);
        break;

    case 5002: // Attack to Orgrimmar
        player->CLOSE_GOSSIP_MENU();
        if(player->GetTeam() == ALLIANCE)
            player->TeleportTo(1, 2432.84f, -2953.04f, 123.75f, 3.263f);
        break;

    case 5003: // Dark Portal
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(0, -11888.9f, -3206.47f, -15.12f, 3.323f);
        break;

    case 5004: // Mysteria Centrum
        player->CLOSE_GOSSIP_MENU();
       	    // player->TeleportTo(1, 7333.12f, -1592.5f, 164.542f, 1.521f);
		// player->TeleportTo(0, -11213.6f, -1800.5f, -28.4029f, 1.5363f);
		player->TeleportTo(1, -10710.190f, 2482.4848f, 9.1479f, 3.5000f);
        break;

    case 5005: // GuildHouse
        if(player->TeleportToGuildHouse())
            player->CLOSE_GOSSIP_MENU();
        else
            
		player->PlayerTalkClass->SendGossipMenu(500001, _Creature->GetObjectGuid());
        break;


    default: // Something wrong?!
        player->CLOSE_GOSSIP_MENU();

    }
}

bool GossipSelect_Teleporter(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    // Main menu
    if (sender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_Teleporter( player, _Creature, action );

    return true;
}

void AddSC_Teleporter()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="npc_teleporter";
    newscript->pGossipHello = &GossipHello_Teleporter;
    newscript->pGossipSelect = &GossipSelect_Teleporter;
    newscript->RegisterSelf();
}
