ALTER TABLE character_db_version CHANGE COLUMN required_111_9767_03_characters_characters required_106_9751_01_characters bit;

/* must be used ".character deleted old 0" before apply */
ALTER TABLE `characters`
   DROP COLUMN `deleteInfos_Account`,
   DROP COLUMN `deleteInfos_Name`,
   DROP COLUMN `deleteDate`;

