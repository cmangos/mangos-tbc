ALTER TABLE character_db_version CHANGE COLUMN required_s2343_01_characters_mangle_cleanup required_s2345_01_characters_instance bit;

ALTER TABLE instance ADD COLUMN `encountersMask` int(10) unsigned NOT NULL DEFAULT '0' AFTER difficulty;


