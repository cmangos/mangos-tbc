ALTER TABLE db_version CHANGE COLUMN required_s2476_01_mangos_spell_template_ap required_s2477_01_mangos_charmed_spell_list bit;

ALTER TABLE `creature_template` ADD COLUMN `CharmedSpellList` INT NOT NULL DEFAULT '0' COMMENT 'creature_spell_list_entry during charm' AFTER `SpellList`;


