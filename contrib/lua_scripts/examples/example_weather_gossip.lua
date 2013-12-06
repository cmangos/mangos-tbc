local npcid =

function TestMenuWeather(event, plr, unit)
    plr:GossipMenuAddItem(0, "Test Weather", 0, 1)
    plr:GossipMenuAddItem(0, "Nevermind..", 0, 2)
    plr:GossipSendMenu(1, unit)
end

function TestMenuSelectWeather(event, plr, unit, sender, intid, code)
    if (intid == 1) then
        local weather = FindWeather(plr:GetZoneId())	
	
        if (weather == nil) then
            weather = AddWeather(plr:GetZoneId())
        end

        print (weather:GetZoneId())
	
        weather:SetWeather(2, 3)
        plr:GossipComplete()
    elseif (intid == 2) then
        plr:GossipComplete()
    end
end

RegisterCreatureGossipEvent(npcid, 1, TestMenuWeather)
RegisterCreatureGossipEvent(npcid, 2, TestMenuSelectWeather)