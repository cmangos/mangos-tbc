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

class SpellRegulator;
class AutoBroadcast;

class Custom : public CSingleton<Custom>
{
public:
    Custom();
    ~Custom();

    SpellRegulator* spellRegulator {};
    AutoBroadcast* autoBroadcast {};

    void Load();
    void Update(uint32 diff);
    IntervalTimer& GetTimer(CustomTimers timer) { return m_timers[timer]; }
private:
    IntervalTimer m_timers[CUPDATE_COUNT];};

#define sCustom Custom::Instance()
