ALTER TABLE db_version CHANGE COLUMN required_s2462_01_mangos_creature_drops required_s2463_01_mangos_spawn_data_equip bit;

ALTER TABLE `creature_spawn_data_template` CHANGE `EquipmentId` `EquipmentId` MEDIUMINT(8) NOT NULL DEFAULT '-1';