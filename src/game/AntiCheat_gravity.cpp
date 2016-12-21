#include "AntiCheat_gravity.h"
#include "CPlayer.h"

AntiCheat_gravity::AntiCheat_gravity(CPlayer* player) : AntiCheat(player)
{
    m_StartJumpZ = 0;

    gravity = 19.29110527038574;

    /// Velocity bounds that makes fall speed limited
    terminalVelocity = 60.148003f;
    terminalSavefallVelocity = 7.f;

    terminal_length = float(terminalVelocity* terminalVelocity) / (2.f* gravity);
    terminal_savefall_length = (terminalSavefallVelocity* terminalSavefallVelocity) / (2.f* gravity);
    terminalFallTime = float(terminalVelocity / gravity); // the time that needed to reach terminalVelocity
}

bool AntiCheat_gravity::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        m_StartJumpZ = m_MoveInfo[0].GetPos()->z;
        m_StartVelocity = 0.f;
        return false;
    }

    if (!isFalling(m_MoveInfo[1]) && isFalling(m_MoveInfo[0]))
    {
        m_StartJumpZ = m_MoveInfo[0].GetPos()->z;

        m_StartVelocity = m_MoveInfo[0].GetJumpInfo().velocity;
    }

    float expectedZ = computeFallElevation(m_MoveInfo[0].GetFallTime() / 1000.f, false, m_StartVelocity);

    if (opcode == MSG_MOVE_FALL_LAND)
    {
        m_Player->BoxChat << "m_StartJumpZ: " << m_StartJumpZ << std::endl;
        m_Player->BoxChat << "currentZ: " << m_MoveInfo[0].GetPos()->z << std::endl;
        m_Player->BoxChat << "expectedZ: " << m_StartJumpZ - expectedZ << std::endl;
        m_Player->BoxChat << "falltime: " << m_MoveInfo[0].GetFallTime() << std::endl;
        m_Player->BoxChat << "velocity: " << m_StartVelocity << std::endl;
    }

    return false;
}

void AntiCheat_gravity::HandleRelocate(float x, float y, float z, float o)
{
    AntiCheat::HandleRelocate(x, y, z, o);
}

void AntiCheat_gravity::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    m_StartJumpZ = m_MoveInfo[0].GetPos()->z;
    m_StartVelocity = verticalSpeed;
}

float AntiCheat_gravity::computeFallElevation(float t_passed, bool isSafeFall, float start_velocity)
{
    float termVel = isSafeFall ? terminalSavefallVelocity : terminalVelocity;
    float result;

    if (isSafeFall)
        termVel = terminalSavefallVelocity;
    else
        termVel = terminalVelocity;

    if (start_velocity > termVel)
        start_velocity = termVel;

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