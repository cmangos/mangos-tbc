-- ================================================
-- Table structure for table `characters_limited`
-- ================================================

CREATE TABLE `characters_limited` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `fly_last_date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY  (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Player System';