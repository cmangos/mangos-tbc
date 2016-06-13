ALTER TABLE db_version CHANGE COLUMN required_s2328_01_mangos_scriptdev2_tables required_s2329_01_mangos_creature_template bit;

ALTER TABLE creature_template ADD COLUMN SchoolImmuneMask INT(10) UNSIGNED DEFAULT 0 NOT NULL AFTER MechanicImmuneMask; 