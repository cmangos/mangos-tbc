ALTER TABLE db_version CHANGE COLUMN required_s0708_9064_01_mangos_spell_proc_event required_s0794_xxxxx_01_mangos_spell_threat bit;

DELETE FROM spell_threat WHERE entry IN (99,20243);

INSERT INTO `spell_threat` VALUES
(99,42,1,0),
(20243,101,1,0);
