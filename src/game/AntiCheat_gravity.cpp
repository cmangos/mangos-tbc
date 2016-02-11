#include "AntiCheat_gravity.h"
#include "CPlayer.h"

AntiCheat_gravity::AntiCheat_gravity(CPlayer* player) : AntiCheat(player)
{
    m_StartJumpZ = 0;
    m_StartJumpWater = false;
}

bool AntiCheat_gravity::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        m_StartJumpZ = m_MoveInfo[0].GetPos()->z;
        return false;
    }

    std::stringstream& ss = m_Player->BoxChat;

    if (opcode == MSG_MOVE_JUMP)
    {
        m_StartJumpZ = m_MoveInfo[0].GetPos()->z;
        m_StartJumpWater = m_Player->GetTerrain()->IsUnderWater(m_MoveInfo[0].GetPos()->x, m_MoveInfo[0].GetPos()->y, m_MoveInfo[0].GetPos()->z - 0.5f);
    }

    float jumpdiff = m_MoveInfo[0].GetPos()->z - m_StartJumpZ;

    if (isFalling() && ((m_StartJumpWater && jumpdiff > JUMPHEIGHT_WATER) || (!m_StartJumpWater && jumpdiff > JUMPHEIGHT_LAND)))
    {
        const Position* pos = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);
        ss << "Gravity hacking: " << jumpdiff << "\n";
        ss << "m_StartJumpWater: " << m_StartJumpWater << "\n";

        return true;
    }

    m_MoveInfo[1] = m_MoveInfo[0];
    return false;
}

void AntiCheat_gravity::HandleTeleport()
{
    m_Initialized = false;
}
