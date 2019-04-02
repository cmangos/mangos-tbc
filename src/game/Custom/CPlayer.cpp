#include "CPlayer.h"
#include "Custom/Custom.h"
#include "Entities/Object.h"
#include "Spells/SpellAuras.h"
#include "Spells/SpellMgr.h"
#include "Spells/Spell.h"
#include "Globals/ObjectMgr.h"
#include "World/World.h"
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
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_SPEEDCHEAT))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_speed(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_TELEPORT))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_teleport(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_FLY))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_fly(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_JUMP))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_jump(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_GRAVITY))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_gravity(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_WATERWALKING))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_waterwalking(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_WALLCLIMBING))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_wallclimb(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_WALLJUMPING))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_walljump(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_TELE2PLANE))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_tptoplane(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_NOFALL))
        antiCheatStorage.push_back(AntiCheatPtr(new AntiCheat_nofall(this)));
    if (sWorld.getConfig(CONFIG_BOOL_ANTICHEAT_TIME))
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

void CPlayer::CFJoinBattleGround()
{
    if (!sWorld.getConfig(CONFIG_BOOL_CFBG_ENABLED))
        return;

    if (NativeTeam())
        return;

    SetByteValue(UNIT_FIELD_BYTES_0, 0, getFRace());
    setFaction(getFFaction());
    ReplaceRacials(false);
    FakeDisplayID();

    sWorld.InvalidatePlayerDataToAllClient(this->GetObjectGuid());
}

void CPlayer::CFLeaveBattleGround()
{
    if (!sWorld.getConfig(CONFIG_BOOL_CFBG_ENABLED))
        return;

    SetByteValue(UNIT_FIELD_BYTES_0, 0, getORace());
    setFaction(getOFaction());
    ReplaceRacials(true);
    InitDisplayIds();

    sWorld.InvalidatePlayerDataToAllClient(GetObjectGuid());
}

void CPlayer::FakeDisplayID()
{
    if (!sWorld.getConfig(CONFIG_BOOL_CFBG_ENABLED))
        return;

    PlayerInfo const* info = sObjectMgr.GetPlayerInfo(getRace(), getClass());
    if (!info)
        for (uint32 i = 1; i <= CLASS_DRUID; i++)
            if ((info = sObjectMgr.GetPlayerInfo(getRace(), i)))
                break;

    if (!info)
    {
        sLog.outError("Player %u has incorrect race/class pair. Can't init display ids.", GetGUIDLow());
        return;
    }

    SetObjectScale(DEFAULT_OBJECT_SCALE);

    uint8 gender = getGender();
    switch (gender)
    {
    case GENDER_FEMALE:
        SetDisplayId(info->displayId_f);
        SetNativeDisplayId(info->displayId_f);
        break;
    case GENDER_MALE:
        SetDisplayId(info->displayId_m);
        SetNativeDisplayId(info->displayId_m);
        break;
    default:
        sLog.outError("Invalid gender %u for player", gender);
        return;
    }
}

void CPlayer::ReplaceRacials(bool native)
{
    if (!sWorld.getConfig(CONFIG_BOOL_CFBG_ENABLED) ||
        sWorld.getConfig(CONFIG_BOOL_CFBG_REPLACERACIALS))
        return;

    // SpellId, Original Team Spell
    auto spells = std::unordered_map<uint32, bool>();

    for (auto& i : sObjectMgr.GetPlayerInfo(getORace(), getClass())->spell)
        if (auto spell = sSpellTemplate.LookupEntry<SpellEntry>(i))
                if (spell->Effect[0] != SPELL_EFFECT_LANGUAGE)
                    spells[spell->Id] = true;

    for (auto& i : sObjectMgr.GetPlayerInfo(getFRace(), getClass())->spell)
        if (auto spell = sSpellTemplate.LookupEntry<SpellEntry>(i))
                if (spell->Effect[0] != SPELL_EFFECT_LANGUAGE)
                    spells[spell->Id] = false;

    for (auto& i : spells)
    {
        if (i.second == native)
            learnSpell(i.first, true);
        else
            this->removeSpell(i.first);
    }
}

void CPlayer::SetFakeValues()
{
    m_oRace = GetByteValue(UNIT_FIELD_BYTES_0, 0);
    m_oFaction = GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE);

    m_fRace = 0;

    while (m_fRace == 0)
    {
        for (uint8 i = RACE_HUMAN; i <= RACE_DRAENEI; ++i)
        {
            if (i == RACE_GOBLIN)
                continue;

            PlayerInfo const* info = sObjectMgr.GetPlayerInfo(i, getClass());
            if (!info || Player::TeamForRace(i) == GetOTeam())
                continue;

            if (urand(0, 5) == 0)
                m_fRace = i;
        }
    }

    m_fFaction = Player::getFactionForRace(m_fRace);
}

Team Player::GetTeam() const
{
    return ToCPlayer()->GetTeam();
}
