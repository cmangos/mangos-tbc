ALTER TABLE db_version CHANGE COLUMN required_s1234_xxxxx_01_mangos_spell_affect required_s1244_11513_01_mangos_mangos_string bit;

DELETE FROM mangos_string WHERE entry IN (8);
INSERT INTO mangos_string VALUES
(8,'Command %s have subcommands:',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
