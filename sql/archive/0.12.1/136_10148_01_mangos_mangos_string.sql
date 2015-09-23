ALTER TABLE db_version CHANGE COLUMN required_135_10125_01_mangos_mangos_string required_136_10148_01_mangos_mangos_string bit;

DELETE FROM mangos_string WHERE entry IN (63, 64);
INSERT INTO mangos_string () VALUES
(63, "Accepts whispers", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(64, "Doesn't accept whispers", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
