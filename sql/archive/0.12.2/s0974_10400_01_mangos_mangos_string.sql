ALTER TABLE db_version CHANGE COLUMN required_s0972_10237_01_mangos_spell_bonus_data required_s0974_10400_01_mangos_mangos_string bit;

DELETE FROM mangos_string WHERE entry IN (1165);

INSERT INTO mangos_string VALUES
(1165,'Spell %u not have auras.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
