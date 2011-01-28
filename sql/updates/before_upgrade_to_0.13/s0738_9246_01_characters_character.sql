ALTER TABLE character_db_version CHANGE COLUMN required_s0738_9246_01_characters_character required_s0636_10973_02_characters_game_event_status bit;

ALTER TABLE characters
  ADD COLUMN `arena_pending_points` int(10) UNSIGNED NOT NULL default '0' AFTER taxi_path,
  DROP COLUMN `totalHonorPoints`,
  DROP COLUMN `todayHonorPoints`,
  DROP COLUMN `yesterdayHonorPoints`,
  DROP COLUMN `totalKills`,
  DROP COLUMN `todayKills`,
  DROP COLUMN `yesterdayKills`,
  DROP COLUMN `chosenTitle`,
  DROP COLUMN `watchedFaction`,
  DROP COLUMN `drunk`,
  DROP COLUMN `health`,
  DROP COLUMN `power1`,
  DROP COLUMN `power2`,
  DROP COLUMN `power3`,
  DROP COLUMN `power4`,
  DROP COLUMN `power5`;

UPDATE IGNORE characters SET
  arena_pending_points = arenaPoints -
    SUBSTRING(data, length(SUBSTRING_INDEX(data, ' ', 1563))+2, length(SUBSTRING_INDEX(data, ' ', 1563+1))- length(SUBSTRING_INDEX(data, ' ', 1563)) - 1),

ALTER TABLE characters
  DROP COLUMN `arenaPoints`;
