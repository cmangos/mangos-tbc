#include "CPlayer.h"

CPlayer::CPlayer(WorldSession* session) : Player(session)
{
}

CPlayer::~CPlayer()
{
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