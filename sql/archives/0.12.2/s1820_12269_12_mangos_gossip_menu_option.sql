ALTER TABLE db_version CHANGE COLUMN required_s1820_12269_11_mangos_gossip_menu required_s1820_12269_12_mangos_gossip_menu_option bit;

ALTER TABLE gossip_menu_option DROP COLUMN cond_3_val_2, DROP COLUMN cond_3_val_1, DROP COLUMN cond_3,
                               DROP COLUMN cond_2_val_2, DROP COLUMN cond_2_val_1, DROP COLUMN cond_2,
                               DROP COLUMN cond_1_val_2, DROP COLUMN cond_1_val_1, DROP COLUMN cond_1;
