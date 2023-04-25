-- ================================================
-- Table structure for table `character_talent`
-- ================================================

DROP TABLE IF EXISTS `character_talent`;
CREATE TABLE `character_talent` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0',
  `spell` int(11) unsigned NOT NULL DEFAULT '0',
  `spec` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`,`spell`,`spec`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ================================================
-- Table structure for table `character_action`
-- ================================================
ALTER TABLE `character_action`
  ADD COLUMN `spec` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `guid`,
  DROP PRIMARY KEY,
  ADD PRIMARY KEY (`guid`, `spec`, `button`);
    
-- ================================================
-- Table structure for table `characters`
-- ================================================

ALTER TABLE `characters`
  ADD COLUMN `specCount` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1' AFTER `actionBars`,
  ADD COLUMN `activeSpec` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `specCount`;
    
-- ================================================
-- Table structure for table `character_talent_name`
-- ================================================

DROP TABLE IF EXISTS `character_talent_name`;
CREATE TABLE `character_talent_name` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0',
  `spec` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `name` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`guid`,`spec`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
