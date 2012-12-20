ALTER TABLE db_version CHANGE COLUMN required_126_10044_02_mangos_spell_proc_event required_127_10045_01_mangos_spell_proc_event bit;

DELETE FROM  `spell_proc_event` WHERE `entry` IN (26016, 26021);
