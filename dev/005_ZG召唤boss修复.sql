-- =====================================================
-- ZG summon boss fix (005) - idempotent (safe to re-run)
-- Bloodlord Mandokir bell (180526): remove the
-- unconditional GOOBER event (data2 = eventId 9066),
-- summon is script controlled only
-- =====================================================

-- 1) Bloodlord Mandokir bell (180526): clear unconditional event
UPDATE gameobject_template SET data2 = 0 WHERE entry = 180526;

-- 2) Scripted summon: delete-then-insert makes this re-runnable
DELETE FROM dbscripts_on_go_template_use WHERE id = 180526;
INSERT INTO dbscripts_on_go_template_use (id, delay, command, datalong, datalong2, comments)
VALUES (180526, 10000, 10, 14515, 900000, 'ZG - Bloodlord Mandokir bell summons Arlokk (script controlled)');
