ALTER TABLE db_version CHANGE COLUMN required_s0974_10400_01_mangos_mangos_string required_s1019_10742_01_mangos_spell_bonus_data bit;

ALTER TABLE spell_bonus_data
  ADD COLUMN ap_dot_bonus float NOT NULL default '0' AFTER ap_bonus;

DELETE FROM `spell_bonus_data` WHERE `entry` IN (26573,31803,9007,1822,33745,703,1495,1978,3044,13797,13812);
INSERT INTO `spell_bonus_data` VALUES
(26573, 0,      0.04,    0,     0.04,  'Paladin - Consecration'),
(31803, 0,      0.013,   0,     0.15,  'Paladin - Holy Vengeance'),
(9007,0,0,0,0.03,'Druid - Pounce Bleed'),
(1822,0,0,0,0.02,'Druid - Rake'),
(33745,0,0,0.01,0.01,'Druid - Lacerate'),
(703,0,0,0,0.03,'Rogue - Garrote'),
(1495,0,0,0.2,0,'Hunter - Mongoose Bite'),
(1978,0,0,0,0.02,'Hunter - Serpent Sting'),
(3044,0,0,0.15,0,'Hunter - Arcane Shot'),
(13797,0,0,0,0.02,'Hunter - Immolation Trap'),
(13812,0,0,0.1,0.1,'Hunter - Explosive Trap');
