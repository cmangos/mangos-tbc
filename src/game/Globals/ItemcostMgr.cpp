#include "ItemCostMgr.h"

ItemCost::ItemCost(uint32 itemid)
{
    item = sObjectMgr.GetItemPrototype(itemid);
}

ItemCost::ItemCost(const ItemPrototype* item)
{
    item = item;
}

ItemCost::~ItemCost()
{
}

uint32 ItemCost::GetItemCost()
{
    float cost = 10000;

    cost *= GetClassModifier();
    cost *= GetLevelModifier();

    return cost;
}

float ItemCost::GetClassModifier()
{
    float mod = 1.f;

    switch (item->Class)
    {
    case ITEM_CLASS_WEAPON:     mod *= 1.5f; break;
    case ITEM_CLASS_ARMOR:      mod *= 1.2f; break;
    case ITEM_CLASS_PROJECTILE: mod *= 0.1f; break;
    case ITEM_CLASS_CONSUMABLE: mod *= 0.1f; break;
    }

    return mod;
}

float ItemCost::GetLevelModifier()
{
    float mod = 1.f;

    mod *= item->ItemLevel;

    return mod;
}

float ItemCost::GetQualityModifier()
{
    float mod = 1.f;

    mod *= item->Quality;

    return mod;
}