-- Shattered Hand Legionnaire now gets handled via Core Script
UPDATE creature_template SET AIName="",  ScriptName = "mob_shattered_hand_legionnair" WHERE Entry="16700";
DELETE FROM creature_ai_scripts WHERE creature_id = "16700";


-- Shattered Hand Legionnaire Call for Reinforcements texts
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `broadcast_text_id`, `comment`) VALUES
('-1540056', 'Join the fight! Agrama-ka!', null, null, null, null, null, null, null, null, '10181', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540057', 'Next warrior, now!', null, null, null, null, null, null, null, null, '10174', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540058', 'Next warrior, step up!', null, null, null, null, null, null, null, null, '10180', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540059', 'Fighter down!', null, null, null, null, null, null, null, null, '10172', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540060', 'Where\'s my support?', null, null, null, null, null, null, null, null, '10176', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540061', 'Replacement, quickly!', null, null, null, null, null, null, null, null, '10173', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540062', 'Look Alive!', null, null, null, null, null, null, null, null, '10177', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540063', 'Engage the enemy!', null, null, null, null, null, null, null, null, '10178', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540064', 'Attack!', null, null, null, null, null, null, null, null, '10179', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540065', 'Fall in! Mok-thora ka!', null, null, null, null, null, null, null, null, '10175', '1', '0', '5', '0', 'Shattered Hand Legionnaire - Call for Reinforcements'),
('-1540066', '%s goes into a rage after seeing a friend fall in battle!', null, null, null, null, null, null, null, null, '0', '2', '0', '0', '0', 'Shattered Hand Legionnaire - Call for Reinforcements');


