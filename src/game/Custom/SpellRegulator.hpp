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
        SpellRegulationMap.clear();

        try {
            auto result = WorldDatabase.PQuery("SELECT spellid, modifier FROM custom_spellregulator");

            do
            {
                auto fields = result->Fetch();
                uint32 spellid = fields[0].GetUInt32();
                float modifier = fields[1].GetFloat();

                if (SpellRegulationMap.find(spellid) == SpellRegulationMap.end())
                    SpellRegulationMap.insert(std::make_pair(spellid, modifier));

                auto chainresult = WorldDatabase.PQuery("SELECT spell_id FROM spell_chain WHERE first_spell = (SELECT first_spell FROM spell_chain WHERE spell_id = '%u')", spellid);

                do
                {
                    auto chainspellid = chainresult->Fetch()[0].GetUInt32();

                    if (SpellRegulationMap.find(chainspellid) == SpellRegulationMap.end())
                        SpellRegulationMap.insert(std::make_pair(chainspellid, modifier));
                }
                while (chainresult->NextRow());
            }
            while (result->NextRow());

            sLog.outString("Loaded spellregulator data");
        } catch (std::exception) {
            sLog.outError("Failed to load spellregulator from database");
        }
    }

//private:
    std::unordered_map<uint32, float> SpellRegulationMap {};
};
