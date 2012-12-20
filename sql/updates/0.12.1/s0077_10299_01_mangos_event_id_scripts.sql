ALTER TABLE db_version CHANGE COLUMN required_s0075_10289_02_mangos_creature_model_info required_s0077_10299_01_mangos_event_id_scripts bit;

DROP TABLE IF EXISTS `event_id_scripts`;
CREATE TABLE `event_id_scripts` (
  `id` mediumint(8) NOT NULL,
  `ScriptName` char(64) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Script library scripted events';
