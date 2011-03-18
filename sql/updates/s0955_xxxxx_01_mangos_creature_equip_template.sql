ALTER TABLE db_version CHANGE COLUMN required_s0939_9967_01_mangos_spell_proc_event required_s0955_xxxxx_01_mangos_creature_equip_template bit;

DROP TABLE IF EXISTS creature_equip_template_raw;

RENAME TABLE creature_equip_template TO creature_equip_template_raw;

DROP TABLE IF EXISTS `creature_equip_template`;
CREATE TABLE `creature_equip_template` (
  `entry` mediumint(8) unsigned NOT NULL default '0' COMMENT 'Unique entry',
  `equipentry1` mediumint(8) unsigned NOT NULL default '0',
  `equipentry2` mediumint(8) unsigned NOT NULL default '0',
  `equipentry3` mediumint(8) unsigned NOT NULL default '0',
  PRIMARY KEY  (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Creature System (Equipment)';

