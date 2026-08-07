-- ============================================================
-- locales_gameobject: idempotent fix (safe to re-run)
-- 1) rename castbarcaption_locX -> opening_text_locX if the old
--    column still exists
-- 2) add closing_text_locX if missing
-- ============================================================

-- castbarcaption -> opening_text (loc1)
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'castbarcaption_loc1') > 0,
    'ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc1` `opening_text_loc1` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- castbarcaption -> opening_text (loc2)
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'castbarcaption_loc2') > 0,
    'ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc2` `opening_text_loc2` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- castbarcaption -> opening_text (loc3)
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'castbarcaption_loc3') > 0,
    'ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc3` `opening_text_loc3` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- castbarcaption -> opening_text (loc4)
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'castbarcaption_loc4') > 0,
    'ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc4` `opening_text_loc4` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- castbarcaption -> opening_text (loc5)
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'castbarcaption_loc5') > 0,
    'ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc5` `opening_text_loc5` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- castbarcaption -> opening_text (loc6)
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'castbarcaption_loc6') > 0,
    'ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc6` `opening_text_loc6` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- castbarcaption -> opening_text (loc7)
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'castbarcaption_loc7') > 0,
    'ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc7` `opening_text_loc7` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- castbarcaption -> opening_text (loc8)
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'castbarcaption_loc8') > 0,
    'ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc8` `opening_text_loc8` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- add closing_text_loc1 if missing
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'closing_text_loc1') = 0,
    'ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc1` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- add closing_text_loc2 if missing
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'closing_text_loc2') = 0,
    'ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc2` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- add closing_text_loc3 if missing
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'closing_text_loc3') = 0,
    'ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc3` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- add closing_text_loc4 if missing
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'closing_text_loc4') = 0,
    'ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc4` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- add closing_text_loc5 if missing
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'closing_text_loc5') = 0,
    'ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc5` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- add closing_text_loc6 if missing
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'closing_text_loc6') = 0,
    'ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc6` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- add closing_text_loc7 if missing
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'closing_text_loc7') = 0,
    'ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc7` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;

-- add closing_text_loc8 if missing
SET @sql = IF((SELECT COUNT(*) FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'locales_gameobject' AND COLUMN_NAME = 'closing_text_loc8') = 0,
    'ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc8` varchar(100)', 'SELECT 1');
PREPARE stmt FROM @sql; EXECUTE stmt; DEALLOCATE PREPARE stmt;
