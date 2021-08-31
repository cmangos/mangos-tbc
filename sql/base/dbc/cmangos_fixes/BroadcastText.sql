-- ============================================================
-- Classic section
-- ============================================================


-- ============================================================
-- TBC section
-- ============================================================

-- Hallow's End - Shade of the Horseman
-- these two texts were different before 3.0 changes were made to the event
-- the npc_text and broadcast_text data in tbc-db incorrectly had the 3.0 version
UPDATE `broadcast_text` SET `text1`='The Headless Horseman''s undead mind is obsessed!  During Hallow''s End, his attacks on this village are as rhythmic as his insane voice.  He will return in roughly $4676D.' WHERE `id`=22061; -- Alliance
UPDATE `broadcast_text` SET `text1`='The Headless Horseman''s mind is plagued with dementia!  During Hallow''s End, his attacks on this village are as rhythmic as his insane voice.$B$BHe will return in roughly $4676D.' WHERE `id`=22528; -- Horde
-- the first text of the jack-o-lantern was slightly different in TBC
UPDATE broadcast_text SET `text`="This large jack-o'-lantern rests in the middle of the village.  It eyes those who look up it, betraying a dark menace within." WHERE id=23650;

-- Sunwell Plateau Optional Progression Gating
-- NOTE: This is a custom modification to broadcast text
-- append onto ID 24247 since we have nothing else to go on (either this or make a custom ID)
-- source: https://warcraft.blizzplanet.com/blog/comments/wow_burning_crusade___patch_2_4___agamath_the_first_gate
UPDATE broadcast_text SET `text`="Should Kil'jaeden rise up through the Sunwell our world will be thrown into a war the likes of which has not been seen for 10,000 years!$B$BOur mages are $3253w percent through the defenses of the first gate, Agamath." WHERE id=24247;

-- ============================================================
-- WotLK section
-- ============================================================


