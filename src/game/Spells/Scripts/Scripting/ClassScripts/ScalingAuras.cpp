/*
* This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "Spells/Scripts/SpellScript.h"
#include "Spells/SpellAuras.h"

enum
{
    SPELL_PET_RESISTANCE = 37386,
    SPELL_INCREASED_ATTACK_POWER = 38297,
};

struct HunterPetScaling1 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // stamina
                if (Unit* owner = caster->GetOwner())
                {
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                    if (owner->HasAura(SPELL_INCREASED_ATTACK_POWER))
                        value += 52;
                }
                break;
            case EFFECT_INDEX_1: // attack power
                if (Unit* owner = caster->GetOwner())
                {
                    value = owner->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.25f;
                    if (owner->HasAura(SPELL_INCREASED_ATTACK_POWER))
                        value += 70;
                }
                break;
            case EFFECT_INDEX_2: // spell power
                if (Unit* owner = caster->GetOwner())
                    value = owner->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.125f;
                break;
        }
        return value;
    }
};

struct HunterPetScaling2 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_FIRE) * 0.4f);
                break;
            case EFFECT_INDEX_1: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_FROST) * 0.4f);
                break;
            case EFFECT_INDEX_2: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_NATURE) * 0.4f);
                break;
        }
        return value;
    }
};

struct HunterPetScaling3 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_SHADOW) * 0.4f);
                break;
            case EFFECT_INDEX_1: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_ARCANE) * 0.4f);
                break;
            case EFFECT_INDEX_2: // armor
                if (Unit* owner = caster->GetOwner())
                {
                    value = owner->GetArmor() * 0.35f;
                    if (owner->HasAura(SPELL_INCREASED_ATTACK_POWER))
                        value += 490;
                }
                break;
        }
        return value;
    }
};

struct WarlockPetScaling1 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // stamina
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // attack power
                if (Unit* owner = caster->GetOwner())
                {
                    if (owner->IsPlayer())
                    {
                        int32 fire = int32(owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_FIRE)) - owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + SPELL_SCHOOL_FIRE);
                        int32 shadow = int32(owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW)) - owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + SPELL_SCHOOL_SHADOW);
                        int32 maximum = (fire > shadow) ? fire : shadow;
                        if (maximum < 0)
                            maximum = 0;
                        value = maximum * 0.57f;
                    }
                }
                break;
            case EFFECT_INDEX_2: // spell power
                if (Unit* owner = caster->GetOwner())
                {
                    if (owner->IsPlayer())
                    {
                        int32 fire = int32(owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_FIRE)) - owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + SPELL_SCHOOL_FIRE);
                        int32 shadow = int32(owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW)) - owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + SPELL_SCHOOL_SHADOW);
                        int32 maximum = (fire > shadow) ? fire : shadow;
                        if (maximum < 0)
                            maximum = 0;
                        value = maximum * 0.15f;
                    }
                }
                break;
        }
        return value;
    }
};

struct WarlockPetScaling2 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // intelect
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // armor
                if (Unit* owner = caster->GetOwner())
                    value = owner->GetArmor() * 0.35f;
                break;
            case EFFECT_INDEX_2: // resistance
                if (Unit* owner = caster->GetOwner())
                {
                    value = (owner->GetResistance(SPELL_SCHOOL_FIRE) * 0.4f);
                    if (owner->HasAura(SPELL_PET_RESISTANCE))
                        value += 130;
                }
                break;
        }
        return value;
    }
};

struct WarlockPetScaling3 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                if (Unit* owner = caster->GetOwner())
                {
                    value = (owner->GetResistance(SPELL_SCHOOL_FROST) * 0.4f);
                    if (owner->HasAura(SPELL_PET_RESISTANCE))
                        value += 130;
                }
                break;
            case EFFECT_INDEX_1: // resistance
                if (Unit* owner = caster->GetOwner())
                {
                    value = (owner->GetResistance(SPELL_SCHOOL_ARCANE) * 0.4f);
                    if (owner->HasAura(SPELL_PET_RESISTANCE))
                        value += 130;
                }
                break;
            case EFFECT_INDEX_2: // resistance
                if (Unit* owner = caster->GetOwner())
                {
                    value = (owner->GetResistance(SPELL_SCHOOL_NATURE) * 0.4f);
                    if (owner->HasAura(SPELL_PET_RESISTANCE))
                        value += 130;
                }
                break;
        }
        return value;
    }
};

struct WarlockPetScaling4 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                if (Unit* owner = caster->GetOwner())
                {
                    value = (owner->GetResistance(SPELL_SCHOOL_SHADOW) * 0.4f);
                    if (owner->HasAura(SPELL_PET_RESISTANCE))
                        value += 130;
                }
                break;
            case EFFECT_INDEX_1: // mana regen
                if (Unit* owner = caster->GetOwner())
                    if (owner->IsPlayer())
                        value = static_cast<Player*>(owner)->GetFloatValue(PLAYER_FIELD_MOD_MANA_REGEN) * 0.1f * 5.f;
                break;
            default: break;
        }
        return value;
    }
};

struct MagePetScaling1 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // stamina
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // attack power
                break;
            case EFFECT_INDEX_2: // spell power
                if (Unit* owner = caster->GetOwner())
                {
                    if (owner->IsPlayer())
                    {
                        int32 frost = int32(owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_FROST)) - owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + SPELL_SCHOOL_FROST);
                        if (frost < 0)
                            frost = 0;
                        value = frost * 0.4f;
                    }
                }
                break;
        }
        return value;
    }
};

struct MagePetScaling2 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // intelect
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // armor
                if (Unit* owner = caster->GetOwner())
                    value = owner->GetArmor() * 0.35f;
                break;
            case EFFECT_INDEX_2: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_FIRE) * 0.4f);
                break;
        }
        return value;
    }
};

struct MagePetScaling3 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_FROST) * 0.4f);
                break;
            case EFFECT_INDEX_1: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_ARCANE) * 0.4f);
                break;
            case EFFECT_INDEX_2: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_NATURE) * 0.4f);
                break;
        }
        return value;
    }
};

struct MagePetScaling4 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                if (Unit* owner = caster->GetOwner())
                    value = (owner->GetResistance(SPELL_SCHOOL_SHADOW) * 0.4f);
                break;
            default: break;
        }
        return value;
    }
};

struct PriestPetScaling1 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // stamina
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // attack power
                if (Unit* owner = caster->GetOwner())
                {
                    if (owner->IsPlayer())
                    {
                        int32 shadow = int32(owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW)) - owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + SPELL_SCHOOL_SHADOW);
                        if (shadow < 0)
                            shadow = 0;
                        value = shadow * 0.65f;
                    }
                }
                break;
            case EFFECT_INDEX_2: // spell power
                break;
        }
        return value;
    }
};

struct PriestPetScaling2 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // intelect
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // armor
                break;
            case EFFECT_INDEX_2: // resistance
                break;
        }
        return value;
    }
};

struct PriestPetScaling3 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            case EFFECT_INDEX_1: // resistance
                break;
            case EFFECT_INDEX_2: // resistance
                break;
        }
        return value;
    }
};

struct PriestPetScaling4 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            default: break;
        }
        return value;
    }
};

struct ElementalPetScaling1 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // dummy - unk
                break;
            case EFFECT_INDEX_1: // attack power
                break;
            case EFFECT_INDEX_2: // spell power
                break;
        }
        return value;
    }
};

struct ElementalPetScaling2 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // intelect
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // armor
                break;
            case EFFECT_INDEX_2: // resistance
                break;
        }
        return value;
    }
};

struct ElementalPetScaling3 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            case EFFECT_INDEX_1: // resistance
                break;
            case EFFECT_INDEX_2: // resistance
                break;
        }
        return value;
    }
};

struct ElementalPetScaling4 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            default: break;
        }
        return value;
    }
};

struct DruidPetScaling1 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // stamina
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.15f; // unconfirmed value
                break;
            case EFFECT_INDEX_1: // attack power
                if (Unit* owner = caster->GetOwner())
                {
                    if (owner->IsPlayer())
                    {
                        int32 nature = int32(owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_NATURE)) - owner->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + SPELL_SCHOOL_NATURE);
                        if (nature < 0)
                            nature = 0;
                        value = nature * 1.f;
                    }
                }
                break;
            case EFFECT_INDEX_2: // spell power
                break;
        }
        return value;
    }
};

struct DruidPetScaling2 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // intelect
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // armor
                break;
            case EFFECT_INDEX_2: // resistance
                break;
        }
        return value;
    }
};

struct DruidPetScaling3 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            case EFFECT_INDEX_1: // resistance
                break;
            case EFFECT_INDEX_2: // resistance
                break;
        }
        return value;
    }
};

struct DruidPetScaling4 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            default: break;
        }
        return value;
    }
};

struct EnhancementPetScaling1 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // stamina
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // attack power
                break;
            case EFFECT_INDEX_2: // spell power
                break;
        }
        return value;
    }
};

struct EnhancementPetScaling2 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            case EFFECT_INDEX_1: // resistance
                break;
            case EFFECT_INDEX_2: // resistance
                break;
        }
        return value;
    }
};

struct EnhancementPetScaling3 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            case EFFECT_INDEX_1: // resistance
                break;
            case EFFECT_INDEX_2: // armor
                break;
        }
        return value;
    }
};

struct InfernalPetScaling1 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // stamina
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // attack power
                break;
            case EFFECT_INDEX_2: // spell power
                break;
        }
        return value;
    }
};

struct InfernalPetScaling2 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // intelect
                if (Unit* owner = caster->GetOwner())
                    value = float(owner->GetStat(STAT_STAMINA)) * 0.3f;
                break;
            case EFFECT_INDEX_1: // armor
                break;
            case EFFECT_INDEX_2: // resistance
                break;
        }
        return value;
    }
};

struct InfernalPetScaling3 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            case EFFECT_INDEX_1: // resistance
                break;
            case EFFECT_INDEX_2: // resistance
                break;
        }
        return value;
    }
};

struct InfernalPetScaling4 : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* /*caster*/, int32 value) const override
    {
        switch (aura->GetEffIndex())
        {
            case EFFECT_INDEX_0: // resistance
                break;
            case EFFECT_INDEX_1: // mana regen
                break;
            default: break;
        }
        return value;
    }
};

void LoadScalingScripts()
{
    RegisterAuraScript<HunterPetScaling1>("spell_hunter_pet_scaling_1");
    RegisterAuraScript<HunterPetScaling2>("spell_hunter_pet_scaling_2");
    RegisterAuraScript<HunterPetScaling3>("spell_hunter_pet_scaling_3");

    RegisterAuraScript<WarlockPetScaling1>("spell_warlock_pet_scaling_1");
    RegisterAuraScript<WarlockPetScaling2>("spell_warlock_pet_scaling_2");
    RegisterAuraScript<WarlockPetScaling3>("spell_warlock_pet_scaling_3");
    RegisterAuraScript<WarlockPetScaling4>("spell_warlock_pet_scaling_4");

    RegisterAuraScript<MagePetScaling1>("spell_mage_pet_scaling_1");
    RegisterAuraScript<MagePetScaling2>("spell_mage_pet_scaling_2");
    RegisterAuraScript<MagePetScaling3>("spell_mage_pet_scaling_3");
    RegisterAuraScript<MagePetScaling4>("spell_mage_pet_scaling_4");

    RegisterAuraScript<PriestPetScaling1>("spell_priest_pet_scaling_1");
    RegisterAuraScript<PriestPetScaling2>("spell_priest_pet_scaling_2");
    RegisterAuraScript<PriestPetScaling3>("spell_priest_pet_scaling_3");
    RegisterAuraScript<PriestPetScaling4>("spell_priest_pet_scaling_4");

    RegisterAuraScript<ElementalPetScaling1>("spell_elemental_pet_scaling_1");
    RegisterAuraScript<ElementalPetScaling2>("spell_elemental_pet_scaling_2");
    RegisterAuraScript<ElementalPetScaling3>("spell_elemental_pet_scaling_3");
    RegisterAuraScript<ElementalPetScaling4>("spell_elemental_pet_scaling_4");

    RegisterAuraScript<DruidPetScaling1>("spell_druid_pet_scaling_1");
    RegisterAuraScript<DruidPetScaling2>("spell_druid_pet_scaling_2");
    RegisterAuraScript<DruidPetScaling3>("spell_druid_pet_scaling_3");
    RegisterAuraScript<DruidPetScaling4>("spell_druid_pet_scaling_4");

    RegisterAuraScript<EnhancementPetScaling1>("spell_enhancement_pet_scaling_1");
    RegisterAuraScript<EnhancementPetScaling2>("spell_enhancement_pet_scaling_2");
    RegisterAuraScript<EnhancementPetScaling3>("spell_enhancement_pet_scaling_3");

    RegisterAuraScript<InfernalPetScaling1>("spell_infernal_pet_scaling_1");
    RegisterAuraScript<InfernalPetScaling2>("spell_infernal_pet_scaling_2");
    RegisterAuraScript<InfernalPetScaling3>("spell_infernal_pet_scaling_3");
    RegisterAuraScript<InfernalPetScaling4>("spell_infernal_pet_scaling_4");
}
