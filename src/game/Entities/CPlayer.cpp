#include "CPlayer.h"
#include "Spells/SpellAuras.h"
#include "Spells/SpellMgr.h"
#include "Spells/Spell.h"
#include "AntiCheat/AntiCheat.h"
#include "AntiCheat/AntiCheat_speed.h"
#include "AntiCheat/AntiCheat_teleport.h"
#include "AntiCheat/AntiCheat_fly.h"
#include "AntiCheat/AntiCheat_jump.h"
#include "AntiCheat/AntiCheat_gravity.h"
#include "AntiCheat/AntiCheat_waterwalking.h"
#include "AntiCheat/AntiCheat_wallclimb.h"
#include "AntiCheat/AntiCheat_walljump.h"
#include "AntiCheat/AntiCheat_tptoplane.h"
#include "AntiCheat/AntiCheat_nofall.h"
#include "AntiCheat/AntiCheat_test.h"

CPlayer::CPlayer(WorldSession* session) : Player(session)
{
    new AntiCheat_speed(this);
    new AntiCheat_teleport(this);
    new AntiCheat_fly(this);
    new AntiCheat_jump(this);
    new AntiCheat_gravity(this);
    new AntiCheat_waterwalking(this);
    new AntiCheat_wallclimb(this);
    new AntiCheat_walljump(this);
    new AntiCheat_tptoplane(this);
    new AntiCheat_nofall(this);
    //new AntiCheat_test(this);

    m_GMFly = false;
}

CPlayer::~CPlayer()
{
    for (auto& i : m_AntiCheatStorage)
        delete i;
}

bool CPlayer::HandleAntiCheat(MovementInfo& moveInfo, Opcodes opcode)
{
    bool cheat = false;

    for (auto& i : m_AntiCheatStorage)
        if (i->HandleMovement(moveInfo, opcode, cheat))
            cheat = true;

    return cheat;
}

void CPlayer::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    for (auto& i : m_AntiCheatStorage)
        i->HandleKnockBack(angle, horizontalSpeed, verticalSpeed);
}

void CPlayer::HandleRelocate(float x, float y, float z, float o)
{
    for (auto& i : m_AntiCheatStorage)
        i->HandleRelocate(x, y, z, o);
}

void CPlayer::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
    for (auto& i : m_AntiCheatStorage)
        i->HandleTeleport(map, x, y, z, o);
}

void CPlayer::HandleUpdate(uint32 update_diff, uint32 p_time)
{
    for (auto& i : m_AntiCheatStorage)
        i->HandleUpdate(update_diff, p_time);
}

void CPlayer::AddAntiCheatModule(AntiCheat* antiCheat)
{
    m_AntiCheatStorage.push_back(antiCheat);
}

void CPlayer::SendSteamMessages(MessageTypes type, std::stringstream &ss)
{
    if (!ss.str().empty())
    {
        std::string item;

        while (std::getline(ss, item))
        {
            item = MSG_COLOR_WHITE + item + "|r"; // Default chat to white.
            const char* msg = item.c_str();

            if ((type & CHAT_BOX) != 0)
                ChatHandler(GetSession()).SendSysMessage(msg);
            if ((type & CHAT_WIDE) != 0)
            {
                WorldPacket data(SMSG_NOTIFICATION, (strlen(msg) + 1));
                data << msg;
                GetSession()->SendPacket(data);
            }
        }

        ss.str(""); // Clear content
        ss.clear(); // Clear state flags.
    }
}

void CPlayer::CUpdate(uint32 update_diff, uint32 p_time)
{
    HandleUpdate(update_diff, p_time);

    SendSteamMessages(MessageTypes(CHAT_BOX), BoxChat);
    SendSteamMessages(MessageTypes(CHAT_WIDE), WideChat);
    SendSteamMessages(MessageTypes(CHAT_BOX | CHAT_WIDE), BothChat);
}

bool CPlayer::AddAura(uint32 spellid)
{
    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellid);
    if (!spellInfo)
        return false;

    if (!IsSpellAppliesAura(spellInfo, (1 << EFFECT_INDEX_0) | (1 << EFFECT_INDEX_1) | (1 << EFFECT_INDEX_2)) &&
        !IsSpellHaveEffect(spellInfo, SPELL_EFFECT_PERSISTENT_AREA_AURA))
    {
        return false;
    }

    SpellAuraHolder* holder = CreateSpellAuraHolder(spellInfo, this, this);

    for (uint32 i = 0; i < MAX_EFFECT_INDEX; ++i)
    {
        uint8 eff = spellInfo->Effect[i];
        if (eff >= TOTAL_SPELL_EFFECTS)
            continue;
        if (IsAreaAuraEffect(eff) ||
            eff == SPELL_EFFECT_APPLY_AURA ||
            eff == SPELL_EFFECT_PERSISTENT_AREA_AURA)
        {
            Aura* aur = CreateAura(spellInfo, SpellEffectIndex(i), nullptr, holder, this);
            holder->AddAura(aur, SpellEffectIndex(i));
        }
    }

    this->AddSpellAuraHolder(holder);

    return true;
}
