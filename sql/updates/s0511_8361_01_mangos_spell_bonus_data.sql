ALTER TABLE db_version CHANGE COLUMN required_s0498_10867_02_mangos_creature_template required_s0511_8361_01_mangos_spell_bonus_data bit;

DELETE FROM `spell_bonus_data` where entry in (40293);

INSERT INTO `spell_bonus_data` VALUES
(40293, 0, 0, 0, 'Item - Siphon Essence');
