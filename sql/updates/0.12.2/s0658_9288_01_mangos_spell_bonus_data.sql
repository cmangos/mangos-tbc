ALTER TABLE db_version CHANGE COLUMN required_s0656_8815_01_mangos_mangos_string required_s0658_9288_01_mangos_spell_bonus_data bit;

DELETE FROM spell_bonus_data WHERE entry IN (31024,38395,5707,17712);
INSERT INTO spell_bonus_data VALUES
(31024,0,0,0,'Item - Living Ruby Pedant'),
(38395,0,0,0,'Item - Siphon Essence'),
(5707,0,0,0,'Item - Lifestone Regeneration'),
(17712,0,0,0,'Item - Lifestone Healing');
