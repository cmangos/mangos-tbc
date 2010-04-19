ALTER TABLE db_version CHANGE COLUMN required_101_9663_01_mangos_mangos_string required_107_9728_01_mangos_gossip_menu_option bit;

UPDATE gossip_menu_option SET option_icon=0 WHERE menu_id=0 AND option_id=16;
