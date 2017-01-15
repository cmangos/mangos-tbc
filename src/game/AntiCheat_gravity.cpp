#include "AntiCheat_gravity.h"
#include "CPlayer.h"

AntiCheat_gravity::AntiCheat_gravity(CPlayer* player) : AntiCheat(player)
{
    m_StartFallZ = 0;
    m_Falling = false;

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
        m_StartFallZ = m_MoveInfo[0].GetPos()->z;
        m_StartVelocity = 0.f;
        m_Falling = false;
        return false;
    }

    if (!m_Falling && ((!isFalling(m_MoveInfo[1]) && isFalling(m_MoveInfo[0])) || opcode == MSG_MOVE_JUMP))
    {
        m_Falling = true;
        m_StartFallZ = m_MoveInfo[0].GetPos()->z;
        m_StartVelocity = opcode == MSG_MOVE_JUMP ? m_MoveInfo[0].GetJumpInfo().velocity : 0.f;
    }

    if (isFalling() && m_Player->HasAuraType(SPELL_AURA_FEATHER_FALL))
        m_SlowFall = true;

    float expectedfalldist = computeFallElevation(m_MoveInfo[0].GetFallTime() / 1000.f, m_SlowFall, m_StartVelocity);
    float expectedz = m_StartFallZ - expectedfalldist;

    if (opcode == MSG_MOVE_FALL_LAND)
    {
        if (m_MoveInfo[0].GetPos()->z - expectedz > 1.f) // 1.f is magic precision number
            m_Player->BoxChat << "CHEAT" << std::endl;

        m_Player->BoxChat << "m_StartFallZ: " << m_StartFallZ << std::endl;
        m_Player->BoxChat << "currentz: " << m_MoveInfo[0].GetPos()->z << std::endl;
        m_Player->BoxChat << "expectedz: " << expectedz << std::endl;
        m_Player->BoxChat << "falltime: " << m_MoveInfo[0].GetFallTime() << std::endl;
        m_Player->BoxChat << "velocity: " << m_StartVelocity << std::endl;
        m_Falling = false;
        m_SlowFall = false;
    }

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
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
    m_StartFallZ = m_MoveInfo[0].GetPos()->z;
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