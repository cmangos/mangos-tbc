DROP TABLE IF EXISTS `template_item`;
CREATE TABLE `template_item` (
  `templateEntry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `itemEntry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `itemAmount` tinyint(3) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`templateEntry`,`itemEntry`)
);
