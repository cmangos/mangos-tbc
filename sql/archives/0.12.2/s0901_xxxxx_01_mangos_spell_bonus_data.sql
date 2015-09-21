ALTER TABLE db_version CHANGE COLUMN required_s0859_11190_01_mangos_pool_gameobject_template required_s0901_xxxxx_01_mangos_spell_bonus_data bit;

DELETE FROM `spell_bonus_data` WHERE `entry` IN (
  17,122,421,589,689,1064,1449,2136,2912,2944,2948,5676,6789,8092,
  11366,11426,17877,17962,18265,25902,25911,25912,27176,29722,
  30283,30451,32379,33073,33110,33763,34861,44457,44459,44461
);

INSERT INTO `spell_bonus_data` VALUES
(44459, 0.4,    0,       0,     'Mage - Living Bomb'),
(44461, 0.4,    0,       0,     'Mage - Living Bomb');

DELETE FROM `spell_bonus_data` WHERE `entry` IN (
  139,596,635,774,8004,8936,13908,19750,25903,25913,25914,27175,32546,33074,44203
);

INSERT INTO `spell_bonus_data` VALUES
(8936,  0,      0.1,     0,     'Druid - Regrowth'),
(33763, 0.3429, 0,       0,     'Druid - Lifebloom');
