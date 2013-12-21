ALTER TABLE db_version CHANGE COLUMN required_s2049_12540_01_mangos_command required_s2055_12579_01_mangos_gameobject_template bit;

ALTER TABLE `gameobject_template` ADD `AIName` char(64) NOT NULL DEFAULT '' AFTER `maxgold`;
