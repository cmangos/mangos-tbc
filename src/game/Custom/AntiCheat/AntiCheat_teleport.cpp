#include "AntiCheat_teleport.h"
#include "Custom/AntiCheat/AntiCheat.h"
#include "Custom/CPlayer.h"

AntiCheat_teleport::AntiCheat_teleport(CPlayer* player) : AntiCheat(player)
{
    antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_TELEPORT;
}

bool AntiCheat_teleport::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, triggeredcheats);

    if (!Initialized())
    {
        serverInitiatedMove = false;
        
        return SetOldMoveInfo(false);
    }

    if (triggeredcheats.none() && !serverInitiatedMove)
    {
        if (!IsMoving(oldmoveInfo) && GetDistOrTransportDist(true) > 0.1f && (!isFalling() || opcode == MSG_MOVE_JUMP))
        {
			m_Player->TeleportToPos(oldMapID, oldmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

            if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
                m_Player->BoxChat << "TELE CHEAT" << "\n";

            return SetOldMoveInfo(true);
        }
    }

    if (opcode == MSG_MOVE_FALL_LAND)
        serverInitiatedMove = false;

    return SetOldMoveInfo(false);
}

void AntiCheat_teleport::HandleKnockBack(float  /*angle*/, float  /*horizontalSpeed*/, float  /*verticalSpeed*/)
{
    serverInitiatedMove = true;
}

void AntiCheat_teleport::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
    AntiCheat::HandleTeleport(map, x, y, z, o);
    serverInitiatedMove = true;
}

