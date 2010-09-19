ALTER TABLE character_db_version CHANGE COLUMN required_s0201_7255_01_characters_characters required_s0114_09136_01_characters_character_ticket bit;

ALTER TABLE `characters`
  DROP COLUMN `bgid`,
  DROP COLUMN `bgteam`,
  DROP COLUMN `bgmap`,
  DROP COLUMN `bgx`,
  DROP COLUMN `bgy`,
  DROP COLUMN `bgz`,
  DROP COLUMN `bgo`;

