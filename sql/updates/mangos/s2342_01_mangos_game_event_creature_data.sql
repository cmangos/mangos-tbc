ALTER TABLE db_version CHANGE COLUMN required_s2342_01_mangos_quest_template required_s2342_01_mangos_game_event_creature_data bit;

ALTER TABLE `game_event_creature_data`
ADD COLUMN `vendor_id`  mediumint(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `equipment_id`;