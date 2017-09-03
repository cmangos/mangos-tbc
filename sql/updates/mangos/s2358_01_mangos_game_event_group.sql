ALTER TABLE db_version CHANGE COLUMN required_s2356_01_mangos_dbscript_string_rename required_s2358_01_mangos_game_event_group bit;

ALTER TABLE game_event
ADD EventGroup mediumint(8) unsigned NOT NULL DEFAULT '0' AFTER linkedTo;


