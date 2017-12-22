ALTER TABLE db_version CHANGE COLUMN required_s2371_01_mangos_game_event_primary_key required_s2372_01_mangos_creature_template_spells_extension bit;

ALTER TABLE creature_template_spells ADD COLUMN `spell5` mediumint(8) unsigned NOT NULL DEFAULT '0';
ALTER TABLE creature_template_spells ADD COLUMN `spell6` mediumint(8) unsigned NOT NULL DEFAULT '0';
ALTER TABLE creature_template_spells ADD COLUMN `spell7` mediumint(8) unsigned NOT NULL DEFAULT '0';
ALTER TABLE creature_template_spells ADD COLUMN `spell8` mediumint(8) unsigned NOT NULL DEFAULT '0';


