ALTER TABLE db_version CHANGE COLUMN required_s2469_01_mangos_trainer_ability required_s2470_01_mangos_worldstate_expression_spawn_group bit;

ALTER TABLE `spawn_group` ADD COLUMN `WorldStateExpression` INT(11) NOT NULL DEFAULT 0 AFTER `WorldState`;


