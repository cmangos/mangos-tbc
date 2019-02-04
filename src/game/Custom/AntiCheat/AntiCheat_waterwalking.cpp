#include "AntiCheat_waterwalking.h"
#include "Custom/CPlayer.h"
#include "Spells/Spell.h"
#include "Spells/SpellAuras.h"
#include "Spells/SpellMgr.h"

AntiCheat_waterwalking::AntiCheat_waterwalking(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_waterwalking::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return SetOldMoveInfo(false);

    if (!cheat && !CanWaterwalk() && MoveInfo->HasMovementFlag(MOVEFLAG_WATERWALKING))
    {
        m_Player->SetWaterWalk(false);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "WATERWALK CHEAT" << "\n";

        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}
