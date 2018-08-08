ALTER TABLE character_db_version CHANGE COLUMN required_s2375_01_characters_pet_loyalty required_s2376_01_characters_taxi_system_format_update bit;

-- Convert data from the previous format into orphaned mode for failsafe loading: orphaned destination
UPDATE `characters` SET `taxi_path` = SUBSTRING_INDEX(`taxi_path`, ':', -1) WHERE LENGTH(`taxi_path`) > 0;
