DROP TABLE IF EXISTS `account_instances_entered`;
CREATE TABLE `account_instances_entered` (
   `accountId` INT(11) UNSIGNED NOT NULL COMMENT 'Player account',
   `enterTime` BIGINT(40) NOT NULL COMMENT 'Time when instance was entered',
   `instanceId` INT(11) UNSIGNED NOT NULL COMMENT 'ID of instance entered',
   PRIMARY KEY(`accountId`,`instanceId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT='Instance reset system';


