ALTER TABLE db_version CHANGE COLUMN required_s0391_10679_02_mangos_creature_template required_s0407_10704_01_mangos_gossip_menu_option bit;

ALTER TABLE gossip_menu_option CHANGE COLUMN action_menu_id action_menu_id MEDIUMINT(8) NOT NULL DEFAULT '0';
