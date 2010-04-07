ALTER TABLE character_db_version CHANGE COLUMN required_102_9687_01_characters_character_queststatus_daily required_097_9611_01_characters bit;

ALTER TABLE `character_queststatus_daily`
  ADD COLUMN `time` bigint(20) unsigned NOT NULL default '0' AFTER `quest`;

ALTER TABLE `saved_variables`
  DROP COLUMN `NextDailyQuestResetTime`;

