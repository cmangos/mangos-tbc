ALTER TABLE db_version CHANGE COLUMN required_s1997_xxxxx_01_mangos_command required_s1997_xxxxx_02_mangos_mangos_string bit;

DELETE FROM mangos_string WHERE entry = 371;
