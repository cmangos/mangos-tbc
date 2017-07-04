#include "AntiCheat_waterwalking.h"
#include "Entities/CPlayer.h"
#include "Spells/Spell.h"
#include "Spells/SpellAuras.h"
#include "Spells/SpellMgr.h"

AntiCheat_waterwalking::AntiCheat_waterwalking(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_waterwalking::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    if (!Initialized())
        return false;

    if (!cheat && !m_Player->HasAuraType(SPELL_AURA_WATER_WALK) && !m_Player->HasAuraType(SPELL_AURA_GHOST) && MoveInfo.HasMovementFlag(MOVEFLAG_WATERWALKING))
    {
        m_Player->SetWaterWalk(false);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "WATERWALK CHEAT" << "\n";

        return true;
    }

    return false;
}
