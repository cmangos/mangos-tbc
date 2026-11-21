ALTER TABLE db_version CHANGE COLUMN required_s2492_01_mangos_gobject_near_link required_s2494_01_mangos_creature_immunity_flags bit;

ALTER TABLE creature_template ADD COLUMN `ImmunityFlags` INT UNSIGNED NOT NULL DEFAULT 0 AFTER `SchoolImmuneMask`;


