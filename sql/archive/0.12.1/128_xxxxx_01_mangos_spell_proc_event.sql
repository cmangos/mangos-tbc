ALTER TABLE db_version CHANGE COLUMN required_127_10045_01_mangos_spell_proc_event required_128_xxxxx_01_mangos_spell_proc_event bit;

DELETE FROM  `spell_proc_event` WHERE `entry` IN (20210);

INSERT INTO `spell_proc_event` VALUES
(20210, 0x00, 10, 0x00010000C0000000, 0x00000000, 0x00000002, 0.000000, 0.000000,  0);
