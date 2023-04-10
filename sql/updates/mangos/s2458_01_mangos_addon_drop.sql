ALTER TABLE db_version CHANGE COLUMN required_s2457_01_mangos_reference_loot_template_names required_s2458_01_mangos_addon_drop bit;

ALTER TABLE creature_template_addon DROP COLUMN b2_1_flags;
ALTER TABLE creature_addon DROP COLUMN b2_1_flags;

