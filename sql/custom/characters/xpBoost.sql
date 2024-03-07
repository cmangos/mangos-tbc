DROP TABLE IF EXISTS `experience_bracket_cap`;
CREATE TABLE `experience_bracket_cap` (
  `low` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Lower bracket bound',
  `high` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Upper bracket bound',
  `team` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Bracket team',
  `value` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Bracket XP cap',
  PRIMARY KEY (`low`,`high`,`team`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT='XP System';

DROP TABLE IF EXISTS `character_settings`;
CREATE TABLE `character_settings` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Player GUID',
  `id` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Setting ID',
  `value` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Setting value',
  PRIMARY KEY (`guid`,`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT='Player System';