ALTER TABLE db_version CHANGE COLUMN required_s2450_01_mangos_quest_maxlevel required_s2451_01_mangos_waypoint_path_name bit;

DROP TABLE IF EXISTS waypoint_path_name;
CREATE TABLE waypoint_path_name(
  `PathId` int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Path ID for entry',
  `Name` VARCHAR(300) NOT NULL COMMENT 'Description of usage',
  PRIMARY KEY(`PathId`)
);


