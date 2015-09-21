ALTER TABLE db_version CHANGE COLUMN required_137_7053_01_mangos_mangos_string required_138_7056_01_mangos_spell_proc_event bit;

-- (33953) Essence of Life ()
DELETE FROM `spell_proc_event` WHERE `entry` IN (33953);
INSERT INTO `spell_proc_event` VALUES
(33953, 0x00, 0, 0x0000000000000000, 0x00004000, 0x00000000, 0.000000, 0.000000, 45);
