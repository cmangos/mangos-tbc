ALTER TABLE db_version CHANGE COLUMN required_s2263_12823_04_mangos_creature required_s2324_12916_01_mangos_battleground_template bit;

ALTER TABLE `battleground_template` ADD `StartMaxDist` float NOT NULL DEFAULT 0 AFTER `HordeStartO`;

UPDATE `battleground_template` SET `StartMaxDist`=100 WHERE `id`=1; -- AV
UPDATE `battleground_template` SET `StartMaxDist`=75 WHERE `id` IN (2,3,7); -- WS, AB, EY
