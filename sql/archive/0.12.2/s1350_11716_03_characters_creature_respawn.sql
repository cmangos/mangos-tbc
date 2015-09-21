ALTER TABLE character_db_version CHANGE COLUMN required_s1350_11716_02_characters_characters required_s1350_11716_03_characters_creature_respawn bit;

ALTER TABLE `creature_respawn`
  CHANGE COLUMN `respawntime` `respawntime` bigint(20) unsigned NOT NULL default '0';
