ALTER TABLE db_version CHANGE COLUMN required_s1231_11489_01_mangos_creature_template required_s1234_xxxxx_01_mangos_spell_affect bit;

DELETE FROM `spell_affect` WHERE `entry` IN (17804, 17805);
INSERT INTO spell_affect ( entry , effectId , SpellFamilyMask ) VALUES
(17804, 1, 0x0000000000000008),
(17805, 1, 0x0000000000000008);
