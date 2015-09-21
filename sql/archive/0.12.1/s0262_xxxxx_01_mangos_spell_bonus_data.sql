ALTER TABLE db_version CHANGE COLUMN required_s0251_10537_01_mangos_command required_s0262_xxxxx_01_mangos_spell_bonus_data bit;

DELETE FROM `spell_bonus_data` WHERE `entry` IN ( 596, 2060, 2061, 13908, 32546, 10461, 10460, 6372, 6371, 5672);
INSERT INTO `spell_bonus_data`(`entry`,`direct_bonus`,`dot_bonus`,`ap_bonus`,`comments`) VALUES
(  596, 0.4285, 0, 0, 'Priest - Prayer of Healing'),
( 2060, 1.2353, 0, 0, 'Priest - Greater Heal'),
( 2061, 0.6177, 0, 0, 'Priest - Flash Heal'),
(13908, 0.4286, 0, 0, 'Priest - Desperate Prayer'),
(32546, 0.4286, 0, 0, 'Priest - Binding Heal'),
( 5672, 0.0450, 0, 0, 'Shaman - Healing Stream Totem Rank 1'),
( 6371, 0.0450, 0, 0, 'Shaman - Healing Stream Totem Rank 2'),
( 6372, 0.0450, 0, 0, 'Shaman - Healing Stream Totem Rank 3'),
(10460, 0.0450, 0, 0, 'Shaman - Healing Stream Totem Rank 4'),
(10461, 0.0450, 0, 0, 'Shaman - Healing Stream Totem Rank 5');
