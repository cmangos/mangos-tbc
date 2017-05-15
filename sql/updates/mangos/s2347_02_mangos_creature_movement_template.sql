ALTER TABLE db_version CHANGE COLUMN required_s2347_01_mangos_dbscript_string_template required_s2347_02_mangos_creature_movement_template bit;

ALTER TABLE creature_movement_template ADD pathId int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Path ID for entry' AFTER entry, DROP PRIMARY KEY, ADD PRIMARY KEY (entry, pathId, point);
