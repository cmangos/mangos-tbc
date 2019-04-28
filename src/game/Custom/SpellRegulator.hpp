#pragma once

#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "Log.h"
#include "Spells/SpellMgr.h"

#include <unordered_map>

class SpellRegulator
{
public:
    void RegulateSpell(uint32 spellid, int32& effect)
    {
        if (SpellRegulationMap.find(spellid) != SpellRegulationMap.end())
            effect *= SpellRegulationMap[spellid];
    }

    void RegulateSpell(uint32 spellid, uint32& effect)
    {
        if (SpellRegulationMap.find(spellid) != SpellRegulationMap.end())
            effect *= SpellRegulationMap[spellid];
    }

    void LoadRegulators()
    {
        // TODO: Anyone great with SQL who can unnest these queries?

        SpellRegulationMap.clear();

        auto result = WorldDatabase.PQuery("SELECT spellid, modifier, allranks FROM custom_spellregulator");

        if (!result)
        {
            sLog.outErrorDb("Couldn't load custom_spellregulator table");
            return;
        }

        do
        {
            auto fields = result->Fetch();
            uint32 spellid = fields[0].GetUInt32();
            float modifier = fields[1].GetFloat();
            bool allranks = fields[2].GetBool();

            if (!allranks)
            {
                SpellRegulationMap.insert(std::make_pair(spellid, modifier));
                continue;
            }

            auto spellmap = sSpellMgr.GetSpellChainNext();

            for (auto i = spellmap.lower_bound(spellid); i != spellmap.upper_bound(spellid); ++i)
               if (SpellRegulationMap.find(i->second) == SpellRegulationMap.end())
                    SpellRegulationMap.insert(std::make_pair(i->second, modifier));
        }
        while (result->NextRow());
        delete result;

        sLog.outString("Loaded spellregulator data");
    }

private:
    std::unordered_map<uint32, float> SpellRegulationMap {};
};
