-- Fix TBC instances that were improperly assigned 430 in the previous patch
UPDATE `skill_fishing_base_level` SET `skill` = 305 WHERE `entry` IN (3715, 3716, 3717); -- Coilfang Instances
UPDATE `skill_fishing_base_level` SET `skill` = 355 WHERE `entry` IN (4075, 4131); -- Sunwell Instances
UPDATE `skill_fishing_base_level` SET `skill` = 205 WHERE `entry` = 2367; -- Old Hillsbrad

-- Insert missing TBC capitals, subzones, and CoT instances
REPLACE INTO `skill_fishing_base_level` (`entry`, `skill`) VALUES
(3703, 355), -- Shattrath City
(3487, -20), -- Silvermoon City
(3557, -20), -- The Exodar
(3679, 405), -- Skettis
(2366, 205), -- The Black Morass
(3606, 330); -- Hyjal Summit

-- Insert remaining missing high-level subzones from Terokkar and Zangarmarsh
REPLACE INTO `skill_fishing_base_level` (`entry`, `skill`) VALUES
(3720, 355), -- Twin Spire Ruins (Zangarmarsh)
(3680, 405), -- Blackwind Valley (Terokkar)
(3693, 405), -- Skethyl Mountains (Terokkar)
(3975, 405); -- Terokk's Rest (Terokkar)
