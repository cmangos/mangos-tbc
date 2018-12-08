ALTER TABLE db_version CHANGE COLUMN required_s2380_01_mangos_cones required_s2381_01_mangos_creature_template_faction_removal bit;

ALTER TABLE creature_template DROP COLUMN FactionHorde;
ALTER TABLE creature_template CHANGE FactionAlliance Faction SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0';

