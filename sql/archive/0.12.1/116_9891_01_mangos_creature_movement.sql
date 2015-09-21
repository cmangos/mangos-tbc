ALTER TABLE db_version CHANGE COLUMN required_115_9883_01_mangos_scripts required_116_9891_01_mangos_creature_movement bit;

ALTER TABLE creature_movement ADD COLUMN script_id MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER waittime;
