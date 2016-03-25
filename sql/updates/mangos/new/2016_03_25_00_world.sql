ALTER TABLE `npc_vendor`
DROP COLUMN `slot`,
ADD COLUMN `slot`  tinyint(3) NOT NULL DEFAULT 0 AFTER `item`;

ALTER TABLE `npc_vendor_template`
DROP COLUMN `slot`,
ADD COLUMN `slot`  tinyint(3) NOT NULL DEFAULT 0 AFTER `item`;
