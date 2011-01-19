ALTER TABLE db_version CHANGE COLUMN required_s0696_11023_01_mangos_spell_threat required_s0708_9064_01_mangos_spell_proc_event bit;

DELETE FROM spell_proc_event WHERE entry IN (45355);
INSERT INTO spell_proc_event VALUES
(45355, 0x00,  0, 0x0000000000000000, 0x00000000, 0x00000000, 0.000000, 0.000000, 45);
