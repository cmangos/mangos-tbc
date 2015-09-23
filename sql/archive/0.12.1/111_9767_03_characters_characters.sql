ALTER TABLE character_db_version CHANGE COLUMN required_106_9751_01_characters required_111_9767_03_characters_characters bit;

ALTER TABLE `characters`
   ADD COLUMN `deleteInfos_Account` int(11) UNSIGNED default NULL AFTER arena_pending_points,
   ADD COLUMN `deleteInfos_Name` varchar(12) default NULL AFTER deleteInfos_Account,
   ADD COLUMN `deleteDate` bigint(20) default NULL AFTER deleteInfos_Name;
