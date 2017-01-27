#include "AntiCheat_waterwalking.h"
#include "CPlayer.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellMgr.h"

AntiCheat_waterwalking::AntiCheat_waterwalking(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_waterwalking::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return SetOldMoveInfo(false);

    if (!cheat && !m_Player->HasAuraType(SPELL_AURA_WATER_WALK) && !m_Player->HasAuraType(SPELL_AURA_GHOST) && newMoveInfo.HasMovementFlag(MOVEFLAG_WATERWALKING))
    {
        m_Player->SetWaterWalk(false);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "WATERWALK CHEAT" << "\n";

        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}
