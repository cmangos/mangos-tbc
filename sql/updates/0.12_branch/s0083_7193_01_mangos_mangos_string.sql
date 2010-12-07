ALTER TABLE db_version CHANGE COLUMN required_s0080_10307_03_mangos_scripted_event_id required_s0083_7193_01_mangos_mangos_string bit;

UPDATE mangos_string SET content_default = 'Unit Flags: %u.\nDynamic Flags: %u.\nFaction Template: %u.' WHERE entry = 542;
