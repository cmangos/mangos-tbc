ALTER TABLE character_db_version CHANGE COLUMN required_s2204_12756_01_characters_pvpstats required_s2323_12931_01_characters_guild bit;

ALTER TABLE `guild` CHANGE `info` `info` varchar(500) NOT NULL DEFAULT '';
ALTER TABLE `guild` CHANGE `motd` `motd` varchar(128) NOT NULL DEFAULT '';
