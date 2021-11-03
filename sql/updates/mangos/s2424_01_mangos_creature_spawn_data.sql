ALTER TABLE db_version CHANGE COLUMN required_s2422_01_mangos_creature_template_spells_extension required_s2424_01_mangos_creature_spawn_data bit;

--
-- Table structure for table `creature_spawn_data`
--

DROP TABLE IF EXISTS `creature_spawn_data`;
CREATE TABLE `creature_spawn_data` (
  `Guid` int unsigned NOT NULL COMMENT 'guid of creature',
  `Id` int unsigned NOT NULL COMMENT 'ID of template',
  PRIMARY KEY (`Guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Creature System (Spawn Data)';

--
-- Dumping data for table `creature_spawn_data`
--

LOCK TABLES `creature_spawn_data` WRITE;
/*!40000 ALTER TABLE `creature_spawn_data` DISABLE KEYS */;
/*!40000 ALTER TABLE `creature_spawn_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `creature_spawn_data_template`
--

DROP TABLE IF EXISTS `creature_spawn_data_template`;
CREATE TABLE `creature_spawn_data_template` (
  `Entry` int unsigned NOT NULL COMMENT 'ID of template',
  `UnitFlags` bigint NOT NULL DEFAULT '-1',
  `Faction` int unsigned NOT NULL DEFAULT '0',
  `ModelId` mediumint unsigned NOT NULL DEFAULT '0',
  `EquipmentId` mediumint NOT NULL DEFAULT '0',
  `CurHealth` int unsigned NOT NULL DEFAULT '1',
  `CurMana` int unsigned NOT NULL DEFAULT '0',
  `SpawnFlags` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`Entry`,`UnitFlags`,`ModelId`,`EquipmentId`,`CurHealth`,`CurMana`,`SpawnFlags`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Creature System (Spawn Data Template)';

--
-- Dumping data for table `creature_spawn_data_template`
--

LOCK TABLES `creature_spawn_data_template` WRITE;
/*!40000 ALTER TABLE `creature_spawn_data_template` DISABLE KEYS */;
INSERT INTO `creature_spawn_data_template` (`Entry`) VALUES (0);
/*!40000 ALTER TABLE `creature_spawn_data_template` ENABLE KEYS */;
UNLOCK TABLES;
