#include "CPlayer.h"
#include "Custom.h"
#include "World/World.h"

#include <algorithm>
#include <execution>
#include <numeric>

void CPlayer::HandlePvPKill()
{
    if (!sWorld.getConfig(CONFIG_BOOL_PVPREWARD_ENABLE))
        return;

    // Get total damage dealt to victim
    float TotalDMG = std::reduce(
        std::execution::unseq,
        GetDamagers().begin(),
        GetDamagers().end(),
        0.f, // Start value
        [](const float prev, const DMGHEALMap::value_type& current)
        {
            return prev + current.second;
        }
    );

    for (DMGHEALMap::value_type& damager : GetDamagers())
    {
        CPlayer* attacker = sCustom.GetCPlayer(damager.first);
        if (!attacker)
            continue; // Attacker no longer ingame

        float attackReward = damager.second / TotalDMG;
        attacker->AddReward(GetNameLink(true), attackReward);

        // Get total healing done to attacker
        float TotalHeal = std::reduce(
            std::execution::unseq,
            attacker->GetHealers().begin(),
            attacker->GetHealers().end(),
            0.f, // Start value
            [](const float prev, const DMGHEALMap::value_type& current)
            {
                return prev + current.second;
            }
        );

        for (DMGHEALMap::value_type& healinfo : attacker->GetHealers())
        {
            CPlayer* healer = sCustom.GetCPlayer(healinfo.first);
            if (!healer)
                continue; // Healer no longer ingame

            float healReward = attackReward * (healinfo.second / TotalDMG) * (healinfo.second / attacker->GetMaxHealth());
            healer->AddReward(GetNameLink(true), healReward);
        }

        // Decrease everyones healing on an attacker once one target is killed
        // to allow new healers to gain some rewards too.
        std::for_each(
            attacker->GetHealers().begin(),
            attacker->GetHealers().end(),
            [](DMGHEALMap::value_type& current)
            {
                current.second *= 0.75;
            }
        );
    }

    GetDamagers().clear();
    GetHealers().clear();
}

void CPlayer::AddDamage(ObjectGuid guid, uint32 amount)
{
    if (sWorld.getConfig(CONFIG_BOOL_PVPREWARD_ENABLE))
        m_Damagers[guid] += amount;
}

void CPlayer::AddHealing(ObjectGuid guid, uint32 amount)
{
    if (sWorld.getConfig(CONFIG_BOOL_PVPREWARD_ENABLE))
        m_Healers[guid] += amount;
}

void CPlayer::AddReward(std::string name, float amount)
{
    m_rewards.push_back(name + "|r");
    m_PendingReward += amount;

    if (m_PendingReward >= 1)
    {
        uint32 Reward = m_PendingReward * 10000.f;
        m_PendingReward = 0;

        SetMoney(GetMoney() + Reward);
        BoxChat << "You were rewarded with " << GetGoldString(Reward) << " for the kills of " << GetRewardNames() << std::endl;
        m_rewards.clear();
    }
}

std::string CPlayer::GetRewardNames(bool duplicates)
{
    auto Names = m_rewards;

    // Remove duplicates if wanted by caller
    if (!duplicates)
        Names.erase(std::unique(Names.begin(), Names.end()), Names.end());

    std::ostringstream ss;
    for (auto name = Names.begin(); name != Names.end(); ++name)
    {
        auto nextname = name;
        // Get next name in this loop already.
        std::advance(nextname, 1);

        // If next name is last, add "and", else add ",".
        if (nextname == Names.end())
            ss << " and ";
        else if (name != Names.begin())
            ss << ", ";

        ss << *name;
    }

    return ss.str();
}

std::string CPlayer::GetGoldString(uint32 copper)
{
    std::ostringstream ss;

    int32 gold = copper / 10000;
    copper -= gold * 10000;
    int32 silver = copper / 100;
    copper -= silver * 100;

    // If there's more than one gold display gold
    if (gold)
        ss << gold << " Gold";

    // If the value is roundable to gold and silver only, display
    // "and" rather than "," for proper scentence building
    if (gold && silver && !copper)
        ss << " and ";
    else if (gold && silver)
        ss << ", ";

    // Display silver amount
    if (silver)
        ss << silver << " Silver";
    // Display copper amount
    if (copper)
        ss << " and " << copper << " Copper";

    return ss.str();
}