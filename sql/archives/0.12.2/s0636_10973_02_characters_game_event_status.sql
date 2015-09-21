ALTER TABLE character_db_version CHANGE COLUMN required_s0540_8469_01_characters_character_spell required_s0636_10973_02_characters_game_event_status bit;

DROP TABLE IF EXISTS `game_event_status`;
CREATE TABLE `game_event_status` (
  `event` smallint(6) unsigned NOT NULL default '0',
  PRIMARY KEY  (`event`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Game event system';
