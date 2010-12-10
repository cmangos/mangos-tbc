ALTER TABLE db_version CHANGE COLUMN required_s0481_8249_02_mangos_spell_chain required_s0481_xxxxx_03_mangos_spell_bonus_data bit;

DELETE FROM spell_bonus_data WHERE entry IN (8037, 10458, 16352, 16353, 25501);
