#pragma once

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Globals/ObjectMgr.h"
#include "World/World.h"
#include "Database/DatabaseEnv.h"
#include "Entities/Creature.h"

typedef std::multimap<uint8, TrainerSpell> TrainerMap;

class AutoLearnSpells
{
public:
    void LoadTrainerSpells()
    {
        m_trainerspells.clear();

        if (!sWorld.getConfig(CONFIG_BOOL_AUTOLEARNSPELLS))
            return;

        for (uint8 i = CLASS_WARRIOR; i <= CLASS_DRUID; ++i)
        {
            auto result = WorldDatabase.PQuery("SELECT DISTINCT trainertemplateid FROM creature_template WHERE trainerclass = %u AND trainertemplateid != 0", i);

            if (!result)
                continue;

            do
            {
                auto trainerid = result->Fetch()[0].GetUInt32();

                TrainerSpellData const* tSpells = sObjectMgr.GetNpcTrainerTemplateSpells(trainerid);
                if (!tSpells)
                    continue;

                for (auto& j : tSpells->spellList)
                    m_trainerspells.insert(std::make_pair(i, j.second));
            }
            while (result->NextRow());
            delete result;
        }
    }

    TrainerMap::const_iterator Begin(uint8 classid) { return m_trainerspells.lower_bound(classid); }
    TrainerMap::const_iterator End(uint8 classid) { return m_trainerspells.upper_bound(classid); }

private:
    TrainerMap m_trainerspells {};
};
