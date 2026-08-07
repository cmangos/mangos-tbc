-- =====================================================
-- ZG 召唤 Boss 修复 (005)
-- 贝瑟克之锣：修复阿洛克可被无限召唤
-- =====================================================

-- ① 贝瑟克之锣（180526）：去掉 GOOBER 的无条件事件（data2 = eventId 9066）
UPDATE gameobject_template SET data2 = 0 WHERE entry = 180526;

-- 召唤移到模板使用脚本，只有 GOUse 脚本返回 false（首次/团灭重试）时执行
INSERT INTO dbscripts_on_go_template_use (id, delay, command, datalong, datalong2, comments)
VALUES (180526, 10000, 10, 14515, 900000, 'ZG - 贝瑟克之锣召唤阿洛克（受脚本状态控制）');
