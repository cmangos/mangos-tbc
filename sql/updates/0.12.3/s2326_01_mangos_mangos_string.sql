ALTER TABLE db_version CHANGE COLUMN required_s2325_03_mangos required_s2326_01_mangos_mangos_string bit;

DELETE FROM mangos_string WHERE entry=58;

INSERT INTO mangos_string VALUES
(58,'Using script library',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
