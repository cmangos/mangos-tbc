ALTER TABLE db_version CHANGE COLUMN required_s0663_8931_01_mangos_spell_bonus_data required_s0671_11002_01_mangos_spell_proc_event bit;

DELETE FROM spell_proc_event WHERE entry IN (23582);
INSERT INTO spell_proc_event VALUES
(23582, 0x00,  8, 0x0000000000000800, 0x00004000, 0x00000000, 0.000000, 0.000000,  0);
