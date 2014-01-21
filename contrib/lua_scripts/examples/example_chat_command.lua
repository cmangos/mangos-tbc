local ChatPrefix = "#example"

local function ChatSystem(event, player, msg, _, lang)
    if (msg:sub(1, ChatPrefix:len()) == ChatPrefix) then
        player:SendNotification("Example Chat Command Works")
    end
end

RegisterPlayerEvent(18, ChatSystem)