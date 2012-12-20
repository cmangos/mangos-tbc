ALTER TABLE character_db_version CHANGE COLUMN required_s0858_xxxxx_01_characters_characters required_s0860_9634_01_characters_corpse bit;

ALTER TABLE corpse
  DROP COLUMN data,
  DROP COLUMN zone;
