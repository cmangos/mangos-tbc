ALTER TABLE db_version CHANGE COLUMN required_s1932_12401_01_mangos_spell_template required_s1960_12440_01_mangos_spell_area bit;

ALTER TABLE spell_area ADD COLUMN `condition_id` mediumint(8) unsigned NOT NULL default '0' AFTER quest_end;
