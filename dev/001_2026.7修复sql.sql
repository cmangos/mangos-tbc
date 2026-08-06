-- ============================================
-- 1. 修复冰脉（Icy Veins）与嗜血（Bloodlust）的冲突
--    将法术 12472 的效果光环类型改为 216（可能对应一种不会冲突的机制）
-- ============================================
UPDATE `tbcmangos`.`spell_template` SET `EffectApplyAuraName1` = '216' WHERE (`Id` = '12472');

-- ============================================
-- 2. 修复午夜（Midnight）在普通/英雄模式下的技能可用性
--    将指定技能列表中的第一个技能（Position = 1）的 Availability 设为 0（禁用）
-- ============================================
UPDATE `tbcmangos`.`creature_spell_list` SET `Availability` = '0' WHERE (`Id` = '1615101') AND (`Position` = '1');
UPDATE `tbcmangos`.`creature_spell_list` SET `Availability` = '0' WHERE (`Id` = '1615102') AND (`Position` = '1');

-- ============================================
-- 3. 修复阿图门（Attumen）的语音和广播文本
--    更新 script_texts 表中的声音、类型和广播文本ID
-- ============================================
UPDATE `tbcmangos`.`creature_spell_list` SET `Availability` = '0' WHERE (`Id` = '1615101') and (`Position` = '1');
UPDATE `tbcmangos`.`creature_spell_list` SET `Availability` = '0' WHERE (`Id` = '1615102') and (`Position` = '1');
UPDATE script_texts SET sound = 0, type = 3, broadcast_text_id = 13439 WHERE entry = -1532137;
UPDATE script_texts SET sound = 9167, broadcast_text_id = 13459 WHERE entry = -1532001;
UPDATE script_texts SET sound = 9298, broadcast_text_id = 15378 WHERE entry = -1532002;
UPDATE script_texts SET sound = 9299, broadcast_text_id = 15379 WHERE entry = -1532003;
UPDATE script_texts SET sound = 9168, broadcast_text_id = 13456 WHERE entry = -1532004;
UPDATE script_texts SET sound = 9166, broadcast_text_id = 13490 WHERE entry = -1532007;
UPDATE script_texts SET sound = 9165, broadcast_text_id = 13462 WHERE entry = -1532008;
UPDATE script_texts SET sound = 9173, broadcast_text_id = 15334 WHERE entry = -1532000;
UPDATE script_texts SET sound = 9170, broadcast_text_id = 13460 WHERE entry = -1532009;
UPDATE script_texts SET sound = 9304, broadcast_text_id = 15333 WHERE entry = -1532010;
DELETE FROM script_texts WHERE entry = -1532005;
INSERT INTO script_texts (entry, content_default, sound, type, language, comment, broadcast_text_id) VALUES (-1532005, 'Another trophy to add to my collection!', 9169, 1, 0, 'attumen SAY_KILL_1', 15333);
DELETE FROM script_texts WHERE entry = -1532006;
INSERT INTO script_texts (entry, content_default, sound, type, language, comment, broadcast_text_id) VALUES (-1532006, 'You are no match for me!', 9300, 1, 0, 'attumen SAY_KILL_2', 13460);

-- ============================================
-- 4. 修复象棋事件 AI（增加 staticflags2 标志位 1024）
--    对涉及的生物添加该标志，以启用正确的行为
--    添加移动和转向脚本
-- ============================================
UPDATE `creature_template` 
SET `staticflags2` = `staticflags2` | 1024
WHERE `entry` IN (17469, 21748, 21750, 21747, 21726, 21752, 17211, 21664, 21683, 21682, 21160, 21684);
DELETE FROM `spell_scripts` WHERE id = 30253;
INSERT INTO `spell_scripts` (`id`, `ScriptName`) VALUES
(30253, 'spell_chess_move_to_square');
DELETE FROM `spell_scripts` WHERE id = 30270;
INSERT INTO `spell_scripts` (`id`, `ScriptName`) VALUES
(30270, 'spell_chess_face_square');


-- =====================================================
-- 5.批量修复临时武器附魔持续时间
-- 说明：EffectBasePoints1 存储值为 持续时间秒数 - 1
--       3599 = 3600秒 = 1小时，1799 = 1800秒 = 30分钟
-- =====================================================


-- 1. 磨刀石/平衡石系列：30分钟 → 1小时
UPDATE `spell_template` SET `EffectBasePoints1` = 3599 WHERE `id` IN (    2828, 2829, 2830,    9900, 16138,    22756,    29452, 29453,    3112, 3113, 3114,    9903, 16622,    34339, 34340);

-- 2. 致命毒药（部分等级）：10分钟 → 1小时
UPDATE `spell_template` SET `EffectBasePoints1` = 3599 WHERE `id` IN (    2824, 11355, 11356,    25351, 26967, 27186);

-- 3. 速效毒药：无持续时间 → 1小时
UPDATE `spell_template` SET `EffectBasePoints1` = 3599 WHERE `id` IN (    8679, 8686, 8688,    11338, 11339, 11340, 26891);

-- 4. 麻醉毒药：无持续时间 → 1小时
UPDATE `spell_template` SET `EffectBasePoints1` = 3599 WHERE `id` IN (26785);

-- 5. 巫师油/法力油系列：30分钟 → 1小时
UPDATE `spell_template` SET `EffectBasePoints1` = 3599 WHERE `id` IN (    25117, 25118,    25119, 25120,    25121, 25122, 25123,    28013, 28017);

-- 6. 圣化武器：30分钟 → 1小时
UPDATE `spell_template` SET `EffectBasePoints1` = 3599 WHERE `id` IN (28891, 37360);

-- 7. 暗影之油、冰霜之油、速效毒素：0 → 30分钟
UPDATE `spell_template` SET `EffectBasePoints1` = 1799 WHERE `id` IN (3594, 3595, 6650);


-- =====================================================
-- 6.祖尔格拉布暗影箭雨
-- =====================================================

UPDATE `tbcmangos`.`spell_template` SET `RecoveryTime` = '10000' WHERE (`Id` = '20741');


-- =====================================================
-- 7.猫德回能
-- =====================================================
UPDATE `tbcmangos`.`spell_template` SET `EffectApplyAuraName3` = '0' WHERE (`Id` = '3025');






