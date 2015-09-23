ALTER TABLE db_version CHANGE COLUMN required_s0356_10621_01_mangos_quest_template required_s0378_xxxxx_01_mangos_spell_proc_event bit;

DELETE FROM spell_proc_event WHERE entry IN (33953);
INSERT INTO spell_proc_event VALUES
(33953, 0x00,  0, 0x0000000000000000, 0x00000000, 0x00000000, 0.000000, 0.000000, 45);