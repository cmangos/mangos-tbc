#include "AntiCheat_jump.h"
#include "Custom/AntiCheat/AntiCheat.h"
#include "Custom/CPlayer.h"

AntiCheat_jump::AntiCheat_jump(CPlayer* player) : AntiCheat(player)
{
    antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_JUMP;
}

bool AntiCheat_jump::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, triggeredcheats);

    if (!Initialized())
        return false;

    if (triggeredcheats.none() && opcode == MSG_MOVE_JUMP && isFalling(oldmoveInfo))
    {
		m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "Jump hack" << "\n";

        return SetOldMoveInfo(true);
    }

    if (opcode == MSG_MOVE_JUMP)
        SetStoredMoveInfo(false);

    return SetOldMoveInfo(false);
}
