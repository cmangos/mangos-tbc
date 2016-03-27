#ifndef _TEMPLATE_MGR
#define _TEMPLATE_MGR

#include "precompiled.h"

enum TemplateEntry {
};

struct TemplateItem
{
    uint32 itemEntry;
    uint32 itemAmount;
};

class TemplateMgr
{
public:
    void _Load();
    void AddItems(Player* player, TemplateEntry te);

private:
    std::map<uint32, std::vector<TemplateItem*>> templateItems;
};

#define sTemplateMgr MaNGOS::Singleton<TemplateMgr>::Instance()

#endif
