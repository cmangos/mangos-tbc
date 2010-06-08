ALTER TABLE db_version CHANGE COLUMN  required_125_xxxxx_01_mangos_spell_affect required_126_10044_01_mangos_spell_chain bit;

DELETE FROM  `spell_chain` WHERE `spell_id` IN (
 31833, 31835, 31836, 33142, 33145, 33146, 34506,
 34507, 34508, 34838, 34839, 34950, 34954
);
