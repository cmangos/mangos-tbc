#include "AntiCheat_waterwalking.h"
#include "Custom/CPlayer.h"
#include "Spells/Spell.h"
#include "Spells/SpellAuras.h"
#include "Spells/SpellMgr.h"

AntiCheat_waterwalking::AntiCheat_waterwalking(CPlayer* player) : AntiCheat(player)
{
    antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_WATERWALK;
}

bool AntiCheat_waterwalking::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, triggeredcheats);

    if (!Initialized())
        return false;

    if (!CanWaterwalk() && MoveInfo->HasMovementFlag(MOVEFLAG_WATERWALKING))
    {
        m_Player->SetWaterWalk(false);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "WATERWALK CHEAT" << "\n";

        return true;
    }

    return true;
}
