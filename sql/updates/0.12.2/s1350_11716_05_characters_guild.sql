ALTER TABLE character_db_version CHANGE COLUMN required_s1350_11716_04_characters_gameobject_respawn required_s1350_11716_05_characters_guild bit;

ALTER TABLE `guild`
  CHANGE COLUMN `createdate` `createdate` bigint(20) unsigned NOT NULL default '0',
  CHANGE COLUMN `BankMoney` `BankMoney` bigint(20) unsigned NOT NULL default '0';
