ALTER TABLE db_version CHANGE COLUMN required_s2055_12579_01_mangos_gameobject_template required_s2055_12579_02_mangos_game_weather bit;

ALTER TABLE `game_weather` ADD `ScriptName` varchar(64) NOT NULL DEFAULT '' AFTER `winter_storm_chance`;
