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

#include "Common.h"
#include "WorldPacket.h"
#include "Server/WorldSession.h"
#include "Server/Opcodes.h"
#include "Log.h"
#include "Entities/Player.h"
#include "Maps/MapManager.h"
#include "Entities/Transports.h"
#include "BattleGround/BattleGround.h"
#include "MotionGenerators/WaypointMovementGenerator.h"
#include "Maps/MapPersistentStateMgr.h"
#include "Globals/ObjectMgr.h"
#include "Globals/ObjectMgr.h"
#include "World/World.h"
#include "Tools/Language.h"

#define MOVEMENT_PACKET_TIME_DELAY 0

 //#define __ANTI_DEBUG__
#ifdef __ANTI_DEBUG__
#include "Chat/Chat.h"

std::string FlagsToStr(const uint32 Flags)
{
    std::string Ret = "";
    if (Flags == 0)
    {
        Ret = "None";
        return Ret;
    }
    if (Flags & MOVEMENTFLAG_FORWARD)
    {
        Ret += "FW ";
    }
    if (Flags & MOVEMENTFLAG_BACKWARD)
    {
        Ret += "BW ";
    }
    if (Flags & MOVEMENTFLAG_STRAFE_LEFT)
    {
        Ret += "STL ";
    }
    if (Flags & MOVEMENTFLAG_STRAFE_RIGHT)
    {
        Ret += "STR ";
    }
    if (Flags & MOVEMENTFLAG_LEFT)
    {
        Ret += "LF ";
    }
    if (Flags & MOVEMENTFLAG_RIGHT)
    {
        Ret += "RI ";
    }
    if (Flags & MOVEMENTFLAG_PITCH_UP)
    {
        Ret += "PTUP ";
    }
    if (Flags & MOVEMENTFLAG_PITCH_DOWN)
    {
        Ret += "PTDW ";
    }
    if (Flags & MOVEMENTFLAG_WALK_MODE)
    {
        Ret += "WALK ";
    }
    if (Flags & MOVEMENTFLAG_ONTRANSPORT)
    {
        Ret += "TRANS ";
    }
    if (Flags & MOVEMENTFLAG_LEVITATING)
    {
        Ret += "LEVI ";
    }
    if (Flags & MOVEMENTFLAG_FLY_UNK1)
    {
        Ret += "FLYUNK1 ";
    }
    if (Flags & MOVEMENTFLAG_JUMPING)
    {
        Ret += "JUMP ";
    }
    if (Flags & MOVEMENTFLAG_UNK4)
    {
        Ret += "UNK4 ";
    }
    if (Flags & MOVEMENTFLAG_FALLING)
    {
        Ret += "FALL ";
    }
    if (Flags & MOVEMENTFLAG_SWIMMING)
    {
        Ret += "SWIM ";
    }
    if (Flags & MOVEMENTFLAG_FLY_UP)
    {
        Ret += "FLYUP ";
    }
    if (Flags & MOVEMENTFLAG_CAN_FLY)
    {
        Ret += "CFLY ";
    }
    if (Flags & MOVEMENTFLAG_FLYING)
    {
        Ret += "FLY ";
    }
    if (Flags & MOVEMENTFLAG_FLYING2)
    {
        Ret += "FLY2 ";
    }
    if (Flags & MOVEMENTFLAG_WATERWALKING)
    {
        Ret += "WTWALK ";
    }
    if (Flags & MOVEMENTFLAG_SAFE_FALL)
    {
        Ret += "SAFE ";
    }
    if (Flags & MOVEMENTFLAG_UNK3)
    {
        Ret += "UNK3 ";
    }
    if (Flags & MOVEMENTFLAG_SPLINE)
    {
        Ret += "SPLINE ";
    }
    if (Flags & MOVEMENTFLAG_SPLINE2)
    {
        Ret += "SPLINE2 ";
    }
    return Ret;
}
#endif // __ANTI_DEBUG__

bool WorldSession::Anti__ReportCheat(const char* Reason, float Speed, const char* Op, float Val1, uint32 Val2)
{
    if (!Reason)
    {
        sLog.outError("Anti__ReportCheat: Missing Reason parameter!");
        return false;
    }
    const char* Player = GetPlayer()->GetName();
    uint32 Acc = GetPlayer()->GetSession()->GetAccountId();
    uint32 Map = GetPlayer()->GetMapId();
    if (!Player)
    {
        sLog.outError("Anti__ReportCheat: Player with no name?!?");
        return false;
    }

    GetPlayer()->m_anti_old_map = Map;
    GetPlayer()->m_anti_old_x = GetPlayer()->GetPositionX();
    GetPlayer()->m_anti_old_y = GetPlayer()->GetPositionY();
    GetPlayer()->m_anti_old_z = GetPlayer()->GetPositionZ();
    GetPlayer()->m_anti_old_o = GetPlayer()->GetOrientation();

    QueryResult *Res = CharacterDatabase.PQuery("SELECT speed,Val1 FROM cheaters WHERE player='%s' AND reason LIKE '%s' AND Map='%u' AND last_date >= NOW()-300", Player, Reason, Map);
    if (Res)
    {
        Field* Fields = Res->Fetch();

        std::stringstream Query;
        Query << "UPDATE cheaters SET count=count+1,last_date=NOW()";
        Query.precision(5);
        if (Speed>0.0f && Speed > Fields[0].GetFloat())
        {
            Query << ",speed='";
            Query << std::fixed << Speed;
            Query << "'";
        }

        if (Val1>0.0f && Val1 > Fields[1].GetFloat())
        {
            Query << ",Val1='";
            Query << std::fixed << Val1;
            Query << "'";
        }

        Query << " WHERE player='" << Player << "' AND reason='" << Reason << "' AND Map='" << Map << "' AND last_date >= NOW()-300 ORDER BY entry DESC LIMIT 1";
        CharacterDatabase.Execute(Query.str().c_str());
        delete Res;
    }
    else
    {
        if (!Op)
        {
            Op = "";
        }
        std::stringstream Pos;
        Pos << "OldPos: " << GetPlayer()->GetPositionX() << " " << GetPlayer()->GetPositionY() << " " << GetPlayer()->GetPositionZ();
        CharacterDatabase.PExecute("INSERT INTO cheaters (player,acctid,reason,speed,count,first_date,last_date,`Op`,Val1,Val2,Map,Pos,Level) "
             "VALUES ('%s','%u','%s','%f','1',NOW(),NOW(),'%s','%f','%u','%u','%s','%u')",
            Player, Acc, Reason, Speed, Op, Val1, Val2, Map, Pos.str().c_str(), GetPlayer()->getLevel());
    }
    if (sWorld.GetMvAnticheatKill() && GetPlayer()->isAlive())
    {
        GetPlayer()->DealDamage(GetPlayer(), GetPlayer()->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
    }

    //Back to the starting point.
    if (strcmp(Reason, "Tele hack") == 0)
    {
        GetPlayer()->TeleportTo(GetPlayer()->m_anti_old_map, GetPlayer()->m_anti_old_x, GetPlayer()->m_anti_old_y, GetPlayer()->m_anti_old_z, GetPlayer()->m_anti_old_o);
    }

    if (sWorld.GetMvAnticheatKick())
    {
        GetPlayer()->GetSession()->KickPlayer();
    }

    if (sWorld.GetMvAnticheatBan() & 1)
    {
        sWorld.BanAccount(BAN_CHARACTER, Player, sWorld.GetMvAnticheatBanTime(), "Cheat", "Anticheat");
    }
    if (sWorld.GetMvAnticheatBan() & 2)
    {
        QueryResult *result = LoginDatabase.PQuery("SELECT last_ip FROM account WHERE id=%u", Acc);
        if (result)
        {
            Field *fields = result->Fetch();
            std::string LastIP = fields[0].GetCppString();
            if (!LastIP.empty())
            {
                sWorld.BanAccount(BAN_IP, LastIP, sWorld.GetMvAnticheatBanTime(), "Cheat", "Anticheat");
            }
            delete result;
        }
    }
    return true;
}

bool WorldSession::Anti__CheatOccurred(uint32 CurTime, const char* Reason, float Speed, const char* Op, float Val1, uint32 Val2)
{
    if (!Reason)
    {
        sLog.outError("Anti__CheatOccurred: Missing Reason parameter!");
        return false;
    }

    GetPlayer()->m_anti_lastalarmtime = CurTime;
    GetPlayer()->m_anti_alarmcount = GetPlayer()->m_anti_alarmcount + 1;
    if (GetPlayer()->m_anti_alarmcount > sWorld.GetMvAnticheatAlarmCount())
    {
        Anti__ReportCheat(Reason, Speed, Op, Val1, Val2);
        if (sWorld.GetMvAnticheatAnnounce())
            sWorld.SendWorldText(LANG_ANNOUNCE_CHEAT, GetPlayer()->GetName(), Reason);
        return true;
    }
    return false;
}

void WorldSession::HandleMoveWorldportAckOpcode(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("WORLD: got MSG_MOVE_WORLDPORT_ACK.");
    HandleMoveWorldportAckOpcode();
}

void WorldSession::HandleMoveWorldportAckOpcode()
{
    // ignore unexpected far teleports
    if (!GetPlayer()->IsBeingTeleportedFar())
        return;

    // get start teleport coordinates (will used later in fail case)
    WorldLocation old_loc;
    GetPlayer()->GetPosition(old_loc);

    // get the teleport destination
    WorldLocation& loc = GetPlayer()->GetTeleportDest();

    // possible errors in the coordinate validity check (only cheating case possible)
    if (!MapManager::IsValidMapCoord(loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z, loc.orientation))
    {
        sLog.outError("WorldSession::HandleMoveWorldportAckOpcode: %s was teleported far to a not valid location "
                      "(map:%u, x:%f, y:%f, z:%f) We port him to his homebind instead..",
                      GetPlayer()->GetGuidStr().c_str(), loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z);
        // stop teleportation else we would try this again and again in LogoutPlayer...
        GetPlayer()->SetSemaphoreTeleportFar(false);
        // and teleport the player to a valid place
        GetPlayer()->TeleportToHomebind();
        return;
    }

    // get the destination map entry, not the current one, this will fix homebind and reset greeting
    MapEntry const* mEntry = sMapStore.LookupEntry(loc.mapid);

    Map* pMap = nullptr;

    // prevent crash at attempt landing to not existed battleground instance
    if (mEntry->IsBattleGroundOrArena())
    {
        if (GetPlayer()->GetBattleGroundId())
            pMap = sMapMgr.FindMap(loc.mapid, GetPlayer()->GetBattleGroundId());

        if (!pMap)
        {
            DETAIL_LOG("WorldSession::HandleMoveWorldportAckOpcode: %s was teleported far to nonexisten battleground instance "
                       " (map:%u, x:%f, y:%f, z:%f) Trying to port him to his previous place..",
                       GetPlayer()->GetGuidStr().c_str(), loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z);

            GetPlayer()->SetSemaphoreTeleportFar(false);

            // Teleport to previous place, if cannot be ported back TP to homebind place
            if (!GetPlayer()->TeleportTo(old_loc))
            {
                DETAIL_LOG("WorldSession::HandleMoveWorldportAckOpcode: %s cannot be ported to his previous place, teleporting him to his homebind place...",
                           GetPlayer()->GetGuidStr().c_str());
                GetPlayer()->TeleportToHomebind();
            }
            return;
        }
    }

    InstanceTemplate const* mInstance = ObjectMgr::GetInstanceTemplate(loc.mapid);

    // reset instance validity, except if going to an instance inside an instance
    if (GetPlayer()->m_InstanceValid == false && !mInstance)
        GetPlayer()->m_InstanceValid = true;

    GetPlayer()->SetSemaphoreTeleportFar(false);

    // relocate the player to the teleport destination
    if (!pMap)
        pMap = sMapMgr.CreateMap(loc.mapid, GetPlayer());

    GetPlayer()->SetMap(pMap);
    GetPlayer()->Relocate(loc.coord_x, loc.coord_y, loc.coord_z, loc.orientation);
    GetPlayer()->m_anti_TeleTime = time(nullptr);

    GetPlayer()->SendInitialPacketsBeforeAddToMap();
    // the CanEnter checks are done in TeleporTo but conditions may change
    // while the player is in transit, for example the map may get full
    if (!pMap->Add(GetPlayer()))
    {
        // if player wasn't added to map, reset his map pointer!
        GetPlayer()->ResetMap();

        DETAIL_LOG("WorldSession::HandleMoveWorldportAckOpcode: %s was teleported far but couldn't be added to map "
                   " (map:%u, x:%f, y:%f, z:%f) Trying to port him to his previous place..",
                   GetPlayer()->GetGuidStr().c_str(), loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z);

        // Teleport to previous place, if cannot be ported back TP to homebind place
        if (!GetPlayer()->TeleportTo(old_loc))
        {
            DETAIL_LOG("WorldSession::HandleMoveWorldportAckOpcode: %s cannot be ported to his previous place, teleporting him to his homebind place...",
                       GetPlayer()->GetGuidStr().c_str());
            GetPlayer()->TeleportToHomebind();
        }
        return;
    }

    // battleground state prepare (in case join to BG), at relogin/tele player not invited
    // only add to bg group and object, if the player was invited (else he entered through command)
    if (_player->InBattleGround())
    {
        // cleanup setting if outdated
        if (!mEntry->IsBattleGroundOrArena())
        {
            // We're not in BG
            _player->SetBattleGroundId(0, BATTLEGROUND_TYPE_NONE);
            // reset destination bg team
            _player->SetBGTeam(TEAM_NONE);
        }
        // join to bg case
        else if (BattleGround* bg = _player->GetBattleGround())
        {
            if (_player->IsInvitedForBattleGroundInstance(_player->GetBattleGroundId()))
                bg->AddPlayer(_player);
        }
    }

    GetPlayer()->SendInitialPacketsAfterAddToMap();

    // flight fast teleport case
    if (GetPlayer()->GetMotionMaster()->GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE)
    {
        if (!_player->InBattleGround())
        {
            // short preparations to continue flight
            FlightPathMovementGenerator* flight = (FlightPathMovementGenerator*)(GetPlayer()->GetMotionMaster()->top());
            flight->Reset(*GetPlayer());
            return;
        }

        // battleground state prepare, stop flight
        GetPlayer()->GetMotionMaster()->MovementExpired();
        GetPlayer()->m_taxi.ClearTaxiDestinations();
    }

    if (mEntry->IsRaid() && mInstance)
    {
        if (time_t timeReset = sMapPersistentStateMgr.GetScheduler().GetResetTimeFor(mEntry->MapID))
        {
            uint32 timeleft = uint32(timeReset - time(nullptr));
            GetPlayer()->SendInstanceResetWarning(mEntry->MapID, timeleft);
        }
    }

    // mount allow check
    if (!pMap->IsMountAllowed())
        _player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);

    // honorless target
    if (GetPlayer()->pvpInfo.inPvPEnforcedArea)
        GetPlayer()->CastSpell(GetPlayer(), 2479, TRIGGERED_OLD_TRIGGERED);

    // resummon pet
    GetPlayer()->ResummonPetTemporaryUnSummonedIfAny();
    GetPlayer()->Anti__SetLastTeleTime(::time(nullptr));
    GetPlayer()->m_anti_BeginFallZ = INVALID_HEIGHT;

    // lets process all delayed operations on successful teleport
    GetPlayer()->ProcessDelayedOperations();

    // notify group after successful teleport
    if (_player->GetGroup())
        _player->SetGroupUpdateFlag(GROUP_UPDATE_FULL);
}

void WorldSession::HandleMoveTeleportAckOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("MSG_MOVE_TELEPORT_ACK");

    ObjectGuid guid;

    recv_data >> guid;

    uint32 counter, time;
    recv_data >> counter >> time;
    DEBUG_LOG("Guid: %s", guid.GetString().c_str());
    DEBUG_LOG("Counter %u, time %u", counter, time / IN_MILLISECONDS);

    Unit* mover = _player->GetMover();
    Player* plMover = mover->GetTypeId() == TYPEID_PLAYER ? (Player*)mover : nullptr;

    if (!plMover || !plMover->IsBeingTeleportedNear())
        return;

    if (guid != plMover->GetObjectGuid())
        return;

    plMover->SetSemaphoreTeleportNear(false);

    uint32 old_zone = plMover->GetZoneId();

    WorldLocation const& dest = plMover->GetTeleportDest();

    plMover->SetPosition(dest.coord_x, dest.coord_y, dest.coord_z, dest.orientation, true);

    uint32 newzone, newarea;
    plMover->GetZoneAndAreaId(newzone, newarea);
    plMover->UpdateZone(newzone, newarea);

    // new zone
    if (old_zone != newzone)
    {
        // honorless target
        if (plMover->pvpInfo.inPvPEnforcedArea)
            plMover->CastSpell(plMover, 2479, TRIGGERED_OLD_TRIGGERED);
    }

    // resummon pet
    GetPlayer()->ResummonPetTemporaryUnSummonedIfAny();
    if (plMover)
    {
        plMover->Anti__SetLastTeleTime(::time(nullptr));
        plMover->m_anti_BeginFallZ = INVALID_HEIGHT;
    }

    // lets process all delayed operations on successful teleport
    GetPlayer()->ProcessDelayedOperations();
}

void WorldSession::HandleMovementOpcodes(WorldPacket& recv_data)
{
    Opcodes opcode = recv_data.GetOpcode();
    if (!sLog.HasLogFilter(LOG_FILTER_PLAYER_MOVES))
    {
        DEBUG_LOG("WORLD: Received opcode %s (%u, 0x%X)", LookupOpcodeName(opcode), opcode, opcode);
        recv_data.hexlike();
    }

    Unit* mover = _player->GetMover();
    Player* plMover = mover->GetTypeId() == TYPEID_PLAYER ? (Player*)mover : nullptr;

    // ignore, waiting processing in WorldSession::HandleMoveWorldportAckOpcode and WorldSession::HandleMoveTeleportAck
    if (plMover && plMover->IsBeingTeleported())
    {
        recv_data.rpos(recv_data.wpos());                   // prevent warnings spam
        return;
    }

    /* extract packet */
    MovementInfo movementInfo;
    recv_data >> movementInfo;
    /*----------------*/

    if (!VerifyMovementInfo(movementInfo))
        return;

    // fall damage generation (ignore in flight case that can be triggered also at lags in moment teleportation to another map).
    if (opcode == MSG_MOVE_FALL_LAND && plMover && !plMover->IsTaxiFlying())
    {
        plMover->m_anti_justjumped = 0;
        plMover->m_anti_jumpbase = 0;
        plMover->HandleFall(movementInfo);
    }
        

    // Remove auras that should be removed at landing on ground or water
    if (opcode == MSG_MOVE_FALL_LAND || opcode == MSG_MOVE_START_SWIM)
        mover->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_FLAG_LANDING); // Parachutes

    if (plMover)
    {
        //calc time deltas
        int32 timedelta = 1500;
        if (plMover->m_anti_lastmovetime != 0)
        {
            timedelta = movementInfo.GetTime() - plMover->m_anti_lastmovetime;
            plMover->m_anti_lastmovetime = movementInfo.GetTime();
        }
        else
        {
            plMover->m_anti_lastmovetime = movementInfo.GetTime();
        }
        // ---- anti-cheat features -->>>
        uint32 Anti_TeleTimeDiff = plMover ? time(nullptr) - plMover->Anti__GetLastTeleTime() : time(nullptr);
        static const uint32 Anti_TeleTimeIgnoreDiff = sWorld.GetMvAnticheatIgnoreAfterTeleport();
        if (plMover && (plMover->m_transport == 0) && sWorld.GetMvAnticheatEnable() &&
            GetPlayer()->GetSession()->GetSecurity() <= sWorld.GetMvAnticheatGmLevel() &&
            GetPlayer()->GetMotionMaster()->GetCurrentMovementGeneratorType() != FLIGHT_MOTION_TYPE &&
            Anti_TeleTimeDiff>Anti_TeleTimeIgnoreDiff)
        {
            const uint32 CurTime = WorldTimer::getMSTime();
            if (WorldTimer::getMSTimeDiff(GetPlayer()->m_anti_lastalarmtime, CurTime) > sWorld.GetMvAnticheatAlarmPeriod())
            {
                GetPlayer()->m_anti_alarmcount = 0;
            }

            UnitMoveType move_type;

            if (plMover->HasMovementFlag(MOVEFLAG_FLYING2)) move_type = plMover->HasMovementFlag(MOVEFLAG_BACKWARD) ? MOVE_FLIGHT_BACK : MOVE_FLIGHT;
            else if (plMover->HasMovementFlag(MOVEFLAG_SWIMMING)) move_type = plMover->HasMovementFlag(MOVEFLAG_BACKWARD) ? MOVE_SWIM_BACK : MOVE_SWIM;
            else if (plMover->HasMovementFlag(MOVEFLAG_WALK_MODE)) move_type = MOVE_WALK;
            //hmm... in first time after login player has MOVE_SWIMBACK instead MOVE_WALKBACK
            else move_type = plMover->HasMovementFlag(MOVEFLAG_BACKWARD) ? MOVE_SWIM_BACK : MOVE_RUN;

            float allowed_delta = 0;
            float current_speed = plMover->GetSpeed(move_type);
            float delta_x = GetPlayer()->GetPositionX() - movementInfo.GetPos()->x;
            float delta_y = GetPlayer()->GetPositionY() - movementInfo.GetPos()->y;
            float delta_z = GetPlayer()->GetPositionZ() - movementInfo.GetPos()->z;
            float delta = sqrt(delta_x * delta_x + delta_y * delta_y); // Len of movement-vector via Pythagoras (a^2+b^2=Len^2)
            float real_delta = delta_x * delta_x + delta_y * delta_y;
            float tg_z = 0.0f; //tangens
            float delta_t = WorldTimer::getMSTimeDiff(GetPlayer()->m_anti_lastmovetime, CurTime);

            GetPlayer()->m_anti_lastmovetime = CurTime;
            GetPlayer()->m_anti_MovedLen += delta;

            if (delta_t > 15000.0f)
            {
                delta_t = 15000.0f;
            }

            // Tangens of walking angel
            if (!(movementInfo.GetMovementFlags() & (MOVEFLAG_FLYING | MOVEFLAG_SWIMMING)))
            {
                tg_z = ((delta != 0.0f) && (delta_z > 0.0f)) ? (atan((delta_z*delta_z) / delta) * 180.0f / M_PI) : 0.0f;
            }

            float time_delta = (timedelta < 1500) ? (float)timedelta / 1000 : 1.5f;

            if (current_speed < GetPlayer()->m_anti_last_hspeed)
                allowed_delta = GetPlayer()->m_anti_last_hspeed;
            else
                allowed_delta = current_speed;

            allowed_delta = allowed_delta * time_delta;
            allowed_delta = allowed_delta * allowed_delta + 2;

            //antiOFF fall-damage, MOVEMENTFLAG_UNK4 seted by client if player try movement when falling and unset in this case the MOVEMENTFLAG_FALLING flag. 
            if ((!GetPlayer()->CanFly() && GetPlayer()->m_anti_BeginFallZ == INVALID_HEIGHT) && (movementInfo.GetMovementFlags() & (MOVEFLAG_FALLING | MOVEFLAG_FALLINGFAR)) != 0)
            {
                GetPlayer()->m_anti_BeginFallZ = (float)(movementInfo.GetPos()->z);
            }
            if (GetPlayer()->m_anti_NextLenCheck <= CurTime)
            {
                // Check every 500ms is a lot more advisable then 1000ms, because normal movment packet arrives every 500ms
                uint32 OldNextLenCheck = GetPlayer()->m_anti_NextLenCheck;
                float delta_xyt = GetPlayer()->m_anti_MovedLen / (float)(WorldTimer::getMSTimeDiff(OldNextLenCheck - 500, CurTime));
                GetPlayer()->m_anti_NextLenCheck = CurTime + 500;
                GetPlayer()->m_anti_MovedLen = 0.0f;
                static const float MaxDeltaXYT = sWorld.GetMvAnticheatMaxXYT();

                if (delta_xyt > MaxDeltaXYT && delta <= 100.0f && GetPlayer()->GetZoneId() != 2257 && GetPlayer()->IsFleeing() == 0 && GetPlayer()->IsConfused() == 0)
                {
                    if (sWorld.GetMvAnticheatSpeedCheck())
                        Anti__CheatOccurred(CurTime, "Speed hack 1", delta_xyt, LookupOpcodeName(opcode), (float)(GetPlayer()->GetMotionMaster()->GetCurrentMovementGeneratorType()),
                            (float)(WorldTimer::getMSTimeDiff(OldNextLenCheck - 500, CurTime)));
                }
            }

            if (delta > 100.0f && GetPlayer()->GetZoneId() != 2257)
            {
                if (sWorld.GetMvAnticheatTeleportCheck())
                    Anti__ReportCheat("Tele hack", delta, LookupOpcodeName(opcode));
            }

            // Check for waterwalking . Fix new way of checking for waterwalking by Darky88
            if (movementInfo.HasMovementFlag(MOVEFLAG_WATERWALKING) && !(GetPlayer()->HasAuraType(SPELL_AURA_WATER_WALK) || GetPlayer()->HasAuraType(SPELL_AURA_GHOST)))
            {
                if (sWorld.GetMvAnticheatWaterCheck())
                    Anti__CheatOccurred(CurTime, "Water walking", 0.0f, nullptr, 0.0f, (uint32)(movementInfo.GetMovementFlags()));
            }

            // Check for walking upwards a mountain while not beeing able to do that, New check by Darky88 
            if ((delta_z < -2.3f) && (tg_z > 2.37f))
            {
                if (sWorld.GetMvAnticheatMountainCheck())
                    Anti__CheatOccurred(CurTime, "Mountain hack", tg_z, nullptr, delta, delta_z);
            }

            static const float DIFF_OVERGROUND = 10.0f;
            float Anti__GroundZ = GetPlayer()->GetMap()->GetHeight(GetPlayer()->GetPositionX(), GetPlayer()->GetPositionY(), MAX_HEIGHT);
            float Anti__FloorZ = GetPlayer()->GetMap()->GetHeight(GetPlayer()->GetPositionX(), GetPlayer()->GetPositionY(), GetPlayer()->GetPositionZ());
            float Anti__MapZ = ((Anti__FloorZ <= (INVALID_HEIGHT + 5.0f)) ? Anti__GroundZ : Anti__FloorZ) + DIFF_OVERGROUND;

            if (opcode == MSG_MOVE_STOP)
            {
                plMover->m_anti_jumpbase = 0;
                plMover->m_anti_justjumped = 0;
                if (plMover->blink_test && (abs(delta_x)<0.001f) && (abs(delta_y)<0.001f) && (abs(delta_z)<0.001f))
                    Anti__CheatOccurred(CurTime, "Blink cheat", 0.0f, LookupOpcodeName(opcode), 0.0f, movementInfo.GetMovementFlags());
            }

            if (opcode == MSG_MOVE_START_FORWARD && (movementInfo.GetJumpInfo().sinAngle == 0.f)
                && (movementInfo.GetJumpInfo().cosAngle == 0.f) && (movementInfo.GetJumpInfo().velocity == 0.f)
                && (movementInfo.GetJumpInfo().xyspeed == 0.f) && (real_delta>0.001f || abs(delta_z)>0.001f))
                plMover->blink_test = true;
            else
                plMover->blink_test = false;

            //AntiGravitation (thanks to Meekro)
            float JumpHeight = plMover->m_anti_jumpbase - movementInfo.GetPos()->z;
            if ((plMover->m_anti_jumpbase != 0) && !(plMover->m_movementInfo.HasMovementFlag(MOVEFLAG_SWIMMING) || plMover->m_movementInfo.HasMovementFlag(MOVEFLAG_FLYING) || plMover->m_movementInfo.HasMovementFlag(MOVEFLAG_FLYING2))
               && (JumpHeight < -2.3f))
            {
                Anti__CheatOccurred(CurTime, "Gravitation Jump", 0.0f, LookupOpcodeName(opcode), 0.0f, movementInfo.GetMovementFlags());
            }
            // Mod part. Air jump
            if (opcode == MSG_MOVE_JUMP && !plMover->IsInWater())
            {
                if (plMover->m_anti_justjumped >= 1)
                    Anti__CheatOccurred(CurTime, "Air Jump", 0.0f, LookupOpcodeName(opcode), 0.0f, movementInfo.GetMovementFlags());
                else
                    plMover->m_anti_justjumped += 1;
            }
            else
            {
                if (plMover->IsInWater())
                {
                    plMover->m_anti_justjumped = 0;
                }
            }

            if (real_delta > allowed_delta && GetPlayer()->IsFleeing() == 0 && GetPlayer()->IsConfused() == 0)
            {
                Anti__CheatOccurred(CurTime, "Speed hack 2", 0.0f, LookupOpcodeName(opcode), 0.0f, movementInfo.GetMovementFlags());
            }
            if ((real_delta>4900.0f) && !(real_delta < allowed_delta))
            {
                Anti__CheatOccurred(CurTime, "Teleport", 0.0f, LookupOpcodeName(opcode), 0.0f, movementInfo.GetMovementFlags());
            }
            if ((movementInfo.HasMovementFlag(MOVEFLAG_FLYING) || plMover->m_movementInfo.HasMovementFlag(MOVEFLAG_FLYING2)) && !plMover->CanFly() && !plMover->isGameMaster() && (opcode != 201))// && !(plMover->HasAuraType(SPELL_AURA_FLY) || plMover->HasAuraType(SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED)))
            {
                Anti__CheatOccurred(CurTime, "Fly hack", 0.0f, LookupOpcodeName(opcode), 0.0f, movementInfo.GetMovementFlags());
            }

            //Teleport To Plane checks
            if (movementInfo.GetPos()->z < 0.0001f && movementInfo.GetPos()->z > -0.0001f && (!movementInfo.HasMovementFlag(MovementFlags(MOVEFLAG_SWIMMING | MOVEFLAG_CAN_FLY | MOVEFLAG_FLYING))))
            {
                if (sWorld.GetMvAnticheatTeleport2PlaneCheck() && GetPlayer()->IsFleeing() == 0 && GetPlayer()->IsConfused() == 0)
                {
                    // Prevent using TeleportToPlan.
                    Map *map = GetPlayer()->GetMap();
                    if (map)
                    {
                        float plane_z = map->GetHeight(movementInfo.GetPos()->x, movementInfo.GetPos()->y, MAX_HEIGHT) - movementInfo.GetPos()->z;
                        plane_z = (plane_z < -500.0f) ? 0 : plane_z; //check holes in heigth map
                        if (plane_z > 0.1f || plane_z < -0.1f)
                        {
                            if (sWorld.GetMvAnticheatTeleport2PlaneCheck())
                                Anti__CheatOccurred(CurTime, "Teleport2Plane hack", GetPlayer()->GetPositionZ(), nullptr, plane_z);
                        }
                     }
                }
           }
       }
      // <<---- anti-cheat features
    }

    /* process position-change */
    HandleMoverRelocation(movementInfo);

    if (plMover)
        plMover->UpdateFallInformationIfNeed(movementInfo, opcode);

    WorldPacket data(opcode, recv_data.size());
    data << mover->GetPackGUID();                           // write guid
    movementInfo.Write(data);                               // write data
    mover->SendMessageToSetExcept(data, _player);
}

void WorldSession::HandleForceSpeedChangeAckOpcodes(WorldPacket& recv_data)
{
    Opcodes opcode = recv_data.GetOpcode();
    DEBUG_LOG("WORLD: Received %s (%u, 0x%X) opcode", recv_data.GetOpcodeName(), opcode, opcode);

    /* extract packet */
    ObjectGuid guid;
    MovementInfo movementInfo;
    float  newspeed;

    recv_data >> guid;
    recv_data >> Unused<uint32>();                          // counter or moveEvent
    recv_data >> movementInfo;
    recv_data >> newspeed;

    // now can skip not our packet
    if (_player->GetObjectGuid() != guid)
        return;
    /*----------------*/

    // client ACK send one packet for mounted/run case and need skip all except last from its
    // in other cases anti-cheat check can be fail in false case
    UnitMoveType move_type;
    UnitMoveType force_move_type;

    static char const* move_type_name[MAX_MOVE_TYPE] = {  "Walk", "Run", "RunBack", "Swim", "SwimBack", "TurnRate", "Flight", "FlightBack" };

    switch (opcode)
    {
        case CMSG_FORCE_WALK_SPEED_CHANGE_ACK:          move_type = MOVE_WALK;          force_move_type = MOVE_WALK;        break;
        case CMSG_FORCE_RUN_SPEED_CHANGE_ACK:           move_type = MOVE_RUN;           force_move_type = MOVE_RUN;         break;
        case CMSG_FORCE_RUN_BACK_SPEED_CHANGE_ACK:      move_type = MOVE_RUN_BACK;      force_move_type = MOVE_RUN_BACK;    break;
        case CMSG_FORCE_SWIM_SPEED_CHANGE_ACK:          move_type = MOVE_SWIM;          force_move_type = MOVE_SWIM;        break;
        case CMSG_FORCE_SWIM_BACK_SPEED_CHANGE_ACK:     move_type = MOVE_SWIM_BACK;     force_move_type = MOVE_SWIM_BACK;   break;
        case CMSG_FORCE_TURN_RATE_CHANGE_ACK:           move_type = MOVE_TURN_RATE;     force_move_type = MOVE_TURN_RATE;   break;
        case CMSG_FORCE_FLIGHT_SPEED_CHANGE_ACK:        move_type = MOVE_FLIGHT;        force_move_type = MOVE_FLIGHT;      break;
        case CMSG_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK:   move_type = MOVE_FLIGHT_BACK;   force_move_type = MOVE_FLIGHT_BACK; break;
        default:
            sLog.outError("WorldSession::HandleForceSpeedChangeAck: Unknown move type opcode: %u", opcode);
            return;
    }

    // skip all forced speed changes except last and unexpected
    // in run/mounted case used one ACK and it must be skipped.m_forced_speed_changes[MOVE_RUN} store both.
    if (_player->m_forced_speed_changes[force_move_type] > 0)
    {
        --_player->m_forced_speed_changes[force_move_type];
        if (_player->m_forced_speed_changes[force_move_type] > 0)
            return;
    }

    if (!_player->GetTransport() && fabs(_player->GetSpeed(move_type) - newspeed) > 0.01f)
    {
        if (_player->GetSpeed(move_type) > newspeed)        // must be greater - just correct
        {
            sLog.outError("%sSpeedChange player %s is NOT correct (must be %f instead %f), force set to correct value",
                          move_type_name[move_type], _player->GetName(), _player->GetSpeed(move_type), newspeed);
            _player->SetSpeedRate(move_type, _player->GetSpeedRate(move_type), true);
        }
        else                                                // must be lesser - cheating
        {
            BASIC_LOG("Player %s from account id %u kicked for incorrect speed (must be %f instead %f)",
                      _player->GetName(), _player->GetSession()->GetAccountId(), _player->GetSpeed(move_type), newspeed);
            _player->GetSession()->KickPlayer();
        }
    }
}

void WorldSession::HandleSetActiveMoverOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("WORLD: Received opcode CMSG_SET_ACTIVE_MOVER");

    ObjectGuid guid;
    recv_data >> guid;

    if (_player->GetMover()->GetObjectGuid() != guid)
    {
        sLog.outError("HandleSetActiveMoverOpcode: incorrect mover guid: mover is %s and should be %s",
                      _player->GetMover()->GetGuidStr().c_str(), guid.GetString().c_str());
        return;
    }
}

void WorldSession::HandleMoveNotActiveMoverOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("WORLD: Received opcode CMSG_MOVE_NOT_ACTIVE_MOVER");
    recv_data.hexlike();

    ObjectGuid old_mover_guid;
    MovementInfo mi;

    recv_data >> old_mover_guid;
    recv_data >> mi;

    if (_player->GetMover() && _player->GetMover()->GetObjectGuid() == old_mover_guid)
    {
        sLog.outError("HandleMoveNotActiveMover: incorrect mover guid: mover is %s and should be %s instead of %s",
                      _player->GetMover()->GetGuidStr().c_str(),
                      _player->GetGuidStr().c_str(),
                      old_mover_guid.GetString().c_str());
        recv_data.rpos(recv_data.wpos());                   // prevent warnings spam
        return;
    }

    _player->m_movementInfo = mi;
}

void WorldSession::HandleMountSpecialAnimOpcode(WorldPacket& /*recvdata*/)
{
    // DEBUG_LOG("WORLD: Received opcode CMSG_MOUNTSPECIAL_ANIM");

    WorldPacket data(SMSG_MOUNTSPECIAL_ANIM, 8);
    data << GetPlayer()->GetObjectGuid();

    GetPlayer()->SendMessageToSet(data, false);
}

void WorldSession::HandleMoveKnockBackAck(WorldPacket& recv_data)
{
    DEBUG_LOG("CMSG_MOVE_KNOCK_BACK_ACK");

    Unit* mover = _player->GetMover();
    Player* plMover = mover->GetTypeId() == TYPEID_PLAYER ? (Player*)mover : nullptr;

    // ignore, waiting processing in WorldSession::HandleMoveWorldportAckOpcode and WorldSession::HandleMoveTeleportAck
    if (plMover && plMover->IsBeingTeleported())
    {
        recv_data.rpos(recv_data.wpos());                   // prevent warnings spam
        return;
    }

    ObjectGuid guid;
    MovementInfo movementInfo;

    recv_data >> guid;
    recv_data >> Unused<uint32>();                          // knockback packets counter
    recv_data >> movementInfo;

    if (!VerifyMovementInfo(movementInfo, guid))
        return;

    HandleMoverRelocation(movementInfo);

    WorldPacket data(MSG_MOVE_KNOCK_BACK, recv_data.size() + 15);
    data << mover->GetObjectGuid();
    data << movementInfo;
    data << movementInfo.GetJumpInfo().sinAngle;
    data << movementInfo.GetJumpInfo().cosAngle;
    data << movementInfo.GetJumpInfo().xyspeed;
    data << movementInfo.GetJumpInfo().velocity;
    mover->SendMessageToSetExcept(data, _player);
}

void WorldSession::SendKnockBack(float angle, float horizontalSpeed, float verticalSpeed) const
{
    float vsin = sin(angle);
    float vcos = cos(angle);

    WorldPacket data(SMSG_MOVE_KNOCK_BACK, 9 + 4 + 4 + 4 + 4 + 4);
    data << GetPlayer()->GetPackGUID();
    data << uint32(0);                                  // Sequence
    data << float(vcos);                                // x direction
    data << float(vsin);                                // y direction
    data << float(horizontalSpeed);                     // Horizontal speed
    data << float(-verticalSpeed);                      // Z Movement speed (vertical)
    SendPacket(data);
}

void WorldSession::HandleMoveHoverAck(WorldPacket& recv_data)
{
    DEBUG_LOG("CMSG_MOVE_HOVER_ACK");

    MovementInfo movementInfo;

    recv_data >> Unused<uint64>();                          // guid
    recv_data >> Unused<uint32>();                          // unk
    recv_data >> movementInfo;
    recv_data >> Unused<uint32>();                          // unk2
}

void WorldSession::HandleMoveWaterWalkAck(WorldPacket& recv_data)
{
    DEBUG_LOG("CMSG_MOVE_WATER_WALK_ACK");

    MovementInfo movementInfo;

    recv_data.read_skip<uint64>();                          // guid
    recv_data.read_skip<uint32>();                          // unk
    recv_data >> movementInfo;
    recv_data >> Unused<uint32>();                          // unk2
}

void WorldSession::HandleSummonResponseOpcode(WorldPacket& recv_data)
{
    if (!_player->isAlive() || _player->isInCombat())
        return;

    ObjectGuid summonerGuid;
    bool agree;
    recv_data >> summonerGuid;
    recv_data >> agree;

    _player->SummonIfPossible(agree);
}

bool WorldSession::VerifyMovementInfo(MovementInfo const& movementInfo, ObjectGuid const& guid) const
{
    // ignore wrong guid (player attempt cheating own session for not own guid possible...)
    if (guid != _player->GetMover()->GetObjectGuid())
        return false;

    return VerifyMovementInfo(movementInfo);
}

bool WorldSession::VerifyMovementInfo(MovementInfo const& movementInfo) const
{
    if (!MaNGOS::IsValidMapCoord(movementInfo.GetPos()->x, movementInfo.GetPos()->y, movementInfo.GetPos()->z, movementInfo.GetPos()->o))
        return false;

    if (movementInfo.HasMovementFlag(MOVEFLAG_ONTRANSPORT))
    {
        // transports size limited
        // (also received at zeppelin/lift leave by some reason with t_* as absolute in continent coordinates, can be safely skipped)
        if (movementInfo.GetTransportPos()->x > 50 || movementInfo.GetTransportPos()->y > 50 || movementInfo.GetTransportPos()->z > 100)
            return false;

        if (!MaNGOS::IsValidMapCoord(movementInfo.GetPos()->x + movementInfo.GetTransportPos()->x, movementInfo.GetPos()->y + movementInfo.GetTransportPos()->y,
                                     movementInfo.GetPos()->z + movementInfo.GetTransportPos()->z, movementInfo.GetPos()->o + movementInfo.GetTransportPos()->o))
        {
            return false;
        }
    }

    return true;
}

void WorldSession::HandleMoverRelocation(MovementInfo& movementInfo)
{
    if (m_clientTimeDelay == 0)
        m_clientTimeDelay = WorldTimer::getMSTime() - movementInfo.GetTime();
    movementInfo.UpdateTime(movementInfo.GetTime() + m_clientTimeDelay + MOVEMENT_PACKET_TIME_DELAY);

    Unit* mover = _player->GetMover();

    if (Player* plMover = mover->GetTypeId() == TYPEID_PLAYER ? (Player*)mover : nullptr)
    {
        if (movementInfo.HasMovementFlag(MOVEFLAG_ONTRANSPORT))
        {
            if (!plMover->m_transport)
            {
                float trans_rad = movementInfo.GetTransportPos()->x*movementInfo.GetTransportPos()->x + movementInfo.GetTransportPos()->y*movementInfo.GetTransportPos()->y + movementInfo.GetTransportPos()->z*movementInfo.GetTransportPos()->z;
                if (trans_rad > 3600.0f) // transport radius = 60 yards //cheater with on_transport_flag
                    return;

                // elevators also cause the client to send MOVEFLAG_ONTRANSPORT - just unmount if the guid can be found in the transport list
                for (MapManager::TransportSet::const_iterator iter = sMapMgr.m_Transports.begin(); iter != sMapMgr.m_Transports.end(); ++iter)
                {
                    if ((*iter)->GetObjectGuid() == movementInfo.GetTransportGuid())
                    {
                        plMover->m_transport = (*iter);
                        (*iter)->AddPassenger(plMover);
                        break;
                    }
                }
            }
        }
        else if (plMover->m_transport)               // if we were on a transport, leave
        {
            plMover->m_transport->RemovePassenger(plMover);
            plMover->m_transport = nullptr;
            movementInfo.ClearTransportData();
        }

        if (movementInfo.HasMovementFlag(MOVEFLAG_SWIMMING) != plMover->IsInWater())
        {
            // now client not include swimming flag in case jumping under water
            plMover->SetInWater(!plMover->IsInWater() || plMover->GetTerrain()->IsUnderWater(movementInfo.GetPos()->x, movementInfo.GetPos()->y, movementInfo.GetPos()->z));
            if (plMover->GetTerrain()->IsUnderWater(movementInfo.GetPos()->x, movementInfo.GetPos()->y, movementInfo.GetPos()->z - 7.0f))
                plMover->m_anti_BeginFallZ = INVALID_HEIGHT;
        }

        plMover->SetPosition(movementInfo.GetPos()->x, movementInfo.GetPos()->y, movementInfo.GetPos()->z, movementInfo.GetPos()->o);
        plMover->m_movementInfo = movementInfo;

        if (movementInfo.GetPos()->z < -500.0f)
        {
            if (plMover->GetBattleGround()
                    && plMover->GetBattleGround()->HandlePlayerUnderMap(_player))
            {
                // do nothing, the handle already did if returned true
            }
            else
            {
                // NOTE: this is actually called many times while falling
                // even after the player has been teleported away
                // TODO: discard movement packets after the player is rooted
                if (plMover->isAlive())
                {
                    plMover->EnvironmentalDamage(DAMAGE_FALL_TO_VOID, plMover->GetMaxHealth());
                    // pl can be alive if GM/etc
                    if (!plMover->isAlive())
                    {
                        // change the death state to CORPSE to prevent the death timer from
                        // starting in the next player update
                        plMover->KillPlayer();
                        plMover->BuildPlayerRepop();
                    }
                }

                // cancel the death timer here if started
                plMover->RepopAtGraveyard();
            }
        }
    }
    else                                                    // creature charmed
    {
        if (mover->IsInWorld())
            mover->GetMap()->CreatureRelocation((Creature*)mover, movementInfo.GetPos()->x, movementInfo.GetPos()->y, movementInfo.GetPos()->z, movementInfo.GetPos()->o);
    }
}
