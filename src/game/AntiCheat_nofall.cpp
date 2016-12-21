#include "AntiCheat_nofall.h"
#include "CPlayer.h"
#include "World.h"

AntiCheat_nofall::AntiCheat_nofall(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_nofall::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        m_LastCheck = sWorld.GetGameTime();
        return false;
    }

    Map* pMap = m_Player->GetMap();

    if (!pMap)
        return false;

    if (isTransport())
        return false;

    if (isSwimming())
        return false;

    if (GetDistance2D() < 1.f)
        return false;

    if (std::abs(GetDistanceZ()) > 0.f)
        return SetOldMoveInfo(false);

    float floorz = pMap->GetHeight(m_Player->GetPositionX(), m_Player->GetPositionY(), m_Player->GetPositionZ());

    if (m_MoveInfo[0].GetPos()->z - floorz > JUMPHEIGHT_LAND)
    {
        const Position* p = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);

        m_Player->BoxChat << "NOFALLCHEAT" << "\n";
    }

    return SetOldMoveInfo(false);
}

void AntiCheat_nofall::HandleRelocate(float x, float y, float z, float o)
{
}

void AntiCheat_nofall::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
}