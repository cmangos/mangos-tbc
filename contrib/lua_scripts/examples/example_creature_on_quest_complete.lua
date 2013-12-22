local npcId =
local questId =

local function OnQuestComplete(event, player, creature, quest)
    if (quest:GetId() == questId) then
        player:SendNotification("Example OnQuestComplete Works")
    end
end

RegisterCreatureEvent(npcId, 33, OnQuestComplete)