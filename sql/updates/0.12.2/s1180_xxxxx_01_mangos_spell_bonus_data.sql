ALTER TABLE db_version CHANGE COLUMN required_s1130_11348_01_mangos_spell_bonus_data required_s1180_xxxxx_01_mangos_spell_bonus_data bit;

DELETE FROM `spell_bonus_data` WHERE `entry` IN (33763);
INSERT INTO `spell_bonus_data` VALUES
(33763, 0.3429, 0.0742,  0,     0,     'Druid - Lifebloom');
