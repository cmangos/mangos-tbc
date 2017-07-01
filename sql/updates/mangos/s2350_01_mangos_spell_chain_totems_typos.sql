ALTER TABLE db_version CHANGE COLUMN required_s2349_01_mangos_spell_chain_totems required_s2350_01_mangos_spell_chain_totems_typos bit;

DELETE FROM `spell_chain` WHERE `spell_id` IN (10534);
INSERT INTO `spell_chain` VALUES
(10534,8185,8185,2,0);
