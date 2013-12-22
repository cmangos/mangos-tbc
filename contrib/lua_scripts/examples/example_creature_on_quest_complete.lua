local NpcId =
local QuestId =

local SAY_01 = "Example OnQuestComplete Works"

local function OnQuestComplete(event, player, creature, quest)
    if (quest:GetId() == QuestId) then
        creature:SendUnitSay(SAY_01, 0)
    end
end

RegisterCreatureEvent(NpcId, 33, OnQuestComplete)