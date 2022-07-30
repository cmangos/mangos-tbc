ALTER TABLE db_version CHANGE COLUMN required_s2443_01_mangos_creature_addon required_s2444_01_mangos_creature_spawn_data_template bit;

ALTER TABLE `creature_spawn_data_template` ADD COLUMN `NpcFlags` INT(10) DEFAULT -1 NOT NULL AFTER `Entry`, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `NpcFlags`, `UnitFlags`, `ModelId`, `EquipmentId`, `CurHealth`, `CurMana`, `SpawnFlags`);

