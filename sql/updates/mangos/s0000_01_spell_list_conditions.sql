-- change of operation enum for CONDITION_WORLDSTATE to official enum
UPDATE conditions SET value2=5 WHERE type=42 AND value2=1;
UPDATE conditions SET value2=6 WHERE type=42 AND value2=2;
UPDATE conditions SET value2=1 WHERE type=42 AND value2=0;

ALTER TABLE creature_spell_targeting ADD COLUMN `UnitCondition` INT(11) NOT NULL DEFAULT -1 AFTER Param3;
ALTER TABLE creature_spell_list ADD COLUMN `CombatCondition` INT(11) NOT NULL DEFAULT -1 AFTER Flags;
