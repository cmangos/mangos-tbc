#include "CPlayer.h"
#include "Globals/Custom.h"
#include "Entities/Object.h"
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
#include "AntiCheat/AntiCheat_time.h"

#include <iomanip>

CPlayer::CPlayer(WorldSession* session) : Player(session)
{
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_speed(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_teleport(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_fly(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_jump(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_gravity(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_waterwalking(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_wallclimb(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_walljump(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_tptoplane(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_nofall(this)));
    antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_time(this)));
    //antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_test(this)));

    m_GMFly = false;
}

CPlayer::~CPlayer()
= default;

bool CPlayer::HandleAntiCheat(const MovementInfoPtr& moveInfo, Opcodes opcode)
{
    if (!IsInWorld())
        return false;

    bool cheat = false;

    for (auto& i : antiCheatStorage)
        if (i->HandleMovement(moveInfo, opcode, cheat))
            cheat = true;

    return cheat;
}

void CPlayer::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    for (auto& i : antiCheatStorage)
        i->HandleKnockBack(angle, horizontalSpeed, verticalSpeed);
}

void CPlayer::HandleRelocate(float x, float y, float z, float o)
{
    for (auto& i : antiCheatStorage)
        i->HandleRelocate(x, y, z, o);
}

void CPlayer::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
    for (auto& i : antiCheatStorage)
        i->HandleTeleport(map, x, y, z, o);
}

void CPlayer::SendStreamMessages(MessageType type, std::stringstream &ss)
{
    if (!ss.str().empty())
    {
        std::string item;

        while (std::getline(ss, item))
        {
            item.insert(0, MSG_COLOR_WHITE).append("|r");
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
        ss << std::fixed; // Use fixed precision
    }
}

void CPlayer::Update(uint32 update_diff)
{
    Player::Update(update_diff);

    SendStreamMessages(MessageType(CHAT_BOX), BoxChat);
    SendStreamMessages(MessageType(CHAT_WIDE), WideChat);
    SendStreamMessages(MessageType(CHAT_BOX | CHAT_WIDE), BothChat);

    for (auto& i : antiCheatStorage)
        i->HandleUpdate(update_diff);
}

bool CPlayer::AddAura(uint32 spellid)
{
    auto const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellid);
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
        const uint32 eff = spellInfo->Effect[i];
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

bool CPlayer::TeleportToPos(uint32 mapid, const Position* pos, uint32 options, AreaTrigger const* at)
{
	return TeleportTo(mapid, pos->x, pos->y, pos->z, pos->o, options, at);
}
