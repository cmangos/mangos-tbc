ALTER TABLE db_version CHANGE COLUMN required_s0262_xxxxx_01_mangos_spell_bonus_data required_s0263_7388_01_mangos_mangos_string bit;

DELETE FROM mangos_string WHERE entry IN (726,750,751);
INSERT INTO mangos_string VALUES (750,'Not enough players. This game will close in %u mins.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO mangos_string VALUES (751,'Not enough players. This game will close in %u seconds.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
