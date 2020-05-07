-- Shattered Hand Legionnair now gets handled via Core Script
UPDATE creature_template SET AIName="",  ScriptName = "mob_shattered_hand_legionnair" WHERE Entry="16700";
DELETE FROM creature_ai_scripts WHERE creature_id = "16700";