#include "Spell.h"

extern std::function<Spell*(Unit*, SpellEntry const*, bool, ObjectGuid, SpellEntry const*)> spellFactories[MAX_TBC_SPELL_ID];

void AddSpellFactoriesTBC();

void AddSpellFactories();

void DestroySpellFactories();