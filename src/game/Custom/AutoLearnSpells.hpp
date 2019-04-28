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

                auto* clsEntry = sChrClassesStore.LookupEntry(classid);
                if (!clsEntry)
                    continue;

                auto* tSpells = sObjectMgr.GetNpcTrainerTemplateSpells(trainerid);
                if (!tSpells)
                    continue;

                for (auto& j : tSpells->spellList)
                    m_trainerspells.insert(std::make_pair(classid, j.second));
            }
            while (result->NextRow());
            delete result;
            result = nullptr;

            // Add Weapon skills as well
            result = WorldDatabase.PQuery("SELECT trainertemplateid FROM creature_template WHERE trainertype = 2");
            if (!result)
                return;

            do
            {
                auto trainerid = result->Fetch()[0].GetUInt32();

                auto* tSpells = sObjectMgr.GetNpcTrainerTemplateSpells(trainerid);
                if (!tSpells)
                    continue;

                for (auto& j : tSpells->spellList)
                    if (auto* spellproto = sSpellTemplate.LookupEntry<SpellEntry>(j.second.learnedSpell))
                        if (spellproto->Effect[0] == SPELL_EFFECT_WEAPON)
                            for (auto classid = 0; classid < MAX_CLASSES; ++classid)
                                if (sChrClassesStore.LookupEntry(classid))
                                    m_trainerspells.insert(std::make_pair(classid, j.second));
             }
            while (result->NextRow());
            delete result;
            result = nullptr;
    }

    TrainerMap::const_iterator Begin(uint8 classid) { return m_trainerspells.lower_bound(classid); }
    TrainerMap::const_iterator End(uint8 classid) { return m_trainerspells.upper_bound(classid); }

private:
    TrainerMap m_trainerspells {};
};
