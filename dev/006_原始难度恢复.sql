-- =====================================================
-- Boss original difficulty reverts - 2026-08-07
-- Database: tbcmangos (Nmangos TBC 2.4.3)
-- Changes: Magtheridon cube exhaustion 90s, Kael advisors/weapons HP +11.1%
-- Note: gating / Mark of Solarian / Persuasion / cube-failure exhaustion are source changes
-- =====================================================

-- 1) Magtheridon: cube Mind Exhaustion 90s (was 90s before 2.4.0, reduced to 30s in 2.4.0)
--    DurationIndex: 9 = 30s -> 23 = 90s (SpellDuration.dbc)
UPDATE spell_template SET DurationIndex = 23 WHERE Id = 44032;

-- 2) Kael'thas four advisors: HP +11.1% (nerfed 10% in 2.3.0; HealthMultiplier 36 -> 40)
--    20060 Lord Sanguinar / 20062 Grand Astromancer Capernian / 20063 Master Engineer Telonicus / 20064 Thaladred the Darkener
UPDATE creature_template SET HealthMultiplier = 40 WHERE entry IN (20060, 20062, 20063, 20064);

-- 3) Kael'thas summoned weapons: HP +11.1%
UPDATE creature_template SET HealthMultiplier = 30 WHERE entry = 21268; -- Netherstrand Longbow
UPDATE creature_template SET HealthMultiplier = 35 WHERE entry = 21269; -- Devastation
UPDATE creature_template SET HealthMultiplier = 40 WHERE entry = 21270; -- Cosmic Infuser
UPDATE creature_template SET HealthMultiplier = 30 WHERE entry = 21271; -- Infinity Blades
UPDATE creature_template SET HealthMultiplier = 40 WHERE entry = 21272; -- Warp Slicer
UPDATE creature_template SET HealthMultiplier = 45 WHERE entry = 21273; -- Phaseshift Bulwark
UPDATE creature_template SET HealthMultiplier = 25 WHERE entry = 21274; -- Staff of Disintegration
