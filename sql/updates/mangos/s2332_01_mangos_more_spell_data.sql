ALTER TABLE db_version CHANGE COLUMN required_s2331_01_mangos_event_linkedto required_s2332_01_mangos_more_spell_data bit;

DELETE FROM `spell_bonus_data` WHERE `entry` IN (42463, 7001);
INSERT INTO `spell_bonus_data` VALUES
(42463, 0.022,  0,       0,     0,     'Paladin - Seal of Vengeance Proc on Enemy (fully stacked)'),
(7001,  0,      0.33,    0,     0,     'Priest - Lightwell Renew');

DELETE FROM `spell_chain` WHERE `spell_id` IN (7001,27873,27874,28276);
INSERT INTO `spell_chain` VALUES
(7001,0,7001,1,0),
(27873,7001,7001,2,0),
(27874,27873,7001,3,0),
(28276,27874,7001,4,0);

DELETE FROM `spell_proc_event` WHERE `entry` IN (18096);
INSERT INTO `spell_proc_event` VALUES
(18096, 0x00,  5, 0x0000008000000060, 0x0000008000000060, 0x0000008000000060, 0x00051000, 0x00000000, 0.000000, 0.000000,  0);
