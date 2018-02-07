ALTER TABLE db_version CHANGE COLUMN required_s2370_01_mangos_creatures required_s2370_02_mangos_gameobjects bit;

UPDATE gameobject SET spawntimesecsmax = spawntimesecsmin WHERE spawntimesecsmax < spawntimesecsmin;
