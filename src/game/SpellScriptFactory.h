#include "Spell.h"

/*Dummy class for spell creation*/
struct ScriptedSpellFactory
{
    virtual Spell* operator ()(Unit* caster, SpellEntry const* info, bool triggered, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr) = 0;
};

void AddSpellFactoriesTBC();

void AddSpellFactories();

void DestroySpellFactories();