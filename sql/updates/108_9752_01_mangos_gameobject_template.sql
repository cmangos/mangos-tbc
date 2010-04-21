ALTER TABLE db_version CHANGE COLUMN required_107_9728_01_mangos_gossip_menu_option required_108_9752_01_mangos_gameobject_template bit;

ALTER TABLE gameobject_template ADD COLUMN mingold MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER data23;
ALTER TABLE gameobject_template ADD COLUMN maxgold MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER mingold;
