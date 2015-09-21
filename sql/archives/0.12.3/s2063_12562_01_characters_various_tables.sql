ALTER TABLE character_db_version CHANGE COLUMN required_s1350_11716_09_characters_mail required_s2063_12562_01_characters_various_tables bit;


ALTER TABLE character_queststatus_daily DROP INDEX idx_guid;
ALTER TABLE character_social DROP INDEX friend;
ALTER TABLE character_social DROP INDEX guid;
ALTER TABLE guild_bank_eventlog DROP INDEX guildid_key;
ALTER TABLE guild_bank_item DROP INDEX guildid_key;
ALTER TABLE guild_bank_right DROP INDEX guildid_key;
ALTER TABLE guild_bank_tab DROP INDEX guildid_key;
ALTER TABLE guild_member DROP INDEX guildid_key;
