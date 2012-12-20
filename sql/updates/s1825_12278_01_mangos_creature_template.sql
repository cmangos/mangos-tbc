ALTER TABLE db_version CHANGE COLUMN required_ required_s1825_12278_01_mangos_creature_template bit;

ALTER TABLE creature_template DROP COLUMN spell1, DROP COLUMN spell2, DROP COLUMN spell3, DROP COLUMN spell4;
