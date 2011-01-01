ALTER TABLE db_version CHANGE COLUMN required_s0611_10945_01_mangos_mangos_string required_s0612_10946_01_mangos_spell_proc_event bit;

DELETE FROM spell_proc_event WHERE entry IN (16257, 16277, 16278, 16279, 16280);
DELETE FROM spell_proc_event WHERE entry IN (12966, 12967, 12968, 12969, 12970);

DELETE FROM spell_proc_event WHERE entry IN (12880);
INSERT INTO `spell_proc_event` VALUES
(12880, 0x00,  0, 0x0000000000000000, 0x00000000, 0x00000000, 0.000000, 0.000000,  0);
