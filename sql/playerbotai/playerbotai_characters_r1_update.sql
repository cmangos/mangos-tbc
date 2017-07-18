-- MySQL Manual Build
--
-- Host: localhost    Database: characters
-- ------------------------------------------------------

--
-- Table structure for table `playerbotai_db_version`
--

-- When updating, don't forget to update revision_sql.h

DROP TABLE IF EXISTS `playerbotai_db_version`;
CREATE TABLE `playerbotai_db_version` (
  `version` varchar(120) default NULL,
  `required_1_playerbotai_initial` bit(1) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Used DB version notes';

--
-- Dumping data for table `playerbotai_db_version`
--

LOCK TABLES `playerbotai_db_version` WRITE;
INSERT INTO `playerbotai_db_version` VALUES
('PlayerbotAI default database.',NULL);
UNLOCK TABLES;
