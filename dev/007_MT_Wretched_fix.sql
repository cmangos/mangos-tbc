-- =====================================================================
-- 007 魔导师平台：失心者修复
-- =====================================================================


-- ① 清理原 007 的无效技能列表（幂等）
DELETE FROM `creature_spell_list` WHERE `Id` IN (2557500, 2557600, 2557700);
DELETE FROM `creature_spell_list_entry` WHERE `Id` IN (2557500, 2557600, 2557700);

UPDATE  creature_template  SET `AIName` = 'EventAI' where Entry in (24688, 24689, 24690);

-- ③ 44505 仅在生命 <= 20% 施放（原 009，EventAI 血量事件）
-- 普通难度：重复间隔 30~60s
UPDATE `creature_ai_scripts` SET
    `event_type`  = 2,          -- EVENT_T_HP
    `event_param1` = 20,        -- HPMax%
    `event_param2` = 0,         -- HPMin%
    `event_param3` = 30000,     -- RepeatMin
    `event_param4` = 60000,     -- RepeatMax
    `comment` = 'Wretched (Normal) - Cast Drink Fel Infusion below 20% HP'
WHERE `id` IN (2468802, 2468902, 2469003);

-- 英雄难度：重复间隔 15~30s
UPDATE `creature_ai_scripts` SET
    `event_type`  = 2,
    `event_param1` = 20,
    `event_param2` = 0,
    `event_param3` = 15000,
    `event_param4` = 30000,
    `comment` = 'Wretched (Heroic) - Cast Drink Fel Infusion below 20% HP'
WHERE `id` IN (2468803, 2468903, 2469004);
