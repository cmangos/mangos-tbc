ALTER TABLE db_version CHANGE COLUMN required_s0298_7196_01_mangos_spell_chain required_s0298_7196_02_mangos_spell_bonus_data bit;

DELETE FROM spell_bonus_data WHERE entry IN (5672, 6371, 6372, 10460, 10461, 25566, 8004, 331, 139, 974, 15407, 33763, 8936, 44203, 1454);
INSERT INTO spell_bonus_data (entry, direct_bonus, dot_bonus, ap_bonus, comments) VALUES
(1454, 0.8,    0,      0, 'Warlock - Life Tap'),
(5672, 0,      0.0450, 0, 'Shaman - Healing Stream Totem'),
(331,  0.8571, 0,      0, 'Shaman - Healing Wave'),
(8004, 0.4286, 0,      0, 'Shaman - Lesser Healing Wave'),
(974,  0.2857, 0,      0, 'Shaman - Earth Shield'),
(15407,0,      0.19,   0, 'Priest - Mind Flay'),
(139,  0,      0.2,    0, 'Priest - Renew'),
(33763,0.3429, 0.074,  0, 'Druid - Lifebloom'),
(8936, 0.3,    0.1,    0, 'Druid - Regrowth'),
(44203,0.2,    0,      0, 'Druid - Tranquility Triggered');
