ALTER TABLE db_version CHANGE COLUMN required_s2432_01_mangos_gameobject_spawn_entry required_s2433_01_mangos_anticheat bit;

/*
SQLyog Community v13.1.5  (64 bit)
MySQL - 5.7.20-log : Database - vengeance_world
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
/*Table structure for table `warden_scans` */

DROP TABLE IF EXISTS `warden_scans`;

CREATE TABLE `warden_scans` (
  `id` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `type` int(2) DEFAULT '0',
  `str` text,
  `data` text,
  `address` int(8) DEFAULT '0',
  `length` int(2) DEFAULT '0',
  `result` tinytext NOT NULL,
  `flags` smallint(5) unsigned NOT NULL,
  `comment` tinytext NOT NULL,
  UNIQUE KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=83 DEFAULT CHARSET=utf8;

/*Data for the table `warden_scans` */

insert  into `warden_scans`(`id`,`type`,`str`,`data`,`address`,`length`,`result`,`flags`,`comment`) values 
(1,2,NULL,'82D7E5CBC8D2F78A791E189BAB3FD5D4342BF7EB0CA3F129',74044,NULL,'0',2,'Cheat Engine dll'),
(2,2,NULL,'A444519CC419521B6D39990C1D95329C8D94B59226CBAA98',16507,NULL,'0',2,'WPE PRO dll'),
(3,2,NULL,'3A0F8985E701343E439C74B675C72BBE2D8810A745569913',372624,NULL,'0',2,'rPE dll'),
(4,2,NULL,'6A006A00E897AC0100',7072,NULL,'1',2,'Warden packet process code search sanity check'),
(5,1,'kernel32.dll',NULL,0,0,'1',2,'Warden module search bypass sanity check'),
(6,1,'wpespy.dll',NULL,0,0,'0',2,'WPE Pro'),
(7,1,'speedhack-i386.dll',NULL,0,0,'0',2,'CheatEngine'),
(8,0,NULL,NULL,9093388,6,'686561646572',2,'Packet internal sign - \"header\"'),
(9,0,NULL,NULL,9036012,6,'53595354454D',2,'Packet internal sign - \"SYSTEM\"'),
(10,0,NULL,NULL,8100097,4,'C87A8F00',2,'Jump gravity reference'),
(11,0,NULL,NULL,9403080,4,'D893FEC0',2,'Jump gravity value'),
(12,0,NULL,NULL,8100083,4,'20007408',2,'Jump gravity water'),
(13,0,NULL,NULL,6105764,5,'385F4D7412',2,'Anti root'),
(14,0,NULL,NULL,6103822,1,'F8',2,'Anti move'),
(15,0,NULL,NULL,8100062,1,'75',2,'Anti jump'),
(16,0,NULL,NULL,8103104,3,'8B4F7C',2,'No fall damage'),
(17,0,NULL,NULL,6525996,2,'7419',2,'Super fly'),
(18,0,NULL,NULL,6106878,2,'7819',2,'Heartbeat interval speedhack'),
(19,0,NULL,NULL,6403348,1,'F8',2,'Anti slow hack'),
(20,0,NULL,NULL,6525986,7,'F745F800100000',2,'No fall damage'),
(21,0,NULL,NULL,8099964,3,'100000',2,'Fly hack'),
(22,1,'d3dhook.dll',NULL,0,0,'0',2,'CheatEngine D3D Hook'),
(23,0,NULL,NULL,9208728,4,'BB8D243F',2,'Wall climb'),
(24,0,NULL,NULL,8095957,3,'894808',2,'No fall damage'),
(25,0,NULL,NULL,8979976,8,'000000E04D62503F',2,'Fly hack'),
(26,0,NULL,NULL,6638471,1,'74',2,'Water walk'),
(27,0,NULL,NULL,4685455,1,'74',2,'Hyper mode'),
(28,0,NULL,NULL,4685480,1,'74',2,'Hyper mode'),
(29,0,NULL,NULL,4685502,5,'E89DFD1D00',2,'Hyper mode'),
(30,0,NULL,NULL,4685631,3,'8B450C',2,'Hyper mode'),
(31,0,NULL,NULL,4685653,3,'8B5508',2,'Hyper mode'),
(32,0,NULL,NULL,8100021,1,'6B',2,'Hyper mode'),
(33,0,NULL,NULL,8100052,1,'4C',2,'Hyper mode'),
(34,0,NULL,NULL,8100063,1,'41',2,'Hyper mode'),
(35,0,NULL,NULL,8100078,1,'32',2,'Hyper mode'),
(36,0,NULL,NULL,4760304,2,'721B',2,'P2Point Teleport'),
(37,0,NULL,NULL,4840352,6,'558BEC833D40',2,'LuaProtectionOkay'),
(38,1,'Maelstrom_Keys_Hook.dll',NULL,0,0,'0',2,'WoW Maelstrom keys hook'),
(39,1,'Maelstrom_Mess_Hook.dll',NULL,0,0,'0',2,'WoW Maelstrom mess hook'),
(40,0,NULL,NULL,6518444,2,'DECA',2,'Wow Maelstrom memory patch'),
(41,0,NULL,NULL,6965758,4,'0F84B300',2,'WoW Admin Panel'),
(46,0,NULL,NULL,4774481,3,'0F8465',2,'TranslatePatch'),
(79,1,'SZATYOR.DLL',NULL,0,0,'0',2,'Packet Sniffer - Injected DLL'),
(45,0,NULL,NULL,4653019,3,'83F803',2,'GlueXML_SignaturePatch'),
(47,0,NULL,NULL,4785563,2,'7520',2,'LanguageRestriction'),
(48,0,NULL,NULL,4840370,2,'7465',2,'Lua_Patch'),
(49,0,NULL,NULL,4896176,5,'A1CCECC600',2,'GetCamera (Is this valid?)'),
(50,0,NULL,NULL,4912512,2,'7460',2,'AFK Jump'),
(51,0,NULL,NULL,4912599,2,'7509',2,'Anti AFK'),
(52,0,NULL,NULL,5433092,2,'743C',2,'GlueXML_RenamePatch'),
(53,0,NULL,NULL,5524941,2,'7F17',2,'Show levels'),
(54,0,NULL,NULL,5634208,8,'558BEC568BF1837E',2,'SendPacket function hack'),
(55,0,NULL,NULL,6160566,6,'8B80E0100000',2,'Tracking'),
(56,0,NULL,NULL,6181252,6,'8BB1E4100000',2,'World Tracking'),
(57,0,NULL,NULL,6321600,6,'8B81D40E0000',2,'GetModel (Is this valid?)'),
(58,0,NULL,NULL,6377767,3,'0F8560',2,'NameplatePatch'),
(59,0,NULL,NULL,6518444,2,'DECA',2,'Wallclimb'),
(60,0,NULL,NULL,6559495,2,'8931',2,'TimeSetPatch'),
(61,0,NULL,NULL,6563465,2,'F3A5',2,'TimeSetPatch 2'),
(62,0,NULL,NULL,6583320,2,'7413',2,'Model Hack'),
(63,0,NULL,NULL,6966126,4,'741D8B96',2,'Go through object'),
(64,0,NULL,NULL,6998506,4,'750632C0',2,'Go through buildings'),
(65,0,NULL,NULL,7146485,2,'FFD2',2,'Warden packet read'),
(66,0,NULL,NULL,7641168,6,'8B0D14F8E100',2,'OsGetAsyncTimeMs (Is this valid?)'),
(67,0,NULL,NULL,8095301,2,'7513',2,'Air Jump'),
(68,0,NULL,NULL,8095954,3,'8B4908',2,'Teleport To Plane'),
(69,0,NULL,NULL,8103107,3,'894E3C',2,'NoFallTime'),
(70,0,NULL,NULL,8979979,5,'E04D62503F',2,'Hyper speed'),
(71,0,NULL,NULL,9208732,4,'3630613F',2,'MountainClimbPatch'),
(72,0,NULL,NULL,9208920,8,'000000C0854A3340',2,'Gravity 2'),
(73,0,NULL,NULL,9208923,5,'C0854A3340',2,'Gravity'),
(74,0,NULL,NULL,12339960,4,'8E977042',2,'Fall speed'),
(75,1,'ICANHAZSPEED.DLL',NULL,0,0,'0',2,'ICanHazSpeed - Injected DLL'),
(76,1,'RPE.DLL',NULL,0,0,'0',2,'rEdoX Packet Editor'),
(77,1,'SETPRIV.DLL',NULL,0,0,'0',2,'HideToolz - Injected DLL'),
(78,1,'SPEEDHACK.DLL',NULL,0,0,'0',2,'Cheat Engine - Injected DLL'),
(80,1,'TAMIA.DLL',NULL,0,0,'0',2,'Tamia hack'),
(81,1,'WHIFF.DLL',NULL,0,0,'0',2,'Packet Sniffer - Injected DLL'),
(82,1,'AUTH_BYPASS.DLL',NULL,0,0,'0',2,'Namreeb Auth Password Bypass'),
(83,2,NULL,'FCBDF405450081C6FF3F000081E600C0FFFF8B', '6404', NULL, '0', '2', 'Wow Maelstrom keys hook DLL pattern'),
(84,2,NULL,'80E6FFFF568BCB0FB745FE66BA3C00E8', '38544', NULL, '0', '2', 'Wow Maelstrom mess hook DLL pattern');

DROP TABLE IF EXISTS `warden_check_driver`; 
DROP TABLE IF EXISTS `warden_check_lua`; 
DROP TABLE IF EXISTS `warden_check_memory`; 
DROP TABLE IF EXISTS `warden_check_memory_dynamic`; 
DROP TABLE IF EXISTS `warden_check_module`; 
DROP TABLE IF EXISTS `warden_check_mpq`; 
DROP TABLE IF EXISTS `warden_check_page_a`; 
DROP TABLE IF EXISTS `warden_check_page_b`; 
DROP TABLE IF EXISTS `warden_module`;

REPLACE INTO mangos_string VALUES
(67,'|c00FFFFFF|Announce:',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
