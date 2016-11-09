ALTER TABLE character_db_version CHANGE COLUMN required_s2333_01_characters_reset_talents required_s2335_01_characters_wotlk_timer_port bit;

DROP TABLE IF EXISTS `character_queststatus_monthly`;
CREATE TABLE `character_queststatus_monthly` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `quest` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Quest Identifier',
  PRIMARY KEY (`guid`,`quest`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Player System';

ALTER TABLE saved_variables
ADD `NextMonthlyQuestResetTime` bigint(40) unsigned NOT NULL DEFAULT '0';
ALTER TABLE saved_variables
ADD `NextWeeklyQuestResetTime` bigint(40) unsigned NOT NULL DEFAULT '0';
