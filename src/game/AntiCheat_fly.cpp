#include "AntiCheat_fly.h"
#include "CPlayer.h"

AntiCheat_fly::AntiCheat_fly(Player* player) : AntiCheat(player)
{
}

bool AntiCheat_fly::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    if (isFlying(m_MoveInfo[0]) && !CanFly())
        m_Player->SetCanFly(false);

    m_MoveInfo[1] = m_MoveInfo[0];
    return false;
}

bool AntiCheat_fly::CanFly()
{
    return m_Player->HasAuraType(SPELL_AURA_FLY) || m_Player->ToCPlayer()->GetGMFly();
}
