ALTER TABLE db_version CHANGE COLUMN required_s1019_10743_02_mangos_spell_chain required_s1022_10746_01_mangos_mangos_string bit;

DELETE FROM mangos_string WHERE entry IN (468);

INSERT INTO mangos_string VALUES
(468,'id: %d eff: %d type: %d duration: %d maxduration: %d name: %s%s%s caster: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
