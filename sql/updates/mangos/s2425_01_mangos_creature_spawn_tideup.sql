ALTER TABLE db_version CHANGE COLUMN required_s2424_01_mangos_creature_spawn_data required_s2425_01_mangos_creature_spawn_tideup bit;

-- Adding a few touches to the previous db version
ALTER TABLE `creature_spawn_data` ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Creature System (Spawn Data)';
ALTER TABLE `creature_spawn_data_template` ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Creature System (Spawn Data Template)';
