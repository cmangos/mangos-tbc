ALTER TABLE db_version CHANGE COLUMN required_s2490_01_mangos_spell_threat_mask required_s2491_01_mangos_spillover_rename bit;

ALTER TABLE `quest_template` RENAME COLUMN `ReputationSpilloverMask` TO `RewFactionFlags`;

