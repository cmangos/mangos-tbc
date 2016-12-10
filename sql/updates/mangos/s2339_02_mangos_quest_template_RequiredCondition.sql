ALTER TABLE db_version CHANGE COLUMN required_s2339_01_mangos_areatrigger_teleport_condition_id required_s2339_02_mangos_quest_template_RequiredCondition bit;

ALTER TABLE quest_template ADD COLUMN RequiredCondition INT(11) UNSIGNED NOT NULL DEFAULT 0 AFTER RequiredSkillValue;


