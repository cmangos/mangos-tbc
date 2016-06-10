#include "SpellScriptFactory.h"

ScriptedSpellFactory* spellFactories[MAX_TBC_SPELL_ID];

void AddSpellFactories()
{
    AddSpellFactoriesTBC();
};

void DestroySpellFactories()
{
    for (int i = 0; i < MAX_TBC_SPELL_ID; i++)
    {
        delete spellFactories[i];
    }
}