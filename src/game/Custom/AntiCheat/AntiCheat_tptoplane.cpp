#include "AntiCheat_tptoplane.h"
#include "Custom/CPlayer.h"

AntiCheat_tptoplane::AntiCheat_tptoplane(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_tptoplane::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return SetOldMoveInfo(false);

    const Position* pn = newmoveInfo->GetPos();
    const Position* po = oldmoveInfo->GetPos();

    if (!m_Player->isAlive())
        return SetOldMoveInfo(false);

    if (std::fabs(po->z) <= 0.0001f && std::fabs(pn->z) <= 0.0001f &&
        std::fabs(po->z - pn->z) < 0.0001f)
    {
        auto groundz = m_Player->GetTerrain()->GetHeightStatic(pn->x, pn->y, pn->y, true);
        if (groundz > pn->z + 2.f)
        {
            if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
                m_Player->BoxChat << "TELEPORT TO PLANE CHEAT" << "\n";

            // Since tptoplane cheats forces the player back to 0.f again
            // The only protection is to kill them and hope they've learned their lesson
            m_Player->EnvironmentalDamage(DAMAGE_FALL_TO_VOID, m_Player->GetHealth());
        }
    }

    return SetOldMoveInfo(false);
}
