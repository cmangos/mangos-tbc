#include "SpellScriptFactory.h"

/*Spell 34063*/
enum
{
    SPELL_SOUL_MIRROR = 34063
};

struct SoulMirror : public Spell
{
    SoulMirror(Unit* caster, SpellEntry const* info, bool triggered, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr)
        : Spell(caster, info, triggered, originalCasterGUID, triggeredBy) {}

    void EffectDummy(SpellEffectIndex eff_idx) override
    {
        if (!unitTarget)
            return;

        m_caster->SummonCreature(19480, unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(), unitTarget->GetOrientation(), TEMPSUMMON_TIMED_OOC_OR_DEAD_DESPAWN, 30000);
        unitTarget->DealDamage(unitTarget, unitTarget->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
    }
};

Spell* SoulMirrorFactory(Unit* caster, SpellEntry const* info, bool triggered, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr)
{
    return new SoulMirror(caster, info, triggered, originalCasterGUID, triggeredBy);
}

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

    SpellCastResult CheckCast(bool strict) override
    {
        SpellCastResult result = Spell::CheckCast(strict);
        if (result != SPELL_CAST_OK)
            return result;

        if (ObjectGuid target = m_caster->GetTargetGuid())
        {
            if (!(target.GetEntry() == 16943 || target.GetEntry() == 20928))  // Mental Interference can be cast only on these two targets
                return SPELL_FAILED_BAD_TARGETS;
        }

        return SPELL_CAST_OK;
    }
};


Spell* MentalInterferenceFactory(Unit* caster, SpellEntry const* info, bool triggered, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr)
{
    return new MentalInterference(caster, info, triggered, originalCasterGUID, triggeredBy);
}

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

Spell* DetonateTeleporterFactory(Unit* caster, SpellEntry const* info, bool triggered, ObjectGuid originalCasterGUID = ObjectGuid(), SpellEntry const* triggeredBy = nullptr)
{
    return new DetonateTeleporter(caster, info, triggered, originalCasterGUID, triggeredBy);
}

void AddSpellFactoriesTBC()
{
    spellFactories[SPELL_SOUL_MIRROR] = SoulMirrorFactory;
    spellFactories[SPELL_MENTAL_INTERFERENCE] = MentalInterferenceFactory;
    spellFactories[SPELL_DETONATE_TELEPORTER] = DetonateTeleporterFactory;
}

