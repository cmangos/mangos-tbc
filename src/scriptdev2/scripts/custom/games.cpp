/*
Scripted by Funnygirl 2015

#define ITEMID_HT 10663		// Change this to your ID 
#define ITEMID_HM 10662		// Change this to your ID 
#define ITEMID_DT 23580		// Change this to your ID 
#define ITEMID_DM 34368		// Change this to your ID 
#define ITEMID_ET 26045		// Change this to your ID 
#define ITEMID_EM 26044		// Change this to your ID 
#define ItemTAKEAmount 1	// Change this to your item's amount 
#define ItemGIVEAmount 2	// Change this to your item's amount 
*/

#include "precompiled.h"

#define BET_GAME 1000000		// 100g 00s 00c

uint32 m = 0; //
#define TEXT_NEXT		"|cffff0000==[Next Page]==>> |r"		// red
#define TEXT_BACK		"<<==[ Back ]=="						// black
#define TEXT_BACK_BLUE	"|cff0000ff<<==[ Back ]== |r"			// blue
#define TEXT_MAIN_MENU	"|cff0000ff<==[[ Main Menu ]]==> |r"	// blue 
#define TEXT_BYE		"|cff00ff00Bye, bye.... |r"				// green
#define TEXT_AGAIN		"|cff0000ffPlay again? |r"				// blue

#define WSG_BGM	20558	//  Warsong Gulch Mark of Honor
#define AB_BGM 20559	//  Arathi Basin Mark of Honor
#define EOS_BGM	29024	//  Eye of the Storm Mark of Honor
#define AV_BGM 20560	// Alterac Valley Mark of Honor
#define POCET_BGM 1
#define HONOR_PRICE 522

bool onGossipHello_CasinoGames(Player *player, Creature *_Creature)
{
	// Kontrola goldov
	if(player->GetMoney() < BET_GAME)
	{
		player->GetSession()->SendNotification("%s haven't enough money to play this game!", player->GetName());
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG,  "|cffff0000>>> haven't enough money to play this game! <<< |r",	GOSSIP_SENDER_MAIN, 0);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",			GOSSIP_SENDER_MAIN, 0);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",			GOSSIP_SENDER_MAIN, 0);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",			GOSSIP_SENDER_MAIN, 0);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_BYE,	GOSSIP_SENDER_MAIN, 99);
		player->PlayerTalkClass->SendGossipMenu(0, _Creature->GetObjectGuid());
	} else {
		////////////////// MAIN MENU ///////////////////////////
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|cffff0000Select from the options: |r", GOSSIP_SENDER_MAIN, 1); // Main Menu
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|cff0000ffHow to play? |r",	GOSSIP_SENDER_MAIN, 2);  // ako hrat?
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",									GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "=====>I'm ready to play!",			GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",									GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TABARD, "|cff0000ffThank you, I do not play! |r",	GOSSIP_SENDER_MAIN, 99);  // bye, bye

		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
	}

	return true;
}

void onSendDefaultMenu_CasinoGames(Player *player, Creature *_Creature, uint32 action)
{

	switch(action)
	{

		// Kamen Rock
	case 10:
		// definovanie random 1-3 (1 - kamen, 2 - papier, 3 - noznice)
		m = rand() % 3 +1;

		// kamen
		if (m == 1) {
			// player->PlayDirectSound(9659); // parry
			player->GetSession()->SendAreaTriggerMessage("Parry!");
			//player->GetSession()->SendNotification("We both choose ROCK, we tied!");
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000Parry |r",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "We both choose ROCK, we tied!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_AGAIN,						GOSSIP_SENDER_MAIN, 8); 
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		}

		// papier
		if (m == 2) {
			// player->PlayDirectSound(9656); // cheer
			player->GetSession()->SendAreaTriggerMessage("You Loose!");
			//player->GetSession()->SendNotification("I choose PAPER, I win!");
			player->ModifyMoney(-1*BET_GAME);
			//player->DestroyItemCount(ITEMID_HT, ItemTAKEAmount, true, false);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000You Loose! |r",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "You select ROCK!",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "I choose PAPER, I win!!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Loose:  - 100 golds!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_AGAIN,						GOSSIP_SENDER_MAIN, 8); 
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		}

		// noznice
		if (m == 3) {
			player->GetSession()->SendAreaTriggerMessage("You Win!");
			//player->GetSession()->SendNotification("I choose SCISSOR, QQ.");
			//player->PlayDirectSound(9657); // congratulation
			player->ModifyMoney(1*BET_GAME);
			//player->GetItemCount(ITEMID_HT, ItemGIVEAmount);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000You Win! |r",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "You select ROCK!",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "I choose  SCISSORS, QQ.",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Win:   + 100 golds!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_AGAIN,						GOSSIP_SENDER_MAIN, 8); 
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		}
		break;

		// Papier Paper
	case 20:
		// definovanie random 1-3 (1 - kamen, 2 - papier, 3 - noznice)
		m = rand() % 3 +1;

		// kamen
		if (m == 1) {
			player->GetSession()->SendAreaTriggerMessage("You Win!");
			//player->GetSession()->SendNotification("I chose ROCK, you win.");
			//player->PlayDirectSound(9657); // congratulation
			player->ModifyMoney(1*BET_GAME);
			//player->GetItemCount(ITEMID_HT, ItemGIVEAmount);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000You Win! |r",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "You select PAPER!",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "I choose ROCK, QQ.",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Win:   + 100 golds!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_AGAIN,						GOSSIP_SENDER_MAIN, 8); 
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		}

		// remiza papier
		if (m == 2) {
			//player->PlayDirectSound(9659); // parry
			player->GetSession()->SendAreaTriggerMessage("Parry!");
			//player->GetSession()->SendNotification("We both choose PAPER, tie!");
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000Parry |r",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "We both choose PAPER!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);	
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_AGAIN,						GOSSIP_SENDER_MAIN, 8); 
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		}

		// noznice
		if (m == 3) {
			// player->PlayDirectSound(9656); // cheer
			player->GetSession()->SendAreaTriggerMessage("You Loose!");
			//player->GetSession()->SendNotification("I choose SCISSORS and cut through your paper like butter.");
			player->ModifyMoney(-1*BET_GAME);
			//player->DestroyItemCount(ITEMID_HT, ItemTAKEAmount, true, false);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000You Loose! |r",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "You select PAPER!",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "I choose SCISSORS, I win!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Loose:  - 100 golds!",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_AGAIN,						GOSSIP_SENDER_MAIN, 8); 
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		}
		break;

		// Noznice Scissors
	case 30:
		// definovanie random 1-3 (1 - kamen, 2 - papier, 3 - noznice)
		m = rand() % 3 +1;

		// kamen
		if (m == 1) {
			// player->PlayDirectSound(9656); // cheer
			player->GetSession()->SendAreaTriggerMessage("You Loose!");
			//player->GetSession()->SendNotification("I choose ROCK and crushed your puny scissors, I win!");
			player->ModifyMoney(-1*BET_GAME);
			//player->DestroyItemCount(ITEMID_HT, ItemTAKEAmount, true, false);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000You Loose! |r",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "You select SCISSORS!",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "I choose  ROCK, I Win!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Loose:  - 100 golds!",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_AGAIN,						GOSSIP_SENDER_MAIN, 8); 
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		}

		// papier
		if (m == 2) {
			player->GetSession()->SendAreaTriggerMessage("You Win!");
			//player->GetSession()->SendNotification("Aww... Your SCISSORS cut through my paper.");	
			//player->PlayDirectSound(9657); // congratulation
			player->ModifyMoney(1*BET_GAME);
			//player->GetItemCount(ITEMID_HT, ItemGIVEAmount);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000You Win! |r",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "You select SCISSORS!",		GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "I choose  PAPER, QQ.",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Win:   + 100 golds!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_AGAIN,						GOSSIP_SENDER_MAIN, 8); 
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		}

		// remiza noznice
		if (m == 3) {
			//player->PlayDirectSound(9659); // parry
			player->GetSession()->SendAreaTriggerMessage("Parry!");
			//player->GetSession()->SendNotification("Parry, we tied!!");
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000Parry |r",			GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "We both choose SCISSORS!",	GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);	
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_AGAIN,						GOSSIP_SENDER_MAIN, 8); 
			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		}
		break;

		// velky risk nechcem hrat - bye, bye...
	case 99:
		player->GetSession()->SendNotification("Maybe later!?");
		//player->PlayDirectSound(9654); // bye
		player->CLOSE_GOSSIP_MENU();
		break;

	case 1: // <- Main Menu
		onGossipHello_CasinoGames(player, _Creature);
		break;

	case 2: // How to play?
		player->GetSession()->SendNotification("How to play -> Rock, Paper, Scissors?");
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000How to play? |r",	GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "                  Easy !!!",	GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000Bid is 100 golds !!! |r",	GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Select one options: ",	GOSSIP_SENDER_MAIN, 2);	
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "   Rock, Paper or Scissors.", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Win:    + 100 golds!",		GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Lose:   - 100 golds!",			GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Remiza:  nothing. ",					GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "                 Good Luck!",	GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",								GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_MAIN_MENU,					GOSSIP_SENDER_MAIN, 1); 
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		break;

	case 8:
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "|cffff0000Select one options:|r",				GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",									GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK, "===> I select Rock!",			GOSSIP_SENDER_MAIN, 10);  // kamen
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK, "=====> I select Paper!",			GOSSIP_SENDER_MAIN, 20);  // papier
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK, "=======> I select Scissors!",		GOSSIP_SENDER_MAIN, 30);  // noznice
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, " ",									GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, TEXT_MAIN_MENU,						GOSSIP_SENDER_MAIN, 1);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		break;

	default:  // Something wrong?!
		player->CLOSE_GOSSIP_MENU();
	}
}

bool onGossipSelect_CasinoGames(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
	// Main menu
	if (sender == GOSSIP_SENDER_MAIN)
		onSendDefaultMenu_CasinoGames(player, _Creature, action);
	return true;
}

void AddSC_CasinoGames()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name="npc_casino";
	newscript->pGossipHello = &onGossipHello_CasinoGames;
	newscript->pGossipSelect = &onGossipSelect_CasinoGames;
	newscript->RegisterSelf();
}
