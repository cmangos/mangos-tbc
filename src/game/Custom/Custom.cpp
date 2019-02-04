#include "Custom.h"
#include "Policies/Singleton.h"
#include "Config/Config.h"
#include "World/World.h"
#include "Server/WorldSession.h"
#include "Entities/Player.h"
#include "Custom/CPlayer.h"
#include "SpellRegulator.hpp"
#include "AutoBroadcast.hpp"

Custom::Custom()
{
    spellRegulator = new SpellRegulator();
    autoBroadcast = new AutoBroadcast();
}

Custom::~Custom()
{
    delete spellRegulator;
    delete autoBroadcast;
}

void Custom::Update(uint32 diff)
{
    for (size_t i = 0; i < CUPDATE_COUNT; ++i)
        m_timers[i].Update(diff);

    autoBroadcast->SendAutoBroadcasts();
}

void Custom::LoadConfig()
{
    sWorld.setConfig(CONFIG_BOOL_CFBG_ENABLED, "BattleGround.CrossfactionQueueing", false);
    sWorld.setConfig(CONFIG_BOOL_DUELRESET_ENABLED, "Custom.DuelReset", false);
    sWorld.setConfig(CONFIG_UINT32_AUTOBROADCAST_TIMER, "Custom.AutoBroadcastTimer", 0);
    m_timers[CUPDATE_AUTOBROADCAST].SetInterval(sWorld.getConfig(CONFIG_UINT32_AUTOBROADCAST_TIMER) * IN_MILLISECONDS);
    autoBroadcast->SetAutoBroadcastPrefix(sConfig.GetStringDefault("Custom.AutoBroadcastPrefix", ""));

    autoBroadcast->LoadAutoBroadcasts();
    spellRegulator->LoadRegulators();
}


