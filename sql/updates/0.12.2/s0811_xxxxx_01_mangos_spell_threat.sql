ALTER TABLE db_version CHANGE COLUMN required_s0808_9539_01_mangos_spell_bonus_data required_s0811_xxxxx_01_mangos_spell_threat bit;

DELETE FROM spell_threat WHERE entry IN (845, 7369, 11608, 11609, 20569, 25231, 14921, 11775);

INSERT INTO `spell_threat` VALUES
/* Cleave */
(  845,  10, 1, 0),
( 7369,  40, 1, 0),
(11608,  60, 1, 0),
(11609,  70, 1, 0),
(20569, 100, 1, 0),
(25231, 130, 1, 0);
