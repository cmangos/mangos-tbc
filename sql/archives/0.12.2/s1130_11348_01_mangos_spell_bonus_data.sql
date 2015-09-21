ALTER TABLE db_version CHANGE COLUMN required_s1120_11335_02_mangos_mangos_string required_s1130_11348_01_mangos_spell_bonus_data bit;

DELETE FROM spell_bonus_data WHERE entry = 43733;
INSERT INTO spell_bonus_data VALUES
(43733, 0,      0,       0,     0,     'Item - Lightning Zap');
