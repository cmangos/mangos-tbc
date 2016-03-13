#include "PlayerBot.h"
#include "World.h"
#include "WorldSession.h"
#include "Database/DatabaseEnv.h"

PlayerBot::PlayerBot(uint32 accountId)
{
    InitializeSession(accountId);
}

PlayerBot::~PlayerBot()
{
    Logout();
}

void PlayerBot::InitializeSession(uint32 accountId)
{
    uint32 security = SEC_PLAYER;
    uint8 expansion = EXPANSION_TBC;
    time_t mutetime = time_t(0);
    LocaleConstant locale = DEFAULT_LOCALE;
    WorldSocket* sock = nullptr;

    WorldSession* session = new WorldSession(accountId, sock, AccountTypes(security), expansion, mutetime, locale);
    if (!session)
        return;

    session->SetPlayerBot(true);
    session->SetPlayerBotActive(true);
    sWorld.AddSession(session);

    m_session = session;
}

bool PlayerBot::Login(ObjectGuid characterId)
{
    if (IsLoggedIn())
        return false;

    m_session->HandleBotPlayerLogin(characterId);

    return true;
}

bool PlayerBot::Logout()
{
    if (!IsLoggedIn())
        return true;

    m_session->LogoutPlayer(true);

    return true;

}

bool PlayerBot::IsLoggedIn()
{
    if (!m_session)
        return false;

    return m_session->GetPlayer();
}

Player* PlayerBot::GetPlayer()
{
    return IsLoggedIn() ? m_session->GetPlayer() : nullptr;
}
