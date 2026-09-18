-- Update low level instances that were incorrectly set to -20 (starter zone) instead of 55
UPDATE `skill_fishing_base_level` SET `skill` = 55 WHERE `entry` IN (718, 719);

-- Insert missing instances from the legacy Spell.cpp switch statement
REPLACE INTO `skill_fishing_base_level` (`entry`, `skill`) VALUES
(2557, 330), -- Dire Maul
(3715, 430), -- The Steamvault
(3716, 430), -- The Underbog
(3717, 430), -- The Slave Pens
(2367, 430), -- Old Hillsbrad Foothills
(4075, 430), -- Sunwell Plateau
(4131, 430); -- Magisters' Terrace
