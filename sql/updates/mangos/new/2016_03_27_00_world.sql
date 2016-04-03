DROP TABLE IF EXISTS `template_item`;
CREATE TABLE `template_item` (
  `templateEntry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `itemEntry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `itemAmount` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `enchantEntry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `gemEntry1` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `gemEntry2` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `gemEntry3` mediumint(8) unsigned NOT NULL DEFAULT '0'
);

DROP TABLE IF EXISTS `template_spell`;
CREATE TABLE `template_spell` (
  `templateEntry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `spellEntry` mediumint(8) unsigned NOT NULL DEFAULT '0'
);
ALTER TABLE `template_spell`
ADD PRIMARY KEY (`templateEntry`, `spellEntry`);

DROP TABLE IF EXISTS `template_reputation`;
CREATE TABLE `template_reputation` (
  `templateEntry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `factionEntry` mediumint(8) unsigned NOT NULL DEFAULT '0'.
  `factionStanding` mediumint(8) unsigned NOT NULL DEFAULT '0'
);
ALTER TABLE `template_reputation`
ADD PRIMARY KEY (`templateEntry`, `factionEntry`);
