ALTER TABLE db_version CHANGE COLUMN required_s2449_01_mangos_spawn_group_chanced_spawns required_s2450_01_mangos_quest_maxlevel bit;

ALTER TABLE `quest_template` ADD COLUMN `MaxLevel` tinyint(3) unsigned NOT NULL DEFAULT '255' AFTER MinLevel;

