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
        knockBack = false;
        return false;
    }

    if (opcode == MSG_MOVE_FALL_LAND)
        knockBack = false;

    if (opcode == MSG_MOVE_JUMP)
    {
        m_StartJumpZ = m_MoveInfo[0].GetPos()->z;
        m_StartJumpWater = m_Player->GetTerrain()->IsUnderWater(m_MoveInfo[0].GetPos()->x, m_MoveInfo[0].GetPos()->y, m_MoveInfo[0].GetPos()->z - 0.5f);
    }
    else if (!isFalling())
        m_StartJumpZ = m_MoveInfo[0].GetPos()->z;

    float jumpdiff = m_MoveInfo[0].GetPos()->z - m_StartJumpZ;

    if (isFalling(m_MoveInfo[0]) && !knockBack && ((m_StartJumpWater && jumpdiff > JUMPHEIGHT_WATER) || (!m_StartJumpWater && jumpdiff > JUMPHEIGHT_LAND)))
    {
        const Position* pos = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_COMBAT);
        m_Player->BoxChat << "Gravity hacking: " << jumpdiff << "\n";
        m_Player->BoxChat << "m_StartJumpWater: " << m_StartJumpWater << "\n";

        return true;
    }

    return false;
}

void AntiCheat_gravity::HandleRelocate(float x, float y, float z, float o)
{
    AntiCheat::HandleRelocate(x, y, z, o);
    m_StartJumpZ = z;
}

void AntiCheat_gravity::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    knockBack = true;
}
