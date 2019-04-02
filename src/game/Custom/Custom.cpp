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

void Custom::Load()
{
    sWorld.setConfig(CONFIG_BOOL_CFBG_ENABLED, "BattleGround.Crossfaction.Queueing", false);
    sWorld.setConfig(CONFIG_BOOL_CFBG_ENABLED, "BattleGround.Crossfaction.ReplaceRacials", false);
    sWorld.setConfig(CONFIG_BOOL_DUELRESET_ENABLED, "Custom.DuelReset", false);
    sWorld.setConfig(CONFIG_UINT32_AUTOBROADCAST_TIMER, "Custom.AutoBroadcastTimer", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_SPEEDCHEAT, "Custom.AntiCheat.SpeedCheat", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_TELEPORT, "Custom.AntiCheat.Teleport", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_FLY, "Custom.AntiCheat.Fly", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_JUMP, "Custom.AntiCheat.Jump", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_GRAVITY, "Custom.AntiCheat.Gravity", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_WATERWALKING, "Custom.AntiCheat.WaterWalking", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_WALLCLIMBING, "Custom.AntiCheat.WallClimbing", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_WALLJUMPING, "Custom.AntiCheat.WallJumping", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_TELE2PLANE, "Custom.AntiCheat.Tele2Plane", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_NOFALL, "Custom.AntiCheat.NoFall", 0);
    sWorld.setConfig(CONFIG_BOOL_ANTICHEAT_TIME, "Custom.AntiCheat.Time", 0);
    m_timers[CUPDATE_AUTOBROADCAST].SetInterval(sWorld.getConfig(CONFIG_UINT32_AUTOBROADCAST_TIMER) * IN_MILLISECONDS);
    autoBroadcast->SetAutoBroadcastPrefix(sConfig.GetStringDefault("Custom.AutoBroadcastPrefix", ""));

    autoBroadcast->LoadAutoBroadcasts();
    spellRegulator->LoadRegulators();
}


