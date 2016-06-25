/* ScriptData
SDName: npc_mysteria_changer
SD%Complete: 100
SDComment: PVP token changer
SDCategory: Custom
Author: Casso, Funnygirl
Year: 2010
EndScriptData */

#include "precompiled.h"
#include "Chat.h"
#include "Channel.h"

#define WSG_BGM	20558	//  Warsong Gulch Mark of Honor
#define AB_BGM 20559	//  Arathi Basin Mark of Honor
#define EOS_BGM	29024	//  Eye of the Storm Mark of Honor
#define AV_BGM 20560	// Alterac Valley Mark of Honor
#define POCET_BGM 1		// pocet mariek potrebnych z kazdej marky na vymenu
#define HONOR_PRICE_BGM 500 // kolko honoru dostane za vymenu
#define SPELL_HONORLESS_TARGET 2479

bool GossipHello_BGTokenChanger(Player *player, Creature *_Creature)
{
	if (_Creature->isQuestGiver())
		player->PrepareQuestMenu(_Creature->GetObjectGuid());

	player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE, "Change BG Marks for 500 Honor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

	player->PlayerTalkClass->SendGossipMenu(1, _Creature->GetObjectGuid());

	return true;
}

bool GossipSelect_BGTokenChanger(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
	switch(action)
	{
	case GOSSIP_ACTION_INFO_DEF+1: // Výmena BG Marky za 500 Honoru

		if(!player->HasItemCount(WSG_BGM, POCET_BGM, false) || !player->HasItemCount(AB_BGM, POCET_BGM, false) || !player->HasItemCount(EOS_BGM, POCET_BGM, false) || !player->HasItemCount(AV_BGM, POCET_BGM, false))
		{
			player->GetSession()->SendNotification("You don't have required BG Marks! (1 WSG + 1 AB + 1 EOS + 1 AV)");
			player->CLOSE_GOSSIP_MENU();
		}
		else
		{
			player->ModifyHonorPoints(1*HONOR_PRICE_BGM);
			player->DestroyItemCount(WSG_BGM, POCET_BGM, true, false);
			player->DestroyItemCount(AB_BGM, POCET_BGM, true, false);
			player->DestroyItemCount(EOS_BGM, POCET_BGM, true, false);
			player->DestroyItemCount(AV_BGM, POCET_BGM, true, false);
			player->GetSession()->SendNotification("BG Marks change for 500 Honors!");
			player->CLOSE_GOSSIP_MENU();
		}
		break;
	}

	return false;
}

void AddSC_BGTokenChanger()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name="npc_mysteria_bgchanger";
	newscript->pGossipHello = &GossipHello_BGTokenChanger;
	newscript->pGossipSelect = &GossipSelect_BGTokenChanger;
	newscript->RegisterSelf();
}
