/**
 *
 * @File : item_increaseskill.cpp
 * @Authors : yukozh
 * @Date : 10/27/2019
 *
 **/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"
#include "Pomelo/DBConfigMgr.h"
#include "Pomelo/CustomCurrencyMgr.h"
#include "Chat/Chat.h"
#include "World/World.h"

#define INCREASE_SKILL_ITEM_MINING        83550
#define INCREASE_SKILL_ITEM_ALCHEMY       83551
#define INCREASE_SKILL_ITEM_BLACKSMITHING 83552
#define INCREASE_SKILL_ITEM_TAILORING     83553
#define INCREASE_SKILL_ITEM_LETHERWORKING 83554
#define INCREASE_SKILL_ITEM_ENCHANTMENT   83555
#define INCREASE_SKILL_ITEM_JEWELCRAFTING 83556
#define INCREASE_SKILL_ITEM_ENGINEERING   83557
#define INCREASE_SKILL_ITEM_HERBALISM     83558
#define INCREASE_SKILL_ITEM_SKINNING      83559
#define INCREASE_SKILL_ITEM_FIRSTAID      83560
#define INCREASE_SKILL_ITEM_COOKING       83561
#define INCREASE_SKILL_ITEM_FISHING       83562

bool IncreaseSkillItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    uint32 item = pItem->GetProto()->ItemId;
    bool result = false;
    if (item == INCREASE_SKILL_ITEM_MINING)
    {
        result = pPlayer->UpdateSkillProMax(186);
        if (result)
        {
            pPlayer->learnSpell(2575, false);
            pPlayer->learnSpell(2576, false);
            pPlayer->learnSpell(3564, false);
            pPlayer->learnSpell(10248, false);
            pPlayer->learnSpell(29354, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_ALCHEMY)
    {
        result = pPlayer->UpdateSkillProMax(171);
        if (result)
        {
            pPlayer->learnSpell(2259, false);
            pPlayer->learnSpell(3101, false);
            pPlayer->learnSpell(3464, false);
            pPlayer->learnSpell(11611, false);
            pPlayer->learnSpell(28596, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_BLACKSMITHING)
    {
        result = pPlayer->UpdateSkillProMax(164);
        if (result)
        {
            pPlayer->learnSpell(2018, false);
            pPlayer->learnSpell(3100, false);
            pPlayer->learnSpell(3538, false);
            pPlayer->learnSpell(9785, false);
            pPlayer->learnSpell(29844, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_TAILORING)
    {
        result = pPlayer->UpdateSkillProMax(197);
        if (result) 
        {
            pPlayer->learnSpell(3908, false);
            pPlayer->learnSpell(3909, false);
            pPlayer->learnSpell(3910, false);
            pPlayer->learnSpell(12180, false);
            pPlayer->learnSpell(26790, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_LETHERWORKING)
    {
        result = pPlayer->UpdateSkillProMax(165);
        if (result)
        {
            pPlayer->learnSpell(2108, false);
            pPlayer->learnSpell(3104, false);
            pPlayer->learnSpell(3811, false);
            pPlayer->learnSpell(10662, false);
            pPlayer->learnSpell(32549, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_ENCHANTMENT)
    {
        result = pPlayer->UpdateSkillProMax(333);
        if (result)
        {
            pPlayer->learnSpell(7411, false);
            pPlayer->learnSpell(7412, false);
            pPlayer->learnSpell(7413, false);
            pPlayer->learnSpell(13920, false);
            pPlayer->learnSpell(28029, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_JEWELCRAFTING)
    {
        result = pPlayer->UpdateSkillProMax(755);
        if (result)
        {
            pPlayer->learnSpell(25229, false);
            pPlayer->learnSpell(25230, false);
            pPlayer->learnSpell(28894, false);
            pPlayer->learnSpell(28895, false);
            pPlayer->learnSpell(28897, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_ENGINEERING)
    {
        result = pPlayer->UpdateSkillProMax(202);
        if (result)
        {
            pPlayer->learnSpell(4036, false);
            pPlayer->learnSpell(4037, false);
            pPlayer->learnSpell(4038, false);
            pPlayer->learnSpell(12656, false);
            pPlayer->learnSpell(30350, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_HERBALISM)
    {
        result = pPlayer->UpdateSkillProMax(182);
        if (result)
        {
            pPlayer->learnSpell(2366, false);
            pPlayer->learnSpell(2368, false);
            pPlayer->learnSpell(3570, false);
            pPlayer->learnSpell(11993, false);
            pPlayer->learnSpell(28695, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_SKINNING)
    {
        result = pPlayer->UpdateSkillProMax(393);
        if (result)
        {
            pPlayer->learnSpell(8613, false);
            pPlayer->learnSpell(8617, false);
            pPlayer->learnSpell(8618, false);
            pPlayer->learnSpell(10768, false);
            pPlayer->learnSpell(32678, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_FIRSTAID)
    {
        result = pPlayer->UpdateSkillProMax(129);
        if (result)
        {
            pPlayer->learnSpell(3273, false);
            pPlayer->learnSpell(3274, false);
            pPlayer->learnSpell(7924, false);
            pPlayer->learnSpell(10846, false);
            pPlayer->learnSpell(27028, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_COOKING)
    {
        result = pPlayer->UpdateSkillProMax(185);
        if (result)
        {
            pPlayer->learnSpell(2550, false);
            pPlayer->learnSpell(3102, false);
            pPlayer->learnSpell(3413, false);
            pPlayer->learnSpell(18260, false);
            pPlayer->learnSpell(33359, false);
        }
    }
    else if (item == INCREASE_SKILL_ITEM_FISHING)
    {
        result = pPlayer->UpdateSkillProMax(356);
        if (result)
        {
            pPlayer->learnSpell(7620, false);
            pPlayer->learnSpell(7731, false);
            pPlayer->learnSpell(7732, false);
            pPlayer->learnSpell(18248, false);
            pPlayer->learnSpell(33095, false);
        }
    }
    else
    {
        return false;
    }

    if (result)
        pPlayer->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
    else
        pPlayer->GetSession()->SendNotification(LANG_CANNOT_USE_INC_SKILL_ITEM);

    return true;
}

void AddSC_item_increaseskill()
{
	// Register script
    Script *newscript;
    newscript = new Script;
    newscript->Name="item_increaseskill";
	newscript->pItemUse = &IncreaseSkillItemUse;
    newscript->RegisterSelf();
}
