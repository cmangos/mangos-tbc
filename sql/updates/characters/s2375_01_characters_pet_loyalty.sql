ALTER TABLE character_db_version CHANGE COLUMN required_s2370_01_characters_taxi_system_update required_s2375_01_characters_pet_loyalty bit;

ALTER TABLE character_pet ADD COLUMN `xpForNextLoyalty` int(11) unsigned NOT NULL default '0' AFTER `loyalty`;
