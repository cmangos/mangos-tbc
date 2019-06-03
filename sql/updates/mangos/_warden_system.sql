ALTER TABLE db_version CHANGE COLUMN required_s2374_01_mangos_quest_template_rewmaxrep required_z2720_01_mangos_warden_system bit;

DROP TABLE IF EXISTS `warden`;
CREATE TABLE `warden` (
  `id` smallint(5) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Check ID from warden_checks',
  `groupid` smallint(5) unsigned NOT NULL COMMENT 'The Grouping ID of the warden_checks',
  `build` smallint(5) unsigned NOT NULL COMMENT 'Client build',
  `type` tinyint(3) unsigned DEFAULT NULL COMMENT 'Check Type',
  `data` varchar(48) NOT NULL DEFAULT '',
  `str` varchar(20) NOT NULL DEFAULT '',
  `address` int(10) unsigned NOT NULL DEFAULT '0',
  `length` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `result` varchar(24) NOT NULL DEFAULT '',
  `comment` varchar(50) DEFAULT '' COMMENT 'Description of what the check is',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Warden System';

LOCK TABLES `warden` WRITE;
/*!40000 ALTER TABLE `warden` DISABLE KEYS */;
INSERT INTO `warden` (`id`, `groupid`, `build`, `type`, `data`, `str`, `address`, `length`, `result`, `comment`) VALUES 
/*!40000 ALTER TABLE `warden` ENABLE KEYS */;
UNLOCK TABLES;
