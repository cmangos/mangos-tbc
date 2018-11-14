ALTER TABLE character_db_version CHANGE COLUMN required_s2376_01_characters_taxi_system_format_update required_s2379_01_characters_playerbot_saved_data bit;

ALTER TABLE playerbot_saved_data ADD COLUMN combat_order tinyint(3) unsigned NOT NULL DEFAULT '0' AFTER guid;
ALTER TABLE playerbot_saved_data DROP COLUMN bot_primary_order;
ALTER TABLE playerbot_saved_data DROP COLUMN bot_secondary_order;