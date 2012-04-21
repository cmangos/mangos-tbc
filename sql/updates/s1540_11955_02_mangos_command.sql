ALTER TABLE db_version CHANGE COLUMN required_s1540_11955_01_mangos_mangos_string required_s1540_11955_02_mangos_command bit;

DELETE FROM command WHERE name LIKE 'hover';
