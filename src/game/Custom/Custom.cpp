#include "Custom.h"
#include "Policies/Singleton.h"
#include "Config/Config.h"
#include "World/World.h"
#include "Server/WorldSession.h"
#include "Entities/Player.h"
#include "Custom/CPlayer.h"

Custom::Custom()
{
}

Custom::~Custom()
{
}

void Custom::Update(uint32 diff)
{
    for (size_t i = 0; i < CUPDATE_COUNT; ++i)
        m_timers[i].Update(diff);

    SendAutoBroadcasts();
}

void Custom::LoadConfig()
{
    sWorld.setConfig(CONFIG_BOOL_CFBG_ENABLED, "BattleGround.CrossfactionQueueing", false);
    sWorld.setConfig(CONFIG_BOOL_DUELRESET_ENABLED, "Custom.DuelReset", false);
    sWorld.setConfig(CONFIG_UINT32_AUTOBROADCAST_TIMER, "Custom.AutoBroadcastTimer", 0);
    m_timers[CUPDATE_AUTOBROADCAST].SetInterval(sWorld.getConfig(CONFIG_UINT32_AUTOBROADCAST_TIMER) * IN_MILLISECONDS);
    AutoBroadcastPrefix = sConfig.GetStringDefault("Custom.AutoBroadcastPrefix", "");

    LoadAutoBroadcasts();
}

void Custom::LoadAutoBroadcasts()
{
    AutoBroadcastMessages.clear();

    try
    {
        auto result = WorldDatabase.PQuery("SELECT text, type FROM custom_autobroadcasts ORDER BY id");

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

void Custom::SendAutoBroadcasts()
{
    if (sWorld.getConfig(CONFIG_UINT32_AUTOBROADCAST_TIMER) == 0)
        return;

    if (m_timers[CUPDATE_AUTOBROADCAST].Passed())
    {
        m_timers[CUPDATE_AUTOBROADCAST].Reset();

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
