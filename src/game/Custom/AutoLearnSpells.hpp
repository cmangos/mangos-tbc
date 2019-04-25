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

            auto result = WorldDatabase.PQuery("SELECT DISTINCT trainertemplateid, trainerclass FROM creature_template WHERE trainertemplateid != 0");

            if (!result)
                return;

            do
            {
                auto trainerid = result->Fetch()[0].GetUInt32();
                auto classid   = result->Fetch()[1].GetUInt32();

                TrainerSpellData const* tSpells = sObjectMgr.GetNpcTrainerTemplateSpells(trainerid);
                if (!tSpells)
                    continue;

                for (auto& j : tSpells->spellList)
                    m_trainerspells.insert(std::make_pair(classid, j.second));
            }
            while (result->NextRow());
            delete result;
    }

    TrainerMap::const_iterator Begin(uint8 classid) { return m_trainerspells.lower_bound(classid); }
    TrainerMap::const_iterator End(uint8 classid) { return m_trainerspells.upper_bound(classid); }

private:
    TrainerMap m_trainerspells {};
};
