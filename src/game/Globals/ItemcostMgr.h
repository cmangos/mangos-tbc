#pragma once

struct ItemPrototype;

class ItemCost
{
public:
    ItemCost(uint32 itemid);
    ItemCost(const ItemPrototype* item);
    ~ItemCost();

    uint32 GetItemCost();

private:
    float GetClassModifier();
    float GetLevelModifier();
    float GetQualityModifier();

    const ItemPrototype* item;
};
