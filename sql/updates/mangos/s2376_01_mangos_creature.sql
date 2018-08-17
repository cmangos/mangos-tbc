ALTER TABLE db_version CHANGE COLUMN required_s2375_01_mangos_trainer_greeting required_s2376_01_mangos_creature bit;

ALTER TABLE `creature` CHANGE COLUMN `curhealth` `curhealth` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `currentwaypoint`;

UPDATE `creature` SET `curhealth` = 0 WHERE `curhealth` = 1;  