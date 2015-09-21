ALTER TABLE db_version CHANGE COLUMN required_s0046_10263_03_mangos_pool_pool required_s0065_10286_01_mangos_creature_addon bit;

ALTER TABLE creature_addon
  CHANGE `guid` `guid` int(10) unsigned NOT NULL default '0';
