#include "SpellScriptFactory.h"

std::function<Spell*(Unit*, SpellEntry const*, bool, ObjectGuid, SpellEntry const*)> spellFactories[MAX_TBC_SPELL_ID];

void AddSpellFactories()
{
    AddSpellFactoriesTBC();
};

void DestroySpellFactories()
{
    delete spellFactories;
}