/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Entities/Object.h"
#include "Entities/Player.h"
#include "BattleGround.h"
#include "BattleGroundRL.h"
#include "Tools/Language.h"
#include "WorldPacket.h"
#include "World/WorldStateDefines.h"
#include "World/WorldStateVariableManager.h"

BattleGroundRL::BattleGroundRL()
{
    m_startDelayTimes[BG_STARTING_EVENT_FIRST]  = BG_START_DELAY_1M;
    m_startDelayTimes[BG_STARTING_EVENT_SECOND] = BG_START_DELAY_30S;
    m_startDelayTimes[BG_STARTING_EVENT_THIRD]  = BG_START_DELAY_15S;
    m_startDelayTimes[BG_STARTING_EVENT_FOURTH] = BG_START_DELAY_NONE;

    // we must set messageIds
    m_startMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_ARENA_ONE_MINUTE;
    m_startMessageIds[BG_STARTING_EVENT_SECOND] = LANG_ARENA_THIRTY_SECONDS;
    m_startMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_ARENA_FIFTEEN_SECONDS;
    m_startMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_ARENA_HAS_BEGUN;
}

void BattleGroundRL::Reset()
{
    GetBgMap()->GetVariableManager().SetVariable(WORLD_STATE_ARENA_RL_HUD_ENABLED, 1);
    GetBgMap()->GetVariableManager().SetVariableData(WORLD_STATE_ARENA_RL_HUD_ENABLED, true, 0, 0);
    GetBgMap()->GetVariableManager().SetVariableData(WORLD_STATE_ARENA_RL_ALLIANCE_ALIVE, true, 0, 0);
    GetBgMap()->GetVariableManager().SetVariableData(WORLD_STATE_ARENA_RL_HORDE_ALIVE, true, 0, 0);
}

void BattleGroundRL::StartingEventOpenDoors()
{
    OpenDoorEvent(BG_EVENT_DOOR);
}

void BattleGroundRL::AddPlayer(Player* plr)
{
    BattleGround::AddPlayer(plr);
    // create score and add it to map, default values are set in constructor
    BattleGroundRLScore* sc = new BattleGroundRLScore;

    // Needed for scoreboard if player leaves.
    sc->Team = plr->GetBGTeam();

    m_playerScores[plr->GetObjectGuid()] = sc;

    GetBgMap()->GetVariableManager().SetVariable(WORLD_STATE_ARENA_RL_ALLIANCE_ALIVE, GetAlivePlayersCountByTeam(ALLIANCE));
    GetBgMap()->GetVariableManager().SetVariable(WORLD_STATE_ARENA_RL_HORDE_ALIVE, GetAlivePlayersCountByTeam(HORDE));
}

void BattleGroundRL::RemovePlayer(Player* /*plr*/, ObjectGuid /*guid*/)
{
    if (GetStatus() == STATUS_WAIT_LEAVE)
        return;

    GetBgMap()->GetVariableManager().SetVariable(WORLD_STATE_ARENA_RL_ALLIANCE_ALIVE, GetAlivePlayersCountByTeam(ALLIANCE));
    GetBgMap()->GetVariableManager().SetVariable(WORLD_STATE_ARENA_RL_HORDE_ALIVE, GetAlivePlayersCountByTeam(HORDE));

    CheckArenaWinConditions();
}

void BattleGroundRL::HandleKillPlayer(Player* player, Player* killer)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    if (!killer)
    {
        sLog.outError("Killer player not found");
        return;
    }

    BattleGround::HandleKillPlayer(player, killer);

    GetBgMap()->GetVariableManager().SetVariable(WORLD_STATE_ARENA_RL_ALLIANCE_ALIVE, GetAlivePlayersCountByTeam(ALLIANCE));
    GetBgMap()->GetVariableManager().SetVariable(WORLD_STATE_ARENA_RL_HORDE_ALIVE, GetAlivePlayersCountByTeam(HORDE));

    CheckArenaWinConditions();
}

bool BattleGroundRL::HandlePlayerUnderMap(Player* player)
{
    player->TeleportTo(GetMapId(), 1285.810547f, 1667.896851f, 39.957642f, player->GetOrientation());
    return true;
}
