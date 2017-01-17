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

    if ((isFalling() || opcode == MSG_MOVE_JUMP) && m_Player->HasAuraType(SPELL_AURA_FEATHER_FALL))
        m_SlowFall = true;

    float expectedfalldist = computeFallElevation(falltime / 1000.f, m_SlowFall, m_StartVelocity);
    float expectedz = m_StartFallZ - expectedfalldist;

    float diff = m_MoveInfo[0].GetPos()->z - expectedz;

    if (m_InitialDiff == 0 && diff > 0.f)
        m_InitialDiff = diff;

    if (!m_Jumping)
        diff -= m_InitialDiff;

    if (m_Falling && diff > 0.05f)
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "m_StartFallZ: " << m_StartFallZ << std::endl;
            m_Player->BoxChat << "currentz: " << m_MoveInfo[0].GetPos()->z << std::endl;
            m_Player->BoxChat << "expectedz: " << expectedz << std::endl;
            m_Player->BoxChat << "falltime: " << falltime << std::endl;
            m_Player->BoxChat << "velocity: " << m_StartVelocity << std::endl;
            m_Player->BoxChat << "diff: " << diff << std::endl;
        }

        m_Player->BoxChat << "Gravitycheat" << std::endl;

        const Position* p = m_MoveInfo[2].GetPos();
        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);
    }

    if (stopfalling || opcode == MSG_MOVE_FALL_LAND || opcode == MSG_MOVE_START_SWIM)
    {
        m_Falling = false;
        m_Jumping = false;
        m_SlowFall = false;
        m_InitialDiff = 0;
    }

    SetOldMoveInfo();

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
    m_Falling = true;
    m_StartFallZ = m_MoveInfo[0].GetPos()->z;
    m_StartVelocity = -verticalSpeed;
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
