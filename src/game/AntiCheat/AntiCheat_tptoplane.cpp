#include "AntiCheat_tptoplane.h"
#include "Entities/CPlayer.h"

AntiCheat_tptoplane::AntiCheat_tptoplane(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_tptoplane::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return SetoldmoveInfo(false);

    const Position* p = newmoveInfo->GetPos();

    if (GetDiff() < 1000 || std::abs(p->z) > 0.1f)
        return false;

    TerrainInfo const* terrain = m_Player->GetTerrain();

    float groundZ = terrain->GetHeightStatic(p->x, p->y, p->z, true);

    float playerZ = p->z;

    if (!cheat && playerZ - groundZ < -1.f && playerZ < groundZ)
    {
        p = oldmoveInfo->GetPos();
        groundZ = terrain->GetHeightStatic(p->x, p->y, p->z);

		m_Player->TeleportToPos(oldMapID, oldmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "TELEPORT TO PLANE CHEAT" << "\n";

        return SetoldmoveInfo(true);
    }

    return SetoldmoveInfo(false);
}
