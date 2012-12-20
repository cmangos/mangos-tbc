ALTER TABLE db_version CHANGE COLUMN required_s0345_10628_01_mangos_mangos_string required_s0346_10629_01_mangos_mangos_string bit;

DELETE FROM mangos_string WHERE entry IN (470);

INSERT INTO mangos_string VALUES
(470,'id: %d eff: %d name: %s%s%s caster: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
