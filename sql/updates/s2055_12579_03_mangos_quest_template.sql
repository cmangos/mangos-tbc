ALTER TABLE db_version CHANGE COLUMN  required_s2055_12579_02_mangos_game_weather required_s2055_12579_03_mangos_quest_template bit;

ALTER TABLE `quest_template` ADD COLUMN `MaxLevel` tinyint(3) unsigned NOT NULL DEFAULT '0' AFTER `MinLevel`;
