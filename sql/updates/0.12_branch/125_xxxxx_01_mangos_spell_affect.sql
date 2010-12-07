ALTER TABLE db_version CHANGE COLUMN required_124_8237_01_mangos_creature_template required_125_xxxxx_01_mangos_spell_affect bit;

DELETE FROM spell_affect WHERE entry = 32601 AND effectId = 0 OR entry = 44452 AND effectId = 1;

INSERT INTO spell_affect ( entry , effectId , SpellFamilyMask ) VALUES
(32601, 0, 0x00000009003E0000),
(44452, 1, 0x0000000000004000);
