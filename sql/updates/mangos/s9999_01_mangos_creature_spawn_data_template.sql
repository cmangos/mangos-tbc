ALTER TABLE `creature_spawn_data_template` ADD COLUMN `NpcFlags` INT(10) DEFAULT -1 NOT NULL AFTER `Entry`, DROP PRIMARY KEY, ADD PRIMARY KEY (`Entry`, `NpcFlags`, `UnitFlags`, `ModelId`, `EquipmentId`, `CurHealth`, `CurMana`, `SpawnFlags`);

