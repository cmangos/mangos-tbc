ALTER TABLE db_version CHANGE COLUMN required_s0028_10208_01_mangos_playercreateinfo required_s0038_10251_01_mangos_command bit;

DELETE FROM command WHERE name = 'wp';
