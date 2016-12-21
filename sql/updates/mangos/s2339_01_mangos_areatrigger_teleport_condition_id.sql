ALTER TABLE db_version CHANGE COLUMN required_s2338_01_mangos_item_extraflags required_s2339_01_mangos_areatrigger_teleport_condition_id bit;

ALTER TABLE areatrigger_teleport ADD COLUMN `condition_id` INT(11) unsigned NOT NULL default '0' AFTER target_orientation;

