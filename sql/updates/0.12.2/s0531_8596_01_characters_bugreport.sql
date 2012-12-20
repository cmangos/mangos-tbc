ALTER TABLE character_db_version CHANGE COLUMN required_s0507_8339_02_characters_character_battleground_data required_s0531_8596_01_characters_bugreport bit;

ALTER TABLE `bugreport` CHANGE `type` `type` LONGTEXT NOT NULL;
ALTER TABLE `bugreport` CHANGE `content` `content` LONGTEXT NOT NULL;
