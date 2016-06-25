/* ScriptData
SDName: 
SD%Complete: 100
SDComment: 
SDCategory: Custom
Authors: 
Year: 2010
EndScriptData */

#include "precompiled.h"

#define SINGLE_COST 10000  // 1 golds
#define CLASS_COST 50000  // 5 golds

#define TEXT_NEXT		"|cffff0000==[Next Page]==>> |r"		// red 
#define TEXT_BACK		"<<==[ Back ]=="						// black
#define TEXT_BACK_BLUE	"|cff0000ff<<==[ Back ]== |r"			// blue
#define TEXT_MAIN_MENU	"|cff0000ff<==[[ Main Menu ]]==> |r"	// blue 
#define TEXT_BYE		"|cff00ff00Bye, bye.... |r"				// green

#define MAINMENU "|TInterface/ICONS/Ability_Spy:30:30:-18:0|t|cff0000ff<==[[ Main Menu ]]==>|r"
#define MORE "|TInterface/ICONS/Spell_chargepositive:30:30:-18:0|t|cffff0000==[Next Page]==>>|r"
#define LESS "|TInterface/ICONS/Spell_chargenegative:30:30:-18:0|t|cff0000ff<<==[ Back ]== |r"


enum spells
{	
	AGILITY = 33077,
	ARCANE_INTELECT = 27126,
	BLESSING_OF_KINGS = 20217, //25898,
	BLESSING_OF_MIGHT = 27141,
	BLESSING_OF_SALVATION = 25895,
	BLESSING_OF_WISDOM = 27143,
	DIVINE_SPIRIT = 25312,
	INTELLECT = 33078,
	MARK_OF_THE_WILD = 26990,
	POWER_WORD_FORTITUDE = 25389,
	SHADOW_PROTECTION = 25433,
	SPIRIT = 33080,
	STAMINA = 33081,
	STRENGHT = 33082,
	THORNS = 26992,
	WATER_WALKING = 11319,
	SONGFLOWER_SERENADE = 15366
};
// 26990, 27126, 20217, 25433, 25312, 25389
bool GossipHello_MCBuffer(Player *player, Creature *_Creature)
{  
	////////////////// MAIN MENU ///////////////////////////
	player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, " |cffff0000 Choose from menu: |r",			GOSSIP_SENDER_MAIN, 9999);
	// kontrola kombatu
	if(player->isInCombat())
	{
		//player->GetSession()->SendAreaTriggerMessage("You are in Combat!");
		//player->GetSession()->SendNotification("You are in Combat %s !", player->GetName());
		player->GetSession()->SendNotification("|cffffffff[|r|cFFFF4500Combat Check|r|cffffffff]:|r |cffffffffYou're in combat %s ! |r", player->GetName());
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, "|cff0000ffYou are in combat!!! |r",	GOSSIP_SENDER_MAIN, 9999);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT,  TEXT_BYE,									GOSSIP_SENDER_MAIN, 9998);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		// player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_Creature->GetGUID());
		//player->PlayerTalkClass->SendCloseGossip();
		return true;
	} else {
		if(player->getLevel() >= 70)
		{

			// kontrola goldov
			if(player->GetMoney() >= SINGLE_COST) 
			{
				player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, " |TInterface/ICONS/Spell_holy_spellwarding:30:30:-18:0|t  --[[ BUFFS ]]--",								GOSSIP_SENDER_MAIN, 100);	
			} else {
				player->GetSession()->SendAreaTriggerMessage("%s , You haven't enough money to buy Buffs!", player->GetName());
				player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE,  "|cff0000ff>>> You haven't enough money! <<< |r",	GOSSIP_SENDER_MAIN, 9999);
			}
			if(player->GetMoney() >= CLASS_COST) 
			{
				player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE,  " |TInterface/ICONS/Spell_holy_prayerofhealing:30:30:-18:0|t  --[Buffs for Specialization]--",					GOSSIP_SENDER_MAIN, 1000);
			} else {
				player->GetSession()->SendAreaTriggerMessage("%s ,You haven't enough money to buy Buffs for Specialization!", player->GetName());
				player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE,  "|cff0000ff>>> You haven't enough money! <<< |r",	GOSSIP_SENDER_MAIN, 9999);
			}
		} else { 
			//player->GetSession()->SendAreaTriggerMessage("Enough level!");
			player->GetSession()->SendNotification("|cffffffffYou must be at least level 70+ %s ! |r", player->GetName());
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE,  "|cff12300ff>>> You must be at least level 70+! <<<",			GOSSIP_SENDER_MAIN, 9999);
		}
	}
	if(player->isGameMaster()) 
	{					
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_BATTLE,  "|cff00ff05-[ Heal me ]- visible only GM (.gm on) |r",	GOSSIP_SENDER_MAIN, 8000);
	}
	player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT,  TEXT_BYE,														GOSSIP_SENDER_MAIN, 9998);
	player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
	return true;
}

void SendDefaultMenu_MCBuffer(Player *player, Creature *_Creature, uint32 action)
{
	switch(action)  // switch(player->getClass())
	{
		/*	AGILITY = 33077,	ARCANE_INTELECT = 27126,	BLESSING_OF_KINGS = 25898,	BLESSING_OF_MIGHT = 27141,	BLESSING_OF_SALVATION = 25895,	BLESSING_OF_WISDOM = 27143,	DIVINE_SPIRIT = 25312,	INTELLECT = 33078,	MARK_OF_THE_WILD = 26990,
		POWER_WORD_FORTITUDE = 25389,	SHADOW_PROTECTION = 25433,	SPIRIT = 33080,	STAMINA = 33081,	STRENGHT = 33082,	THORNS = 26992,		WATER_WALKING = 11319 */
		////////////////// BUFFS SUBMENU ///////////////////////////
	case 100: // Buffs
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, " |cff0000ff Buff cost: 1 golds |r",	GOSSIP_SENDER_MAIN, 9999); // 0
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_wordfortitude:30:30:-18:0|t POWER WORD: FORTITUDE",	GOSSIP_SENDER_MAIN, 101);  // 1
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_divinespirit:30:30:-18:0|t DIVINE SPIRIT",			GOSSIP_SENDER_MAIN, 102);  // 2
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_shadow_antishadow:30:30:-18:0|t SHADOW PROTECTION",		GOSSIP_SENDER_MAIN, 103);  // 3		
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_fistofjustice:30:30:-18:0|t BLESSING OF MIGHT",      GOSSIP_SENDER_MAIN, 107);  // 6
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_magic_magearmor:30:30:-18:0|t BLESSING OF KINGS",      GOSSIP_SENDER_MAIN, 108);  // 7
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_sealofwisdom:30:30:-18:0|t BLESSING OF WISDOM",     GOSSIP_SENDER_MAIN, 109);  // 8
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_greaterblessingofsalvation:30:30:-18:0|t BLESSING OF SALVATION",  GOSSIP_SENDER_MAIN, 110);  // 9
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, MORE,					GOSSIP_SENDER_MAIN, 120);  // 10
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, LESS,					GOSSIP_SENDER_MAIN, 9999); // 11
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		break;
	case 120: // Buffs Next Page 1
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, " |cff0000ff Buff cost: 1 golds |r",	GOSSIP_SENDER_MAIN, 9999); // 0
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_nature_regeneration:30:30:-18:0|t MARK OF THE WILD",		GOSSIP_SENDER_MAIN, 104);  // 4
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_nature_thorns:30:30:-18:0|t THORNS",					GOSSIP_SENDER_MAIN, 105);  // 5
		//player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_nature_strength:30:30:-18:0|t STRENGHT",		GOSSIP_SENDER_MAIN, 121); // 1
		//player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_nature_unyeildingstamina.:30:30:-18:0|t STAMINA",		GOSSIP_SENDER_MAIN, 122); // 2
		//player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_blessingofagility:30:30:-18:0|t AGILITY",		GOSSIP_SENDER_MAIN, 123); // 3
		//player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_divinespirit:30:30:-18:0|t SPIRIT",			GOSSIP_SENDER_MAIN, 124); // 4
		//player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_magicalsentry:30:30:-18:0|t INTELLECT",		GOSSIP_SENDER_MAIN, 125); // 5		
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_magicalsentry:30:30:-18:0|t ARCANE INTELECT", GOSSIP_SENDER_MAIN, 106);  // 6
		// player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_frost_windwalkon:30:30:-18:0|t WATER WALKING",	GOSSIP_SENDER_MAIN, 126); // 7
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TRAINER, "|TInterface/ICONS/Spell_holy_mindvision:30:30:-18:0|t SONGFLOWER SERENADE",	GOSSIP_SENDER_MAIN, 127); // 7
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, MAINMENU,		GOSSIP_SENDER_MAIN, 9999); // 8
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, LESS,			GOSSIP_SENDER_MAIN, 100); // 9
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT,  TEXT_BYE,			GOSSIP_SENDER_MAIN, 9998); // 10
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		break;

		////////////////// BUFFS for Specialization SUBMENU ///////////////////////////
	case 1000: // Buff for Specialization
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_MONEY_BAG, " |cff0000ff Buffs cost: 5 golds |r",	GOSSIP_SENDER_MAIN, 9999);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TABARD, "|TInterface/ICONS/Ability_warrior_defensivestance:30:30:-18:0|t TANK",		GOSSIP_SENDER_MAIN, 1001); // Spell_holy_devotionaura.
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TABARD, "|TInterface/ICONS/Spell_holy_circleofrenewal:30:30:-18:0|t HEAL",		GOSSIP_SENDER_MAIN, 1002);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TABARD, "|TInterface/ICONS/Spell_fire_flamebolt:30:30:-18:0|t SPELL DMG",	GOSSIP_SENDER_MAIN, 1003);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TABARD, "|TInterface/ICONS/Spell_holy_fistofjustice:30:30:-18:0|t MELLE DMG",	GOSSIP_SENDER_MAIN, 1004);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TABARD, "|TInterface/ICONS/Inv_ammo_arrow_02:30:30:-18:0|t RANGED DMG",  GOSSIP_SENDER_MAIN, 1005);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, LESS,	GOSSIP_SENDER_MAIN, 9999);
		player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT,  TEXT_BYE,		GOSSIP_SENDER_MAIN, 9998);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, _Creature->GetObjectGuid());
		break;

	case 1001: // TANK		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, POWER_WORD_FORTITUDE, true);
		_Creature->CastSpell(player, ARCANE_INTELECT, true);
		//_Creature->CastSpell(player, AGILITY, true);
		//_Creature->CastSpell(player, STRENGHT, true);
		_Creature->CastSpell(player, THORNS, true);
		_Creature->CastSpell(player, MARK_OF_THE_WILD, true);
		_Creature->CastSpell(player, BLESSING_OF_KINGS, true);
		player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-CLASS_COST);
		break;
	case 1002: // HEAL		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, MARK_OF_THE_WILD, true);
		_Creature->CastSpell(player, POWER_WORD_FORTITUDE, true);
		//_Creature->CastSpell(player, STAMINA, true);
		_Creature->CastSpell(player, ARCANE_INTELECT, true);
		_Creature->CastSpell(player, BLESSING_OF_SALVATION, true);
		//_Creature->CastSpell(player, SPIRIT, true);
		_Creature->CastSpell(player, DIVINE_SPIRIT, true);
		player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-CLASS_COST);
		break;
	case 1003: // SPELL DMG			
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, MARK_OF_THE_WILD, true);
		_Creature->CastSpell(player, POWER_WORD_FORTITUDE, true);
		_Creature->CastSpell(player, ARCANE_INTELECT, true);
		_Creature->CastSpell(player, BLESSING_OF_SALVATION, true);
		_Creature->CastSpell(player, DIVINE_SPIRIT, true);
		//_Creature->CastSpell(player, SPIRIT, true);
		//_Creature->CastSpell(player, STAMINA, true);
		player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-CLASS_COST);
		break;
	case 1004: // MELE DMG		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, POWER_WORD_FORTITUDE, true);
		//_Creature->CastSpell(player, AGILITY, true);
		//_Creature->CastSpell(player, STRENGHT, true);
		_Creature->CastSpell(player, ARCANE_INTELECT, true);
		_Creature->CastSpell(player, BLESSING_OF_MIGHT, true);
		_Creature->CastSpell(player, MARK_OF_THE_WILD, true);		
		_Creature->CastSpell(player, DIVINE_SPIRIT, true);
		//_Creature->CastSpell(player, STAMINA, true);
		player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-CLASS_COST);
		break;		
	case 1005: // RANGED DMG		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, MARK_OF_THE_WILD, true);
		_Creature->CastSpell(player, POWER_WORD_FORTITUDE, true);
		//_Creature->CastSpell(player, AGILITY, true);
		//_Creature->CastSpell(player, STRENGHT, true);
		//_Creature->CastSpell(player, STAMINA, true);
		_Creature->CastSpell(player, BLESSING_OF_SALVATION, true);
		_Creature->CastSpell(player, ARCANE_INTELECT, true);
		_Creature->CastSpell(player, DIVINE_SPIRIT, true);
		player->GetSession()->SendAreaTriggerMessage("You are now full buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-CLASS_COST);
		break;

		/////////////////////////////////////////// BUFFS ///////////////////////////////////////////////
		/*	AGILITY = 33077,	ARCANE_INTELECT = 27126,	BLESSING_OF_KINGS = 25898,	BLESSING_OF_MIGHT = 27141,	BLESSING_OF_SALVATION = 25895,	BLESSING_OF_WISDOM = 27143,	DIVINE_SPIRIT = 25312,	INTELLECT = 33078,	MARK_OF_THE_WILD = 26990,
		POWER_WORD_FORTITUDE = 25389,	SHADOW_PROTECTION = 25433,	SPIRIT = 33080,	STAMINA = 33081,	STRENGHT = 33082,	THORNS = 26992,		WATER_WALKING = 11319 */
	case 101: // POWER_WORD_FORTITUDE		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, POWER_WORD_FORTITUDE, true);		
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed %s !", player->GetName());
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 102: // DIVINE_SPIRIT		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, DIVINE_SPIRIT, true);		
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 103: // SHADOW_PROTECTION		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, SHADOW_PROTECTION, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 104: // MARK_OF_THE_WILD 		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, MARK_OF_THE_WILD, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 105: // THORNS		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, THORNS, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 106: // ARCANE_INTELECT		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, ARCANE_INTELECT, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 107: // BLESSING_OF_MIGHT	
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, BLESSING_OF_MIGHT, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 108: // BLESSING_OF_KINGS		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, BLESSING_OF_KINGS, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 109: // BLESSING_OF_WISDOM	
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, BLESSING_OF_WISDOM, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 110: // BLESSING_OF_SALVATION		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, BLESSING_OF_SALVATION, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
		/*	AGILITY = 33077,	ARCANE_INTELECT = 27126,	BLESSING_OF_KINGS = 25898,	BLESSING_OF_MIGHT = 27141,	BLESSING_OF_SALVATION = 25895,	BLESSING_OF_WISDOM = 27143,	DIVINE_SPIRIT = 25312,	INTELLECT = 33078,	MARK_OF_THE_WILD = 26990,
		POWER_WORD_FORTITUDE = 25389,	SHADOW_PROTECTION = 25433,	SPIRIT = 33080,	STAMINA = 33081,	STRENGHT = 33082,	THORNS = 26992,		WATER_WALKING = 11319 */	
	case 121: // STRENGHT		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, STRENGHT, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 122: // STAMINA		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, STAMINA, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 123: // AGILITY		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, AGILITY, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 124: // SPIRIT		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, SPIRIT, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 125: // INTELLECT 		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, INTELLECT, true);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 126: // WATER_WALKING		
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, WATER_WALKING, false);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
	case 127: // SONGFLOWER SERENADE	
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, SONGFLOWER_SERENADE, false);			
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->GetSession()->SendAreaTriggerMessage("You are now buffed!");
		player->PlayDirectSound(3337); //
		player->ModifyMoney(-SINGLE_COST);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case 8000: // Heal me			
		player->CLOSE_GOSSIP_MENU();
		_Creature->CastSpell(player, 38588, true);  //  38588 Flash Heal efect, 31782 Rejuvenation
		if(player->GetPowerType() == POWER_MANA){
			player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
			player->SetHealth(player->GetMaxHealth());
			player->GetSession()->SendNotification("You are now healed and Mana regen %s !", player->GetName());
			player->GetSession()->SendAreaTriggerMessage("You are now Healed and Mana regen %s !", player->GetName());
		} else {
			player->SetHealth(player->GetMaxHealth());
			player->GetSession()->SendNotification("You are now healed %s !", player->GetName());			
			player->GetSession()->SendAreaTriggerMessage("You are now healed %s !", player->GetName());
		}

		//player->GetSession()->SendAreaTriggerMessage("You are now healed!");
		player->PlayDirectSound(2676); //
		_Creature->HandleEmote(EMOTE_ONESHOT_WAVE);
		player->ModifyMoney(-SINGLE_COST);
		break;

	case 9998: // Bye
		player->CLOSE_GOSSIP_MENU();
		break;

	case 9999: //<- Back
		GossipHello_MCBuffer(player, _Creature);
		break;

	default: // Something wrong?!
		player->CLOSE_GOSSIP_MENU();

	}
}

bool GossipSelect_MCBuffer(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
	// Main menu
	if (sender == GOSSIP_SENDER_MAIN)
		SendDefaultMenu_MCBuffer(player, _Creature, action);
	return true;
}

void AddSC_MCBuffer()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name="npc_buffer";
	newscript->pGossipHello = &GossipHello_MCBuffer;
	newscript->pGossipSelect = &GossipSelect_MCBuffer;
	newscript->RegisterSelf();
}
/*        ////////////////// SUB MENUS ///////////////////////////
case 1000: // Buff podla class
// Alliance
if(player->GetTeam() == ALLIANCE)
{
player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",		GOSSIP_SENDER_MAIN, 1001);
player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",		GOSSIP_SENDER_MAIN, 1002);
player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",		GOSSIP_SENDER_MAIN, 1003);
player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",		GOSSIP_SENDER_MAIN, 1004);
if(player->getLevel() >= 60) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",      GOSSIP_SENDER_MAIN, 1005);
}
// Horde
else if(player->GetTeam() == HORDE)
{
player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",		GOSSIP_SENDER_MAIN, 1006);
player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",		GOSSIP_SENDER_MAIN, 1007);
player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",		GOSSIP_SENDER_MAIN, 1008);
player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",		GOSSIP_SENDER_MAIN, 1009);
if(player->getLevel() >= 60) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",       GOSSIP_SENDER_MAIN, 1010);
}

// Neutral
if(player->getLevel() >= 60) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",		GOSSIP_SENDER_MAIN, 1011);
if(player->getLevel() >= 60) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",       GOSSIP_SENDER_MAIN, 1012);
if(player->getLevel() >= 30) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",       GOSSIP_SENDER_MAIN, 1013);
if(player->getLevel() >= 30) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",       GOSSIP_SENDER_MAIN, 1014);
if(player->getLevel() >= 30) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",       GOSSIP_SENDER_MAIN, 1016);
if(player->getLevel() >= 40) player->ADD_GOSSIP_ITEM( GOSSIP_ICON_VENDOR, "",       GOSSIP_SENDER_MAIN, 1015);


player->ADD_GOSSIP_ITEM( GOSSIP_ICON_TALK,   "<- Back",  GOSSIP_SENDER_MAIN, 6000);

player->PlayerTalkClass->SendGossipMenu(0, _Creature->GetObjectGuid());
break;
*/

/*
case CLASS_WARRIOR:
{
player->CastSpell(player, POWER_WORD_FORTITUDE, true);
player->CastSpell(player, KINGS_BUFF, true);
player->CastSpell(player, MARK_OF_THE_WILD, true);
player->CastSpell(player, PRAYER_OF_SPRITE, true);
player->CastSpell(player, SHADOW_BUFF, true);
pCreature->MonsterWhisper("You are now buffed!", player->GetGUID(), true);
}break;

case CLASS_PALADIN:
{
player->CastSpell(player, POWER_WORD_FORTITUDE, true);
player->CastSpell(player, KINGS_BUFF, true);
player->CastSpell(player, MARK_OF_THE_WILD, true);
player->CastSpell(player, PRAYER_OF_SPRITE, true);
player->CastSpell(player, ARCANE_BUFF, true);
player->CastSpell(player, SHADOW_BUFF, true);
pCreature->MonsterWhisper("You are now buffed!", player->GetGUID(), true);
}break;

case CLASS_HUNTER:
{
player->CastSpell(player, POWER_WORD_FORTITUDE, true);
player->CastSpell(player, KINGS_BUFF, true);
player->CastSpell(player, MARK_OF_THE_WILD, true);
player->CastSpell(player, PRAYER_OF_SPRITE, true);
player->CastSpell(player, ARCANE_BUFF, true);
player->CastSpell(player, SHADOW_BUFF, true);
pCreature->MonsterWhisper("You are now buffed!", player->GetGUID(), true);
}break;

case CLASS_ROGUE:
{
player->CastSpell(player, POWER_WORD_FORTITUDE, true);
player->CastSpell(player, KINGS_BUFF, true);
player->CastSpell(player, MARK_OF_THE_WILD, true);
player->CastSpell(player, PRAYER_OF_SPRITE, true);
player->CastSpell(player, SHADOW_BUFF, true);
pCreature->MonsterWhisper("You are now buffed!", player->GetGUID(), true);
}break;

case CLASS_PRIEST:
{
player->CastSpell(player, POWER_WORD_FORTITUDE, true);
player->CastSpell(player, KINGS_BUFF, true);
player->CastSpell(player, MARK_OF_THE_WILD, true);
player->CastSpell(player, PRAYER_OF_SPRITE, true);
player->CastSpell(player, ARCANE_BUFF, true);
player->CastSpell(player, SHADOW_BUFF, true);
pCreature->MonsterWhisper("You are now buffed!", player->GetGUID(), true);
}break;

case CLASS_SHAMAN:
{
player->CastSpell(player, POWER_WORD_FORTITUDE, true);
player->CastSpell(player, KINGS_BUFF, true);
player->CastSpell(player, MARK_OF_THE_WILD, true);
player->CastSpell(player, PRAYER_OF_SPRITE, true);
player->CastSpell(player, ARCANE_BUFF, true);
player->CastSpell(player, SHADOW_BUFF, true);
pCreature->MonsterWhisper("You are now buffed!", player->GetGUID(), true);
}break;

case CLASS_MAGE:
{
player->CastSpell(player, POWER_WORD_FORTITUDE, true);
player->CastSpell(player, KINGS_BUFF, true);
player->CastSpell(player, MARK_OF_THE_WILD, true);
player->CastSpell(player, PRAYER_OF_SPRITE, true);
player->CastSpell(player, ARCANE_BUFF, true);
player->CastSpell(player, SHADOW_BUFF, true);
pCreature->MonsterWhisper("You are now buffed!", player->GetGUID(), true);
}break;

case CLASS_WARLOCK:
{
player->CastSpell(player, POWER_WORD_FORTITUDE, true);
player->CastSpell(player, KINGS_BUFF, true);
player->CastSpell(player, MARK_OF_THE_WILD, true);
player->CastSpell(player, PRAYER_OF_SPRITE, true);
player->CastSpell(player, ARCANE_BUFF, true);
player->CastSpell(player, SHADOW_BUFF, true);
pCreature->MonsterWhisper("You are now buffed!", player->GetGUID(), true);
}break;

case CLASS_DRUID:
{
player->CastSpell(player, POWER_WORD_FORTITUDE, true);
player->CastSpell(player, KINGS_BUFF, true);
player->CastSpell(player, MARK_OF_THE_WILD, true);
player->CastSpell(player, PRAYER_OF_SPRITE, true);
player->CastSpell(player, ARCANE_BUFF, true);
player->CastSpell(player, SHADOW_BUFF, true);
pCreature->MonsterWhisper("You are now buffed!", player->GetGUID(), true);
}break;
*/