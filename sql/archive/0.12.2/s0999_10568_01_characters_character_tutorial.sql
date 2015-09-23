ALTER TABLE character_db_version CHANGE COLUMN required_s0963_10156_02_characters_pet_aura required_s0999_10568_01_characters_character_tutorial bit;

DELETE FROM `character_tutorial`; -- for avoid duplication errors and other problems.

ALTER TABLE `character_tutorial` DROP PRIMARY KEY;
ALTER TABLE `character_tutorial` DROP COLUMN `realmid`;
ALTER TABLE `character_tutorial` ADD PRIMARY KEY (`account`);
ALTER TABLE `character_tutorial` DROP KEY `acc_key`;
