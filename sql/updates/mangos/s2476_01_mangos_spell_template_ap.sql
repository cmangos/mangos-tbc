ALTER TABLE db_version CHANGE COLUMN required_s2475_01_mangos_spell_template required_s2476_01_mangos_spell_template_ap bit;

ALTER TABLE `spell_template`
	ADD COLUMN `EffectBonusCoefficientFromAP1` FLOAT NOT NULL DEFAULT '0' AFTER `EffectBonusCoefficient3`,
	ADD COLUMN `EffectBonusCoefficientFromAP2` FLOAT NOT NULL DEFAULT '0' AFTER `EffectBonusCoefficientFromAP1`,
	ADD COLUMN `EffectBonusCoefficientFromAP3` FLOAT NOT NULL DEFAULT '0' AFTER `EffectBonusCoefficientFromAP2`;
