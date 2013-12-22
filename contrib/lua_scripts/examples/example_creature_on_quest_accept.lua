local NpcId =
local QuestId =

local SAY_01 = "Example OnQuestAccept Works"

local function OnQuestAccept(event, player, creature, quest)
    if (quest:GetId() == QuestId) then
        creature:SendUnitSay(SAY_01, 0)
    end
end

RegisterCreatureEvent(NpcId, 31, OnQuestAccept)