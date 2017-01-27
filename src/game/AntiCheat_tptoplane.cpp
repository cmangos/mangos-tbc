#include "AntiCheat_tptoplane.h"
#include "CPlayer.h"

AntiCheat_tptoplane::AntiCheat_tptoplane(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_tptoplane::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return SetOldMoveInfo(false);

    const Position* p = newMoveInfo.GetPos();

    if (GetDiff() < 1000 || std::abs(p->z) > 0.1f)
        return false;

    TerrainInfo const* terrain = m_Player->GetTerrain();

    float groundZ = terrain->GetHeightStatic(p->x, p->y, p->z, true);

    float playerZ = p->z;

    if (!cheat && playerZ - groundZ < -1.f && playerZ < groundZ)
    {
        p = oldMoveInfo.GetPos();
        groundZ = terrain->GetHeightStatic(p->x, p->y, p->z);

        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, groundZ, p->o, TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "TELEPORT TO PLANE CHEAT" << "\n";

        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}
