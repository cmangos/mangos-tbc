#include "SpellScriptFactory.h"

extern ScriptedSpellFactory* spellFactories[MAX_TBC_SPELL_ID];

enum
{
    SPELL_MENTAL_INTERFERENCE = 38915
};

/*Spell 38915*/
struct MentalInterference : public Spell
{
    MentalInterference(Unit* caster, SpellEntry const* info, bool triggered, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr)
        : Spell(caster, info, triggered, originalCasterGUID, triggeredBy)
    {

    }

    SpellCastResult CustomCheckCast(bool strict) override
    {
        if (ObjectGuid target = m_caster->GetTargetGuid())
        {
            if (!(target.GetEntry() == 16943 || target.GetEntry() == 20928))  // Mental Interference can be cast only on these two targets
                return SPELL_FAILED_BAD_TARGETS;
        }

        return SPELL_CAST_OK;
    }
};

struct MentalInterferenceFactory : public ScriptedSpellFactory
{
    virtual Spell* operator ()(Unit* caster, SpellEntry const* info, bool triggered, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr) override
    {
        return new MentalInterference(caster, info, triggered, originalCasterGUID, triggeredBy);
    }
};

enum
{
    SPELL_DETONATE_TELEPORTER = 38920
};

/*Spell 38920*/
struct DetonateTeleporter : public Spell
{
    DetonateTeleporter(Unit* caster, SpellEntry const* info, bool triggered, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr)
        : Spell(caster, info, triggered, originalCasterGUID, triggeredBy)
    {

    }

    void EffectScriptEffect(SpellEffectIndex eff_idx) override
    {
        if (Player* player = dynamic_cast<Player*>(m_caster->GetCharmer()))
        {
            player->RewardPlayerAndGroupAtEvent(unitTarget->GetEntry(), unitTarget);
        }
    }
};

struct DetonateTeleporterFactory : public ScriptedSpellFactory
{
    virtual Spell* operator ()(Unit* caster, SpellEntry const* info, bool triggered, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr) override
    {
        return new DetonateTeleporter(caster, info, triggered, originalCasterGUID, triggeredBy);
    }
};

void AddSpellFactoriesTBC()
{
    spellFactories[SPELL_MENTAL_INTERFERENCE] = new MentalInterferenceFactory();
    spellFactories[SPELL_DETONATE_TELEPORTER] = new DetonateTeleporterFactory();
}

