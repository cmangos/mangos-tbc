#pragma once

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "World/World.h"
#include "Singleton.h"

enum MessageType : uint8
{
    CHAT_BOX = 0x1,
    CHAT_WIDE = 0x2
};

enum CustomTimers : uint8
{
    CUPDATE_AUTOBROADCAST,
    CUPDATE_COUNT
};

struct AutoBroadcastMsg
{
    std::string text { "" };
    MessageType type { CHAT_BOX };
};

class Custom : public CSingleton<Custom>
{
public:
    Custom();
    ~Custom();

    void LoadConfig();
    void LoadAutoBroadcasts();
    void SendAutoBroadcasts();
    void Update(uint32 diff);
private:
    IntervalTimer m_timers[CUPDATE_COUNT];
    std::string AutoBroadcastPrefix {""};
    std::vector<AutoBroadcastMsg> AutoBroadcastMessages {};
    size_t AutoBroadcastItr { 0 };
};

#define sCustom Custom::Instance()
