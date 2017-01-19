#include "AntiCheat_gravity.h"
#include "CPlayer.h"

AntiCheat_gravity::AntiCheat_gravity(CPlayer* player) : AntiCheat(player)
{
    m_StartFallZ = 0;
    m_Falling = false;
}

bool AntiCheat_gravity::HandleMovement(MovementInfo& moveInfo, Opcodes opcode, bool cheat)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_Falling = false;
        m_Jumping = false;
        m_SlowFall = false;
        m_StartFallZ = 0.f;
        m_StartVelocity = 0.f;
        m_InitialDiff = 0.f;
        m_MoveInfo[2] = m_MoveInfo[0];
        return SetOldMoveInfo(false);
    }

    bool startfalling = !isFalling(m_MoveInfo[1]) && isFalling(m_MoveInfo[0]);
    bool stopfalling = !isFalling(m_MoveInfo[0]) && isFalling(m_MoveInfo[1]);

    if (!m_Falling)
        m_StartFallZ = m_MoveInfo[0].GetPos()->z;

    uint32 falltime = m_Falling ? m_MoveInfo[0].GetFallTime() : 0;

    if (!m_Falling && (startfalling || opcode == MSG_MOVE_JUMP))
    {
        m_Falling = true;
        m_StartVelocity = (opcode == MSG_MOVE_JUMP ? m_MoveInfo[0].GetJumpInfo().velocity : 0.f);
        m_MoveInfo[2] = opcode == MSG_MOVE_JUMP ? m_MoveInfo[0] : m_MoveInfo[1];

        if (opcode == MSG_MOVE_JUMP)
            m_Jumping = true;
    }

    bool oldslowfall = m_SlowFall;

    if ((m_Falling || isFalling() || opcode == MSG_MOVE_JUMP) && m_Player->HasAuraType(SPELL_AURA_FEATHER_FALL))
        m_SlowFall = true;

    if (!oldslowfall && m_SlowFall)
        m_InitialDiff = 0;

    float expectedfalldist = ComputeFallElevation(falltime / 1000.f, m_SlowFall, m_StartVelocity);
    float expectedz = m_StartFallZ - expectedfalldist;

    float diff = m_MoveInfo[0].GetPos()->z - expectedz;

    if (m_InitialDiff == 0 && diff > 0.f)
        m_InitialDiff = diff;

    if (!m_Jumping)
        diff -= m_InitialDiff;

    if (!cheat && m_Falling && diff > 0.05f) // Make acceptable diff configureable
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "m_StartFallZ: " << m_StartFallZ << std::endl;
            m_Player->BoxChat << "currentz: " << m_MoveInfo[0].GetPos()->z << std::endl;
            m_Player->BoxChat << "expectedz: " << expectedz << std::endl;
            m_Player->BoxChat << "falltime: " << falltime << std::endl;
            m_Player->BoxChat << "velocity: " << m_StartVelocity << std::endl;
            m_Player->BoxChat << "m_SlowFall: " << m_SlowFall << std::endl;
            m_Player->BoxChat << "velocityZ: " << GetDistanceZ() / GetDiffInSec() << std::endl;
            m_Player->BoxChat << "diff: " << diff << std::endl;
            m_Player->BoxChat << "Gravity hack" << std::endl;
        }

        const Position* p = m_MoveInfo[2].GetPos();
        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);

        return SetOldMoveInfo(true);
    }

    if (stopfalling || opcode == MSG_MOVE_FALL_LAND || opcode == MSG_MOVE_START_SWIM)
    {
        m_Falling = false;
        m_Jumping = false;
        m_SlowFall = false;
        m_InitialDiff = 0;
    }

    return SetOldMoveInfo(false);
}

void AntiCheat_gravity::HandleTeleport(uint32 mapid, float x, float y, float z, float o)
{
    AntiCheat::HandleTeleport(mapid, x, y, z, o);
    m_Falling = true;
    m_StartFallZ = z;
    m_StartVelocity = 0.f;
}

void AntiCheat_gravity::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    m_Falling = true;
    m_StartFallZ = m_MoveInfo[0].GetPos()->z;
    m_StartVelocity = -verticalSpeed;
}

float AntiCheat_gravity::ComputeFallElevation(float t_passed, bool isSafeFall, float start_velocity)
{
    double gravity = 19.29110527038574;
    /// Velocity bounds that makes fall speed limited
    float terminalVelocity = isSafeFall ? 7.f : 60.148003f;

    float terminal_length = float(terminalVelocity * terminalVelocity) / (2.f* gravity);
    float terminalFallTime = float(terminalVelocity / gravity); // the time that needed to reach terminalVelocity

    float result = 0.f;

    if (start_velocity > terminalVelocity)
        start_velocity = terminalVelocity;

    float terminal_time = terminalFallTime - start_velocity / gravity; // the time that needed to reach terminalVelocity

    if (t_passed > terminal_time)
    {
        result = terminalVelocity * (t_passed - terminal_time) +
            start_velocity * terminal_time + gravity * terminal_time * terminal_time * 0.5f;
    }
    else
        result = t_passed * (start_velocity + t_passed * gravity * 0.5f);

    return result;
}
