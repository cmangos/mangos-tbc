/* ScriptData 
SDName: npc_barber
SD%Complete: 100
SDComment: Barber
SDCategory: Custom
Authors: TC devs, Morenn, Casso
Year: 2010
EndScriptData */

#include "precompiled.h"
#define BET 500000

uint32 hairstyle;
uint32 haircolor;
uint32 facialfeature;
bool   helmetShown;

typedef struct maxStyles_struct {
    uint8 maxMale;
    uint8 maxFemale;
} maxStyles_t;

maxStyles_t maxHairStyles[MAX_RACES] =
{
    {0,0},  //                        0
    {11,18},// RACE_HUMAN           = 1,
    {6,6},  //  RACE_ORC            = 2,
    {10,13},// RACE_DWARF           = 3,
    {6,6},  // RACE_NIGHTELF        = 4,
    {10,9}, // RACE_UNDEAD_PLAYER   = 5,
    {7,6},  //  RACE_TAUREN         = 6,
    {6,6},  // RACE_GNOME           = 7,
    {5,4},  // RACE_TROLL           = 8,
    {0,0},  // RACE_GOBLIN          = 9,
    {9,13}, //  RACE_BLOODELF       = 10,
    {7,10}, //  RACE_DRAENEI        = 11
};

uint8 maxHairColor[MAX_RACES] =
{
    0,  //                        0
    9,  // RACE_HUMAN           = 1,
    7,  //  RACE_ORC            = 2,
    9,  // RACE_DWARF           = 3,
    7,  // RACE_NIGHTELF        = 4,
    9,  // RACE_UNDEAD_PLAYER   = 5,
    2,  //  RACE_TAUREN         = 6,
    8,  // RACE_GNOME           = 7,
    9,  // RACE_TROLL           = 8,
    0,  // RACE_GOBLIN          = 9,
    9,  //  RACE_BLOODELF       = 10,
    6,  //  RACE_DRAENEI        = 11
};

maxStyles_t maxFacialFeatures[MAX_RACES] =
{
    {0,0},  //                        0
    {8,6},  // RACE_HUMAN           = 1,
    {10,6}, // RACE_ORC             = 2,
    {10,5}, // RACE_DWARF           = 3,
    {5,9},  // RACE_NIGHTELF        = 4,
    {16,7}, // RACE_UNDEAD_PLAYER   = 5,
    {6,4},  // RACE_TAUREN          = 6,
    {7,6},  // RACE_GNOME           = 7,
    {10,5}, // RACE_TROLL           = 8,
    {0,0},  // RACE_GOBLIN          = 9,
    {10,9}, // RACE_BLOODELF        = 10,
    {7,6},  // RACE_DRAENEI         = 11
};


void SelectFacialFeature(Player *player, int change);
void SelectHairColor(Player *player, int change);
void SelectHairStyle(Player *player, int change);

#define GOSSIP_SENDER_OPTION 50
#define GOSSIP_SENDER_SUBOPTION 51

bool GossipHello_barber(Player *player, Creature *_Creature)
{
    int32 text = 0;
    bool sitting = true;
    
    //if (player->IsStandState())
    //    sitting = false;

    // Select a gossip text
    if(!sitting)
        text = player->GetTeam() == ALLIANCE ? 60011 : 60000;
    else switch (player->getRace())
    {
        case RACE_HUMAN:
            text = player->getGender() == GENDER_FEMALE ? 60013 : 60012;
            break;
        case RACE_ORC:
            text = player->getGender() == GENDER_FEMALE ? 60002 : 60001;
            break;
        case RACE_DWARF:
            text = player->getGender() == GENDER_FEMALE ? 60015 : 60014;
            break;
        case RACE_NIGHTELF:
            text = player->getGender() == GENDER_FEMALE ? 60019 : 60018;
            break;
        case RACE_UNDEAD:
            text = player->getGender() == GENDER_FEMALE ? 60008 : 60007;
            break;
        case RACE_TAUREN:
            text = player->getGender() == GENDER_FEMALE ? 60006 : 60005;
            break;
        case RACE_GNOME:
            text = player->getGender() == GENDER_FEMALE ? 60017 : 60016;
            break;        
        case RACE_DRAENEI:
            text = player->getGender() == GENDER_FEMALE ? 60021 : 60020;
            break;
        case RACE_TROLL:
            text = player->getGender() == GENDER_FEMALE ? 60004 : 60003;
            break;
        case RACE_BLOODELF:
            text = player->getGender() == GENDER_FEMALE ? 60010 : 60009;
            break;
    }
    // store values to restore if player choose to cancel
    hairstyle = player->GetByteValue(PLAYER_BYTES, 2); 
    haircolor = player->GetByteValue(PLAYER_BYTES, 3); 
    facialfeature = player->GetByteValue(PLAYER_BYTES_2, 0); 
    if (sitting)
    {
        // 1xDT (23580) 5xHT (10663)
        //if (player->HasItemCount(23580,1,false) && player->HasItemCount(10663,5,false))
		if(player->GetMoney() >= BET) 
		     player->ADD_GOSSIP_ITEM(0, "I want to change my appearance!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        else 
            player->ADD_GOSSIP_ITEM(0, "Sorry you don't have enough money!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);


    }
    player->PlayerTalkClass->SendGossipMenu(text, _Creature->GetObjectGuid());
    return true;
}

void ChangeEffect(Player *player)
{
    // First Send update to player, so most recent datas are up
    player->SendCreateUpdateToPlayer(player); 

    // Force client to reload this player, so changes are visible
    WorldPacket data(SMSG_FORCE_DISPLAY_UPDATE, 8);
    data << player->GetObjectGuid();
    player->SendMessageToSet(&data,true);

    // Do some visual effect (Vanish visual spell)
    //player->CastSpell(player,24222,true);
}

void SelectHairStyle(Player *player, int change)
{
    uint8 max=maxHairStyles[player->getRace()].maxMale;
    if (player->getGender() == GENDER_FEMALE)
        max=maxHairStyles[player->getRace()].maxFemale;

    int current = player->GetByteValue(PLAYER_BYTES, 2);

    current += change;

    if (current > max)
        current = 0;
    else if (current < 0)
        current = max;

    player->SetByteValue(PLAYER_BYTES, 2, current);
    ChangeEffect(player);
}

void SelectHairColor(Player *player, int change)
{
    uint8 max=maxHairColor[player->getRace()];
    int current = player->GetByteValue(PLAYER_BYTES, 3);

    current += change;

    if (current > max)
        current = 0;
    else if (current < 0)
        current = max;

    player->SetByteValue(PLAYER_BYTES, 3, current);
    ChangeEffect(player);
}

void SelectFacialFeature(Player *player, int change)
{
    uint8 max=maxFacialFeatures[player->getRace()].maxMale;
    if (player->getGender() == GENDER_FEMALE)
        max=maxFacialFeatures[player->getRace()].maxFemale;

    int current = player->GetByteValue(PLAYER_BYTES_2, 0); 

    current += change;

    if (current > max)
        current = 0;
    else if (current < 0)
        current = max;

    player->SetByteValue(PLAYER_BYTES_2, 0, current);
    ChangeEffect(player);
}

bool GossipSelect_barber(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    char const* FeatureGossipMenu = " I want to change my beard.";
    switch (player->getRace())
    {
    case RACE_HUMAN:
        if (player->getGender() == GENDER_FEMALE)
            FeatureGossipMenu = " I want to change my priercing";
        break;
    case RACE_ORC:
        if (player->getGender() == GENDER_FEMALE)
            FeatureGossipMenu = " I want to change my priercing";
        break;
    case RACE_DWARF:
        if (player->getGender() == GENDER_FEMALE)
            FeatureGossipMenu = " I want to change my earrings.";
        break;
    case RACE_NIGHTELF:
        if (player->getGender() == GENDER_FEMALE)
            FeatureGossipMenu = "I want to change my face marks.";
        break;
    case RACE_UNDEAD:
        FeatureGossipMenu = "I want to change my face.";
        break;
    case RACE_TAUREN:
        if (player->getGender() == GENDER_FEMALE)
            FeatureGossipMenu = "I want to change my hair.";
        break;
    case RACE_GNOME:
        if (player->getGender() == GENDER_FEMALE)
            FeatureGossipMenu = " I want to change my earrings.";
        break;
    case RACE_TROLL:
        FeatureGossipMenu = " I want to change my tusks.";
        break;
    case RACE_BLOODELF:
        if (player->getGender() == GENDER_FEMALE)
            FeatureGossipMenu = " I want to change my earrings.";
        break;
    case RACE_DRAENEI:
        player->getGender() == GENDER_FEMALE ? FeatureGossipMenu = " I want to change my horns." : FeatureGossipMenu = " I want to change my face tentacles.";
        break;
    }
    // MAP
    // 1 - main menu
    // 2 - next hair style
    // 3 - prev hair style
    // 4 - next hair color
    // 5 - prev hair color
    // 6 - next facial feature
    // 7 - prev facial feature
    // 8 - not enought gold, or other close

    switch (action)
    {
        // After player requested the action
    case GOSSIP_ACTION_INFO_DEF+1:   
        if (sender == GOSSIP_SENDER_MAIN)
        {
			// if (!player->HasItemCount(23580,1,false) || !player->HasItemCount(10663,5,false))
			if(player->GetMoney() < BET) 
            {
                player->PlayerTalkClass->CloseGossip();
                break;
            }

			player->ModifyMoney(-1*BET);

            //player->DestroyItemCount(23580, 1, true, false);
            //player->DestroyItemCount(10663, 5, true, false);

            // Skrytie helmy
            if (!player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_HIDE_HELM))
                player->ToggleFlag(PLAYER_FLAGS, PLAYER_FLAGS_HIDE_HELM);
            
        }
        player->ADD_GOSSIP_ITEM(0, " I want to change my hairstyle.", GOSSIP_SENDER_OPTION , GOSSIP_ACTION_INFO_DEF + 2);
        player->ADD_GOSSIP_ITEM(0, " I want to change my hair color.", GOSSIP_SENDER_OPTION , GOSSIP_ACTION_INFO_DEF + 4);
        player->ADD_GOSSIP_ITEM(0, FeatureGossipMenu, GOSSIP_SENDER_OPTION , GOSSIP_ACTION_INFO_DEF + 6);
        player->PlayerTalkClass->SendGossipMenu(60023, _Creature->GetObjectGuid());
        break;
        // hair style
        // next - increase hair style
    case GOSSIP_ACTION_INFO_DEF+2:
        if (sender == GOSSIP_SENDER_SUBOPTION)
            SelectHairStyle(player,1);
        // previous - decrease it
    case GOSSIP_ACTION_INFO_DEF+3:
        if (action == GOSSIP_ACTION_INFO_DEF+3 && sender == GOSSIP_SENDER_SUBOPTION)
            SelectHairStyle(player,-1);
        // choose options again
        player->ADD_GOSSIP_ITEM(0, "Next!", GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 2);
        player->ADD_GOSSIP_ITEM(0, "Previous one!!", GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 3);
        player->ADD_GOSSIP_ITEM(0, "I want this.", GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 1);
        player->PlayerTalkClass->SendGossipMenu(60024, _Creature->GetObjectGuid());
        break;

        // hair color
        // next - increase hair color
    case GOSSIP_ACTION_INFO_DEF+4:
        if (sender == GOSSIP_SENDER_SUBOPTION)
            SelectHairColor(player,1);
        // previous - decrease hair color
    case GOSSIP_ACTION_INFO_DEF+5:
        if (action == GOSSIP_ACTION_INFO_DEF+5 && sender == GOSSIP_SENDER_SUBOPTION)
            SelectHairColor(player,-1);
        // choose options again
        player->ADD_GOSSIP_ITEM(0, "Next!", GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 4);
        player->ADD_GOSSIP_ITEM(0, "Previous one!",GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 5);
        player->ADD_GOSSIP_ITEM(0, "I want this.", GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 1);
        player->PlayerTalkClass->SendGossipMenu(60024, _Creature->GetObjectGuid());
        break;

        // facial feature
        // next - increase facial style
    case GOSSIP_ACTION_INFO_DEF+6:
        if (sender == GOSSIP_SENDER_SUBOPTION)
            SelectFacialFeature(player,1);
        // previous - decrease it
    case GOSSIP_ACTION_INFO_DEF+7:
        if (action == GOSSIP_ACTION_INFO_DEF+7 && sender == GOSSIP_SENDER_SUBOPTION)
            SelectFacialFeature(player,-1);
        // choose options again
        player->ADD_GOSSIP_ITEM(0, "Next!", GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 6);
        player->ADD_GOSSIP_ITEM(0, "Previous one!", GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 7);
        player->ADD_GOSSIP_ITEM(0, "I want this.", GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 1);
        player->PlayerTalkClass->SendGossipMenu(60024, _Creature->GetObjectGuid());
        break;

        // cannot affort
    case GOSSIP_ACTION_INFO_DEF+8:
        player->PlayerTalkClass->CloseGossip();
        break;

/*		// OK zaplat
    case GOSSIP_ACTION_INFO_DEF+8:
		// if (!player->HasItemCount(23580,1,false) || !player->HasItemCount(10663,5,false))
			if(player->GetMoney() < BET) 
            {
                player->PlayerTalkClass->CloseGossip();
                break;
            }

			player->ModifyMoney(-1*BET);

            //player->DestroyItemCount(23580, 1, true, false);
            //player->DestroyItemCount(10663, 5, true, false);
			player->ADD_GOSSIP_ITEM(0, "Another change.", GOSSIP_SENDER_SUBOPTION , GOSSIP_ACTION_INFO_DEF + 1);
			player->SEND_GOSSIP_MENU(60024, _Creature->GetGUID());
		break;
*/
    }
    return true;
}


void AddSC_barber()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="npc_barber";
    newscript->pGossipHello = &GossipHello_barber;
    newscript->pGossipSelect = &GossipSelect_barber;
    newscript->RegisterSelf();
}
