ALTER TABLE db_version CHANGE COLUMN required_s0658_9288_01_mangos_spell_bonus_data required_s0660_10989_01_mangos_loot_template bit;

ALTER TABLE creature_loot_template
  CHANGE COLUMN entry entry mediumint(8) unsigned NOT NULL default '0' COMMENT 'entry 0 used for player insignia loot';

ALTER TABLE fishing_loot_template
  CHANGE COLUMN entry entry mediumint(8) unsigned NOT NULL default '0' COMMENT 'entry 0 used for junk loot at fishing fail (if allowed by config option)';
