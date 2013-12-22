local NpcId =

local function TestMenuWeather(event, plr, unit)
    plr:GossipMenuAddItem(0, "Test Weather", 0, 1)
    plr:GossipMenuAddItem(0, "Nevermind..", 0, 2)
    plr:GossipSendMenu(1, unit)
end

local function TestMenuSelectWeather(event, plr, unit, sender, intid, code)
    if (intid == 1) then
        local weather = FindWeather(plr:GetZoneId()) or AddWeather(plr:GetZoneId())
        if (not weather) then
            error("Unable to find or add weather to zone ("..plr:GetZoneId()..")")
            return
        end

        print (weather:GetZoneId())
        print (weather:GetScriptId())

        weather:SetWeather(2, 3)
        plr:GossipComplete()
    elseif (intid == 2) then
        plr:GossipComplete()
    end
end

RegisterCreatureGossipEvent(NpcId, 1, TestMenuWeather)
RegisterCreatureGossipEvent(NpcId, 2, TestMenuSelectWeather)