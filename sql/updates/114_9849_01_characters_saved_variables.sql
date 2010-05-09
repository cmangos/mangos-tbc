ALTER TABLE character_db_version CHANGE COLUMN required_112_8874_01_characters_character_skills required_114_9849_01_characters_saved_variables bit;

ALTER TABLE saved_variables ADD cleaning_flags int(11) unsigned NOT NULL default '0' AFTER NextDailyQuestResetTime;
UPDATE saved_variables SET cleaning_flags = 0xF;
