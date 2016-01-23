#include "CPlayer.h"
#include "AntiCheat.h"
#include "AntiCheat_speed.h"
#include "AntiCheat_teleport.h"
#include "AntiCheat_fly.h"
#include "AntiCheat_jump.h"
#include "AntiCheat_gravity.h"

CPlayer::CPlayer(WorldSession* session) : Player(session)
{
    new AntiCheat_speed(this);
    new AntiCheat_teleport(this);
    new AntiCheat_fly(this);
    new AntiCheat_jump(this);
    new AntiCheat_gravity(this);

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
        if (i->HandleMovement(moveInfo, opcode))
            cheat = true;

    return cheat;
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
                GetSession()->SendPacket(&data);
            }
        }

        ss.str(""); // Clear content
        ss.clear(); // Clear state flags.
    }
}

void CPlayer::CUpdate(uint32 update_diff, uint32 p_time)
{
    SendSteamMessages(MessageTypes(CHAT_BOX), BoxChat);
    SendSteamMessages(MessageTypes(CHAT_WIDE), WideChat);
    SendSteamMessages(MessageTypes(CHAT_BOX | CHAT_WIDE), BothChat);
}