ALTER TABLE db_version CHANGE COLUMN required_s1820_12269_12_mangos_gossip_menu_option required_s1825_12278_01_mangos_creature_template bit;

ALTER TABLE creature_template DROP COLUMN spell1, DROP COLUMN spell2, DROP COLUMN spell3, DROP COLUMN spell4;
