ALTER TABLE character_db_version CHANGE COLUMN required_s2429_01_characters_raf required_s2452_01_characters_fishingSteps bit;

ALTER TABLE characters ADD COLUMN `fishingSteps` TINYINT UNSIGNED NOT NULL DEFAULT '0' AFTER `grantableLevels`;


