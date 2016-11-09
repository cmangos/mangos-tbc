ALTER TABLE db_version CHANGE COLUMN required_s2334_01_mangos_flametongue required_s2336_01_mangos_mangle bit;

DELETE FROM `spell_threat` WHERE `entry` IN (33878, 33986, 33987);
INSERT INTO `spell_threat` VALUES
(33878,       0,  1.3,    0);
