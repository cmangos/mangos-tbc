#include "AntiCheat_slowfall.h"
#include "CPlayer.h"
#include "Transports.h"

AntiCheat_slowfall::AntiCheat_slowfall(CPlayer* player) : AntiCheat(player)
{
	m_OldSpeed = 0.f;
}

// Okay, so what we're doing is checking that the player keeps accelerating until he reaches terminal velocity

bool AntiCheat_slowfall::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

	if (GetDistance3D() <= 1.f)
		return false;

	bool onTransport = isTransport(m_MoveInfo[0]) && isTransport(m_MoveInfo[1]);

	float m_Speed = (onTransport ? GetTransportDist3D() : GetDistance3D()) / GetVirtualDiffInSec();

	float m_Speedz = GetDistanceZ() / GetVirtualDiffInSec();

    bool cheat = true;

    if (opcode == MSG_MOVE_JUMP)
        cheat = false;

    if (opcode == MSG_MOVE_FALL_LAND)
        cheat = false;

    if (!isFalling())
        cheat = false;

    if (GetDistanceZ() >= 0.f)
        cheat = false;

	if (m_Speed > m_OldSpeed)
		cheat = false;

	if (m_Speedz < -60.f)
		cheat = false;

    if (cheat)
    {
        m_Player->BoxChat << "SLOWFALL CHEAT" << "\n";
    }
	
	if (GetDistanceZ() <= 0.f)
		m_OldSpeed = m_Speed;
	else
		m_OldSpeed = 0.f;

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_slowfall::HandleRelocate(float x, float y, float z, float o)
{
}

void AntiCheat_slowfall::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
}