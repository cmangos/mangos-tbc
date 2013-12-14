local GobId =

local function OnGossipHello(event, player, go)
    player:GossipMenuAddItem(0, "Test Eluna Gossip GameObject", 0, 1)
    player:GossipSendMenu(1, go)
end

local function OnGossipSelect(event, player, go, sender, intid, code)
    if (intid == 1) then
        player:GossipMenuAddItem(0, "Back", 0, 2)
        player:GossipSendMenu(1, go)
    elseif (intid == 2) then
        OnGossipHello(event, player, go)
    end
end

RegisterGameObjectGossipEvent(GobId, 1, OnGossipHello)
RegisterGameObjectGossipEvent(GobId, 2, OnGossipSelect)