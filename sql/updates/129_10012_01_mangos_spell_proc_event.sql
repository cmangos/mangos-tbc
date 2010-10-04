ALTER TABLE db_version CHANGE COLUMN required_128_xxxxx_01_mangos_spell_proc_event required_129_10012_01_mangos_spell_proc_event bit;

DELETE FROM `spell_proc_event` WHERE `entry` = 16246;
INSERT INTO `spell_proc_event` VALUES
(16246, 0x00, 11, 0x0000000090100003, 0x00000000, 0x00000000, 0.000000, 0.000000,  0);
