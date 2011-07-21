ALTER TABLE db_version CHANGE COLUMN required_s1308_xxxxx_01_mangos_instance_template required_s1329_11679_01_mangos_spell_proc_event bit;

DELETE FROM spell_proc_event WHERE entry = 31785;
INSERT INTO spell_proc_event VALUES
(31785, 0x7F,  0, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x00000000, 0x00040003, 0.000000, 0.000000,  0);
