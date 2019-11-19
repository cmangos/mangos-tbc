ALTER TABLE `creature_linking_template`
ADD COLUMN `dist`  float NOT NULL AFTER `search_range`,
ADD COLUMN `angle`  float NOT NULL AFTER `dist`;

ALTER TABLE `creature_linking`
ADD COLUMN `dist`  float NOT NULL AFTER `master_guid`,
ADD COLUMN `angle`  float NOT NULL AFTER `dist`;