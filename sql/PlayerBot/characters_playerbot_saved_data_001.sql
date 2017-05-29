-- MySQL Manual Build
--
-- Host: localhost    Database: characters
-- ------------------------------------------------------

--
-- Table structure for table `playerbotai_db_version`
--

-- When updating, don't forget to update revision_sql.h

DROP TABLE IF EXISTS `playerbot_db_version`;
CREATE TABLE `playerbot_db_version` (
  `version` varchar(120) default NULL,
  `characters_playerbot_saved_data_001` bit(1) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Used DB version notes';

--
-- Dumping data for table `playerbotai_db_version`
--

LOCK TABLES `playerbot_db_version` WRITE;
INSERT INTO `playerbot_db_version` VALUES
('PlayerbotAI default database.',NULL);
UNLOCK TABLES;

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
