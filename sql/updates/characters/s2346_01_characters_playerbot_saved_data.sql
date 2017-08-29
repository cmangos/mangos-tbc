-- MySQL Manual Build
--
-- Host: localhost    Database: characters
-- ------------------------------------------------------

ALTER TABLE character_db_version CHANGE COLUMN required_s2345_01_characters_instance required_s2346_01_characters_playerbot_saved_data bit;

-- ----------------------------
-- Table structure for `playerbot_saved_data`
-- ----------------------------
DROP TABLE IF EXISTS `playerbot_saved_data`;
CREATE TABLE `playerbot_saved_data` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0',
  `bot_primary_order` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `bot_secondary_order` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `primary_target` int(11) unsigned NOT NULL DEFAULT '0',
  `secondary_target` int(11) unsigned NOT NULL DEFAULT '0',
  `pname` varchar(12) NOT NULL DEFAULT '',
  `sname` varchar(12) NOT NULL DEFAULT '',
  `combat_delay` INT(11) unsigned NOT NULL DEFAULT '0',
  `auto_follow` INT(11) unsigned NOT NULL DEFAULT '1',
  `autoequip` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Persistent Playerbot settings per alt';
