ALTER TABLE db_version CHANGE COLUMN required_s0671_11002_01_mangos_spell_proc_event required_s0681_8992_01_mangos_spell_proc_event bit;

/*Ferocious Inspiration*/
DELETE FROM `spell_proc_event` WHERE `entry` IN (34457);
INSERT INTO `spell_proc_event` VALUES
(34457, 0x00,  0, 0x0000000000000000, 0x00000000, 0x00000002, 0.000000, 0.000000,  0);

/*Frenzy*/
DELETE FROM `spell_proc_event` WHERE `entry` IN (20784);
INSERT INTO `spell_proc_event` VALUES 
(20784, 0x00,  0, 0x0000000000000000, 0x00000000, 0x00000002, 0.000000, 0.000000,  0);
