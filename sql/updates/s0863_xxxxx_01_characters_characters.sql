ALTER TABLE character_db_version CHANGE COLUMN required_s0860_9634_01_characters_corpse required_s0863_xxxxx_01_characters_characters bit;


UPDATE characters SET exploredZones = CONCAT(TRIM(exploredZones),' ');

UPDATE characters
   SET exploredZones = CONCAT(exploredZones,'0 ')
WHERE length(SUBSTRING_INDEX(exploredZones, ' ', 127)) < length(exploredZones) and length(SUBSTRING_INDEX(exploredZones, ' ', 127+1)) >= length(exploredZones);

/* use this version instead if you have data_backup table in characters DB
UPDATE characters, data_backup SET
  exploredZones = SUBSTRING(data,
  length(SUBSTRING_INDEX(data, ' ', 1332))+2,
  length(SUBSTRING_INDEX(data, ' ', 1459+1))- length(SUBSTRING_INDEX(data, ' ', 1332)) - 1)
  WHERE characters.guid = data_backup.guid;
*/