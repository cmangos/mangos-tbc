ALTER TABLE db_version CHANGE COLUMN required_s2442_01_mangos_npc_vendor required_s2443_01_mangos_creature_addon bit;

ALTER TABLE `creature_template` ADD COLUMN `InteractionPauseTimer` INT(10) DEFAULT -1 NOT NULL AFTER `GossipMenuId`;

