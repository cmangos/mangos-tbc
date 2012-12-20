ALTER TABLE db_version CHANGE COLUMN required_s1415_11754_01_mangos_mangos_string required_s1440_11851_01_mangos_string bit;

DELETE FROM mangos_string WHERE entry=816;
INSERT INTO mangos_string VALUES
(816,'Your body is too exhausted to travel to the Spectral Realm.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
