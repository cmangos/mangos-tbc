ALTER TABLE db_version CHANGE COLUMN required_s0803_11115_01_mangos_command required_s0806_xxxxx_01_mangos_spell_threat bit;

DELETE FROM spell_threat WHERE entry IN (99, 1735, 9490, 9747, 9898, 26998, 30016, 30022);

INSERT INTO `spell_threat` VALUES
(   99,  15, 1, 0),
( 1735,  25, 1, 0),
( 9490,  29, 1, 0),
( 9747,  36, 1, 0),
( 9898,  42, 1, 0),
(26998,  49, 1, 0);
