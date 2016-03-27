#include "precompiled.h"
#include "system/system.h"
#include "TemplateMgr.h"

INSTANTIATE_SINGLETON_1(TemplateMgr);

void TemplateMgr::_Load()
{
    QueryResult* result = SD2Database.Query(
                                   "SELECT templateEntry, itemEntry, itemAmount "
                                   " FROM template_item");
    if (result)
    {
        do
        {
            Field* pFields = result->Fetch();

            TemplateItem* pTemp = new TemplateItem;
            uint32 templateEntry  = pFields[0].GetUInt32();
            pTemp->itemEntry      = pFields[1].GetUInt32();
            pTemp->itemAmount     = pFields[2].GetUInt32();

            templateItems[templateEntry].push_back(pTemp);
        }
        while (result->NextRow());

        delete result;
    }
}

void TemplateMgr::AddItems(Player* player, TemplateEntry te)
{
    auto it = templateItems.find(uint32(te));
    if (it != templateItems.end())
    {
        for (auto it2 : it->second)
        {
            uint32 itemEntry = it2->itemEntry;
            uint32 itemAmount = it2->itemAmount;

            player->StoreNewItemInBestSlots(itemEntry, itemAmount);
        }
    }
}
