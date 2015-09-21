ALTER TABLE character_db_version CHANGE COLUMN required_s0384_10664_01_characters_arena_team_stats required_s0386_10662_01_characters_item_loot bit;

DROP TABLE IF EXISTS `item_loot`;
CREATE TABLE `item_loot` (
  `guid` int(11) unsigned NOT NULL default '0',
  `owner_guid` int(11) unsigned NOT NULL default '0',
  `itemid` int(11) unsigned NOT NULL default '0',
  `amount` int(11) unsigned NOT NULL default '0',
  `suffix` int(11) unsigned NOT NULL default '0',
  `property` int(11) NOT NULL default '0',
  PRIMARY KEY  (`guid`,`itemid`),
  KEY `idx_owner_guid` (`owner_guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Item System';
