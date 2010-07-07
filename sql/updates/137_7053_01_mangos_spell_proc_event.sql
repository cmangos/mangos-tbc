ALTER TABLE db_version CHANGE COLUMN required_136_10148_01_mangos_mangos_string required_137_7053_01_mangos_mangos_string bit;

-- (36541) Curse of Burning Shadows ()
DELETE FROM `spell_proc_event` WHERE `entry` IN (36541);
INSERT INTO `spell_proc_event` VALUES
(36541, 0x04,  0, 0x0000000000000000, 0x00000000, 0x00000000, 0.000000, 0.000000,  0);

-- (37379) Flameshadow ()
DELETE FROM `spell_proc_event` WHERE `entry` IN (37379);
INSERT INTO `spell_proc_event` VALUES
(37379, 0x20,  5, 0x0000000000000000, 0x00000000, 0x00000000, 0.000000, 0.000000,  0);
