ALTER TABLE db_version CHANGE COLUMN required_s2472_01_mangos_precision_decimal required_s2475_01_mangos_spell_template bit;

ALTER TABLE `spell_template`
	ADD COLUMN `EffectBonusCoefficient1` FLOAT NOT NULL DEFAULT '0' AFTER `SchoolMask`,
	ADD COLUMN `EffectBonusCoefficient2` FLOAT NOT NULL DEFAULT '0' AFTER `EffectBonusCoefficient1`,
	ADD COLUMN `EffectBonusCoefficient3` FLOAT NOT NULL DEFAULT '0' AFTER `EffectBonusCoefficient2`;

DROP TABLE `spell_bonus_data`;
