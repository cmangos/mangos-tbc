/* 
<--------------------------------------------------------------------------->
- Developer: Funnygirl, Mireno, Trix'
- Complete: 100%
- ScriptName: 'Beastmaster_Trainer'
- Developed: 06/03/2016
- Update: 06/04/2016
<--------------------------------------------------------------------------->
*/
#include "precompiled.h"
#include "Pet.h"
#include <cstring>
#include "Player.h"
#include "Creature.h"
#include "Unit.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "Map.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "MapManager.h"
#include "Common.h"
#include "Language.h"
#include "ObjectGuid.h"
#include "World.h"
#include "CreatureAI.h"
#include "Util.h"

#define MAINMENU "|TInterface/ICONS/Ability_Spy:30:30:-18:0|t <= Main Menu"
#define MORE "|TInterface/ICONS/Spell_chargepositive:30:30:-18:0|t More =>"
#define LESS "|TInterface/ICONS/Spell_chargenegative:30:30:-18:0|t <= Back"

void CreatePet(Player* player, Creature* creature, uint32 entry)
{
	if(player->getClass() != CLASS_HUNTER)
	{
		creature->MonsterWhisper("I can only train Hunters in the way of the beast.",  player, false);
		player->GetSession()->SendNotification("%s , you are not a Hunter!", player->GetName());
		player->CLOSE_GOSSIP_MENU();
		return;
	}
	Map *map = player->GetMap();
	// Creature* creatureTarget = (Creature*)entry;
	Creature* creatureTarget = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() -2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 0); // TEMPSUMMON_CORPSE_TIMED_DESPAWN, 0
	if(!creatureTarget) return;

	uint32 spell_id = 13481;
	SpellEntry const* spellInfo = sSpellStore.LookupEntry(spell_id);
		
	Pet* pet = new Pet(HUNTER_PET);
	if (!pet->CreateBaseAtCreature(creatureTarget))
	{
		delete pet;
		return;
	}
	/*
	//CreatureCreatePos pos(creature, creature->GetOrientation());
	//uint32 pet_number = sObjectMgr.GeneratePetNumber();

	// CreatedBySpell
	pet->SetUInt32Value(UNIT_CREATED_BY_SPELL, spell_id);

	// kill original creature
	creatureTarget->SetDeathState(JUST_DIED);
	creatureTarget->SetHealth(0);
	creatureTarget->RemoveCorpse();

	// uint32 guid = map->GenerateLocalLowGuid(HIGHGUID_PET);
	// pet type
	pet->setPetType(HUNTER_PET);
	// happiness
	// pet->SetMaxPower(POWER_HAPPINESS, pet->GetCreatePowers(POWER_HAPPINESS));
	pet->SetPower(POWER_HAPPINESS, 10480000);
	// owner
	pet->SetOwnerGuid(player->GetObjectGuid());
	//pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUIDLow());
	// faction
	pet->setFaction(player->getFaction());
	// prepare visual effect for levelup
	pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
	// pet->SetLevel(player->getLevel() -1);

	// pet->GetMap()->GetObjectsStore().insert<Pet>(pet->GetGUID(), (Pet*)entry);
	// pet->GetMap()->AddToMap((Creature*)pet);
	pet->GetMap()->Add((Creature*)pet);
	// visual effect for levelup for lulz
	// pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() -1);

	CreatureInfo const* creatureInfo = ObjectMgr::GetCreatureTemplate(entry);
	if(!creatureInfo || !creatureInfo->isTameable())
	{
		delete pet;
		return;
	}

	pet->SetPowerType(POWER_FOCUS);
	pet->SetCanModifyStats(true);
	// experience
	// pet->SetUInt32Value(UNIT_FIELD_PETEXPERIENCE, 0);
	// loyalty
	pet->SetByteValue(UNIT_FIELD_BYTES_1, 1, 6);
	// SET TP
	pet->SetTP(350);
	// react state
	pet->GetCharmInfo()->SetReactState(ReactStates(1));
	// pvp
	if(player->IsPvP())
		pet->SetPvP(true);

	// pet number
	pet->GetCharmInfo()->SetPetNumber(sObjectMgr.GeneratePetNumber(), true);
	if (!pet->InitStatsForLevel(player->getLevel()))
	{
		//pet init stats for lvl
		pet->InitStatsForLevel(player->getLevel());
		pet->SynchronizeLevelWithOwner();
		pet->UpdateAllStats();
		pet->InitPetCreateSpells();
		// pet->UpdateWalkMode(player);
	}

	// caster has pet now
	player->SetPet(pet); 
	// pet->AIM_Initialize();
	// creature->AddToWorld();

	player->PetSpellInitialize();
	// Save pet to DB
	pet->SavePetToDB(PET_SAVE_AS_CURRENT);
	*/
	pet->SetOwnerGuid(player->GetObjectGuid());
	pet->SetCreatorGuid(player->GetObjectGuid());
	pet->setFaction(player->getFaction());
	pet->SetUInt32Value(UNIT_CREATED_BY_SPELL, spell_id);
	
	if (player->IsPvP())
		pet->SetPvP(true);

	if (!pet->InitStatsForLevel(player->getLevel()))
	{
		sLog.outError("Pet::InitStatsForLevel() failed for creature (Entry: %u)!", creatureTarget->GetEntry());
		delete pet;
		return;
	}

	pet->GetCharmInfo()->SetPetNumber(sObjectMgr.GeneratePetNumber(), true);
	// this enables pet details window (Shift+P)
	pet->AIM_Initialize();
	pet->InitPetCreateSpells();
	pet->SetHealth(pet->GetMaxHealth());
	// happiness
	pet->SetPower(POWER_HAPPINESS, 10480000);
	// loyalty
	pet->SetByteValue(UNIT_FIELD_BYTES_1, 1, 6);
	// SET TP
	pet->SetTP(350);
	// pet->SetTP(pet->getLevel() * (pet->GetLoyaltyLevel() - 1));
	// react state
	pet->GetCharmInfo()->SetReactState(ReactStates(1));
	// "kill" original creature
	creatureTarget->ForcedDespawn();

	// prepare visual effect for levelup
	pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);

	// add to world
	pet->GetMap()->Add((Creature*)pet);

	// visual effect for levelup
	pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());

	// caster have pet now
	player->SetPet(pet);

	pet->SavePetToDB(PET_SAVE_AS_CURRENT);
	player->PetSpellInitialize();

	player->CLOSE_GOSSIP_MENU();
	creature->MonsterWhisper("You have learned a way of the beast, congratulations.",  player, false);
}


bool GossipHello_Npc_Beastmaster(Player* player, Creature* m_creature)
{
	player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Ability_hunter_beasttaming:26:26:-15:0|t Obtain a New Pet.", GOSSIP_SENDER_MAIN, 10);
	player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Ability_hunter_beastcall:26:26:-15:0|t Take me to the Stable.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
	player->ADD_GOSSIP_ITEM(6, "|TInterface\\icons\\Inv_misc_food_58:26:26:-15:0|t Sell me some Food for my Pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
	player->ADD_GOSSIP_ITEM(5, "|TInterface\\icons\\Ability_spy:26:26:-15:0|t Close Beastmaster Window.", GOSSIP_SENDER_MAIN, 150);
	player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
	return true;
}

bool GossipSelect_Npc_Beastmaster(Player* player, Creature* m_creature, uint32 /*sender*/, uint32 action)
{
	player->PlayerTalkClass->ClearMenus();

	switch(action)
	{

	case 100:
		player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Ability_hunter_beasttaming:26:26:-15:0|t Obtain a New Pet.", GOSSIP_SENDER_MAIN, 10);
		player->ADD_GOSSIP_ITEM(2, "|TInterface\\icons\\Ability_hunter_beastcall:26:26:-15:0|t Take me to the Stable.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
		player->ADD_GOSSIP_ITEM(6, "|TInterface\\icons\\Inv_misc_food_58:26:26:-15:0|t Sell me some Food for my Pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
		player->ADD_GOSSIP_ITEM(5, "|TInterface\\icons\\Ability_spy:26:26:-15:0|t Close Beastmaster Window.", GOSSIP_SENDER_MAIN, 150);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
		break;

		// Close
	case 150:
		player->CLOSE_GOSSIP_MENU();
		break;
		// Stable master
	case GOSSIP_OPTION_STABLEPET:
		player->GetSession()->SendStablePet(m_creature->GetObjectGuid());
		break; 
		// Food vendor
	case GOSSIP_OPTION_VENDOR:
		player->GetSession()->SendListInventory(m_creature->GetObjectGuid());
		break;

		// rozdelenie petov
	case 10:
		if(player->GetPet())
		{
			m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_AnimalHandler:26:26:-15:0|t|r Cunning (PvP)", GOSSIP_SENDER_MAIN, 1000);	// PVP	Ability_hunter_dragonhawk
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_druid_primaltenacity:26:26:-15:0|t|r Ferocity (Dmg)", GOSSIP_SENDER_MAIN, 2000);  // Dmg
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Spell_nature_shamanrage.:26:26:-15:0|t|r Tenacity (Tank)", GOSSIP_SENDER_MAIN, 3000); // Tank
		player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
		break;

		// Cunning pets
	case 1000:
		if(player->GetPet())
		{
			m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_bat:26:26:-15:0|t|r Bat (Cower-6, Screech-4)", GOSSIP_SENDER_MAIN, 1001);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_vulture:26:26:-15:0|t|r Bird", GOSSIP_SENDER_MAIN, 1002);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_ravager:26:26:-15:0|t|r Ravager.", GOSSIP_SENDER_MAIN, 1003);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_windserpent:26:26:-15:0|t|r Serpent.", GOSSIP_SENDER_MAIN, 1004); 
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_scorpid:26:26:-15:0|t|r Scorpid.", GOSSIP_SENDER_MAIN, 1005);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_spider:26:26:-15:0|t|r Spider.", GOSSIP_SENDER_MAIN, 1006);
		player->ADD_GOSSIP_ITEM(2, LESS, GOSSIP_SENDER_MAIN, 10);
		player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
		break;

		// Ferocity pets
	case 2000:
		if(player->GetPet())
		{
			m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_cat:26:26:-15:0|t|r Bangalash.", GOSSIP_SENDER_MAIN, 2001);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_wolf:26:26:-15:0|t|r Cat.", GOSSIP_SENDER_MAIN, 2002);	
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_boar:26:26:-15:0|t|r Boar.", GOSSIP_SENDER_MAIN, 2003);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_crab:26:26:-15:0|t|r Crab.", GOSSIP_SENDER_MAIN, 2004);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_crocolisk:26:26:-15:0|t|r Crocolisk.", GOSSIP_SENDER_MAIN, 2005);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_dragonhawk:26:26:-15:0|t|r Dragonhawk.", GOSSIP_SENDER_MAIN, 2006);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_owl:26:26:-15:0|t|r Owl (Claw-9, Dive-3)", GOSSIP_SENDER_MAIN, 2007);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_raptor:26:26:-15:0|t|r Raptor.", GOSSIP_SENDER_MAIN, 2008);
		player->ADD_GOSSIP_ITEM(2, MORE, GOSSIP_SENDER_MAIN, 2100);
		player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
		break;

	// NEXT FEROCITY
	case 2100:
		if(player->GetPet())
		{
			m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_tallstrider:26:26:-15:0|t|r Strider.", GOSSIP_SENDER_MAIN, 2009);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_hyena:26:26:-15:0|t|r Hyena.", GOSSIP_SENDER_MAIN, 2010);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_cat:26:26:-15:0|t|r Mountain Lion - Prowl.", GOSSIP_SENDER_MAIN, 2011);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_wolf:26:26:-15:0|t|r Wolf.", GOSSIP_SENDER_MAIN, 2012);
		player->ADD_GOSSIP_ITEM(2, LESS, GOSSIP_SENDER_MAIN, 2000);
		player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
		break;

		// Tenacity pets
	case 3000:
		if(player->GetPet())
		{
			m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_turtle:26:26:-15:0|t|r Turtle.", GOSSIP_SENDER_MAIN, 3001);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_bear:26:26:-15:0|t|r Bear.", GOSSIP_SENDER_MAIN, 3002);
		player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_gorilla:26:26:-15:0|t|r Gorilla.", GOSSIP_SENDER_MAIN, 3003); // Ability_hunter_pet_gorill		
		player->ADD_GOSSIP_ITEM(2, LESS, GOSSIP_SENDER_MAIN, 10);
		player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
		break;
		// ======================================================================================================================================================================

	case 1001: // Bat
		CreatePet(player, m_creature, 8602);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1002: // Bird, Rock
		CreatePet(player, m_creature, 5430); // 23051
		player->CLOSE_GOSSIP_MENU();
		break;  
	case 1003: // Ravager
		CreatePet(player, m_creature, 22123); // 19349
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1004: // Serpent
		CreatePet(player, m_creature, 5349);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1005: // Scorpid
		CreatePet(player, m_creature, 4696);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1006: // Spider
		CreatePet(player, m_creature, 18467);
		player->CLOSE_GOSSIP_MENU();
		break;
// ============================================            
	case 2001: // Bangalash
		CreatePet(player, m_creature, 731);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 2002: // Tiger - cat
		CreatePet(player, m_creature, 21723); // 772
		player->CLOSE_GOSSIP_MENU();
		break;
	case 2003: // Boar
		CreatePet(player, m_creature, 157); // 1984
		player->CLOSE_GOSSIP_MENU();
		break;
	case 2004: // Crab 
		CreatePet(player, m_creature, 3106); // 
		player->CLOSE_GOSSIP_MENU();
		break;
	case 2005: // Crokolisk
		CreatePet(player, m_creature, 4344); // 
		player->CLOSE_GOSSIP_MENU();
		break;
	case 2006: // Dragonhawk
		CreatePet(player, m_creature, 20749); // 
		player->CLOSE_GOSSIP_MENU();
		break;
	case 2007: // Owl 
		CreatePet(player, m_creature, 22265); // 
		player->CLOSE_GOSSIP_MENU();
		break; 
	case 2008: // Raptor
		CreatePet(player, m_creature, 22052); // 
		player->CLOSE_GOSSIP_MENU();
		break; 
	case 2009: // Talonstrider 
		CreatePet(player, m_creature, 2955); // 
		player->CLOSE_GOSSIP_MENU();
		break; 
	case 2010: // Hyena
		CreatePet(player, m_creature, 5426); // 3425
		player->CLOSE_GOSSIP_MENU();
		break;
	case 2011: // Mountain Lion Prowl 
		CreatePet(player, m_creature, 2406); // 
		player->CLOSE_GOSSIP_MENU();
		break;
	case 2012: // Wolf
		CreatePet(player, m_creature, 20330); // 1131
		player->CLOSE_GOSSIP_MENU();
		break;
// ============================================
	case 3001: // Turtle
		CreatePet(player, m_creature, 14123);
		player->CLOSE_GOSSIP_MENU();
		break;  
	case 3002: // Bear
		CreatePet(player, m_creature, 7443);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 3003: // Gorila
		CreatePet(player, m_creature, 1114);
		player->CLOSE_GOSSIP_MENU();
		break;
	}
	return true;
}

void AddSC_Npc_Beastmaster()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name="npc_beastmaster";
	newscript->pGossipHello = &GossipHello_Npc_Beastmaster;
	newscript->pGossipSelect = &GossipSelect_Npc_Beastmaster;
	newscript->RegisterSelf();
}

/*

player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_turtle:26:26:-15:0|t|r Turtle.", GOSSIP_SENDER_MAIN, 19);
player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_wasp:26:26:-15:0|t|r Wasp.", GOSSIP_SENDER_MAIN, 20);
player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_worm:26:26:-15:0|t|r Worm.", GOSSIP_SENDER_MAIN, 56);  
player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_druid_catform:26:26:-15:0|t|r Loque'nahak.", GOSSIP_SENDER_MAIN, 57);
player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Spell_nature_spiritwolf:26:26:-15:0|t|r Skoll.", GOSSIP_SENDER_MAIN, 58);
player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Spell_shadow_spectralsight:26:26:-15:0|t|r Gondria.", GOSSIP_SENDER_MAIN, 59);
player->ADD_GOSSIP_ITEM(2, "<- Get a New Normal Pet.", GOSSIP_SENDER_MAIN, 100);		
player->ADD_GOSSIP_ITEM(4, LESS, GOSSIP_SENDER_MAIN, 30);
player->ADD_GOSSIP_ITEM(2, MAINMENU, GOSSIP_SENDER_MAIN, 100);
Ability hunter pet netherray
Ability hunter pet owl
Ability hunter pet sporebat
Ability hunter pet vulture
*/