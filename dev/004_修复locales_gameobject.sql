-- ============================================================
-- 修复 locales_gameobject 落后于核心的问题
-- 对应核心补丁 s2485_01_mangos_closing_text.sql 的 locales 部分
-- （gameobject_template 的 OpeningText/ClosingText 已存在，无需处理）
-- ============================================================

-- castbarcaption -> opening_text（保留原数据）
ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc1` `opening_text_loc1` varchar(100);
ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc2` `opening_text_loc2` varchar(100);
ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc3` `opening_text_loc3` varchar(100);
ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc4` `opening_text_loc4` varchar(100);
ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc5` `opening_text_loc5` varchar(100);
ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc6` `opening_text_loc6` varchar(100);
ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc7` `opening_text_loc7` varchar(100);
ALTER TABLE `locales_gameobject` CHANGE `castbarcaption_loc8` `opening_text_loc8` varchar(100);

-- 新增 closing_text
ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc1` varchar(100);
ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc2` varchar(100);
ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc3` varchar(100);
ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc4` varchar(100);
ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc5` varchar(100);
ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc6` varchar(100);
ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc7` varchar(100);
ALTER TABLE `locales_gameobject` ADD COLUMN `closing_text_loc8` varchar(100);
