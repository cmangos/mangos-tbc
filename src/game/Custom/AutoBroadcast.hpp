#pragma once

#include "Common.h"
#include "Custom.h"
#include "Database/DatabaseEnv.h"
#include "Server/Opcodes.h"
#include "WorldPacket.h"
#include "Log.h"

struct AutoBroadcastMsg
{
    std::string text { "" };
    MessageType type { CHAT_BOX };
};

class AutoBroadcast
{
public:
    void SetAutoBroadcastPrefix(std::string prefix)
    {
        AutoBroadcastPrefix = prefix;
    }

    void LoadAutoBroadcasts()
    {
        AutoBroadcastMessages.clear();

        try
        {
            auto result = WorldDatabase.PQuery("SELECT text, type FROM custom_autobroadcasts ORDER BY id");

            if (!result)
            {
                sLog.outErrorDb("Couldn't load custom_autobroadcasts table");
                return;
            }

            do
            {
                auto field = result->Fetch();

                AutoBroadcastMsg msg;
                msg.text = field[0].GetCppString();
                msg.type = MessageType(field[1].GetUInt8());
                AutoBroadcastMessages.push_back(msg);
            }
            while (result->NextRow());
        }
        catch (std::exception)
        {
            sLog.outError("Failed to load autobroadcasts, make sure table exists in world database");
        }
    }

    void SendAutoBroadcasts()
    {
        if (sWorld.getConfig(CONFIG_UINT32_AUTOBROADCAST_TIMER) == 0)
            return;

        if (sCustom.GetTimer(CUPDATE_AUTOBROADCAST).Passed())
        {
            sCustom.GetTimer(CUPDATE_AUTOBROADCAST).Reset();

            if (AutoBroadcastMessages.size() == 0)
                return;

            if (AutoBroadcastItr >= AutoBroadcastMessages.size())
                AutoBroadcastItr = 0;

            auto msg = AutoBroadcastMessages[AutoBroadcastItr];
            ++AutoBroadcastItr;

            std::string message = AutoBroadcastPrefix + msg.text;

            if ((msg.type & CHAT_BOX) != 0)
                sWorld.SendServerMessage(SERVER_MSG_CUSTOM, message.c_str());
            if ((msg.type & CHAT_WIDE) != 0)
            {
                WorldPacket data(SMSG_NOTIFICATION, (message.length() + 1));
                data << message.c_str();
                sWorld.SendGlobalMessage(data);
            }
        }
    }
private:
    std::string AutoBroadcastPrefix {""};
    std::vector<AutoBroadcastMsg> AutoBroadcastMessages {};
    size_t AutoBroadcastItr { 0 };
};
