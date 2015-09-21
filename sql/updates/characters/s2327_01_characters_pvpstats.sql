ALTER TABLE character_db_version CHANGE COLUMN required_s2325_02_characters required_s2327_01_characters_pvpstats bit;

ALTER TABLE pvpstats_players CHANGE COLUMN player_guid character_guid int(10) unsigned NOT NULL AFTER battleground_id;
