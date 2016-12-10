ALTER TABLE db_version CHANGE COLUMN required_s2339_02_mangos_quest_template_RequiredCondition required_s2339_03_mangos_npc_trainer_conditon_id bit;

ALTER TABLE npc_trainer ADD COLUMN `condition_id` INT(11) unsigned NOT NULL default '0' AFTER reqlevel;


