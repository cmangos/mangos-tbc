ALTER TABLE db_version CHANGE COLUMN required_s2451_01_mangos_waypoint_path_name required_s2452_01_mangos_warlock_t3_vampirism bit;

-- Fix #3941: Warlock Tier 3 (Plagueheart) 2-piece set bonus "Vampirism" (28831)
-- procced on every Shadow Bolt because spell_template.ProcChance was 101.
-- Set it to 10% to match intended behavior.
UPDATE `spell_template` SET `ProcChance` = 10 WHERE `Id` = 28831;
