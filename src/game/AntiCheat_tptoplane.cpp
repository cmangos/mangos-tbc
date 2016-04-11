#include "AntiCheat_tptoplane.h"
#include "CPlayer.h"

AntiCheat_tptoplane::AntiCheat_tptoplane(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_tptoplane::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    const Position* p = m_MoveInfo[0].GetPos();

    if (GetDiff() < 1000 || abs(p->z) > 0.1f)
        return false;

    TerrainInfo const* terrain = m_Player->GetTerrain();

    float groundZ = terrain->GetHeightStatic(p->x, p->y, p->z, true);

    float playerZ = p->z;

    if (playerZ - groundZ < -1.f && playerZ < groundZ)
    {
        p = m_MoveInfo[1].GetPos();
        groundZ = terrain->GetHeightStatic(p->x, p->y, p->z);

        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, groundZ, p->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);
        m_Player->BoxChat << "TELEPORT TO PLANE CHEAT" << "\n";
    }

    m_MoveInfo[1] = m_MoveInfo[0];
    return false;
}
