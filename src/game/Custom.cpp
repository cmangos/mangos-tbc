#include "Custom.h"
#include "ObjectMgr.h"

Custom::Custom()
{
}

Custom::~Custom()
{
}

uint32 Custom::GetAutoItemPrice(uint32 itemid)
{
    ItemPrototype const* item = sObjectMgr.GetItemPrototype(itemid);

    float price = item->ItemLevel;

    switch (item->Quality)
    {
    case 0: price *= 1.f; break;
    case 1: price *= 1.1f; break;
    case 2: price *= 1.2f; break;
    case 3: price *= 1.3f; break;
    case 4: price *= 1.4f; break;
    case 5: price *= 1.5f; break;

    default: price *= 1.f; break;
    }

    switch (item->InventoryType)
    {
    case INVTYPE_NON_EQUIP:
    case INVTYPE_HEAD:
    case INVTYPE_NECK:
    case INVTYPE_SHOULDERS:
    case INVTYPE_BODY:
    case INVTYPE_CHEST:
    case INVTYPE_WAIST:
    case INVTYPE_LEGS:
    case INVTYPE_FEET:
    case INVTYPE_WRISTS:
    case INVTYPE_HANDS:
    case INVTYPE_FINGER:
    case INVTYPE_TRINKET:
    case INVTYPE_WEAPON:
    case INVTYPE_SHIELD:
    case INVTYPE_RANGED:
    case INVTYPE_CLOAK:
    case INVTYPE_2HWEAPON:
    case INVTYPE_BAG:
    case INVTYPE_TABARD:
    case INVTYPE_ROBE:
    case INVTYPE_WEAPONMAINHAND:
    case INVTYPE_WEAPONOFFHAND:
    case INVTYPE_HOLDABLE:
    case INVTYPE_AMMO:
    case INVTYPE_THROWN:
    case INVTYPE_RANGEDRIGHT:
    case INVTYPE_QUIVER:
    case INVTYPE_RELIC:
    default:
        break;
    }

    return floor(price);
}
