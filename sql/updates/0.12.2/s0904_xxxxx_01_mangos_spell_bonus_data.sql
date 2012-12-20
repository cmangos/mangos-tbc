ALTER TABLE db_version CHANGE COLUMN required_s0902_11214_02_mangos_command required_s0904_xxxxx_01_mangos_spell_bonus_data bit;

DELETE FROM `spell_bonus_data` WHERE `entry` IN (
  2061,2060,
  5185,774,8936,44203,23455,23458,23459,27803,27804,27805,25329,755
);


INSERT INTO `spell_bonus_data` VALUES
(5185,  1,      0,       0,     'Druid - Healing Touch'),
(774,   0,      0.16,    0,     'Druid - Rejuvenation'),
(8936,  0.3,    0.1,     0,     'Druid - Regrowth'),
(44203, 0.1825, 0,       0,     'Druid - Tranquility Triggered'),
(23455, 0.1606, 0,       0,     'Priest - Holy Nova Heal Rank 1'),
(23458, 0.1606, 0,       0,     'Priest - Holy Nova Heal Rank 2'),
(23459, 0.1606, 0,       0,     'Priest - Holy Nova Heal Rank 3'),
(27803, 0.1606, 0,       0,     'Priest - Holy Nova Heal Rank 4'),
(27804, 0.1606, 0,       0,     'Priest - Holy Nova Heal Rank 5'),
(27805, 0.1606, 0,       0,     'Priest - Holy Nova Heal Rank 6'),
(25329, 0.1606, 0,       0,     'Priest - Holy Nova Heal Rank 7'),
(755,   0,      0.2857,  0,     'Warlock - Health Funnel');
