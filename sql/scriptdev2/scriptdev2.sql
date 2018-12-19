/* INITIAL CLEANUP */
-- Clear all ScriptNames
-- This will clear all ScriptNames from any table in the World-Database

TRUNCATE scripted_areatrigger;
TRUNCATE scripted_event_id;
UPDATE creature_template SET ScriptName='';
UPDATE gameobject_template SET ScriptName='';
UPDATE item_template SET ScriptName='';
UPDATE instance_template SET ScriptName='';
UPDATE world_template SET ScriptName='';
/*  */

/* AREATRIGGER */
INSERT INTO scripted_areatrigger VALUES
(171, 'at_huldar_miran'),
(1726,'at_scent_larkorwi'),
(1727,'at_scent_larkorwi'),
(1728,'at_scent_larkorwi'),
(1729,'at_scent_larkorwi'),
(1730,'at_scent_larkorwi'),
(1731,'at_scent_larkorwi'),
(1732,'at_scent_larkorwi'),
(1733,'at_scent_larkorwi'),
(1734,'at_scent_larkorwi'),
(1735,'at_scent_larkorwi'),
(1736,'at_scent_larkorwi'),
(1737,'at_scent_larkorwi'),
(1738,'at_scent_larkorwi'),
(1739,'at_scent_larkorwi'),
(1740,'at_scent_larkorwi'),
(1966,'at_murkdeep'),
(2026,'at_blackrock_spire'),
(2046,'at_blackrock_spire'),
(2066,'at_blackrock_spire'),
(2067,'at_blackrock_spire'),
(3066,'at_ravenholdt'),
(3546,'at_childrens_week_spot'), -- Darnassian bank
(3547,'at_childrens_week_spot'), -- Undercity - thone room
(3548,'at_childrens_week_spot'), -- Stonewrought Dam
(3549,'at_childrens_week_spot'), -- The Mor'shan Rampart
(3550,'at_childrens_week_spot'), -- Ratchet Docks
(3552,'at_childrens_week_spot'), -- Westfall Lighthouse
(3587,'at_ancient_leaf'),
(3626,'at_vaelastrasz'),
(3958,'at_zulgurub'),
(3960,'at_zulgurub'),
(4047,'at_temple_ahnqiraj'),
(4052,'at_temple_ahnqiraj'),
(4112,'at_naxxramas'),
(4113,'at_naxxramas'),
(4156,'at_naxxramas'),
(4288,'at_dark_portal'),
(4422,'at_area_52'),
(4466,'at_area_52'),
(4471,'at_area_52'),
(4472,'at_area_52'),
(4479,'at_haramad_teleport'),
(4485,'at_dark_portal'),
(4524,'at_shattered_halls'),
(4560,'at_legion_teleporter'),
(4591,'at_coilfang_waterfall'),
(4937,'at_sunwell_plateau');

/* BATTLEGROUNDS */
UPDATE creature_template SET ScriptName='npc_spirit_guide' WHERE entry IN (13116, 13117);

/* WORLD BOSS */
UPDATE creature_template SET ScriptName='boss_ysondre' WHERE entry=14887;
UPDATE creature_template SET ScriptName='boss_emeriss' WHERE entry=14889;
UPDATE creature_template SET ScriptName='boss_taerar' WHERE entry=14890;
UPDATE creature_template SET ScriptName='boss_azuregos' WHERE entry=6109;
UPDATE creature_template SET ScriptName='boss_lethon' WHERE entry=14888;
UPDATE creature_template SET ScriptName='npc_spirit_shade' WHERE entry=15261;

/* GO */
UPDATE gameobject_template SET ScriptName='go_ethereum_prison' WHERE entry BETWEEN 184418 AND 184431;
UPDATE creature_template SET ScriptName='npc_ethereum_prisoner' WHERE entry IN(20520,20889);
UPDATE gameobject_template SET ScriptName='go_ethereum_stasis' WHERE entry BETWEEN 185465 AND 185467;
UPDATE gameobject_template SET ScriptName='go_ethereum_stasis' WHERE entry=184595;
UPDATE gameobject_template SET ScriptName='go_ethereum_stasis' WHERE entry BETWEEN 185461 AND 185464;
UPDATE gameobject_template SET ScriptName='go_stasis_chamber_alpha' WHERE entry IN(185512);
UPDATE gameobject_template SET ScriptName='go_jump_a_tron' WHERE entry=183146;
UPDATE gameobject_template SET ScriptName='go_andorhal_tower' WHERE entry IN (176094,176095,176096,176097);
UPDATE gameobject_template SET ScriptName='go_bells' WHERE entry IN(182064,175885,176573);
UPDATE gameobject_template SET ScriptName='go_darkmoon_faire_music' WHERE entry=180335;
UPDATE gameobject_template SET ScriptName='go_pirate_day_music' WHERE entry=190363;
UPDATE gameobject_template SET ScriptName='go_midsummer_music' WHERE entry=188174;
UPDATE gameobject_template SET ScriptName='go_brewfest_music' WHERE entry=186221;
UPDATE gameobject_template SET ScriptName='go_elemental_rift' WHERE entry IN (179664, 179665, 179666, 179667);

/* GUARD */
UPDATE creature_template SET ScriptName='guard_azuremyst' WHERE entry=18038;
UPDATE creature_template SET ScriptName='guard_orgrimmar' WHERE entry=3296;
UPDATE creature_template SET ScriptName='guard_stormwind' WHERE entry IN (68,1976);
UPDATE creature_template SET ScriptName='guard_contested' WHERE entry IN (9460,4624,3502,11190,15184);
UPDATE creature_template SET ScriptName='guard_elwynnforest' WHERE entry=1423;
UPDATE creature_template SET ScriptName='guard_eversong' WHERE entry=16221;
UPDATE creature_template SET ScriptName='guard_darnassus' WHERE entry=4262;
UPDATE creature_template SET ScriptName='guard_teldrassil' WHERE entry=3571;
UPDATE creature_template SET ScriptName='guard_ironforge' WHERE entry=5595;
UPDATE creature_template SET ScriptName='guard_dunmorogh' WHERE entry IN (727,13076);
UPDATE creature_template SET ScriptName='guard_undercity' WHERE entry=5624;
UPDATE creature_template SET ScriptName='guard_bluffwatcher' WHERE entry=3084;
UPDATE creature_template SET ScriptName='guard_durotar' WHERE entry=5953;
UPDATE creature_template SET ScriptName='guard_mulgore' WHERE entry IN (3212,3215,3217,3218,3219,3220,3221,3222,3223,3224);
UPDATE creature_template SET ScriptName='guard_dunmorogh' WHERE entry IN (727,13076);
UPDATE creature_template SET ScriptName='guard_tirisfal' WHERE entry IN (1735,1738,2210,1744,1745,5725,1743,2209,1746,1742);
UPDATE creature_template SET ScriptName='guard_silvermoon' WHERE entry=16222;
UPDATE creature_template SET ScriptName='guard_exodar' WHERE entry=16733;
UPDATE creature_template SET ScriptName='guard_shattrath' WHERE entry=19687;
UPDATE creature_template SET ScriptName='guard_shattrath_aldor' WHERE entry=18549;
UPDATE creature_template SET ScriptName='guard_shattrath_scryer' WHERE entry=18568;

/* ITEM */
UPDATE item_template SET ScriptName='item_arcane_charges' WHERE entry=34475;
UPDATE item_template SET ScriptName='item_flying_machine' WHERE entry IN (34060,34061);
UPDATE item_template SET ScriptName='item_gor_dreks_ointment' WHERE entry=30175;
UPDATE item_template SET ScriptName='item_petrov_cluster_bombs' WHERE entry=33098;
UPDATE item_template SET ScriptName='item_orb_of_draconic_energy' WHERE entry=12300;

/* NPC (usually creatures to be found in more than one specific zone) */
UPDATE creature_template SET ScriptName='npc_air_force_bots' WHERE entry IN (2614, 2615, 21974, 21993, 21996, 21997, 21999, 22001, 22002, 22003, 22063, 22065, 22066, 22068, 22069, 22070, 22071, 22078, 22079, 22080, 22086, 22087, 22088, 22090, 22124, 22125, 22126);
UPDATE creature_template SET ScriptName='npc_chicken_cluck' WHERE entry=620;
UPDATE creature_template SET ScriptName='npc_dancing_flames' WHERE entry=25305;
UPDATE creature_template SET ScriptName='npc_garments_of_quests' WHERE entry IN (12429,12423,12427,12430,12428);
UPDATE creature_template SET ScriptName='npc_guardian' WHERE entry=5764;
UPDATE creature_template SET ScriptName='npc_doctor' WHERE entry IN (12939,12920);
UPDATE creature_template SET ScriptName='npc_injured_patient' WHERE entry IN (12936,12937,12938,12923,12924,12925);
UPDATE creature_template SET ScriptName='npc_prof_blacksmith' WHERE entry IN (5164,11145,11146,11176,11177,11178,11191,11192,11193);
UPDATE creature_template SET ScriptName='npc_prof_leather' WHERE entry IN (7866,7867,7868,7869,7870,7871);
-- disabled, but can be used for custom
-- UPDATE creature_template SET ScriptName='' WHERE npcflag!=npcflag|65536 AND ScriptName='npc_innkeeper';
-- UPDATE creature_template SET ScriptName='npc_innkeeper' WHERE npcflag=npcflag|65536;
UPDATE creature_template SET ScriptName='npc_redemption_target' WHERE entry IN (6172,6177,17542,17768);
UPDATE creature_template SET ScriptName='npc_burster_worm' WHERE entry IN (16844,16857,16968,17075,18678,21380,21849,22038,22466,22482,23285);
UPDATE creature_template SET ScriptName='npc_aoe_damage_trigger' WHERE entry IN (16697,17471,18370);
UPDATE creature_template SET ScriptName='npc_the_cleaner' WHERE entry=14503;
UPDATE creature_template SET ScriptName='npc_shaman_earth_elemental' WHERE entry IN(15352); -- greater earth elemental
UPDATE creature_template SET ScriptName='npc_shaman_fire_elemental' WHERE entry IN(15438); -- greater fire elemental
UPDATE creature_template SET ScriptName='npc_snakes' WHERE entry IN(19921,19833);
UPDATE creature_template SET ScriptName='npc_nether_ray' WHERE entry IN(18880,21901,23501);

/*Quest (quest scripts which are not in one zone)*/
UPDATE creature_template SET ScriptName='npc_quest_attunement' WHERE entry IN(22421,18528,19935);

/* SPELL */
UPDATE creature_template SET ScriptName='spell_dummy_npc' WHERE entry IN (
-- eastern kingdoms
1200,8888,13016,
-- kalimdor
9299,12296,12298,
-- outland
16880,16518,16847,17157,17326,17654,18879,21729,24918,24922,25084,25085);

UPDATE gameobject_template SET ScriptName='spell_dummy_go' WHERE entry IN (181616);

/* WORLD MAP SCRIPTS */
DELETE FROM world_template WHERE map IN (0, 1, 530);
INSERT INTO world_template VALUES
(0, 'world_map_eastern_kingdoms'),
(1, 'world_map_kalimdor'),
(530, 'world_map_outland');

-- gromgol UC
INSERT INTO scripted_event_id VALUES
(15314,'event_transports'),
(15315,'event_transports'),
(15312,'event_transports'),
(15313,'event_transports');
-- OG UC
INSERT INTO scripted_event_id VALUES
(15318,'event_transports'),
(15319,'event_transports'),
(15320,'event_transports'),
(15321,'event_transports');
-- gromgol OG
INSERT INTO scripted_event_id VALUES
(15322,'event_transports'),
(15323,'event_transports'),
(15324,'event_transports'),
(15325,'event_transports');

/*  */
/* ZONE */
/* */

/* ALTERAC MOUNTAINS */

/* ALTERAC VALLEY */

/* ARATHI HIGHLANDS */
UPDATE creature_template SET ScriptName='npc_professor_phizzlethorpe' WHERE entry=2768;
UPDATE creature_template SET ScriptName='npc_kinelory' WHERE entry=2713;

/* ASHENVALE */
UPDATE creature_template SET ScriptName='npc_muglash' WHERE entry=12717;
UPDATE gameobject_template SET ScriptName='go_naga_brazier' WHERE entry=178247;
UPDATE creature_template SET ScriptName='npc_ruul_snowhoof' WHERE entry=12818;
UPDATE creature_template SET ScriptName='npc_torek' WHERE entry=12858;
UPDATE creature_template SET ScriptName='npc_feero_ironhand' WHERE entry=4484;

/*  */
/* AUCHINDOUN */
/*  */

/* MANA TOMBS */
UPDATE creature_template SET ScriptName='boss_pandemonius' WHERE entry=18341;
UPDATE creature_template SET ScriptName='boss_nexusprince_shaffar' WHERE entry=18344;
UPDATE creature_template SET ScriptName='npc_shaheen' WHERE entry=19671;
UPDATE creature_template SET ScriptName='npc_ethereum_prisoner_dungeon' WHERE entry IN(22927);
UPDATE gameobject_template SET ScriptName='go_stasis_chamber_mana_tombs' WHERE entry IN(185519);
UPDATE gameobject_template SET ScriptName='go_stasis_chamber_shaffar' WHERE entry IN(185522);

/* AUCHENAI CRYPTS */
UPDATE creature_template SET ScriptName='boss_exarch_maladaar' WHERE entry=18373;
UPDATE creature_template SET ScriptName='mob_stolen_soul' WHERE entry=18441;
UPDATE creature_template SET ScriptName='boss_shirrak' WHERE entry=18371;

/* SETHEKK HALLS */
UPDATE instance_template SET ScriptName='instance_sethekk_halls' WHERE map=556;
UPDATE creature_template SET ScriptName='boss_talon_king_ikiss' WHERE entry=18473;
UPDATE creature_template SET ScriptName='boss_darkweaver_syth' WHERE entry=18472;
UPDATE creature_template SET ScriptName='boss_anzu' WHERE entry=23035;
INSERT INTO scripted_event_id VALUES
(14797,'event_spell_summon_raven_god');
UPDATE creature_template SET ScriptName='npc_anzu_bird_spirit' WHERE entry IN(23134,23135,23136);

/* SHADOW LABYRINTH */
UPDATE instance_template SET ScriptName='instance_shadow_labyrinth' WHERE map=555;
UPDATE creature_template SET ScriptName='boss_murmur' WHERE entry=18708;
UPDATE creature_template SET ScriptName='boss_grandmaster_vorpil' WHERE entry=18732;
UPDATE creature_template SET ScriptName='boss_blackheart_the_inciter' WHERE entry=18667;
UPDATE creature_template SET ScriptName='boss_ambassador_hellmaw' WHERE entry=18731;
UPDATE creature_template SET ScriptName='npc_void_traveler' WHERE entry=19226;

/* AZSHARA */
UPDATE creature_template SET ScriptName='npc_rizzle_sprysprocket' WHERE entry=23002;
UPDATE creature_template SET ScriptName='npc_depth_charge' WHERE entry=23025;
UPDATE gameobject_template SET ScriptName='go_southfury_moonstone' WHERE entry=185566;
UPDATE creature_template SET ScriptName='mobs_spitelashes' WHERE entry IN (6190,6193,6194,6195,6196);
UPDATE creature_template SET ScriptName='npc_loramus_thalipedes' WHERE entry=7783;
UPDATE creature_template SET ScriptName='npc_felhound_tracker' WHERE entry=8668;

/* AZUREMYST ISLE */
UPDATE creature_template SET ScriptName='npc_draenei_survivor' WHERE entry=16483;
UPDATE creature_template SET ScriptName='npc_magwin' WHERE entry=17312;

/* BADLANDS */

/* BARRENS */
UPDATE creature_template SET ScriptName='npc_gilthares' WHERE entry=3465;
UPDATE creature_template SET ScriptName='npc_taskmaster_fizzule' WHERE entry=7233;
UPDATE creature_template SET ScriptName='npc_twiggy_flathead' WHERE entry=6248;
INSERT INTO scripted_areatrigger VALUES
(522,'at_twiggy_flathead');
UPDATE creature_template SET ScriptName='npc_wizzlecranks_shredder' WHERE entry=3439;
UPDATE creature_template SET ScriptName='npc_gallywix' WHERE entry=7288;

/* BLACK TEMPLE */
UPDATE instance_template SET ScriptName='instance_black_temple' WHERE map=564;
UPDATE creature_template SET ScriptName='npc_akama_shade' WHERE entry=23191; -- Akama at Shade of Akama
UPDATE creature_template SET ScriptName='npc_akama_illidan' WHERE entry=23089; -- Akama at Illidan
UPDATE creature_template SET ScriptName='mob_illidari_council' WHERE entry=23426; -- Illidari Council controller mob
UPDATE creature_template SET ScriptName='mob_blood_elf_council_voice_trigger' WHERE entry=23499; -- Voice Trigger Mob (Controls Aggro + Enrage yells)
UPDATE creature_template SET ScriptName='boss_veras_darkshadow' WHERE entry=22952; -- Rogue of Illidari Council
UPDATE creature_template SET ScriptName='boss_teron_gorefiend' WHERE entry=22871; -- Teron Gorefiend
UPDATE creature_template SET ScriptName='boss_supremus' WHERE entry=22898; -- Supremus
UPDATE creature_template SET ScriptName='boss_shade_of_akama' WHERE entry=22841; -- Shade of Akama
UPDATE creature_template SET ScriptName='boss_reliquary_of_souls' WHERE entry=22856; -- Reliquary Controller Mob
UPDATE creature_template SET ScriptName='boss_essence_of_suffering' WHERE entry=23418; -- Essence Of Suffering
UPDATE creature_template SET ScriptName='boss_essence_of_desire' WHERE entry=23419; -- Essence of Desire
UPDATE creature_template SET ScriptName='boss_essence_of_anger' WHERE entry=23420; -- Essence of Anger
UPDATE creature_template SET ScriptName='boss_najentus' WHERE entry=22887; -- High Warlord Naj'entus
UPDATE creature_template SET ScriptName='boss_gurtogg_bloodboil' WHERE entry=22948; -- Gurtogg Bloodboil
UPDATE creature_template SET ScriptName='boss_mother_shahraz' WHERE entry=22947; -- Mother Shahraz
UPDATE creature_template SET ScriptName='boss_lady_malande' WHERE entry=22951; -- Priest <3 at Illidari Council
UPDATE creature_template SET ScriptName='boss_illidan_stormrage' WHERE entry=22917; -- Illidan The Betrayer!
UPDATE creature_template SET ScriptName='boss_high_nethermancer_zerevor' WHERE entry=22950; -- Mage at Illidari Council
UPDATE creature_template SET ScriptName='boss_gathios_the_shatterer' WHERE entry=22949; -- Paladin at Illidari Council
UPDATE creature_template SET ScriptName='boss_maiev_shadowsong' WHERE entry=23197; -- Maiev Shadowsong
UPDATE creature_template SET ScriptName='mob_flame_of_azzinoth' WHERE entry=22997; -- Flame of Azzinoth (Illidan Phase 2)
UPDATE creature_template SET ScriptName='mob_blade_of_azzinoth' WHERE entry=22996; -- Blade of Azzinoth (Illidan Phase 2)
UPDATE creature_template SET ScriptName='mob_cage_trap_trigger' WHERE entry=23304; -- Cage Trap mob in Illidan Phase 3/4 Normal
UPDATE creature_template SET ScriptName='mob_shadow_demon' WHERE entry=23375; -- Shadow Demon in Illidan Demon Form
UPDATE creature_template SET ScriptName='npc_volcano' WHERE entry=23085; -- Supremus Volcano
UPDATE creature_template SET ScriptName='molten_flame' WHERE entry=23095; -- Molten Flame in SUpremus
UPDATE creature_template SET ScriptName='mob_ashtongue_channeler' WHERE entry=23421; -- Ashtongue CHanneler in Shade of AKama
UPDATE creature_template SET ScriptName='mob_ashtongue_sorcerer' WHERE entry=23215; -- Ashtongue Sorcerer in Shade of Akama
UPDATE creature_template SET ScriptName='npc_spirit_of_olum' WHERE entry=23411;
UPDATE creature_template SET ScriptName='npc_enslaved_soul' WHERE entry=23469;

/* BLACKFATHOM DEPTHS */
UPDATE instance_template SET ScriptName='instance_blackfathom_deeps' WHERE map=48;
UPDATE gameobject_template SET ScriptName='go_fire_of_akumai' WHERE entry IN (21118,21119,21120,21121);
UPDATE gameobject_template SET ScriptName='go_fathom_stone' WHERE entry=177964;

/* BLACKROCK DEPTHS */
INSERT INTO scripted_areatrigger VALUES
(1526,'at_ring_of_law'),
(1786,'at_shadowforge_bridge');
UPDATE instance_template SET ScriptName='instance_blackrock_depths' WHERE map =230;
UPDATE creature_template SET ScriptName='boss_emperor_dagran_thaurissan' WHERE entry=9019;
UPDATE creature_template SET ScriptName='boss_moira_bronzebeard' WHERE entry=8929;
UPDATE creature_template SET ScriptName='boss_ambassador_flamelash' WHERE entry=9156;
UPDATE creature_template SET ScriptName='boss_doomrel' WHERE entry=9039;
UPDATE creature_template SET ScriptName='boss_general_angerforge' WHERE entry=9033;
UPDATE creature_template SET ScriptName='boss_high_interrogator_gerstahn' WHERE entry=9018;
UPDATE creature_template SET ScriptName='boss_coren_direbrew' WHERE entry=23872;
UPDATE creature_template SET ScriptName='npc_grimstone' WHERE entry=10096;
UPDATE creature_template SET ScriptName='npc_theldren_trigger' WHERE entry=16079;
UPDATE creature_template SET ScriptName='npc_phalanx' WHERE entry=9502;
UPDATE creature_template SET ScriptName='npc_mistress_nagmara' WHERE entry=9500;
UPDATE creature_template SET ScriptName='npc_rocknot' WHERE entry=9503;
UPDATE creature_template SET ScriptName='npc_marshal_windsor' WHERE entry=9023;
UPDATE creature_template SET ScriptName='npc_dughal_stormwing' WHERE entry=9022;
UPDATE creature_template SET ScriptName='npc_tobias_seecher' WHERE entry=9679;
UPDATE creature_template SET ScriptName='npc_hurley_blackbreath' WHERE entry=9537;
UPDATE creature_template SET ScriptName='boss_plugger_spazzring' WHERE entry=9499;
UPDATE creature_template SET ScriptName='npc_ironhand_guardian' WHERE entry=8982;
UPDATE gameobject_template SET ScriptName='go_shadowforge_brazier' WHERE entry IN (174744, 174745);
UPDATE gameobject_template SET ScriptName='go_relic_coffer_door' WHERE entry IN (174554, 174555, 174556, 174557, 174558, 174559, 174560, 174561, 174562, 174563, 174564, 174566);
UPDATE gameobject_template SET ScriptName='go_bar_beer_keg' WHERE entry=164911;
UPDATE gameobject_template SET ScriptName='go_bar_ale_mug' WHERE entry IN (165738,165739);

/* BLACKROCK SPIRE */
UPDATE instance_template SET ScriptName='instance_blackrock_spire' WHERE map=229;
UPDATE creature_template SET ScriptName='boss_overlord_wyrmthalak' WHERE entry=9568;
UPDATE creature_template SET ScriptName='boss_gyth' WHERE entry=10339;
UPDATE creature_template SET ScriptName='boss_pyroguard_emberseer' WHERE entry=9816;
UPDATE creature_template SET ScriptName='npc_rookery_hatcher' WHERE entry=10683;
INSERT INTO scripted_event_id VALUES
(4884,'event_spell_altar_emberseer');
UPDATE gameobject_template SET ScriptName='go_father_flame' WHERE entry=175245;

/* BLACKWING LAIR */
UPDATE instance_template SET ScriptName='instance_blackwing_lair' WHERE map=469;
UPDATE creature_template SET ScriptName='boss_razorgore' WHERE entry=12435;
UPDATE creature_template SET ScriptName='npc_blackwing_orb' WHERE entry=14449;
UPDATE gameobject_template SET ScriptName='go_black_dragon_egg' WHERE entry=177807;
UPDATE creature_template SET ScriptName='boss_vaelastrasz' WHERE entry=13020;
UPDATE gameobject_template SET ScriptName='go_suppression' WHERE entry=179784;
UPDATE creature_template SET ScriptName='boss_broodlord' WHERE entry=12017;
UPDATE creature_template SET ScriptName='boss_firemaw' WHERE entry=11983;
UPDATE creature_template SET ScriptName='boss_ebonroc' WHERE entry=14601;
UPDATE creature_template SET ScriptName='boss_flamegor' WHERE entry=11981;
UPDATE creature_template SET ScriptName='boss_chromaggus' WHERE entry=14020;
UPDATE creature_template SET ScriptName='boss_victor_nefarius' WHERE entry=10162;
UPDATE creature_template SET ScriptName='boss_nefarian' WHERE entry=11583;
INSERT INTO scripted_event_id VALUES
(8446, 'event_weekly_chromatic_selection'),
(8447, 'event_weekly_chromatic_selection'),
(8448, 'event_weekly_chromatic_selection'),
(8449, 'event_weekly_chromatic_selection'),
(8450, 'event_weekly_chromatic_selection'),
(8451, 'event_weekly_chromatic_selection'),
(8452, 'event_weekly_chromatic_selection'),
(8453, 'event_weekly_chromatic_selection'),
(8454, 'event_weekly_chromatic_selection'),
(8455, 'event_weekly_chromatic_selection'),
(8520, 'event_weekly_chromatic_selection'),
(8521, 'event_weekly_chromatic_selection'),
(8522, 'event_weekly_chromatic_selection'),
(8523, 'event_weekly_chromatic_selection'),
(8524, 'event_weekly_chromatic_selection'),
(8525, 'event_weekly_chromatic_selection'),
(8526, 'event_weekly_chromatic_selection'),
(8527, 'event_weekly_chromatic_selection'),
(8528, 'event_weekly_chromatic_selection'),
(8529, 'event_weekly_chromatic_selection');


/* BLADE'S EDGE MOUNTAINS */
UPDATE creature_template SET ScriptName='mobs_nether_drake' WHERE entry IN (20021,21817,21820,21821,21823);
UPDATE creature_template SET ScriptName='npc_daranelle' WHERE entry=21469;
UPDATE creature_template SET ScriptName='npc_bloodmaul_stout_trigger' WHERE entry=21241;
UPDATE creature_template SET ScriptName='npc_simon_game_bunny' WHERE entry=22923;
UPDATE creature_template SET ScriptName='npc_light_orb_collector' WHERE entry IN (21926,22333);
UPDATE creature_template SET ScriptName='npc_bloodmaul_dire_wolf' WHERE entry=20058;
UPDATE creature_template SET ScriptName='npc_obelisk_trigger' WHERE entry=22422;
UPDATE creature_template SET ScriptName='npc_vimgol_visual_bunny' WHERE entry=23040;
UPDATE creature_template SET ScriptName='npc_vimgol_middle_bunny' WHERE entry=23081;
UPDATE creature_template SET ScriptName='npc_vimgol' WHERE entry=22911;
UPDATE creature_template SET ScriptName='npc_bird_spirit' WHERE entry=22023;
UPDATE creature_template SET ScriptName='npc_spirit_prisoner_of_bladespire' WHERE entry IN(22460);
UPDATE creature_template SET ScriptName='npc_deadsoul_orb' WHERE entry=20845;
UPDATE creature_template SET ScriptName='npc_evergrove_druid' WHERE entry=22423;
UPDATE creature_template SET ScriptName='npc_apexis_flayer' WHERE entry=22175;
INSERT INTO scripted_areatrigger VALUES
(4613, "mobs_grishna_arrakoa"),
(4615, "mobs_grishna_arrakoa"),
(4616, "mobs_grishna_arrakoa"),
(4617, "mobs_grishna_arrakoa");
UPDATE creature_template SET ScriptName='npc_soulgrinder' WHERE entry=23019;
UPDATE creature_template SET ScriptName='npc_mogdorg_the_wizened' WHERE entry=22941;
UPDATE creature_template SET ScriptName='npc_supplicant' WHERE entry IN(23052,23053);
INSERT INTO scripted_event_id VALUES(14739,'event_into_the_soulgrinder');
UPDATE creature_template SET ScriptName='npc_warp_gate' WHERE entry IN(22471,22472);
UPDATE creature_template SET ScriptName='npc_fel_cannon' WHERE entry=22443;

/* BLASTED LANDS */
UPDATE creature_template SET ScriptName='npc_fallen_hero_of_horde' WHERE entry=7572;

/* BLOODMYST ISLE */
UPDATE creature_template SET ScriptName='mob_webbed_creature' WHERE entry=17680;
UPDATE creature_template SET ScriptName='npc_demolitionist_legoso' WHERE entry=17982;

/* BURNING STEPPES */
UPDATE creature_template SET ScriptName='npc_ragged_john' WHERE entry=9563;
UPDATE creature_template SET ScriptName='npc_grark_lorkrub' WHERE entry=9520;
UPDATE creature_template SET ScriptName='npc_klinfran' WHERE entry IN (14529,14534);

/*  */
/* CAVERNS OF TIME */
/*  */

/* MT. HYJAL */
UPDATE instance_template SET ScriptName='instance_hyjal' WHERE map=534;
UPDATE creature_template SET ScriptName='npc_tyrande_whisperwind' WHERE entry=17948;
UPDATE creature_template SET ScriptName='npc_thrall' WHERE entry=17852;
UPDATE creature_template SET ScriptName='npc_jaina_proudmoore' WHERE entry=17772;
UPDATE creature_template SET ScriptName='boss_archimonde' WHERE entry=17968;
UPDATE creature_template SET ScriptName='npc_doomfire_spirit' WHERE entry=18104;

/* OLD HILLSBRAD */
UPDATE instance_template SET ScriptName='instance_old_hillsbrad' WHERE map=560;
UPDATE creature_template SET ScriptName='npc_erozion' WHERE entry=18723;
UPDATE creature_template SET ScriptName='npc_taretha' WHERE entry=18887;
UPDATE creature_template SET ScriptName='npc_thrall_old_hillsbrad' WHERE entry=17876;
INSERT INTO scripted_event_id VALUES
(11111,'event_go_barrel_old_hillsbrad');

/* THE DARK PORTAL */
UPDATE creature_template SET ScriptName='boss_chrono_lord_deja' WHERE entry=17879;
UPDATE creature_template SET ScriptName='boss_aeonus' WHERE entry=17881;
UPDATE creature_template SET ScriptName='boss_temporus' WHERE entry=17880;
UPDATE instance_template SET ScriptName='instance_dark_portal' WHERE map=269;
UPDATE creature_template SET ScriptName='npc_medivh_black_morass' WHERE entry=15608;
UPDATE creature_template SET ScriptName='npc_time_rift' WHERE entry=17838;

/*  */
/* COILFANG RESERVOIR */
/*  */

/* THE SLAVE PENS */
UPDATE creature_template SET ScriptName='boss_ahune' WHERE entry=25740;
UPDATE creature_template SET ScriptName='npc_frozen_core' WHERE entry=25865;
UPDATE creature_template SET ScriptName='npc_ice_spear_bunny' WHERE entry=25985;
UPDATE instance_template SET ScriptName='instance_slave_pens' WHERE map=547;
INSERT INTO scripted_areatrigger VALUES
(4295,'at_naturalist_bite');
UPDATE creature_template SET ScriptName='npc_naturalist_bite' WHERE entry IN(17893); -- gossip only

/* THE UNDERBOG */
UPDATE creature_template SET ScriptName='mob_underbog_mushroom' WHERE entry=17990;
UPDATE creature_template SET ScriptName='boss_hungarfen' WHERE entry=17770;
UPDATE instance_template SET ScriptName='instance_underbog' WHERE map=546;
INSERT INTO scripted_areatrigger VALUES
(4302,'at_ghazan_surface');

/* THE STEAMVAULT */
UPDATE instance_template SET ScriptName='instance_steam_vault' WHERE map=545;
UPDATE creature_template SET ScriptName='boss_hydromancer_thespia' WHERE entry=17797;
UPDATE creature_template SET ScriptName='boss_mekgineer_steamrigger' WHERE entry=17796;
UPDATE creature_template SET ScriptName='boss_warlord_kalithresh' WHERE entry=17798;
UPDATE gameobject_template SET ScriptName='go_main_chambers_access_panel' WHERE entry IN (184125,184126);
UPDATE creature_template SET ScriptName='mob_naga_distiller' WHERE entry=17954;
UPDATE creature_template SET ScriptName='mob_steamrigger_mechanic' WHERE entry=17951;

/* SERPENTSHRINE CAVERN */
UPDATE instance_template SET ScriptName='instance_serpent_shrine' WHERE map=548;
UPDATE gameobject_template SET ScriptName='go_ssc_boss_consoles' WHERE entry IN(185117,185118,185115,185114,185116);
UPDATE creature_template SET ScriptName='npc_serpentshrine_parasite' WHERE entry=22379;
/* Hydross the Unstable event */
UPDATE creature_template SET ScriptName='boss_hydross_the_unstable' WHERE entry=21216;
UPDATE creature_template SET ScriptName='npc_spawn_of_hydross' WHERE entry IN(22035,22036);
/* Leotheras the Blind event */
UPDATE creature_template SET ScriptName='boss_leotheras_the_blind' WHERE entry=21215;
UPDATE creature_template SET ScriptName='npc_inner_demon' WHERE entry=21857;
/* Fathom-lord Karathress event */
UPDATE creature_template SET ScriptName='boss_fathomlord_karathress' WHERE entry=21214;
UPDATE creature_template SET ScriptName='boss_fathomguard_sharkkis' WHERE entry=21966;
UPDATE creature_template SET ScriptName='boss_fathomguard_tidalvess' WHERE entry=21965;
UPDATE creature_template SET ScriptName='boss_fathomguard_caribdis' WHERE entry=21964;
/* Morogrim Tidewalker event */
UPDATE creature_template SET ScriptName='boss_morogrim_tidewalker' WHERE entry=21213;
UPDATE creature_template SET ScriptName='mob_water_globule' WHERE entry=21913;
/* Lady Vashj event */
UPDATE creature_template SET ScriptName='boss_lady_vashj' WHERE entry=21212;
UPDATE creature_template SET ScriptName='mob_enchanted_elemental' WHERE entry=21958;
UPDATE gameobject_template SET ScriptName='go_shield_generator' WHERE entry IN (185051,185052,185053,185054);
UPDATE item_template SET ScriptName='item_tainted_core' WHERE entry=31088;
UPDATE gameobject_template SET ScriptName='go_vashj_bridge' WHERE entry IN(184568);
/* The Lurker Below event */
UPDATE gameobject_template SET ScriptName='go_strange_pool' WHERE entry=184956;
UPDATE creature_template SET ScriptName='boss_the_lurker_below' WHERE entry=21217;

/* DARKSHORE */
UPDATE creature_template SET ScriptName='npc_kerlonian' WHERE entry=11218;
UPDATE creature_template SET ScriptName='npc_prospector_remtravel' WHERE entry=2917;
UPDATE creature_template SET ScriptName='npc_threshwackonator' WHERE entry=6669;
UPDATE creature_template SET ScriptName='npc_volcor' WHERE entry=3692;
UPDATE creature_template SET ScriptName='npc_therylune' WHERE entry=3584;
UPDATE creature_template SET ScriptName='npc_rabid_bear' WHERE entry=2164;

/* DARNASSUS */

/* DEADMINES */
UPDATE creature_template SET ScriptName='boss_mr_smite' WHERE entry=646;
UPDATE instance_template SET ScriptName='instance_deadmines' WHERE map=36;
UPDATE gameobject_template SET ScriptName='go_defias_cannon' WHERE entry=16398;

/* DEADWIND PASS */

/* DESOLACE */
UPDATE creature_template SET ScriptName='npc_aged_dying_ancient_kodo' WHERE entry IN (4700, 4701, 4702, 11627);
UPDATE creature_template SET ScriptName='npc_dalinda_malem' WHERE entry=5644;
UPDATE creature_template SET ScriptName='npc_melizza_brimbuzzle' WHERE entry=12277;
UPDATE creature_template SET ScriptName='npc_cork_gizelton' WHERE entry=11625;
UPDATE creature_template SET ScriptName='npc_rigger_gizelton' WHERE entry=11626;
UPDATE creature_template SET ScriptName='npc_magrami_spectre' WHERE entry=11560;

/* DIRE MAUL */
UPDATE instance_template SET ScriptName='instance_dire_maul' WHERE map=429;
UPDATE gameobject_template SET ScriptName='go_fixed_trap' WHERE entry=179512;
UPDATE creature_template SET ScriptName='npc_mizzle_crafty' WHERE entry=14353;
INSERT INTO scripted_event_id VALUES
(8420,'event_spells_warlock_dreadsteed'),
(8428,'event_spells_warlock_dreadsteed');

/* DUN MOROGH */

/* DUROTAR */
UPDATE creature_template SET ScriptName='npc_lazy_peon' WHERE entry=10556;

/* DUSKWOOD */

/* DUSTWALLOW MARSH */
UPDATE creature_template SET ScriptName='mobs_risen_husk_spirit' WHERE entry IN (23554,23555);
UPDATE creature_template SET ScriptName='npc_ogron' WHERE entry=4983;
UPDATE creature_template SET ScriptName='npc_morokk' WHERE entry=4500;
UPDATE creature_template SET ScriptName='npc_restless_apparition' WHERE entry=23861;
UPDATE creature_template SET ScriptName='npc_private_hendel' WHERE entry=4966;
UPDATE creature_template SET ScriptName='npc_stinky_ignatz' WHERE entry=4880;
UPDATE creature_template SET ScriptName='boss_tethyr' WHERE entry=23899;
INSERT INTO scripted_areatrigger VALUES
(302,'at_sentry_point');
INSERT INTO scripted_areatrigger VALUES
(4752,'at_nats_landing');

/* EASTERN PLAGUELANDS */
UPDATE creature_template SET ScriptName='npc_eris_havenfire' WHERE entry=14494;

/* ELWYNN FOREST */

/* EVERSONG WOODS */
UPDATE creature_template SET ScriptName='npc_kelerun_bloodmourn' WHERE entry=17807;
UPDATE gameobject_template SET ScriptName='go_harbinger_second_trial' WHERE entry=182052;
UPDATE creature_template SET ScriptName='npc_prospector_anvilward' WHERE entry=15420;
UPDATE creature_template SET ScriptName='npc_apprentice_mirveda' WHERE entry=15402;
UPDATE creature_template SET ScriptName='npc_infused_crystal' WHERE entry=16364;

/* FELWOOD */
INSERT INTO scripted_event_id VALUES
(8328, 'npc_kroshius');
UPDATE creature_template SET ScriptName='npc_kitten' WHERE entry=9937;
UPDATE creature_template SET ScriptName='npc_corrupt_saber' WHERE entry=10042;
UPDATE creature_template SET ScriptName='npc_niby_the_almighty' WHERE entry=14469;
UPDATE creature_template SET ScriptName='npc_kroshius' WHERE entry=14467;
UPDATE creature_template SET ScriptName='npc_captured_arkonarin' WHERE entry=11016;
UPDATE creature_template SET ScriptName='npc_arei' WHERE entry=9598;

/* FERALAS */
UPDATE creature_template SET ScriptName='npc_oox22fe' WHERE entry=7807;
UPDATE creature_template SET ScriptName='npc_shay_leafrunner' WHERE entry=7774;

/* GHOSTLANDS */
UPDATE creature_template SET ScriptName='npc_ranger_lilatha' WHERE entry=16295;

/* GNOMEREGAN */
UPDATE creature_template SET ScriptName='boss_thermaplugg' WHERE entry=7800;
UPDATE gameobject_template SET ScriptName='go_gnomeface_button' WHERE entry BETWEEN 142214 AND 142219;
UPDATE creature_template SET ScriptName='npc_blastmaster_emi_shortfuse' WHERE entry=7998;
UPDATE creature_template SET ScriptName='npc_kernobee' WHERE entry=7850;
UPDATE instance_template SET ScriptName='instance_gnomeregan' WHERE map=90;

/* GRUUL'S LAIR */
UPDATE instance_template SET ScriptName='instance_gruuls_lair' WHERE map =565;
UPDATE creature_template SET ScriptName='boss_gruul' WHERE entry=19044;
/* Maulgar and Event */
UPDATE creature_template SET ScriptName='boss_high_king_maulgar' WHERE entry=18831;
UPDATE creature_template SET ScriptName='boss_kiggler_the_crazed' WHERE entry=18835;
UPDATE creature_template SET ScriptName='boss_blindeye_the_seer' WHERE entry=18836;
UPDATE creature_template SET ScriptName='boss_olm_the_summoner' WHERE entry=18834;
UPDATE creature_template SET ScriptName='boss_krosh_firehand' WHERE entry=18832;

/*  */
/* HELLFIRE CITADEL */
/*  */

/* BLOOD FURNACE */
/* The Maker,Broggok,Kelidan,Broggok's cloud */
UPDATE creature_template SET ScriptName='boss_the_maker' WHERE entry=17381;
UPDATE creature_template SET ScriptName='boss_broggok' WHERE entry=17380;
UPDATE creature_template SET ScriptName='boss_kelidan_the_breaker' WHERE entry=17377;
UPDATE creature_template SET ScriptName='mob_broggok_poisoncloud' WHERE entry=17662;
UPDATE creature_template SET ScriptName='mob_shadowmoon_channeler' WHERE entry=17653;
UPDATE gameobject_template SET ScriptName='go_prison_cell_lever' WHERE entry=181982;
UPDATE instance_template SET ScriptName='instance_blood_furnace' WHERE map=542;

/* HELLFIRE RAMPARTS */
/* Vazruden,Omor the Unscarred,Watchkeeper Gargolmar */
UPDATE creature_template SET ScriptName='boss_omor_the_unscarred' WHERE entry=17308;
UPDATE creature_template SET ScriptName='boss_watchkeeper_gargolmar' WHERE entry=17306;
UPDATE creature_template SET ScriptName='boss_vazruden_herald' WHERE entry=17307;
UPDATE creature_template SET ScriptName='boss_vazruden' WHERE entry=17537;
UPDATE instance_template SET ScriptName='instance_ramparts' WHERE map=543;

/* SHATTERED HALLS */
/* Nethekurse and his spawned shadowfissure */
UPDATE creature_template SET ScriptName='boss_grand_warlock_nethekurse' WHERE entry=16807;
UPDATE creature_template SET ScriptName='boss_warbringer_omrogg' WHERE entry=16809;
UPDATE creature_template SET ScriptName='mob_fel_orc_convert' WHERE entry=17083;
UPDATE creature_template SET ScriptName='mob_omrogg_heads' WHERE entry IN (19523,19524);
UPDATE creature_template SET ScriptName='boss_warchief_kargath_bladefist' WHERE entry=16808;
UPDATE creature_template SET ScriptName='npc_blade_dance_target' WHERE entry IN(20709);
UPDATE instance_template SET ScriptName='instance_shattered_halls' WHERE map=540;

/* MAGTHERIDON'S LAIR */
UPDATE instance_template SET ScriptName='instance_magtheridons_lair' WHERE map=544;
UPDATE gameobject_template SET ScriptName='go_manticron_cube' WHERE entry=181713;
UPDATE creature_template SET ScriptName='boss_magtheridon' WHERE entry=17257;
UPDATE creature_template SET ScriptName='mob_abyssal' WHERE entry=17454;
UPDATE creature_template SET ScriptName='mob_hellfire_channeler' WHERE entry=17256;
UPDATE creature_template SET ScriptName='npc_target_trigger' WHERE entry=17474;

/* HELLFIRE PENINSULA */
UPDATE creature_template SET ScriptName='boss_doomlord_kazzak' WHERE entry=18728;
UPDATE creature_template SET ScriptName='npc_aeranas' WHERE entry=17085;
UPDATE creature_template SET ScriptName='npc_ancestral_wolf' WHERE entry=17077;
UPDATE creature_template SET ScriptName='npc_demoniac_scryer' WHERE entry=22258;
UPDATE creature_template SET ScriptName='npc_wounded_blood_elf' WHERE entry=16993;
UPDATE creature_template SET ScriptName='npc_fel_guard_hound' WHERE entry=21847;
UPDATE creature_template SET ScriptName='npc_anchorite_barada' WHERE entry=22431;
UPDATE creature_template SET ScriptName='npc_colonel_jules' WHERE entry=22432;
UPDATE creature_template SET ScriptName='npc_magister_aledis' WHERE entry=20159;
UPDATE creature_template SET ScriptName='npc_living_flare' WHERE entry=24916;
UPDATE creature_template SET ScriptName='npc_danath_trollbane' WHERE `Entry`='16819';
UPDATE creature_template SET ScriptName='npc_nazgrel' WHERE `Entry`='3230';

/* HILLSBRAD FOOTHILLS */

/* HINTERLANDS */
UPDATE creature_template SET ScriptName='npc_00x09hl' WHERE entry=7806;
UPDATE creature_template SET ScriptName='npc_rinji' WHERE entry=7780;

/* IRONFORGE */

/* ISLE OF QUEL'DANAS */
UPDATE creature_template SET ScriptName='npc_converted_sentry' WHERE entry=24981;

/* KARAZHAN */
UPDATE instance_template SET ScriptName='instance_karazhan' WHERE map=532;
UPDATE creature_template SET ScriptName='boss_midnight' WHERE entry=16151;
UPDATE creature_template SET ScriptName='boss_attumen' WHERE entry IN (15550,16152);
UPDATE creature_template SET ScriptName='boss_moroes' WHERE entry=15687;
UPDATE creature_template SET ScriptName='boss_maiden_of_virtue' WHERE entry=16457;
UPDATE creature_template SET ScriptName='boss_curator' WHERE entry=15691;
UPDATE creature_template SET ScriptName='boss_julianne' WHERE entry=17534;
UPDATE creature_template SET ScriptName='boss_romulo' WHERE entry=17533;
UPDATE creature_template SET ScriptName='boss_dorothee' WHERE entry=17535;
UPDATE creature_template SET ScriptName='boss_strawman' WHERE entry=17543;
UPDATE creature_template SET ScriptName='boss_tinhead' WHERE entry=17547;
UPDATE creature_template SET ScriptName='boss_roar' WHERE entry=17546;
UPDATE creature_template SET ScriptName='boss_crone' WHERE entry=18168;
UPDATE creature_template SET ScriptName='boss_terestian_illhoof' WHERE entry=15688;
UPDATE creature_template SET ScriptName='boss_shade_of_aran' WHERE entry=16524;
UPDATE creature_template SET ScriptName='boss_netherspite' WHERE entry=15689;
UPDATE creature_template SET ScriptName='boss_malchezaar' WHERE entry=15690;
UPDATE creature_template SET ScriptName='boss_nightbane' WHERE entry=17225;
UPDATE creature_template SET ScriptName='boss_bigbadwolf' WHERE entry=17521;
UPDATE creature_template SET ScriptName='mob_demon_chain' WHERE entry=17248;
UPDATE creature_template SET ScriptName='npc_fiendish_portal' WHERE entry=17265;
UPDATE creature_template SET ScriptName='npc_shade_of_aran_blizzard' WHERE entry=17161;
UPDATE creature_template SET ScriptName='npc_netherspite_portal' WHERE entry IN (17367,17368,17369);
UPDATE creature_template SET ScriptName='npc_infernal_target' WHERE entry=17644;
UPDATE creature_template SET ScriptName='npc_barnes' WHERE entry=16812;
UPDATE creature_template SET ScriptName='npc_grandmother' WHERE entry=17603;
UPDATE creature_template SET ScriptName='npc_image_of_medivh' WHERE entry=17651;
UPDATE creature_template SET ScriptName='npc_image_arcanagos' WHERE entry=17652;
UPDATE creature_template SET ScriptName='npc_echo_of_medivh' WHERE entry=16816;
UPDATE creature_template SET ScriptName='npc_king_llane' WHERE entry=21684;
UPDATE creature_template SET ScriptName='npc_warchief_blackhand' WHERE entry=21752;
UPDATE creature_template SET ScriptName='npc_human_conjurer' WHERE entry=21683;
UPDATE creature_template SET ScriptName='npc_orc_warlock' WHERE entry=21750;
UPDATE creature_template SET ScriptName='npc_human_footman' WHERE entry=17211;
UPDATE creature_template SET ScriptName='npc_orc_grunt' WHERE entry=17469;
UPDATE creature_template SET ScriptName='npc_water_elemental' WHERE entry=21160;
UPDATE creature_template SET ScriptName='npc_summoned_daemon' WHERE entry=21726;
UPDATE creature_template SET ScriptName='npc_human_charger' WHERE entry=21664;
UPDATE creature_template SET ScriptName='npc_orc_wolf' WHERE entry=21748;
UPDATE creature_template SET ScriptName='npc_human_cleric' WHERE entry=21682;
UPDATE creature_template SET ScriptName='npc_orc_necrolyte' WHERE entry=21747;
INSERT INTO scripted_event_id VALUES
(10591,'event_spell_summon_nightbane'),
(10951,'event_spell_medivh_journal');
UPDATE creature_template SET ScriptName='npc_infernal_relay' WHERE entry=17645;

/* LOCH MODAN */
UPDATE creature_template SET ScriptName='npc_mountaineer_pebblebitty' WHERE entry=3836;
UPDATE creature_template SET ScriptName='npc_miran' WHERE entry=1379;

/* MAGISTER'S TERRACE */
UPDATE instance_template SET ScriptName='instance_magisters_terrace' WHERE map=585;
UPDATE creature_template SET ScriptName='boss_selin_fireheart' WHERE entry=24723;
UPDATE creature_template SET ScriptName='mob_fel_crystal' WHERE entry=24722;
UPDATE creature_template SET ScriptName='boss_vexallus' WHERE entry=24744;
UPDATE creature_template SET ScriptName='mob_pure_energy' WHERE entry=24745;
UPDATE creature_template SET ScriptName='boss_priestess_delrissa' WHERE entry=24560;
UPDATE creature_template SET ScriptName='npc_kagani_nightstrike' WHERE entry=24557;
UPDATE creature_template SET ScriptName='npc_ellris_duskhallow' WHERE entry=24558;
UPDATE creature_template SET ScriptName='npc_eramas_brightblaze' WHERE entry=24554;
UPDATE creature_template SET ScriptName='npc_yazzai' WHERE entry=24561;
UPDATE creature_template SET ScriptName='npc_warlord_salaris' WHERE entry=24559;
UPDATE creature_template SET ScriptName='npc_garaxxas' WHERE entry=24555;
UPDATE creature_template SET ScriptName='npc_apoko' WHERE entry=24553;
UPDATE creature_template SET ScriptName='npc_zelfan' WHERE entry=24556;
UPDATE creature_template SET ScriptName='boss_felblood_kaelthas' WHERE entry=24664;
UPDATE creature_template SET ScriptName='mob_arcane_sphere' WHERE entry=24708;
UPDATE creature_template SET ScriptName='mob_felkael_phoenix' WHERE entry=24674;
UPDATE creature_template SET ScriptName='mob_felkael_phoenix_egg' WHERE entry=24675;
UPDATE creature_template SET ScriptName='npc_kalecgos' WHERE entry=24844;
INSERT INTO scripted_event_id VALUES
(16547,'event_go_scrying_orb');

/* MARAUDON */
UPDATE instance_template SET ScriptName="instance_maraudon" WHERE map=349;
UPDATE creature_template SET ScriptName='boss_noxxion' WHERE entry=13282;
UPDATE gameobject_template SET ScriptName="go_larva_spewer" WHERE entry=178559;

/* MOLTEN CORE */
UPDATE instance_template SET ScriptName='instance_molten_core' WHERE map=409;
UPDATE creature_template SET ScriptName='boss_lucifron' WHERE entry=12118;
UPDATE creature_template SET ScriptName='boss_magmadar' WHERE entry=11982;
UPDATE creature_template SET ScriptName='boss_gehennas' WHERE entry=12259;
UPDATE creature_template SET ScriptName='boss_garr' WHERE entry=12057;
UPDATE creature_template SET ScriptName='boss_baron_geddon' WHERE entry=12056;
UPDATE creature_template SET ScriptName='boss_shazzrah' WHERE entry=12264;
UPDATE creature_template SET ScriptName='boss_golemagg' WHERE entry=11988;
UPDATE creature_template SET ScriptName='boss_sulfuron' WHERE entry=12098;
UPDATE creature_template SET ScriptName='boss_majordomo' WHERE entry=12018;
UPDATE creature_template SET ScriptName='boss_ragnaros' WHERE entry=11502;
UPDATE creature_template SET ScriptName='mob_firesworn' WHERE entry=12099;
UPDATE creature_template SET ScriptName='mob_core_rager' WHERE entry=11672;
UPDATE creature_template SET ScriptName='mob_flamewaker_priest' WHERE entry=11662;
UPDATE gameobject_template SET ScriptName='go_molten_core_rune' WHERE entry IN (176951, 176952, 176953, 176954, 176955, 176956, 176957);

/* MOONGLADE */
UPDATE creature_template SET ScriptName='npc_clintar_dw_spirit' WHERE entry=22916;
UPDATE creature_template SET ScriptName='npc_keeper_remulos' WHERE entry=11832;
UPDATE creature_template SET ScriptName='boss_eranikus' WHERE entry=15491;
UPDATE gameobject_template SET ScriptName='go_omen_cluster' WHERE entry=180859;

/* MULGORE */
UPDATE creature_template SET ScriptName='npc_kyle_the_frenzied' WHERE entry=23616;

/* NAGRAND */
UPDATE creature_template SET ScriptName='mob_lump' WHERE entry=18351;
UPDATE creature_template SET ScriptName='npc_nagrand_captive' WHERE entry IN (18209,18210);
UPDATE creature_template SET ScriptName='npc_creditmarker_visit_with_ancestors' WHERE entry IN (18840,18841,18842,18843);
UPDATE creature_template SET ScriptName='npc_rethhedron' WHERE entry=22357;

/* NAXXRAMAS */
UPDATE instance_template SET ScriptName='instance_naxxramas' WHERE map=533;
UPDATE creature_template SET ScriptName='boss_anubrekhan' WHERE entry=15956;
UPDATE creature_template SET ScriptName='boss_faerlina' WHERE entry=15953;
UPDATE creature_template SET ScriptName='boss_maexxna' WHERE entry=15952;
UPDATE creature_template SET ScriptName='npc_web_wrap' WHERE entry=16486;
UPDATE creature_template SET ScriptName='boss_noth' WHERE entry=15954;
UPDATE creature_template SET ScriptName='boss_heigan' WHERE entry=15936;
UPDATE creature_template SET ScriptName='boss_loatheb' WHERE entry=16011;
UPDATE creature_template SET ScriptName='boss_razuvious' WHERE entry=16061;
UPDATE creature_template SET ScriptName='boss_gothik' WHERE entry=16060;
UPDATE creature_template SET ScriptName='spell_anchor' WHERE entry=16137;
UPDATE creature_template SET ScriptName='boss_thane_korthazz' WHERE entry=16064;
UPDATE creature_template SET ScriptName='boss_sir_zeliek' WHERE entry=16063;
UPDATE creature_template SET ScriptName='boss_lady_blaumeux' WHERE entry=16065;
UPDATE creature_template SET ScriptName='boss_alexandros_mograine' WHERE entry=16062;
UPDATE creature_template SET ScriptName='boss_patchwerk' WHERE entry=16028;
UPDATE creature_template SET ScriptName='boss_grobbulus' WHERE entry=15931;
UPDATE creature_template SET ScriptName='boss_gluth' WHERE entry=15932;
UPDATE creature_template SET ScriptName='boss_thaddius' WHERE entry=15928;
UPDATE creature_template SET ScriptName='boss_stalagg' WHERE entry=15929;
UPDATE creature_template SET ScriptName='boss_feugen' WHERE entry=15930;
UPDATE creature_template SET ScriptName='npc_tesla_coil' WHERE entry=16218;
UPDATE creature_template SET ScriptName='boss_sapphiron' WHERE entry=15989;
UPDATE gameobject_template SET ScriptName='go_sapphiron_birth' WHERE entry=181356;
UPDATE gameobject_template SET ScriptName='go_anub_door' WHERE entry=181126;
UPDATE creature_template SET ScriptName='boss_kelthuzad' WHERE entry=15990;

/* NETHERSTORM */
INSERT INTO scripted_areatrigger VALUES
(4497,'at_commander_dawnforge');
UPDATE gameobject_template SET ScriptName='go_manaforge_control_console' WHERE entry IN (183770,183956,184311,184312);
UPDATE creature_template SET ScriptName='npc_manaforge_control_console' WHERE entry IN (20209,20417,20418,20440);
UPDATE `creature_template` SET `ScriptName`='npc_manaforge_spawn' WHERE `Entry` IN(20218,20438,20439,20460);
UPDATE creature_template SET ScriptName='npc_commander_dawnforge' WHERE entry=19831;
UPDATE creature_template SET ScriptName='npc_bessy' WHERE entry=20415;
UPDATE creature_template SET ScriptName='npc_maxx_a_million' WHERE entry=19589;
UPDATE creature_template SET ScriptName='npc_zeppit' WHERE entry=22484;
UPDATE creature_template SET ScriptName='npc_protectorate_demolitionist' WHERE entry=20802;
UPDATE creature_template SET ScriptName='npc_captured_vanguard' WHERE entry=20763;
UPDATE creature_template SET ScriptName='npc_drijya' WHERE entry=20281;
UPDATE creature_template SET ScriptName='npc_dimensius' WHERE entry=19554;
UPDATE creature_template SET ScriptName='npc_salhadaar' WHERE entry=20454;
UPDATE creature_template SET ScriptName='npc_energy_ball' WHERE entry=20769;
UPDATE creature_template SET ScriptName='npc_scrap_reaver' WHERE entry IN(19849);
UPDATE creature_template SET ScriptName='npc_scrapped_fel_reaver' WHERE entry IN(20243);
UPDATE creature_template SET ScriptName='npc_adyen_the_lightwarden' WHERE entry IN(18537);
UPDATE creature_template SET ScriptName='npc_kaylaan_the_lost' WHERE entry IN(20794);
INSERT INTO scripted_areatrigger VALUES
(4523, 'at_socrethar_seat');
UPDATE creature_template SET ScriptName='npc_commander_hobb' WHERE entry IN(23434);
UPDATE creature_template SET ScriptName='npc_commander_arcus' WHERE entry IN(23452);

/* ONYXIA'S LAIR */
UPDATE instance_template SET ScriptName='instance_onyxias_lair' WHERE map=249;
UPDATE creature_template SET ScriptName='boss_onyxia' WHERE entry=10184;

/* ORGRIMMAR */
UPDATE creature_template SET ScriptName='npc_shenthul' WHERE entry=3401;
UPDATE creature_template SET ScriptName='npc_thrall_warchief' WHERE entry=4949;

/* RAGEFIRE CHASM */

/* RAZORFEN DOWNS */
UPDATE instance_template SET ScriptName='instance_razorfen_downs' WHERE map=129;
UPDATE creature_template SET ScriptName='npc_belnistrasz' WHERE entry=8516;
INSERT INTO scripted_event_id VALUES (3130, 'event_go_tutenkash_gong');

/* RAZORFEN KRAUL */
UPDATE instance_template SET ScriptName='instance_razorfen_kraul' WHERE map=47;
UPDATE creature_template SET ScriptName='npc_willix_the_importer' WHERE entry=4508;
UPDATE creature_template SET ScriptName='npc_snufflenose_gopher' WHERE entry=4781;

/* REDRIDGE MOUNTAINS */
UPDATE creature_template SET ScriptName='npc_corporal_keeshan' WHERE entry=349;

/* RUINS OF AHN'QIRAJ */
UPDATE instance_template SET ScriptName='instance_ruins_of_ahnqiraj' WHERE map=509;
UPDATE creature_template SET ScriptName='mob_anubisath_guardian' WHERE entry=15355;
UPDATE creature_template SET ScriptName='boss_kurinnaxx' WHERE entry=15348;
UPDATE creature_template SET ScriptName='boss_ayamiss' WHERE entry=15369;
UPDATE creature_template SET ScriptName='boss_moam' WHERE entry=15340;
UPDATE creature_template SET ScriptName='boss_ossirian' WHERE entry=15339;
UPDATE gameobject_template SET ScriptName='go_ossirian_crystal' WHERE entry=180619;
UPDATE creature_template SET ScriptName='npc_hive_zara_larva' WHERE entry=15555;
UPDATE creature_template SET ScriptName='boss_buru' WHERE entry=15370;
UPDATE creature_template SET ScriptName='npc_buru_egg' WHERE entry=15514;
UPDATE creature_template SET ScriptName='npc_general_andorov' WHERE entry=15471;
UPDATE creature_template SET ScriptName='npc_kaldorei_elite' WHERE entry=15473;

/* SCARLET MONASTERY */
UPDATE instance_template SET ScriptName='instance_scarlet_monastery' WHERE map=189;
UPDATE creature_template SET ScriptName='boss_arcanist_doan' WHERE entry=6487;
UPDATE creature_template SET ScriptName='boss_herod' WHERE entry=3975;
UPDATE creature_template SET ScriptName='boss_high_inquisitor_whitemane' WHERE entry=3977;
UPDATE creature_template SET ScriptName='boss_scarlet_commander_mograine' WHERE entry=3976;
UPDATE creature_template SET ScriptName='mob_scarlet_trainee' WHERE entry=6575;
UPDATE creature_template SET ScriptName='boss_headless_horseman' WHERE entry=23682;
UPDATE creature_template SET ScriptName='boss_head_of_horseman' WHERE entry=23775;

/* SCHOLOMANCE */
UPDATE instance_template SET ScriptName='instance_scholomance' WHERE map=289;
UPDATE creature_template SET ScriptName='boss_darkmaster_gandling' WHERE entry=1853;
UPDATE creature_template SET ScriptName='boss_jandice_barov' WHERE entry=10503;
UPDATE creature_template SET ScriptName='npc_spectral_tutor' WHERE entry=10498;
INSERT INTO scripted_event_id VALUES
(5140,'event_dawn_gambit'),
(5618,'event_spell_gandling_shadow_portal'),
(5619,'event_spell_gandling_shadow_portal'),
(5620,'event_spell_gandling_shadow_portal'),
(5621,'event_spell_gandling_shadow_portal'),
(5622,'event_spell_gandling_shadow_portal'),
(5623,'event_spell_gandling_shadow_portal');

/* SEARING GORGE */
UPDATE creature_template SET ScriptName='npc_dorius_stonetender' WHERE entry=8284;

/* SHADOWFANG KEEP */
UPDATE instance_template SET ScriptName='instance_shadowfang_keep' WHERE map=33;
UPDATE creature_template SET ScriptName='npc_shadowfang_prisoner' WHERE entry IN (3849,3850);
UPDATE creature_template SET ScriptName='npc_arugal' WHERE entry=10000;
UPDATE creature_template SET ScriptName='npc_deathstalker_vincent' WHERE entry=4444;
UPDATE creature_template SET ScriptName='mob_arugal_voidwalker' WHERE entry=4627;
UPDATE creature_template SET ScriptName='boss_arugal' WHERE entry=4275;

/* SHADOWMOON VALLEY */
UPDATE creature_template SET ScriptName='boss_doomwalker' WHERE entry=17711;
UPDATE creature_template SET ScriptName='npc_dragonmaw_peon' WHERE entry=22252;
UPDATE creature_template SET ScriptName='mob_mature_netherwing_drake' WHERE entry=21648;
UPDATE creature_template SET ScriptName='mob_enslaved_netherwing_drake' WHERE entry=21722;
UPDATE creature_template SET ScriptName='npc_wilda' WHERE entry=21027;
UPDATE creature_template SET ScriptName='mob_torloth' WHERE entry=22076;
UPDATE creature_template SET ScriptName='npc_totem_of_spirits' WHERE entry=21071;
INSERT INTO scripted_event_id VALUES
(13513,'event_spell_soul_captured_credit'),
(13514,'event_spell_soul_captured_credit'),
(13515,'event_spell_soul_captured_credit'),
(13516,'event_spell_soul_captured_credit');
UPDATE creature_template SET ScriptName='npc_lord_illidan_stormrage' WHERE entry=22083;
UPDATE gameobject_template SET ScriptName='go_crystal_prison' WHERE entry=185126;
UPDATE creature_template SET ScriptName='npc_spawned_oronok_tornheart' WHERE entry=21685;
UPDATE creature_template SET ScriptName='npc_domesticated_felboar' WHERE entry=21195;
UPDATE creature_template SET ScriptName='npc_shadowmoon_tuber_node' WHERE entry=21347;
UPDATE creature_template SET ScriptName='npc_veneratus_spawn_node' WHERE entry=21334;
UPDATE creature_template SET ScriptName='mob_shadowmoon_soulstealer' WHERE entry=22061;
UPDATE creature_template SET ScriptName='npc_shadowlord_deathwail' WHERE entry=22006;
UPDATE creature_template SET ScriptName='npc_disobedient_dragonmaw_peon' WHERE entry IN(23311);
UPDATE creature_template SET ScriptName='npc_dragonmaw_racer_muckjaw' WHERE entry=23340;
UPDATE creature_template SET ScriptName='npc_dragonmaw_racer_trope' WHERE entry=23342;
UPDATE creature_template SET ScriptName='npc_dragonmaw_racer_corlok' WHERE entry=23344;
UPDATE creature_template SET ScriptName='npc_dragonmaw_racer_ichman' WHERE entry=23345;
UPDATE creature_template SET ScriptName='npc_dragonmaw_racer_mulverick' WHERE entry=23346;
UPDATE creature_template SET ScriptName='npc_dragonmaw_racer_skyshatter' WHERE entry=23348;
UPDATE creature_template SET ScriptName='mob_bt_battle_fighter' WHERE entry IN (22857, 22858, 22860, 22861, 22862, 22863, 22864, 22988);
UPDATE creature_template SET ScriptName='npc_bt_battle_sensor' WHERE entry=22934;

/* SHATTRATH */
UPDATE creature_template SET ScriptName='npc_dirty_larry' WHERE entry=19720;
UPDATE creature_template SET ScriptName='npc_khadgars_servant' WHERE entry=19685;
UPDATE creature_template SET ScriptName='npc_salsalabim' WHERE entry=18584;
UPDATE creature_template SET ScriptName='npc_adal' WHERE entry IN(18481);

/* SILITHUS */
UPDATE creature_template SET ScriptName='npc_anachronos_the_ancient' WHERE entry=15381;
UPDATE gameobject_template SET ScriptName='go_crystalline_tear' WHERE entry=180633;
UPDATE creature_template SET ScriptName='npc_solenor' WHERE entry IN (14530,14536);

/* SILVERMOON */

/* SILVERPINE FOREST */
UPDATE creature_template SET ScriptName='npc_deathstalker_erland' WHERE entry=1978;
UPDATE creature_template SET ScriptName='npc_deathstalker_faerleia' WHERE entry=2058;

/* STOCKADES */


/* STONETALON MOUNTAINS */
UPDATE creature_template SET ScriptName='npc_kaya' WHERE entry=11856;

/* STORMWIND CITY */
UPDATE creature_template SET ScriptName='npc_bartleby' WHERE entry=6090;
UPDATE creature_template SET ScriptName='npc_dashel_stonefist' WHERE entry=4961;
UPDATE creature_template SET ScriptName='npc_lady_katrana_prestor' WHERE entry=1749;
UPDATE creature_template SET ScriptName='npc_squire_rowe' WHERE entry=17804;
UPDATE creature_template SET ScriptName='npc_reginald_windsor' WHERE entry =12580;

/* STRANGLETHORN VALE */
UPDATE creature_template SET ScriptName='mob_yenniku' WHERE entry=2530;
UPDATE gameobject_template SET ScriptName='go_transpolyporter_bb' WHERE entry IN(142172);

/* STRATHOLME */
UPDATE instance_template SET ScriptName='instance_stratholme' WHERE map=329;
UPDATE creature_template SET ScriptName='boss_dathrohan_balnazzar' WHERE entry=10812;
UPDATE creature_template SET ScriptName='boss_maleki_the_pallid' WHERE entry=10438;
UPDATE creature_template SET ScriptName='boss_cannon_master_willey' WHERE entry=10997;
UPDATE creature_template SET ScriptName='boss_baroness_anastari' WHERE entry=10436;
UPDATE creature_template SET ScriptName='boss_silver_hand_bosses' WHERE entry IN (17910,17911,17912,17913,17914);
UPDATE creature_template SET ScriptName='npc_aurius' WHERE entry=10917;
UPDATE creature_template SET ScriptName='mobs_spectral_ghostly_citizen' WHERE entry IN (10384,10385);
UPDATE creature_template SET ScriptName='mob_restless_soul' WHERE entry=11122;
UPDATE gameobject_template SET ScriptName='go_gauntlet_gate' WHERE entry=175357;
UPDATE gameobject_template SET ScriptName='go_service_gate' WHERE entry=175368;
UPDATE gameobject_template SET ScriptName='go_stratholme_postbox' WHERE entry IN (176346,176349,176350,176351,176352,176353);

/* SUNKEN TEMPLE */
UPDATE instance_template SET ScriptName='instance_sunken_temple' WHERE map=109;
INSERT INTO scripted_areatrigger VALUES
(4016,'at_shade_of_eranikus');
UPDATE creature_template SET ScriptName='npc_malfurion_stormrage' WHERE entry=15362;
INSERT INTO scripted_event_id VALUES
(3094,'event_antalarion_statue_activation'),
(3095,'event_antalarion_statue_activation'),
(3097,'event_antalarion_statue_activation'),
(3098,'event_antalarion_statue_activation'),
(3099,'event_antalarion_statue_activation'),
(3100,'event_antalarion_statue_activation');
UPDATE creature_template SET ScriptName='npc_shade_of_hakkar' WHERE entry=8440;
UPDATE gameobject_template SET ScriptName='go_eternal_flame' WHERE entry IN (148418,148419,148420,148421);
INSERT INTO scripted_event_id VALUES
(8502,'event_avatar_of_hakkar');

/* SUNWELL PLATEAU */
UPDATE instance_template SET ScriptName='instance_sunwell_plateau' WHERE map=580;
UPDATE creature_template SET ScriptName='boss_brutallus' WHERE entry=24882;
UPDATE creature_template SET ScriptName='boss_kalecgos' WHERE entry=24850;
UPDATE creature_template SET ScriptName='boss_kalecgos_humanoid' WHERE entry=24891;
UPDATE creature_template SET ScriptName='boss_sathrovarr' WHERE entry=24892;
INSERT INTO scripted_areatrigger VALUES
(4853,'at_madrigosa');
UPDATE creature_template SET ScriptName='boss_alythess' WHERE entry=25166;
UPDATE creature_template SET ScriptName='boss_sacrolash' WHERE entry=25165;
UPDATE creature_template SET ScriptName='npc_shadow_image' WHERE entry=25214;
UPDATE creature_template SET ScriptName='boss_muru' WHERE entry=25741;
UPDATE creature_template SET ScriptName='boss_entropius' WHERE entry=25840;
UPDATE creature_template SET ScriptName='npc_portal_target' WHERE entry=25770;
UPDATE creature_template SET ScriptName='boss_kiljaeden' WHERE entry=25315;
UPDATE creature_template SET ScriptName='npc_kiljaeden_controller' WHERE entry=25608;
UPDATE creature_template SET ScriptName='spell_dummy_npc_brutallus_cloud' WHERE entry=25703;
UPDATE creature_template SET ScriptName='boss_felmyst' WHERE entry=25038;
UPDATE creature_template SET ScriptName='npc_shield_orb' WHERE entry=25502;
UPDATE creature_template SET ScriptName='npc_power_blue_flight' WHERE entry=25653;
UPDATE creature_template SET ScriptName='npc_demonic_vapor' WHERE entry=25265;
UPDATE creature_template SET ScriptName='npc_darkness' WHERE entry=25879;
UPDATE creature_template SET ScriptName='npc_singularity' WHERE entry=25855;

/* SWAMP OF SORROWS */
UPDATE creature_template SET ScriptName='npc_galen_goodward' WHERE entry=5391;

/* TANARIS */
UPDATE creature_template SET ScriptName='mob_aquementas' WHERE entry=9453;
UPDATE creature_template SET ScriptName='npc_custodian_of_time' WHERE entry=20129;
UPDATE creature_template SET ScriptName='npc_oox17tn' WHERE entry=7784;
UPDATE creature_template SET ScriptName='npc_stone_watcher_of_norgannon' WHERE entry=7918;
UPDATE creature_template SET ScriptName='npc_tooga' WHERE entry=5955;

/* TELDRASSIL */
UPDATE creature_template SET ScriptName='npc_mist' WHERE entry=3568;

/*  */
/* TEMPEST KEEP */
/*  */

/* THE MECHANAR */
UPDATE creature_template SET ScriptName='boss_mechano_lord_capacitus' WHERE entry = 19219;
UPDATE creature_template SET ScriptName='boss_nethermancer_sepethrea' WHERE entry=19221;
UPDATE creature_template SET ScriptName='boss_pathaleon_the_calculator' WHERE entry=19220;
UPDATE creature_template SET ScriptName='mob_nether_wraith' WHERE entry=21062;
UPDATE instance_template SET ScriptName='instance_mechanar' WHERE map=554;
UPDATE creature_template SET ScriptName='npc_raging_flames' WHERE entry=20481;

/* THE BOTANICA */
UPDATE creature_template SET ScriptName='boss_high_botanist_freywinn' WHERE entry=17975;
UPDATE creature_template SET ScriptName='boss_laj' WHERE entry=17980;
UPDATE creature_template SET ScriptName='boss_warp_splinter' WHERE entry=17977;
UPDATE creature_template SET ScriptName='mob_warp_splinter_treant' WHERE entry=19949;
UPDATE creature_template SET ScriptName='boss_thorngrin' WHERE entry IN(17978);

/* THE ARCATRAZ */
UPDATE instance_template SET ScriptName='instance_arcatraz' WHERE map=552;
UPDATE creature_template SET ScriptName='boss_harbinger_skyriss' WHERE entry=20912;
UPDATE creature_template SET ScriptName='boss_dalliah' WHERE entry=20885;
UPDATE creature_template SET ScriptName='boss_soccothrates' WHERE entry=20886;
UPDATE creature_template SET ScriptName='npc_warden_mellichar' WHERE entry=20904;
UPDATE creature_template SET ScriptName='npc_millhouse_manastorm' WHERE entry=20977;
UPDATE creature_template SET ScriptName='npc_arcatraz_defender' WHERE entry=20857;

/* THE EYE */
UPDATE instance_template SET ScriptName='instance_the_eye' WHERE map=550;
/* Al'ar event */
UPDATE creature_template SET ScriptName='boss_alar' WHERE entry=19514;
/* Void Reaver event */
UPDATE creature_template SET ScriptName='boss_void_reaver' WHERE entry=19516;
/* Astromancer event */
UPDATE creature_template SET ScriptName='boss_high_astromancer_solarian' WHERE entry=18805;
UPDATE creature_template SET ScriptName='mob_solarium_priest' WHERE entry=18806;
/* Kael'thas event */
UPDATE creature_template SET ScriptName='boss_kaelthas' WHERE entry=19622;
UPDATE creature_template SET ScriptName='boss_thaladred_the_darkener' WHERE entry=20064;
UPDATE creature_template SET ScriptName='boss_lord_sanguinar' WHERE entry=20060;
UPDATE creature_template SET ScriptName='boss_grand_astromancer_capernian' WHERE entry=20062;
UPDATE creature_template SET ScriptName='boss_master_engineer_telonicus' WHERE entry=20063;
UPDATE creature_template SET ScriptName='mob_phoenix_tk' WHERE entry=21362;
UPDATE creature_template SET ScriptName='mob_phoenix_egg_tk' WHERE entry=21364;

/* TEMPLE OF AHN'QIRAJ */
UPDATE instance_template SET ScriptName='instance_temple_of_ahnqiraj' WHERE map=531;
UPDATE creature_template SET ScriptName='boss_cthun' WHERE entry=15727;
UPDATE creature_template SET ScriptName='boss_skeram' WHERE entry=15263;
UPDATE creature_template SET ScriptName='boss_vem' WHERE entry=15544;
UPDATE creature_template SET ScriptName='boss_yauj' WHERE entry=15543;
UPDATE creature_template SET ScriptName='boss_kri' WHERE entry=15511;
UPDATE creature_template SET ScriptName='boss_sartura' WHERE entry=15516;
UPDATE creature_template SET ScriptName='boss_fankriss' WHERE entry=15510;
UPDATE creature_template SET ScriptName='boss_viscidus' WHERE entry=15299;
UPDATE creature_template SET ScriptName='npc_glob_of_viscidus' WHERE entry=15667;
UPDATE creature_template SET ScriptName='boss_huhuran' WHERE entry=15509;
UPDATE creature_template SET ScriptName='boss_veklor' WHERE entry=15276;
UPDATE creature_template SET ScriptName='boss_veknilash' WHERE entry=15275;
UPDATE creature_template SET ScriptName='boss_ouro' WHERE entry=15517;
UPDATE creature_template SET ScriptName='npc_ouro_spawner' WHERE entry=15957;
UPDATE creature_template SET ScriptName='boss_eye_of_cthun' WHERE entry=15589;
UPDATE creature_template SET ScriptName='mob_sartura_royal_guard' WHERE entry=15984;
UPDATE creature_template SET ScriptName='mob_giant_claw_tentacle' WHERE entry=15728;
UPDATE creature_template SET ScriptName='mob_anubisath_sentinel' WHERE entry=15264;
INSERT INTO scripted_areatrigger VALUES
(4033,'at_stomach_cthun'),
(4034,'at_stomach_cthun');

/* TEROKKAR FOREST */
UPDATE creature_template SET ScriptName='mob_netherweb_victim' WHERE entry=22355;
UPDATE creature_template SET ScriptName='mob_unkor_the_ruthless' WHERE entry=18262;
UPDATE creature_template SET ScriptName='npc_akuno' WHERE entry=22377;
UPDATE creature_template SET ScriptName='npc_hungry_nether_ray' WHERE entry=23439;
UPDATE creature_template SET ScriptName='npc_letoll' WHERE entry=22458;
UPDATE creature_template SET ScriptName='npc_isla_starmane' WHERE entry=18760;
UPDATE creature_template SET ScriptName="npc_skywing" WHERE entry=22424;
UPDATE creature_template SET ScriptName="npc_cenarion_sparrowhawk" WHERE entry=22972;
UPDATE creature_template SET ScriptName="npc_skyguard_prisoner" WHERE entry=23383;
UPDATE creature_template SET ScriptName='npc_avatar_of_terokk' WHERE entry=22375;
UPDATE creature_template SET ScriptName='npc_minion_of_terokk' WHERE entry=22376;
UPDATE creature_template SET ScriptName='npc_draenei_tomb_guardian' WHERE entry=22285;
UPDATE creature_template SET ScriptName='npc_vengeful_harbinger' WHERE entry=21638;
UPDATE creature_template SET ScriptName='boss_terokk' WHERE entry IN(21838);
INSERT INTO scripted_event_id VALUES
(15014, 'event_summon_terokk');

/* THOUSAND NEEDLES */
UPDATE creature_template SET ScriptName='npc_kanati' WHERE entry=10638;
UPDATE creature_template SET ScriptName='npc_plucky_johnson' WHERE entry=6626;
UPDATE creature_template SET ScriptName='npc_paoka_swiftmountain' WHERE entry=10427;
UPDATE creature_template SET ScriptName='npc_lakota_windsong' WHERE entry=10646;

/* THUNDER BLUFF */

/* TIRISFAL GLADES */
UPDATE gameobject_template SET ScriptName='go_mausoleum_trigger' WHERE entry=104593;
UPDATE gameobject_template SET ScriptName='go_mausoleum_door' WHERE entry=176594;
UPDATE creature_template SET ScriptName='npc_calvin_montague' WHERE entry=6784;

/* ULDAMAN */
INSERT INTO scripted_event_id VALUES
(2228,'event_spell_altar_boss_aggro'),
(2268,'event_spell_altar_boss_aggro');
UPDATE creature_template SET ScriptName='boss_archaedas' WHERE entry=2748;
UPDATE creature_template SET ScriptName='mob_archaeras_add' WHERE entry IN (7309,7076,7077,10120);
UPDATE instance_template SET ScriptName='instance_uldaman' WHERE map=70;

/* UN'GORO CRATER */
UPDATE creature_template SET ScriptName='npc_ame01' WHERE entry=9623;
UPDATE creature_template SET ScriptName='npc_ringo' WHERE entry=9999;
UPDATE creature_template SET ScriptName='npc_simone_seductress' WHERE entry=14533;
UPDATE creature_template SET ScriptName='npc_simone_the_inconspicuous' WHERE entry=14527;
UPDATE creature_template SET ScriptName='npc_precious_the_devourer' WHERE entry=14538;

/* UNDERCITY */
UPDATE creature_template SET ScriptName='npc_lady_sylvanas_windrunner' WHERE entry=10181;

/* WAILING CAVERNS */
UPDATE instance_template SET ScriptName='instance_wailing_caverns' WHERE map=43;
UPDATE creature_template SET ScriptName='npc_disciple_of_naralex' WHERE entry=3678;

/* WESTERN PLAGUELANDS */
UPDATE creature_template SET ScriptName='npc_the_scourge_cauldron' WHERE entry=11152;
UPDATE creature_template SET ScriptName='npc_anchorite_truuen' WHERE entry=17238;
UPDATE creature_template SET ScriptName='npc_taelan_fordring' WHERE entry=1842;
UPDATE creature_template SET ScriptName='npc_isillien' WHERE entry=1840;
UPDATE creature_template SET ScriptName='npc_tirion_fordring' WHERE entry=12126;

/* WESTFALL */
UPDATE creature_template SET ScriptName='npc_daphne_stilwell' WHERE entry=6182;
UPDATE creature_template SET ScriptName='npc_defias_traitor' WHERE entry=467;

/* WETLANDS */
UPDATE creature_template SET ScriptName='npc_tapoke_slim_jahn' WHERE entry=4962;
UPDATE creature_template SET ScriptName='npc_mikhail' WHERE entry=4963;

/* WINTERSPRING */
UPDATE creature_template SET ScriptName='npc_ranshalla' WHERE entry=10300;
UPDATE gameobject_template SET ScriptName='go_elune_fire' WHERE entry IN (177417, 177404);
UPDATE creature_template SET ScriptName='npc_artorius' WHERE entry IN (14531,14535);

/* ZANGARMARSH */
INSERT INTO scripted_event_id VALUES
(11225,'event_taxi_stormcrow');
UPDATE creature_template SET ScriptName='npc_cooshcoosh' WHERE entry=18586;
UPDATE creature_template SET ScriptName='npc_kayra_longmane' WHERE entry=17969;
UPDATE creature_template SET ScriptName='npc_fhwoor' WHERE entry=17877;
UPDATE creature_template SET ScriptName='npc_frostbite' WHERE entry=20061;

/* ZUL'AMAN */
UPDATE instance_template SET ScriptName='instance_zulaman' WHERE map=568;
UPDATE creature_template SET ScriptName='npc_harrison_jones_za' WHERE entry=24358;
UPDATE gameobject_template SET ScriptName='go_strange_gong' WHERE entry=187359;
UPDATE creature_template SET ScriptName='boss_akilzon' WHERE entry=23574;
UPDATE creature_template SET ScriptName='mob_soaring_eagle' WHERE entry=24858;
UPDATE creature_template SET ScriptName='boss_halazzi' WHERE entry=23577;
UPDATE creature_template SET ScriptName='boss_spirit_lynx' WHERE entry=24143;
UPDATE creature_template SET ScriptName='boss_janalai' WHERE entry=23578;
UPDATE creature_template SET ScriptName='boss_malacrass' WHERE entry=24239;
UPDATE creature_template SET ScriptName='boss_nalorakk' WHERE entry=23576;
UPDATE creature_template SET ScriptName='boss_zuljin' WHERE entry=23863;
UPDATE creature_template SET ScriptName='npc_feather_vortex' WHERE entry=24136;
UPDATE creature_template SET ScriptName='npc_dragonhawk_egg' WHERE entry=23817;
UPDATE creature_template SET ScriptName='npc_janalai_firebomb' WHERE entry=23920;
UPDATE creature_template SET ScriptName='npc_amanishi_hatcher' WHERE entry IN (23818,24504);
UPDATE creature_template SET ScriptName='npc_forest_frog' WHERE entry=24396;

/* ZUL'FARRAK */
UPDATE instance_template SET ScriptName='instance_zulfarrak' WHERE map=209;
INSERT INTO scripted_event_id VALUES
(2488,'event_go_zulfarrak_gong'),
(2609,'event_spell_unlocking');
INSERT INTO scripted_areatrigger VALUES
(1447,'at_zulfarrak');
UPDATE creature_template SET ScriptName='boss_zumrah' WHERE entry=7271;

/* ZUL'GURUB */
UPDATE instance_template SET ScriptName='instance_zulgurub' WHERE map=309;
UPDATE creature_template SET ScriptName='boss_jeklik' WHERE entry=14517;
UPDATE creature_template SET ScriptName='boss_venoxis' WHERE entry=14507;
UPDATE creature_template SET ScriptName='boss_marli' WHERE entry=14510;
UPDATE creature_template SET ScriptName='boss_mandokir' WHERE entry=11382;
UPDATE creature_template SET ScriptName='mob_ohgan' WHERE entry=14988;
UPDATE creature_template SET ScriptName='boss_jindo' WHERE entry=11380;
UPDATE creature_template SET ScriptName='boss_hakkar' WHERE entry=14834;
UPDATE creature_template SET ScriptName='boss_thekal' WHERE entry=14509;
UPDATE creature_template SET ScriptName='boss_arlokk' WHERE entry=14515;
UPDATE gameobject_template SET ScriptName='go_gong_of_bethekk' WHERE entry=180526;
UPDATE creature_template SET ScriptName='boss_hazzarah' WHERE entry=15083;
UPDATE creature_template SET ScriptName='boss_renataki' WHERE entry=15084;
UPDATE creature_template SET ScriptName='mob_zealot_lorkhan' WHERE entry=11347;
UPDATE creature_template SET ScriptName='mob_zealot_zath' WHERE entry=11348;
UPDATE creature_template SET ScriptName='mob_healing_ward' WHERE entry=14987;
UPDATE creature_template SET ScriptName='npc_gurubashi_bat_rider' WHERE entry=14750;
UPDATE creature_template SET ScriptName='npc_zulian_prowler' WHERE entry=15101;
UPDATE creature_template SET ScriptName='npc_soulflayer' WHERE entry=11359;

--
-- Below contains data for table `script_texts` mainly used in C++ parts.
-- valid entries for table are between -1000000 and -1999999
--

TRUNCATE script_texts;

--
-- -1 000 000 First 100 entries are reserved for special use, do not add regular text here.
--

INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1000000,'<ScriptDev2 Text Entry Missing!>',0,0,0,0,'DEFAULT_TEXT'),
(-1000001,'%s goes into a killing frenzy!',0,2,0,0,'EMOTE_GENERIC_FRENZY_KILL'),
(-1000002,'%s goes into a frenzy!',0,2,0,0,'EMOTE_GENERIC_FRENZY'),
(-1000003,'%s becomes enraged!',0,2,0,0,'EMOTE_GENERIC_ENRAGED'),
(-1000004,'%s goes into a berserker rage!',0,2,0,0,'EMOTE_GENERIC_BERSERK'),
(-1000005,'%s goes into a frenzy!',0,3,0,0,'EMOTE_BOSS_GENERIC_FRENZY'),
(-1000006,'%s becomes enraged!',0,3,0,0,'EMOTE_BOSS_GENERIC_ENRAGED');

--
-- Normal text entries below. Say/Yell/Whisper/Emote for any regular world object.
-- Text entries for text used by creatures in instances are using map id as part of entry.
-- Example: for map 430, the database text entry for all creatures normally on this map start with -1430
-- Values decrement as they are made.
-- For creatures outside instance, use -1 000 100 and below. Decrement value as they are made.
--
-- Comment should contain a unique name that can be easily identified later by using sql queries like for example
-- SELECT * FROM script_texts WHERE comment LIKE '%defias%';
-- Place the define used in script itself at the end of the comment.
--
-- Do not change entry without a very good reason. Localization projects depends on using entries that does not change!
-- Example: UPDATE script_texts SET content_loc1 = 'the translated text' WHERE entry = -1000100;
--

-- -1 000 100 GENERAL MAPS (not instance maps)
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1000100,'Come, little ones. Face me!',0,1,0,0,'azuregos SAY_TELEPORT'),

(-1000101,'Follow me, $N. I\'ll take you to the Defias hideout. But you better protect me or I am as good as dead',0,0,7,0,'defias traitor SAY_START'),
(-1000102,'The entrance is hidden here in Moonbrook. Keep your eyes peeled for thieves. They want me dead.',0,0,7,0,'defias traitor SAY_PROGRESS'),
(-1000103,'You can go tell Stoutmantle this is where the Defias Gang is holed up, $N.',0,0,7,0,'defias traitor SAY_END'),
(-1000104,'$N coming in fast! Prepare to fight!',0,0,7,0,'defias traitor SAY_AGGRO_1'),
(-1000105,'Help!',0,0,7,0,'defias traitor SAY_AGGRO_2'),

(-1000106,'Everyone ready?',0,0,1,0,'torek SAY_READY'),
(-1000107,'Ok, Lets move out!',0,0,1,0,'torek SAY_MOVE'),
(-1000108,'Prepare yourselves. Silverwing is just around the bend.',0,0,1,0,'torek SAY_PREPARE'),
(-1000109,'Silverwing is ours!',0,0,1,0,'torek SAY_WIN'),
(-1000110,'Go report that the outpost is taken. We will remain here.',0,0,1,0,'torek SAY_END'),

(-1000111,'Our house is this way, through the thicket.',0,0,7,1,'magwin SAY_START'),
(-1000112,'Help me!',0,0,7,0,'magwin SAY_AGGRO'),
(-1000113,'My poor family. Everything has been destroyed.',0,0,7,5,'magwin SAY_PROGRESS'),
(-1000114,'Father! Father! You\'re alive!',0,0,7,22,'magwin SAY_END1'),
(-1000115,'You can thank $N for getting me back here safely, father.',0,0,7,1,'magwin SAY_END2'),
(-1000116,'%s hugs her father.',0,2,7,5,'magwin EMOTE_HUG'),

(-1000117,'Thank you for agreeing to help. Now, let\'s get out of here $N.',0,0,1,0,'wounded elf SAY_ELF_START'),
(-1000118,'Over there! They\'re following us!',0,0,1,0,'wounded elf SAY_ELF_SUMMON1'),
(-1000119,'Allow me a moment to rest. The journey taxes what little strength I have.',0,0,1,16,'wounded elf SAY_ELF_RESTING'),
(-1000120,'Did you hear something?',0,0,1,0,'wounded elf SAY_ELF_SUMMON2'),
(-1000121,'Falcon Watch, at last! Now, where\'s my... Oh no! My pack, it\'s missing! Where has -',0,0,1,0,'wounded elf SAY_ELF_COMPLETE'),
(-1000122,'You won\'t keep me from getting to Falcon Watch!',0,0,1,0,'wounded elf SAY_ELF_AGGRO'),

(-1000123,'Ready when you are, $c.',0,0,0,15,'big will SAY_BIG_WILL_READY'),
(-1000124,'The Affray has begun. $n, get ready to fight!',0,0,0,0,'twiggy SAY_TWIGGY_BEGIN'),
(-1000125,'You! Enter the fray!',0,0,0,0,'twiggy SAY_TWIGGY_FRAY'),
(-1000126,'Challenger is down!',0,0,0,0,'twiggy SAY_TWIGGY_DOWN'),
(-1000127,'The Affray is over.',0,0,0,0,'twiggy SAY_TWIGGY_OVER'),

(-1000128,'We need you to send reinforcements to Manaforge Duro, Ardonis. This is not a request, it\'s an order.',0,0,0,0,'dawnforge SAY_COMMANDER_DAWNFORGE_1'),
(-1000129,'You cannot be serious! We are severely understaffed and can barely keep this manaforge functional!',0,0,0,0,'dawnforge SAY_ARCANIST_ARDONIS_1'),
(-1000130,'You will do as ordered. Manaforge Duro has come under heavy attack by mana creatures and the situation is out of control. Failure to comply will not be tolerated!',0,0,0,0,'dawnforge SAY_COMMANDER_DAWNFORGE_2'),
(-1000131,'Indeed, it is not a request.',0,0,0,0,'dawnforge SAY_PATHALEON_CULATOR_IMAGE_1'),
(-1000132,'My lord!',0,0,0,0,'dawnforge SAY_COMMANDER_DAWNFORGE_3'),
(-1000133,'Duro will be reinforced! Ultris was a complete disaster. I will NOT have that mistake repeated!',0,0,0,0,'dawnforge PATHALEON_CULATOR_IMAGE_2'),
(-1000134,'We\'ve had too many setbacks along the way: Hellfire Citadel, Fallen Sky Ridge, Firewing Point... Prince Kael\'thas will tolerate no further delays. I will tolerate nothing other than complete success!',0,0,0,0,'dawnforge PATHALEON_CULATOR_IMAGE_2_1'),
(-1000135,'I am returning to Tempest Keep. See to it that I do not have reason to return!',0,0,0,0,'dawnforge PATHALEON_CULATOR_IMAGE_2_2' ),
(-1000136,'Yes, my lord.',0,0,0,0,'dawnforge COMMANDER_DAWNFORGE_4 SAY_ARCANIST_ARDONIS_2'),
(-1000137,'See to it, Ardonis!',0,0,0,0,'dawnforge COMMANDER_DAWNFORGE_5'),

(-1000138,'Prepare to enter oblivion, meddlers. You have unleashed a god!',0,1,0,15,'Salhadaar SAY'),
(-1000139,'Avruu\'s magic is broken! I\'m free once again!',0,0,0,0,'aeranas SAY_FREE'),

(-1000140,'Let\'s go.',0,0,1,0,'lilatha SAY_START'),
(-1000141,'$N, let\'s use the antechamber to the right.',0,0,1,0,'lilatha SAY_PROGRESS1'),
(-1000142,'I can see the light at the end of the tunnel!',0,0,1,0,'lilatha SAY_PROGRESS2'),
(-1000143,'There\'s Farstrider Enclave now, $C. Not far to go... Look out! Troll ambush!!',0,0,1,0,'lilatha SAY_PROGRESS3'),
(-1000144,'Thank you for saving my life and bringing me back to safety, $N',0,0,1,0,'lilatha SAY_END1'),
(-1000145,'Captain Helios, I\'ve been rescued from the Amani Catacombs. Reporting for duty, sir!',0,0,1,0,'lilatha SAY_END2'),
(-1000146,'Liatha, get someone to look at those injuries. Thank you for bringing her back safely.',0,0,1,0,'lilatha CAPTAIN_ANSWER'),

(-1000147,'I remember well the sting of defeat at the conclusion of the Third War. I have waited far too long for my revenge. Now the shadow of the Legion falls over this world. It is only a matter of time until all of your failed creation... is undone.',11332,1,0,0,'kazzak SAY_INTRO'),
(-1000148,'The Legion will conquer all!',11333,1,0,0,'kazzak SAY_AGGRO1'),
(-1000149,'All mortals will perish!',11334,1,0,0,'kazzak SAY_AGGRO2'),
(-1000150,'All life must be eradicated!',11335,1,0,0,'kazzak SAY_SURPREME1'),
(-1000151,'I\'ll rip the flesh from your bones!',11336,1,0,0,'kazzak SAY_SURPREME2'),
(-1000152,'Kirel Narak!',11337,1,0,0,'kazzak SAY_KILL1'),
(-1000153,'Contemptible wretch!',11338,1,0,0,'kazzak SAY_KILL2'),
(-1000154,'The universe will be remade.',11339,1,0,0,'kazzak SAY_KILL3'),
(-1000155,'The Legion... will never... fall.',11340,1,0,0,'kazzak SAY_DEATH'),

(-1000156,'Bloodmaul Brew? Me favorite!',0,0,0,0,'bladespire ogre SAY_BREW_1'),

(-1000157,'Invaders, you dangle upon the precipice of oblivion! The Burning Legion comes and with it comes your end.',0,1,0,0,'kazzak SAY_RAND1'),
(-1000158,'Impudent whelps, you only delay the inevitable. Where one has fallen, ten shall rise. Such is the will of Kazzak...',0,1,0,0,'kazzak SAY_RAND2'),

(-1000159,'Do not proceed. You will be eliminated.',11344,1,0,0,'doomwalker SAY_AGGRO'),
(-1000160,'Tectonic disruption commencing.',11345,1,0,0,'doomwalker SAY_EARTHQUAKE_1'),
(-1000161,'Magnitude set. Release.',11346,1,0,0,'doomwalker SAY_EARTHQUAKE_2'),
(-1000162,'Trajectory locked.',11347,1,0,0,'doomwalker SAY_OVERRUN_1'),
(-1000163,'Engage maximum speed.',11348,1,0,0,'doomwalker SAY_OVERRUN_2'),
(-1000164,'Threat level zero.',11349,1,0,0,'doomwalker SAY_SLAY_1'),
(-1000165,'Directive accomplished.',11350,1,0,0,'doomwalker SAY_SLAY_2'),
(-1000166,'Target exterminated.',11351,1,0,0,'doomwalker SAY_SLAY_3'),
(-1000167,'System failure in five, f-o-u-r...',11352,1,0,0,'doomwalker SAY_DEATH'),

(-1000168,'Who dares awaken Aquementas?',0,1,0,0,'aquementas AGGRO_YELL_AQUE'),

(-1000169,'Muahahahaha! You fool! You\'ve released me from my banishment in the interstices between space and time!',0,1,0,0,'nether_drake SAY_NIHIL_1'),
(-1000170,'All of Draenor shall quick beneath my feet! I will destroy this world and reshape it in my image!',0,1,0,0,'nether_drake SAY_NIHIL_2'),
(-1000171,'Where shall I begin? I cannot bother myself with a worm such as yourself. There is a world to be conquered!',0,1,0,0,'nether_drake SAY_NIHIL_3'),
(-1000172,'No doubt the fools that banished me are long dead. I shall take wing survey my demense. Pray to whatever gods you hold dear that we do not meet again.',0,1,0,0,'nether_drake SAY_NIHIL_4'),
(-1000173,'NOOOOooooooo!',0,1,0,0,'nether_drake SAY_NIHIL_INTERRUPT'),

(-1000174,'Good, $n, you are under the spell\'s influence. I must analyze it quickly, then we can talk.',0,0,0,0,'daranelle SAY_SPELL_INFLUENCE'),

(-1000175,'Thank you, mortal.',0,0,11,0,' SAY_JUST_EATEN'),

(-1000176,'What is this? Where am I? How... How did I... Cursed ethereals! I was on an escort mission out of Shattrath when we were ambushed! I must return to the city at once! Your name will be recorded as a friend of the Lower City, $n.',0,0,0,5,'SAY_LC'),
(-1000177,'Blessed Light! Free of my confines at last... Thank you, hero. A\'dal will be told of your heroics.',0,0,0,5,'SAY_SHAT'),
(-1000178,'At last I am released! Thank you, gentle $r. I must return to the expedition at once! They will know of your deeds. This I vow.',0,0,0,5,'SAY_CE'),
(-1000179,'I will tell the tale of your heroics to Haramad myself! All Consortium will know your name, $n. Thank you, my friend.',0,0,0,5,'SAY_CON'),
(-1000180,'The Keepers of Time thank you for your assistance. The Timeless One shall be pleased with this outcome...',0,0,0,5,'SAY_KT'),
(-1000181,'$R save me! Thank you! My people thank you too!',0,0,0,5,'SAY_SPOR'),
(-1000182,'REUSE ME',0,0,0,0,'REUSE_ME'),
(-1000183,'REUSE ME',0,0,0,0,'REUSE_ME'),

(-1000184,'Daughter!',0,0,7,5,'cowlen SAY_DAUGHTER'),

(-1000185,'There\'s no turning back now, $n. Stay close and watch my back.',0,0,0,1,'demolitionist_legoso SAY_ESCORT_START'),
(-1000186,'There it is! Do you see where the large red crystal is jutting out from the Vector Coil? That\'s where I need to plant the first set of explosives.',0,0,0,25,'demolitionist_legoso SAY_ESCORT_1'),

(-1000187,'Thank you, dear $C, you just saved my life.',0,0,0,0,'npc_redemption_target SAY_HEAL'),

(-1000188,'Deployment sucessful. Trespassers will be neutralized.',0,0,0,0,'converted_sentry SAY_CONVERTED_1'),
(-1000189,'Objective acquired. Initiating security routines.',0,0,0,0,'converted_sentry SAY_CONVERTED_2'),

(-1000190,'In Nagrand, food hunt ogre!',0,0,0,0,' SAY_LUMP_0'),
(-1000191,'You taste good with maybe a little salt and pepper.',0,0,0,0,' SAY_LUMP_1'),
(-1000192,'OK, OK! Lump give up!',0,0,0,0,' SAY_LUMP_DEFEAT'),

(-1000193,'%s looks down at the discarded necklace. In her sadness, the lady incants a glamour, which beckons forth Highborne spirits. The chamber resonates with their ancient song about the Sin\'dorei...',10896,2,1,0,'lady_sylvanas EMOTE_LAMENT_START'),

(-1000194,'I give up! Please don\'t kill me!',0,0,0,0,'unkor SAY_SUBMIT'),

(-1000195,'Thank you again, $N. I\'ll make my way to the road now. When you can, find Terenthis and let him know we escaped.',0,0,0,1,'volcor SAY_ESCAPE'),

(-1000196,'Belore...',0,0,1,0,'lady_sylvanas SAY_LAMENT_END'),
(-1000197,'%s kneels down and pick up the amulet.',0,2,1,16,'lady_sylvanas EMOTE_LAMENT_END'),

(-1000198,'Taste blade, mongrel!',0,0,0,0,'SAY_GUARD_SIL_AGGRO1'),
(-1000199,'Please tell me that you didn\'t just do what I think you just did. Please tell me that I\'m not going to have to hurt you...',0,0,0,0,'SAY_GUARD_SIL_AGGRO2'),
(-1000200,'As if we don\'t have enough problems, you go and create more!',0,0,0,0,'SAY_GUARD_SIL_AGGRO3'),

(-1000201,'I\'m saved! Thank you, doctor!',0,0,0,0,'injured_patient SAY_DOC1'),
(-1000202,'HOORAY! I AM SAVED!',0,0,0,0,'injured_patient SAY_DOC2'),
(-1000203,'Sweet, sweet embrace... take me...',0,0,0,0,'injured_patient SAY_DOC3'),

(-1000204,'%s looks up at you quizzically. Maybe you should inspect it?',0,2,0,0,'cluck EMOTE_A_HELLO'),
(-1000205,'%s looks at you unexpectadly.',0,2,0,0,'cluck EMOTE_H_HELLO'),
(-1000206,'%s starts pecking at the feed.',0,2,0,0,'cluck EMOTE_CLUCK_TEXT2'),

(-1000207,'Mmm. Me thirsty!',0,0,0,0,'bladespire ogre SAY_BREW_2'),
(-1000208,'Ohh, look! Bloodmaul Brew! Mmmm...',0,0,0,0,'bladespire ogre SAY_BREW_3'),

(-1000209,'Very well. Let\'s see what you have to show me, $N.',0,0,1,0,'anvilward SAY_ANVIL1'),
(-1000210,'What manner of trick is this, $R? If you seek to ambush me, I warn you I will not go down quietly!',0,0,1,0,'anvilward SAY_ANVIL2'),

(-1000211,'Warning! %s emergency shutdown process initiated by $N. Shutdown will complete in two minutes.',0,2,0,0,'manaforge_control EMOTE_START'),
(-1000212,'Emergency shutdown will complete in one minute.',0,2,0,0,'manaforge_control EMOTE_60'),
(-1000213,'Emergency shutdown will complete in thirty seconds.',0,2,0,0,'manaforge_control EMOTE_30'),
(-1000214,'Emergency shutdown will complete in ten seconds.',0,2,0,0,'manaforge_control EMOTE_10'),
(-1000215,'Emergency shutdown complete.',0,2,0,0,'manaforge_control EMOTE_COMPLETE'),
(-1000216,'Emergency shutdown aborted.',0,2,0,0,'manaforge_control EMOTE_ABORT'),

(-1000217,'Greetings, $N. I will guide you through the cavern. Please try and keep up.',0,4,0,0,'WHISPER_CUSTODIAN_1'),
(-1000218,'We do not know if the Caverns of Time have always been accessible to mortals. Truly, it is impossible to tell as the Timeless One is in perpetual motion, changing our timeways as he sees fit. What you see now may very well not exist tomorrow. You may wake up and have no memory of this place.',0,4,0,0,'WHISPER_CUSTODIAN_2'),
(-1000219,'It is strange, I know... Most mortals cannot actually comprehend what they see here, as often, what they see is not anchored within their own perception of reality.',0,4,0,0,'WHISPER_CUSTODIAN_3'),
(-1000220,'Follow me, please.',0,4,0,0,'WHISPER_CUSTODIAN_4'),
(-1000221,'There are only two truths to be found here: First, that time is chaotic, always in flux, and completely malleable and second, perception does not dictate reality.',0,4,0,0,'WHISPER_CUSTODIAN_5'),
(-1000222,'As custodians of time, we watch over and care for Nozdormu\'s realm. The master is away at the moment, which means that attempts are being made to dramatically alter time. The master never meddles in the affairs of mortals but instead corrects the alterations made to time by others. He is reactionary in this regard.',0,4,0,0,'WHISPER_CUSTODIAN_6'),
(-1000223,'For normal maintenance of time, the Keepers of Time are sufficient caretakers. We are able to deal with most ordinary disturbances. I speak of little things, such as rogue mages changing something in the past to elevate their status or wealth in the present.',0,4,0,0,'WHISPER_CUSTODIAN_7'),
(-1000224,'These tunnels that you see are called timeways. They are infinite in number. The ones that currently exist in your reality are what the master has deemed as \'trouble spots.\' These trouble spots may differ completely in theme but they always share a cause. That is, their existence is a result of the same temporal disturbance. Remember that should you venture inside one...',0,4,0,0,'WHISPER_CUSTODIAN_8'),
(-1000225,'This timeway is in great disarray! We have agents inside right now attempting to restore order. What information I have indicates that Thrall\'s freedom is in jeopardy. A malevolent organization known as the Infinite Dragonflight is trying to prevent his escape. I fear without outside assistance, all will be lost.',0,4,0,0,'WHISPER_CUSTODIAN_9'),
(-1000226,'We have very little information on this timeway. Sa\'at has been dispatched and is currently inside. The data we have gathered from his correspondence is that the Infinite Dragonflight are once again attempting to alter time. Could it be that the opening of the Dark Portal is being targeted for sabotage? Let us hope not...',0,4,0,0,'WHISPER_CUSTODIAN_10'),
(-1000227,'This timeway is currently collapsing. What that may hold for the past, present and future is currently unknown...',0,4,0,0,'WHISPER_CUSTODIAN_11'),
(-1000228,'The timeways are currently ranked in order from least catastrophic to most catastrophic. Note that they are all classified as catastrophic, meaning that any single one of these timeways collapsing would mean that your world would end. We only classify them in such a way so that the heroes and adventurers that are sent here know which timeway best suits their abilities.',0,4,0,0,'WHISPER_CUSTODIAN_12'),
(-1000229,'All we know of this timeway is that it leads to Mount Hyjal. The Infinite Dragonflight have gone to great lengths to prevent our involvement. We know next to nothing, mortal. Soridormi is currently attempting to break through the timeway\'s defenses but has thus far been unsuccessful. You might be our only hope of breaking through and resolving the conflict.',0,4,0,0,'WHISPER_CUSTODIAN_13'),
(-1000230,'Our time is at an end $N. I would wish you luck, if such a thing existed.',0,4,0,0,'WHISPER_CUSTODIAN_14'),

(-1000231,'Ah, $GPriest:Priestess; you came along just in time. I appreciate it.',0,0,0,20,'garments SAY_COMMON_HEALED'),
(-1000232,'Thank you! Thank you, $GPriest:Priestess;. Now I can take on those gnolls with your power to back me!',0,0,1,4,'garments SAY_DG_KEL_THANKS'),
(-1000233,'Farewell to you, and may shadow always protect you!',0,0,1,3,'garments SAY_DG_KEL_GOODBYE'),

(-1000234,'Follow me, stranger. This won\'t take long.',0,0,0,0,'SAY_KHAD_SERV_0'),
(-1000235,'Shattrath was once the draenei capital of this world. Its name means "dwelling of light."',0,4,0,0,'SAY_KHAD_SERV_1'),
(-1000236,'When the Burning Legion turned the orcs against the draenei, the fiercest battle was fought here. The draenei fought tooth and nail, but in the end the city fell.',0,4,0,0,'SAY_KHAD_SERV_2'),
(-1000237,'The city was left in ruins and darkness... until the Sha\'tar arrived.',0,4,0,0,'SAY_KHAD_SERV_3'),
(-1000238,'Let us go into the Lower City. I will warn you that as one of the only safe havens in Outland, Shattrath has attracted droves of refugees from all wars, current and past.',0,4,0,0,'SAY_KHAD_SERV_4'),
(-1000239,'The Sha\'tar, or "born from light" are the naaru that came to Outland to fight the demons of the Burning Legion.',0,4,0,0,'SAY_KHAD_SERV_5'),
(-1000240,'They were drawn to the ruins of Shattrath City where a small remnant of the draenei priesthood conducted its rites inside a ruined temple on this very spot.',0,4,0,0,'SAY_KHAD_SERV_6'),
(-1000241,'The priesthood, known as the Aldor, quickly regained its strength as word spread that the naaru had returned and reconstruction soon began. The ruined temple is now used as an infirmary for injured refugees.',0,4,0,0,'SAY_KHAD_SERV_7'),
(-1000242,'It wouldn\'t be long, however, before the city came under attack once again. This time, the attack came from Illidan\'s armies. A large regiment of blood elves had been sent by Illidan\'s ally, Kael\'thas Sunstrider, to lay waste to the city.',0,4,0,0,'SAY_KHAD_SERV_8'),
(-1000243,'As the regiment of blood elves crossed this very bridge, the Aldor\'s exarchs and vindicators lined up to defend the Terrace of Light. But then the unexpected happened.',0,4,0,0,'SAY_KHAD_SERV_9'),
(-1000244,'The blood elves laid down their weapons in front of the city\'s defenders; their leader, a blood elf elder known as Voren\'thal, stormed into the Terrace of Light and demanded to speak to A\'dal.',0,4,0,0,'SAY_KHAD_SERV_10'),
(-1000245,'As the naaru approached him, Voren\'thal kneeled before him and uttered the following words: "I\'ve seen you in a vision, naaru. My race\'s only hope for survival lies with you. My followers and I are here to serve you."',0,4,0,0,'SAY_KHAD_SERV_11'),
(-1000246,'The defection of Voren\'thal and his followers was the largest loss ever incurred by Kael\'s forces. And these weren\'t just any blood elves. Many of the best and brightest amongst Kael\'s scholars and magisters had been swayed by Voren\'thal\'s influence.',0,4,0,0,'SAY_KHAD_SERV_12'),
(-1000247,'The naaru accepted the defectors, who would become known as the Scryers; their dwelling lies in the platform above. Only those initiated with the Scryers are allowed there.',0,4,0,0,'SAY_KHAD_SERV_13'),
(-1000248,'The Aldor are followers of the Light and forgiveness and redemption are values they understand. However, they found hard to forget the deeds of the blood elves while under Kael\'s command.',0,4,0,0,'SAY_KHAD_SERV_14'),
(-1000249,'Many of the priesthood had been slain by the same magisters who now vowed to serve the naaru. They were not happy to share the city with their former enemies.',0,4,0,0,'SAY_KHAD_SERV_15'),
(-1000250,'The Aldor\'s most holy temple and its surrounding dwellings lie on the terrace above. As a holy site, only the initiated are welcome inside.',0,4,0,0,'SAY_KHAD_SERV_16'),
(-1000251,'The attacks against Shattrath continued, but the city did not fall\, as you can see. On the contrary, the naaru known as Xi\'ri led a successful incursion into Shadowmoon Valley - Illidan\'s doorstep.',0,4,0,0,'SAY_KHAD_SERV_17'),
(-1000252,'There he continues to wage war on Illidan with the assistance of the Aldor and the Scryers. The two factions have not given up on their old feuds, though.',0,4,0,0,'SAY_KHAD_SERV_18'),
(-1000253,'Such is their animosity that they vie for the honor of being sent to assist the naaru there. Each day, that decision is made here by A\'dal. The armies gather here to receive A\'dal\'s blessing before heading to Shadowmoon.',0,4,0,0,'SAY_KHAD_SERV_19'),
(-1000254,'Khadgar should be ready to see you again. Just remember that to serve the Sha\'tar you will most likely have to ally with the Aldor or the Scryers. And seeking the favor of one group will cause the others\' dislike.',0,4,0,0,'SAY_KHAD_SERV_20'),
(-1000255,'Good luck stranger, and welcome to Shattrath City.',0,4,0,0,'SAY_KHAD_SERV_21'),

(-1000256,'Thank you! Thank you, $GPriest:Priestess;. Now I can take on those murlocs with the Light on my side!',0,0,7,4,'garments SAY_ROBERTS_THANKS'),
(-1000257,'Farewell to you, and may the Light be with you always.',0,0,7,3,'garments SAY_ROBERTS_GOODBYE'),
(-1000258,'Thank you! Thank you, $GPriest:Priestess;. Now I can take on those humans with your power to back me!',0,0,1,4,'garments SAY_KORJA_THANKS'),
(-1000259,'Farewell to you, and may our ancestors be with you always!',0,0,1,3,'garments SAY_KORJA_GOODBYE'),
(-1000260,'Thank you! Thank you, $GPriest:Priestess;. Now I can take on those wendigo with the Light on my side!',0,0,7,4,'garments SAY_DOLF_THANKS'),
(-1000261,'Farewell to you, and may the Light be with you always.',0,0,7,3,'garments SAY_DOLF_GOODBYE'),
(-1000262,'Thank you! Thank you, $GPriest:Priestess;. Now I can take on those corrupt timberlings with Elune\'s power behind me!',0,0,2,4,'garments SAY_SHAYA_THANKS'),
(-1000263,'Farewell to you, and may Elune be with you always.',0,0,2,3,'garments SAY_SHAYA_GOODBYE'),

(-1000264,'Ok, $N. Follow me to the cave where I\'ll attempt to harness the power of the rune stone into these goggles.',0,0,0,1,'phizzlethorpe SAY_PROGRESS_1'),
(-1000265,'I discovered this cave on our first day here. I believe the energy in the stone can be used to our advantage.',0,0,0,1,'phizzlethorpe SAY_PROGRESS_2'),
(-1000266,'I\'ll begin drawing energy from the stone. Your job, $N, is to defend me. This place is cursed... trust me.',0,0,0,1,'phizzlethorpe SAY_PROGRESS_3'),
(-1000267,'%s begins tinkering with the goggles before the stone.',0,2,0,0,'phizzlethorpe EMOTE_PROGRESS_4'),
(-1000268,'Help!!! Get these things off me so I can get my work done!',0,0,0,0,'phizzlethorpe SAY_AGGRO'),
(-1000269,'Almost done! Just a little longer!',0,0,0,1,'phizzlethorpe SAY_PROGRESS_5'),
(-1000270,'I\'ve done it! I have harnessed the power of the stone into the goggles! Let\'s get out of here!',0,0,0,1,'phizzlethorpe SAY_PROGRESS_6'),
(-1000271,'Phew! Glad to be back from that creepy cave.',0,0,0,1,'phizzlethorpe SAY_PROGRESS_7'),
(-1000272,'%s hands one glowing goggles over to Doctor Draxlegauge.',0,2,0,0,'phizzlethorpe EMOTE_PROGRESS_8'),
(-1000273,'Doctor Draxlegauge will give you further instructions, $N. Many thanks for your help!',0,0,0,1,'phizzlethorpe SAY_PROGRESS_9'),

(-1000274,'Time to teach you a lesson in manners, little $Gboy:girl;!',0,0,0,5,'larry SAY_START'),
(-1000275,'Now I\'m gonna give you to the count of \'3\' to get out of here before I sick the dogs on you.',0,0,0,1,'larry SAY_COUNT'),
(-1000276,'1...',0,0,0,0,'larry SAY_COUNT_1'),
(-1000277,'2...',0,0,0,0,'larry SAY_COUNT_2'),
(-1000278,'Time to meet your maker!',0,0,0,0,'larry SAY_ATTACK_5'),
(-1000279,'Alright, we give up! Don\'t hurt us!',0,0,0,20,'larry SAY_GIVEUP'),

(-1000280,'A shadowy, sinister presence has invaded the Emerald Dream. Its power is poised to spill over into our world, $N. We must oppose it! That\'s why I cannot accompany you in person.',0,0,0,1,'clintar SAY_START'),
(-1000281,'The Emerald Dream will never be yours!',0,0,0,0,'clintar SAY_AGGRO_1'),
(-1000282,'Begone from this place!',0,0,0,0,'clintar SAY_AGGRO_2'),
(-1000283,'That\'s the first relic, but there are still two more. Follow me, $N.',0,0,0,0,'clintar SAY_RELIC1'),
(-1000284,'I\'ve recovered the second relic. Take a moment to rest, and then we\'ll continue to the last reliquary.',0,0,0,0,'clintar SAY_RELIC2'),
(-1000285,'We have all three of the relics, but my energy is rapidly fading. We must make our way back to Dreamwarden Lurosa! He will let you know what to do next.',0,0,0,0,'clintar SAY_RELIC3'),
(-1000286,'Lurosa, I am entrusting the Relics of Aviana to $N, who will take them to Morthis Whisperwing. I must return completely to the Emerald Dream now. Do not let $N fail!',0,0,0,1,'clintar SAY_END'),

(-1000287,'Emergency power activated! Initializing ambulanory motor! CLUCK!',0,0,0,0,'oox SAY_OOX_START'),
(-1000288,'Physical threat detected! Evasive action! CLUCK!',0,0,0,0,'oox SAY_OOX_AGGRO1'),
(-1000289,'Threat analyzed! Activating combat plan beta! CLUCK!',0,0,0,0,'oox SAY_OOX_AGGRO2'),
(-1000290,'CLUCK! Sensors detect spatial anomaly - danger imminent! CLUCK!',0,0,0,0,'oox SAY_OOX_AMBUSH'),
(-1000291,'No one challanges the Wastewander nomads - not even robotic chickens! ATTACK!',0,0,0,0,'oox SAY_OOX17_AMBUSH_REPLY'),
(-1000292,'Cloaking systems online! CLUCK! Engaging cloak for transport to Booty Bay!',0,0,0,0,'oox SAY_OOX_END'),

(-1000293,'To the house! Stay close to me, no matter what! I have my gun and ammo there!',0,0,7,0,'stilwell SAY_DS_START'),
(-1000294,'We showed that one!',0,0,7,0,'stilwell SAY_DS_DOWN_1'),
(-1000295,'One more down!',0,0,7,0,'stilwell SAY_DS_DOWN_2'),
(-1000296,'We\'ve done it! We won!',0,0,7,0,'stilwell SAY_DS_DOWN_3'),
(-1000297,'Meet me down by the orchard--I just need to put my gun away.',0,0,7,0,'stilwell SAY_DS_PROLOGUE'),

(-1000298,'Alright, alright I think I can figure out how to operate this thing...',0,0,0,393,'wizzlecrank SAY_START'),
(-1000299,'Arrrgh! This isn\'t right!',0,0,0,0,'wizzlecrank SAY_STARTUP1'),
(-1000300,'Okay, I think I\'ve got it, now. Follow me, $n!',0,0,0,1,'wizzlecrank SAY_STARTUP2'),
(-1000301,'There\'s the stolen shredder! Stop it or Lugwizzle will have our hides!',0,1,0,0,'wizzlecrank SAY_MERCENARY'),
(-1000302,'Looks like we\'re out of woods, eh? Wonder what this does...',0,0,0,0,'wizzlecrank SAY_PROGRESS_1'),
(-1000303,'Come on, don\'t break down on me now!',0,0,0,393,'wizzlecrank SAY_PROGRESS_2'),
(-1000304,'That was a close one! Well, let\'s get going, it\'s still a ways to Ratchet!',0,0,0,0,'wizzlecrank SAY_PROGRESS_3'),
(-1000305,'Hmm... I don\'t think this blinking red light is a good thing...',0,0,0,0,'wizzlecrank SAY_END'),

(-1000306,'Let\'s get to the others, and keep an eye open for those wolves cutside...',0,0,1,0,'erland SAY_START_1'),
(-1000307,'Be careful, $N. Those wolves like to hide among the trees.',0,0,1,0,'erland SAY_START_2'),
(-1000308,'A $C attacks!',0,0,1,0,'erland SAY_AGGRO_1'),
(-1000309,'Beware! I am under attack!',0,0,1,0,'erland SAY_AGGRO_2'),
(-1000310,'Oh no! A $C is upon us!',0,0,1,0,'erland SAY_AGGRO_3'),
(-1000311,'We\'re almost there!',0,0,1,0,'erland SAY_PROGRESS'),
(-1000312,'We made it! Thanks, $N. I couldn\'t have gotten without you.',0,0,1,0,'erland SAY_END'),
(-1000313,'It\'s good to see you again, Erland. What is your report?',0,0,33,1,'erland SAY_RANE'),
(-1000314,'Masses of wolves are to the east, and whoever lived at Malden\'s Orchard is gone.',0,0,1,1,'erland SAY_RANE_REPLY'),
(-1000315,'If I am excused, then I\'d like to check on Quinn...',0,0,1,1,'erland SAY_CHECK_NEXT'),
(-1000316,'Hello, Quinn. How are you faring?',0,0,1,1,'erland SAY_QUINN'),
(-1000317,'I\'ve been better. Ivar the Foul got the better of me...',0,0,33,1,'erland SAY_QUINN_REPLY'),
(-1000318,'Try to take better care of yourself, Quinn. You were lucky this time.',0,0,1,1,'erland SAY_BYE'),

(-1000319,'Let the trial begin, Bloodwrath, attack!',0,1,1,0,'kelerun SayId1'),
(-1000320,'Champion Lightrend, make me proud!',0,1,1,0,'kelerun SayId2'),
(-1000321,'Show this upstart how a real Blood Knight fights, Swiftblade!',0,1,1,0,'kelerun SayId3'),
(-1000322,'Show $n the meaning of pain, Sunstriker!',0,1,1,0,'kelerun SayId4'),

(-1000323,'Mist! I feared I would never see you again! Yes, I am well, do not worry for me. You must rest and recover your health.',0,0,7,0,'mist SAY_AT_HOME'),
(-1000324,'%s growls in acknowledgement before straightening and making her way off into the forest.',0,2,0,0,'mist EMOTE_AT_HOME'),

(-1000325,'"Threshwackonator First Mate unit prepared to follow"',0,2,0,0,'threshwackonator EMOTE_START'),
(-1000326,'YARRR! Swabie, what have ye done?! He\'s gone mad! Baton him down the hatches! Hoist the mast! ARRRR! Every man for hi\'self!',0,0,7,0,'threshwackonator SAY_AT_CLOSE'),

(-1000327,'Ok, $n, let\'s go find where I left that mysterious fossil. Follow me!',0,0,7,0,'remtravel SAY_REM_START'),
(-1000328,'Now where did I put that mysterious fossil? Ah, maybe up there...',0,0,7,0,'remtravel SAY_REM_RAMP1_1'),
(-1000329,'Hrm, nothing up here.',0,0,7,0,'remtravel SAY_REM_RAMP1_2'),
(-1000330,'No mysterious fossil here... Ah, but my copy of Green Hills of Stranglethorn. What a good book!',0,0,7,0,'remtravel SAY_REM_BOOK'),
(-1000331,'I bet you I left it in the tent!',0,0,7,0,'remtravel SAY_REM_TENT1_1'),
(-1000332,'Oh wait, that\'s Hollee\'s tent... and it\'s empty.',0,0,7,0,'remtravel SAY_REM_TENT1_2'),
(-1000333,'Interesting... I hadn\'t noticed this earlier...',0,0,7,0,'remtravel SAY_REM_MOSS'),
(-1000334,'%s inspects the ancient, mossy stone.',0,2,7,0,'remtravel EMOTE_REM_MOSS'),
(-1000335,'Oh wait! I\'m supposed to be looking for that mysterious fossil!',0,0,7,0,'remtravel SAY_REM_MOSS_PROGRESS'),
(-1000336,'Nope. didn\'t leave the fossil back here!',0,0,7,0,'remtravel SAY_REM_PROGRESS'),
(-1000337,'Ah. I remember now! I gave the mysterious fossil to Hollee! Check with her.',0,0,7,0,'remtravel SAY_REM_REMEMBER'),
(-1000338,'%s goes back to work, oblivious to everything around him.',0,2,7,0,'remtravel EMOTE_REM_END'),
(-1000339,'Something tells me this $r wants the mysterious fossil too. Help!',0,0,7,0,'remtravel SAY_REM_AGGRO'),

(-1000340,'%s howls in delight at the sight of his lunch!',0,2,0,0,'kyle EMOTE_SEE_LUNCH'),
(-1000341,'%s eats his lunch.',0,2,0,0,'kyle EMOTE_EAT_LUNCH'),
(-1000342,'%s thanks you with a special dance.',0,2,0,0,'kyle EMOTE_DANCE'),

-- REUSE 343-347

(-1000348,'Ah...the wondrous sound of kodos. I love the way they make the ground shake... inspect the beast for me.',0,0,0,0,'kodo round SAY_SMEED_HOME_1'),
(-1000349,'Hey, look out with that kodo! You had better inspect that beast before i give you credit!',0,0,0,0,'kodo round SAY_SMEED_HOME_2'),
(-1000350,'That kodo sure is a beauty. Wait a minute, where are my bifocals? Perhaps you should inspect the beast for me.',0,0,0,0,'kodo round SAY_SMEED_HOME_3'),

(-1000351,'You, there! Hand over that moonstone and nobody gets hurt!',0,1,0,0,'sprysprocket SAY_START'),
(-1000352,'%s takes the Southfury moonstone and escapes into the river. Follow her!',0,3,0,0,'sprysprocket EMOTE_START'),
(-1000353,'Just chill!',0,4,0,0,'sprysprocket SAY_WHISPER_CHILL'),
(-1000354,'Stupid grenade picked a fine time to backfire! So much for high quality goblin engineering!',0,1,0,0,'sprysprocket SAY_GRENADE_FAIL'),
(-1000355,'All right, you win! I surrender! Just don\'t hurt me!',0,1,0,0,'sprysprocket SAY_END'),

(-1000356,'Okay, okay... gimme a minute to rest now. You gone and beat me up good.',0,0,1,14,'calvin SAY_COMPLETE'),

(-1000357,'Let\'s go before they find out I\'m free!',0,0,0,1,'KAYA_SAY_START'),
(-1000358,'Look out! We\'re under attack!',0,0,0,0,'KAYA_AMBUSH'),
(-1000359,'Thank you for helping me. I know my way back from here.',0,0,0,0,'KAYA_END'),

(-1000360,'The strands of LIFE have been severed! The Dreamers must be avenged!',0,1,0,0,' ysondre SAY_AGGRO'),
(-1000361,'Come forth, ye Dreamers - and claim your vengeance!',0,1,0,0,' ysondre SAY_SUMMONDRUIDS'),

(-1000362,'Let\'s go $N. I am ready to reach Whitereach Post.',0,0,1,0,'paoka SAY_START'),
(-1000363,'Now this looks familiar. If we keep heading east, I think we can... Ahh, Wyvern on the attack!',0,0,1,0,'paoka SAY_WYVERN'),
(-1000364,'Thanks a bunch... I can find my way back to Whitereach Post from here. Be sure to talk with Motega Firemane; perhaps you can keep him from sending me home.',0,0,1,0,'paoka SAY_COMPLETE'),

(-1000365,'Be on guard... Arnak has some strange power over the Grimtotem... they will not be happy to see me escape.',0,0,1,0,'lakota SAY_LAKO_START'),
(-1000366,'Look out, the Grimtotem are upon us!',0,0,1,0,'lakota SAY_LAKO_LOOK_OUT'),
(-1000367,'Here they come.',0,0,1,0,'lakota SAY_LAKO_HERE_COME'),
(-1000368,'More Grimtotems are coming this way!',0,0,1,0,'lakota SAY_LAKO_MORE'),
(-1000369,'Finally, free at last... I must be going now, thanks for helping me escape. I can get back to Freewind Post by myself.',0,0,1,0,'lakota SAY_LAKO_END'),

(-1000370,'Stay close, $n. I\'ll need all the help I can get to break out of here. Let\'s go!',0,0,1,1,'gilthares SAY_GIL_START'),
(-1000371,'At last! Free from Northwatch Hold! I need a moment to catch my breath...',0,0,1,5,'gilthares SAY_GIL_AT_LAST'),
(-1000372,'Now I feel better. Let\'s get back to Ratchet. Come on, $n.',0,0,1,23,'gilthares SAY_GIL_PROCEED'),
(-1000373,'Looks like the Southsea Freebooters are heavily entrenched on the coast. This could get rough.',0,0,1,25,'gilthares SAY_GIL_FREEBOOTERS'),
(-1000374,'Help! $C attacking!',0,0,1,0,'gilthares SAY_GIL_AGGRO_1'),
(-1000375,'$C heading this way fast! Time for revenge!',0,0,1,0,'gilthares SAY_GIL_AGGRO_2'),
(-1000376,'$C coming right at us!',0,0,1,0,'gilthares SAY_GIL_AGGRO_3'),
(-1000377,'Get this $C off of me!',0,0,1,0,'gilthares SAY_GIL_AGGRO_4'),
(-1000378,'Almost back to Ratchet! Let\'s keep up the pace...',0,0,1,0,'gilthares SAY_GIL_ALMOST'),
(-1000379,'Ah, the sweet salt air of Ratchet.',0,0,1,0,'gilthares SAY_GIL_SWEET'),
(-1000380,'Captain Brightsun, $N here has freed me! $N, I am certain the Captain will reward your bravery.',0,0,1,66,'gilthares SAY_GIL_FREED'),

(-1000381,'I sense the tortured spirits, $n. They are this way, come quickly!',0,0,0,1,'wilda SAY_WIL_START'),
(-1000382,'Watch out!',0,0,0,0,'wilda SAY_WIL_AGGRO1'),
(-1000383,'Naga attackers! Defend yourself!',0,0,0,0,'wilda SAY_WIL_AGGRO2'),
(-1000384,'Grant me protection, $n. I must break through their foul magic!',0,0,0,0,'wilda SAY_WIL_PROGRESS1'),
(-1000385,'The naga of Coilskar are exceptionally cruel to their prisoners. It is a miracle that I survived inside that watery prison for as long as I did. Earthmother be praised.',0,0,0,0,'wilda SAY_WIL_PROGRESS2'),
(-1000386,'Now we must find the exit.',0,0,0,1,'wilda SAY_WIL_FIND_EXIT'),
(-1000387,'Lady Vashj must answer for these atrocities. She must be brought to justice!',0,0,0,0,'wilda SAY_WIL_PROGRESS4'),
(-1000388,'The tumultuous nature of the great waterways of Azeroth and Draenor are a direct result of tormented water spirits.',0,0,0,0,'wilda SAY_WIL_PROGRESS5'),
(-1000389,'It shouldn\'t be much further, $n. The exit is just up ahead.',0,0,0,1,'wilda SAY_WIL_JUST_AHEAD'),
(-1000390,'Thank you, $n. Please return to my brethren at the Altar of Damnation, near the Hand of Gul\'dan, and tell them that Wilda is safe. May the Earthmother watch over you...',0,0,0,3,'wilda SAY_WIL_END'),

(-1000391,'I\'m Thirsty.',0,0,0,0,'tooga SAY_TOOG_THIRST'),
(-1000392,'Torta must be so worried.',0,0,0,0,'tooga SAY_TOOG_WORRIED'),
(-1000393,'Torta, my love! I have returned at long last.',0,0,0,0,'tooga SAY_TOOG_POST_1'),
(-1000394,'You have any idea how long I\'ve been waiting here? And where\'s dinner? All that time gone and nothing to show for it?',0,0,0,0,'tooga SAY_TORT_POST_2'),
(-1000395,'My dearest Torta. I have been gone for so long. Finally we are reunited. At long last our love can blossom again.',0,0,0,0,'tooga SAY_TOOG_POST_3'),
(-1000396,'Enough with the rambling. I am starving! Now, get your dusty shell into that ocean and bring momma some grub.',0,0,0,0,'tooga SAY_TORT_POST_4'),
(-1000397,'Yes Torta. Whatever your heart desires...',0,0,0,0,'tooga SAY_TOOG_POST_5'),
(-1000398,'And try not to get lost this time...',0,0,0,0,'tooga SAY_TORT_POST_6'),

(-1000399,'Peace is but a fleeting dream! Let the NIGHTMARE reign!',0,1,0,0,'taerar SAY_AGGRO'),
(-1000400,'Children of Madness - I release you upon this world!',0,1,0,0,'taerar SAY_SUMMONSHADE'),

(-1000401,'Hope is a DISEASE of the soul! This land shall wither and die!',0,1,0,0,'emeriss SAY_AGGRO'),
(-1000402,'Taste your world\'s corruption!',0,1,0,0,'emeriss SAY_CASTCORRUPTION'),

(-1000403,'Rin\'ji is free!',0,0,0,0,'SAY_RIN_FREE'),
(-1000404,'Attack my sisters! The troll must not escape!',0,0,0,0,'SAY_RIN_BY_OUTRUNNER'),
(-1000405,'Rin\'ji needs help!',0,0,1,0,'SAY_RIN_HELP_1'),
(-1000406,'Rin\'ji is being attacked!',0,0,1,0,'SAY_RIN_HELP_2'),
(-1000407,'Rin\'ji can see road now, $n. Rin\'ji knows the way home.',0,0,1,0,'SAY_RIN_COMPLETE'),
(-1000408,'Rin\'ji will tell you secret now... $n, should go to the Overlook Cliffs. Rin\'ji hid something on island  there',0,0,1,0,'SAY_RIN_PROGRESS_1'),
(-1000409,'You find it, you keep it! Don\'t tell no one that Rin\'ji talked to you!',0,0,1,0,'SAY_RIN_PROGRESS_2'),

(-1000410,'Here they come! Defend yourself!',0,0,1,5,'kanati SAY_KAN_START'),

-- REUSE -1000411 TO -1000414
(-1000415,'%s, too injured, gives up the chase.',0,2,0,0,'hendel EMOTE_SURRENDER'),

(-1000416,'Well, I\'m not sure how far I\'ll make it in this state... I\'m feeling kind of faint...',0,0,0,0,'ringo SAY_RIN_START_1'),
(-1000417,'Remember, if I faint again, the water that Spraggle gave you will revive me.',0,0,0,0,'ringo SAY_RIN_START_2'),
(-1000418,'The heat... I can\'t take it...',0,0,0,0,'ringo SAY_FAINT_1'),
(-1000419,'Maybe... you could carry me?',0,0,0,0,'ringo SAY_FAINT_2'),
(-1000420,'Uuuuuuggggghhhhh....',0,0,0,0,'ringo SAY_FAINT_3'),
(-1000421,'I\'m not feeling so well...',0,0,0,0,'ringo SAY_FAINT_4'),
(-1000422,'Where... Where am I?',0,0,0,0,'ringo SAY_WAKE_1'),
(-1000423,'I am feeling a little better now, thank you.',0,0,0,0,'ringo SAY_WAKE_2'),
(-1000424,'Yes, I must go on.',0,0,0,0,'ringo SAY_WAKE_3'),
(-1000425,'How am I feeling? Quite soaked, thank you.',0,0,0,0,'ringo SAY_WAKE_4'),
(-1000426,'Spraggle! I didn\'t think I\'d make it back!',0,0,0,0,'ringo SAY_RIN_END_1'),
(-1000427,'Ringo! You\'re okay!',0,0,0,0,'ringo SAY_SPR_END_2'),
(-1000428,'Oh... I\'m feeling faint...',0,0,0,0,'ringo SAY_RIN_END_3'),
(-1000429,'%s collapses onto the ground.',0,2,0,0,'ringo EMOTE_RIN_END_4'),
(-1000430,'%s stands up after a short pause.',0,2,0,0,'ringo EMOTE_RIN_END_5'),
(-1000431,'Ugh.',0,0,0,0,'ringo SAY_RIN_END_6'),
(-1000432,'Ringo? Wake up! Don\'t worry, I\'ll take care of you.',0,0,0,0,'ringo SAY_SPR_END_7'),
(-1000433,'%s fades away after a long pause.',0,2,0,0,'ringo EMOTE_RIN_END_8'),

(-1000434,'Liladris has been waiting for me at Maestra\'s Post, so we should make haste, $N.',0,0,0,0,'kerlonian SAY_KER_START'),
(-1000435,'%s looks very sleepy...',0,2,0,0,'kerlonian EMOTE_KER_SLEEP_1'),
(-1000436,'%s suddenly falls asleep',0,2,0,0,'kerlonian EMOTE_KER_SLEEP_2'),
(-1000437,'%s begins to drift off...',0,2,0,0,'kerlonian EMOTE_KER_SLEEP_3'),
(-1000438,'This looks like the perfect place for a nap...',0,0,0,0,'kerlonian SAY_KER_SLEEP_1'),
(-1000439,'Yaaaaawwwwwnnnn...',0,0,0,0,'kerlonian SAY_KER_SLEEP_2'),
(-1000440,'Oh, I am so tired...',0,0,0,0,'kerlonian SAY_KER_SLEEP_3'),
(-1000441,'You don\'t mind if I stop here for a moment, do you?',0,0,0,0,'kerlonian SAY_KER_SLEEP_4'),
(-1000442,'Be on the alert! The Blackwood furbolgs are numerous in the area...',0,0,0,0,'kerlonian SAY_KER_ALERT_1'),
(-1000443,'It\'s quiet... Too quiet...',0,0,0,0,'kerlonian SAY_KER_ALERT_2'),
(-1000444,'Oh, I can see Liladris from here... Tell her I\'m here, won\'t you?',0,0,0,0,'kerlonian SAY_KER_END'),
(-1000445,'%s wakes up!',0,2,0,0,'kerlonian EMOTE_KER_AWAKEN'),

(-1000446,'A-Me good. Good, A-Me. Follow... follow A-Me. Home. A-Me go home.',0,0,0,0,'ame01 SAY_AME_START'),
(-1000447,'Good... good, A-Me. A-Me good. Home. Find home.',0,0,0,0,'ame01 SAY_AME_PROGRESS'),
(-1000448,'A-Me home! A-Me good! Good A-Me. Home. Home. Home.',0,0,0,0,'ame01 SAY_AME_END'),
(-1000449,'$c, no hurt A-Me. A-Me good.',0,0,0,0,'ame01 SAY_AME_AGGRO1'),
(-1000450,'Danger. Danger! $c try hurt A-Me.',0,0,0,0,'ame01 SAY_AME_AGGRO2'),
(-1000451,'Bad, $c. $c, bad!',0,0,0,0,'ame01 SAY_AME_AGGRO3'),

(-1000452,'I noticed some fire on that island over there. A human, too. Let\'s go check it out, $n.',0,0,1,0,'ogron SAY_OGR_START'),
(-1000453,'That\'s Reethe alright. Let\'s go see what he has to say, yeah?',0,0,1,1,'ogron SAY_OGR_SPOT'),
(-1000454,'W-what do you want? Just leave me alone...',0,0,0,6,'ogron SAY_OGR_RET_WHAT'),
(-1000455,'I swear. I didn\'t steal anything from you! Here, take some of my supplies, just go away!',0,0,0,27,'ogron SAY_OGR_RET_SWEAR'),
(-1000456,'Just tell us what you know about the Shady Rest Inn, and I won\'t bash your skull in.',0,0,1,0,'ogron SAY_OGR_REPLY_RET'),
(-1000457,'I... Well, I may of taken a little thing or two from the inn... but what would an ogre care about that?',0,0,0,6,'ogron SAY_OGR_RET_TAKEN'),
(-1000458,'Look here, if you don\'t tell me about the fire--',0,0,1,0,'ogron SAY_OGR_TELL_FIRE'),
(-1000459,'Not one step closer, ogre!',0,0,0,27,'ogron SAY_OGR_RET_NOCLOSER'),
(-1000460,'And I don\'t know anything about this fire of yours...',0,0,0,0,'ogron SAY_OGR_RET_NOFIRE'),
(-1000461,'What was that? Did you hear something?',0,0,0,0,'ogron SAY_OGR_RET_HEAR'),
(-1000462,'Paval Reethe! Found you at last. And consorting with ogres now? No fear, even deserters and traitors are afforded some mercy.',0,0,0,0,'ogron SAY_OGR_CAL_FOUND'),
(-1000463,'Private, show Lieutenant Reethe some mercy.',0,0,0,29,'ogron SAY_OGR_CAL_MERCY'),
(-1000464,'Gladly, sir.',0,0,0,0,'ogron SAY_OGR_HALL_GLAD'),
(-1000465,'%s staggers backwards as the arrow lodges itself deeply in his chest.',0,2,0,0,'ogron EMOTE_OGR_RET_ARROW'),
(-1000466,'Ugh... Hallan, didn\'t think you had it in you...',0,0,0,34,'ogron SAY_OGR_RET_ARROW'),
(-1000467,'Now, let\'s clean up the rest of the trash, men!',0,0,0,0,'ogron SAY_OGR_CAL_CLEANUP'),
(-1000468,'Damn it! You\'d better not die on me, human!',0,0,1,0,'ogron SAY_OGR_NODIE'),
(-1000469,'Still with us, Reethe?',0,0,1,0,'ogron SAY_OGR_SURVIVE'),
(-1000470,'Must be your lucky day. Alright, I\'ll talk. Just leave me alone. Look, you\'re not going to believe me, but it wa... oh, Light, looks like the girl could shoot...',0,0,0,0,'ogron SAY_OGR_RET_LUCKY'),
(-1000471,'By the way, thanks for watching my back.',0,0,1,0,'ogron SAY_OGR_THANKS'),

(-1000472,'The %s, having fought the good fight, falls to pieces.',0,2,0,0,'Scrap Reaver X6000 - on death anim emote'),
(-1000473,'The %s''s mechanical heart begins to beat softly.',0,2,0,0,'Scrapped Fel Reaver - on event start emote'),
(-1000474,'The naaru''s emergency shutdown will disable the manaforge permanently! It must be aborted!',0,0,0,0,'manaforge shutdown'),
(-1000475,'Stop this immediately!',0,0,0,0,'manaforge shutdown say 2'),
(-1000476,'You will not shut my manaforge down, scum!',0,1,0,0,'manaforge ara elite yell'),

(-1000477,'Let us leave this place. I\'ve had enough of these madmen!',0,0,0,0,'akuno SAY_AKU_START'),
(-1000478,'You\'ll go nowhere, fool!',0,0,0,0,'akuno SAY_AKU_AMBUSH_A'),
(-1000479,'Beware! More cultists come!',0,0,0,0,'akuno SAY_AKU_AMBUSH_B'),
(-1000480,'You will not escape us so easily!',0,0,0,0,'akuno SAY_AKU_AMBUSH_B_REPLY'),
(-1000481,'I can find my way from here. My friend Mekeda will reward you for your kind actions.',0,0,0,0,'akuno SAY_AKU_COMPLETE'),

(-1000482,'Look out!',0,0,0,25,'maghar captive SAY_MAG_START'),
(-1000483,'Don\'t let them escape! Kill the strong one first!',0,0,0,0,'maghar captive SAY_MAG_NO_ESCAPE'),
(-1000484,'More of them coming! Watch out!',0,0,0,5,'maghar captive SAY_MAG_MORE'),
(-1000485,'Where do you think you\'re going? Kill them all!',0,0,0,0,'maghar captive SAY_MAG_MORE_REPLY'),
(-1000486,'Ride the lightning, filth!',0,0,0,0,'maghar captive SAY_MAG_LIGHTNING'),
(-1000487,'FROST SHOCK!!!',0,0,0,0,'maghar captive SAY_MAG_SHOCK'),
(-1000488,'It is best that we split up now, in case they send more after us. Hopefully one of us will make it back to Garrosh. Farewell stranger.',0,0,0,1,'maghar captive SAY_MAG_COMPLETE'),

(-1000489,'Show our guest around Shattrath, will you? Keep an eye out for pickpockets in the lower city.',0,0,0,0,'SAY_KHAD_START'),
(-1000490,'A newcomer to Shattrath! Make sure to drop by later. We can always use a hand with the injured.',0,0,0,0,'SAY_KHAD_INJURED'),
(-1000491,'Be mindful of what you say, this one\'s being shown around by Khadgar\'s pet.',0,0,0,0,'SAY_KHAD_MIND_YOU'),
(-1000492,'Are you joking? I\'m a Scryer, I always watch what i say. More enemies than allies in this city, it seems.',0,0,0,0,'SAY_KHAD_MIND_ALWAYS'),
(-1000493,'Light be with you, $n. And welcome to Shattrath.',0,0,0,0,'SAY_KHAD_ALDOR_GREET'),
(-1000494,'We\'re rather selective of who we befriend, $n. You think you have what it takes?',0,0,0,0,'SAY_KHAD_SCRYER_GREET'),
(-1000495,'Khadgar himself is showing you around? You must have made a good impression, $n.',0,0,0,0,'SAY_KHAD_HAGGARD'),

(-1000496,'%s lifts its head into the air, as if listening for something.',0,2,0,0,'ancestral wolf EMOTE_WOLF_LIFT_HEAD'),
(-1000497,'%s lets out a howl that rings across the mountains to the north and motions for you to follow.',0,2,0,0,'ancestral wolf EMOTE_WOLF_HOWL'),
(-1000498,'Welcome, kind spirit. What has brought you to us?',0,0,0,0,'ancestral wolf SAY_WOLF_WELCOME'),

(-1000499,'Puny $r wanna fight %s? Me beat you! Me boss here!',0,0,1,0,'morokk SAY_MOR_CHALLENGE'),
(-1000500,'Me scared! Me run now!',0,1,0,0,'morokk SAY_MOR_SCARED'),

(-1000501,'Are you sure that you are ready? If we do not have a group of your allies to aid us, we will surely fail.',0,0,1,0,'muglash SAY_MUG_START1'),
(-1000502,'This will be a tough fight, $n. Follow me closely.',0,0,1,0,'muglash SAY_MUG_START2'),
(-1000503,'This is the brazier, $n. Put it out. Vorsha is a beast, worthy of praise from no one!',0,0,1,0,'muglash SAY_MUG_BRAZIER'),
(-1000504,'Now we must wait. It won\'t be long before the naga realize what we have done.',0,0,1,0,'muglash SAY_MUG_BRAZIER_WAIT'),
(-1000505,'Be on your guard, $n!',0,0,1,0,'muglash SAY_MUG_ON_GUARD'),
(-1000506,'Perhaps we will get a moment to rest. But i will not give up until we have faced off against Vorsha!',0,0,1,0,'muglash SAY_MUG_REST'),
(-1000507,'We have done it!',0,0,1,0,'muglash SAY_MUG_DONE'),
(-1000508,'You have my deepest gratitude. I thank you.',0,0,1,0,'muglash SAY_MUG_GRATITUDE'),
(-1000509,'I am going to patrol the area for a while longer and ensure that things are truly safe.',0,0,1,0,'muglash SAY_MUG_PATROL'),
(-1000510,'Please return to Zoram\'gar and report our success to the Warsong runner.',0,0,1,0,'muglash SAY_MUG_RETURN'),

(-1000511,'Aright, listen up! Form a circle around me and move out!',0,0,0,0,'letoll SAY_LE_START'),
(-1000512,'Aright, $r, just keep us safe from harm while we work. We\'ll pay you when we return.',0,0,0,0,'letoll SAY_LE_KEEP_SAFE'),
(-1000513,'The dig site is just north of here.',0,0,0,0,'letoll SAY_LE_NORTH'),
(-1000514,'We\'re here! Start diggin\'!',0,0,0,0,'letoll SAY_LE_ARRIVE'),
(-1000515,'I think there\'s somethin\' buried here, beneath the sand!',0,0,0,0,'letoll SAY_LE_BURIED'),
(-1000516,'Almost got it!',0,0,0,0,'letoll SAY_LE_ALMOST'),
(-1000517,'By brann\'s brittle bananas! What is it!? It... It looks like a drum.',0,0,0,0,'letoll SAY_LE_DRUM'),
(-1000518,'Wow... a drum.',0,0,0,0,'letoll SAY_LE_DRUM_REPLY'),
(-1000519,'This discovery will surely rock the foundation of modern archaeology.',0,0,0,0,'letoll SAY_LE_DISCOVERY'),
(-1000520,'Yea, great. Can we leave now? This desert is giving me hives.',0,0,0,0,'letoll SAY_LE_DISCOVERY_REPLY'),
(-1000521,'Have ye gone mad? You expect me to leave behind a drum without first beatin\' on it? Not this son of Ironforge! No sir!',0,0,0,0,'letoll SAY_LE_NO_LEAVE'),
(-1000522,'This reminds me of that one time where you made us search Silithus for evidence of sand gnomes.',0,0,0,0,'letoll SAY_LE_NO_LEAVE_REPLY1'),
(-1000523,'Or that time when you told us that you\'d discovered the cure for the plague of the 20th century. What is that even? 20th century?',0,0,0,0,'letoll SAY_LE_NO_LEAVE_REPLY2'),
(-1000524,'I don\'t think it can top the one time where he told us that he\'d heard that Artha\'s "cousin\'s" skeleton was frozen beneath a glacier in Winterspring. I\'ll never forgive you for that one, Letoll. I mean honestly... Artha\'s cousin?',0,0,0,0,'letoll SAY_LE_NO_LEAVE_REPLY3'),
(-1000525,'I dunno. It can\'t possibly beat the time he tried to convince us that we\'re all actually a figment of some being\'s imagination and that they only use us for their own personal amusement. That went over well during dinner with the family.',0,0,0,0,'letoll SAY_LE_NO_LEAVE_REPLY4'),
(-1000526,'Shut yer yaps! I\'m gonna bang on this drum and that\'s that!',0,0,0,0,'letoll SAY_LE_SHUT'),
(-1000527,'Say, do you guys hear that?',0,0,0,0,'letoll SAY_LE_REPLY_HEAR'),
(-1000528,'IN YOUR FACE! I told you there was somethin\' here!',0,0,0,0,'letoll SAY_LE_IN_YOUR_FACE'),
(-1000529,'Don\'t just stand there! Help him out!',0,0,0,0,'letoll SAY_LE_HELP_HIM'),
(-1000530,'%s picks up the drum.',0,2,0,0,'letoll EMOTE_LE_PICK_UP'),
(-1000531,'You\'ve been a tremendous help, $r! Let\'s get out of here before more of those things show up! I\'ll let Dwarfowitz know you did the job asked of ya\' admirably.',0,0,0,0,'letoll SAY_LE_THANKS'),

(-1000532,'At your command, my liege...',0,0,0,0,'torloth TORLOTH_DIALOGUE1'),
(-1000533,'As you desire, Lord Illidan.',0,0,0,0,'torloth TORLOTH_DIALOGUE2'),
(-1000534,'Yes, Lord Illidan, I would sacrifice to you this magnificent physique. On this day you will fall - another victim of Torloth...',0,0,0,0,'torloth TORLOTH_DIALOGUE3'),
(-1000535,'Destroy them, Torloth. Let lose their blood like a river upon this hallowed ground.',0,0,0,0,'lordillidan ILLIDAN_DIALOGUE'),
(-1000536,'What manner of fool dares stand before Illidan Stormrage? Soldiers, destroy these insects!',0,1,0,0,'lordillidan ILLIDAN_SUMMON1'),
(-1000537,'You are no challenge for the Crimson Sigil. Mind breakers, end this nonsense.',0,1,0,0,'lordillidan ILLIDAN_SUMMON2'),
(-1000538,'Run while you still can. The highlords come soon...',0,1,0,0,'lordillidan ILLIDAN_SUMMON3'),
(-1000539,'Torloth your master calls!',0,1,0,0,'lordillidan ILLIDAN_SUMMON4'),
(-1000540,'So you have defeated the Crimson Sigil. You now seek to challenge my rule? Not even Arthas could defeat me, yet you dare to even harbor such thoughts? Then I say to you, come! Come $N! The Black Temple awaits...',0,1,0,0,'lordillidan EVENT_COMPLETED'),

(-1000541,'%s jumps into the moonwell and goes underwater...',0,2,0,0,'kitten EMOTE_SAB_JUMP'),
(-1000542,'%s follows $n obediently.',0,2,0,0,'kitten EMOTE_SAB_FOLLOW'),

(-1000543,'Why have you come here, outsider? You will only find pain! Our fate will be yours...',0,0,0,25,'restless app SAY_RAND_1'),
(-1000544,'It was ... terrible... the demon...',0,0,0,25,'restless app SAY_RAND_2'),
(-1000545,'The darkness... the corruption... they came too quickly for anyone to know...',0,0,0,25,'restless app SAY_RAND_3'),
(-1000546,'The darkness will consume all... all the living...',0,0,0,25,'restless app SAY_RAND_4'),
(-1000547,'It is too late for us, living one. Take yourself and your friend away from here before you both are... claimed...',0,0,0,25,'restless app SAY_RAND_5'),
(-1000548,'It is too late for Jarl... its hold is too strong...',0,0,0,25,'restless app SAY_RAND_6'),
(-1000549,'Go away, whoever you are! Witch Hill is mine... mine!',0,0,0,25,'restless app SAY_RAND_7'),
(-1000550,'The manor... someone else... will soon be consumed...',0,0,0,25,'restless app SAY_RAND_8'),

(-1000553,'Be ready, $N. I hear the council returning. Prepare to ambush!',0,0,0,0,'deathstalker_faerleia SAY_START'),
(-1000554,'Well done. A blow to Arugal no doubt!',0,0,0,0,'deathstalker_faerleia SAY_END'),

(-1000561,'My wounds are grave. Forgive my slow pace but my injuries won\'t allow me to walk any faster.',0,0,0,0,'SAY_CORPORAL_KEESHAN_1'),
(-1000562,'Ah, fresh air, at last! I need a moment to rest.',0,0,0,0,'SAY_CORPORAL_KEESHAN_2'),
(-1000563,'The Blackrock infestation is thick in these parts. I will do my best to keep the pace. Let\'s go!',0,0,0,0,'SAY_CORPORAL_KEESHAN_3'),
(-1000564,'Marshal Marris, sir. Corporal Keeshan of the 12th Sabre Regiment returned from battle and reporting for duty!',0,0,0,0,'SAY_CORPORAL_KEESHAN_4'),
(-1000565,'Brave adventurer, thank you for rescuing me! I am sure Marshal Marris will reward your kind deed.',0,0,0,0,'SAY_CORPORAL_KEESHAN_5'),

(-1000566,'Stand back! Stand clear! The infernal will need to be given a wide berth!',0,0,0,0,'SAY_NIBY_1'),
(-1000567,'BOW DOWN TO THE ALMIGHTY! BOW DOWN BEFORE MY INFERNAL DESTRO... chicken?',0,0,0,0,'SAY_NIBY_2'),
(-1000568,'%s rolls on the floor laughing.',0,2,0,0,'EMOTE_IMPSY_1'),
(-1000569,'Niby, you\' re an idiot.',0,0,0,0,'SAY_IMPSY_1'),
(-1000570,'Silence, servant! Vengeance will be mine! Death to Stormwind! Death by chicken!',0,0,0,0,'SAY_NIBY_3'),

(-1000571,'Help! I\'ve only one hand to defend myself with.',0,0,0,0,'SAY_MIRAN_1'),
(-1000572,'Feel the power of the Dark Iron Dwarves!',0,0,0,0,'SAY_DARK_IRON_DWARF'),
(-1000573,'Send them on! I\'m not afraid of some scrawny beasts!',0,0,0,0,'SAY_MIRAN_2'),
(-1000574,'Ah, here at last! It\'s going to feel so good to get rid of these barrels.',0,0,0,0,'SAY_MIRAN_3'),

(-1000579,'There! Destroy him! The Cipher must be recovered!',0,0,0,25,'spirit hunter - SAY_VENERATUS_SPAWN'),

(-1000582,'Help! Please, You must help me!',0,0,0,0,'Galen - periodic say'),
(-1000583,'Let us leave this place.',0,0,0,0,'Galen - quest accepted'),
(-1000584,'Look out! The $c attacks!',0,0,0,0,'Galen - aggro 1'),
(-1000585,'Help! I\'m under attack!',0,0,0,0,'Galen - aggro 2'),
(-1000586,'Thank you $N. I will remember you always. You can find my strongbox in my camp, north of Stonard.',0,0,0,0,'Galen - quest complete'),
(-1000587,'%s whispers to $N the secret to opening his strongbox.',0,2,0,0,'Galen - emote whisper'),
(-1000588,'%s disappears into the swamp.',0,2,0,0,'Galen - emote disapper'),

(-1000589,'Kroshius live? Kroshius crush!',0,1,0,0,'SAY_KROSHIUS_REVIVE'),

(-1000590,'The feast of curruption is no more! Magtheridon has fallen to the battle prowess of $N and $Ghis:her; allies! Witness the might of the Alliance! A pit lord commander is destroyed!', '0', '6', '0', '15', 'Yell Magtheridon Death1 A'),
(-1000591,'Hear me brothers and sisters-in-arms! The time of our enemies is at an end! We must strike at the fel orcs that remain! Exterminate them like the vermin that they are! Carry with you the favor of the Sons of Lothar!', '0', '6', '0', '22', 'Yell Magtheridon Death2 A'),
(-1000592,'For the first time - in as long as I can remember - there is silence.', '0', '6', '0', '15', 'Yell Magtheridon Death1 H'),
(-1000593,'This defeat is not only a blow to Illidan, $n. The Legion too reels... A pit lord commander has been defeated. The siege of Hellfire Citadel now holds no purpose for the Burning Legion. All of their efforts will undoubtedly be turned upon the Black Temple. Redemption comes for Illidan... and soon.', '0', '6', '0', '22', 'Yell Magtheridon Death2 H'),

(-1000603,'Do not test me, scurvy dog! I\'m trained in the way of the Blood Knights!',0,0,0,0,'silvermoon harry SAY_AGGRO'),
(-1000604,'I\'ll pay! I\'ll pay! Eeeek! Please don\'t hurt me!',0,0,0,0,'silvermoon harry SAY_BEATEN'),

(-1000615,'Use my shinies...make weather good again...make undead things go away.',0,0,0,0,'mosswalker victim SAY_DIE_1'),
(-1000616,'We gave shinies to shrine... we not greedy... why this happen?',0,0,0,0,'mosswalker victim SAY_DIE_2'),
(-1000617,'I do something bad? I sorry....',0,0,0,0,'mosswalker victim SAY_DIE_3'),
(-1000618,'We not do anything... to them... I no understand.',0,0,0,0,'mosswalker victim SAY_DIE_4'),
(-1000619,'Thank...you.',0,0,0,0,'mosswalker victim SAY_DIE_5'),
(-1000620,'Please take... my shinies. All done...',0,0,0,0,'mosswalker victim SAY_DIE_6'),

(-1000621,'All systems on-line.  Prepare yourself, we leave shortly.',0,0,0,0,'maxx SAY_START'),
(-1000622,'Be careful in there and come back in one piece!',0,0,0,0,'maxx SAY_ALLEY_FAREWELL'),
(-1000623,'Proceed.',0,0,0,0,'maxx SAY_CONTINUE'),
(-1000624,'You\'re back!  Were you able to get all of the machines?',0,0,0,0,'maxx SAY_ALLEY_FINISH'),

(-1000625,'%s gathers the warp chaser\'s blood.',0,2,0,0,'zeppit EMOTE_GATHER_BLOOD'),

(-1000628,'%s feeds on the freshly-killed warp chaser.',0,2,0,0,'hungry ray EMOTE_FEED'),

(-1000629,'<cough> <cough> Damsel in distress over here!',0,0,0,0,'isla starmane - SAY_ISLA_PERIODIC_1'),
(-1000630,'Hello? Help?',0,0,0,0,'isla starmane - SAY_ISLA_PERIODIC_2'),
(-1000631,'Don\'t leave me in here! Cause if you do I will find you!',0,0,0,0,'isla starmane - SAY_ISLA_PERIODIC_3'),
(-1000632,'Ok, let\'s get out of here!',0,0,0,0,'isla starmane - SAY_ISLA_START'),
(-1000633,'You sure you\'re ready? Take a moment.',0,0,0,0,'isla starmane - SAY_ISLA_WAITING'),
(-1000634,'Alright, let\'s do this!',0,0,0,0,'isla starmane - SAY_ISLA_LEAVE_BUILDING'),

(-1000644,'Ouch! That\'s it, I quit the target business!',0,0,0,0,'SAY_LUCKY_HIT_1'),
(-1000645,'My ear! You grazed my ear!',0,0,0,0,'SAY_LUCKY_HIT_2'),
(-1000646,'Not the \'stache! Now I\'m asymmetrical!',0,0,0,5,'SAY_LUCKY_HIT_3'),
(-1000647,'Good shot!',0,0,0,4,'SAY_LUCKY_HIT_APPLE'),
(-1000648,'Stop whining. You\'ve still got your luck.',0,0,0,0,'SAY_DROSTAN_GOT_LUCKY_1'),
(-1000649,'Bah, it\'s an improvement.',0,0,0,11,'SAY_DROSTAN_GOT_LUCKY_2'),
(-1000650,'Calm down lad, it\'s just a birdshot!',0,0,0,0,'SAY_DROSTAN_HIT_BIRD_1'),
(-1000651,'The only thing hurt is your pride, lad! Buck up!',0,0,0,0,'SAY_DROSTAN_HIT_BIRD_2'),

(-1000652,'Me so hungry! YUM!',0,0,0,71,'dragonmaw peon SAY_PEON_1'),
(-1000653,'Hey... me not feel so good.',0,0,0,0,'dragonmaw peon SAY_PEON_2'),
(-1000654,'You is bad orc... baaad... or... argh!',0,0,0,0,'dragonmaw peon SAY_PEON_3'),
(-1000655,'Time for eating!?',0,0,0,71,'dragonmaw peon SAY_PEON_4'),
(-1000656,'It put the mutton in the stomach!',0,0,0,71,'dragonmaw peon SAY_PEON_5'),

(-1000666,'I can sense the SHADOW on your hearts. There can be no rest for the wicked!',0,1,0,0,'lethon SAY_LETHON_AGGRO'),
(-1000667,'Your wicked souls shall feed my power!',0,1,0,0,'lethon SAY_LETHON_SHADE'),

(-1000668,'%s releases the last of its energies into the nearby runestone, successfully reactivating it.',0,2,0,0,'infused crystal SAY_DEFENSE_FINISH'),

(-1000669,'We will locate the origin of the Nightmare through the fragments you collected, $N. From there, we will pull Eranikus through a rift in the Dream. Steel yourself, $C. We are inviting the embodiment of the Nightmare into our world.',0,0,0,0,'remulos SAY_REMULOS_INTRO_1'),
(-1000670,'To Nighthaven! Keep your army close, champion. ',0,0,0,0,'remulos SAY_REMULOS_INTRO_2'),
(-1000671,'The rift will be opened there, above the Lake Elun\'ara. Prepare yourself, $N. Eranikus entry into our world will be wrought with chaos and strife.',0,0,0,0,'remulos SAY_REMULOS_INTRO_3'),
(-1000672,'He will stop at nothing to get to Malfurion\'s physical manifistation. That must not happen... We must keep the beast occupied long enough for Tyrande to arrive.',0,0,0,0,'remulos SAY_REMULOS_INTRO_4'),
(-1000673,'Defend Nightaven, hero...',0,0,0,0,'remulos SAY_REMULOS_INTRO_5'),
(-1000674,'%s has entered our world',0,3,0,0,'eranikus EMOTE_SUMMON_ERANIKUS'),
(-1000675,'Pitful predictable mortals... You know not what you have done! The master\'s will fulfilled. The Moonglade shall be destroyed and Malfurion along with it!',0,1,0,0,'eranikus SAY_ERANIKUS_SPAWN'),
(-1000676,'Fiend! Face the might of Cenarius!',0,1,0,1,'remulos SAY_REMULOS_TAUNT_1'),
(-1000677,'%s lets loose a sinister laugh.',0,2,0,0,'eranikus EMOTE_ERANIKUS_LAUGH'),
(-1000678,'You are certanly not your father, insect. Should it interest me, I would crush you with but a swipe of my claws. Turn Shan\'do Stormrage over to me and your pitiful life will be spared along with the lives of your people.',0,1,0,0,'eranikus SAY_ERANIKUS_TAUNT_2'),
(-1000679,'Who is the predictable one, beast? Surely you did not think that we would summon you on top of Malfurion? Your redemption comes, Eranikus. You will be cleansed of this madness - this corruption.',0,1,0,1,'remulos SAY_REMULOS_TAUNT_3'),
(-1000680,'My redemption? You are bold, little one. My redemption comes by the will of my god.',0,1,0,0,'eranikus SAY_ERANIKUS_TAUNT_4'),
(-1000681,'%s roars furiously.',0,2,0,0,'eranikus EMOTE_ERANIKUS_ATTACK'),
(-1000682,'Hurry, $N! We must find protective cover!',0,0,0,0,'remulos SAY_REMULOS_DEFEND_1'),
(-1000683,'Please, champion, protect our people.',0,0,0,1,'remulos SAY_REMULOS_DEFEND_2'),
(-1000684,'Rise, servants of the Nightmare! Rise and destroy this world! Let there be no survivors...',0,1,0,0,'eranikus SAY_ERANIKUS_SHADOWS'),
(-1000685,'We will battle these fiends, together! Nighthaven\'s Defenders are also among us. They will fight to the death if asked. Now, quickly, we must drive these aberations back to the Nightmare. Destroy them all!',0,0,0,1,'remulos SAY_REMULOS_DEFEND_3'),
(-1000686,'Where is your savior? How long can you hold out against my attacks?',0,1,0,0,'eranikus SAY_ERANIKUS_ATTACK_1'),
(-1000687,'Defeated my minions? Then face me, mortals!',0,1,0,0,'eranikus SAY_ERANIKUS_ATTACK_2'),
(-1000688,'Remulos, look how easy they fall before me? You can stop this, fool. Turn the druid over to me and it will all be over...',0,1,0,0,'eranikus SAY_ERANIKUS_ATTACK_3'),
(-1000689,'Elune, hear my prayers. Grant us serenity! Watch over our fallen...',0,1,0,0,'tyrande SAY_TYRANDE_APPEAR'),
(-1000690,'Tend to the injuries of the wounded, sisters!',0,0,0,0,'tyrande SAY_TYRANDE_HEAL'),
(-1000691,'Seek absolution, Eranikus. All will be forgiven...',0,1,0,0,'tyrande SAY_TYRANDE_FORGIVEN_1'),
(-1000692,'You will be forgiven, Eranikus. Elune will always love you. Break free of the bonds that command you!',0,1,0,0,'tyrande SAY_TYRANDE_FORGIVEN_2'),
(-1000693,'The grasp of the Old Gods is unmoving. He is consumed by their dark thoughts... I... I... I cannot... cannot channel much longer... Elune aide me.',0,0,0,0,'tyrande SAY_TYRANDE_FORGIVEN_3'),
(-1000694,'IT BURNS! THE PAIN.. SEARING...',0,1,0,0,'eranikus SAY_ERANIKUS_DEFEAT_1'),
(-1000695,'WHY? Why did this happen to... to me? Where were you Tyrande? Where were you when I fell from the grace of Elune?',0,1,0,0,'eranikus SAY_ERANIKUS_DEFEAT_2'),
(-1000696,'I... I feel... I feel the touch of Elune upon my being once more... She smiles upon me... Yes... I...', 0,1,0,0,'eranikus SAY_ERANIKUS_DEFEAT_3'),
(-1000697,'%s is wholly consumed by the Light of Elune. Tranquility sets in over the Moonglade',0,2,0,0,'eranikus EMOTE_ERANIKUS_REDEEM'),
(-1000698,'%s falls to one knee.',0,2,0,0,'tyrande EMOTE_TYRANDE_KNEEL'),
(-1000699,'Praise be to Elune... Eranikus is redeemed.',0,1,0,0,'tyrande SAY_TYRANDE_REDEEMED'),
(-1000700,'For so long, I was lost... The Nightmare\'s corruption had consumed me... And now, you... all of you.. you have saved me. Released me from its grasp.',0,0,0,0,'eranikus SAY_REDEEMED_1'),
(-1000701,'But... Malfurion, Cenarius, Ysera... They still fight. They need me. I must return to the Dream at once.', 0,0,0,0,'eranikus SAY_REDEEMED_2'),
(-1000702,'My lady, I am unworthy of your prayer. Truly, you are an angel of light. Please, assist me in returning to the barrow den so that I may return to the Dream. I like Malfurion, also have a love awaiting me... I must return to her... to protect her...', 0,0,0,0,'eranikus SAY_REDEEMED_3'),
(-1000703,'And heroes... I hold that which you seek. May it once more see the evil dissolved. Remulos, see to it that our champion receives the shard of the Green Flight.',0,0,0,0,'eranikus SAY_REDEEMED_4'),
(-1000704,'It will be done, Eranikus. Be well, ancient one.',0,0,0,0,'remulos SAY_REMULOS_OUTRO_1'),
(-1000705,'Let us leave Nighthave, hero. Seek me out at the grove.',0,0,0,0,'remulos SAY_REMULOS_OUTRO_2'),
(-1000706,'Your world shall suffer an unmerciful end. The Nightmare comes for you!',0,0,0,0,'eranikus SAY_ERANIKUS_KILL'),

(-1000707,'This blue light... It\'s strange. What do you think it means?',0,0,0,0,'Ranshalla SAY_ENTER_OWL_THICKET'),
(-1000708,'We\'ve found it!',0,0,0,0,'Ranshalla SAY_REACH_TORCH_1'),
(-1000709,'Please, light this while I am channeling',0,0,0,0,'Ranshalla SAY_REACH_TORCH_2'),
(-1000710,'This is the place. Let\'s light it.',0,0,0,0,'Ranshalla SAY_REACH_TORCH_3'),
(-1000711,'Let\'s find the next one.',0,0,0,0,'Ranshalla SAY_AFTER_TORCH_1'),
(-1000712,'We must continue on now.',0,0,0,0,'Ranshalla SAY_AFTER_TORCH_2'),
(-1000713,'It is time for the final step; we must activate the altar.',0,0,0,0,'Ranshalla SAY_REACH_ALTAR_1'),
(-1000714,'I will read the words carved into the stone, and you must find a way to light it.',0,0,0,0,'Ranshalla SAY_REACH_ALTAR_2'),
(-1000715,'The altar is glowing! We have done it!',0,0,0,0,'Ranshalla SAY_RANSHALLA_ALTAR_1'),
(-1000716,'What is happening? Look!',0,0,0,0,'Ranshalla SAY_RANSHALLA_ALTAR_2'),
(-1000717,'It has been many years...',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_3'),
(-1000718,'Who has disturbed the altar of the goddess?',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_4'),
(-1000719,'Please, priestesses, forgive us for our intrusion. We do not wish any harm here.',0,0,0,0,'Ranshalla SAY_RANSHALLA_ALTAR_5'),
(-1000720,'We only wish to know why the wildkin guard this area...',0,0,0,0,'Ranshalla SAY_RANSHALLA_ALTAR_6'),
(-1000721,'Enu thora\'serador. This is a sacred place.',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_7'),
(-1000722,'We will show you...',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_8'),
(-1000723,'Look above you; thara dormil dorah...',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_9'),
(-1000724,'This gem once allowed direct communication with Elune, herself.',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_10'),
(-1000725,'Through the gem, Elune channeled her infinite wisdom...',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_11'),
(-1000726,'Realizing that the gem needed to be protected, we turned to the goddess herself.',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_12'),
(-1000727,'Soon after, we began to have visions of a creature... A creature with the feathers of an owl, but the will and might of a bear...',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_13'),
(-1000728,'It was on that day that the wildkin were given to us. Fierce guardians, the goddess assigned the wildkin to protect all of her sacred places.',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_14'),
(-1000729,'Anu\'dorini Talah, Ru shallora enudoril.',0,0,0,0,'Voice of Elune SAY_VOICE_ALTAR_15'),
(-1000730,'But now, many years later, the wildkin have grown more feral, and without the guidance of the goddess, they are confused...',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_16'),
(-1000731,'Without a purpose, they wander... But many find their way back to the sacred areas that they once were sworn to protect.',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_17'),
(-1000732,'Wildkin are inherently magical; this power was bestowed upon them by the goddess.',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_18'),
(-1000733,'Know that wherever you might find them in the world, they are protecting something of importance, as they were entrusted to do so long ago.',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_19'),
(-1000734,'Please, remember what we have shown you...',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_20'),
(-1000735,'Farewell.',0,0,0,0,'Priestess of Elune SAY_PRIESTESS_ALTAR_21'),
(-1000736,'Thank you for you help, $n. I wish you well in your adventures.',0,0,0,0,'Ranshalla SAY_QUEST_END_1'),
(-1000737,'I want to stay here and reflect on what we have seen. Please see Erelas and tell him what we have learned.',0,0,0,0,'Ranshalla SAY_QUEST_END_2'),
(-1000738,'%s begins chanting a strange spell...',0,2,0,0,'Ranshalla EMOTE_CHANT_SPELL'),
(-1000739,'Remember, I need your help to properly channel. I will ask you to aid me several times in our path, so please be ready.',0,0,0,0,'Ranshalla SAY_QUEST_START'),

(-1000740,'We must act quickly or all shall be lost!',0,0,0,1,'SAY_ANACHRONOS_INTRO_1'),
(-1000741,'My forces cannot overcome the Qiraji defenses. We will not be able to get close enough to place your precious barrier, dragon.',0,0,0,0,'SAY_FANDRAL_INTRO_2'),
(-1000742,'There is a way...',0,0,0,22,'SAY_MERITHRA_INTRO_3'),
(-1000743,'%s nods knowingly.',0,2,0,0,'EMOTE_ARYGOS_NOD'),
(-1000744,'Aye, Fandral, remember these words: Let not your grief guide your faith. These thoughts you hold... dark places you go, night elf. Absolution cannot be had through misguided vengeance.',0,0,0,1,'SAY_CAELESTRASZ_INTRO_4'),
(-1000745,'%s glances at her compatriots.',0,2,0,0,'EMOTE_MERITHRA_GLANCE'),
(-1000746,'We will push him back, Anachronos. This I vow. Uphold your end of this task. Let not your hands falter as you seal our fates behind the barrier.',0,0,0,1,'SAY_MERITHRA_INTRO_5'),
(-1000747,'Succumb to the endless dream, little ones. Let it consume you!',0,1,0,22,'SAY_MERITHRA_ATTACK_1'),
(-1000748,'Anachronos, this diversion will give you and the young druid time enough to seal the gate. Do not falter. Now, let us see how they deal with chaotic magic.',0,0,0,1,'SAY_ARYGOS_ATTACK_2'),
(-1000749,'Let them feel the wrath of the Blue Flight! May Malygos protect me!',0,1,0,22,'SAY_ARYGOS_ATTACK_3'),
(-1000750,'Do not forget sacrifices made on this day, night elf. We have all suffered immensely at the hands of these beasts.',0,0,0,1,'SAY_CAELESTRASZ_ATTACK_4'),
(-1000751,'Alexstrasza give me the resolve to drive our enemies back!',0,1,0,22,'SAY_CAELESTRASZ_ATTACK_5'),
(-1000752,'NOW, STAGHELM! WE GO NOW! Prepare your magic!',0,0,0,22,'SAY_ANACHRONOS_SEAL_1'),
(-1000753,'It is done, dragon. Lead the way.',0,0,0,25,'SAY_FANDRAL_SEAL_2'),
(-1000754,'Stay close...',0,0,0,0,'SAY_ANACHRONOS_SEAL_3'),
(-1000755,'The sands of time will halt, but only for a moment! I will now conjure the barrier.',0,0,0,0,'SAY_ANACHRONOS_SEAL_4'),
(-1000756,'FINISH THE SPELL, STAGHELM! I CANNOT HOLD THE GLYPHS OF WARDING IN PLACE MUCH LONGER! CALL FORTH THE ROOTS!', 0,0,0,0,'SAY_ANACHRONOS_SEAL_5'),
(-1000757,'Ancient ones guide my hand... Wake from your slumber! WAKE AND SEAL THIS CURSED PLACE!',0,0,0,0, 'SAY_FANDRAL_SEAL_6'),
(-1000758,'%s falls to one knee - exhausted.',0,2,0,0,'EMOTE_FANDRAL_EXHAUSTED'),
(-1000759,'It... It is over, Lord Staghelm. We are victorious. Albeit the cost for this victory was great.',0,0,0,1,'SAY_ANACHRONOS_EPILOGUE_1'),
(-1000760,'There is but one duty that remains...',0,0,0,1,'SAY_ANACHRONOS_EPILOGUE_2'),
(-1000761,'Before I leave this place, I make one final offering for you, Lord Staghelm. Should a time arise in which you must gain entry to this accursed fortress, use the Scepter of the Shifting Sands on the sacred gong. The magic holding the barrier together will dissipate and the horrors of the Ahn\'Qiraj will be unleashed upon the world once more.',0,0,0,1,'SAY_ANACHRONOS_EPILOGUE_3'),
(-1000762,'%s hands the Scepter of the Shifting Sands to $N.',0,2,0,0,'EMOTE_ANACHRONOS_SCEPTER'),
(-1000763,'After the savagery that my people have witnessed and felt, you expect me to accept another burden, dragon? Surely you are mad.',0,0,0,1,'SAY_FANDRAL_EPILOGUE_4'),
(-1000764,'I want nothing to do with Silithus, the Qiraji and least of all, any damned dragons!',0,0,0,1,'SAY_FANDRAL_EPILOGUE_5'),
(-1000765,'%s hurls the Scepter of the Shifting Sands into the barrier, shattering it.',0,2,0,0,'EMOTE_FANDRAL_SHATTER'),
(-1000766,'Lord Staghelm, where are you going? You would shatter our bond for the sake of pride?',0,0,0,1,'SAY_ANACHRONOS_EPILOGUE_6'),
(-1000767,'My son\'s soul will find no comfort in this hollow victory, dragon. I will have him back. Though it takes a millennia, I WILL have my son back!',0,0,0,1,'SAY_FANDRAL_EPILOGUE_7'),
(-1000768,'%s shakes his head in disappointment.',0,2,0,25,'EMOTE_ANACHRONOS_DISPPOINTED'),
(-1000769,'%s kneels down to pickup the fragments of the shattered scepter.',0,2,0,0,'EMOTE_ANACHRONOS_PICKUP'),
(-1000770,'And now you know all that there is to know, mortal...',0,0,0,0,'SAY_ANACHRONOS_EPILOGUE_8'),

(-1000771,'Let\'s go $N!',0,0,0,0,'Feero Ironhand SAY_QUEST_START'),
(-1000772,'It looks like we\'re in trouble. Look lively, here they come!',0,0,0,0,'Feero Ironhand SAY_FIRST_AMBUSH_START'),
(-1000773,'Assassins from that cult you found... Let\'s get moving before someone else finds us out here.',0,0,0,0,'Feero Ironhand SAY_FIRST_AMBUSH_END'),
(-1000774,'Hold! I sense an evil presence... Undead!',0,0,0,0,'Feero Ironhand SAY_SECOND_AMBUSH_START'),
(-1000775,'A $C! Slaying him would please the master. Attack!',0,0,0,0,'Forsaken Scout SAY_SCOUT_SECOND_AMBUSH'),
(-1000776,'They\'re coming out of the woodwork today. Let\'s keep moving or we may find more things that want me dead.',0,0,0,0,'Feero Ironhand SAY_SECOND_AMBUSH_END'),
(-1000777,'These three again?',0,0,0,0,'Feero Ironhand SAY_FINAL_AMBUSH_START'),
(-1000778,'Not quite so sure of yourself without the Purifier, hm?',0,0,0,0,'Balizar the Umbrage SAY_BALIZAR_FINAL_AMBUSH'),
(-1000779,'I\'ll finish you off for good this time!',0,0,0,0,'Feero Ironhand SAY_FINAL_AMBUSH_ATTACK'),
(-1000780,'Well done! I should be fine on my own from here. Remember to talk to Delgren when you return to Maestra\'s Post in Ashenvale.',0,0,0,0,'Feero Ironhand SAY_QUEST_END'),

(-1000784,'Thanks $N. Now let\'s get out of here!',0,0,0,0,'melizza SAY_MELIZZA_START'),
(-1000785,'We made it! Thanks again! I\'m going to run ahead!',0,0,0,0,'melizza SAY_MELIZZA_FINISH'),
(-1000786,'Hey Hornizz! I\'m back! And there are some people behind me who helped me out of a jam.',0,0,0,1,'melizza SAY_MELIZZA_1'),
(-1000787,'We\'re going to have to scratch the Maraudines off our list. Too hard to work with...',0,0,0,1,'melizza SAY_MELIZZA_2'),
(-1000788,'Well, I\'m off to the Gelkis. They\'re not as dumb as the Maraudines, but they\'re more reasonable.',0,0,0,3,'melizza SAY_MELIZZA_3'),

(-1000789,'Well, now or never I suppose. Remember, once we get to the road safety, return to Terenthis to let him know we escaped.',0,0,0,0,'volcor SAY_START'),
(-1000790,'We made it, My friend. Remember to find Terenthis and let him know we\'re safe. Thank you again.',0,0,0,0,'volcor SAY_END'),
(-1000791,'Here they come.',0,0,0,0,'volcor SAY_FIRST_AMBUSH'),
(-1000792,'We can overcome these foul creatures.',0,0,0,0,'volcor SAY_AGGRO_1'),
(-1000793,'We shall earn our deaths at the very least!',0,0,0,0,'volcor SAY_AGGRO_2'),
(-1000794,'Don\'t give up! Fight, to the death!',0,0,0,0,'volcor SAY_AGGRO_3'),

(-1000795,'Ow! Ok, I\'ll get back to work, $N!',0,0,1,0,'Lazy Peon SAY_PEON_AWOKEN'),
(-1000796,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1000797,'%s squawks and heads toward Veil Shalas. Hurry and follow!',0,2,0,0,'skywing SAY_SKYWING_START'),
(-1000798,'%s pauses briefly before the tree and then heads inside.',0,2,0,0,'skywing SAY_SKYWING_TREE_DOWN'),
(-1000799,'%s seems to be looking for something. He wants you to follow.',0,2,0,0,'skywing SAY_SKYWING_TREE_UP'),
(-1000800,'%s flies to the platform below! You\'d better jump if you want to keep up. Hurry!',0,2,0,0,'skywing SAY_SKYWING_JUMP'),
(-1000801,'%s bellows a loud squawk!',0,2,0,0,'skywing SAY_SKYWING_SUMMON'),
(-1000802,'Free at last from that horrible curse! Thank you! Please send word to Rilak the Redeemed that I am okay. My mission lies in Skettis. Terokk must be defeated!',0,0,0,0,'skywing SAY_SKYWING_END'),

(-1000803,'You do not fight alone, $n! Together, we will banish this spawn of hellfire!',0,1,0,0,'Oronok SAY_ORONOK_TOGETHER'),
(-1000804,'We will fight when you are ready.',0,0,0,0, 'Oronok SAY_ORONOK_READY'),
(-1000805,'We will set the elements free of your grasp by force!',0,1,0,0,'Oronok SAY_ORONOK_ELEMENTS'),
(-1000806,'What say the elements, Torlok? I only hear silence.',0,0,0,1,'Oronok SAY_ORONOK_EPILOGUE_1'),
(-1000807,'I hear what you hear, brother. Look behind you...',0,0,0,1,'Torlok SAY_TORLOK_EPILOGUE_2'),
(-1000808,'They are redeemed! Then we have won?',0,0,0,1,'Oronok SAY_ORONOK_EPILOGUE_3'),
(-1000809,'It is now as it should be, shaman. You have done well.',0,0,0,0,'Spirit of Earth SAY_EARTH_EPILOGUE_4'),
(-1000810,'Yes... Well enough for the elements that are here, but the cipher is known to another... The spirits of fire are in turmoil... If this force is not stopped, the world where these mortals came from will cease.',0,0,0,0,'Spirit of Fire SAY_FIRE_EPILOGUE_5'),
(-1000811,'Farewell, mortals... The earthmender knows what fire feels...',0,0,0,0, 'Spirit of Earth SAY_EARTH_EPILOGUE_6'),
(-1000812,'We leave, then, Torlok. I have only one request...',0,0,0,1,'Oronok SAY_ORONOK_EPILOGUE_7'),
(-1000813,'The Torn-heart men give their weapons to Earthmender Torlok.',0,2,0,0,'Torlok EMOTE_GIVE_WEAPONS'),
(-1000814,'Give these to the heroes that made this possible.',0,0,0,1,'Oronok SAY_ORONOK_EPILOGUE_8'),

(-1000815,'Be healed!',0,1,0,0,'Eris Havenfire SAY_PHASE_HEAL'),
(-1000816,'We are saved! The peasants have escaped the Scourge!',0,1,0,0,'Eris Havenfire SAY_EVENT_END'),
(-1000817,'I have failed once more...',0,1,0,0,'Eris Havenfire SAY_EVENT_FAIL_1'),
(-1000818,'I now return to whence I came, only to find myself here once more to relive the same epic tragedy.',0,0,0,0,'Eris Havenfire SAY_EVENT_FAIL_2'),
(-1000819,'The Scourge are upon us! Run! Run for your lives!',0,1,0,0,'Peasant SAY_PEASANT_APPEAR_1'),
(-1000820,'Please help us! The Prince has gone mad!',0,1,0,0,'Peasant SAY_PEASANT_APPEAR_2'),
(-1000821,'Seek sanctuary in Hearthglen! It is our only hope!',0,1,0,0,'Peasant SAY_PEASANT_APPEAR_3'),

(-1000822,'The signal has been sent. He should be arriving shortly.',0,0,0,1,'squire rowe SAY_SIGNAL_SENT'),
(-1000823,'Yawww!',0,0,0,35,'reginald windsor SAY_DISMOUNT'),
(-1000824,'I knew you would come, $N. It is good to see you again, friend.',0,0,0,1,'reginald windsor SAY_WELCOME'),

(-1000825,'On guard, friend. The lady dragon will not give in without a fight.',0,0,0,1,'reginald windsor SAY_QUEST_ACCEPT'),
(-1000826,'As was fated a lifetime ago in Karazhan, monster - I come - and with me I bring justice.',0,6,0,22,'reginald windsor SAY_GET_READY'),
(-1000827,'Seize him! Seize the worthless criminal and his allies!',0,6,0,0,'prestor SAY_GONNA_DIE'),
(-1000828,'Reginald, you know that I cannot let you pass.',0,0,0,1,'jonathan SAY_DIALOG_1'),
(-1000829,'You must do what you think is right, Marcus. We served together under Turalyon. He made us both the men that we are today. Did he err with me? Do you truly believe my intent is to cause harm to our alliance? Would I shame our heroes?',0,0,0,1,'reginald windsor SAY_DIALOG_2'),
(-1000830,'Holding me here is not the right decision, Marcus.',0,0,0,1,'reginald windsor SAY_DIALOG_3'),
(-1000831,'%s appears lost in contemplation.',0,2,0,0,'jonathan EMOTE_CONTEMPLATION'),
(-1000832,'I am ashamed, old friend. I know not what I do anymore. It is not you that would dare bring shame to the heroes of legend - it is I. It is I and the rest of these corrupt politicians. They fill our lives with empty promises, unending lies.',0,0,0,1,'jonathan SAY_DIALOG_4'),
(-1000833,'We shame our ancestors. We shame those lost to us... forgive me, Reginald.',0,0,0,1,'jonathan SAY_DIALOG_5'),
(-1000834,'Dear friend, you honor them with your vigilant watch. You are steadfast in your allegiance. I do not doubt for a moment that you would not give as great a sacrifice for your people as any of the heroes you stand under.',0,0,0,1,'reginald windsor SAY_DIALOG_6'),
(-1000835,'Now, it is time to bring her reign to an end, Marcus. Stand down, friend.',0,0,0,1,'reginald windsor SAY_DIALOG_7'),
(-1000836,'Stand down! Can you not see that heroes walk among us?',0,0,0,5,'jonathan SAY_DIALOG_8'),
(-1000837,'Move aside! Let them pass!',0,0,0,5,'jonathan SAY_DIALOG_9'),
(-1000838,'Reginald Windsor is not to be harmed! He shall pass through untouched!',0,1,0,22,'jonathan SAY_DIALOG_10'),
(-1000839,'Go, Reginald. May the light guide your hand.',0,0,0,1,'jonathan SAY_DIALOG_11'),
(-1000840,'Thank you, old friend. You have done the right thing.',0,0,0,1,'reginald windsor SAY_DIALOG_12'),
(-1000841,'Follow me, friends. To Stormwind Keep!',0,0,0,0,'reginald windsor SAY_DIALOG_13'),
(-1000842,'Light be with you, sir.',0,0,0,66,'guard SAY_1'),
(-1000843,'We are but dirt beneath your feet, sir.',0,0,0,66,'guard SAY_2'),
(-1000844,'...nerves of thorium.',0,0,0,66,'guard SAY_3'),
(-1000845,'Make way!',0,0,0,66,'guard SAY_4'),
(-1000846,'A living legend...',0,0,0,66,'guard SAY_5'),
(-1000847,'A moment I shall remember for always.',0,0,0,66,'guard SAY_6'),
(-1000848,'You are an inspiration to us all, sir.',0,0,0,66,'guard SAY_7'),
(-1000849,'Be brave, friends. The reptile will thrash wildly. It is an act of desperation. When you are ready, give me the word.',0,0,0,25,'reginald windsor SAY_BEFORE_KEEP'),
(-1000850,'Onward!',0,0,0,5,'reginald windsor SAY_GO_TO_KEEP'),
(-1000851,'Majesty, run while you still can. She is not what you think her to be...',0,0,0,1,'reginald windsor SAY_IN_KEEP_1'),
(-1000852,'To the safe hall, your majesty.',0,0,0,1,'bolvar SAY_IN_KEEP_2'),
(-1000853,'The masquerade is over, Lady Prestor. Or should I call you by your true name... Onyxia...',0,0,0,25,'reginald windsor SAY_IN_KEEP_3'),
(-1000854,'%s laughs.',0,2,0,11,'prestor EMOTE_IN_KEEP_LAUGH'),
(-1000855,'You will be incarcerated and tried for treason, Windsor. I shall watch with glee as they hand down a guilty verdict and sentence you to death by hanging...',0,0,0,1,'prestor SAY_IN_KEEP_4'),
(-1000856,'And as your limp body dangles from the rafters, I shall take pleasure in knowing that a mad man has been put to death. After all, what proof do you have? Did you expect to come in here and point your fingers at royalty and leave unscathed?',0,0,0,6,'prestor SAY_IN_KEEP_5'),
(-1000857,'You will not escape your fate, Onyxia. It has been prophesied - a vision resonating from the great halls of Karazhan. It ends now...',0,0,0,1,'reginald windsor SAY_IN_KEEP_6'),
(-1000858,'%s reaches into his pack and pulls out the encoded tablets...',0,2,0,0,'reginald windsor EMOTE_IN_KEEP_REACH'),
(-1000859,'The Dark Irons thought these tablets to be encoded. This is not any form of coding, it is the tongue of ancient dragon.',0,0,0,1,'reginald windsor SAY_IN_KEEP_7'),
(-1000860,'Listen, dragon. Let the truth resonate throughout these halls.',0,0,0,1,'reginald windsor SAY_IN_KEEP_8'),
(-1000861,'%s reads from the tablets. Unknown, unheard sounds flow through your consciousness',0,2,0,0,'reginald windsor EMOTE_IN_KEEP_READ'),
(-1000862,'%s gasps.',0,2,0,0,'bolvar EMOTE_IN_KEEP_GASP'),
(-1000863,'Curious... Windsor, in this vision, did you survive? I only ask because one thing that I can and will assure is your death. Here and now.',0,0,0,1,'onyxia SAY_IN_KEEP_9'),
(-1000864,'Dragon filth! Guards! Guards! Seize this monster!',0,1,0,22,'bolvar SAY_IN_KEEP_1'),
(-1000865,'Yesss... Guards, come to your lord\'s aid!',0,0,0,1,'onyxia SAY_IN_KEEP_10'),
(-1000866,'DO NOT LET HER ESCAPE!',0,0,0,1,'reginald windsor SAY_IN_KEEP_11'),
(-1000867,'Was this fabled, Windsor? If it was death that you came for then the prophecy has been fulfilled. May your consciousness rot in the Twisting Nether. Finish the rest of these meddlesome insects, children. Bolvar, you have been a pleasureable puppet.',0,0,0,0,'onyxia SAY_IN_KEEP_12'),
(-1000868,'You have failed him, mortalsss... Farewell!',0,1,0,0,'onyxia SAY_IN_KEEP_12'),
(-1000869,'Reginald... I... I am sorry.',0,0,0,0,'bolvar SAY_IN_KEEP_13'),
(-1000870,'Bol... Bolvar... the medallion... use...',0,0,0,0,'reginald windsor SAY_IN_KEEP_14'),
(-1000871,'%s dies.',0,2,0,0,'reginald windsor EMOTE_IN_KEEP_DIE'),
(-1000872,'%s hisses',0,2,0,0,'reginald windsor EMOTE_GUARD_TRANSFORM'),

(-1000873,'I know the way, insect. There is no need to prod me as if I were cattle.',0,0,0,1,'grark SAY_START'),
(-1000874,'Surely you do not think that you will get away with this incursion. They will come for me and you shall pay for your insolence.',0,0,0,1,'grark SAY_PAY'),
(-1000875,'RUN THEM THROUGH BROTHERS!',0,0,0,5,'grark SAY_FIRST_AMBUSH_START'),
(-1000876,'I doubt you will be so lucky the next time you encounter my brethren.',0,0,0,1,'grark SAY_FIRST_AMBUSH_END'),
(-1000877,'They come for you, fool!',0,0,0,5,'grark SAY_SEC_AMBUSH_START'),
(-1000878,'What do you think you accomplish from this, fool? Even now, the Blackrock armies make preparations to destroy your world.',0,0,0,1,'grark SAY_SEC_AMBUSH_END'),
(-1000879,'On darkest wing they fly. Prepare to meet your end!',0,0,0,5,'grark SAY_THIRD_AMBUSH_START'),
(-1000880,'The worst is yet to come!',0,0,0,1,'grark SAY_THIRD_AMBUSH_END'),
(-1000881,'%s laughs.',0,2,0,11,'grark EMOTE_LAUGH'),
(-1000882,'Time to make your final stand, Insect.',0,0,0,0,'grark SAY_LAST_STAND'),
(-1000883,'Kneel, Grark',0,0,0,1,'lexlort SAY_LEXLORT_1'),
(-1000884,'Grark Lorkrub, you have been charged and found guilty of treason against Horde. How you plead is unimportant. High Executioner Nuzrak, step forward.',0,0,0,1,'lexlort SAY_LEXLORT_2'),
(-1000885,'%s raises his massive axe over Grark.',0,2,0,27,'nuzark EMOTE_RAISE_AXE'),
(-1000886,'%s raises his hand and then lowers it.',0,2,0,0,'lexlort EMOTE_LOWER_HAND'),
(-1000887,'End him...',0,0,0,0,'lexlort SAY_LEXLORT_3'),
(-1000888,'You, soldier, report back to Kargath at once!',0,0,0,1,'lexlort SAY_LEXLORT_4'),
(-1000889,'%s submits.',0,2,0,0,'grark EMOTE_SUBMIT'),
(-1000890,'You have come to play? Then let us play!',0,0,0,0,'grark SAY_AGGRO'),

(-1000891,'Let\'s do this... Just keep me covered and I\'ll deliver the package.',0,0,0,0,'demolitionist SAY_INTRO'),
(-1000892,'I\'m under attack! I repeat, I am under attack!',0,0,0,0,'demolitionist SAY_ATTACK_1'),
(-1000893,'I need to find a new line of work.',0,0,0,0,'demolitionist SAY_ATTACK_2'),
(-1000894,'By the second sun of K\'aresh, look at this place! I can only imagine what Salhadaar is planning. Come on, let\'s keep going.',0,0,0,1,'demolitionist SAY_STAGING_GROUNDS'),
(-1000895,'With this much void waste and run off, a toxic void horror can\'t be too far behind.',0,0,0,0,'demolitionist SAY_TOXIC_HORROR'),
(-1000896,'Look there, fleshling! Salhadaar\'s conduits! He\'s keeping well fed...',0,0,0,1,'demolitionist SAY_SALHADAAR'),
(-1000897,'Alright, keep me protected while I plant this disruptor. This shouldn\'t take very long...',0,0,0,0,'demolitionist SAY_DISRUPTOR'),
(-1000898,'Protect the conduit! Stop the intruders!',0,0,0,0,'nexus stalkers SAY_PROTECT'),
(-1000899,'Done! Back up! Back up!',0,0,0,0,'demolitionist SAY_FINISH_1'),
(-1000900,'Looks like my work here is done. Report to the holo-image of Ameer over at the transporter.',0,0,0,1,'demolitionist SAY_FINISH_2'),

(-1000901,'Thanks, friend. Will you help me get out of here?',0,0,0,1,'vanguard SAY_VANGUARD_INTRO'),
(-1000902,'We\'re not too far from the Protectorate Watch Post, $N. This way!',0,0,0,1,'vanguard SAY_VANGUARD_START'),
(-1000903,'Commander! This fleshling rescued me!',0,0,0,0,'vanguard SAY_VANGUARD_FINISH'),
(-1000904,'%s salutes $N.',0,2,0,0,'vanguard EMOTE_VANGUARD_FINISH'),

(-1000905,'Ok, let\'s go!!',0,0,0,1,'therylune SAY_THERYLUNE_START'),
(-1000906,'I can make it the rest of the way. $N. THANKS!',0,0,0,1,'therylune SAY_THERYLUNE_START'),

(-1000907,'%s sniffs at the air. A tuber is near!',0,2,0,0,'domesticated felboar EMOTE_SNIFF_AIR'),
(-1000908,'%s starts to dig.',0,2,0,0,'domesticated felboar EMOTE_START_DIG'),
(-1000909,'%s squeals with glee at its discovery.',0,2,0,0,'domesticated felboar EMOTE_SQUEAL'),

(-1000910,'Shall we begin, my friend?',0,0,0,0,'anchorite truuen SAY_BEGIN'),
(-1000911,'This area is known to be full of foul Scourge. You may want to take a moment to prepare any defenses at your disposal.',0,0,0,0,'anchorite truuen SAY_FIRST_STOP'),
(-1000912,'Very well, let us continue.',0,0,0,0,'anchorite truuen SAY_CONTINUE'),
(-1000913,'Beware! We are attacked!',0,0,0,0,'anchorite truuen SAY_FIRST_ATTACK'),
(-1000914,'It must be the purity of the Mark of the Lightbringer that is drawing forth the Scourge to us. We must proceed with caution lest we overwhelmed!',0,0,0,0,'anchorite truuen SAY_PURITY'),
(-1000915,'We are beset upon again! Defend yourself!',0,0,0,0,'anchorite truuen SAY_SECOND_ATTACK'),
(-1000916,'The land truly needs to be cleansed by the Light! Let us continue on the tomb. It isn\'t far now.',0,0,0,0,'anchorite truuen SAY_CLEANSE'),
(-1000917,'Be welcome, friends!',0,0,0,0,'high priest thel\'danis SAY_WELCOME'),
(-1000918,'Thank you for coming in remembrance of me. Your efforts in recovering that symbol, while unnecessary, are certainly touching to an old man\'s heart.',0,0,0,0,'ghost of uther SAY_EPILOGUE_1'),
(-1000919,'Please, rise my friend. Keep the Blessing as a symbol of the strength of the Light and how heroes long gone might once again rise in each of us to inspire.',0,0,0,0,'ghost of uther SAY_EPILOGUE_2'),

(-1000948,'Well then, let\'s get this started. The longer we\'re here, the more damage the undead could be doing back in Hilsbrad.',0,0,0,0,'kinelory SAY_START'),
(-1000949,'All right, this is where we really have to be on our paws. Be ready!',0,0,0,0,'kinelory SAY_REACH_BOTTOM'),
(-1000950,'Attack me if you will, but you won\'t stop me from getting back to Quae.',0,0,0,0,'kinelory SAY_AGGRO_KINELORY'),
(-1000951,'You have my word that I shall find a use for your body after I\'ve killed you, Kinelory.',0,0,0,0,'jorell SAY_AGGRO_JORELL'),
(-1000952,'Watch my rear! I\'ll see what I can find in all this junk...',0,0,0,0,'kinelory SAY_WATCH_BACK'),
(-1000953,'%s begins rummaging through the apothecary\'s belongings.',0,2,0,0,'kinelory EMOTE_BELONGINGS'),
(-1000954,'I bet Quae\'ll think this is important. She\'s pretty knowledgeable about these things--no expert, but knowledgable.',0,0,0,0,'kinelory SAY_DATA_FOUND'),
(-1000955,'Okay, let\'s get out of here quick quick! Try and keep up. I\'m going to make a break for it.',0,0,0,0,'kinelory SAY_ESCAPE'),
(-1000956,'We made it! Quae, we made it!',0,0,0,0,'kinelory SAY_FINISH'),
(-1000957,'%s hands her pack to Quae.',0,2,0,0,'kinelory EMOTE_HAND_PACK'),

(-1000958,'Ok, let\'s get started.',0,0,0,0,'stinky ignatz SAY_STINKY_BEGIN'),
(-1000959,'Now let\'s look for the herb.',0,0,0,0,'stinky ignatz SAY_STINKY_FIRST_STOP'),
(-1000960,'Help! The beast is on me!',0,0,0,0,'stinky ignatz SAY_AGGRO_1'),
(-1000961,'Help! I\'m under attack!',0,0,0,0,'stinky ignatz SAY_AGGRO_2'),
(-1000962,'I can make it from here. Thanks, $N! And talk to my employer about a reward!',0,0,0,0,'stinky ignatz SAY_STINKY_END'),

(-1000963,'%s looks at you for a moment, then motions for you to follow.',0,2,0,0,'cenarion sparrowhawk EMOTE_FOLLOW'),
(-1000964,'%s surveys the ground for the buried raven stones.',0,2,0,0,'cenarion sparrowhawk EMOTE_SURVEY'),
(-1000965,'%s locates a buried raven stone.',0,2,0,0,'cenarion sparrowhawk EMOTE_LOCATE'),

(-1000966,'I WILL CRUSH YOU LIKE A GNAT!',0,1,0,0,'reth\'hedron SAY_LOW_HP'),
(-1000967,'You will regret this, mortal! Reth\'hedron will return... I will have my vengeance!',0,1,0,53,'reth\'hedron SAY_EVENT_END'),

(-1000968,'Very well. Before we head down there, take a moment to prepare yourself.',0,0,0,1,'drijya SAY_DRIJYA_START'),
(-1000969,'Let\'s proceed at a brisk pace.',0,0,0,0,'drijya SAY_DRIJYA_1'),
(-1000970,'We\'ll start at that first energy pylon, straight ahead. Remember, try to keep them off of me.',0,0,0,1,'drijya SAY_DRIJYA_2'),
(-1000971,'Keep them off me!',0,0,0,0,'drijya SAY_DRIJYA_3'),
(-1000972,'I\'m done with this pylon. On to the next.',0,0,0,1,'drijya SAY_DRIJYA_4'),
(-1000973,'Alright, pylon two down. Now for the heat mainfold.',0,0,0,1,'drijya SAY_DRIJYA_5'),
(-1000974,'That should do it. The teleporter should blow any second now!',0,0,0,5,'drijya SAY_DRIJYA_6'),
(-1000975,'Ok, let\'s get out of here!',0,0,0,1,'drijya SAY_DRIJYA_7'),
(-1000976,'Thank you, $n! I couldn\'t have done it without you. You\'ll let Gahruj know?',0,0,0,1,'drijya SAY_DRIJYA_COMPLETE'),

(-1000977,'Oh, it\'s on now! But you thought I\'d be alone too, huh?!',0,0,0,0,'tapoke slim jahn SAY_AGGRO'),
(-1000978,'Okay, okay! No need to get all violent. I\'ll talk. I\'ll talk!',0,0,0,20,'tapoke slim jahn SAY_DEFEAT'),
(-1000979,'Whoa! This is way more than what I bargained for, you\'re on your own, Slim!',0,0,0,0,'slim\'s friend SAY_FRIEND_DEFEAT'),
(-1000980,'I have a few notes from the job back at my place. I\'ll get them and then meet you back in the inn.',0,0,0,1,'tapoke slim jahn SAY_NOTES'),

(-1000981,'It is time. The rite of exorcism will now commence...',0,0,0,0,'anchorite barada SAY_EXORCISM_1'),
(-1000982,'Prepare yourself. Do not allow the ritual to be interrupted or we may lose our patient...',0,0,0,1,'anchorite barada SAY_EXORCISM_2'),
(-1000983,'Keep away. The fool is mine.',0,0,0,0,'colonel jules SAY_EXORCISM_3'),
(-1000984,'Back, foul beings of darkness! You have no power here!',0,0,0,0,'anchorite barada SAY_EXORCISM_4'),
(-1000985,'No! Not yet! This soul is ours!',0,0,0,0,'colonel jules SAY_EXORCISM_5'),
(-1000986,'Back! I cast you back... corrupter of faith! Author of pain! Do not return, or suffer the same fate as you did here today!',0,0,0,2,'anchorite barada SAY_EXORCISM_6'),
(-1000987,'I... must not...falter!',0,0,0,0,'anchorite barada SAY_EXORCISM_RANDOM_1'),
(-1000988,'Be cleansed with Light, human! Let not the demonic corruption overwhelm you.',0,0,0,0,'anchorite barada SAY_EXORCISM_RANDOM_2'),
(-1000989,'Back, foul beings of darkness! You have no power here!',0,0,0,0,'anchorite barada SAY_EXORCISM_RANDOM_3'),
(-1000990,'This is fruitless, draenei! You and your little helper cannot wrest control of this pathetic human. He is mine!',0,0,0,0,'colonel jules SAY_EXORCISM_RANDOM_4'),
(-1000991,'I see your ancestors, Anchorite! They writhe and scream in the darkness... they are with us!',0,0,0,0,'colonel jules SAY_EXORCISM_RANDOM_5'),
(-1000992,'I will tear your soul into morsels and slow roast them over demon fire!',0,0,0,0,'colonel jules SAY_EXORCISM_RANDOM_6'),

(-1000993,'It\'s on! $N, meet my fists. Fists, say hello to $N.',0,0,0,0,'dorius stonetender SAY_AGGRO_1'),
(-1000994,'I\'m about to open a can on this $N.',0,0,0,0,'dorius stonetender SAY_AGGRO_2'),

(-1000995,'Fhwoor go now, $N. Get ark, come back.',0,0,0,0,'fhwoor SAY_ESCORT_START'),
(-1000996,'Take moment... get ready.',0,0,0,0,'fhwoor SAY_PREPARE'),
(-1000997,'We go!',0,0,0,0,'fhwoor SAY_CAMP_ENTER'),
(-1000998,'Uh oh...',0,0,0,0,'fhwoor SAY_AMBUSH'),
(-1000999,'Ha ha, squishy naga!',0,0,0,0,'fhwoor SAY_AMBUSH_CLEARED'),
(-1001000,'Fhwoor do good!',0,0,0,0,'fhwoor SAY_ESCORT_COMPLETE'),

(-1001001,'We must leave before more are alerted.',0,0,0,1,'kurenai captive SAY_KUR_START'),
(-1001002,'It\'s an ambush! Defend yourself!',0,0,0,5,'kurenai captive SAY_KUR_AMBUSH_1'),
(-1001003,'We are surrounded!',0,0,0,5,'kurenai captive SAY_KUR_AMBUSH_2'),
(-1001004,'Up ahead is the road to Telaar. We will split up when we reach the fork as they will surely send more Murkblood after us. Hopefully one of us makes it back to Telaar alive.',0,0,0,25,'kurenai captive SAY_KUR_COMPLETE'),
(-1001005,'Farewell, stranger. Your heroics will be remembered by my people. Now, hurry to Telaar!',0,0,0,1,'kurenai captive SAY_KUR_COMPLETE_2'),

(-1001006,'Thanks for your help. Let\'s get out of here!',0,0,0,1,'skyguard prisoner SAY_ESCORT_START'),
(-1001007,'Let\'s keep moving. I don\'t like this place.',0,0,0,1,'skyguard prisoner SAY_AMBUSH_END'),
(-1001008,'Thanks again. Sergeant Doryn will be glad to hear he has one less scout to replace this week.',0,0,0,1,'skyguard prisoner SAY_ESCORT_COMPLETE'),
(-1001009,'Death to our enemies!',0,0,0,0,'skettis wing guard SAY_AMBUSH_1'),
(-1001010,'No one escapes Skettis!',0,0,0,0,'skettis wing guard SAY_AMBUSH_2'),
(-1001011,'Skettis prevails!',0,0,0,0,'skettis wing guard SAY_AMBUSH_3'),
(-1001012,'You\'ll go nowhere, Skyguard scum!',0,0,0,0,'skettis wing guard SAY_AMBUSH_4'),

(-1001072,'Something is wrong with the Highlord. Do something!',0,0,0,1,'scarlet cavalier SAY_CAVALIER_WORRY_1'),
(-1001073,'Hey, what is going on over there? Sir, are you alright?',0,0,0,1,'scarlet cavalier SAY_CAVALIER_WORRY_2'),
(-1001074,'What the....',0,0,0,1,'scarlet cavalier SAY_CAVALIER_WORRY_3'),
(-1001075,'Sir?',0,0,0,1,'scarlet cavalier SAY_CAVALIER_WORRY_4'),
(-1001076,'NOOOOOOOOOOOOO!',0,1,0,15,'taelan fordring SAY_SCARLET_COMPLETE_1'),
(-1001077,'I will lead us through Hearthglen to the forest\'s edge. From there, you will take me to my father.',0,0,0,1,'taelan fordring SAY_SCARLET_COMPLETE_2'),
(-1001078,'Remove your disguise, lest you feel the bite of my blade when the fury has taken control.',0,0,0,1,'taelan fordring SAY_ESCORT_START'),
(-1001079,'Halt.',0,0,0,0,'taelan fordring SAY_TAELAN_MOUNT'),
(-1001080,'%s calls for his mount.',0,2,0,22,'taelan fordring EMOTE_TAELAN_MOUNT'),
(-1001081,'It\'s not much further. The main road is just up ahead.',0,0,0,1,'taelan fordring SAY_REACH_TOWER'),
(-1001082,'You will not make it to the forest\'s edge, Fordring.',0,0,0,1,'isillien SAY_ISILLIEN_1'),
(-1001083,'Isillien!',0,1,0,25,'taelan fordring SAY_ISILLIEN_2'),
(-1001084,'This is not your fight, stranger. Protect yourself from the attacks of the Crimson Elite. I shall battle the Grand Inquisitor.',0,0,0,1,'taelan fordring SAY_ISILLIEN_3'),
(-1001085,'You disappoint me, Taelan. I had plans for you... grand plans. Alas, it was only a matter of time before your filthy bloodline would catch up with you.',0,0,0,1,'isillien SAY_ISILLIEN_4'),
(-1001086,'It is as they say: Like father, like son. You are as weak of will as Tirion... perhaps more so. I can only hope my assassins finally succeeded in ending his pitiful life.',0,0,0,1,'isillien SAY_ISILLIEN_5'),
(-1001087,'The Grand Crusader has charged me with destroying you and your newfound friends, Taelan, but know this: I do this for pleasure, not of obligation or duty.',0,0,0,1,'isillien SAY_ISILLIEN_6'),
(-1001088,'%s calls for his guardsman.',0,2,0,22,'isillien EMOTE_ISILLIEN_ATTACK'),
(-1001089,'The end is now, Fordring.',0,0,0,25,'isillien SAY_ISILLIEN_ATTACK'),
(-1001090,'Enough!',0,0,0,0,'isillien SAY_KILL_TAELAN_1'),
(-1001091,'%s laughs.',0,2,0,11,'isillien EMOTE_ISILLIEN_LAUGH'),
(-1001092,'Did you really believe that you could defeat me? Your friends are soon to join you, Taelan.',0,0,0,0,'isillien SAY_KILL_TAELAN_2'),
(-1001093,'%s turns his attention towards you.',0,2,0,0,'isillien EMOTE_ATTACK_PLAYER'),
(-1001094,'What have you done, Isillien? You once fought with honor, for the good of our people... and now... you have murdered my boy...',0,0,0,0,'tirion fordring SAY_TIRION_1'),
(-1001095,'Tragic. The elder Fordring lives on... You are too late, old man. Retreat back to your cave, hermit, unless you wish to join your son in the Twisting Nether.',0,0,0,0,'isillien SAY_TIRION_2'),
(-1001096,'May your soul burn in anguish, Isillien! Light give me strength to battle this fiend.',0,0,0,15,'tirion fordring SAY_TIRION_3'),
(-1001097,'Face me, coward. Face the faith and strength that you once embodied.',0,0,0,25,'tirion fordring SAY_TIRION_4'),
(-1001098,'Then come, hermit!',0,0,0,0,'isillien SAY_TIRION_5'),
(-1001099,'A thousand more like him exist. Ten thousand. Should one fall, another will rise to take the seat of power.',0,0,0,0,'tirion fordring SAY_EPILOG_1'),
(-1001100,'%s falls to one knee.',0,2,0,16,'tirion fordring EMOTE_FALL_KNEE'),
(-1001101,'Look what they did to my boy.',0,0,0,5,'tirion fordring SAY_EPILOG_2'),
(-1001102,'%s holds the limp body of Taelan Fordring and softly sobs.',0,2,0,0,'tirion fordring EMOTE_HOLD_TAELAN'),
(-1001103,'Too long have I sat idle, gripped in this haze... this malaise, lamenting what could have been... what should have been.',0,0,0,0,'tirion fordring SAY_EPILOG_3'),
(-1001104,'Your death will not have been in vain, Taelan. A new Order is born on this day... an Order which will dedicate itself to extinguising the evil that plagues this world. An evil that cannot hide behind politics and pleasantries.',0,0,0,0,'tirion fordring SAY_EPILOG_4'),
(-1001105,'This I promise... This I vow...',0,0,0,15,'tirion fordring SAY_EPILOG_5'),

(-1001106,'Don\'t forget to get my bell out of the chest here. And remember, if do happen to wander off, just ring it and I\'ll find you again.',0,0,0,1,'shay leafrunner SAY_ESCORT_START'),
(-1001107,'Are we taking the scenic route?',0,0,0,0,'shay leafrunner SAY_WANDER_1'),
(-1001108,'Oh, what a beautiful flower over there...',0,0,0,0,'shay leafrunner SAY_WANDER_2'),
(-1001109,'Are you sure this is the right way? Maybe we should go this way instead...',0,0,0,0,'shay leafrunner SAY_WANDER_3'),
(-1001110,'Hmmm, I wonder what\'s over this way?',0,0,0,0,'shay leafrunner SAY_WANDER_4'),
(-1001111,'This is quite an adventure!',0,0,0,0,'shay leafrunner SAY_WANDER_DONE_1'),
(-1001112,'Oh, I wandered off again. I\'m sorry.',0,0,0,0,'shay leafrunner SAY_WANDER_DONE_2'),
(-1001113,'The bell again, such a sweet sound.',0,0,0,0,'shay leafrunner SAY_WANDER_DONE_3'),
(-1001114,'%s begins to wander off.',0,2,0,0,'shay leafrunner EMOTE_WANDER'),
(-1001115,'Oh, here you are, Rockbiter! I\'m sorry, I know I\'m not supposed to wander off.',0,0,0,1,'shay leafrunner SAY_EVENT_COMPLETE_1'),
(-1001116,'I\'m so glad yer back Shay. Please, don\'t ever run off like that again! What would I tell yer parents if I lost ya?',0,0,0,1,'rockbiter SAY_EVENT_COMPLETE_2'),

(-1001141,'Nope, not here...',0,0,0,0,'stinky ignatz SAY_SECOND_STOP'),
(-1001142,'There must be one around here somewhere...',0,0,0,0,'stinky ignatz SAY_THIRD_STOP_1'),
(-1001143,'Ah, there\'s one!',0,0,0,0,'stinky ignatz SAY_THIRD_STOP_2'),
(-1001144,'Come, $N! Let\'s go over there and collect it!',0,0,0,0,'stinky ignatz SAY_THIRD_STOP_3'),
(-1001145,'Ok, let\'s get out of here!',0,0,0,0,'stinky ignatz SAY_PLANT_GATHERED'),
(-1001146,'I\'m glad you\'re here! Because I need your help!!',0,0,0,0,'stinky ignatz SAY_AGGRO_3'),
(-1001147,'Look out! The $N attacks!',0,0,0,0,'stinky ignatz SAY_AGGRO_4'),

(-1001148,'I am ready, $N. Let\'s find my equipment and get out of here. I think I know where it is.',0,0,0,1,'captured arko\'narin SAY_ESCORT_START'),
(-1001149,'Oh my! Look at this... all these candles. I\'m sure they\'re used for some terrible ritual or dark summoning. We best make haste.',0,0,0,18,'captured arko\'narin SAY_FIRST_STOP'),
(-1001150,'There! Over there!',0,0,0,25,'captured arko\'narin SAY_SECOND_STOP'),
(-1001151,'You will not stop me from escaping here, $N!',0,0,0,0,'captured arko\'narin SAY_AGGRO'),
(-1001152,'All I need now is a golden lasso.',0,0,0,0,'captured arko\'narin SAY_EQUIPMENT'),
(-1001153,'DIE DEMON DOGS!',0,0,0,0,'captured arko\'narin SAY_ESCAPE'),
(-1001154,'Ah! Fresh air at last! I never thought I\'d see the day.',0,0,0,4,'captured arko\'narin SAY_FRESH_AIR'),
(-1001155,'BETRAYER!',0,1,0,0,'spirit of trey lightforge SAY_BETRAYER'),
(-1001156,'What was that?! Trey? TREY?',0,0,0,22,'captured arko\'narin SAY_TREY'),
(-1001157,'You kept me in the cell for too long, monster!',0,0,0,0,'captured arko\'narin SAY_ATTACK_TREY'),
(-1001158,'No! My friend... what\'s happened? This is all my fault...',0,0,0,18,'captured arko\'narin SAY_ESCORT_COMPLETE'),

(-1001159,'Please, help me to get through this cursed forest, $r.',0,0,0,0,'arei SAY_ESCORT_START'),
(-1001160,'This creature suffers from the effect of the fel... We must end its misery.',0,0,0,0,'arei SAY_ATTACK_IRONTREE'),
(-1001161,'The corruption of the fel has not left any of the creatures of Felwood untouched, $N. Please, be on your guard.',0,0,0,0,'arei SAY_ATTACK_TOXIC_HORROR'),
(-1001162,'I sense the taint of corruption upon this $N. Help me detroy it.',0,0,0,0,'arei SAY_EXIT_WOODS'),
(-1001163,'That I must fight against my own kind deeply saddens me.',0,0,0,0,'arei SAY_CLEAR_PATH'),
(-1001164,'I can sense it now, $N. Ashenvale lies down this path.',0,0,0,0,'arei SAY_ASHENVALE'),
(-1001165,'I feel... something strange...',0,0,0,0,'arei SAY_TRANSFORM'),
(-1001166,'$N my form has now changed! The true strength of my spirit is returing to me now... The cursed grasp of the forest is leaving me.',0,0,0,0,'arei SAY_LIFT_CURSE'),
(-1001167,'Thank you, $N. Now my spirit will finally be at peace.',0,0,0,0,'arei SAY_ESCORT_COMPLETE'),

(-1001168,'The naga torture the spirits of water. They invoke chaos and destruction!',0,0,0,0,'wilda SAY_WIL_PROGRESS_4'),
(-1001169,'The naga do not respect nature. They twist and corrupt it to meet their needs. They live to agitate the spirits.',0,0,0,0,'wilda SAY_WIL_PROGRESS_5'),

(-1001170,'Time only has meaning to mortals, insect. Dimensius is infinite!',0,1,0,0,'dimensius SAY_AGGRO'),
(-1001171,'I hunger! Feed me the power of this forge, my children!',0,1,0,0,'dimensius SAY_SUMMON'),

(-1001172,'Spare my life! I will tell you about Arelion\'s secret.',0,0,0,0,'magister_aledis SAY_ALEDIS_DEFEAT'),

-- warning ids in range -1001173 to -1001190 are used in WOTLK

(-1001191,'Hey, you call yourself a body guard? Get to work and protect us...',0,0,0,0,'SAY_CORK_AMBUSH1'),
(-1001192,'Mister body guard, are you going to earn your money or what?',0,0,0,0,'SAY_CORK_AMBUSH2'),
(-1001193,'You\'re fired! <Cough...Cork clears throat.> I mean, help!',0,0,0,0,'SAY_CORK_AMBUSH3'),
(-1001194,'Blast those stupid centaurs! Sigh - well, it seems you kept your bargain. Up the road you shall find Smeed Scrabblescrew, he has your money.',0,0,0,1,'SAY_CORK_END'),
(-1001195,'Eeck! Demons hungry for the kodos!',0,0,0,0,'SAY_RIGGER_AMBUSH1'),
(-1001196,'What am I paying you for? The kodos are nearly dead!',0,0,0,0,'SAY_RIGGER_AMBUSH2'),
(-1001197,'Wow! We did it... not sure why we thought we needed the likes of you. Nevertheless, speak with Smeed Srablescrew; he will give you your earnings!',0,0,0,0,'SAY_RIGGER_END'),

(-1001198,'Cover me!',0,0,0,5,'demolitionist_legoso SAY_ESCORT_2'),
(-1001199,'It won\'t be much longer, $n. Just keep them off me while I work.',0,0,0,133,'demolitionist_legoso SAY_ESCORT_3'),
(-1001200,'That\'ll do it! Quickly, take cover!',0,0,0,5,'demolitionist_legoso SAY_ESCORT_4'),
(-1001201,'3...',0,0,0,0,'demolitionist_legoso SAY_ESCORT_COUNT_3'),
(-1001202,'2...',0,0,0,0,'demolitionist_legoso SAY_ESCORT_COUNT_2'),
(-1001203,'1...',0,0,0,0,'demolitionist_legoso SAY_ESCORT_COUNT_1'),
(-1001204,'Don\'t get too excited, hero, that was the easy part. The challenge lies ahead! Let\'s go.',0,0,0,1,'demolitionist_legoso SAY_ESCORT_CONTINUE'),
(-1001205,'What in the Nether is that?!?!',0,0,0,5,'demolitionist_legoso SAY_ESCORT_5'),
(-1001206,'Be ready for anything, $n.',0,0,0,1,'demolitionist_legoso SAY_ESCORT_6'),
(-1001207,'Blessed Light! She\'s siphoning energy right out of the Vector Coil!',0,0,0,34,'demolitionist_legoso SAY_ESCORT_7'),
(-1001208,'Cover me, we have to do this quickly. Once I blow the support on this side, it will disrupt the energy beams and she\'ll break out! I doubt very much that she\'ll be happy to see us.',0,0,0,1,'demolitionist_legoso SAY_ESCORT_8'),
(-1001209,'I\'ve almost got it! Just a little more time...',0,0,0,0,'demolitionist_legoso SAY_ESCORT_9'),
(-1001210,'Take cover and be ready for the fight of your life, $n!',0,0,0,5,'demolitionist_legoso SAY_ESCORT_10'),
(-1001211,'Holy mother of O\'ros!',0,0,0,5,'demolitionist_legoso SAY_ESCORT_AGGRO'),
(-1001212,'I... I can\'t believe it\'s over. You did it! You\'ve destroyed the blood elves and their leader!',0,0,0,1,'demolitionist_legoso SAY_ESCORT_COMPLETE_1'),
(-1001213,'Get back to Blood Watch. I\'ll see you there...',0,0,0,1,'demolitionist_legoso SAY_ESCORT_COMPLETE_2'),

(-1001214,'%s becomes unstable with brimming energy.',0,2,0,0,'living_flare EMOTE_UNSTABLE'),
(-1001215,'%s releases its energy, engulfing its surroundings in flames!',0,2,0,0,'living_flare EMOTE_BURST'),

(-1001216,'The last thing I remember is the ship falling and us getting into the pods. I\'ll go see how I can help. Thank you!',0,0,7,0,'draenei_survivor SAY_HEAL1'),
(-1001217,'Where am I? Who are you? Oh no! What happened to the ship?',0,0,7,0,'draenei_survivor SAY_HEAL2'),
(-1001218,'$C You saved me! I owe you a debt that I can never repay. I\'ll go see if I can help the others.',0,0,7,0,'draenei_survivor SAY_HEAL3'),
(-1001219,'Ugh... what is this place? Is that all that\'s left of the ship over there?',0,0,7,0,'draenei_survivor SAY_HEAL4'),
(-1001220,'Many thanks to you, $c. I''d best get to the crash site and see how I can help out. Until we meet again.',0,0,7,0,'draenei_survivor SAY_HEAL5'),
(-1001221,'Huh? What happened? Oh... my head feels like it''s going to explode! I''d best get back to the crash site.',0,0,7,0,'draenei_survivor SAY_HEAL6'),
(-1001222,'Oh, the pain...',0,0,7,0,'draenei_survivor SAY_HELP1'),
(-1001223,'Everything hurts. Please, make it stop...',0,0,7,0,'draenei_survivor SAY_HELP2'),
(-1001224,'Ughhh... I hurt. Can you help me?',0,0,7,0,'draenei_survivor SAY_HELP3'),
(-1001225,'I don''t know if I can make it. Please help me...',0,0,7,0,'draenei_survivor SAY_HELP4'),
(-1001226,'%s is drawn to the ghost magnet...',0,2,0,0,'Magrami Spectre on spawn 1'),
(-1001227,'%s is angered!',0,2,0,0,'Magrami Spectre on spawn 2'),
(-1001228,'The Avatar of Terokk has been defeated! Death to Terokk! Death to Skettis!',0,0,7,0,'Defender Grashna on Avatar of Terokk death'),

-- warning ids in range -1001229 to -1001241 are used in WOTLK

(-1001242,'%s cracks his knuckles.',0,2,0,23,'larry EMOTE_KNUCKLES'),
(-1001243,'Is the way clear? Let\'s get out while we can, $N.',0,0,0,0,'kayra SAY_START'),
(-1001244,'Looks like we won\'t get away so easy. Get ready!',0,0,0,0,'kayra SAY_AMBUSH1'),
(-1001245,'Let\'s keep moving. We\'re not safe here!',0,0,0,0,'kayra SAY_PROGRESS1'),
(-1001246,'Look out, $N! Enemies ahead!',0,0,0,0,'kayra SAY_AMBUSH2'),
(-1001247,'We\'re almost to the refuge! Let\'s go.',0,0,0,0,'kayra SAY_PROGRESS2'),
(-1001248,'I can see my fellow druids from here.  Thank you, $n.  I''m sure Ysiel will reward you for your actions!',0,0,0,0,'kayra SAY_END'),
(-1001249,'You won''t escape us, druid!',0,0,0,0,'Umbrafen Slavebinder SAY_AMBUSH2'),
(-1001250,'%s is silenced by the venemous sting.',0,2,0,0,'npc_simone EMOTE_SILENCE'),
(-1001251,'%s is stricken by a virulent poison.',0,2,0,0,'npc_artorius EMOTE_POISON'),
(-1001252,'%s is immobilized.',0,2,0,0,'npc_solenor EMOTE_IMMOBILIZED'),
(-1001253,'You dare interfere with this being''s testing? The battle must be fought alone! You shall all pay for this interference!',0,0,0,0,'the_cleaner SAY_CLEANER_AGGRO'),
(-1001254,'We''re here for you, lost brother.  It is custom to offer you a chance to repent before you are destroyed.  We offer you this chance, as the naaru''s law commands.', '0', '0', '0', '0','SAY_ADYEN_1'),
(-1001255,'Do not make me laugh.  Is this the mighty Aldor army that''s come to defeat me?', '0', '1', '0', '153','SAY_SOCRETHAR_1'),
(-1001256,'We may be few, Socrethar, but our faith is strong.  Something you will never understand.  Now that custom has been served, prepare to meet your end.', '0', '0', '0', '0','SAY_ADYEN_2'),
(-1001257,'Yes, let us settle this.  Before we begin, however, there''s somebody I''d like you to meet.', '0', '1', '0', '1','SAY_SOCRETHAR_2'),
(-1001258,'How... how could you?!', '0', '0', '0', '0','SAY_ORELIS_1'),
(-1001259,'My heart has been filled with hate since our sworn enemies were allowed into our city.  I knew the one known as Voren''thal before he was called a Seer.  It was by his hand that my brother was slain.', '0', '0', '0', '0','SAY_KAYLAAN_1'),
(-1001260,'I turned that hate on the Illidari and the Burning Legion... but they weren''t the ones who betrayed us.  We were the naaru''s chosen!  We lived and died for them!', '0', '0', '0', '0','SAY_KAYLAAN_2'),
(-1001261,'Once the hatred in my heart became focused, everything became clear to me.  Shattrath must be destroyed and the naaru with it.', '0', '0', '0', '0','SAY_KAYLAAN_3'),
(-1001262,'Socrethar is clouding your mind, Kaylaan!  You do not mean these words!  I remember training you when you were but a youngling.  Your will was strong even then!', '0', '0', '0', '0','SAY_ADYEN_3'),
(-1001263,'You are wrong, Adyen.  My mind has never been clearer.', '0', '0', '0', '0','SAY_KAYLAAN_4'),
(-1001264,'Slay these dogs, Kaylaan!  Earn your place in the Burning Legion!', '0', '1', '0', '25','SAY_SOCRETHAR_3'),
(-1001265,'What are you waiting for?  Finish them, young one.  Let your hatred burn!', '0', '1', '0', '53','SAY_SOCRETHAR_4'),
(-1001266,'Yes... master.', '0', '0', '0', '0','SAY_KAYLAAN_5'),
(-1001267,'Teacher...', '0', '0', '0', '0','SAY_KAYLAAN_6'),
(-1001268,'The Light wants its lost son back, Socrethar.', '0', '0', '0', '0','SAY_ISHANAH_1'),
(-1001269,'I offer myself in exchange.  You will have Ishanah, the High Priestess of the Aldor, as your prisoner if you release Kaylaan from your dark grasp.', '0', '0', '0', '0','SAY_ISHANAH_2'),
(-1001270,'You foolish old hag... Why would I do that when I can have you both?', '0', '1', '0', '0','SAY_SOCRETHAR_5'),
(-1001271,'No!  What have I done?', '0', '1', '0', '0','SAY_KAYLAAN_7'),
(-1001272,'Light grant me strength!', '0', '1', '0', '0','SAY_KAYLAAN_8'),
(-1001273,'Oh, please!  This is sickening; I''m going to have to kill you all myself.', '0', '1', '0', '0','SAY_SOCRETHAR_6'),
(-1001274,'Now you''re gonna get it good, $n!', '0', '0', '0', '0','dashel stonefist SAY_STONEFIST_1'),
(-1001275,'Okay, okay! Enough fighting. No one else needs to get hurt.', '0', '0', '0', '0','dashel stonefist SAY_STONEFIST_2'),
(-1001276,'It''s okay, boys. Back off. You''ve done enough. I''ll meet up with you later.', '0', '0', '0', '0','dashel stonefist SAY_STONEFIST_3'),
(-1001277,'That could have gone better. $n, come here, please. I have something I need you to take care of for me.','0','4','0','0','Ambassador Sunsorrow - During Lament of the Highborne script'),
(-1001278,'Who calls me to this world?  The stars are not yet aligned... my powers fail me!  You will pay for this!',0,0,0,1,'Terokk SAY_SPAWN'),
(-1001279,'Show me what you''re made of, $n!',0,6,0,1,'Terokk SAY_CHOSEN_ONE'),
(-1001280,'Kwa! You cannot kill me, I am immortal!',0,6,0,1,'Terokk SAY_DIVINE_SHIELD'),
(-1001281,'%s becomes enraged as his shield shatters.',0,3,0,1,'Terokk SAY_ENRAGE'),
(-1001282,'Enemy sighted!  Fall into formation and prepare for bombing maneuvers!',0,6,0,1,'Skyguard Ace SAY_SPAWN'),
(-1001283,'Quickly! Use the flames and support the ground troops. Its ancient magic should cleanse Terokk''s shield.',0,6,0,1,'Skyguard Ace SAY_FLAMES'),
(-1001284,'They did it!  Enemy down!  Return to base!',0,6,0,1,'Skyguard Ace SAY_TEROKK_DOWN'),
(-1001285,'Work is da poop! NO MORE!',0,0,0,15,'Dosobedient Dragonmaw Peon SAY_IDLE1'),
(-1001286,'Me no work no more!',0,0,0,15,'Dosobedient Dragonmaw Peon SAY_IDLE2'),
(-1001287,'HEY! No more booterang! Me sorry! Me work!',0,0,0,34,'Dosobedient Dragonmaw Peon SAY_BOOTERANG1'),
(-1001288,'ARGH! BOOTERANG!',0,0,0,34,'Dosobedient Dragonmaw Peon SAY_BOOTERANG2'),
(-1001289,'OWWWW! Ok, ok, me go back to work!',0,0,0,34,'Dosobedient Dragonmaw Peon SAY_BOOTERANG3'),
(-1001290,'WHY IT PUT DA BOOTERANG ON DA SKIN?? WHY??',0,0,0,34,'Dosobedient Dragonmaw Peon SAY_BOOTERANG4'),
(-1001291,'AYAYA! One day me have dat booterang...',0,0,0,34,'Dosobedient Dragonmaw Peone SAY_BOOTERANG5'),
(-1001292,'OOF! Booterang hurted me! Me tink work better den booterang!',0,0,0,34,'Dosobedient Dragonmaw Peon SAY_BOOTERANG6'),
(-1001293,'The Dragonmaw must be stopped...',0,1,0,22,'Commander Arcus SAY_EVENT_ACCEPT'),
(-1001294,'Stand tall, soldiers. Show them no quarter!',0,0,0,5,'Commander Arcus SAY_EVENT_START'),
(-1001295,'Victory to the Aldor! The Dragonmaw have been defeated!',0,1,0,0,'Commander Arcus SAY_EVENT_END'),
(-1001296,'Defenders, show these mongrels the fury of a Scryer!',0,1,0,22,'Commander Hobb SAY_EVENT_ACCEPT'),
(-1001297,'Stand tall, soldiers. Show them no quarter!',0,0,0,1,'Commander Hobb SAY_EVENT_START'),
(-1001298,'Victory to the Scryers! The Dragonmaw have been defeated!',0,1,0,0,'Commander Hobb SAY_EVENT_END'),
(-1001299,'I may be old but I can still take on a young whippersnapper like you, $n. Try not to fall behind...',0,0,0,0,'Murg "Oldie" Muckjaw SAY_MUCKJAW_START'),
(-1001300,'Well, you won... I guess.',0,0,0,0,'Murg "Oldie" Muckjaw SAY_MUCKJAW_END'),
(-1001301,'Trope will show you how to fly like a Dragonmaw... You will show Trope how to die like a scrub.',0,0,0,1,'Trope the Filth-Belcher SAY_TROPE_START'),
(-1001302,'You did well. Certainly a surprise to Trope... Report back to Ja''y.',0,0,0,0,'Trope the Filth-Belcher SAY_TROPE_END'),
(-1001303,'Let''s get this over with...',0,0,0,1,'Corlok the Vet SAY_START_CORLOK'),
(-1001304,'You put up a hell of a fight, newbie. Hell of a fight...',0,0,0,1,'Corlok the Vet SAY_END_CORLOK'),
(-1001305,'I''m taking this back to the old school. I''ll be the Alliance and you be Frostwolf Village. BOMBS AWAY!',0,0,0,1,'Wing Commander Ichman SAY_START_ICHMAN'),
(-1001306,'Thank you for that... It was humbling to be served in such a manner.',0,0,0,1,'Wing Commander Ichman SAY_END_ICHMAN'),
(-1001307,'You''re in for a rough ride, $n. I hope you''ve already made funeral arrangements.',0,0,0,1,'Wing Commander Mulverick SAY_START_MULVERICK'),
(-1001308,'You''re the best I''ve ever seen. I can''t believe I''m saying this but you might have a chance against Skyshatter. And hey, if that doesn''t go so well you can be my wing man...',0,0,0,1,'Wing Commander Mulverick SAY_END_MULVERICK'),
(-1001309,'Prepare a funeral pyre! $n has challenged Skyshatter!',0,1,0,1,'Captain Skyshatter - SAY_START_SKYSHATTER'),
(-1001310,'I weep for you, $n. You really have no idea what you''ve gotten yourself into...',0,0,0,1,'Captain Skyshatter - SAY_MID_SKYSHATTER'),
(-1001311,'I... I am undone... The new top orc is $n!',0,1,0,1,'Captain Skyshatter - SAY_END_SKYSHATTER');

-- -1 010 000 Classic texts

-- -1 015 000 TBC texts
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1015001, '%s lets loose a low, gultural growl.',0,2,0,0,'Enraged Netherwing Drake - EMOTE on script spell hit'),
(-1015002, 'You will never get the Heart of Fury!  Its power belongs to Illidan!',0,1,0,0,'Shadowlord Deathwail - yell on descent'),
(-1015003, '%s retrieves the Heart of Fury.',0,2,0,0,'Shadowlord Deathwail - grabs heart'),
(-1015004, 'Master... I\'ve failed you...',0,1,0,0,'Shadowlord Deathwail - death'),
(-1015005,'The power of Light compels you! Back to your pit!',0,0,0,0,'anchorite barada SAY_EXORCISM_RANDOM_6'),
(-1015006,'All is lost, Anchorite! Abandon what hope remains.',0,0,0,0,'colonel jules SAY_EXORCISM_RANDOM_2'),
(-1015007,'The Light is my guide... it is my sustenance!',0,0,0,0,'anchorite barada SAY_EXORCISM_RANDOM_7'),
(-1015008,'Ah! Cease the incantations, Anchorite! Cease, or I will show you such pain that your pathetic people have never imagined!',0,0,0,0,'colonel jules SAY_EXORCISM_RANDOM_3'),
(-1015009, 'You... will... leave... this... man!',0,0,0,0,'anchorite barada SAY_EXORCISM_RANDOM_2'),
(-1015010, 'In the name of the Light! It is Light that commands you! It is Light that flung you to the depths of darkness!',0,0,0,0,'anchorite barada SAY_EXORCISM_RANDOM_4'),
(-1015011, 'You will not succeed, mortal! This shell will lie decrepit, blistered and bleeding before I am done with it. And its spirit will be long cast into darkness.',0,0,0,0,'colonel jules SAY_EXORCISM_RANDOM_4'),
(-1015012,'From the darkest night shall rise again the raven, shall take flight in the shadows, shall reveal the nature of its kind. Prepare yourself for its coming, for the faithful shall be elevated to take flight with the raven, the rest be forgotten to walk upon the ground, clipped wings and shame.', 0,4,0,0,'First Prophecy for Whispers of the Raven God'),
(-1015013,'Steel your minds and guard your thoughts. The dark wings will cloud and consume the minds of the weak, a flock of thralls whose feet may never leave the ground.', 0,4,0,0,'Second Prophecy for Whispers of the Raven God'),
(-1015014,'The old blood will flow once again with the coming of the raven, the return of the darkness in the skies. Scarlet night, and the rise of the old.', 0,4,0,0,'Third Prophecy for Whispers of the Raven God'),
(-1015015,'The raven was struck down once for flying too high, unready. The eons have prepared the Dark Watcher for its ascent, to draw the dark cloak across the horizon.', 0,4,0,0,'Fourth Prophecy for Whispers of the Raven God'),
(-1015016,'Argh! I will shred your soul and grind it to dust!',0,1,0,0,'Skulloc Soulgrinder on last unbanishing phase.'),
(-1015017,'Weak, little bugs!  Your souls aren''t worth eating...',0,1,0,0,'Skulloc Soulgrinder on last unbanishing phase.'),
(-1015018,'%s brushes up against $n and farts like only an ogre can.',0,2,0,0,'Generic Blades Edge Ogre /fart emote response'),
(-1015019,'Me like to fart, too!',0,0,0,1,'Generic Blades Edge Ogre /fart emote response'),
(-1015020,'The %s cowers at the sight of his angered $g king : queen;.',0,2,0,0,'Generic Blades Edge Ogre /angry emote response'),
(-1015021,'Shh... quiet, it da new $g king : queen;.',0,0,0,0,'Bloodmaul/Bladespire Supplicant LoS text'),
(-1015022,'$G King : Queen; $n.',0,0,0,0,'Bloodmaul/Bladespire Supplicant LoS text'),
(-1015023,'All hail, $n, the new King of the ogres!!!',0,6,0,22,'Mog''dorg the Wizened on quest end Into the Soulgrinder'),
(-1015024,'Aw, me not think it work out between us.',0,0,0,1,'Generic Blades Edge Ogre /kiss emote response'),
(-1015025,'What me do wrong, my $g king : queen;?',0,0,0,16,'Generic Blades Edge Ogre /point emote response'),
(-1015026,'$G Him : Her; so tiny!  How $g him : her; rule?',0,0,0,0,'Bloodmaul/Bladespire Supplicant LoS text'),
(-1015027,'$G Him : Her; look too pretty to be da ruler.',0,0,0,0,'Bloodmaul/Bladespire Supplicant LoS text'),
(-1015028,'Me live to serve.',0,0,0,0,'Bloodmaul/Bladespire Supplicant LoS text'),
(-1015029,'For the Deceiver! For Kil''jaeden!',0,0,0,0,'Trelopades on aggro 1'),
(-1015030,'Only flesh and blood...',0,0,0,0,'Trelopades on aggro 2'),
(-1015031, 'Onward, Scryers!  Show Illidan\'s lackeys the temper of our steel!', 0, 1, 0, 0, 'Onward Scryers'),
(-1015032, 'Forward, vindicators!  Drive these demons from our sacred temple!', 0, 1, 0, 0, 'Forward vindicators');
-- -1 020 000 WOTLK texts

-- -1 033 000 SHADOWFANG KEEP
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1033000,'Follow me and I\'ll open the courtyard door for you.',0,0,7,1,'prisoner ashcrombe SAY_FREE_AS'),
(-1033001,'I have just the spell to get this door open. Too bad the cell doors weren\'t locked so haphazardly.',0,0,7,1,'prisoner ashcrombe SAY_OPEN_DOOR_AS'),
(-1033002,'There it is! Wide open. Good luck to you conquering what lies beyond. I must report back to the Kirin Tor at once!',0,0,7,1,'prisoner ashcrombe SAY_POST_DOOR_AS'),

(-1033003,'Free from this wretched cell at last! Let me show you to the courtyard....',0,0,1,1,'prisoner adamant SAY_FREE_AD'),
(-1033004,'You are indeed courageous for wanting to brave the horrors that lie beyond this door.',0,0,1,1,'prisoner adamant SAY_OPEN_DOOR_AD'),
(-1033005,'There we go!',0,0,1,1,'prisoner adamant SAY_POST1_DOOR_AD'),
(-1033006,'Good luck with Arugal. I must hurry back to Hadrec now.',0,0,1,1,'prisoner adamant SAY_POST2_DOOR_AD'),

(-1033007,'About time someone killed the wretch.',0,0,1,1,'prisoner adamant SAY_BOSS_DIE_AD'),
(-1033008,'For once I agree with you... scum.',0,0,7,1,'prisoner ashcrombe SAY_BOSS_DIE_AS'),

(-1033009,'I have changed my mind loyal servants, you do not need to bring the prisoner all the way to my study, I will deal with him here and now.',0,0,0,1,'arugal SAY_INTRO_1'),
(-1033010,'Vincent!  You and your pathetic ilk will find no more success in routing my sons and I than those beggardly remnants of the Kirin Tor.',0,0,0,0,'arugal SAY_INTRO_2'),
(-1033011,'If you will not serve my Master with your sword and knowledge of his enemies...',0,0,0,1,'arugal SAY_INTRO_3'),
(-1033012,'Your moldering remains will serve ME as a testament to what happens when one is foolish enough to trespass in my domain!\n',0,0,0,0,'arugal SAY_INTRO_4'),

(-1033013,'Who dares interfere with the Sons of Arugal?',5791,1,0,0,'boss_arugal YELL_FENRUS'),
(-1033014,'%s vanishes.',0,2,0,0,'prisoner ashcrombe EMOTE_VANISH_AS'),
(-1033015,'%s fumbles with the rusty lock on the courtyard door.',0,2,0,0,'prisoner adamant EMOTE_UNLOCK_DOOR_AD'),
(-1033016,'Arrrgh!',0,0,0,0,'deathstalker vincent SAY_VINCENT_DIE'),
(-1033017,'You, too, shall serve!',5793,1,0,0,'boss_arugal YELL_AGGRO'),
(-1033018,'Another Falls!',5795,1,0,0,'boss_arugal YELL_KILLED_PLAYER'),
(-1033019,'Release your rage!',5797,1,0,0,'boss_arugal YELL_COMBAT'),
(-1033020,'I can\'t believe it! You\'ve destroyed my pack... Now face my wrath!',0,1,0,0,'wolf master nandos YELL_PACK_DEAD');

-- -1 034 000 STOCKADES

-- -1 036 000 DEADMINES
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1036000,'You there! Check out that noise.',5775,6,7,0,'smite INST_SAY_ALARM1'),
(-1036001,'We\'re under attack!  A vast, ye swabs! Repel the invaders!',5777,6,7,0,'smite INST_SAY_ALARM2'),
(-1036002,'You land lubbers are tougher than I thought! I\'ll have to improvise!',5778,0,0,21,'smite SAY_PHASE_2'),
(-1036003,'D\'ah! Now you\'re making me angry!',5779,0,0,15,'smite SAY_PHASE_3');

-- -1 043 000 WAILING CAVERNS
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1043000,'At last! Naralex can be awakened! Come aid me, brave adventurers!',0,6,0,0,'Disciple of Naralex - SAY_INTRO'),
(-1043001,'I must make the necessary preparations before the awakening ritual can begin. You must protect me!',0,0,0,0,'SAY_PREPARE'),
(-1043002,'These caverns were once a temple of promise for regrowth in the Barrens. Now, they are the halls of nightmares.',0,0,0,0,'Disciple of Naralex - SAY_FIRST_CORNER'),
(-1043003,'Come. We must continue. There is much to be done before we can pull Naralex from his nightmare.',0,0,0,0,'Disciple of Naralex - SAY_CONTINUE'),
(-1043004,'Within this circle of fire I must cast the spell to banish the spirits of the slain Fanglords.',0,0,0,0,'Disciple of Naralex - SAY_CIRCLE_BANISH'),
(-1043005,'The caverns have been purified. To Naralex\'s chamber we go!',0,0,0,0,'Disciple of Naralex - SAY_PURIFIED'),
(-1043006,'Beyond this corridor, Naralex lies in fitful sleep. Let us go awaken him before it is too late.',0,0,0,0,'Disciple of Naralex - SAY_NARALEX_CHAMBER'),
(-1043007,'Protect me brave souls as I delve into the Emerald Dream to rescue Naralex and put an end to this corruption!',0,1,0,0,'Disciple of Naralex - SAY_BEGIN_RITUAL'),
(-1043008,'%s begins to perform the awakening ritual on Naralex.',0,2,0,0,'Disciple of Naralex - EMOTE_RITUAL_BEGIN'),
(-1043009,'%s tosses fitfully in troubled sleep.',0,2,0,0,'Naralex - EMOTE_NARALEX_AWAKE'),
(-1043010,'%s writhes in agony. The Disciple seems to be breaking through.',0,2,0,0,'Naralex - EMOTE_BREAK_THROUGH'),
(-1043011,'%s dreams up a horrendous vision. Something stirs beneath the murky waters.',0,2,0,0,'Naralex - EMOTE_VISION'),
(-1043012,'This $N is a minion from Naralex\'s nightmare no doubt!.',0,0,0,0,'Disciple of Naralex - SAY_MUTANUS'),
(-1043013,'I AM AWAKE, AT LAST!',5789,1,0,0,'Naralex - SAY_NARALEX_AWAKE'),
(-1043014,'At last! Naralex awakes from the nightmare.',0,0,0,0,'Disciple of Naralex - SAY_AWAKE'),
(-1043015,'Ah, to be pulled from the dreaded nightmare! I thank you, my loyal Disciple, along with your brave companions.',0,0,0,0,'Naralex - SAY_NARALEX_THANKYOU'),
(-1043016,'We must go and gather with the other Disciplies. There is much work to be done before I can make another attempt to restore the Barrens. Farewell, brave souls!',0,0,0,0,'Naralex - SAY_FAREWELL'),
(-1043017,'Attacked! Help get this $N off of me!',0,0,0,0,'Disciple of Naralex - SAY_AGGRO_1'),
(-1043018,'Help!',0,0,0,0,'Disciple of Naralex - SAY_AGGRO_2'),
(-1043019,'Deal with this $N! I need to prepare to awake Naralex!',0,0,0,0,'Disciple of Naralex - SAY_AGGRO_3');

-- -1 047 000 RAZORFEN KRAUL
INSERT INTO script_texts (entry,content_default,sound,type,LANGUAGE,emote,comment) VALUES
(-1047000,'Woo hoo! Finally getting out of here. It\'s going to be rough though. Keep your eyes peeled for trouble.',0,0,0,0,'willix SAY_READY'),
(-1047001,'Up there is where Charlga Razorflank resides. Blasted old crone.',0,0,0,25,'willix SAY_1'),
(-1047002,'There\'s blueleaf tuber in this trench! It\'s like gold waiting to be mined I tell you!',0,0,0,0,'willix SAY_2'),
(-1047003,'There could be danger around every corner here.',0,0,0,0,'willix SAY_3'),
(-1047004,'I don\'t see how these foul animals live in this place... sheesh it smells!',0,0,0,0,'willix SAY_4'),
(-1047005,'I think I see a way for us to get out of this big twisted mess of a bramble.',0,0,0,0,'willix SAY_5'),
(-1047006,'Glad to be out of that wretched trench. Not much nicer up here though!',0,0,0,0,'willix SAY_6'),
(-1047007,'Finally! I\'ll be glad to get out of this place.',0,0,0,0,'willix SAY_7'),
(-1047008,'I think I\'ll rest a moment and catch my breath before heading back to Ratchet. Thanks for all the help!',0,0,0,0,'willix SAY_END'),
(-1047009,'$N heading this way fast! To arms!',0,0,0,0,'willix SAY_AGGRO_1'),
(-1047010,'Eek! $N coming right at us!',0,0,0,0,'willix SAY_AGGRO_2'),
(-1047011,'Egads! $N on me!',0,0,0,0,'willix SAY_AGGRO_3'),
(-1047012,'Help! Get this $N off of me!',0,0,0,0,'willix SAY_AGGRO_4');

-- -1 048 000 BLACKFATHOM DEEPS

-- -1 070 000 ULDAMAN
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1070000,'REUSE ME',0,0,0,0,'REUSE ME'),
(-1070001,'Who dares awaken Archaedas? Who dares the wrath of the makers!',5855,1,0,0,'archaedas SAY_AGGRO'),
(-1070002,'Awake ye servants, defend the discs!',5856,1,0,0,'archaedas SAY_AWAKE_GUARDIANS'),
(-1070003,'To my side, brothers. For the makers!',5857,1,0,0,'archaedas SAY_AWAKE_WARDERS'),
(-1070004,'Reckless mortal.',5858,1,0,0,'archaedas SAY_UNIT_SLAIN'),
(-1070005,'%s breaks free from his stone slumber!',0,2,0,0,'archaedas EMOTE_BREAK_FREE');

-- -1 090 000 GNOMEREGAN
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1090000,'With your help, I can evaluate these tunnels.',0,0,0,1,'emi shortfuse SAY_START'),
(-1090001,'Let\'s see if we can find out where these Troggs are coming from.... and put a stop to the invasion!',0,0,0,1,'emi shortfuse SAY_INTRO_1'),
(-1090002,'Such devastation... what a horrible mess...',0,0,0,5,'emi shortfuse SAY_INTRO_2'),
(-1090003,'It\'s quiet here....',0,0,0,1,'emi shortfuse SAY_INTRO_3'),
(-1090004,'...too quiet.',0,0,0,1,'emi shortfuse SAY_INTRO_4'),
(-1090005,'Look! Over there at the tunnel wall!',0,0,0,25,'emi shortfuse SAY_LOOK_1'),
(-1090006,'Trogg incursion! Defend me while I blast the hole closed!',0,0,0,5,'emi shortfuse SAY_HEAR_1'),
(-1090007,'Get this, $n off of me!',0,0,0,0,'emi shortfuse SAY_AGGRO_1'),
(-1090008,'I don\'t think one charge is going to cut it. Keep fending them off!',0,0,0,0,'emi shortfuse SAY_CHARGE_1'),
(-1090009,'The charges are set. Get back before they blow!',0,0,0,5,'emi shortfuse SAY_CHARGE_2'),
(-1090010,'Incoming blast in 10 seconds!',0,1,0,5,'emi shortfuse SAY_BLOW_1_10'),
(-1090011,'Incoming blast in 5 seconds. Clear the tunnel! Stay back!',0,1,0,5,'emi shortfuse SAY_BLOW_1_5'),
(-1090012,'FIRE IN THE HOLE!',0,1,0,25,'emi shortfuse SAY_BLOW_1'),
(-1090013,'Well done! Without your help I would have never been able to thwart that wave of troggs.',0,0,0,4,'emi shortfuse SAY_FINISH_1'),
(-1090014,'Did you hear something?',0,0,0,6,'emi shortfuse SAY_LOOK_2'),
(-1090015,'I heard something over there.',0,0,0,25,'emi shortfuse SAY_HEAR_2'),
(-1090016,'More troggs! Ward them off as I prepare the explosives!',0,0,0,0,'emi shortfuse SAY_CHARGE_3'),
(-1090017,'The final charge is set. Stand back!',0,0,0,1,'emi shortfuse SAY_CHARGE_4'),
(-1090018,'10 seconds to blast! Stand back!!!',0,1,0,5,'emi shortfuse SAY_BLOW_2_10'),
(-1090019,'5 seconds until detonation!!!!!',0,1,0,5,'emi shortfuse SAY_BLOW_2_5'),
(-1090020,'Nice work! I\'ll set off the charges to prevent any more troggs from making it to the surface.',0,0,0,1,'emi shortfuse SAY_BLOW_SOON'),
(-1090021,'FIRE IN THE HOLE!',0,1,0,0,'emi shortfuse SAY_BLOW_2'),
(-1090022,'Superb! Because of your help, my people stand a chance of re-taking our beloved city. Three cheers to you!',0,0,0,0,'emi shortfuse SAY_FINISH_2'),

(-1090023,'We come from below! You can never stop us!',0,1,0,1,'grubbis SAY_GRUBBIS_SPAWN'),

(-1090024,'Usurpers! Gnomeregan is mine!',5807,1,0,0,'thermaplugg SAY_AGGRO'),
(-1090025,'My machines are the future! They\'ll destroy you all!',5808,1,0,0,'thermaplugg  SAY_PHASE'),
(-1090026,'Explosions! MORE explosions! I\'ve got to have more explosions!',5809,1,0,0,'thermaplugg  SAY_BOMB'),
(-1090027,'...and stay dead! He got served',5810,1,0,0,'thermaplugg  SAY_SLAY'),

(-1090028,'$n attacking! Help!',0,0,0,0,'emi shortfuse SAY_AGGRO_2');

-- -1 109 000 SUNKEN TEMPLE
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1109000,'The walls of the chamber tremble. Something is happening...',0,2,0,0,'malfurion stormrage EMOTE_MALFURION'),
(-1109001,'Be steadfast, champion. I know why it is that you are here and I know what it is that you seek. Eranikus will not give up the shard freely. He has been twisted... twisted by the same force that you seek to destroy.',0,0,0,0,'malfurion stormrge SAY_MALFURION1'),
(-1109002,'Are you really surprised? Is it hard to believe that the power of an Old God could reach even inside the Dream? It is true - Eranikus, Tyrant of the Dream, wages a battle against us all. The Nightmare follows in his wake of destruction.',0,0,0,0,'malfurion stormrge SAY_MALFURION2'),
(-1109003,'Understand this, Eranikus wants nothing more than to be brought to Azeroth from the Dream. Once he is out, he will stop at nothing to destroy my physical manifestation. This, however, is the only way in which you could recover the scepter shard.',0,0,0,0,'malfurion stormrge SAY_MAFLURION3'),
(-1109004,'You will bring him back into this world, champion.',0,0,0,0,'malfurion Stormrge SAY_MALFURION4'),

(-1109005,'The shield be down! Rise up Atal\'ai! Rise up!',5861,6,0,0,'jammalan SAY_JAMMALAN_INTRO'),

(-1109006,'HAKKAR LIVES!',5870,1,0,0,'avatar SAY_AVATAR_BRAZIER_1'),
(-1109007,'I TASTE THE BLOOD OF LIFE!',5868,1,0,0,'avatar SAY_AVATAR_BRAZIER_2'),
(-1109008,'I DRAW CLOSER TO YOUR WORLD!',5867,1,0,0,'avatar SAY_AVATAR_BRAZIER_3'),
(-1109009,'I AM NEAR!',5869,1,0,0,'avatar SAY_AVATAR_BRAZIER_4'),
(-1109010,'I AM HERE!',0,1,0,0,'avatar SAY_AVATAR_SPAWN');

-- -1 129 000 RAZORFEN DOWNS
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1129000,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1129001,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1129002,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1129003,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1129004,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1129005,'All right, stay close. These fiends will jump right out of the shadows at you if you let your guard down.',0,0,0,0,'belnistrasz SAY_READY'),
(-1129006,'Okay, here we go. It\'s going to take about five minutes to shut this thing down through the ritual. Once I start, keep the vermin off of me or it will be the end of us all!',0,0,0,0,'belnistrasz SAY_START_RIT'),
(-1129007,'You\'ll rue the day you crossed me, $N',0,0,0,0,'belnistrasz SAY_AGGRO_1'),
(-1129008,'Incoming $N - look sharp, friends!',0,0,0,0,'belnistrasz SAY_AGGRO_2'),
(-1129009,'Three minutes left -- I can feel the energy starting to build! Keep up the solid defense!',0,1,0,0,'belnistrasz SAY_3_MIN'),
(-1129010,'Just two minutes to go! We\'re half way there, but don\'t let your guard down!',0,1,0,0,'belnistrasz SAY_2_MIN'),
(-1129011,'One more minute! Hold on now, the ritual is about to take hold!',0,1,0,0,'belnistrasz SAY_1_MIN'),
(-1129012,'That\'s it -- we made it! The ritual is set in motion, and idol fires are about to go out for good! You truly are the heroes I thought you would be!',0,1,0,4,'belnistrasz SAY_FINISH');

-- -1 189 000 SCARLET MONASTERY
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1189000,'Ah, I have been waiting for a real challenge!',5830,1,0,0,'herod SAY_AGGRO'),
(-1189001,'Blades of Light!',5832,1,0,0,'herod SAY_WHIRLWIND'),
(-1189002,'Light, give me strength!',5833,1,0,0,'herod SAY_ENRAGE'),
(-1189003,'Hah, is that all?',5831,1,0,0,'herod SAY_KILL'),
(-1189004,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1189005,'Infidels! They must be purified!',5835,1,0,0,'mograine SAY_MO_AGGRO'),
(-1189006,'Unworthy!',5836,1,0,0,'mograine SAY_MO_KILL'),
(-1189007,'At your side, milady!',5837,1,0,0,'mograine SAY_MO_RESSURECTED'),

(-1189008,'What, Mograine has fallen? You shall pay for this treachery!',5838,1,0,0,'whitemane SAY_WH_INTRO'),
(-1189009,'The Light has spoken!',5839,1,0,0,'whitemane SAY_WH_KILL'),
(-1189010,'Arise, my champion!',5840,1,0,0,'whitemane SAY_WH_RESSURECT'),

(-1189011,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1189012,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1189013,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1189014,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1189015,'The bastard got what he deserved.',0,0,1,0,'vishas SAY_TRIGGER_VORREL'),

(-1189016,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1189017,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1189018,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1189019,'You will not defile these mysteries!',5842,1,0,0,'doan SAY_AGGRO'),
(-1189020,'Burn in righteous fire!',5843,1,0,0,'doan SAY_SPECIALAE'),

(-1189021,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1189022,'It is over, your search is done! Let fate choose now, the righteous one.',11961,1,0,0,'horseman SAY_ENTRANCE'),
(-1189023,'Here\'s my body, fit and pure! Now, your blackened souls I\'ll cure!',12567,1,0,0,'horseman SAY_REJOINED'),
(-1189024,'So eager you are for my blood to spill, yet to vanquish me this my head you must kill!',11969,1,0,0,'horseman SAY_BODY_DEFEAT'),
(-1189025,'Over here, you idiot!',12569,1,0,0,'horseman SAY_LOST_HEAD'),
(-1189026,'Harken, cur! Tis you I spurn! Now, $N, feel the burn!',12573,1,0,0,'horseman SAY_CONFLAGRATION'),
(-1189027,'Soldiers arise, stand and fight! Bring victory at last to this fallen knight!',11963,1,0,0,'horseman SAY_SPROUTING_PUMPKINS'),
(-1189028,'Your body lies beaten, battered and broken. Let my curse be your own, fate has spoken.',11962,1,0,0,'horseman SAY_SLAY'),
(-1189029,'This end have I reached before. What new adventure lies in store?',11964,1,0,0,'horseman SAY_DEATH'),
(-1189030,'%s laughs.',0,2,0,0,'horseman EMOTE_LAUGH'),
(-1189031,'Horseman rise...',0,0,0,0,'horseman SAY_PLAYER1'),
(-1189032,'Your time is night...',0,0,0,0,'horseman SAY_PLAYER2'),
(-1189033,'You felt death once...',0,0,0,0,'horseman SAY_PLAYER3'),
(-1189034,'Now, know demise!',0,0,0,0,'horseman SAY_PLAYER4'),

(-1189035,'The master has fallen! Avenge him my brethren!',5834,1,0,0,'trainee SAY_TRAINEE_SPAWN'),

(-1189036,'Bow down! Kneel before the Ashbringer! A new dawn approaches, brother and sisters! Our message will be delivered to the filth of this world through the chosen one!',0,6,0,0,'mograine SAY_ASHBRINGER_ENTRANCE');

-- -1 209 000 ZUL'FARRAK
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1209000,'How dare you enter my sanctum!',0,0,0,0,'zumrah SAY_INTRO'),
(-1209001,'Sands consume you!',5872,1,14,0,'zumrah SAY_AGGRO'),
(-1209002,'Fall!',5873,1,14,0,'zumrah SAY_KILL'),
(-1209003,'Come to me, my children!',0,0,8,0,'zumrah SAY_SUMMON');

-- -1 229 000 BLACKROCK SPIRE
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1229000,'%s begins to regain its strength!',0,2,0,0,'pyroguard EMOTE_BEGIN'),
(-1229001,'%s is nearly at full strength!',0,2,0,0,'pyroguard EMOTE_NEAR'),
(-1229002,'%s regains its power and breaks free of its bonds!',0,2,0,0,'pyroguard EMOTE_FULL'),
(-1229003,'Ha! Ha! Ha! Thank you for freeing me, fools. Now let me repay you by charring the flesh from your bones.',0,1,0,0,'pyroguard SAY_FREE'),

(-1229004,'Excellent... it would appear as if the meddlesome insects have arrived just in time to feed my legion. Welcome, mortals!',0,1,0,1,'nefarius SAY_INTRO_1'),
(-1229005,'Let not even a drop of their blood remain upon the arena floor, my children. Feast on their souls!',0,1,0,1,'nefarius SAY_INTRO_2'),
(-1229006,'Foolsss...Kill the one in the dress!',0,1,0,0,'nefarius SAY_NEFARIUS_TAUNT1'),
(-1229007,'Sire, let me join the fray! I shall tear their spines out with my bare hands!',0,1,0,1,'rend SAY_REND_TAUNT1'),
(-1229008,'Concentrate your attacks upon the healer!',0,1,0,0,'nefarius SAY_NEFARIUS_TAUNT2'),
(-1229009,'Inconceivable!',0,1,0,0,'nefarius SAY_NEFARIUS_TAUNT3'),
(-1229010,'Do not force my hand, children! I shall use your hides to line my boots.',0,1,0,0,'nefarius SAY_NEFARIUS_TAUNT4'),
(-1229011,'Defilers!',0,1,0,0,'rend SAY_REND_TAUNT2'),
(-1229012,'Impossible!',0,1,0,0,'rend SAY_REND_TAUNT3'),
(-1229013,'Your efforts will prove fruitless. None shall stand in our way!',0,1,0,0,'nefarius SAY_NEFARIUS_TAUNT5'),
(-1229014,'THIS CANNOT BE!!! Rend, deal with these insects.',0,1,0,1,'nefarius SAY_NEFARIUS_LOSE1'),
(-1229015,'With pleasure...',0,1,0,0,'rend SAY_REND_ATTACK'),
(-1229016,'The Warchief shall make quick work of you, mortals. Prepare yourselves!',0,1,0,25,'nefarius SAY_WARCHIEF'),
(-1229017,'Taste in my power!',0,1,0,0,'nefarius SAY_BUFF_GYTH'),
(-1229018,'Your victory shall be short lived. The days of both the Alliance and Horde are coming to an end. The next time we meet shall be the last.',0,1,0,1,'nefarius SAY_VICTORY'),

(-1229019,'%s is knocked off his drake!',0,2,0,0,'rend EMOTE_KNOCKED_OFF'),

(-1229020,'Intruders are destroying our eggs! Stop!!',0,1,0,0,'rookery hatcher - SAY_ROOKERY_EVENT_START'),

(-1229021,'I promise you an eternity of dung clean up duty for this failure!',0,1,0,0,'nefarius SAY_NEFARIUS_TAUNT6'),
(-1229022,'Use the freezing breath, imbecile!',0,1,0,0,'nefarius SAY_NEFARIUS_TAUNT7'),
(-1229023,'I will wear your skin as a fashion accessory!',0,1,0,0,'nefarius SAY_NEFARIUS_TAUNT8'),
(-1229024,'Flee while  you still have chance, mortals. You will pray for a swift death should I enter the arena.',0,1,0,0,'rend SAY_REND_TAUNT3');

-- -1 230 000 BLACKROCK DEPTHS
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1230000,'Ah, hits the spot!',0,0,0,5,'rocknot SAY_GOT_BEER'),
(-1230001,'Come to aid the Throne!',0,1,0,0,'dagran SAY_AGGRO'),
(-1230002,'Hail to the king, baby!',0,1,0,0,'dagran SAY_SLAY'),
(-1230003,'You have challenged the Seven, and now you will die!',0,0,0,0,'doomrel SAY_DOOMREL_START_EVENT'),

(-1230004,'The Sons of Thaurissan shall watch you perish in the Ring of the Law!',0,1,0,5,'grimstone SAY_START_1'),
(-1230005,'You have been sentenced to death for crimes against the Dark Iron Nation!',0,1,0,25,'grimstone SAY_START_2'),
(-1230006,'Unleash the fury and let it be done!',0,1,0,15,'grimstone SAY_OPEN_EAST_GATE'),
(-1230007,'But your real punishment lies ahead.',0,1,0,1,'grimstone SAY_SUMMON_BOSS_1'),
(-1230008,'Haha! I bet you thought you were done!',0,1,0,153,'grimstone SAY_SUMMON_BOSS_2'),
(-1230009,'Good Riddance!',0,1,0,5,'grimstone SAY_OPEN_NORTH_GATE'),

(-1230010,'Thank you, $N! I\'m free!!!',0,0,0,0,'dughal SAY_FREE'),
(-1230011,'You locked up the wrong Marshal, $N. Prepare to be destroyed!',0,0,0,0,'windsor SAY_AGGRO_1'),
(-1230012,'I bet you\'re sorry now, aren\'t you?',0,0,0,0,'windsor SAY_AGGRO_2'),
(-1230013,'You better hold me back or $N is going to feel some prison house beatings.',0,0,0,0,'windsor SAY_AGGRO_3'),
(-1230014,'Let\'s get a move on. My gear should be in the storage area up this way...',0,0,0,0,'windsor SAY_START'),
(-1230015,'Check that cell, $N. If someone is alive in there, we need to get them out.',0,0,0,25,'windsor SAY_CELL_DUGHAL_1'),
(-1230016,'Good work! We\'re almost there, $N. This way.',0,0,0,0,'windsor SAY_CELL_DUGHAL_3'),
(-1230017,'This is it, $N. My stuff should be in that room. Cover me, I\'m going in!',0,0,0,0,'windsor SAY_EQUIPMENT_1'),
(-1230018,'Ah, there it is!',0,0,0,0,'windsor SAY_EQUIPMENT_2'),
(-1230019,'Can you feel the power, $N??? It\'s time to ROCK!',0,0,0,0,'reginald_windsor SAY__EQUIPMENT_3'),
(-1230020,'Now we just have to free Tobias and we can get out of here. This way!',0,0,0,0,'reginald_windsor SAY__EQUIPMENT_4'),
(-1230021,'Open it.',0,0,0,25,'reginald_windsor SAY_CELL_JAZ_1'),
(-1230022,'I never did like those two. Let\'s get moving.',0,0,0,0,'reginald_windsor SAY_CELL_JAZ_2'),
(-1230023,'Open it and be careful this time!',0,0,0,25,'reginald_windsor SAY_CELL_SHILL_1'),
(-1230024,'That intolerant dirtbag finally got what was coming to him. Good riddance!',0,0,0,66,'reginald_windsor SAY_CELL_SHILL_2'),
(-1230025,'Alright, let\'s go.',0,0,0,0,'reginald_windsor SAY_CELL_SHILL_3'),
(-1230026,'Open it. We need to hurry up. I can smell those Dark Irons coming a mile away and I can tell you one thing, they\'re COMING!',0,0,0,25,'reginald_windsor SAY_CELL_CREST_1'),
(-1230027,'He has to be in the last cell. Unless... they killed him.',0,0,0,0,'reginald_windsor SAY_CELL_CREST_2'),
(-1230028,'Get him out of there!',0,0,0,25,'reginald_windsor SAY_CELL_TOBIAS_1'),
(-1230029,'Excellent work, $N. Let\'s find the exit. I think I know the way. Follow me!',0,0,0,0,'reginald_windsor SAY_CELL_TOBIAS_2'),
(-1230030,'We made it!',0,0,0,4,'reginald_windsor SAY_FREE_1'),
(-1230031,'Meet me at Maxwell\'s encampment. We\'ll go over the next stages of the plan there and figure out a way to decode my tablets without the decryption ring.',0,0,0,1,'reginald_windsor SAY_FREE_2'),
(-1230032,'Thank you! I will run for safety immediately!',0,0,0,0,'tobias SAY_TOBIAS_FREE_1'),
(-1230033,'Finally!! I can leave this dump.',0,0,0,0,'tobias SAY_TOBIAS_FREE_2'),

(-1230034,'You\'ll pay for this insult, $c!',0,0,0,15,'coren direbrew SAY_AGGRO'),

(-1230035,'%s cries out an alarm!',0,2,0,0,'general_angerforge EMOTE_ALARM'),

(-1230036,'I want more ale! Give me more ale!',0,0,0,0,'rocknot SAY_MORE_BEER'),
(-1230037,'You\'ll pay for that!',0,0,0,0,'Grim Patron SAY_PISSED_PATRON_1'),
(-1230038,'No!',0,0,0,0,'Grim Patron SAY_PISSED_PATRON_2'),
(-1230039,'Oh! Now I\'m pissed!',0,0,0,0,'Grim Patron SAY_PISSED_PATRON_3'),
(-1230040,'Violence! Property damage! None shall pass!!',0,1,0,0,'Phalanx YELL_PHALANX_AGGRO'),
(-1230041,'Get away from those kegs!',0,1,0,0,'Hurley Blackbreath YELL_HURLEY_SPAWN'),
(-1230042,'You\'ll pay for that!',0,0,0,0,'Hurley Blackbreath SAY_HURLEY_AGGRO'),
(-1230043,'You can\'t hide from us. Prepare to burn!',0,1,0,0,'anvilrage guardsman SAY_GUARD_AGGRO'),
(-1230044,'That one\'s empty!!',0,0,0,60,'rocknot SAY_BARREL_1'),
(-1230045,'Ah, empty again!',0,0,0,35,'rocknot SAY_BARREL_2'),
(-1230046,'ALE!',0,0,0,60,'rocknot SAY_BARREL_3'),
(-1230047,'I\m out of here!',0,0,0,0,'rocknot SAY_ROCKNOT_DESPAWN'),
(-1230048,'HALT! There were...reports...of a...disturbance.',0,1,0,0,'Fireguard Destroyer YELL_PATROL_1'),
(-1230049,'We...are...investigating.',0,1,0,0,'Fireguard Destroyer YELL_PATROL_2'),
(-1230050,'Try the boar! It\'s my new recipe!',0,0,0,0,'Plugger Spazzring SAY_OOC_1'),
(-1230051,'Enjoy! You won\'t find better ale anywhere!',0,0,0,0,'Plugger Spazzring SAY_OOC_2'),
(-1230052,'Drink up! There\'s more where that came from!',0,0,0,0,'Plugger Spazzring SAY_OOC_3'),
(-1230053,'Have you tried the Dark Iron Ale? It\'s the best!',0,0,0,0,'Plugger Spazzring SAY_OOC_4'),
(-1230054,'What are you doing over there?',0,1,0,0,'Plugger Spazzring YELL_STOLEN_1'),
(-1230055,'Hey! Get away from that!',0,1,0,0,'Plugger Spazzring YELL_STOLEN_2'),
(-1230056,'No stealing the goods!',0,1,0,0,'Plugger Spazzring YELL_STOLEN_3'),
(-1230057,'That\'s it! You\'re going down!',0,1,0,0,'Plugger Spazzring YELL_AGRRO_1'),
(-1230058,'That\'s it! No more beer until this mess is sorted out!',0,1,0,0,'Plugger Spazzring YELL_AGRRO_2'),
(-1230059,'Hey, my pockets were picked!',0,1,0,0,'Plugger Spazzring YELL_PICKPOCKETED'),
(-1230060,'Ha! You can\'t even begin to imagine the futility of your efforts.',0,1,0,0,'Emperor Thaurissan YELL_SENATOR_1'),
(-1230061,'Is that the best you can do? Do you really expect that you could defeat someone as awe inspiring as me?',0,1,0,0,'Emperor Thaurissan YELL_SENATOR_2'),
(-1230062,'They were just getting in the way anyways.',0,1,0,0,'Emperor Thaurissan YELL_SENATOR_3'),
(-1230063,'Your efforts are utterly pointless, fools! You will never be able to defeat me!',0,1,0,0,'Emperor Thaurissan YELL_SENATOR_4'),
(-1230064,'I will crush you into little tiny pieces!',0,1,0,0,'Emperor Thaurissan YELL_AGGRO_2'),
(-1230065,'Prepare to meet your doom at the hands of Ragnaros\' most powerful servant!',0,1,0,0,'Emperor Thaurissan YELL_AGGRO_3'),
(-1230066,'Hey, Rocknot!',0,0,0,0,'Nagmara SAY_NAGMARA_1'),
(-1230067,'Let\'s go, honey.',0,0,0,0,'Nagmara SAY_NAGMARA_2'),
(-1230068,'%s kisses her lover.',0,2,0,0,'Nagmara TEXTEMOTE_NAGMARA'),
(-1230069,'%s kisses Mistress Nagmara',0,2,0,17,'Rocknot TEXTEMOTE_ROCKNOT');

-- -1 249 000 ONYXIA'S LAIR
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1249000,'How fortuitous. Usually, I must leave my lair to feed.',0,1,0,0,'onyxia SAY_AGGRO'),
(-1249001,'Learn your place mortal!',0,1,0,0,'onyxia SAY_KILL'),
(-1249002,'This meaningless exertion bores me. I\'ll incinerate you all from above!',0,1,0,254,'onyxia SAY_PHASE_2_TRANS'),
(-1249003,'It seems you\'ll need another lesson, mortals!',0,1,0,293,'onyxia SAY_PHASE_3_TRANS'),
(-1249004,'%s takes in a deep breath...',0,3,0,0,'onyxia EMOTE_BREATH'),
(-1249005,'You seek to lure me from my clutch? You shall pay for your insolence!',0,1,0,0,'onyxia SAY_KITE');

-- -1 269 000 OPENING OF THE DARK PORTAL (BLACK MORASS)
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1269000,'Why do you persist? Surely you can see the futility of it all. It is not too late! You may still leave with your lives ...',10442,1,0,0,'temporus SAY_ENTER'),
(-1269001,'So be it ... you have been warned.',10444,1,0,0,'temporus SAY_AGGRO'),
(-1269002,'Time... sands of time is run out for you.',10443,1,0,0,'temporus SAY_BANISH'),
(-1269003,'You should have left when you had the chance.',10445,1,0,0,'temporus SAY_SLAY1'),
(-1269004,'Your days are done.',10446,1,0,0,'temporus SAY_SLAY2'),
(-1269005,'My death means ... little.',10447,1,0,0,'temporus SAY_DEATH'),

(-1269006,'Why do you aid the Magus? Just think of how many lives could be saved if the portal is never opened, if the resulting wars could be erased ...',10412,1,0,0,'chrono_lord_deja SAY_ENTER'),
(-1269007,'If you will not cease this foolish quest, then you will die!',10414,1,0,0,'chrono_lord_deja SAY_AGGRO'),
(-1269008,'You have outstayed your welcome, Timekeeper. Begone!',10413,1,0,0,'chrono_lord_deja SAY_BANISH'),
(-1269009,'I told you it was a fool\'s quest!',10415,1,0,0,'chrono_lord_deja SAY_SLAY1'),
(-1269010,'Leaving so soon?',10416,1,0,0,'chrono_lord_deja SAY_SLAY2'),
(-1269011,'Time ... is on our side.',10417,1,0,0,'chrono_lord_deja SAY_DEATH'),

(-1269012,'The time has come to shatter this clockwork universe forever! Let us no longer be slaves of the hourglass! I warn you: those who do not embrace the greater path shall become victims of its passing!',10400,1,0,0,'aeonus SAY_ENTER'),
(-1269013,'Let us see what fate lays in store...',10402,1,0,0,'aeonus SAY_AGGRO'),
(-1269014,'Your time is up, slave of the past!',10401,1,0,0,'aeonus SAY_BANISH'),
(-1269015,'One less obstacle in our way!',10403,1,0,0,'aeonus SAY_SLAY1'),
(-1269016,'No one can stop us! No one!',10404,1,0,0,'aeonus SAY_SLAY2'),
(-1269017,'It is only a matter...of time.',10405,1,0,0,'aeonus SAY_DEATH'),
(-1269018,'REUSE ME',0,0,0,0,'REUSE ME'),

(-1269019,'Stop! Do not go any further, mortal. You are ill-prepared to face the forces of the Infinite Dragonflight. Come, let me help you.',0,0,0,0,'saat SAY_SAAT_WELCOME'),

(-1269020,'The time has come! Gul\'dan, order your warlocks to double their efforts! Moments from now the gateway will open, and your Horde will be released upon this ripe, unsuspecting world!',10435,1,0,0,'medivh SAY_ENTER'),
(-1269021,'What is this? Champions, coming to my aid? I sense the hand of the dark one in this. Truly this sacred event bears his blessing?',10436,1,0,0,'medivh SAY_INTRO'),
(-1269022,'Champions, my shield grows weak!',10437,1,0,0,'medivh SAY_WEAK75'),
(-1269023,'My powers must be concentrated on the portal! I do not have time to hold the shield!',10438,1,0,0,'medivh SAY_WEAK50'),
(-1269024,'The shield is nearly gone! All that I have worked for is in danger!',10439,1,0,0,'medivh SAY_WEAK25'),
(-1269025,'No... damn this feeble mortal coil...',10441,1,0,0,'medivh SAY_DEATH'),
(-1269026,'I am grateful for your aid, champions. Now, Gul\'dan\'s Horde will sweep across this world, like a locust swarm, and all my designs, all my carefully laid plans will at last fall into place.',10440,1,0,0,'medivh SAY_WIN'),
(-1269027,'Orcs of the Horde! This portalis the gateway to your new destiny! Azeroth lies before you, ripe for the taking!',0,1,0,0,'medivh SAY_ORCS_ENTER'),
(-1269028,'Gul\'dan speaks the truth! We should return at once to tell our brothers of the news! Retreat back trought the portal!',0,1,0,0,'medivh SAY_ORCS_ANSWER');

-- -1 289 000 SCHOLOMANCE
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1289000,'School is in session!',0,1,0,0,'gandling SAY_GANDLING_SPAWN'),
(-1289001,'What is this?! How dare you!',0,1,0,0,'vectus YELL_VECTUS_GAMBIT');

-- -1 309 000 ZUL'GURUB
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1309000,'Let the coils of hate unfurl!',8421,1,0,0,'venoxis SAY_TRANSFORM'),
(-1309001,'Ssserenity..at lassst!',0,1,0,0,'venoxis SAY_DEATH'),

(-1309002,'Lord Hir\'eek, grant me wings of vengance!',8417,1,0,0,'jeklik SAY_AGGRO'),
(-1309003,'I command you to rain fire down upon these invaders!',0,1,0,0,'jeklik SAY_RAIN_FIRE'),
(-1309004,'Finally ...death. Curse you Hakkar! Curse you!',8422,1,0,0,'jeklik SAY_DEATH'),

(-1309005,'Draw me to your web mistress Shadra. Unleash your venom!',8418,1,0,0,'marli SAY_AGGRO'),
(-1309006,'Shadra, make of me your avatar!',0,1,0,0,'marli SAY_TRANSFORM'),
(-1309007,'Aid me my brood!',0,1,0,0,'marli SAY_SPIDER_SPAWN'),
(-1309008,'Bless you mortal for this release. Hakkar controls me no longer...',8423,1,0,0,'marli SAY_DEATH'),

(-1309009,'Shirvallah, fill me with your RAGE!',8419,1,0,0,'thekal SAY_AGGRO'),
(-1309010,'Hakkar binds me no more! Peace at last!',8424,1,0,0,'thekal SAY_DEATH'),

(-1309011,'Bethekk, your priestess calls upon your might!',8416,1,0,0,'arlokk SAY_AGGRO'),
(-1309012,'Feast on $n, my pretties!',0,1,0,0,'arlokk SAY_FEAST_PANTHER'),
(-1309013,'At last, I am free of the Soulflayer!',8412,1,0,0,'arlokk SAY_DEATH'),

(-1309014,'Welcome to da great show friends! Step right up to die!',8425,1,0,0,'jindo SAY_AGGRO'),

(-1309015,'I\'ll feed your souls to Hakkar himself!',8413,1,0,0,'mandokir SAY_AGGRO'),
(-1309016,'DING!',0,1,0,0,'mandokir SAY_DING_KILL'),
(-1309017,'GRATS!',0,1,0,0,'mandokir SAY_GRATS_JINDO'),
(-1309018,'$N! I\'m watching you!',0,1,0,0,'mandokir SAY_WATCH'),
(-1309019,'Don\'t make me angry. You won\'t like it when I\'m angry.',0,4,0,0,'mandokir SAY_WATCH_WHISPER'),

(-1309020,'PRIDE HERALDS THE END OF YOUR WORLD. COME, MORTALS! FACE THE WRATH OF THE SOULFLAYER!',8414,1,0,0,'hakkar SAY_AGGRO'),
(-1309021,'Fleeing will do you no good, mortals!',0,1,0,0,'hakkar SAY_FLEEING'),
(-1309022,'You dare set foot upon Hakkari holy ground? Minions of Hakkar, destroy the infidels!',0,6,0,0,'hakkar SAY_MINION_DESTROY'),
(-1309023,'Minions of Hakkar, hear your God. The sanctity of this temple has been compromised. Invaders encroach upon holy ground! The Altar of Blood must be protected. Kill them all!',0,6,0,0,'hakkar SAY_PROTECT_ALTAR'),

(-1309024,'%s goes into a rage after seeing his raptor fall in battle!',0,2,0,0,'mandokir EMOTE_RAGE'),

(-1309025,'The brood shall not fall!',0,1,0,0,'marli SAY_TRANSFORM_BACK'),

(-1309026,'%s emits a deafening shriek!',0,2,0,0,'jeklik SAY_SHRIEK'),
(-1309027,'%s begins to cast a Great Heal!',0,2,0,0,'jeklik SAY_HEAL'),

(-1309028,'%s fully engulfs in flame and a maddened look appears in his eyes!',0,2,0,0,'gurubashi bat rider - SAY_SELF_DETONATE');

-- -1 329 000 STRATHOLME
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1329000,'Thanks to Egan',0,0,0,0,'freed_soul SAY_ZAPPED0'),
(-1329001,'Rivendare must die',0,0,0,0,'freed_soul SAY_ZAPPED1'),
(-1329002,'Who you gonna call?',0,0,0,0,'freed_soul SAY_ZAPPED2'),
(-1329003,'Don\'t cross those beams!',0,0,0,0,'freed_soul SAY_ZAPPED3'),

(-1329004,'An Ash\'ari Crystal has fallen! Stay true to the Lich King, my brethren, and attempt to resummon it.',0,6,0,0,'thuzadin acolyte SAY_ANNOUNCE_ZIGGURAT_1'),
(-1329005,'One of the Ash\'ari Crystals has been destroyed! Slay the intruders!',0,6,0,0,'thuzadin acolyte SAY_ANNOUNCE_ZIGGURAT_2'),
(-1329006,'An Ash\'ari Crystal has been toppled! Restore the ziggurat before the Necropolis is vulnerable!',0,6,0,0,'thuzadin acolyte SAY_ANNOUNCE_ZIGGURAT_3'),
(-1329007,'The Ash\'ari Crystals have been destroyed! The Slaughterhouse is vulnerable!',0,6,0,0,'baron rivendare SAY_ANNOUNCE_RIVENDARE'),

(-1329008,'Intruders at the Service Gate! Lord Rivendare must be warned!',0,6,0,0,'barthilas SAY_WARN_BARON'),
(-1329009,'Intruders! More pawns of the Argent Dawn, no doubt. I already count one of their number among my prisoners. Withdraw from my domain before she is executed!',0,6,0,0,'baron rivendare SAY_ANNOUNCE_RUN_START'),
(-1329010,'You\'re still here? Your foolishness is amusing! The Argent Dawn wench needn\'t suffer in vain. Leave at once and she shall be spared!',0,6,0,0,'baron rivendare SAY_ANNOUNCE_RUN_10_MIN'),
(-1329011,'I shall take great pleasure in taking this poor wretch\'s life! It\'s not too late, she needn\'t suffer in vain. Turn back and her death shall be merciful!',0,6,0,0,'baron rivendare SAY_ANNOUNCE_RUN_5_MIN'),
(-1329012,'May this prisoner\'s death serve as a warning. None shall defy the Scourge and live!',0,6,0,0,'baron rivendare SAY_ANNOUNCE_RUN_FAIL'),
(-1329013,'So you see fit to toy with the Lich King\'s creations? Ramstein, be sure to give the intruders a proper greeting.',0,6,0,0,'baron rivendare SAY_ANNOUNCE_RAMSTEIN'),
(-1329014,'Time to take matters into my own hands. Come. Enter my domain and challenge the might of the Scourge!',0,6,0,0,'baron rivendare SAY_UNDEAD_DEFEAT'),
(-1329015,'You did it... you\'ve slain Baron Rivendare! The Argent Dawn shall hear of your valiant deeds!',0,0,0,0,'ysida SAY_EPILOGUE'),

(-1329016,'Today you have unmade what took me years to create! For this you shall all die by my hand!',0,1,0,0,'dathrohan SAY_AGGRO'),
(-1329017,'You fools think you can defeat me so easily? Face the true might of the Nathrezim!',0,1,0,0,'dathrohan SAY_TRANSFORM'),
(-1329018,'Damn you mortals! All my plans of revenge, all my hate... all burned to ash...',0,0,0,0,'dathrohan SAY_DEATH'),
(-1329019,'Don\'t worry about me!  Slay this dreadful beast and cleanse this world of his foul taint!',0,6,0,0,'ysida YSIDA_SAY_RUN_5_MIN'),
(-1329020,'My death means nothing.... light... will... prevail!',0,6,0,0,'ysida YSIDA_SAY_RUN_FAIL'),

(-1329021,'Rivendare! I come for you!',0,1,0,0,'aurius YELL_AURIUS_AGGRO'),
(-1329022,'Argh!',0,0,0,0,'aurius SAY_AURIUS_DEATH'),

(-1329023,'Move back and hold the line! We cannot fail or all will be lost!',0,1,0,0,'YELL_BASTION_BARRICADE'),
(-1329024,'Move to the stairs and defend!',0,1,0,0,'YELL_BASTION_STAIRS'),
(-1329025,'The Scourge have broken into the Bastion! Redouble your efforts! We must not fail!',0,1,0,0,'YELL_BASTION_ENTRANCE'),
(-1329026,'They have broken into the Hall of Lights! We must stop the intruders!',0,1,0,0,'YELL_BASTION_HALL_LIGHTS'),
(-1329027,'The Scourge have broken through in all wings! May the light defeat these foul creatures! We shall fight to the last!',0,1,0,0,'YELL_BASTION_INNER_1'),
(-1329028,'This will not be the end of the Scarlet Crusade! You will not break our line!',0,1,0,0,'YELL_BASTION_INNER_2');

-- -1 349 000 MARAUDON

-- -1 389 000 RAGEFIRE CHASM

-- -1 409 000 MOLTEN CORE
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1409000,'%s performs one last service for Ragnaros.',0,2,0,0,'geddon EMOTE_SERVICE'),
(-1409001,'REUSE ME',0,0,0,0,'REUSE ME'),
(-1409002,'%s refuses to die while its master is in trouble.',0,2,0,0,'core rager EMOTE_LOWHP'),

(-1409003,'Reckless mortals! None may challenge the Sons of the Living flame!',8035,1,0,0,'majordomo SAY_AGGRO'),
(-1409004,'The runes of warding have been destroyed! Hunt down the infidels, my brethren!',8039,6,0,0,'majordomo SAY_SPAWN'),
(-1409005,'Ashes to Ashes!',8037,1,0,0,'majordomo SAY_SLAY_1'),
(-1409006,'Burn mortals! Burn for this transgression!',8036,1,0,0,'majordomo SAY_SLAY_2'),
(-1409007,'Impossible! Stay your attack, mortals... I submit! I submit!',8038,1,0,0,'majordomo SAY_DEFEAT_1'),

(-1409008,'Behold Ragnaros - the Firelord! He who was ancient when this world was young! Bow before him, mortals! Bow before your ending!',8040,1,0,0,'ragnaros SAY_SUMMON_MAJ'),
(-1409009,'TOO SOON! YOU HAVE AWAKENED ME TOO SOON, EXECUTUS! WHAT IS THE MEANING OF THIS INTRUSION???',8043,1,0,0,'ragnaros SAY_ARRIVAL1_RAG'),
(-1409010,'These mortal infidels, my lord! They have invaded your sanctum and seek to steal your secrets!',8041,1,0,0,'ragnaros SAY_ARRIVAL2_MAJ'),
(-1409011,'FOOL! YOU ALLOWED THESE INSECTS TO RUN RAMPANT THROUGH THE HALLOWED CORE? AND NOW YOU LEAD THEM TO MY VERY LAIR? YOU HAVE FAILED ME, EXECUTUS! JUSTICE SHALL BE MET, INDEED!',8044,1,0,0,'ragnaros SAY_ARRIVAL3_RAG'),
(-1409012,'NOW FOR YOU, INSECTS! BOLDLY, YOU SOUGHT THE POWER OF RAGNAROS. NOW YOU SHALL SEE IT FIRSTHAND!',8045,1,0,0,'ragnaros SAY_ARRIVAL5_RAG'),

(-1409013,'COME FORTH, MY SERVANTS! DEFEND YOUR MASTER!',8049,1,0,0,'ragnaros SAY_REINFORCEMENTS1'),
(-1409014,'YOU CANNOT DEFEAT THE LIVING FLAME! COME YOU MINIONS OF FIRE! COME FORTH YOU CREATURES OF HATE! YOUR MASTER CALLS!',8050,1,0,0,'ragnaros SAY_REINFORCEMENTS2'),
(-1409015,'BY FIRE BE PURGED!',8046,1,0,0,'ragnaros SAY_HAND'),
(-1409016,'TASTE THE FLAMES OF SULFURON!',8047,1,0,0,'ragnaros SAY_WRATH'),
(-1409017,'DIE INSECT!',8051,1,0,0,'ragnaros SAY_KILL'),
(-1409018,'MY PATIENCE IS DWINDLING! COME GNATS: TO YOUR DEATH!',8048,1,0,0,'ragnaros SAY_MAGMABURST'),

(-1409019,'You think you\'ve won already? Perhaps you\'ll need another lesson in pain!',0,1,0,0,'majordomo SAY_LAST_ADD'),
(-1409020,'Brashly, you have come to wrest the secrets of the Living Flame! You will soon regret the recklessness of your quest.',0,1,0,0,'majordomo SAY_DEFEAT_2'),
(-1409021,'I go now to summon the lord whose house this is. Should you seek an audience with him, your paltry lives will surely be forfeit! Nevertheless, seek out his lair, if you dare!',0,1,0,0,'majordomo SAY_DEFEAT_3'),
(-1409022,'My flame! Please don\'t take away my flame... ',8042,1,0,0,'ragnaros SAY_ARRIVAL4_MAJ'),
(-1409023,'Very well, $n.',0,0,0,0,'majordomo SAY_SUMMON_0'),
(-1409024,'Impudent whelps! You\'ve rushed headlong to your own deaths! See now, the master stirs!',0,1,0,0,'majordomo SAY_SUMMON_1'),
(-1409025,'%s forces one of his Firesworn minions to erupt!',0,2,0,0,'Garr EMOTE_MASSIVE_ERUPTION');

-- -1 429 000 DIRE MAUL
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1429000,'The demon is loose! Quickly we must restrain him!',0,6,0,0,'highborne summoner SAY_FREE_IMMOLTHAR'),
(-1429001,'Who dares disrupt the sanctity of Eldre\'Thalas? Face me, cowards!',0,6,0,0,'prince tortheldrin SAY_KILL_IMMOLTHAR'),

(-1429002,'At last... Freed from his cursed grasp!',0,6,0,0,'old ironbark SAY_IRONBARK_REDEEM'),

(-1429003,'The king is dead - OH NOES! Summon Mizzle da Crafty! He knows what to do next!',0,1,0,0,'cho\'rush SAY_KING_DEAD'),

(-1429004,'Doh!',0,0,0,0,'slip\'kik SAY_SLIPKIK_TRAP');

-- -1 469 000 BLACKWING LAIR
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1469000,'None of your kind should be here! You\'ve doomed only yourselves!',8286,1,0,0,'broodlord SAY_AGGRO'),
(-1469001,'Clever Mortals but I am not so easily lured away from my sanctum!',8287,1,0,0,'broodlord SAY_LEASH'),

(-1469002,'Run! They are coming!',0,1,0,0,'vaelastrasz blackwing tech SAY_INTRO_TECH'),
(-1469003,'%s flinches as its skin shimmers.',0,2,0,0,'chromaggus EMOTE_SHIMMER'),

(-1469004,'In this world where time is your enemy, it is my greatest ally. This grand game of life that you think you play in fact plays you. To that I say...',0,1,0,1,'victor_nefarius SAY_GAMESBEGIN_1'),
(-1469005,'Let the games begin!',8280,1,0,22,'victor_nefarius SAY_GAMESBEGIN_2'),
(-1469006,'Ah...the heroes. You are persistent, aren\'t you? Your ally here attempted to match his power against mine - and paid the price. Now he shall serve me...by slaughtering you.',8279,1,0,23,'victor_nefarius SAY_NEFARIUS_CORRUPT'),

(-1469007,'Well done, my minions. The mortals\' courage begins to wane! Now, let\'s see how they contend with the true Lord of Blackrock Spire!',8288,6,0,0,'nefarian SAY_AGGRO'),
(-1469008,'Enough! Now you vermin shall feel the force of my birthright, the fury of the earth itself.',8289,1,0,0,'nefarian SAY_XHEALTH'),
(-1469009,'BURN! You wretches! BURN!',8290,6,0,0,'nefarian SAY_SHADOWFLAME'),
(-1469010,'Impossible! Rise my minions! Serve your master once more!',8291,1,0,0,'nefarian SAY_RAISE_SKELETONS'),
(-1469011,'Worthless $N! Your friends will join you soon enough!',8293,1,0,0,'nefarian SAY_SLAY'),
(-1469012,'This cannot be!  I am the master here!  You mortals are nothing to my kind!  Do you hear me? Nothing!',8292,1,0,0,'nefarian SAY_DEATH'),
(-1469013,'Mages too? You should be more careful when you play with magic...',0,1,0,0,'nefarian SAY_MAGE'),
(-1469014,'Warriors, I know you can hit harder than that! Let\'s see it!',0,1,0,0,'nefarian SAY_WARRIOR'),
(-1469015,'Druids and your silly shapeshifting. Let\'s see it in action!',0,1,0,0,'nefarian SAY_DRUID'),
(-1469016,'Priests! If you\'re going to keep healing like that, we might as well make it a little more interesting!',0,1,0,0,'nefarian SAY_PRIEST'),
(-1469017,'Paladins, I\'ve heard you have many lives. Show me.',0,1,0,0,'nefarian SAY_PALADIN'),
(-1469018,'Shamans, show me what your totems can do!',0,1,0,0,'nefarian SAY_SHAMAN'),
(-1469019,'Warlocks, you shouldn\'t be playing with magic you don\'t understand. See what happens?',0,1,0,0,'nefarian SAY_WARLOCK'),
(-1469020,'Hunters and your annoying pea-shooters!',0,1,0,0,'nefarian SAY_HUNTER'),
(-1469021,'Rogues? Stop hiding and face me!',0,1,0,0,'nefarian SAY_ROGUE'),

(-1469022,'You\'ll pay for forcing me to do this.',8275,1,0,0,'razorgore SAY_EGGS_BROKEN1'),
(-1469023,'Fools! These eggs are more precious than you know!',8276,1,0,0,'razorgore SAY_EGGS_BROKEN2'),
(-1469024,'No - not another one! I\'ll have your heads for this atrocity!',8277,1,0,0,'razorgore SAY_EGGS_BROKEN3'),
(-1469025,'If I fall into the abyss I\'ll take all of you mortals with me...',8278,1,0,0,'razorgore SAY_RAZORGORE_DEATH'),

(-1469026,'Too late, friends! Nefarius\' corruption has taken hold...I cannot...control myself.',8281,1,0,1,'vaelastrasz SAY_LINE1'),
(-1469027,'I beg you, mortals - FLEE! Flee before I lose all sense of control! The black fire rages within my heart! I MUST- release it!',8282,1,0,1,'vaelastrasz SAY_LINE2'),
(-1469028,'FLAME! DEATH! DESTRUCTION! Cower, mortals before the wrath of Lord...NO - I MUST fight this! Alexstrasza help me, I MUST fight it!',8283,1,0,1,'vaelastrasz SAY_LINE3'),
(-1469029,'Nefarius\' hate has made me stronger than ever before! You should have fled while you could, mortals! The fury of Blackrock courses through my veins!',8285,1,0,0,'vaelastrasz SAY_HALFLIFE'),
(-1469030,'Forgive me, $N! Your death only adds to my failure!',8284,1,0,0,'vaelastrasz SAY_KILLTARGET'),

(-1469031,'Death Knights, get over here!',0,1,0,0,'nefarian SAY_DEATH_KNIGHT'),

(-1469032,'Get up, little red wyrm...and destroy them!',0,1,0,1,'victor_nefarius SAY_NEFARIUS_CORRUPT_2'),

(-1469033,'%s flee as the controlling power of the orb is drained.',0,2,0,0,'razorgore EMOTE_TROOPS_FLEE'),

(-1469034,'Run! They are coming.',0,1,0,0,'blackwing technician SAY_TECHNICIAN_RUN'),

(-1469035,'Orb of Domination loses power and shuts off!',0,2,0,0,'razorgore EMOTE_ORB_SHUT_OFF'),

(-1469036,'Looking for this: [Red Scepter Shard]? Come and get it...',0,6,0,0,'nefarius YELL_REDSHARD_TAUNT_1'),
(-1469037,'I wonder, heroes, what will you do when I manage to destroy this shard? Will the world be beyond Salvation?',0,6,0,0,'nefarius YELL_REDSHARD_TAUNT_2'),
(-1469038,'%s\'s laughter echoes through the halls of Blackwing.',0,7,0,0,'nefarius EMOTE_REDSHARD_TAUNT_1'),
(-1469039,'What\'s this? A chip in the shard? Finally, a weakness exposed... It won\'t be long now.',0,6,0,0,'nefarius YELL_REDSHARD_TAUNT_3'),
(-1469040,'Not even my father could have planned such tragedy... such chaos. You will never make it! Time is running out!',0,6,0,0,'nefarius YELL_REDSHARD_TAUNT_4'),
(-1469041,'Would it not be glorious if you somehow managed to defeat me but not before I could destroy the only hope Kalimdor may have? I am giddy with anticipation. Soon... Soon it will be dust.',0,6,0,0,'nefarius YELL_REDSHARD_TAUNT_5'),
(-1469042,'Ah, the protective layer is nearly gone. Do you hear that, heroes? That... That is the sound of inevitability. Of your hopes and dreams being crushed under the weight of my being.',0,6,0,0,'nefarius YELL_REDSHARD_TAUNT_6'),
(-1469044,'%s\'laughter can once more be heard through the halls of Blackwing.',0,7,0,0,'nefarius EMOTE_REDSHARD_TAUNT_2'),
(-1469043,'The scepter shard is no more! Your beloved Kalimdor shall soon be a desolate wasteland. I will, of course, turn the Eastern Kingdoms into an ashen, lifeless void...',0,6,0,0,'nefarius YELL_REDSHARD_TAUNT_7');

-- -1 509 000 RUINS OF AHN'QIRAJ
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1509000,'%s senses your fear.',0,2,0,0,'moam EMOTE_AGGRO'),
(-1509001,'%s bristles with energy!',0,2,0,0,'moan EMOTE_MANA_FULL'),
(-1509028,'%s drains your mana and turns to stone.',0,2,0,0,'moam EMOTE_ENERGIZING'),

(-1509002,'%s sets eyes on $N!',0,2,0,0,'buru EMOTE_TARGET'),

(-1509003,'They come now. Try not to get yourself killed, young blood.',0,1,0,22,'andorov SAY_ANDOROV_INTRO_3'),
(-1509004,'Remember, Rajaxx, when I said I\'d kill you last?',0,1,0,0,'andorov SAY_ANDOROV_INTRO_1'),

(-1509005,'The time of our retribution is at hand! Let darkness reign in the hearts of our enemies!',8612,1,0,0,'rajaxx SAY_WAVE3'),
(-1509006,'No longer will we wait behind barred doors and walls of stone! No longer will our vengeance be denied! The dragons themselves will tremble before our wrath!',8610,1,0,0,'rajaxx SAY_WAVE4'),
(-1509007,'Fear is for the enemy! Fear and death!',8608,1,0,0,'rajaxx SAY_WAVE5'),
(-1509008,'Staghelm will whimper and beg for his life, just as his whelp of a son did! One thousand years of injustice will end this day!',8611,1,0,0,'rajaxx SAY_WAVE6'),
(-1509009,'Fandral! Your time has come! Go and hide in the Emerald Dream and pray we never find you!',8607,1,0,0,'rajaxx SAY_WAVE7'),
(-1509010,'Impudent fool! I will kill you myself!',8609,1,0,0,'rajaxx SAY_INTRO'),
(-1509011,'Attack and make them pay dearly!',8603,1,0,0,'rajaxx SAY_UNK1'),
(-1509012,'Crush them! Drive them out!',8605,1,0,0,'rajaxx SAY_UNK2'),
(-1509013,'Do not hesitate! Destroy them!',8606,1,0,0,'rajaxx SAY_UNK3'),
(-1509014,'Warriors! Captains! Continue the fight!',8613,1,0,0,'rajaxx SAY_UNK4'),
(-1509015,'You are not worth my time $N!',8614,1,0,0,'rajaxx SAY_DEAGGRO'),
(-1509016,'Breath your last!',8604,1,0,0,'rajaxx SAY_KILLS_ANDOROV'),
(-1509017,'Soon you will know the price of your meddling, mortals... The master is nearly whole... And when he rises, your world will be cease!',0,1,0,0,'rajaxx SAY_COMPLETE_QUEST'),

(-1509018,'I am rejuvinated!',8593,1,0,0,'ossirian SAY_SURPREME1'),
(-1509019,'My powers are renewed!',8595,1,0,0,'ossirian SAY_SURPREME2'),
(-1509020,'My powers return!',8596,1,0,0,'ossirian SAY_SURPREME3'),
(-1509021,'Protect the city at all costs!',8597,1,0,0,'ossirian SAY_RAND_INTRO1'),
(-1509022,'The walls have been breached!',8599,6,0,0,'ossirian SAY_RAND_INTRO2'),
(-1509023,'To your posts. Defend the city.',8600,1,0,0,'ossirian SAY_RAND_INTRO3'),
(-1509024,'Tresspassers will be terminated.',8601,1,0,0,'ossirian SAY_RAND_INTRO4'),
(-1509025,'Sands of the desert rise and block out the sun!',8598,1,0,0,'ossirian SAY_AGGRO'),
(-1509026,'You are terminated.',8602,1,0,0,'ossirian SAY_SLAY'),
(-1509027,'I...have...failed.',8594,1,0,0,'ossirian SAY_DEATH'),
-- 28 (above) = EMOTE_ENERGIZING
(-1509029,'Come get some!',0,0,0,0,'andorov SAY_ANDOROV_INTRO_4'),
(-1509030,'Kill first, ask questions later... Incoming!',0,1,0,0,'andorov SAY_ANDOROV_ATTACK_START'),
(-1509031,'I lied...',0,1,0,0,'andorov SAY_ANDOROV_INTRO_2');

-- -1 531 000 TEMPLE OF AHN'QIRAJ
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1531000,'Are you so eager to die? I would be happy to accomodate you.',8615,1,0,0,'skeram SAY_AGGRO1'),
(-1531001,'Cower mortals! The age of darkness is at hand.',8616,1,0,0,'skeram SAY_AGGRO2'),
(-1531002,'Tremble! The end is upon you.',8621,1,0,0,'skeram SAY_AGGRO3'),
(-1531003,'Let your death serve as an example!',8617,1,0,0,'skeram SAY_SLAY1'),
(-1531004,'Spineless wretches! You will drown in rivers of blood!',8619,1,0,0,'skeram SAY_SLAY2'),
(-1531005,'The screams of the dying will fill the air. A symphony of terror is about to begin!',8620,1,0,0,'skeram SAY_SLAY3'),
(-1531006,'Prepare for the return of the ancient ones!',8618,1,0,0,'skeram SAY_SPLIT'),
(-1531007,'You only delay... the inevetable.',8622,1,0,0,'skeram SAY_DEATH'),

(-1531008,'You will be judged for defiling these sacred grounds! The laws of the Ancients will not be challenged! Trespassers will be annihilated!',8646,1,0,0,'sartura SAY_AGGRO'),
(-1531009,'I sentence you to death!',8647,1,0,0,'sartura SAY_SLAY'),
(-1531010,'I serve to the last!',8648,1,0,0,'sartura SAY_DEATH'),

(-1531011,'%s is weakened!',0,2,0,0,'cthun EMOTE_WEAKENED'),

(-1531012,'The massive floating eyeball in the center of the chamber turns its gaze upon you. You stand before a god.',0,2,0,0,'eye cthun EMOTE_INTRO'),
(-1531013,'Only flesh and bone. Mortals are such easy prey...',0,1,0,0,'veklor SAY_INTRO_1'),
(-1531014,'Where are your manners, brother. Let us properly welcome our guests.',0,1,0,0,'veknilash SAY_INTRO_2'),
(-1531015,'There will be pain...',0,1,0,0,'veklor SAY_INTRO_3'),
(-1531016,'Oh so much pain...',0,1,0,0,'veknilash SAY_INTRO_4'),
(-1531017,'Come, little ones.',0,1,0,0,'veklor SAY_INTRO_5'),
(-1531018,'The feast of souls begin now...',0,1,0,0,'veknilash SAY_INTRO_6'),

(-1531019,'It\'s too late to turn away.',8623,1,0,0,'veklor SAY_AGGRO_1'),
(-1531020,'Prepare to embrace oblivion!',8626,1,0,0,'veklor SAY_AGGRO_2'),
(-1531021,'Like a fly in a web.',8624,1,0,0,'veklor SAY_AGGRO_3'),
(-1531022,'Your brash arrogance!',8628,1,0,0,'veklor SAY_AGGRO_4'),
(-1531023,'You will not escape death!',8629,1,0,0,'veklor SAY_SLAY'),
(-1531024,'My brother...NO!',8625,1,0,0,'veklor SAY_DEATH'),
(-1531025,'To decorate our halls!',8627,1,0,0,'veklor SAY_SPECIAL'),

(-1531026,'Ah, lambs to the slaughter!',8630,1,0,0,'veknilash SAY_AGGRO_1'),
(-1531027,'Let none survive!',8632,1,0,0,'veknilash SAY_AGGRO_2'),
(-1531028,'Join me brother, there is blood to be shed!',8631,1,0,0,'veknilash SAY_AGGRO_3'),
(-1531029,'Look brother, fresh blood!',8633,1,0,0,'veknilash SAY_AGGRO_4'),
(-1531030,'Your fate is sealed!',8635,1,0,0,'veknilash SAY_SLAY'),
(-1531031,'Vek\'lor, I feel your pain!',8636,1,0,0,'veknilash SAY_DEATH'),
(-1531032,'Shall be your undoing!',8634,1,0,0,'veknilash SAY_SPECIAL'),

(-1531033,'Death is close...',8580,4,0,0,'cthun SAY_WHISPER_1'),
(-1531034,'You are already dead.',8581,4,0,0,'cthun SAY_WHISPER_2'),
(-1531035,'Your courage will fail.',8582,4,0,0,'cthun SAY_WHISPER_3'),
(-1531036,'Your friends will abandon you.',8583,4,0,0,'cthun SAY_WHISPER_4'),
(-1531037,'You will betray your friends.',8584,4,0,0,'cthun SAY_WHISPER_5'),
(-1531038,'You will die.',8585,4,0,0,'cthun SAY_WHISPER_6'),
(-1531039,'You are weak.',8586,4,0,0,'cthun SAY_WHISPER_7'),
(-1531040,'Your heart will explode.',8587,4,0,0,'cthun SAY_WHISPER_8'),

(-1531041,'%s begins to slow!',0,2,0,0,'viscidus EMOTE_SLOW'),
(-1531042,'%s is freezing up!',0,2,0,0,'viscidus EMOTE_FREEZE'),
(-1531043,'%s is frozen solid!',0,2,0,0,'viscidus EMOTE_FROZEN'),
(-1531044,'%s begins to crack!',0,2,0,0,'viscidus EMOTE_CRACK'),
(-1531045,'%s looks ready to shatter!',0,2,0,0,'viscidus EMOTE_SHATTER'),
(-1531046,'%s explodes!',0,2,0,0,'viscidus EMOTE_EXPLODE');

-- -1 532 000 KARAZHAN
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1532000,'Well done Midnight!',9173,1,0,0,'attumen SAY_MIDNIGHT_KILL'),
(-1532001,'Cowards! Wretches!',9167,1,0,0,'attumen SAY_APPEAR1'),
(-1532002,'Who dares attack the steed of the Huntsman?',9298,1,0,0,'attumen SAY_APPEAR2'),
(-1532003,'Perhaps you would rather test yourselves against a more formidable opponent?!',9299,1,0,0,'attumen SAY_APPEAR3'),
(-1532004,'Come Midnight, let''s disperse this petty rabble!',9168,1,0,0,'attumen SAY_MOUNT'),
(-1532005,'It was... inevitable.',9169,1,0,0,'attumen SAY_KILL1'),
(-1532006,'Another trophy to add to my collection!',9300,1,0,0,'attumen SAY_KILL2'),
(-1532007,'Weapons are merely a convenience for a warrior of my skill!',9166,1,0,0,'attumen SAY_DISARMED'),
(-1532008,'Always knew... someday I would become... the hunted.',9165,1,0,0,'attumen SAY_DEATH'),
(-1532009,'Such easy sport.',9170,1,0,0,'attumen SAY_RANDOM1'),
(-1532010,'Amateurs! Do not think you can best me! I kill for a living.',9304,1,0,0,'attumen SAY_RANDOM2'),

(-1532011,'Hm, unannounced visitors. Preparations must be made...',9211,1,0,0,'moroes SAY_AGGRO'),
(-1532012,'Now, where was I? Oh, yes...',9215,1,0,0,'moroes SAY_SPECIAL_1'),
(-1532013,'You rang?',9316,1,0,0,'moroes SAY_SPECIAL_2'),
(-1532014,'One more for dinner this evening.',9214,1,0,0,'moroes SAY_KILL_1'),
(-1532015,'Time... Never enough time.',9314,1,0,0,'moroes SAY_KILL_2'),
(-1532016,'I\'ve gone and made a mess.',9315,1,0,0,'moroes SAY_KILL_3'),
(-1532017,'How terribly clumsy of me.',9213,1,0,0,'moroes SAY_DEATH'),

(-1532018,'Your behavior will not be tolerated.',9204,1,0,0,'maiden SAY_AGGRO'),
(-1532019,'Ah ah ah...',9207,1,0,0,'maiden SAY_SLAY1'),
(-1532020,'This is for the best.',9312,1,0,0,'maiden SAY_SLAY2'),
(-1532021,'Impure thoughts lead to profane actions.',9311,1,0,0,'maiden SAY_SLAY3'),
(-1532022,'Cast out your corrupt thoughts.',9313,1,0,0,'maiden SAY_REPENTANCE1'),
(-1532023,'Your impurity must be cleansed.',9208,1,0,0,'maiden SAY_REPENTANCE2'),
(-1532024,'Death comes. Will your conscience be clear?',9206,1,0,0,'maiden SAY_DEATH'),

(-1532025,'Oh at last, at last I can go home!',9190,1,0,0,'dorothee SAY_DOROTHEE_DEATH'),
(-1532026,'Don''t let them hurt us Tito! Oh, you won''t, will you?',9191,1,0,0,'dorothee SAY_DOROTHEE_SUMMON'),
(-1532027,'Tito! Oh Tito, no!',9192,1,0,0,'dorothee SAY_DOROTHEE_TITO_DEATH'),
(-1532028,'Oh Tito, we simply must find a way home! The old wizard could be our only hope! Strawman, Roar, Tinhead, will you - wait... oh golly, look we have visitors!',9195,1,0,0,'dorothee SAY_DOROTHEE_AGGRO'),

(-1532029,'I''m not afraid a'' you! Do you wanna'' fight? Huh, do ya''? C''mon! I''ll fight ya'' with both paws behind my back!',9227,1,0,0,'roar SAY_ROAR_AGGRO'),
(-1532030,'You didn''t have to go and do that!',9229,1,0,0,'roar SAY_ROAR_DEATH'),
(-1532031,'I think I\'m going to go take fourty winks.',9230,1,0,0,'roar SAY_ROAR_SLAY'),

(-1532032,'Now what should I do with you? I simply can''t make up my mind.',9254,1,0,0,'strawman SAY_STRAWMAN_AGGRO'),
(-1532033,'Don''t let them make... a mattress outta'' me.',9256,1,0,0,'strawman SAY_STRAWMAN_DEATH'),
(-1532034,'I guess I\'m not a failure after all.',9257,1,0,0,'strawman SAY_STRAWMAN_SLAY'),

(-1532035,'I could really use a heart. Say, can I have yours?',9268,1,0,0,'tinhead SAY_TINHEAD_AGGRO'),
(-1532036,'Back to being an old rust bucket.',9270,1,0,0,'tinhead SAY_TINHEAD_DEATH'),
(-1532037,'Guess I\'m not so rusty, after all.',9271,1,0,0,'tinhead SAY_TINHEAD_SLAY'),
(-1532038,'%s begins to rust!',0,2,0,0,'tinhead EMOTE_RUST'),

(-1532039,'Woe to each and every one of you, my pretties!',9179,1,0,25,'crone SAY_CRONE_INTRO'),
(-1532040,'It will all be over soon!',9307,1,0,25,'crone SAY_CRONE_INTRO2'),
(-1532041,'How could you? What a cruel, cruel world...',9178,1,0,0,'crone SAY_CRONE_DEATH'),
(-1532042,'Fixed you, didn''t I?',9180,1,0,0,'crone SAY_CRONE_SLAY'),

(-1532043,'The better to own you with!',9276,1,0,0,'wolf SAY_WOLF_AGGRO'),
(-1532044,'Mmmm... delicious.',9277,1,0,0,'wolf SAY_WOLF_SLAY'),
(-1532045,'Run away little girl, run away!',9278,1,0,0,'wolf SAY_WOLF_HOOD'),

(-1532046,'What devil art thou, that dost torment me thus?',9196,1,0,0,'julianne SAY_JULIANNE_AGGRO'),
(-1532047,'Where is my lord? Where is my Romulo?',9199,1,0,0,'julianne SAY_JULIANNE_ENTER'),
(-1532048,'Romulo, I come! Oh... this do I drink to thee!',9198,1,0,0,'julianne SAY_JULIANNE_DEATH01'),
(-1532049,'O happy dagger! This is thy sheath; there rust, and let me die!',9310,1,0,0,'julianne SAY_JULIANNE_DEATH02'),
(-1532050,'Come, gentle night; and give me back my Romulo!',9200,1,0,0,'julianne SAY_JULIANNE_RESURRECT'),
(-1532051,'Parting is such sweet sorrow.',9201,1,0,0,'julianne SAY_JULIANNE_SLAY'),

(-1532052,'Wilt thou provoke me? Then have at thee, boy!',9233,1,0,0,'romulo SAY_ROMULO_AGGRO'),
(-1532053,'Thou smilest... upon the stroke that... murders me.',9235,1,0,0,'romulo SAY_ROMULO_DEATH'),
(-1532054,'This day\'s black fate on more days doth depend. This but begins the woe. Others must end.',9236,1,0,0,'romulo SAY_ROMULO_ENTER'),
(-1532055,'Thou detestable maw, thou womb of death; I enforce thy rotten jaws to open!',9237,1,0,0,'romulo SAY_ROMULO_RESURRECT'),
(-1532056,'How well my comfort is revived by this!',9238,1,0,0,'romulo SAY_ROMULO_SLAY'),

(-1532057,'The Menagerie is for guests only.',9183,1,0,0,'curator SAY_AGGRO'),
(-1532058,'Gallery rules will be strictly enforced.',9188,1,0,0,'curator SAY_SUMMON1'),
(-1532059,'This Curator is equipped for gallery protection.',9309,1,0,0,'curator SAY_SUMMON2'),
(-1532060,'Your request cannot be processed.',9186,1,0,0,'curator SAY_EVOCATE'),
(-1532061,'Failure to comply will result in offensive action.',9185,1,0,0,'curator SAY_ENRAGE'),
(-1532062,'Do not touch the displays.',9187,1,0,0,'curator SAY_KILL1'),
(-1532063,'You are not a guest.',9308,1,0,0,'curator SAY_KILL2'),
(-1532064,'Curator is no longer operation-a-l.',9184,1,0,0,'curator SAY_DEATH'),

(-1532065,'Your blood will anoint my circle.',9264,1,0,0,'terestian SAY_SLAY1'),
(-1532066,'The great one will be pleased.',9329,1,0,0,'terestian SAY_SLAY2'),
(-1532067,'My life is yours, oh great one...',9262,1,0,0,'terestian SAY_DEATH'),
(-1532068,'Ah, you''re just in time. The rituals are about to begin!',9260,1,0,0,'terestian SAY_AGGRO'),
(-1532069,'Please accept this humble offering, oh great one...',9263,1,0,0,'terestian SAY_SACRIFICE1'),
(-1532070,'Let the sacrifice serve his testament to my fealty.',9330,1,0,0,'terestian SAY_SACRIFICE2'),
(-1532071,'Come, you dwellers in the dark! Rally to my call!',9265,1,0,0,'terestian SAY_SUMMON1'),
(-1532072,'Gather, my pets. There is plenty for all.',9331,1,0,0,'terestian SAY_SUMMON2'),

(-1532073,'Please, no more. My son... he\'s gone mad!',9241,1,0,0,'aran SAY_AGGRO1'),
(-1532074,'I''ll not be tortured again!',9323,1,0,0,'aran SAY_AGGRO2'),
(-1532075,'Who are you? What do you want? Stay away from me!',9324,1,0,0,'aran SAY_AGGRO3'),
(-1532076,'I''ll show you: this beaten dog still has some teeth!',9245,1,0,0,'aran SAY_FLAMEWREATH1'),
(-1532077,'Burn you hellish fiends!',9326,1,0,0,'aran SAY_FLAMEWREATH2'),
(-1532078,'I''ll freeze you all!',9246,1,0,0,'aran SAY_BLIZZARD1'),
(-1532079,'Back to the cold dark with you!',9327,1,0,0,'aran SAY_BLIZZARD2'),
(-1532080,'Yes, yes my son is quite powerful... but I have powers of my own!',9242,1,0,0,'aran SAY_EXPLOSION1'),
(-1532081,'I am not some simple jester! I am Nielas Aran!',9325,1,0,0,'aran SAY_EXPLOSION2'),
(-1532082,'Surely you wouldn''t deny an old man a replenishing drink? No, no, I thought not.',9248,1,0,0,'aran SAY_DRINK'),
(-1532083,'I''m not finished yet! No, I have a few more tricks up my sleeve...',9251,1,0,0,'aran SAY_ELEMENTALS'),
(-1532084,'I want this nightmare to be over!',9250,1,0,0,'aran SAY_KILL1'),
(-1532085,'Torment me no more!',9328,1,0,0,'aran SAY_KILL2'),
(-1532086,'You\'ve wasted enough of my time. Let these games be finished!',9247,1,0,0,'aran SAY_TIMEOVER'),
(-1532087,'At last the nightmare is over...',9244,1,0,0,'aran SAY_DEATH'),
(-1532088,'Where did you get that?! Did HE send you?!',9249,1,0,0,'aran SAY_ATIESH'),

(-1532089,'%s cries out in withdrawal, opening gates to the nether.',0,3,0,0,'netherspite EMOTE_PHASE_PORTAL'),
(-1532090,'%s goes into a nether-fed rage!',0,3,0,0,'netherspite EMOTE_PHASE_BANISH'),

(-1532091,'Madness has brought you here to me. I shall be your undoing!',9218,1,0,0,'malchezaar SAY_AGGRO'),
(-1532092,'Simple fools! Time is the fire in which you''ll burn!',9220,1,0,0,'malchezaar SAY_AXE_TOSS1'),
(-1532093,'I see the subtlety of conception is beyond primitives such as you.',9317,1,0,0,'malchezaar SAY_AXE_TOSS2'),
(-1532094,'Who knows what secrets hide in the dark.',9223,1,0,0,'malchezaar SAY_SPECIAL1'),
(-1532095,'The cerestial forces are mine to manipulate.',9320,1,0,0,'malchezaar SAY_SPECIAL2'),
(-1532096,'How can you hope to stand against such overwhelming power?',9321,1,0,0,'malchezaar SAY_SPECIAL3'),
(-1532097,'Surely you did not think you could win.',9222,1,0,0,'malchezaar SAY_SLAY1'),
(-1532098,'Your greed, your foolishness has brought you to this end.',9318,1,0,0,'malchezaar SAY_SLAY2'),
(-1532099,'You are, but a plaything, unfit even to amuse.',9319,1,0,0,'malchezaar SAY_SLAY3'),
(-1532100,'All realities, all dimensions are open to me!',9224,1,0,0,'malchezaar SAY_SUMMON1'),
(-1532101,'You face not Malchezaar alone, but the legions I command!',9322,1,0,0,'malchezaar SAY_SUMMON2'),
(-1532102,'I refuse to concede defeat! I am a prince of the Eredar! I... am...',9221,1,0,0,'malchezaar SAY_DEATH'),

(-1532103,'Welcome ladies and gentlemen, to this evening''s presentation!',9174,1,0,0,'barnes OZ1'),
(-1532104,'Tonight we plumb the depths of the human soul as we join a lost, lonely girl trying desperately--with the help of her loyal companions--to find her way home!',9338,1,0,0,'barnes OZ2'),
(-1532105,'But she is pursued... by a wicked, malevolent crone!',9339,1,0,0,'barnes OZ3'),
(-1532106,'Will she survive? Will she prevail? Only time will tell. And now... on with the show!',9340,1,0,0,'barnes OZ4'),
(-1532107,'Good evening, Ladies and Gentlemen! Welcome to this evening\'s presentation!',9175,1,0,0,'barnes HOOD1'),
(-1532108,'Tonight, things are not what they seem. For tonight, your eyes may not be trusted',9335,1,0,0,'barnes HOOD2'),
(-1532109,'Take for instance, this quiet, elderly woman, waiting for a visit from her granddaughter. Surely there is nothing to fear from this sweet, grey-haired, old lady.',9336,1,0,0,'barnes HOOD3'),
(-1532110,'But don\'t let me pull the wool over your eyes. See for yourself what lies beneath those covers! And now... on with the show!',9337,1,0,0,'barnes HOOD4'),
(-1532111,'Welcome, Ladies and Gentlemen, to this evening\'s presentation!',9176,1,0,0,'barnes RAJ1'),
(-1532112,'Tonight... we explore a tale of forbidden love!',9341,1,0,0,'barnes RAJ2'),
(-1532113,'But beware, for not all love stories end happily, as you may find out. Sometimes, love pricks like a thorn!',9342,1,0,0,'barnes RAJ3'),
(-1532114,'But don''t take it from me; see for yourself what tragedy lies ahead when the paths of star crossed lovers meet! And now... on with the show!',9343,1,0,0,'barnes RAJ4'),
(-1532115,'Splendid. I''m going to get the audience ready. Break a leg!',0,0,0,0,'barnes SAY_EVENT_START'),

(-1532116,'You\'ve got my attention, dragon. You\'ll find I\'m not as easily scared as the villagers below.',0,1,0,0,'image of medivh SAY_MEDIVH_1'),
(-1532117,'Your dabbling in the arcane has gone too far, Medivh. You\'ve attracted the attention of powers beyond your understanding. You must leave Karazhan at once!',0,1,0,0,'arcanagos SAY_ARCANAGOS_2'),
(-1532118,'You dare challenge me at my own dwelling? Your arrogance is astounding, even for a dragon.',0,1,0,0,'image of medivh SAY_MEDIVH_3'),
(-1532119,'A dark power seeks to use you, Medivh! If you stay, dire days will follow. You must hurry, we don\'t have much time!',0,1,0,0,'arcanagos SAY_ARCANAGOS_4'),
(-1532120,'I do not know what you speak of, dragon... but I will not be bullied by this display of insolence. I\'ll leave Karazhan when it suits me!',0,1,0,0,'image of medivh SAY_MEDIVH_5'),
(-1532121,'You leave me no alternative. I will stop you by force if you wont listen to reason.',0,1,0,0,'arcanagos SAY_ARCANAGOS_6'),
(-1532122,'%s begins to cast a spell of great power, weaving his own essence into the magic.',0,2,0,0,'image of medivh EMOTE_CAST_SPELL'),
(-1532123,'What have you done, wizard? This cannot be! I\'m burning from... within!',0,1,0,0,'arcanagos SAY_ARCANAGOS_7'),
(-1532124,'He should not have angered me. I must go... recover my strength now...',0,0,0,0,'image of medivh SAY_MEDIVH_8'),

(-1532125,'An ancient being awakens in the distance...',0,2,0,0,'nightbane EMOTE_AWAKEN'),
(-1532126,'What fools! I shall bring a quick end to your suffering!',0,1,0,0,'nightbane SAY_AGGRO'),
(-1532127,'Miserable vermin. I shall exterminate you from the air!',0,1,0,0,'nightbane SAY_AIR_PHASE'),
(-1532128,'Enough! I shall land and crush you myself!',0,1,0,0,'nightbane SAY_LAND_PHASE_1'),
(-1532129,'Insects! Let me show you my strength up close!',0,1,0,0,'nightbane SAY_LAND_PHASE_2'),
(-1532130,'%s takes a deep breath.',0,3,0,0,'nightbane EMOTE_DEEP_BREATH'),

(-1532131,'The halls of Karazhan shake, as the curse binding the doors of the Gamesman''s Hall is lifted.',0,2,0,0,'echo_of_medivh EMOTE_LIFT_CURSE'),
(-1532132,'%s cheats!',0,3,0,0,'echo_of_medivh EMOTE_CHEAT'),

(-1532133,'%s flaps down from the ceiling...',0,7,0,0,'shadikith_the_glider EMOTE_BAT_SPAWN'),
(-1532134,'%s howls through the halls...',0,7,0,0,'rokad_the_ravager EMOTE_DOG_SPAWN'),
(-1532135,'%s emerges from the shadows...',0,7,0,0,'hyakiss_the_lurker EMOTE_SPIDER_SPAWN'),
(-1532136,'%s shrieks in pain and points at his master.',0,3,0,0,'Kil''Rek EMOTE_DEATH'),
(-1532137,'%s calls for her master!',0,3,0,0,'Midnight EMOTE_CALL'),
(-1532138,'%s skitters out from the shadows...',0,7,0,0,'hyakiss_the_lurker EMOTE_SPIDER_SPAWN2'),
(-1532139,'%s begins channelling his mana into a powerful arcane spell.',0,3,0,0,'aran EMOTE_ARCANE_SPELL');

-- -1 533 000 NAXXRAMAS
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1533000,'Ahh... welcome to my parlor.',8788,1,0,0,'anubrekhan SAY_GREET1'),
(-1533001,'Just a little taste...',8785,1,0,0,'anubrekhan SAY_AGGRO1'),
(-1533002,'There is no way out.',8786,1,0,0,'anubrekhan SAY_AGGRO2'),
(-1533003,'Yes, run! It makes the blood pump faster!',8787,1,0,0,'anubrekhan SAY_AGGRO3'),
(-1533004,'I hear little hearts beating. Yesss... beating faster now. Soon the beating will stop.',8790,1,0,0,'anubrekhan SAY_GREET2'),
(-1533005,'Where to go? What to do? So many choices that all end in pain, end in death.',8791,1,0,0,'anubrekhan SAY_GREET3'),
(-1533006,'Which one shall I eat first? So difficult to choose. They all smell so delicious...',8792,1,0,0,'anubrekhan SAY_GREET4'),
(-1533007,'Closer now... tasty morsels. I\'ve been too long without food. Without blood to drink.',8793,1,0,0,'anubrekhan SAY_GREET5'),
(-1533008,'Shhh... it will all be over soon.',8789,1,0,0,'anubrekhan SAY_SLAY'),

(-1533009,'Your old lives, your mortal desires, mean nothing. You are acolytes of the master now, and you will serve the cause without question! The greatest glory is to die in the master\'s service!',8799,1,0,0,'faerlina SAY_GREET'),
(-1533010,'Slay them in the master\'s name!',8794,1,0,0,'faerlina SAY_AGGRO1'),
(-1533011,'You cannot hide from me!',8795,1,0,0,'faerlina SAY_ENRAGE_1'),
(-1533012,'Kneel before me, worm!',8796,1,0,0,'faerlina SAY_ENRAGE_2'),
(-1533013,'Run while you still can!',8797,1,0,0,'faerlina SAY_ENRAGE_3'),
(-1533014,'You have failed!',8800,1,0,0,'faerlina SAY_SLAY1'),
(-1533015,'Pathetic wretch!',8801,1,0,0,'faerlina SAY_SLAY2'),
(-1533016,'The master... will avenge me!',8798,1,0,0,'faerlina SAY_DEATH'),

(-1533017,'Patchwerk want to play!',8909,1,0,0,'patchwerk SAY_AGGRO1'),
(-1533018,'Kel\'Thuzad make Patchwerk his Avatar of War!',8910,1,0,0,'patchwerk SAY_AGGRO2'),
(-1533019,'No more play?',8912,1,0,0,'patchwerk SAY_SLAY'),
(-1533020,'What happened to... Patch...',8911,1,0,0,'patchwerk SAY_DEATH'),

(-1533021,'%s sprays slime across the room!',0,3,0,0,'grobbulus EMOTE_SPRAY_SLIME'),

(-1533022,'%s lifts off into the air!',0,3,0,0,'sapphiron EMOTE_FLY'),

(-1533023,'Stalagg crush you!',8864,1,0,0,'stalagg SAY_STAL_AGGRO'),
(-1533024,'Stalagg kill!',8866,1,0,0,'stalagg SAY_STAL_SLAY'),
(-1533025,'Master save me...',8865,1,0,0,'stalagg SAY_STAL_DEATH'),
(-1533026,'Feed you to master!',8802,1,0,0,'feugen SAY_FEUG_AGGRO'),
(-1533027,'Feugen make master happy!',8804,1,0,0,'feugen SAY_FEUG_SLAY'),
(-1533028,'No... more... Feugen...',8803,1,0,0,'feugen SAY_FEUG_DEATH'),

(-1533029,'You are too late... I... must... OBEY!',8872,1,0,0,'thaddius SAY_GREET'),
(-1533030,'KILL!',8867,1,0,0,'thaddius SAY_AGGRO1'),
(-1533031,'EAT YOUR BONES!',8868,1,0,0,'thaddius SAY_AGGRO2'),
(-1533032,'BREAK YOU!',8869,1,0,0,'thaddius SAY_AGGRO3'),
(-1533033,'You die now!',8877,1,0,0,'thaddius SAY_SLAY'),
(-1533034,'Now YOU feel pain!',8871,1,0,0,'thaddius SAY_ELECT'),
(-1533035,'Thank... you...',8870,1,0,0,'thaddius SAY_DEATH'),
(-1533036,'REUSE_ME',0,0,0,0,'REUSE'),
(-1533037,'REUSE_ME',0,0,0,0,'REUSE'),
(-1533038,'REUSE_ME',0,0,0,0,'REUSE'),
(-1533039,'REUSE_ME',0,0,0,0,'REUSE'),

(-1533040,'Foolishly you have sought your own demise.',8807,1,0,0,'gothik SAY_SPEECH_1'),
(-1533041,'Death is the only escape.',8806,1,0,0,'gothik SAY_KILL'),
(-1533042,'I... am... undone!',8805,1,0,0,'gothik SAY_DEATH'),
(-1533043,'I have waited long enough! Now, you face the harvester of souls!',8808,1,0,0,'gothik SAY_TELEPORT'),

(-1533044,'Defend yourself!',8892,0,0,0,'blaumeux SAY_BLAU_AGGRO'),
(-1533045,'Come, Zeliek, do not drive them out. Not before we\'ve had our fun.',8896,6,0,0,'blaumeux SAY_BLAU_TAUNT1'),
(-1533046,'I do hope they stay alive long enough for me to... introduce myself.',8897,6,0,0,'blaumeux SAY_BLAU_TAUNT2'),
(-1533047,'The first kill goes to me! Anyone care to wager?',8898,6,0,0,'blaumeux SAY_BLAU_TAUNT3'),
(-1533048,'Your life is mine!',8895,1,0,0,'blaumeux SAY_BLAU_SPECIAL'),
(-1533049,'Who\'s next?',8894,0,0,0,'blaumeux SAY_BLAU_SLAY'),
(-1533050,'Tou... che!',8893,0,0,0,'blaumeux SAY_BLAU_DEATH'),

(-1533051,'Come out and fight, ye wee ninny!',8899,0,0,0,'korthazz SAY_KORT_AGGRO'),
(-1533052,'To arms, ye roustabouts! We\'ve got company!',8903,6,0,0,'korthazz SAY_KORT_TAUNT1'),
(-1533053,'I heard about enough of yer sniveling. Shut yer fly trap \'afore I shut it for ye!',8904,6,0,0,'korthazz SAY_KORT_TAUNT2'),
(-1533054,'I\'m gonna enjoy killin\' these slack-jawed daffodils!',8905,6,0,0,'korthazz SAY_KORT_TAUNT3'),
(-1533055,'I like my meat extra crispy!',8902,0,0,0,'korthazz SAY_KORT_SPECIAL'),
(-1533056,'Next time, bring more friends!',8901,0,0,0,'korthazz SAY_KORT_SLAY'),
(-1533057,'What a bloody waste this is!',8900,0,0,0,'korthazz SAY_KORT_DEATH'),

(-1533058,'Flee, before it\'s too late!',8913,0,0,0,'zeliek SAY_ZELI_AGGRO'),
(-1533059,'Invaders, cease this foolish venture at once! Turn away while you still can!',8917,6,0,0,'zeliek SAY_ZELI_TAUNT1'),
(-1533060,'Perhaps they will come to their senses, and run away as fast as they can!',8918,6,0,0,'zeliek SAY_ZELI_TAUNT2'),
(-1533061,'Do not continue! Turn back while there\'s still time!',8919,6,0,0,'zeliek SAY_ZELI_TAUNT3'),
(-1533062,'I- I have no choice but to obey!',8916,0,0,0,'zeliek SAY_ZELI_SPECIAL'),
(-1533063,'Forgive me!',8915,0,0,0,'zeliek SAY_ZELI_SLAY'),
(-1533064,'It is... as it should be.',8914,0,0,0,'zeliek SAY_ZELI_DEATH'),

(-1533065,'You seek death?',8835,0,0,0,'mograine SAY_MORG_AGGRO1'),
(-1533066,'None shall pass!',8836,0,0,0,'mograine SAY_MORG_AGGRO2'),
(-1533067,'Be still!',8837,0,0,0,'mograine SAY_MORG_AGGRO3'),
(-1533068,'You will find no peace in death.',8839,0,0,0,'mograine SAY_MORG_SLAY1'),
(-1533069,'The master\'s will is done.',8840,0,0,0,'mograine SAY_MORG_SLAY2'),
(-1533070,'Bow to the might of the Highlord!',8841,0,0,0,'mograine SAY_MORG_SPECIAL'),
(-1533071,'Enough prattling. Let them come! We shall grind their bones to dust.',8842,6,0,0,'mograine SAY_MORG_TAUNT1'),
(-1533072,'Conserve your anger! Harness your rage! You will all have outlets for your frustration soon enough.',8843,6,0,0,'mograine SAY_MORG_TAUNT2'),
(-1533073,'Life is meaningless. It is in death that we are truly tested.',8844,6,0,0,'mograine SAY_MORG_TAUNT3'),
(-1533074,'I...am...released! Perhaps it\'s not too late to-NOO! I need...more time...',8838,0,0,0,'mograine SAY_MORG_DEATH'),

(-1533075,'Glory to the master!',8845,1,0,0,'noth SAY_AGGRO1'),
(-1533076,'Your life is forfeit!',8846,1,0,0,'noth SAY_AGGRO2'),
(-1533077,'Die, trespasser!',8847,1,0,0,'noth SAY_AGGRO3'),
(-1533078,'Rise, my soldiers! Rise and fight once more!',8851,1,0,0,'noth SAY_SUMMON'),
(-1533079,'My task is done!',8849,1,0,0,'noth SAY_SLAY1'),
(-1533080,'Breathe no more!',8850,1,0,0,'noth SAY_SLAY2'),
(-1533081,'I will serve the master... in... death!',8848,1,0,0,'noth SAY_DEATH'),

(-1533082,'%s takes in a deep breath...',0,3,0,0,'sapphiron EMOTE_BREATH'),
(-1533083,'%s resumes his attacks!',0,3,0,0,'sapphiron EMOTE_GROUND'),

(-1533084,'Our preparations continue as planned master.',8878,6,0,0,'kelthuzad SAY_SAPP_DIALOG1'),
(-1533085,'It is good that you serve me so faithfully. Soon... all will serve the Lich King and in the end, you shall be rewarded. So long as you do not falter.',8881,6,0,0,'lich_king SAY_SAPP_DIALOG2_LICH'),
(-1533086,'I foresee no complications at this... wait! What is this!?',8879,6,0,0,'kelthuzad SAY_SAPP_DIALOG3'),
(-1533087,'Your security measures have failed! See to this interruption immediately!',8882,6,0,0,'lich_king SAY_SAPP_DIALOG4_LICH'),
(-1533088,'Yes, master!',8880,6,0,0,'kelthuzad SAY_SAPP_DIALOG5'),
(-1533089,'No!!! A curse upon you, interlopers! The armies of the Lich King will hunt you down. You will not escape your fate...',0,6,0,0,'kelthuzad SAY_CAT_DIED'),
(-1533090,'Who dares violate the sanctity of my domain? Be warned, all who trespass here are doomed.',8820,6,0,0,'kelthuzad SAY_TAUNT1'),
(-1533091,'Fools, you think yourselves triumphant? You have only taken one step closer to the abyss! ',8821,6,0,0,'kelthuzad SAY_TAUNT2'),
(-1533092,'I grow tired of these games. Proceed, and I will banish your souls to oblivion!',8822,6,0,0,'kelthuzad SAY_TAUNT3'),
(-1533093,'You have no idea what horrors lie ahead. You have seen nothing! The frozen heart of Naxxramas awaits you!',8823,6,0,0,'kelthuzad SAY_TAUNT4'),
(-1533094,'Pray for mercy!',8809,1,0,0,'kelthuzad SAY_AGGRO1'),
(-1533095,'Scream your dying breath!',8810,1,0,0,'kelthuzad SAY_AGGRO2'),
(-1533096,'The end is upon you!',8811,1,0,0,'kelthuzad SAY_AGGRO3'),
(-1533097,'The dark void awaits you!',8817,1,0,0,'kelthuzad SAY_SLAY1'),
(-1533098,'<Kel\'Thuzad cackles maniacally!>',8818,1,0,0,'kelthuzad SAY_SLAY2'),
(-1533099,'AAAAGHHH!... Do not rejoice... your victory is a hollow one... for I shall return with powers beyond your imagining!',8814,1,0,0,'kelthuzad SAY_DEATH'),
(-1533100,'Your soul, is bound to me now!',8812,1,0,0,'kelthuzad SAY_CHAIN1'),
(-1533101,'There will be no escape!',8813,1,0,0,'kelthuzad SAY_CHAIN2'),
(-1533102,'I will freeze the blood in your veins!',8815,1,0,0,'kelthuzad SAY_FROST_BLAST'),
(-1533103,'Master! I require aid! ',8816,1,0,0,'kelthuzad SAY_REQUEST_AID'),
(-1533104,'Very well... warriors of the frozen wastes, rise up! I command you to fight, kill, and die for your master. Let none survive...',8824,1,0,0,'kelthuzad SAY_ANSWER_REQUEST'),
(-1533105,'Minions, servants, soldiers of the cold dark, obey the call of Kel\'Thuzad!',8819,1,0,0,'kelthuzad SAY_SUMMON_MINIONS'),
(-1533106,'Your petty magics are no challenge to the might of the Scourge! ',9088,1,0,0,'kelthuzad SAY_SPECIAL1_MANA_DET'),
(-1533107,'Enough! I grow tired of these distractions! ',9090,1,0,0,'kelthuzad SAY_SPECIAL3_MANA_DET'),
(-1533108,'Fools, you have spread your powers too thin. Be free, my minions!',9089,1,0,0,'kelthuzad SAY_SPECIAL2_DISPELL'),

(-1533109,'You are mine now!',8825,1,0,0,'heigan SAY_AGGRO1'),
(-1533110,'I see you!',8826,1,0,0,'heigan SAY_AGGRO2'),
(-1533111,'You...are next!',8827,1,0,0,'heigan SAY_AGGRO3'),
(-1533112,'Close your eyes... sleep!',8829,1,0,0,'heigan SAY_SLAY'),
(-1533113,'The races of the world will perish. It is only a matter of time.',8830,1,0,0,'heigan SAY_TAUNT1'),
(-1533114,'I see endless suffering, I see torment, I see rage. I see... everything!',8831,1,0,0,'heigan SAY_TAUNT2'),
(-1533115,'Soon... the world will tremble!',8832,1,0,0,'heigan SAY_TAUNT3'),
(-1533116,'The end is upon you.',8833,1,0,0,'heigan SAY_CHANNELING'),
(-1533117,'Hungry worms will feast on your rotten flesh!',8834,1,0,0,'heigan SAY_TAUNT4'),
(-1533118,'Noo... o...',8828,1,0,0,'heigan SAY_DEATH'),

(-1533119,'%s spots a nearby Zombie to devour!',0,3,0,0,'gluth EMOTE_ZOMBIE'),

(-1533120,'Do as I taught you!',8855,1,0,0,'razuvious SAY_AGGRO1'),
(-1533121,'Show them no mercy!',8856,1,0,0,'razuvious SAY_AGGRO2'),
(-1533122,'The time for practice is over! Show me what you\'ve learned!',8859,1,0,0,'razuvious SAY_AGGRO3'),
(-1533123,'Sweep the leg! Do you have a problem with that?',8861,1,0,0,'razuvious SAY_AGGRO4'),
(-1533124,'You should have stayed home!',8862,1,0,0,'razuvious SAY_SLAY1'),
(-1533125,'You disappoint me, students!',8858,1,0,0,'razuvious SAY_SLAY2'),
(-1533126,'Hah hah, I\'m just getting warmed up!',8852,1,0,0,'razuvious SAY_TRIUMPHANT1'),
(-1533127,'Stand and fight!',8853,1,0,0,'razuvious SAY_TRIUMPHANT2'),
(-1533128,'Show me what you\'ve got!',8854,1,0,0,'razuvious SAY_TRIUMPHANT3'),
(-1533129,'An honorable... death...',8860,1,0,0,'razuvious SAY_DEATH'),

(-1533130,'%s summons forth Skeletal Warriors!',0,3,0,0,'noth EMOTE_WARRIOR'),
(-1533131,'%s raises more skeletons!',0,3,0,0,'noth EMOTE_SKELETON'),
(-1533132,'%s teleports to the balcony above!',0,3,0,0,'noth EMOTE_TELEPORT'),
(-1533133,'%s teleports back into the battle!',0,3,0,0,'noth EMOTE_TELEPORT_RETURN'),

(-1533134,'A Guardian of Icecrown enters the fight!',0,3,0,0,'kelthuzad EMOTE_GUARDIAN'),
(-1533135,'%s strikes!',0,3,0,0,'kelthuzad EMOTE_PHASE2'),

(-1533136,'%s teleports and begins to channel a spell!',0,3,0,0,'heigan EMOTE_TELEPORT'),
(-1533137,'%s rushes to attack once more!',0,3,0,0,'heigan EMOTE_RETURN'),

(-1533138,'%s teleports into the fray!',0,3,0,0,'gothik EMOTE_TO_FRAY'),
(-1533139,'The central gate opens!',0,3,0,0,'gothik EMOTE_GATE'),
(-1533140,'Brazenly you have disregarded powers beyond your understanding.',0,1,0,0,'gothik SAY_SPEECH_2'),
(-1533141,'You have fought hard to invade the realm of the harvester.',0,1,0,0,'gothik SAY_SPEECH_3'),
(-1533142,'Now there is only one way out - to walk the lonely path of the damned.',0,1,0,0,'gothik SAY_SPEECH_4'),

(-1533143,'An aura of necrotic energy blocks all healing!',0,3,0,0,'Loatheb EMOTE_AURA_BLOCKING'),
(-1533144,'The power of Necrotic Aura begins to wane!',0,3,0,0,'Loatheb EMOTE_AURA_WANE'),
(-1533145,'The aura fades away, allowing healing once more!',0,3,0,0,'Loatheb EMOTE_AURA_FADING'),

(-1533146,'%s spins her web into a cocoon!',0,3,0,0,'maexxna EMOTE_SPIN_WEB'),
(-1533147,'Spiderlings appear on the web!',0,3,0,0,'maexxna EMOTE_SPIDERLING'),
(-1533148,'%s sprays strands of web everywhere!',0,3,0,0,'maexxna EMOTE_SPRAY'),

(-1533149,'%s loses its link!',0,3,0,0,'tesla_coil EMOTE_LOSING_LINK'),
(-1533150,'%s overloads!',0,3,0,0,'tesla_coil EMOTE_TESLA_OVERLOAD'),
(-1533151,'The polarity has shifted!',0,3,0,0,'thaddius EMOTE_POLARITY_SHIFT'),

(-1533152,'%s decimates all nearby flesh!',0,3,0,0,'gluth EMOTE_DECIMATE'),

(-1533153,'A %s joins the fight!',0,3,0,0,'crypt_guard EMOTE_CRYPT_GUARD'),
(-1533154,'%s begins to unleash an insect swarm!',0,3,0,0,'anubrekhan EMOTE_INSECT_SWARM'),
(-1533155,'Corpse Scarabs appear from a Crypt Guard\'s corpse!',0,3,0,0,'anubrekhan EMOTE_CORPSE_SCARABS'),

(-1533156,'%s casts Unyielding Pain on everyone!',0,3,0,0,'lady_blaumeux EMOTE_UNYIELDING_PAIN'),
(-1533157,'%s casts Condemation on everyone!',0,3,0,0,'sir_zeliek EMOTE_CONDEMATION');

-- -1 534 000 THE BATTLE OF MT. HYJAL
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1534000,'I\'m in jeopardy, help me if you can!',11007,1,0,0,'jaina hyjal ATTACKED 1'),
(-1534001,'They\'ve broken through!',11049,1,0,0,'jaina hyjal ATTACKED 2'),
(-1534002,'Stay alert! Another wave approaches.',11008,1,0,0,'jaina hyjal INCOMING'),
(-1534003,'Don\'t give up! We must prevail!',11006,1,0,0,'jaina hyjal BEGIN'),
(-1534004,'Hold them back as long as possible.',11050,1,0,0,'jaina hyjal RALLY 1'),
(-1534005,'We must hold strong!',11051,1,0,0,'jaina hyjal RALLY 2'),
(-1534006,'We are lost. Fall back!',11009,1,0,0,'jaina hyjal FAILURE'),
(-1534007,'We have won valuable time. Now we must pull back!',11011,1,0,0,'jaina hyjal SUCCESS'),
(-1534008,'I did... my best.',11010,1,0,0,'jaina hyjal DEATH'),

(-1534009,'I will lie down for no one!',11031,1,0,0,'thrall hyjal ATTACKED 1'),
(-1534010,'Bring the fight to me and pay with your lives!',11061,1,0,0,'thrall hyjal ATTACKED 2'),
(-1534011,'Make ready for another wave! LOK-TAR OGAR!',11032,1,0,0,'thrall hyjal INCOMING'),
(-1534012,'Hold them back! Do not falter!',11030,1,0,0,'thrall hyjal BEGIN'),
(-1534013,'Victory or death!',11059,1,0,0,'thrall hyjal RALLY 1'),
(-1534014,'Do not give an inch of ground!',11060,1,0,0,'thrall hyjal RALLY 2'),
(-1534015,'It is over. Withdraw! We have failed.',11033,1,0,0,'thrall hyjal FAILURE'),
(-1534016,'We have played our part and done well. It is up to the others now.',11035,1,0,0,'thrall hyjal SUCCESS'),
(-1534017,'Uraaa...',11034,1,0,0,'thrall hyjal DEATH'),

(-1534018,'All of your efforts have been in vain, for the draining of the World Tree has already begun. Soon the heart of your world will beat no more.',10986,6,0,0,'archimonde SAY_PRE_EVENTS_COMPLETE'),
(-1534019,'Your resistance is insignificant.',10987,1,0,0,'archimonde SAY_AGGRO'),
(-1534020,'This world will burn!',10990,1,0,0,'archimonde SAY_DOOMFIRE1'),
(-1534021,'Manach sheek-thrish!',11041,1,0,0,'archimonde SAY_DOOMFIRE2'),
(-1534022,'A-kreesh!',10989,1,0,0,'archimonde SAY_AIR_BURST1'),
(-1534023,'Away vermin!',11043,1,0,0,'archimonde SAY_AIR_BURST2'),
(-1534024,'All creation will be devoured!',11044,1,0,0,'archimonde SAY_SLAY1'),
(-1534025,'Your soul will languish for eternity.',10991,1,0,0,'archimonde SAY_SLAY2'),
(-1534026,'I am the coming of the end!',11045,1,0,0,'archimonde SAY_SLAY3'),
(-1534027,'At last it is here! Mourn and lament the passing of all you have ever known, and all that would have been! Hach min corai!',10993,1,0,0,'archimonde SAY_ENRAGE'),
(-1534028,'No, it cannot be! Nooo!',10992,1,0,0,'archimonde SAY_DEATH'),
(-1534029,'You are mine now.',10988,1,0,0,'archimonde SAY_SOUL_CHARGE1'),
(-1534030,'Bow to my will.',11042,1,0,0,'archimonde SAY_SOUL_CHARGE2');

-- -1 540 000 SHATTERED HALLS
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1540000,'You wish to fight us all at once? This should be amusing!',10262,1,0,0,'nethekurse SAY_AGGRO_1'),
(-1540001,'Thank you for saving me the trouble. Now it''s my turn to have some fun!',10270,1,0,0,'nethekurse SAY_AGGRO_2'),
(-1540002,'Come on, show me a real fight!',10272,1,0,0,'nethekurse SAY_AGGRO_3'),
(-1540003,'You can have that one, I no longer need him!',10263,1,0,11,'nethekurse PEON_ATTACK_1'),
(-1540004,'Yes, beat him mercilessly! His skull is as thick as an ogre''s!',10264,1,0,0,'nethekurse PEON_ATTACK_2'),
(-1540005,'Don''t waste your time on that one, he''s weak!',10265,1,0,11,'nethekurse PEON_ATTACK_3'),
(-1540006,'You want him? Very well, take him!',10266,1,0,0,'nethekurse PEON_ATTACK_4'),
(-1540007,'One pitiful wretch down. Go on, take another one.',10267,1,0,0,'nethekurse PEON_DIE_1'),
(-1540008,'Ah, what a waste... next!',10268,1,0,0,'nethekurse PEON_DIE_2'),
(-1540009,'I was going to kill him anyway!',10269,1,0,0,'nethekurse PEON_DIE_3'),
(-1540010,'Beg for your pitiful life!',10259,1,0,0,'nethekurse SAY_TAUNT_1'),
(-1540011,'Run, coward, run!   ',10260,1,0,11,'nethekurse SAY_TAUNT_2'),
(-1540012,'Your pain amuses me!',10261,1,0,11,'nethekurse SAY_TAUNT_3'),
(-1540013,'I had more fun torturing the peons!',10273,1,0,0,'nethekurse SAY_SLAY_1'),
(-1540014,'I''m already bored!',10271,1,0,0,'nethekurse SAY_SAY_2'),
(-1540015,'You lose.',10274,1,0,0,'nethekurse SAY_SLAY_3'),
(-1540016,'Oh, just die!',10275,1,0,0,'nethekurse SAY_SLAY_4'),
(-1540017,'What... a shame.',10276,1,0,0,'nethekurse SAY_DIE'),

(-1540018,'Smash!',10306,1,0,0,'omrogg GoCombat_1'),
(-1540019,'If you nice me let you live.',10308,1,0,0,'omrogg GoCombat_2'),
(-1540020,'Me hungry!',10309,1,0,0,'omrogg GoCombat_3'),
(-1540021,'Why don\'t you let me do the talking?',10317,1,0,0,'omrogg GoCombatDelay_1'),
(-1540022,'No, we will NOT let you live!',10318,1,0,0,'omrogg GoCombatDelay_2'),
(-1540023,'You always hungry. That why we so fat!',10319,1,0,0,'omrogg GoCombatDelay_3'),
(-1540024,'You stay here. Me go kill someone else!',10303,1,0,0,'omrogg Threat_1'),
(-1540025,'What are you doing!',10315,1,0,0,'omrogg Threat_2'),
(-1540026,'Me kill someone else...',10302,1,0,0,'omrogg Threat_3'),
(-1540027,'Me not like this one...',10300,1,0,0,'omrogg Threat_4'),
(-1540028,'That\'s not funny!',10314,1,0,0,'omrogg ThreatDelay1_1'),
(-1540029,'Me get bored...',10305,1,0,0,'omrogg ThreatDelay1_2'),
(-1540030,'I\'m not done yet, idiot!',10313,1,0,0,'omrogg ThreatDelay1_3'),
(-1540031,'Hey you numbskull!',10312,1,0,0,'omrogg ThreatDelay1_4'),
(-1540032,'Ha ha ha.',10304,1,0,0,'omrogg ThreatDelay2_1'),
(-1540033,'Whhy! He almost dead!',10316,1,0,0,'omrogg ThreatDelay2_2'),
(-1540034,'H\'ey...',10307,1,0,0,'omrogg ThreatDelay2_3'),
(-1540035,'We kill his friend!',10301,1,0,0,'omrogg ThreatDelay2_4'),
(-1540036,'This one die easy!',10310,1,0,0,'omrogg Killing_1'),
(-1540037,'I\'m tired. You kill next one!',10320,1,0,0,'omrogg Killing_2'),
(-1540038,'That\'s because I do all the hard work!',10321,1,0,0,'omrogg KillingDelay_1'),
(-1540039,'This all...your fault!',10311,1,0,0,'omrogg YELL_DIE_L'),
(-1540040,'I...hate...you...',10322,1,0,0,'omrogg YELL_DIE_R'),
(-1540041,'%s enrages!',0,2,0,0,'omrogg EMOTE_ENRAGE'),

(-1540042,'Ours is the TRUE Horde! The only Horde!',10323,1,0,0,'kargath SAY_AGGRO1'),
(-1540043,'I\'ll carve the meat from your bones!',10324,1,0,0,'kargath SAY_AGGRO2'),
(-1540044,'I am called Bladefist for a reason, as you will see!',10325,1,0,0,'kargath SAY_AGGRO3'),
(-1540045,'For the real Horde!',10326,1,0,0,'kargath SAY_SLAY1'),
(-1540046,'I am the only Warchief!',10327,1,0,0,'kargath SAY_SLAY2'),
(-1540047,'The true Horde... will.. prevail...',10328,1,0,0,'kargath SAY_DEATH'),
(-1540048,'Cowards! You\'ll never pull me into the shadows!',0,1,0,0,'kargath SAY_EVADE'),

(-1540049,'The Alliance dares to intrude this far into my fortress? Bring out the Honor Hold prisoners and call for the executioner! They\'ll pay with their lives for this trespass!',0,6,0,0,'kargath SAY_EXECUTE_ALLY'),
(-1540050,'It looks like we have a ranking officer among our captives...how amusing. Execute the green-skinned dog at once!',0,6,0,0,'kargath SAY_EXECUTE_HORDE');

-- -1 542 000 BLOOD FURNACE
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1542000,'Who dares interrupt... What is this? What have you done? You ruin everything!',10164,1,0,0,'kelidan SAY_WAKE'),
(-1542001,'You mustn\'t let him loose!',10166,1,0,0,'kelidan SAY_ADD_AGGRO_1'),
(-1542002,'Ignorant whelps!',10167,1,0,0,'kelidan SAY_ADD_AGGRO_2'),
(-1542003,'You fools! He\'ll kill us all!',10168,1,0,0,'kelidan SAY_ADD_AGGRO_3'),
(-1542004,'Just as you deserve!',10169,1,0,0,'kelidan SAY_KILL_1'),
(-1542005,'Your friends will soon be joining you.',10170,1,0,0,'kelidan SAY_KILL_2'),
(-1542006,'Closer... Come closer.. and burn!',10165,1,0,0,'kelidan SAY_NOVA'),
(-1542007,'Good luck... you\'ll need it..',10171,1,0,0,'kelidan SAY_DIE'),

(-1542008,'Come intruders....',0,1,0,0,'broggok SAY_AGGRO'),

(-1542009,'My work must not be interrupted.',10286,1,0,0,'the_maker SAY_AGGRO_1'),
(-1542010,'Perhaps I can find a use for you.',10287,1,0,0,'the_maker SAY_AGGRO_2'),
(-1542011,'Anger... Hate... These are tools I can use.',10288,1,0,0,'the_maker SAY_AGGRO_3'),
(-1542012,'Let\'s see what I can make of you.',10289,1,0,0,'the_maker SAY_KILL_1'),
(-1542013,'It is pointless to resist.',10290,1,0,0,'the_maker SAY_KILL_2'),
(-1542014,'Stay away from... me.',10291,1,0,0,'the_maker SAY_DIE'),

(-1542015,'Kill them!',0,1,0,0,'broggok SAY_BROGGOK_INTRO'),

(-1542016,'How long do you beleive your pathetic sorcery can hold me?',0,6,0,0,'magtheridon SAY_MAGTHERIDON_WARN');

-- -1 543 000 HELLFIRE RAMPARTS
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1543000,'Do you smell that? Fresh meat has somehow breached our citadel. Be wary of any intruders.',0,1,0,0,'gargolmar SAY_TAUNT'),
(-1543001,'Heal me! QUICKLY!',10329,1,0,0,'gargolmar SAY_HEAL'),
(-1543002,'Back off, pup!',10330,1,0,0,'gargolmar SAY_SURGE'),
(-1543003,'What have we here...?',10331,1,0,0,'gargolmar SAY_AGGRO_1'),
(-1543004,'Heh... this may hurt a little.',10332,1,0,0,'gargolmar SAY_AGGRO_2'),
(-1543005,'I\'m gonna enjoy this.',10333,1,0,0,'gargolmar SAY_AGGRO_3'),
(-1543006,'Say farewell!',10334,1,0,0,'gargolmar SAY_KILL_1'),
(-1543007,'Much too easy...',10335,1,0,0,'gargolmar SAY_KILL_2'),
(-1543008,'Hahah.. <cough> ..argh!',10336,1,0,0,'gargolmar SAY_DIE'),

(-1543009,'You dare stand against me?!',10280,1,0,0,'omor SAY_AGGRO_1'),
(-1543010,'I will not be defeated!',10279,1,0,0,'omor SAY_AGGRO_2'),
(-1543011,'Your insolence will be your death.',10281,1,0,0,'omor SAY_AGGRO_3'),
(-1543012,'Achor-she-ki! Feast my pet! Eat your fill!',10277,1,0,0,'omor SAY_SUMMON'),
(-1543013,'A-Kreesh!',10278,1,0,0,'omor SAY_CURSE'),
(-1543014,'Die, weakling!',10282,1,0,0,'omor SAY_KILL_1'),
(-1543015,'It is... not over.',10284,1,0,0,'omor SAY_DIE'),
(-1543016,'I am victorious!',10283,1,0,0,'omor SAY_WIPE'),

(-1543017,'You have faced many challenges, pity they were all in vain. Soon your people will kneel to my lord!',10292,1,0,0,'vazruden SAY_INTRO'),
(-1543018,'Your time is running out!',10294,1,0,0,'vazruden SAY_AGGRO1'),
(-1543019,'You are nothing, I answer a higher call!',10295,1,0,0,'vazruden SAY_AGGRO2'),
(-1543020,'The Dark Lord laughs at you!',10296,1,0,0,'vazruden SAY_AGGRO3'),
(-1543021,'Is there no one left to test me?',10293,1,0,0,'vazruden SAY_TAUNT'),
(-1543022,'It is over. Finished!',10297,1,0,0,'vazruden SAY_KILL1'),
(-1543023,'Your days are done!',10298,1,0,0,'vazruden SAY_KILL2'),
(-1543024,'My lord will be the end you all...',10299,1,0,0,'vazruden SAY_DEATH'),
(-1543025,'%s descends from the sky.',0,3,0,0,'vazruden EMOTE_DESCEND');

-- -1 544 000 MAGTHERIDON'S LAIR
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1544000,'Wretched, meddling insects. Release me and perhaps i will grant you a merciful death!',10247,6,0,0,'magtheridon SAY_TAUNT1'),
(-1544001,'Vermin! Leeches! Take my blood and choke on it!',10248,6,0,0,'magtheridon SAY_TAUNT2'),
(-1544002,'Illidan is an arrogant fool. I will crush him and reclaim Outland as my own.',10249,6,0,0,'magtheridon SAY_TAUNT3'),
(-1544003,'Away, you mindless parasites. My blood is my own!',10250,6,0,0,'magtheridon SAY_TAUNT4'),
(-1544004,'How long do you believe your pathetic sorcery can hold me?',10251,6,0,0,'magtheridon SAY_TAUNT5'),
(-1544005,'My blood will be the end of you!',10252,6,0,0,'magtheridon SAY_TAUNT6'),
(-1544006,'I... am... unleashed!',10253,1,0,0,'magtheridon SAY_FREED'),
(-1544007,'Thank you for releasing me. Now...die!',10254,1,0,0,'magtheridon SAY_AGGRO'),
(-1544008,'Not again... NOT AGAIN!',10256,1,0,0,'magtheridon SAY_BANISH'),
(-1544009,'I will not be taken so easily! Let the walls of this prison tremble... and fall!',10257,1,0,0,'magtheridon SAY_CHAMBER_DESTROY'),
(-1544010,'Did you think me weak? Soft? Who is the weak one now?!',10255,1,0,0,'magtheridon SAY_PLAYER_KILLED'),
(-1544011,'The Legion will consume you all!',10258,1,0,0,'magtheridon SAY_DEATH'),
(-1544012,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1544013,'%s begins to cast Blast Nova!',0,3,0,0,'magtheridon EMOTE_BLASTNOVA'),
(-1544014,'%s''s bonds begin to weaken!',0,2,0,0,'magtheridon EMOTE_BEGIN'),
(-1544015,'%s breaks free!',0,2,0,0,'magtheridon EMOTE_FREED'),
(-1544016,'%s is nearly free of his bonds!',0,2,0,0,'magtheridon EMOTE_NEARLY_FREE');

-- -1 545 000 THE STEAMVAULT
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1545000,'Surge forth my pets!',10360,1,0,0,'thespia SAY_SUMMON'),
(-1545001,'The depths will consume you!',10361,1,0,0,'thespia SAY_AGGRO_1'),
(-1545002,'Meet your doom, surface dwellers!',10362,1,0,0,'thespia SAY_AGGRO_2'),
(-1545003,'You will drown in blood!',10363,1,0,0,'thespia SAY_AGGRO_3'),
(-1545004,'To the depths of oblivion with you!',10364,1,0,0,'thespia SAY_SLAY_1'),
(-1545005,'For my lady and master!',10365,1,0,0,'thespia SAY_SLAY_2'),
(-1545006,'Our matron will be.. the end of.. you..',10366,1,0,0,'thespia SAY_DEAD'),

(-1545007,'I\'m bringin\' the pain!',10367,1,0,0,'mekgineer SAY_MECHANICS'),
(-1545008,'You\'re in for a world of hurt!',10368,1,0,0,'mekgineer SAY_AGGRO_1'),
(-1545009,'Eat hot metal, scumbag!',10369,1,0,0,'mekgineer SAY_AGGRO_2'),
(-1545010,'I\'ll come over there!',10370,1,0,0,'mekgineer SAY_AGGRO_3'),
(-1545011,'I\'m bringin\' the pain!',10371,1,0,0,'mekgineer SAY_AGGRO_4'),
(-1545012,'You just got served, punk!',10372,1,0,0,'mekgineer SOUND_SLAY_1'),
(-1545013,'I own you!',10373,1,0,0,'mekgineer SOUND_SLAY_2'),
(-1545014,'Have fun dyin\', cupcake!',10374,1,0,0,'mekgineer SOUND_SLAY_3'),
(-1545015,'Mommy!',10375,1,0,0,'mekgineer SAY_DEATH'),

(-1545016,'You deem yourselves worthy simply because you bested my guards? Our work here will not be compromised!',10390,1,0,0,'kalithresh SAY_INTRO'),
(-1545017,'This is not nearly over...',10391,1,0,0,'kalithresh SAY_REGEN'),
(-1545018,'Your head will roll!',10392,1,0,0,'kalithresh SAY_AGGRO1'),
(-1545019,'I despise all of your kind!',10393,1,0,0,'kalithresh SAY_AGGRO2'),
(-1545020,'Ba\'ahntha sol\'dorei!',10394,1,0,0,'kalithresh SAY_AGGRO3'),
(-1545021,'Scram, surface filth!',10395,1,0,0,'kalithresh SAY_SLAY1'),
(-1545022,'Ah ha ha ha ha ha ha!',10396,1,0,0,'kalithresh SAY_SLAY2'),
(-1545023,'For her Excellency... for... Vashj!',10397,1,0,0,'kalithresh SAY_DEATH'),

(-1545024,'Enjoy the storm, warm bloods!',0,1,0,0,'thespia SAY_CLOUD');

-- -1 546 000 THE UNDERBOG

-- -1 547 000 THE SLAVE PENS
INSERT INTO script_texts(entry, content_default, sound, type, language, emote, comment) VALUES
(-1547000,'Hey!  Over here!  Yeah, over here... I''m in this cage!!!',0,1,0,0,'Naturalist Bite on Areatrigger');

-- -1 548 000 SERPENTSHRINE CAVERN
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1548000,'I cannot allow you to interfere!',11289,1,0,0,'hydross SAY_AGGRO'),
(-1548001,'Better, much better.',11290,1,0,0,'hydross SAY_SWITCH_TO_CLEAN'),
(-1548002,'They have forced me to this...',11291,1,0,0,'hydross SAY_CLEAN_SLAY1'),
(-1548003,'I have no choice.',11292,1,0,0,'hydross SAY_CLEAN_SLAY2'),
(-1548004,'I am... released...',11293,1,0,0,'hydross SAY_CLEAN_DEATH'),
(-1548005,'Aaghh, the poison...',11297,1,0,0,'hydross SAY_SWITCH_TO_CORRUPT'),
(-1548006,'I will purge you from this place.',11298,1,0,0,'hydross SAY_CORRUPT_SLAY1'),
(-1548007,'You are no better than they!',11299,1,0,0,'hydross SAY_CORRUPT_SLAY2'),
(-1548008,'You are the disease, not I',11300,1,0,0,'hydross SAY_CORRUPT_DEATH'),

(-1548009,'Finally, my banishment ends!',11312,1,0,0,'leotheras SAY_AGGRO'),
(-1548010,'Be gone, trifling elf.  I am in control now!',11304,1,0,0,'leotheras SAY_SWITCH_TO_DEMON'),
(-1548011,'We all have our demons...',11305,1,0,0,'leotheras SAY_INNER_DEMONS'),
(-1548012,'I have no equal.',11306,1,0,0,'leotheras SAY_DEMON_SLAY1'),
(-1548013,'Perish, mortal.',11307,1,0,0,'leotheras SAY_DEMON_SLAY2'),
(-1548014,'Yes, YES! Ahahah!',11308,1,0,0,'leotheras SAY_DEMON_SLAY3'),
(-1548015,'Kill! KILL!',11314,1,0,0,'leotheras SAY_NIGHTELF_SLAY1'),
(-1548016,'That\'s right! Yes!',11315,1,0,0,'leotheras SAY_NIGHTELF_SLAY2'),
(-1548017,'Who\'s the master now?',11316,1,0,0,'leotheras SAY_NIGHTELF_SLAY3'),
(-1548018,'No... no! What have you done? I am the master! Do you hear me? I am... aaggh! Can\'t... contain him...',11313,1,0,0,'leotheras SAY_FINAL_FORM'),
(-1548019,'At last I am liberated. It has been too long since I have tasted true freedom!',11309,1,0,0,'leotheras SAY_FREE'),
(-1548020,'You cannot kill me! Fools, I\'ll be back! I\'ll... aarghh...',11317,1,0,0,'leotheras SAY_DEATH'),

(-1548021,'Guards, attention! We have visitors....',11277,1,0,0,'karathress SAY_AGGRO'),
(-1548022,'Your overconfidence will be your undoing! Guards, lend me your strength!',11278,1,0,0,'karathress SAY_GAIN_BLESSING'),
(-1548023,'Go on, kill them! I\'ll be the better for it!',11279,1,0,0,'karathress SAY_GAIN_ABILITY1'),
(-1548024,'I am more powerful than ever!',11280,1,0,0,'karathress SAY_GAIN_ABILITY2'),
(-1548025,'More knowledge, more power!',11281,1,0,0,'karathress SAY_GAIN_ABILITY3'),
(-1548026,'Land-dwelling scum!',11282,1,0,0,'karathress SAY_SLAY1'),
(-1548027,'Alana be\'lendor!',11283,1,0,0,'karathress SAY_SLAY2'),
(-1548028,'I am rid of you.',11284,1,0,0,'karathress SAY_SLAY3'),
(-1548029,'Her ... excellency ... awaits!',11285,1,0,0,'karathress SAY_DEATH'),

(-1548030,'Flood of the deep, take you!',11321,1,0,0,'morogrim SAY_AGGRO'),
(-1548031,'By the Tides, kill them at once!',11322,1,0,0,'morogrim SAY_SUMMON1'),
(-1548032,'Destroy them my subjects!',11323,1,0,0,'morogrim SAY_SUMMON2'),
(-1548033,'There is nowhere to hide!',11324,1,0,0,'morogrim SAY_SUMMON_BUBL1'),
(-1548034,'Soon it will be finished!',11325,1,0,0,'morogrim SAY_SUMMON_BUBL2'),
(-1548035,'It is done!',11326,1,0,0,'morogrim SAY_SLAY1'),
(-1548036,'Strugging only makes it worse.',11327,1,0,0,'morogrim SAY_SLAY2'),
(-1548037,'Only the strong survive.',11328,1,0,0,'morogrim SAY_SLAY3'),
(-1548038,'Great... currents of... Ageon.',11329,1,0,0,'morogrim SAY_DEATH'),
(-1548039,'%s sends his enemies to their watery graves!',0,3,0,0,'morogrim EMOTE_WATERY_GRAVE'),
(-1548040,'The violent earthquake has alerted nearby Murlocs!',0,3,0,0,'morogrim EMOTE_EARTHQUAKE'),
(-1548041,'%s summons watery globules!',0,3,0,0,'morogrim EMOTE_WATERY_GLOBULES'),

(-1548042,'Water is life. It has become a rare commodity here in Outland. A commodity that we alone shall control. We are the Highborne, and the time has come at last for us to retake our rightful place in the world!',11531,6,0,0,'vashj SAY_INTRO'),
(-1548043,'I\'ll split you from stem to stern!',11532,1,0,0,'vashj SAY_AGGRO1'),
(-1548044,'Victory to Lord Illidan!',11533,1,0,0,'vashj SAY_AGGRO2'),
(-1548045,'I spit on you, surface filth!',11534,1,0,0,'vashj SAY_AGGRO3'),
(-1548046,'Death to the outsiders!',11535,1,0,0,'vashj SAY_AGGRO4'),
(-1548047,'I did not wish to lower myself by engaging your kind, but you leave me little choice...',11538,1,0,0,'vashj SAY_AGGRO5'),
(-1548048,'The time is now! Leave none standing!',11539,1,0,0,'vashj SAY_PHASE2'),
(-1548049,'You may want to take cover.',11540,1,0,0,'vashj SAY_PHASE3'),
(-1548050,'Straight to the heart!',11536,1,0,0,'vashj SAY_BOWSHOT1'),
(-1548051,'Seek your mark!',11537,1,0,0,'vashj SAY_BOWSHOT2'),
(-1548052,'Your time ends now!',11541,1,0,0,'vashj SAY_SLAY1'),
(-1548053,'You have failed!',11542,1,0,0,'vashj SAY_SLAY2'),
(-1548054,'Be\'lemer an-delei!',11543,1,0,0,'vashj SAY_SLAY3'),
(-1548055,'Lord Illidan, I... I am... sorry.',11544,1,0,0,'vashj SAY_DEATH'),

(-1548056,'%s takes a deep breath!',0,3,0,0,'lurker below EMOTE_DEEP_BREATH');

-- -1 550 000 THE EYE
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1550000,'Alert! You are marked for extermination.',11213,1,0,0,'voidreaver SAY_AGGRO'),
(-1550001,'Extermination, successful.',11215,1,0,0,'voidreaver SAY_SLAY1'),
(-1550002,'Imbecile life form, no longer functional.',11216,1,0,0,'voidreaver SAY_SLAY2'),
(-1550003,'Threat neutralized.',11217,1,0,0,'voidreaver SAY_SLAY3'),
(-1550004,'Systems... shutting... d-o-w-n...',11214,1,0,0,'voidreaver SAY_DEATH'),
(-1550005,'Alternative measure commencing...',11218,1,0,0,'voidreaver SAY_POUNDING1'),
(-1550006,'Calculating force parameters...',11219,1,0,0,'voidreaver SAY_POUNDING2'),

(-1550007,'Tal anu\'men no sin\'dorei!',11134,1,0,0,'solarian SAY_AGGRO'),
(-1550008,'Ha ha ha! You are hopelessly outmatched!',11139,1,0,0,'solarian SAY_SUMMON1'),
(-1550009,'I will crush your delusions of grandeur!',11140,1,0,0,'solarian SAY_SUMMON2'),
(-1550010,'Your soul belongs to the Abyss!',11136,1,0,0,'solarian SAY_KILL1'),
(-1550011,'By the blood of the Highborne!',11137,1,0,0,'solarian SAY_KILL2'),
(-1550012,'For the Sunwell!',11138,1,0,0,'solarian SAY_KILL3'),
(-1550013,'The warmth of the sun... awaits.',11135,1,0,0,'solarian SAY_DEATH'),
(-1550014,'Enough of this!  Now I call upon the fury of the cosmos itself.',0,1,0,0,'solarian SAY_VOIDA'),
(-1550015,'I become ONE... with the VOID!',0,1,0,0,'solarian SAY_VOIDB'),

(-1550016,'Energy. Power. My people are addicted to it... a dependence made manifest after the Sunwell was destroyed. Welcome... to the future. A pity you are too late to stop it. No one can stop me now! Selama ashal''anore!',11256,1,0,0,'kaelthas SAY_INTRO note: was changed sometime after TBC'),
(-1550017,'Capernian will see to it that your stay here is a short one.',11257,1,0,0,'kaelthas SAY_INTRO_CAPERNIAN'),
(-1550018,'Well done, you have proven worthy to test your skills against my master engineer, Telonicus.',11258,1,0,0,'kaelthas SAY_INTRO_TELONICUS'),
(-1550019,'Let us see how your nerves hold up against the Darkener, Thaladred!',11259,1,0,0,'kaelthas SAY_INTRO_THALADRED'),
(-1550020,'You have persevered against some of my best advisors... but none can withstand the might of the Blood Hammer. Behold, Lord Sanguinar!',11260,1,0,0,'kaelthas SAY_INTRO_SANGUINAR'),
(-1550021,'As you see, I have many weapons in my arsenal....',11261,1,0,0,'kaelthas SAY_PHASE2_WEAPON'),
(-1550022,'Perhaps I underestimated you. It would be unfair to make you fight all four advisors at once, but... fair treatment was never shown to my people. I''m just returning the favor.',11262,1,0,0,'kaelthas SAY_PHASE3_ADVANCE'),
(-1550023,'Alas, sometimes one must take matters into one''s own hands. Balamore shanal!',11263,1,0,0,'kaelthas SAY_PHASE4_INTRO2'),
(-1550024,'I have not come this far to be stopped! The future I have planned will not be jeopardized! Now you will taste true power!!',11273,1,0,0,'kaelthas SAY_PHASE5_NUTS'),
(-1550025,'You will not prevail.',11270,1,0,0,'kaelthas SAY_SLAY1'),
(-1550026,'You gambled...and lost.',11271,1,0,0,'kaelthas SAY_SLAY2'),
(-1550027,'This was Child\'s play.',11272,1,0,0,'kaelthas SAY_SLAY3'),
(-1550028,'Obey me.',11268,1,0,0,'kaelthas SAY_MINDCONTROL1'),
(-1550029,'Bow to my will.',11269,1,0,0,'kaelthas SAY_MINDCONTROL2'),
(-1550030,'Let us see how you fare when your world is turned upside down.',11264,1,0,0,'kaelthas SAY_GRAVITYLAPSE1'),
(-1550031,'Having trouble staying grounded?',11265,1,0,0,'kaelthas SAY_GRAVITYLAPSE2'),
(-1550032,'Anar''anel belore!',11267,1,0,0,'kaelthas SAY_SUMMON_PHOENIX1'),
(-1550033,'By the power of the sun!',11266,1,0,0,'kaelthas SAY_SUMMON_PHOENIX2'),
(-1550034,'For... Quel''...Thalas!',11274,1,0,0,'kaelthas SAY_DEATH'),

(-1550035,'Prepare yourselves!',11203,1,0,0,'thaladred SAY_THALADRED_AGGRO'),
(-1550036,'Forgive me, my prince! I have... failed.',11204,1,0,0,'thaladred SAY_THALADRED_DEATH'),
(-1550037,'%s sets eyes on $n!',0,2,0,0,'thaladred EMOTE_THALADRED_GAZE'),

(-1550038,'Blood for blood!',11152,1,0,0,'sanguinar SAY_SANGUINAR_AGGRO'),
(-1550039,'NO! I... will... not...',11153,1,0,0,'sanguinar SAY_SANGUINAR_DEATH'),

(-1550040,'The sin''dorei reign supreme!',11117,1,0,0,'capernian SAY_CAPERNIAN_AGGRO'),
(-1550041,'This is not over!',11118,1,0,0,'capernian SAY_CAPERNIAN_DEATH'),

(-1550042,'Anar''alah belore!',11157,1,0,0,'telonicus SAY_TELONICUS_AGGRO'),
(-1550043,'More perils... await...',11158,1,0,0,'telonicus SAY_TELONICUS_DEATH'),

(-1550044,'%s begins to cast Pyroblast!',0,3,0,0,'kaelthas EMOTE_PYROBLAST');

-- -1 552 000 THE ARCATRAZ
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1552000,'It is a small matter to control the mind of the weak... for I bear allegiance to powers untouched by time, unmoved by fate. No force on this world or beyond harbors the strength to bend our knee... not even the mighty Legion!',11122,1,0,0,'skyriss SAY_INTRO'),
(-1552001,'Bear witness to the agent of your demise!',11123,1,0,0,'skyriss SAY_AGGRO'),
(-1552002,'Your fate is written!',11124,1,0,0,'skyriss SAY_KILL_1'),
(-1552003,'The chaos I have sown here is but a taste...',11125,1,0,0,'skyriss SAY_KILL_2'),
(-1552004,'You will do my bidding, weakling.',11127,1,0,0,'skyriss SAY_MIND_1'),
(-1552005,'Your will is no longer your own.',11128,1,0,0,'skyriss SAY_MIND_2'),
(-1552006,'Flee in terror!',11129,1,0,0,'skyriss SAY_FEAR_1'),
(-1552007,'I will show you horrors undreamed of!',11130,1,0,0,'skyriss SAY_FEAR_2'),
(-1552008,'We span the universe, as countless as the stars!',11131,1,0,0,'skyriss SAY_IMAGE'),
(-1552009,'I am merely one of... infinite multitudes.',11126,1,0,0,'skyriss SAY_DEATH'),

(-1552010,'Where in Bonzo\'s brass buttons am I? And who are-- yaaghh, that\'s one mother of a headache!',11171,1,0,0,'millhouse SAY_INTRO_1'),
(-1552011,'\"Lowly\"? I don\'t care who you are friend, no one refers to the mighty Millhouse Manastorm as \"Lowly\"! I have no idea what goes on here, but I will gladly join your fight against this impudent imbecile! Prepare to defend yourself, cretin!',11172,1,0,0,'millhouse SAY_INTRO_2'),
(-1552012,'I just need to get some things ready first. You guys go ahead and get started. I need to summon up some water...',11173,1,0,0,'millhouse SAY_WATER'),
(-1552013,'Fantastic! Next, some protective spells. Yes! Now we\'re cookin\'',11174,1,0,0,'millhouse SAY_BUFFS'),
(-1552014,'And of course i\'ll need some mana. You guys are gonna love this, just wait.',11175,1,0,0,'millhouse SAY_DRINK'),
(-1552015,'Aaalllriiiight!! Who ordered up an extra large can of whoop-ass?',11176,1,0,0,'millhouse SAY_READY'),
(-1552016,'I didn\'t even break a sweat on that one.',11177,1,0,0,'millhouse SAY_KILL_1'),
(-1552017,'You guys, feel free to jump in anytime.',11178,1,0,0,'millhouse SAY_KILL_2'),
(-1552018,'I\'m gonna light you up, sweet cheeks!',11179,1,0,0,'millhouse SAY_PYRO'),
(-1552019,'Ice, ice, baby!',11180,1,0,0,'millhouse SAY_ICEBLOCK'),
(-1552020,'Heal me! Oh, for the love of all that is holy, HEAL me! I\'m dying!',11181,1,0,0,'millhouse SAY_LOWHP'),
(-1552021,'You\'ll be hearing from my lawyer...',11182,1,0,0,'millhouse SAY_DEATH'),
(-1552022,'Who\'s bad? Who\'s bad? That\'s right: we bad!',11183,1,0,0,'millhouse SAY_COMPLETE'),

(-1552023,'I knew the prince would be angry but, I... I have not been myself. I had to let them out! The great one speaks to me, you see. Wait--outsiders. Kael\'thas did not send you! Good... I\'ll just tell the prince you released the prisoners!',11222,1,0,0,'mellichar YELL_INTRO1'),
(-1552024,'The naaru kept some of the most dangerous beings in existence here in these cells. Let me introduce you to another...',11223,1,0,0,'mellichar YELL_INTRO2'),
(-1552025,'Yes, yes... another! Your will is mine!',11224,1,0,0,'mellichar YELL_RELEASE1'),
(-1552026,'Behold another terrifying creature of incomprehensible power!',11225,1,0,0,'mellichar YELL_RELEASE2A'),
(-1552027,'What is this? A lowly gnome? I will do better, O\'great one.',11226,1,0,0,'mellichar YELL_RELEASE2B'),
(-1552028,'Anarchy! Bedlam! Oh, you are so wise! Yes, I see it now, of course!',11227,1,0,0,'mellichar YELL_RELEASE3'),
(-1552029,'One final cell remains. Yes, O\'great one, right away!',11228,1,0,0,'mellichar YELL_RELEASE4'),
(-1552030,'Welcome, O\'great one. I am your humble servant.',11229,1,0,0,'mellichar YELL_WELCOME'),

(-1552031,'It is unwise to anger me.',11086,1,0,0,'dalliah SAY_AGGRO'),
(-1552032,'Ahh... That is much better.',11091,1,0,0,'dalliah SAY_HEAL_1'),
(-1552033,'Ahh... Just what I needed.',11092,1,0,0,'dalliah SAY_HEAL_2'),
(-1552034,'Completely ineffective. Just like someone else I know.',11087,1,0,0,'dalliah SAY_KILL_1'),
(-1552035,'You chose the wrong opponent.',11088,1,0,0,'dalliah SAY_KILL_2'),
(-1552036,'I\'ll cut you to pieces!',11090,1,0,0,'dalliah SAY_WHIRLWIND_1'),
(-1552037,'Reap the Whirlwind!',11089,1,0,0,'dalliah SAY_WHIRLWIND_2'),
(-1552038,'Now I\'m really... angry...',11093,1,0,0,'dalliah SAY_DEATH'),

(-1552039,'Have you come to kill Dalliah? Can I watch?',11237,1,0,1,'soccothrates SAY_DALLIAH_AGGRO_1'),
(-1552040,'This may be the end for you, Dalliah. What a shame that would be.',11245,1,0,1,'soccothrates SAY_DALLIAH_TAUNT_1'),
(-1552041,'Facing difficulties, Dalliah? How nice.',11244,1,0,1,'soccothrates SAY_DALLIAH_TAUNT_2'),
(-1552042,'I suggest a new strategy, you draw the attackers while I gather reinforcements. Hahaha!',11246,1,0,1,'soccothrates SAY_DALLIAH_TAUNT_3'),
(-1552043,'Finally! Well done!',11247,1,0,66,'soccothrates SAY_DALLIAH_DEAD'),
(-1552044,'On guard!',11241,1,0,0,'soccothrates SAY_CHARGE_1'),
(-1552045,'Defend yourself, for all the good it will do...',11242,1,0,0,'soccothrates SAY_CHARGE_2'),
(-1552046,'Knew this was... the only way out',11243,1,0,0,'soccothrates SAY_DEATH'),
(-1552047,'Yes, that was quite satisfying',11239,1,0,0,'soccothrates SAY_KILL'),
(-1552048,'At last, a target for my frustrations!',11238,1,0,0,'soccothrates SAY_AGGRO'),

(-1552049,'Did you call on me?',11236,1,0,397,'soccothrates SAY_INTRO_1'),
(-1552050,'Why would I call on you?',0,1,0,396,'dalliah SAY_INTRO_2'),
(-1552051,'To do your heavy lifting, most likely.',0,1,0,396,'soccothrates SAY_INTRO_3'),
(-1552052,'When I need someone to prance around like an overstuffed peacock, I''ll call on you.',0,1,0,396,'dalliah SAY_INTRO_4'),
(-1552053,'Then I\'ll commit myself to ignoring you.',0,1,0,396,'soccothrates SAY_INTRO_5'),
(-1552054,'What would you know about commitment, sheet-sah?',0,1,0,396,'dalliah SAY_INTRO_6'),
(-1552055,'You\'re the one who should be-- Wait, we have company...',0,1,0,396,'soccothrates SAY_INTRO_7');

-- -1 553 000 THE BOTANICA
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1553000,'What are you doing? These specimens are very delicate!',11144,1,0,0,'freywinn SAY_AGGRO'),
(-1553001,'Your life cycle is now concluded!',11145,1,0,0,'freywinn SAY_KILL_1'),
(-1553002,'You will feed the worms.',11146,1,0,0,'freywinn SAY_KILL_2'),
(-1553003,'Endorel aluminor!',11147,1,0,0,'freywinn SAY_TREE_1'),
(-1553004,'Nature bends to my will!',11148,1,0,0,'freywinn SAY_TREE_2'),
(-1553005,'The specimens...must be preserved.',11149,1,0,0,'freywinn SAY_DEATH'),

(-1553006,'%s emits a strange noise.',0,2,0,0,'laj EMOTE_SUMMON'),

(-1553007,'Who disturbs this sanctuary?',11230,1,0,0,'warp SAY_AGGRO'),
(-1553008,'You must die! But wait: this does not--No, no... you must die!',11231,1,0,0,'warp SAY_SLAY_1'),
(-1553009,'What am I doing? Why do I...',11232,1,0,0,'warp SAY_SLAY_2'),
(-1553010,'Children, come to me!',11233,1,0,0,'warp SAY_SUMMON_1'),
(-1553011,'Maybe this is not--No, we fight! Come to my aid.',11234,1,0,0,'warp SAY_SUMMON_2'),
(-1553012,'So... confused. Do not... belong here!',11235,1,0,0,'warp SAY_DEATH'),
(-1553013, 'You won\'t... get far.',11212,1,0,0,'Thorngrin YELL on Death'),
(-1553014, 'I hate to say I told you so...',11207,1,0,0, 'Thorngrind YELL on Player Kill'),
(-1553015, 'Your life will be mine!',11208,1,0,0,'Thorngrin YELL on Sacrifice'),
(-1553016, 'You seek a prize, eh? How about death?',11206,1,0,0,'Thorngrin YELL on 20% HP'),
(-1553017, 'I revel in your pain!',11209,1,0,0,'Thorngrin YELL on 50% HP'),
(-1553018, 'I\'ll incinerate you!',11210,1,0,0,'Thorngrin YELL on Hellfire 1'),
(-1553019, 'Scream while you burn! ',11211,1,0,0,'Thorngrin YELL on Hellfire 2'),
(-1553020, 'What aggravation is this? You will die!',11205,1,0,0,'Thorngrin YELL on Aggro');

-- -1 554 000 THE MECHANAR
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1554000,'Think you can hurt me, huh? Think I\'m afraid of you?!',11165,1,0,0,'Say on Ability use 1'),
(-1554001,'Go ahead, gimme your best shot. I can take it!',11166,1,0,0,'Say on Ability use 2'),
(-1554002,'Bully!',11167,1,0,0, 'Say on Death'),
(-1554003,'Can\'t say I didn\'t warn you!',11163,1,0,0,'Say on Player Kill 2'),
(-1554004,'Damn, I\'m good!',11164,1,0,0,'Say on Player Kill 1'),
(-1554005,'You should split while you can.',11162,1,0,0,'Say on Aggro'),
(-1554006,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1554007,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1554008,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1554009,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1554010,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1554011,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1554012,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1554013,'Don\'t value your life very much, do you?',11186,1,0,0,'sepethrea SAY_AGGRO'),
(-1554014,'I am not alone.',11191,1,0,0,'sepethrea SAY_SUMMON'),
(-1554015,'Think you can take the heat?',11189,1,0,0,'sepethrea SAY_DRAGONS_BREATH_1'),
(-1554016,'Anar\'endal dracon!',11190,1,0,0,'sepethrea SAY_DRAGONS_BREATH_2'),
(-1554017,'And don\'t come back!',11187,1,0,0,'sepethrea SAY_SLAY1'),
(-1554018,'En\'dala finel el\'dal',11188,1,0,0,'sepethrea SAY_SLAY2'),
(-1554019,'Anu... bala belore...alon.',11192,1,0,0,'sepethrea SAY_DEATH'),

(-1554020,'We are on a strict timetable. You will not interfere!',11193,1,0,0,'pathaleon SAY_AGGRO'),
(-1554021,'I\'m looking for a team player...',11197,1,0,0,'pathaleon SAY_DOMINATION_1'),
(-1554022,'You work for me now!',11198,1,0,0,'pathaleon SAY_DOMINATION_2'),
(-1554023,'Time to supplement my work force.',11196,1,0,0,'pathaleon SAY_SUMMON'),
(-1554024,'I prefeer to be hands-on...',11199,1,0,0,'pathaleon SAY_ENRAGE'),
(-1554025,'A minor inconvenience.',11194,1,0,0,'pathaleon SAY_SLAY_1'),
(-1554026,'Looks like you lose.',11195,1,0,0,'pathaleon SAY_SLAY_2'),
(-1554027,'The project will... continue.',11200,1,0,0,'pathaleon SAY_DEATH'),
(-1554028,'I have been waiting for you!',0,1,0,53,'pathaleon SAY_INTRO');

-- -1 555 000 SHADOW LABYRINTH
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1555000,'Infidels have invaded the sanctuary! Sniveling pests...You have yet to learn the true meaning of agony!',10473,1,0,0,'hellmaw SAY_INTRO'),
(-1555001,'Pathetic mortals! You will pay dearly!',10475,1,0,0,'hellmaw SAY_AGGRO1'),
(-1555002,'I will break you!',10476,1,0,0,'hellmaw SAY_AGGRO2'),
(-1555003,'Finally! Something to relieve the tedium!',10477,1,0,0,'hellmaw SAY_AGGRO3'),
(-1555004,'Aid me, you fools, before it\'s too late!',10474,1,0,0,'hellmaw SAY_HELP'),
(-1555005,'Do you fear death?',10478,1,0,0,'hellmaw SAY_SLAY1'),
(-1555006,'This is the part I enjoy most.',10479,1,0,0,'hellmaw SAY_SLAY2'),
(-1555007,'Do not...grow...overconfident, mortal.',10480,1,0,0,'hellmaw SAY_DEATH'),

(-1555008,'All flesh must burn.',10482,1,0,0,'blackhearth SAY_INTRO1'),
(-1555009,'All creation must be unmade!',10483,1,0,0,'blackhearth SAY_INTRO2'),
(-1555010,'Power will be yours!',10484,1,0,0,'blackhearth SAY_INTRO3'),
(-1555011,'You\'ll be sorry!',10486,1,0,0,'blackhearth SAY_AGGRO1'),
(-1555012,'Time for fun!',10487,1,0,0,'blackhearth SAY_AGGRO2'),
(-1555013,'I see dead people!',10488,1,0,0,'blackhearth SAY_AGGRO3'),
(-1555014,'No comin\' back for you!',10489,1,0,0,'blackhearth SAY_SLAY1'),
(-1555015,'Nice try!',10490,1,0,0,'blackhearth SAY_SLAY2'),
(-1555016,'Help us, hurry!',10485,1,0,0,'blackhearth SAY_HELP'),
(-1555017,'This... no... good...',10491,1,0,0,'blackhearth SAY_DEATH'),

(-1555018,'Be ready for Dark One\'s return.',10492,1,0,0,'blackhearth SAY2_INTRO1'),
(-1555019,'So we have place in new universe.',10493,1,0,0,'blackhearth SAY2_INTRO2'),
(-1555020,'Dark one promise!',10494,1,0,0,'blackhearth SAY2_INTRO3'),
(-1555021,'You\'ll be sorry!',10496,1,0,0,'blackhearth SAY2_AGGRO1'),
(-1555022,'Time to kill!',10497,1,0,0,'blackhearth SAY2_AGGRO2'),
(-1555023,'You be dead people!',10498,1,0,0,'blackhearth SAY2_AGGRO3'),
(-1555024,'Now you gone for good.',10499,1,0,0,'blackhearth SAY2_SLAY1'),
(-1555025,'You failed, haha haha',10500,1,0,0,'blackhearth SAY2_SLAY2'),
(-1555026,'Help us, hurry!',10495,1,0,0,'blackhearth SAY2_HELP'),
(-1555027,'Arrgh, aah...ahhh',10501,1,0,0,'blackhearth SAY2_DEATH'),

(-1555028,'Keep your minds focused for the days of reckoning are close at hand. Soon, the destroyer of worlds will return to make good on his promise. Soon the destruction of all that is will begin!',10522,1,0,0,'vorpil SAY_INTRO'),
(-1555029,'I\'ll make an offering of your blood!',10524,1,0,0,'vorpil SAY_AGGRO1'),
(-1555030,'You\'ll be a fine example, for the others.',10525,1,0,0,'vorpil SAY_AGGRO2'),
(-1555031,'Good, a worthy sacrifice.',10526,1,0,0,'vorpil SAY_AGGRO3'),
(-1555032,'Come to my aid, heed your master now!',10523,1,0,0,'vorpil SAY_HELP'),
(-1555033,'I serve with pride.',10527,1,0,0,'vorpil SAY_SLAY1'),
(-1555034,'Your death is for the greater cause!',10528,1,0,0,'vorpil SAY_SLAY2'),
(-1555035,'I give my life... Gladly.',10529,1,0,0,'vorpil SAY_DEATH'),

(-1555036,'%s draws energy from the air.',0,2,0,0,'murmur EMOTE_SONIC_BOOM');

-- -1 556 000 SETHEKK HALLS
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1556000,'I have pets..<squawk>..of my own!',10502,1,0,0,'syth SAY_SUMMON'),
(-1556001,'Hrrmm.. Time to.. hrrm.. make my move.',10503,1,0,0,'syth SAY_AGGRO_1'),
(-1556002,'Nice pets..hrm.. Yes! <squawking>',10504,1,0,0,'syth SAY_AGGRO_2'),
(-1556003,'Nice pets have.. weapons. No so..<squawk>..nice.',10505,1,0,0,'syth SAY_AGGRO_3'),
(-1556004,'Death.. meeting life is.. <squawking>',10506,1,0,0,'syth SAY_SLAY_1'),
(-1556005,'Uhn.. Be free..<squawk>',10507,1,0,0,'syth SAY_SLAY_2'),
(-1556006,'No more life..hrm. No more pain. <squawks weakly>',10508,1,0,0,'syth SAY_DEATH'),

(-1556007,'<squawk>..Trinkets yes pretty Trinkets..<squawk>..power, great power.<squawk>..power in Trinkets..<squawk>',10557,1,0,0,'ikiss SAY_INTRO'),
(-1556008,'You make war on Ikiss?..<squawk>',10554,1,0,0,'ikiss SAY_AGGRO_1'),
(-1556009,'Ikiss cut you pretty..<squawk>..slice you. Yes!',10555,1,0,0,'ikiss SAY_AGGRO_2'),
(-1556010,'No escape for..<squawk>..for you',10556,1,0,0,'ikiss SAY_AGGRO_3'),
(-1556011,'You die..<squawk>..stay away from Trinkets',10558,1,0,0,'ikiss SAY_SLAY_1'),
(-1556012,'<squawk>',10559,1,0,0,'ikiss SAY_SLAY_2'),
(-1556013,'Ikiss will not..<squawk>..die',10560,1,0,0,'ikiss SAY_DEATH'),
(-1556015,'%s begins to channel arcane energy...',0,3,0,0,'ikiss EMOTE_ARCANE_EXP'),

(-1556016,'No! How can this be?',0,1,0,0,'anzu SAY_INTRO_1'),
(-1556017,'Pain will be the price for your insolence! You cannot stop me from claiming the Emerald Dream as my own!',0,1,0,0,'anzu SAY_INTRO_2'),
(-1556018,'Awaken, my children and assist your master!',0,1,0,0,'anzu SAY_BANISH'),
(-1556019,'Your magics shall be your undoing... ak-a-ak...',0,5,0,0,'anzu SAY_WHISPER_MAGIC_1'),
(-1556020,'%s returns to stone.',0,2,0,0,'anzu EMOTE_BIRD_STONE'),
(-1556021,'Your powers... ak-ak... turn against you...',0,5,0,0,'anzu SAY_WHISPER_MAGIC_2'),
(-1556022,'Your spells... ke-kaw... are weak magics... easy to turn against you...',0,5,0,0,'anzu SAY_WHISPER_MAGIC_3');

-- -1 557 000 MANA TOMBS
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1557000,'What is this? You must forgive me, but I was not expecting company. As you can see, we are somewhat preoccupied right now. But no matter. As I am a gracious host, I will tend to you... personally.',10539,1,0,0,'shaffar SAY_INTRO'),
(-1557001,'We have not yet been properly introduced.',10541,1,0,0,'shaffar SAY_AGGRO_1'),
(-1557002,'An epic battle. How exciting!',10542,1,0,0,'shaffar SAY_AGGRO_2'),
(-1557003,'I have longed for a good adventure.',10543,1,0,0,'shaffar SAY_AGGRO_3'),
(-1557004,'It has been... entertaining.',10544,1,0,0,'shaffar SAY_SLAY_1'),
(-1557005,'And now we part company.',10545,1,0,0,'shaffar SAY_SLAY_2'),
(-1557006,'I have such fascinating things to show you.',10540,1,0,0,'shaffar SAY_SUMMON'),
(-1557007,'I must bid you... farewell.',10546,1,0,0,'shaffar SAY_DEAD'),

(-1557008,'I will feed on your soul.',10561,1,0,0,'pandemonius SAY_AGGRO_1'),
(-1557009,'So... full of life!',10562,1,0,0,'pandemonius SAY_AGGRO_2'),
(-1557010,'Do not... resist.',10563,1,0,0,'pandemonius SAY_AGGRO_3'),
(-1557011,'Yes! I am... empowered!',10564,1,0,0,'pandemonius SAY_KILL_1'),
(-1557012,'More... I must have more!',10565,1,0,0,'pandemonius SAY_KILL_2'),
(-1557013,'To the void... once... more..',10566,1,0,0,'pandemonius SAY_DEATH'),
(-1557014,'%s shifts into the void...',0,3,0,0,'pandemonius EMOTE_DARK_SHELL'),

(-1557015,'This should''t take very long. Just watch my back as I empty these nether collectors.',0,0,0,0,'sha\'heen SAY_ESCORT_START'),
(-1557016,'Fantastic! Let''s move on, shall we?',0,0,0,0,'sha\'heen SAY_START'),
(-1557017,'Looking at these energy levels, Shaffar was set to make a killing!',0,0,0,28,'sha\'heen SAY_FIRST_STOP'),
(-1557018,'That should do it...',0,0,0,0,'sha\'heen SAY_FIRST_STOP_COMPLETE'),
(-1557019,'Hrm, now where is the next collector?',0,0,0,0,'sha\'heen SAY_COLLECTOR_SEARCH'),
(-1557020,'Ah, there it is. Follow me, fleshling.',0,0,0,0,'sha\'heen SAY_COLLECTOR_FOUND'),
(-1557021,'There can''t be too many more of these collectors. Just keep me safe as I do my job.',0,0,0,28,'sha\'heen SAY_SECOND_STOP'),
(-1557022,'What do we have here? I thought you said the area was secure? This is now the third attack? If we make it out of here, I will definitely be deducting this from your reward. Now don''t just stand there, destroy them so I can get to that collector.',0,0,0,0,'sha\'heen SAY_THIRD_STOP'),
(-1557023,'We''re close to the exit. I''ll let you rest for about thirty seconds, but then we''re out of here.',0,0,0,0,'sha\'heen SAY_REST'),
(-1557024,'Are you ready to go?',0,0,0,0,'sha\'heen SAY_READY_GO'),
(-1557025,'Ok break time is OVER. Let''s go!',0,0,0,0,'sha\'heen SAY_BREAK_OVER'),
(-1557026,'Bravo! Bravo! Good show... I couldn''t convince you to work for me, could I? No, I suppose the needless slaughter of my employees might negatively impact your employment application.',0,1,0,0,'xiraxis SAY_SPAWN'),
(-1557027,'Your plan was a good one, Sha''heen, and you would have gotten away with it if not for one thing...',0,0,0,1,'xiraxis SAY_FINAL_STOP_1'),
(-1557028,'Oh really? And what might that be?',0,0,0,1,'sha\'heen SAY_FINAL_STOP_2'),
(-1557029,'Never underestimate the other ethereal''s greed!',0,0,0,0,'xiraxis SAY_FINAL_STOP_3'),
(-1557030,'He was right, you know. I''ll have to take that tag-line for my own... It''s not like he''ll have a use for it anymore!',0,0,0,1,'sha\'heen SAY_XIRAXIS_DEAD'),
(-1557031,'Thanks and good luck!',0,0,0,1,'sha\'heen SAY_COMPLETE'),
(-1557032,'%s checks to make sure his body is intact.',0,2,0,0,'sha\'heen EMOTE_TELEPORT'),
(-1557033,'You made it! Well done, $r. Now if you''ll excuse me, I have to get the rest of our crew inside.',0,0,0,1,'sha\'heen SAY_SPAWN'),
(-1557034,'%s expertly manipulates the control panel.',0,2,0,28,'sha\'heen EMOTE_PANEL'),
(-1557035,'Let''s not waste any time! Take anything that isn''t nailed down to the floor and teleport directly to Stormspire! Chop chop!',0,0,0,1,'sha\'heen SAY_ESCORT_READY'),

(-1557036,'I... I am free! Ethereum were planning on torturing me until I gave in to their requests. I fear that, had you not come along, I would have surely given in to their torment.',0,0,0,1,'Ambassador SAY_RELEASED_1'),
(-1557037,'Know this, $r. Within Shaffar''s chambers at the end of these tombs rests a creature of unimaginable power. It is held in check by the power of the stasis chamber. You must return to Ameer before you venture further if you wish to destroy it!',0,0,0,1,'Ambassador SAY_RELEASED_2');

-- -1 558 000 AUCHENAI CRYPTS
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1558000,'You have defiled the resting place of our ancestors. For this offense, there can be but one punishment. It is fitting that you have come to a place of the dead... for you will soon be joining them.',10509,1,0,0,'maladaar SAY_INTRO'),
(-1558001,'Rise my fallen brothers. Take form and fight!',10512,1,0,0,'maladaar SAY_SUMMON'),
(-1558002,'You will pay with your life!',10513,1,0,0,'maladaar SAY_AGGRO_1'),
(-1558003,'There\'s no turning back now!',10514,1,0,0,'maladaar SAY_AGGRO_2'),
(-1558004,'Serve your penitence!',10515,1,0,0,'maladaar SAY_AGGRO_3'),
(-1558005,'Let your mind be clouded.',10510,1,0,0,'maladaar SAY_ROAR'),
(-1558006,'Stare into the darkness of your soul.',10511,1,0,0,'maladaar SAY_SOUL_CLEAVE'),
(-1558007,'These walls will be your doom.',10516,1,0,0,'maladaar SAY_SLAY_1'),
(-1558008,'<laugh> Now, you\'ll stay for eternity!',10517,1,0,0,'maladaar SAY_SLAY_2'),
(-1558009,'This is... where.. I belong...',10518,1,0,0,'maladaar SAY_DEATH'),

(-1558010,'%s focuses on $N',0,3,0,0,'shirrak EMOTE_FOCUS');

-- -1 560 000 ESCAPE FROM DURNHOLDE (OLD HILLSBRAD)
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1560000,'Thrall! You didn\'t really think you would escape did you? You and your allies shall answer to Blackmoore - after I\'ve had my fun!',10406,0,0,1,'skarloc SAY_ENTER'),

(-1560001,'My magical power can turn back time to before Thrall\'s death, but be careful. My power to manipulate time is limited.',0,0,0,0,'image of eronzion SAY_RESET_THRALL'),
(-1560002,'I have set back the flow of time just once more. If you fail to prevent Thrall\'s death, then all is lost.',0,0,0,0,'image of eronzion SAY_RESET_THRALL_LAST'),

(-1560003,'What\'s the meaning of this? GUARDS!',0,0,0,0,'armorer SAY_CALL_GUARDS'),
(-1560004,'All that you know... will be undone.',0,0,0,0,'infinite dragon SAY_INFINITE_AGGRO_1'),
(-1560005,'Let\'s go.',0,0,0,0,'thrall hillsbrad SAY_TH_ARMORY2'),
(-1560006,'%s startles the horse with a fierce yell!',0,2,0,5,'thrall hillsbrad EMOTE_TH_STARTLE_HORSE'),
(-1560007,'I thought I saw something go into the barn.',0,0,0,0,'tarren mill lookout SAY_LOOKOUT_BARN_1'),
(-1560008,'I didn\'t see anything.',0,0,0,0,'tarren mill lookout SAY_PROTECTOR_BARN_2'),
(-1560009,'%s tries to calm the horse down.',0,2,0,0,'thrall hillsbrad EMOTE_TH_CALM_HORSE'),
(-1560010,'Something riled that horse. Let\'s go!',0,0,0,0,'tarren mill lookout SAY_PROTECTOR_BARN_3'),
(-1560011,'Taretha isn\'t here. Let\'s head into town.',0,0,0,0,'thrall hillsbrad SAY_TH_HEAD_TOWN'),
(-1560012,'She\'s not here.',0,0,0,0,'thrall hillsbrad SAY_TH_CHURCH_ENTER'),

(-1560013,'Thrall! Come outside and face your fate!',10418,1,0,0,'epoch SAY_ENTER1'),
(-1560014,'Taretha\'s life hangs in the balance. Surely you care for her. Surely you wish to save her...',10419,1,0,0,'epoch SAY_ENTER2'),
(-1560015,'Ah, there you are. I had hoped to accomplish this with a bit of subtlety, but I suppose direct confrontation was inevitable. Your future, Thrall, must not come to pass and so...you and your troublesome friends must die!',10420,1,0,0,'epoch SAY_ENTER3'),

(-1560016,'Thrall\'s trapped himself in the chapel. He can\'t escape now.',0,0,0,0,'tarren mill lookout SAY_LOOKOUT_CHURCH'),
(-1560017,'He\'s here, stop him!',0,0,0,0,'tarren mill lookout SAY_LOOKOUT_INN'),
(-1560018,'We have all the time in the world....',0,0,0,0,'infinite dragon SAY_INFINITE_AGGRO_2'),
(-1560019,'You cannot escape us!',0,0,0,0,'infinite dragon SAY_INFINITE_AGGRO_3'),
(-1560020,'Do not think you can win!',0,0,0,0,'infinite dragon SAY_INFINITE_AGGRO_4'),

(-1560021,'REUSE_ME',0,0,0,0,'REUSE_ME'),
(-1560022,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1560023,'Very well then. Let\'s go!',10465,0,0,0,'thrall hillsbrad SAY_TH_START_EVENT_PART1'),
(-1560024,'As long as we\'re going with a new plan, I may aswell pick up a weapon and some armor.',0,0,0,0,'thrall hillsbrad SAY_TH_ARMORY'),
(-1560025,'A rider approaches!',10466,0,0,0,'thrall hillsbrad SAY_TH_SKARLOC_MEET'),
(-1560026,'I\'ll never be chained again!',10467,1,0,0,'thrall hillsbrad SAY_TH_SKARLOC_TAUNT'),
(-1560027,'Very well. Tarren Mill lies just west of here. Since time is of the essence...',10468,0,0,0,'thrall hillsbrad SAY_TH_START_EVENT_PART2'),
(-1560028,'Let\'s ride!',10469,0,0,1,'thrall hillsbrad SAY_TH_MOUNTS_UP'),
(-1560029,'Taretha must be in the inn. Let\'s go.',0,0,0,0,'thrall hillsbrad SAY_TH_CHURCH_END'),
(-1560030,'Taretha! What foul magic is this?',0,0,0,0,'thrall hillsbrad SAY_TH_MEET_TARETHA'),
(-1560031,'Who or what was that?',10470,0,0,1,'thrall hillsbrad SAY_TH_EPOCH_WONDER'),
(-1560032,'No!',10471,0,0,5,'thrall hillsbrad SAY_TH_EPOCH_KILL_TARETHA'),
(-1560033,'Goodbye, Taretha. I will never forget your kindness.',10472,0,0,0,'thrall hillsbrad SAY_TH_EVENT_COMPLETE'),
(-1560034,'Things are looking grim...',10458,1,0,0,'thrall hillsbrad SAY_TH_RANDOM_LOW_HP1'),
(-1560035,'I will fight to the last!',10459,1,0,0,'thrall hillsbrad SAY_TH_RANDOM_LOW_HP2'),
(-1560036,'Taretha....',10460,1,0,0,'thrall hillsbrad SAY_TH_RANDOM_DIE1'),
(-1560037,'A good day... to die.',10461,1,0,0,'thrall hillsbrad SAY_TH_RANDOM_DIE2'),
(-1560038,'I have earned my freedom!',10448,0,0,0,'thrall hillsbrad SAY_TH_RANDOM_AGGRO1'),
(-1560039,'This day is long overdue. Out of my way!',10449,0,0,0,'thrall hillsbrad SAY_TH_RANDOM_AGGRO2'),
(-1560040,'I am a slave no longer!',10450,0,0,0,'thrall hillsbrad SAY_TH_RANDOM_AGGRO3'),
(-1560041,'Blackmoore has much to answer for!',10451,0,0,0,'thrall hillsbrad SAY_TH_RANDOM_AGGRO4'),
(-1560042,'You have forced my hand!',10452,0,0,0,'thrall hillsbrad SAY_TH_RANDOM_KILL1'),
(-1560043,'It should not have come to this!',10453,0,0,0,'thrall hillsbrad SAY_TH_RANDOM_KILL2'),
(-1560044,'I did not ask for this!',10454,0,0,0,'thrall hillsbrad SAY_TH_RANDOM_KILL3'),
(-1560045,'I am truly in your debt, strangers.',10455,0,0,0,'thrall hillsbrad SAY_TH_LEAVE_COMBAT1'),
(-1560046,'Thank you, strangers. You have given me hope.',10456,0,0,0,'thrall hillsbrad SAY_TH_LEAVE_COMBAT2'),
(-1560047,'I will not waste this chance. I will seek out my destiny.',10457,0,0,0,'thrall hillsbrad SAY_TH_LEAVE_COMBAT3'),

(-1560048,'I\'m free! Thank you all!',0,0,0,0,'taretha SAY_TA_FREE'),
(-1560049,'Thrall, you escaped!',0,0,0,0,'taretha SAY_TA_ESCAPED'),

(-1560050,'That\'s enough out of him.',0,0,0,0,'thrall hillsbrad SAY_TH_KILL_ARMORER'),
(-1560051,'That spell should wipe their memories of us and what just happened. All they should remember now is what reality would be like without the attempted temporal interference. Well done. Thrall will journey on to find his destiny, and Taretha...',0,0,0,0,'erozion SAY_WIPE_MEMORY'),
(-1560052,'Her fate is regrettably unavoidable.',0,0,0,0,'erozion SAY_ABOUT_TARETHA'),
(-1560053,'They call you a monster. But they\'re the monsters, not you. Farewell Thrall.',0,0,0,0,'taretha SAY_TA_FAREWELL'),

(-1560054,'I\'m glad you\'re safe, Taretha. None of this would have been possible without your friends. They made all of this happen.',0,0,0,0,'thrall hillsbrad SAY_TR_GLAD_SAFE'),
(-1560055,'Thrall, I\'ve never met these people before in my life.',0,0,0,0,'taretha SAY_TA_NEVER_MET'),
(-1560056,'Then who are these people?',0,0,0,0,'thrall hillsbrad SAY_TR_THEN_WHO'),
(-1560057,'I believe I can explain everything to you two if you give me a moment of your time.',0,0,0,0,'erozion SAY_PRE_WIPE'),
(-1560058,'You have done a great thing. Alas, the young warchief\'s memory of these events must be as they originally were ... Andormu awaits you in the master\'s lair.',0,0,0,0,'erozion SAY_AFTER_WIPE');

-- -1 564 000 BLACK TEMPLE
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1564000,'You will die in the name of Lady Vashj!',11450,1,0,0,'SAY_AGGRO'),
(-1564001,'Stick around!',11451,1,0,0,'SAY_NEEDLE1'),
(-1564002,'I\'ll deal with you later!',11452,1,0,0,'SAY_NEEDLE2'),
(-1564003,'Your success was short lived!',11455,1,0,0,'SAY_SLAY1'),
(-1564004,'Time for you to go!',11456,1,0,0,'SAY_SLAY2'),
(-1564005,'Bel\'anen dal\'lorei!',11453,1,0,0,'SAY_SPECIAL1'),
(-1564006,'Blood will flow!',11454,1,0,0,'SAY_SPECIAL2'),
(-1564007,'Bal\'amer ch\'itah!',11457,1,0,0,'SAY_ENRAGE1'),
(-1564008,'My patience has ran out! Die, DIE!',11458,1,0,0,'SAY_ENRAGE2'),
(-1564009,'Lord Illidan will... crush you!',11459,1,0,0,'SAY_DEATH'),

(-1564010,'%s acquires a new target!',0,3,0,0,'supremus EMOTE_NEW_TARGET'),
(-1564011,'%s punches the ground in anger!',0,3,0,0,'supremus EMOTE_PUNCH_GROUND'),
(-1564012,'The ground begins to crack open!',0,3,0,0,'supremus EMOTE_GROUND_CRACK'),

(-1564013,'No! Not yet...',11386,1,0,0,'akama shade SAY_LOW_HEALTH'),
(-1564014,'I will not last much longer...',11385,1,0,0,'akama shade SAY_DEATH'),
(-1564015,'Come out from the shadows! I\'ve returned to lead you against our true enemy! Shed your chains and raise your weapons against your Illidari masters!',0,1,0,0,'akama shade SAY_FREE'),
(-1564016,'Hail our leader! Hail Akama!',0,1,0,0,'akama shade broken SAY_BROKEN_FREE_01'),
(-1564017,'Hail Akama!',0,1,0,0,'akama shade broken SAY_BROKEN_FREE_02'),

(-1564018,'You play, you pay.',11501,1,0,0,'shahraz SAY_TAUNT1'),
(-1564019,'I\'m not impressed.',11502,1,0,0,'shahraz SAY_TAUNT2'),
(-1564020,'Enjoying yourselves?',11503,1,0,0,'shahraz SAY_TAUNT3'),
(-1564021,'So... business or pleasure?',11504,1,0,0,'shahraz SAY_AGGRO'),
(-1564022,'You seem a little tense...',11505,1,0,0,'shahraz SAY_SPELL1'),
(-1564023,'Don\'t be shy.',11506,1,0,0,'shahraz SAY_SPELL2'),
(-1564024,'I\'m all... yours.',11507,1,0,0,'shahraz SAY_SPELL3'),
(-1564025,'Easy come, easy go.',11508,1,0,0,'shahraz SAY_SLAY1'),
(-1564026,'So much for a happy ending.',11509,1,0,0,'shahraz SAY_SLAY2'),
(-1564027,'Stop toying with my emotions!',11510,1,0,0,'shahraz SAY_ENRAGE'),
(-1564028,'I wasn\'t finished.',11511,1,0,0,'shahraz SAY_DEATH'),

(-1564029,'Horde will... crush you.',11432,1,0,0,'bloodboil SOUND_AGGRO'),
(-1564030,'Time to feast!',11433,1,0,0,'bloodboil SAY_SLAY1'),
(-1564031,'More! I want more!',11434,1,0,0,'bloodboil SAY_SLAY2'),
(-1564032,'Drink your blood. Eat your flesh.',11435,1,0,0,'bloodboil SAY_SPECIAL1'),
(-1564033,'I hunger!',11436,1,0,0,'bloodboil SAY_SPECIAL2'),
(-1564034,'<babbling>',11437,1,0,0,'bloodboil SAY_ENRAGE1'),
(-1564035,'I\'ll rip the meat from your bones!',11438,1,0,0,'bloodboil SAY_ENRAGE2'),
(-1564036,'Aaaahrg...',11439,1,0,0,'bloodboil SAY_DEATH'),

(-1564037,'I was the first you know. For me the wheel of death has spun many times. So much time has passed... I have a lot of catching up to do. ',11512,1,0,0,'teron SAY_INTRO'),
(-1564038,'Vengeance is mine!',11513,1,0,0,'teron SAY_AGGRO'),
(-1564039,'I have use for you!',11514,1,0,0,'teron SAY_SLAY1'),
(-1564040,'It gets worse...',11515,1,0,0,'teron SAY_SLAY2'),
(-1564041,'What are you afraid of?',11517,1,0,0,'teron SAY_SPELL1'),
(-1564042,'Death really isn\'t so bad.',11516,1,0,0,'teron SAY_SPELL2'),
(-1564043,'Give in.',11518,1,0,0,'teron SAY_SPECIAL1'),
(-1564044,'I have something for you...',11519,1,0,0,'teron SAY_SPECIAL2'),
(-1564045,'YOU WILL SHOW THE PROPER RESPECT!',11520,1,0,0,'teron SAY_ENRAGE'),
(-1564046,'The wheel... spins... again.',11521,1,0,0,'teron SAY_DEATH'),

(-1564047,'Pain and suffering are all that await you!',11415,1,0,0,'essence SUFF_SAY_FREED'),
(-1564048,'Don\'t leave me alone!',11416,1,0,0,'essence SUFF_SAY_AGGRO'),
(-1564049,'Look at what you make me do!',11417,1,0,0,'essence SUFF_SAY_SLAY1'),
(-1564050,'I didn\'t ask for this!',11418,1,0,0,'essence SUFF_SAY_SLAY2'),
(-1564051,'The pain is only beginning...',11419,1,0,0,'essence SUFF_SAY_SLAY3'),
(-1564052,'I don\'t want to go back!',11420,1,0,0,'essence SUFF_SAY_RECAP'),
(-1564053,'Now what do I do?',11421,1,0,0,'essence SUFF_SAY_AFTER'),
(-1564054,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1564055,'You can have anything you desire... for a price.',11408,1,0,0,'essence DESI_SAY_FREED'),
(-1564056,'Fulfillment is at hand.',11409,1,0,0,'essence DESI_SAY_SLAY1'),
(-1564057,'Yes... you\'ll stay with us now...',11410,1,0,0,'essence DESI_SAY_SLAY2'),
(-1564058,'Your reach exceeds your grasp.',11412,1,0,0,'essence DESI_SAY_SLAY3'),
(-1564059,'Be careful what you wish for...',11411,1,0,0,'essence DESI_SAY_SPEC'),
(-1564060,'I\'ll be waiting...',11413,1,0,0,'essence DESI_SAY_RECAP'),
(-1564061,'I won\'t be far!',11414,1,0,0,'essence DESI_SAY_AFTER'),

(-1564062,'Beware: I live!',11399,1,0,0,'essence ANGER_SAY_FREED'),
(-1564063,'So... foolish.',11400,1,0,0,'essence ANGER_SAY_FREED2'),
(-1564064,'<maniacal cackle>',11401,1,0,0,'essence ANGER_SAY_SLAY1'),
(-1564065,'Enough. No more.',11402,1,0,0,'essence ANGER_SAY_SLAY2'),
(-1564066,'On your knees!',11403,1,0,0,'essence ANGER_SAY_SPEC'),
(-1564067,'Beware, coward.',11405,1,0,0,'essence ANGER_SAY_BEFORE'),
(-1564068,'I won\'t... be... ignored.',11404,1,0,0,'essence ANGER_SAY_DEATH'),

(-1564069,'You wish to test me?',11524,1,0,0,'council vera AGGRO'),
(-1564070,'I have better things to do...',11422,1,0,0,'council gath AGGRO'),
(-1564071,'Flee or die!',11482,1,0,0,'council mala AGGRO'),
(-1564072,'Common... such a crude language. Bandal!',11440,1,0,0,'council zere AGGRO'),

(-1564073,'Enough games!',11428,1,0,0,'council gath ENRAGE'),
(-1564074,'You wish to kill me? You first!',11530,1,0,0,'council vera ENRAGE'),
(-1564075,'For Quel\'Thalas! For the Sunwell!',11488,1,0,0,'council mala ENRAGE'),
(-1564076,'Sha\'amoor sine menoor!',11446,1,0,0,'council zere ENRAGE'),

(-1564077,'Enjoy your final moments.',11426,1,0,0,'council gath SPECIAL1'),
(-1564078,'You\'re not caught up for this!',11528,1,0,0,'council vera SPECIAL1'),
(-1564079,'No second chances!',11486,1,0,0,'council mala SPECIAL1'),
(-1564080,'Diel fin\'al.',11444,1,0,0,'council zere SPECIAL1'),

(-1564081,'You are mine!',11427,1,0,0,'council gath SPECIAL2'),
(-1564082,'Anar\'alah belore!',11529,1,0,0,'council vera SPECIAL2'),
(-1564083,'I\'m full of surprises!',11487,1,0,0,'council mala SPECIAL2'),
(-1564084,'Sha\'amoor ara mashal?',11445,1,0,0,'council zere SPECIAL2'),

(-1564085,'Selama am\'oronor!',11423,1,0,0,'council gath SLAY'),
(-1564086,'Valiant effort!',11525,1,0,0,'council vera SLAY'),
(-1564087,'My work is done.',11483,1,0,0,'council mala SLAY'),
(-1564088,'Shorel\'aran.',11441,1,0,0,'council zere SLAY'),

(-1564089,'Well done!',11424,1,0,0,'council gath SLAY_COMT'),
(-1564090,'A glorious kill!',11526,1,0,0,'council vera SLAY_COMT'),
(-1564091,'As it should be!',11484,1,0,0,'council mala SLAY_COMT'),
(-1564092,'Belesa menoor!',11442,1,0,0,'council zere SLAY_COMT'),

(-1564093,'Lord Illidan... I...',11425,1,0,0,'council gath DEATH'),
(-1564094,'You got lucky!',11527,1,0,0,'council vera DEATH'),
(-1564095,'Destiny... awaits.',11485,1,0,0,'council mala DEATH'),
(-1564096,'Diel ma\'ahn... orindel\'o.',11443,1,0,0,'council zere DEATH'),

(-1564097,'Akama. Your duplicity is hardly surprising. I should have slaughtered you and your malformed brethren long ago.',11463,1,0,0,'illidan SAY_ILLIDAN_SPEECH_1'),
(-1564098,'We\'ve come to end your reign, Illidan. My people, and all of Outland, shall be free!',11389,1,0,25,'akama(illidan) SAY_AKAMA_SPEECH_2'),
(-1564099,'Boldly said. But I remain... unconvinced.',11464,1,0,6,'illidan SAY_ILLIDAN_SPEECH_3'),
(-1564100,'The time has come! The moment is at hand!',11380,1,0,22,'akama(illidan) SAY_AKAMA_SPEECH_4'),
(-1564101,'You are not prepared!',11466,1,0,406,'illidan SAY_ILLIDAN_SPEECH_5'),
(-1564102,'Is this it, mortals? Is this all the fury you can muster?',11476,1,0,0,'illidan SAY_ILLIDAN_SPEECH_6'),
(-1564103,'Their fury pales before mine, Illidan. We have some unsettled business between us.',11491,1,0,6,'maiev SAY_MAIEV_SPEECH_7'),
(-1564104,'Maiev... How is it even possible?',11477,1,0,1,'illidan SAY_ILLIDAN_SPEECH_8'),
(-1564105,'My long hunt is finally over. Today, Justice will be done!',11492,1,0,5,'maiev SAY_MAIEV_SPEECH_9'),
(-1564106,'Feel the hatred of ten thousand years!',11470,1,0,0,'illidan SAY_FRENZY'),
(-1564107,'It is finished. You are beaten.',11496,1,0,0,'maiev SAY_MAIEV_EPILOGUE_1'),
(-1564108,'You have won... Maiev. But the huntress... is nothing without the hunt. You... are nothing... without me.',11478,1,0,0,'illidan SAY_ILLIDAN_EPILOGUE_2'),
(-1564109,'He\'s right. I feel nothing... I am... nothing.',11497,1,0,0,'maiev SAY_MAIEV_EPILOGUE_3'),
(-1564110,'Farewell, champions.',11498,1,0,0,'maiev SAY_MAIEV_EPILOGUE_4'),
(-1564111,'The Light will bless these dismal halls once again.... I swear it.',11387,1,0,0,'akama(illidan) SAY_AKAMA_EPILOGUE_5'),
(-1564112,'I can feel your hatred.',11467,1,0,0,'illidan SAY_TAUNT_1'),
(-1564113,'Give in to your fear!',11468,1,0,0,'illidan SAY_TAUNT_2'),
(-1564114,'You know nothing of power!',11469,1,0,0,'illidan SAY_TAUNT_3'),
(-1564115,'Such... arrogance!',11471,1,0,0,'illidan SAY_TAUNT_4'),
(-1564116,'That is for Naisha!',11493,1,0,0,'maiev SAY_MAIEV_TAUNT_1'),
(-1564117,'Bleed as I have bled!',11494,1,0,0,'maiev SAY_MAIEV_TAUNT_2'),
(-1564118,'There shall be no prison for you this time!',11495,1,0,0,'maiev SAY_MAIEV_TRAP'),
(-1564119,'Meet your end, demon!',11500,1,0,0,'maiev SAY_MAIEV_TAUNT_4'),
(-1564120,'Be wary friends, The Betrayer meditates in the court just beyond.',11388,1,0,0,'akama(illidan) SAY_AKAMA_BEWARE'),
(-1564121,'Come, my minions. Deal with this traitor as he deserves!',11465,1,0,0,'illidan SAY_AKAMA_MINION'),
(-1564122,'I\'ll deal with these mongrels. Strike now, friends! Strike at the betrayer!',11390,1,0,22,'akama(illidan) SAY_AKAMA_LEAVE'),
(-1564123,'Who shall be next to taste my blades?!',11473,1,0,0,'illidan SAY_KILL1'),
(-1564124,'This is too easy!',11472,1,0,0,'illidan SAY_KILL2'),
(-1564125,'I will not be touched by rabble such as you!',11479,1,0,254,'illidan SAY_TAKEOFF'),
(-1564126,'Behold the flames of Azzinoth!',11480,1,0,0,'illidan SAY_SUMMONFLAMES'),
(-1564127,'Stare into the eyes of the Betrayer!',11481,1,0,0,'illidan SAY_EYE_BLAST'),
(-1564128,'Behold the power... of the demon within!',11475,1,0,0,'illidan SAY_MORPH'),
(-1564129,'You\'ve wasted too much time mortals, now you shall fall!',11474,1,0,0,'illidan SAY_ENRAGE'),

(-1564130,'Broken of the Ashtongue tribe, your leader speaks!',0,1,0,0,'akama(shade) SAY_FREE_1'),

(-1564131,'This door is all that stands between us and the Betrayer.  Stand aside, friends.',0,0,0,1,'akama(illidan) SAY_OPEN_DOOR_1'),
(-1564132,'I cannot do this alone...',0,0,0,0,'akama(illidan) SAY_OPEN_DOOR_2'),
(-1564133,'You are not alone, Akama.',0,0,0,0,'spirit_Udalo SAY_OPEN_DOOR_3'),
(-1564134,'Your people will always be with you!',0,0,0,0,'spirit_Olum SAY_OPEN_DOOR_4');

-- -1 565 000 GRUUL'S LAIR
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1565000,'Gronn are the real power in Outland!',11367,1,0,0,'maulgar SAY_AGGRO'),
(-1565001,'You will not defeat the hand of Gruul!',11368,1,0,0,'maulgar SAY_ENRAGE'),
(-1565002,'You won''t kill next one so easy.',11369,1,0,0,'maulgar SAY_OGRE_DEATH1'),
(-1565003,'Pah! Does not prove anything!',11370,1,0,0,'maulgar SAY_OGRE_DEATH2'),
(-1565004,'I\'m not afraid of you.',11371,1,0,0,'maulgar SAY_OGRE_DEATH3'),
(-1565005,'Good, now you fight me!',11372,1,0,0,'maulgar SAY_OGRE_DEATH4'),
(-1565006,'You not so tough after all!',11373,1,0,0,'maulgar SAY_SLAY1'),
(-1565007,'Aha-ha ha ha!',11374,1,0,0,'maulgar SAY_SLAY2'),
(-1565008,'Maulgar is king!',11375,1,0,0,'maulgar SAY_SLAY3'),
(-1565009,'Gruul... will crush you.',11376,1,0,0,'maulgar SAY_DEATH'),

(-1565010,'Come.... and die.',11355,1,0,0,'gruul SAY_AGGRO'),
(-1565011,'Scurry.',11356,1,0,0,'gruul SAY_SLAM1'),
(-1565012,'No escape.',11357,1,0,0,'gruul SAY_SLAM2'),
(-1565013,'Stay.',11358,1,0,0,'gruul SAY_SHATTER1'),
(-1565014,'Beg for life.',11359,1,0,0,'gruul SAY_SHATTER2'),
(-1565015,'No more.',11360,1,0,0,'gruul SAY_SLAY1'),
(-1565016,'Unworthy.',11361,1,0,0,'gruul SAY_SLAY2'),
(-1565017,'Die.',11362,1,0,0,'gruul SAY_SLAY3'),
(-1565018,'Aaargh...',11363,1,0,0,'gruul SAY_DEATH'),
(-1565019,'%s grows in size!',0,2,0,0,'gruul EMOTE_GROW'),
(-1565020,'%s roars!',0,2,0,0,'gruul EMOTE_SHATTER');

-- -1 568 000 ZUL'AMAN
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1568000,'Spirits of da wind be your doom!',12031,1,0,0,'janalai SAY_AGGRO'),
(-1568001,'I burn ya now!',12032,1,0,0,'janalai SAY_FIRE_BOMBS'),
(-1568002,'Where ma hatcha? Get to work on dem eggs!',12033,1,0,0,'janalai SAY_SUMMON_HATCHER'),
(-1568003,'I show you strength... in numbers.',12034,1,0,0,'janalai SAY_ALL_EGGS'),
(-1568004,'You done run outta time!',12035,1,0,0,'janalai SAY_BERSERK'),
(-1568005,'It all be over now, mon!',12036,1,0,0,'janalai SAY_SLAY_1'),
(-1568006,'Tazaga-choo!',12037,1,0,0,'janalai SAY_SLAY_2'),
(-1568007,'Zul\'jin... got a surprise for you...',12038,1,0,0,'janalai SAY_DEATH'),
(-1568008,'Come, strangers. The spirit of the dragonhawk hot be hungry for worthy souls.',12039,1,0,0,'janalai SAY_EVENT_STRANGERS'),
(-1568009,'Come, friends. Your bodies gonna feed ma hatchlings, and your souls are going to feed me with power!',12040,1,0,0,'janalai SAY_EVENT_FRIENDS'),

(-1568010,'Get da move on, guards! It be killin\' time!',12066,1,0,0,'nalorakk SAY_WAVE1_AGGRO'),
(-1568011,'Guards, go already! Who you more afraid of, dem... or me?',12067,1,0,0,'nalorakk SAY_WAVE2_STAIR1'),
(-1568012,'Ride now! Ride out dere and bring me back some heads!',12068,1,0,0,'nalorakk SAY_WAVE3_STAIR2'),
(-1568013,'I be losin\' me patience! Go on: make dem wish dey was never born!',12069,1,0,0,'nalorakk SAY_WAVE4_PLATFORM'),
(-1568014,'What could be better than servin\' da bear spirit for eternity? Come closer now. Bring your souls to me!',12078,1,0,0,'nalorakk SAY_EVENT1_SACRIFICE'),
(-1568015,'Don\'t be delayin\' your fate. Come to me now. I make your sacrifice quick.',12079,1,0,0,'nalorakk SAY_EVENT2_SACRIFICE'),
(-1568016,'You be dead soon enough!',12070,1,0,0,'nalorakk SAY_AGGRO'),
(-1568017,'I bring da pain!',12071,1,0,0,'nalorakk SAY_SURGE'),
(-1568018,'You call on da beast, you gonna get more dan you bargain for!',12072,1,0,0,'nalorakk SAY_TOBEAR'),
(-1568019,'Make way for Nalorakk!',12073,1,0,0,'nalorakk SAY_TOTROLL'),
(-1568020,'You had your chance, now it be too late!',12074,1,0,0,'nalorakk SAY_BERSERK'),
(-1568021,'Mua-ha-ha! Now whatchoo got to say?',12075,1,0,0,'nalorakk SAY_SLAY1'),
(-1568022,'Da Amani gonna rule again!',12076,1,0,0,'nalorakk SAY_SLAY2'),
(-1568023,'I... be waitin\' on da udda side....',12077,1,0,0,'nalorakk SAY_DEATH'),

(-1568024,'Da eagles gonna bear your spirits to me. Your sacrifice is not gonna be in vein!',12122,1,0,0,'akilzon SAY_EVENT1'),
(-1568025,'Your death gonna be quick, strangers. You shoulda never have come to this place...',12123,1,0,0,'akilzon SAY_EVENT2'),
(-1568026,'I be da predator! You da prey...',12013,1,0,0,'akilzon SAY_AGGRO'),
(-1568027,'Feed, me bruddahs!',12014,1,0,0,'akilzon SAY_SUMMON'),
(-1568028,'Come, and join me bruddahs!',12015,1,0,0,'akilzon SAY_SUMMON_ALT'),
(-1568029,'All you be doing is wasting my time!',12016,1,0,0,'akilzon SAY_ENRAGE'),
(-1568030,'Ya got nothin\'!',12017,1,0,0,'akilzon SAY_SLAY1'),
(-1568031,'Stop your cryin\'!',12018,1,0,0,'akilzon SAY_SLAY2'),
(-1568032,'You can\'t... kill... me spirit!',12019,1,0,0,'akilzon SAY_DEATH'),
(-1568033,'An Electrical Storm Appears!',0,2,0,0,'akilzon EMOTE_STORM'),

(-1568034,'Get on ya knees and bow.... to da fang and claw!',12020,1,0,0,'halazzi SAY_AGGRO'),
(-1568035,'I fight wit\' untamed spirit....',12021,1,0,0,'halazzi SAY_SPLIT'),
(-1568036,'Spirit, come back to me!',12022,1,0,0,'halazzi SAY_MERGE'),
(-1568037,'Me gonna carve ya now!',12023,1,0,0,'halazzi SAY_SABERLASH1'),
(-1568038,'You gonna leave in pieces!',12024,1,0,0,'halazzi SAY_SABERLASH2'),
(-1568039,'Whatch you be doing? Pissin\' yourselves...',12025,1,0,0,'halazzi SAY_BERSERK'),
(-1568040,'You cant fight the power!',12026,1,0,0,'halazzi SAY_KILL1'),
(-1568041,'You gonna fail!',12027,1,0,0,'halazzi SAY_KILL2'),
(-1568042,'Chaga... choka\'jinn.',12028,1,0,0,'halazzi SAY_DEATH'),
(-1568043,'Come, fools. Fill ma empty cages...',12029,1,0,0,'halazzi SAY_EVENT1'),
(-1568044,'I be waitin, strangers. Your deaths gonna make me stronger!',12030,1,0,0,'halazzi SAY_EVENT2'),

(-1568045,'Da shadow gonna fall on you...',12041,1,0,0,'malacrass SAY_AGGRO'),
(-1568046,'Ya don\'t kill me yet, ya don\'t get another chance!',12042,1,0,0,'malacrass SAY_ENRAGE'),
(-1568047,'Dis a nightmare ya don\' wake up from!',12043,1,0,0,'malacrass SAY_KILL1'),
(-1568048,'Azzaga choogo zinn!',12044,1,0,0,'malacrass SAY_KILL2'),
(-1568049,'Your will belong ta me now!',12045,1,0,0,'malacrass SAY_SOUL_SIPHON'),
(-1568050,'Darkness comin\' for you...',12046,1,0,0,'malacrass SAY_DRAIN_POWER'),
(-1568051,'Your soul gonna bleed!',12047,1,0,0,'malacrass SAY_SPIRIT_BOLTS'),
(-1568052,'It not gonna make no difference.',12048,1,0,0,'malacrass SAY_ADD_DIED1'),
(-1568053,'You gonna die worse dan him.',12049,1,0,0,'malacrass SAY_ADD_DIED2'),
(-1568054,'Dat no bodda me.',12050,1,0,0,'malacrass SAY_ADD_DIED3'),
(-1568055,'Dis not... da end of me...',12051,1,0,0,'malacrass SAY_DEATH'),

(-1568056,'Everybody always wanna take from us. Now we gonna start takin\' back. Anybody who get in our way...gonna drown in dey own blood! Da Amani empire be back now...seekin\' vengeance. And we gonna start wit\' you.',12090,1,0,0,'zuljin SAY_INTRO'),
(-1568057,'Nobody badduh dan me!',12091,1,0,0,'zuljin SAY_AGGRO'),
(-1568058,'Got me some new tricks... like me brudda bear....',12092,1,0,0,'zuljin SAY_BEAR_TRANSFORM'),
(-1568059,'Dere be no hidin\' from da eagle!',12093,1,0,0,'zuljin SAY_EAGLE_TRANSFORM'),
(-1568060,'Let me introduce you to me new bruddas: fang and claw!',12094,1,0,0,'zuljin SAY_LYNX_TRANSFORM'),
(-1568061,'Ya don\' have to look to da sky to see da dragonhawk!',12095,1,0,0,'zuljin SAY_DRAGONHAWK_TRANSFORM'),
(-1568062,'Fire kill you just as quick!',12096,1,0,0,'zuljin SAY_FIRE_BREATH'),
(-1568063,'You too slow! Me too strong!',12097,1,0,0,'zuljin SAY_BERSERK'),
(-1568064,'Da Amani de chuka!',12098,1,0,0,'zuljin SAY_KILL1'),
(-1568065,'Lot more gonna fall like you!',12099,1,0,0,'zuljin SAY_KILL2'),
(-1568066,'Mebbe me fall...but da Amani empire...never gonna die...',12100,1,0,0,'zuljin SAY_DEATH'),

(-1568067,'Zul\'jin got a surprise for ya...',12052,6,0,0,'zulaman SAY_INST_RELEASE'),
(-1568068,'Da spirits gonna feast today! Begin da ceremonies, sacrifice da prisoners... make room for our new guests!',12053,6,0,0,'zulaman SAY_INST_BEGIN'),
(-1568069,'Take your pick, trespassers! Any of ma priests be happy to accommodate ya.',12054,6,0,0,'zulaman SAY_INST_PROGRESS_1'),
(-1568070,'Don\'t be shy. Thousands have come before you. Ya not be alone in your service.',12055,6,0,0,'zulaman SAY_INST_PROGRESS_2'),
(-1568071,'Ya gonna fail, strangers. Many try before you, but dey only make us stronger!',12056,6,0,0,'zulaman SAY_INST_PROGRESS_3'),
(-1568072,'Your efforts was in vain, trespassers. The rituals nearly be complete.',12057,6,0,0,'zulaman SAY_INST_WARN_1'),
(-1568073,'Soon da cages gonna be empty, da sacrifices be complete, and you gonna take dere places.',12058,6,0,0,'zulaman SAY_INST_WARN_2'),
(-1568074,'Time be running low, strangers. Soon you gonna join da souls of dem ya failed to save.',12059,6,0,0,'zulaman SAY_INST_WARN_3'),
(-1568075,'Make haste, ma priests! Da rituals must not be interrupted!',12060,6,0,0,'zulaman SAY_INST_WARN_4'),
(-1568076,'Ya make a good try... but now you gonna join da ones who already fall.',12061,6,0,0,'zulaman SAY_INST_SACRIF1'),
(-1568077,'Ya not do too bad. Ya efforts [...] for a small time. Come to me now. Ya prove yourself worthy offerings.',12062,6,0,0,'zulaman SAY_INST_SACRIF2'),
(-1568078,'Watch now. Every offering gonna strengthen our ties to da spirit world. Soon, we gonna be unstoppable!',12065,6,0,0,'zulaman SAY_INST_COMPLETE'),

(-1568079,'Suit yourself. At least five of you must assist me if we\'re to get inside. Follow me.',0,1,0,0,'harrison SAY_START'),
(-1568080,'According to my calculations, if enough of us bang the gong at once the seal on these doors will break and we can enter.',0,1,0,0,'harrison SAY_AT_GONG'),
(-1568081,'I\'ve researched this site extensively and I won\'t allow any dim-witted treasure hunters to swoop in and steal what belongs to in a museum. I\'ll lead this charge.',0,1,0,0,'harrison SAY_OPEN_ENTRANCE'),

(-1568082,'%s absorbs the essence of the bear spirit!',0,2,0,0,'zuljin EMOTE_BEAR_SPIRIT'),
(-1568083,'%s absorbs the essence of the eagle spirit!',0,2,0,0,'zuljin EMOTE_EAGLE_SPIRIT'),
(-1568084,'%s absorbs the essence of the lynx spirit!',0,2,0,0,'zuljin EMOTE_LYNX_SPIRIT'),
(-1568085,'%s absorbs the essence of the dragonhawk spirit!',0,2,0,0,'zuljin EMOTE_DRAGONHAWK_SPIRIT');

-- -1 580 000 SUNWELL PLATEAU
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1580000,'Aggh! No longer will I be a slave to Malygos! Challenge me and you will be destroyed!',12422,1,0,0,'kalecgos SAY_EVIL_AGGRO'),
(-1580001,'I will purge you!',12423,1,0,0,'kalecgos SAY_EVIL_SPELL1'),
(-1580002,'Your pain has only begun!',12424,1,0,0,'kalecgos SAY_EVIL_SPELL2'),
(-1580003,'In the name of Kil\'jaeden!',12425,1,0,0,'kalecgos SAY_EVIL_SLAY1'),
(-1580004,'You were warned!',12426,1,0,0,'kalecgos SAY_EVIL_SLAY2'),
(-1580005,'My awakening is complete! You shall all perish!',12427,1,0,0,'kalecgos SAY_EVIL_ENRAGE'),
(-1580006,'I need... your help... Cannot... resist him... much longer...',12428,1,0,0,'kalecgos humanoid SAY_GOOD_AGGRO'),
(-1580007,'Aaahhh! Help me, before I lose my mind!',12429,1,0,0,'kalecgos humanoid SAY_GOOD_NEAR_DEATH'),
(-1580008,'Hurry! There is not much of me left!',12430,1,0,0,'kalecgos humanoid SAY_GOOD_NEAR_DEATH2'),
(-1580009,'I am forever in your debt. Once we have triumphed over Kil\'jaeden, this entire world will be in your debt as well.',12431,1,0,0,'kalecgos humanoid SAY_GOOD_PLRWIN'),
(-1580010,'There will be no reprieve. My work here is nearly finished.',12451,1,0,0,'sathrovarr SAY_SATH_AGGRO'),
(-1580011,'I\'m... never on... the losing... side...',12452,1,0,0,'sathrovarr SAY_SATH_DEATH'),
(-1580012,'Your misery is my delight!',12453,1,0,0,'sathrovarr SAY_SATH_SPELL1'),
(-1580013,'I will watch you bleed!',12454,1,0,0,'sathrovarr SAY_SATH_SPELL2'),
(-1580014,'Pitious mortal!',12455,1,0,0,'sathrovarr SAY_SATH_SLAY1'),
(-1580015,'Haven\'t you heard? I always win!',12456,1,0,0,'sathrovarr SAY_SATH_SLAY2'),
(-1580016,'I have toyed with you long enough!',12457,1,0,0,'sathrovarr SAY_SATH_ENRAGE'),

(-1580017,'Puny lizard! Death is the only answer you\'ll find here!',12458,1,0,0,'brutallus YELL_INTRO'),
(-1580018,'Grah! Your magic is weak!',12459,1,0,0,'brutallus YELL_INTRO_BREAK_ICE'),
(-1580019,'I will crush you!',12460,1,0,0,'brutallus YELL_INTRO_CHARGE'),
(-1580020,'That was fun, but I still await a true challenge!',12461,1,0,0,'brutallus YELL_INTRO_KILL_MADRIGOSA'),
(-1580021,'Come, try your luck!',12462,1,0,0,'brutallus YELL_INTRO_TAUNT'),
(-1580022,'Ahh! More lambs to the slaughter!',12463,1,0,0,'brutallus YELL_AGGRO'),
(-1580023,'Perish, insect!',12464,1,0,0,'brutallus YELL_KILL1'),
(-1580024,'You are meat!',12465,1,0,0,'brutallus YELL_KILL2'),
(-1580025,'Too easy!',12466,1,0,0,'brutallus YELL_KILL3'),
(-1580026,'Bring the fight to me!',12467,1,0,0,'brutallus YELL_LOVE1'),
(-1580027,'Another day, another glorious battle!',12468,1,0,0,'brutallus YELL_LOVE2'),
(-1580028,'I live for this!',12469,1,0,0,'brutallus YELL_LOVE3'),
(-1580029,'So much for a real challenge... Die!',12470,1,0,0,'brutallus YELL_BERSERK'),
(-1580030,'Gah! Well done... Now... this gets... interesting...',12471,1,0,0,'brutallus YELL_DEATH'),

(-1580031,'Hold, friends! There is information to be had before this devil meets his fate!',12472,1,0,0,'madrigosa YELL_MADR_ICE_BARRIER'),
(-1580032,'Where is Anveena, demon? What has become of Kalec?',12473,1,0,293,'madrigosa YELL_MADR_INTRO'),
(-1580033,'You will tell me where they are!',12474,1,0,0,'madrigosa YELL_MADR_ICE_BLOCK'),
(-1580034,'Speak, I grow weary of asking!',12475,1,0,0,'madrigosa YELL_MADR_TRAP'),
(-1580035,'Malygos, my lord! I did my best!',12476,1,0,0,'madrigosa YELL_MADR_DEATH'),

(-1580036,'Glory to Kil\'jaeden! Death to all who oppose!',12477,1,0,0,'felmyst SAY_INTRO'),
(-1580037,'I kill for the master!',12480,1,0,0,'felmyst SAY_KILL_1'),
(-1580038,'The end has come! ',12481,1,0,0,'felmyst SAY_KILL_2'),
(-1580039,'Choke on your final breath! ',12478,1,0,0,'felmyst SAY_BREATH'),
(-1580040,'I am stronger than ever before! ',12479,1,0,0,'felmyst SAY_TAKEOFF'),
(-1580041,'No more hesitation! Your fates are written! ',12482,1,0,0,'felmyst SAY_BERSERK'),
(-1580042,'Kil\'jaeden... will... prevail... ',12483,1,0,0,'felmyst SAY_DEATH'),
(-1580043,'Madrigosa deserved a far better fate. You did what had to be done, but this battle is far from over.',12439,1,0,0,'kalecgos SAY_KALECGOS_OUTRO'),

(-1580044,'Misery...',12484,1,0,0,'sacrolash SAY_INTRO_1'),
(-1580045,'Depravity...',0,1,0,0,'alythess SAY_INTRO_2'),
(-1580046,'Confusion...',0,1,0,0,'sacrolash SAY_INTRO_3'),
(-1580047,'Hatred...',0,1,0,0,'alythess SAY_INTRO_4'),
(-1580048,'Mistrust...',0,1,0,0,'sacrolash SAY_INTRO_5'),
(-1580049,'Chaos...',0,1,0,0,'alythess SAY_INTRO_6'),
(-1580050,'These are the hallmarks...',0,1,0,0,'sacrolash SAY_INTRO_7'),
(-1580051,'These are the pillars...',0,1,0,0,'alythess SAY_INTRO_8'),

(-1580052,'Shadow to the aid of fire!',12485,1,0,0,'sacrolash SAY_SACROLASH_SHADOW_NOVA'),
(-1580053,'Alythess! Your fire burns within me!',12488,1,0,0,'sacrolash SAY_SACROLASH_EMPOWER'),
(-1580054,'Shadows, engulf!',12486,1,0,0,'sacrolash SAY_SACROLASH_KILL_1'),
(-1580055,'Ee-nok Kryul!',12487,1,0,0,'sacrolash SAY_SACROLASH_KILL_2'),
(-1580056,'I... fade.',12399,1,0,0,'sacrolash SAY_SACROLASH_DEAD'),
(-1580057,'Time is a luxury you no longer possess!',0,1,0,0,'sacrolash SAY_SACROLASH_BERSERK'),
(-1580058,'Fire to the aid of shadow!',12489,1,0,0,'alythess SAY_ALYTHESS_CANFLAGRATION'),
(-1580059,'Sacrolash!',12492,1,0,0,'alythess SAY_ALYTHESS_EMPOWER'),
(-1580060,'Fire, consume!',12490,1,0,0,'alythess SAY_ALYTHESS_KILL_1'),
(-1580061,'Ed-ir Halach!',12491,1,0,0,'alythess SAY_ALYTHESS_KILL_2'),
(-1580062,'De-ek Anur!',12494,1,0,0,'alythess SAY_ALYTHESS_DEAD'),
(-1580063,'Your luck has run its course!',12493,1,0,0,'alythess SAY_ALYTHESS_BERSERK'),

(-1580064,'All my plans have led to this!',12495,6,0,0,'kiljaeden SAY_ORDER_1'),
(-1580065,'Stay on task! Do not waste time!',12496,6,0,0,'kiljaeden SAY_ORDER_2'),
(-1580066,'I have waited long enough!',12497,6,0,0,'kiljaeden SAY_ORDER_3'),
(-1580067,'Fail me and suffer for eternity!',12498,6,0,0,'kiljaeden SAY_ORDER_4'),
(-1580068,'Drain the girl! Drain her power until there is nothing but a vacant shell!',12499,6,0,0,'kiljaeden SAY_ORDER_5'),
(-1580069,'The expendible have perished... So be it! Now I shall succeed where Sargeras could not! I will bleed this wretched world and secure my place as the true master of the Burning Legion. The end has come! Let the unraveling of this world commence!',12500,1,0,0,'kiljaeden SAY_EMERGE'),
(-1580070,'Another step towards destruction!',12501,1,0,0,'kiljaeden SAY_SLAY_1'),
(-1580071,'Anukh-Kyrie!',12502,1,0,0,'kiljaeden SAY_SLAY_2'),
(-1580072,'Who can you trust?',12503,1,0,0,'kiljaeden SAY_REFLECTION_1'),
(-1580073,'The enemy is among you.',12504,1,0,0,'kiljaeden SAY_REFLECTION_2'),
(-1580074,'Chaos!',12505,1,0,0,'kiljaeden SAY_DARKNESS_1'),
(-1580075,'Destruction!',12506,1,0,0,'kiljaeden SAY_DARKNESS_2'),
(-1580076,'Oblivion!',12507,1,0,0,'kiljaeden SAY_DARKNESS_3'),
(-1580077,'I will not be denied! This world shall fall!',12508,1,0,0,'kiljaeden SAY_PHASE_3'),
(-1580078,'Do not harbor false hope. You cannot win!',12509,1,0,0,'kiljaeden SAY_PHASE_4'),
(-1580079,'Aggghh! The powers of the Sunwell... turn... against me! What have you done? What have you done???',12510,1,0,0,'kiljaeden SAY_PHASE_5'),
(-1580080,'You are not alone. The Blue Dragonflight shall help you vanquish the Deceiver.',12438,1,0,0,'kalecgos SAY_KALECGOS_INTRO'),
(-1580081,'Anveena, you must awaken, this world needs you!',12445,1,0,0,'kalecgos SAY_KALECGOS_AWAKE_1'),
(-1580082,'I serve only the Master now.',12511,0,0,0,'anveena SAY_ANVEENA_IMPRISONED'),
(-1580083,'You must let go! You must become what you were always meant to be! The time is now, Anveena!',12446,1,0,0,'kalecgos SAY_KALECGOS_AWAKE_2'),
(-1580084,'But I\'m... lost. I cannot find my way back.',12512,0,0,0,'anveena SAY_ANVEENA_LOST'),
(-1580085,'Anveena, I love you! Focus on my voice, come back for me now! Only you can cleanse the Sunwell!',12447,1,0,0,'kalecgos SAY_KALECGOS_AWAKE_4'),
(-1580086,'Kalec... Kalec?',12513,0,0,0,'anveena SAY_ANVEENA_AWAKE'),
(-1580087,'Yes, Anveena! Let fate embrace you now!',12448,1,0,0,'kalecgos SAY_KALECGOS_AWAKE_5'),
(-1580088,'The nightmare is over, the spell is broken! Goodbye, Kalec, my love!',12514,0,0,0,'anveena SAY_ANVEENA_SACRIFICE'),
(-1580089,'Goodbye, Anveena, my love. Few will remember your name, yet this day you change the course of destiny. What was once corrupt is now pure. Heroes, do not let her sacrifice be in vain.',12450,0,0,0,'kalecgos SAY_KALECGOS_GOODBYE'),
(-1580090,'Strike now, heroes, while he is weakened! Vanquish the Deceiver!',12449,1,0,0,'kalecgos SAY_KALECGOS_ENCOURAGE'),
(-1580091,'I will channel my power into the orbs, be ready!',12440,1,0,0,'kalecgos SAY_KALECGOS_ORB_1'),
(-1580092,'I have empowered another orb! Use it quickly!',12441,1,0,0,'kalecgos SAY_KALECGOS_ORB_2'),
(-1580093,'Another orb is ready! Make haste!',12442,1,0,0,'kalecgos SAY_KALECGOS_ORB_3'),
(-1580094,'I have channeled all I can! The power is in your hands!',12443,1,0,0,'kalecgos SAY_KALECGOS_ORB_4'),

(-1580095,'Mortal heroes - your victory here today was foretold long ago. My brother\'s anguished cry of defeat will echo across the universe - bringing renewed hope to all those who still stand against the Burning Crusade.',12515,0,0,1,'velen SAY_OUTRO_1'),
(-1580096,'As the Legion\'s final defeat draws ever-nearer, stand proud in the knowledge that you have saved worlds without number from the flame.',12516,0,0,1,'velen SAY_OUTRO_2'),
(-1580097,'Just as this day marks an ending, so too does it herald a new beginning...',12517,0,0,1,'velen SAY_OUTRO_3'),
(-1580098,'The creature Entropius, whom you were forced to destroy, was once the noble naaru, M\'uru. In life, M\'uru channeled vast energies of LIGHT and HOPE. For a time, a misguided few sought to steal those energies...',12518,0,0,1,'velen SAY_OUTRO_4'),
(-1580099,'Our arrogance was unpardonable. We damned one of the most noble beings of all. We may never atone for this sin.',12524,0,0,1,'liadrin SAY_OUTRO_5'),
(-1580100,'Than fortunate it is, that I have reclaimed the noble naaru\'s spark from where it fell! Where faith dwells, hope is never lost, young blood elf.',12519,0,0,1,'velen SAY_OUTRO_6'),
(-1580101,'Can it be ?',12525,0,0,1,'liadrin SAY_OUTRO_7'),
(-1580102,'Gaz now, mortals - upon the HEART OF M\'URU! Umblemished. Bathed by the light of Creation - just as it was at the Dawn.',12520,0,0,1,'velen SAY_OUTRO_8'),
(-1580103,'In time, the light and hope held within - will rebirth more than this mere fount of power... Mayhap, they will rebirth the soul of a nation.',12521,0,0,1,'velen SAY_OUTRO_9'),
(-1580104,'Blessed ancestors! I feel it... so much love... so much grace... there are... no words... impossible to describe...',12526,0,0,1,'liadrin SAY_OUTRO_10'),
(-1580105,'Salvation, young one. It waits for us all.',12522,0,0,1,'velen SAY_OUTRO_11'),
(-1580106,'Farewell...!',12523,0,0,1,'velen SAY_OUTRO_12'),

(-1580107,'%s takes a deep breath.',0,3,0,0,'felmyst EMOTE_DEEP_BREATH');

-- -1 585 000 MAGISTER'S TERRACE
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1585000,'You only waste my time!',12378,1,0,0,'selin SAY_AGGRO'),
(-1585001,'My hunger knows no bounds!',12381,1,0,0,'selin SAY_ENERGY'),
(-1585002,'Yes! I am a god!',12382,1,0,0,'selin SAY_EMPOWERED'),
(-1585003,'Enough distractions!',12388,1,0,0,'selin SAY_KILL_1'),
(-1585004,'I am invincible!',12385,1,0,0,'selin SAY_KILL_2'),
(-1585005,'No! More... I must have more!',12383,1,0,0,'selin SAY_DEATH'),
(-1585006,'%s begins to channel from the nearby Fel Crystal...',0,3,0,0,'selin EMOTE_CRYSTAL'),

(-1585007,'Drain...life!',12389,1,0,0,'vexallus SAY_AGGRO'),
(-1585008,'Un...con...tainable.',12392,1,0,0,'vexallus SAY_ENERGY'),
(-1585009,'Un...leash...',12390,1,0,0,'vexallus SAY_OVERLOAD'),
(-1585010,'Con...sume.',12393,1,0,0,'vexallus SAY_KILL'),
(-1585011,'%s discharges pure energy!',0,3,0,0,'vexallus EMOTE_DISCHARGE_ENERGY'),

(-1585012,'Annihilate them!',12395,1,0,0,'delrissa SAY_AGGRO'),
(-1585013,'Oh, the horror.',12398,1,0,0,'delrissa LackeyDeath1'),
(-1585014,'Well, aren\'t you lucky?',12400,1,0,0,'delrissa LackeyDeath2'),
(-1585015,'Now I\'m getting annoyed.',12401,1,0,0,'delrissa LackeyDeath3'),
(-1585016,'Lackies be damned! I\'ll finish you myself!',12403,1,0,0,'delrissa LackeyDeath4'),
(-1585017,'I call that a good start.',12405,1,0,0,'delrissa PlayerDeath1'),
(-1585018,'I could have sworn there were more of you.',12407,1,0,0,'delrissa PlayerDeath2'),
(-1585019,'Not really much of a group, anymore, is it?',12409,1,0,0,'delrissa PlayerDeath3'),
(-1585020,'One is such a lonely number.',12410,1,0,0,'delrissa PlayerDeath4'),
(-1585021,'It\'s been a kick, really.',12411,1,0,0,'delrissa PlayerDeath5'),
(-1585022,'Not what I had... planned...',12397,1,0,0,'delrissa SAY_DEATH'),

(-1585023,'Don\'t look so smug! I know what you\'re thinking, but Tempest Keep was merely a set back. Did you honestly believe I would trust the future to some blind, half-night elf mongrel?',12413,1,0,0,'kaelthas MT SAY_INTRO_1'),
(-1585024,'Vengeance burns!',12415,1,0,0,'kaelthas MT SAY_PHOENIX'),
(-1585025,'Felomin ashal!',12417,1,0,0,'kaelthas MT SAY_FLAMESTRIKE'),
(-1585026,'I\'ll turn your world... upside... down...',12418,1,0,0,'kaelthas MT SAY_GRAVITY_LAPSE'),
(-1585027,'Master... grant me strength.',12419,1,0,0,'kaelthas MT SAY_TIRED'),
(-1585028,'Do not... get too comfortable.',12420,1,0,0,'kaelthas MT SAY_RECAST_GRAVITY'),
(-1585029,'My demise accomplishes nothing! The Master will have you! You will drown in your own blood! This world shall burn! Aaaghh!',12421,1,0,0,'kaelthas MT SAY_DEATH'),
(-1585030,'Oh no, he was merely an instrument, a stepping stone to a much larger plan! It has all led to this, and this time, you will not interfere!',0,1,0,0,'kaelthas MT SAY_INTRO_2');

-- -1 999 900 EXAMPLE TEXT
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1999900,'Let the games begin.',8280,1,0,0,'example_creature SAY_AGGRO'),
(-1999901,'I see endless suffering. I see torment. I see rage. I see everything.',8831,1,0,0,'example_creature SAY_RANDOM_0'),
(-1999902,'Muahahahaha',8818,1,0,0,'example_creature SAY_RANDOM_1'),
(-1999903,'These mortal infedels my lord, they have invaded your sanctum and seek to steal your secrets.',8041,1,0,0,'example_creature SAY_RANDOM_2'),
(-1999904,'You are already dead.',8581,1,0,0,'example_creature SAY_RANDOM_3'),
(-1999905,'Where to go? What to do? So many choices that all end in pain, end in death.',8791,1,0,0,'example_creature SAY_RANDOM_4'),
(-1999906,'$N, I sentance you to death!',8588,1,0,0,'example_creature SAY_BESERK'),
(-1999907,'The suffering has just begun!',0,1,0,0,'example_creature SAY_PHASE'),
(-1999908,'I always thought I was a good dancer.',0,0,0,0,'example_creature SAY_DANCE'),
(-1999909,'Move out Soldier!',0,0,0,0,'example_creature SAY_SALUTE'),

(-1999910,'Help $N! I\'m under attack!',0,0,0,0,'example_escort SAY_AGGRO1'),
(-1999911,'Die scum!',0,0,0,0,'example_escort SAY_AGGRO2'),
(-1999912,'Hmm a nice day for a walk alright',0,0,0,0,'example_escort SAY_WP_1'),
(-1999913,'Wild Felboar attack!',0,0,0,0,'example_escort SAY_WP_2'),
(-1999914,'Time for me to go! See ya around $N!',0,0,0,3,'example_escort SAY_WP_3'),
(-1999915,'Bye Bye!',0,0,0,3,'example_escort SAY_WP_4'),
(-1999916,'How dare you leave me like that! I hate you! =*(',0,3,0,0,'example_escort SAY_DEATH_1'),
(-1999917,'...no...how could you let me die $N',0,0,0,0,'example_escort SAY_DEATH_2'),
(-1999918,'ugh...',0,0,0,0,'example_escort SAY_DEATH_3'),
(-1999919,'Taste death!',0,0,0,0,'example_escort SAY_SPELL'),
(-1999920,'Fireworks!',0,0,0,0,'example_escort SAY_RAND_1'),
(-1999921,'Hmm, I think I could use a buff.',0,0,0,0,'example_escort SAY_RAND_2'),

(-1999922,'Normal select, guess you\'re not interested.',0,0,0,0,'example_gossip_codebox SAY_NOT_INTERESTED'),
(-1999923,'Wrong!',0,0,0,0,'example_gossip_codebox SAY_WRONG'),
(-1999924,'You\'re right, you are allowed to see my inner secrets.',0,0,0,0,'example_gossip_codebox SAY_CORRECT'),

(-1999925,'Hi!',0,0,0,0,'example_areatrigger SAY_HI');

--
-- GOSSIP TEXTS
--

--
-- Below contains data for table `gossip_texts`
-- valid entries for table are between -3000000 and -3999999
--

TRUNCATE gossip_texts;

-- -3 000 000 RESERVED (up to 100)
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3000000,'[PH] SD2 unknown text','GOSSIP_ID_UNKNOWN_TEXT');

-- -3 000 100 GENERAL MAPS (not instance maps)
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3000105,'Ezekiel said that you might have a certain book...','dirty larry GOSSIP_ITEM_BOOK'),
(-3000106,'Let Marshal Windsor know that I am ready.','squire rowe GOSSIP_ITEM_WINDSOR'),
(-3000107,'I am ready, as are my forces. Let us end this masquerade!','reginald windsor GOSSIP_ITEM_START'),
(-3000108,'I need a moment of your time, sir.','prospector anvilward GOSSIP_ITEM_MOMENT'),
(-3000109,'I am ready, Oronok. Let us destroy Cyrukh and free the elements!','oronok torn-heart GOSSIP_ITEM_FIGHT'),
(-3000110,'Why... yes, of course. I\'ve something to show you right inside this building, Mr. Anvilward.','prospector anvilward GOSSIP_ITEM_SHOW'),
(-3000111,'I am ready, Anchorite. Let us begin the exorcism.','anchorite barada GOSSIP_ITEM_EXORCISM'),
(-3000112,'Turn the key to start the machine.','threshwackonator  GOSSIP_ITEM_TURN_KEY');

-- -3 033 000 SHADOWFANG KEEP
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3033000,'Please unlock the courtyard door.','deathstalker adamant/ sorcerer ashcrombe - GOSSIP_ITEM_DOOR');

-- -3 043 000 WAILING CAVERNS
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3043000,'Let the event begin!','Disciple of Naralex - GOSSIP_ITEM_BEGIN');

-- -3 090 000 GNOMEREGAN
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3090000,'I am ready to begin.','emi shortfuse GOSSIP_ITEM_START');

-- -3 230 000 BLACKROCK DEPTHS
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3230000,'You\'re free, Dughal! Get out of here!','dughal GOSSIP_ITEM_DUGHAL'),
(-3230001,'Get out of here, Tobias, you\'re free!','tobias GOSSIP_ITEM_TOBIAS'),
(-3230002,'Your bondage is at an end, Doom\'rel. I challenge you!','doomrel GOSSIP_ITEM_CHALLENGE'),
(-3230003,'Why don\'t you and Rocknot go find somewhere private...','nagmara GOSSIP_ITEM_NAGMARA');

-- -3 409 000 MOLTEN CORE
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3409000,'Tell me more.','majordomo_executus GOSSIP_ITEM_SUMMON_1'),
(-3409001,'What else do you have to say?','majordomo_executus GOSSIP_ITEM_SUMMON_2'),
(-3409002,'You challenged us and we have come. Where is this master you speak of?','majordomo_executus GOSSIP_ITEM_SUMMON_3');

-- -3 469 000 BLACKWING LAIR
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3469000,'I\'ve made no mistakes.','victor_nefarius GOSSIP_ITEM_NEFARIUS_1'),
(-3469001,'You have lost your mind, Nefarius. You speak in riddles.','victor_nefarius GOSSIP_ITEM_NEFARIUS_2'),
(-3469002,'Please do.','victor_nefarius GOSSIP_ITEM_NEFARIUS_3'),

(-3469003,'I cannot, Vaelastrasz! Surely something can be done to heal you!','vaelastrasz GOSSIP_ITEM_VAEL_1'),
(-3469004,'Vaelastrasz, no!!!','vaelastrasz GOSSIP_ITEM_VAEL_2');

-- -3 509 000 RUINS OF AHN'QIRAJ
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3509000,'Let\'s find out.','andorov GOSSIP_ITEM_START'),
(-3509001,'Let\'s see what you have.','andorov GOSSIP_ITEM_TRADE');

-- -3 532 000 KARAZHAN
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3532000,'Teleport me to the Guardian\'s Library','berthold GOSSIP_ITEM_TELEPORT'),
(-3532001,'I\'m not an actor.','barnes GOSSIP_ITEM_OPERA_1'),
(-3532002,'Ok, I\'ll give it a try, then.','barnes GOSSIP_ITEM_OPERA_2'),
(-3532003,'I\'ve never been more ready.','barnes GOSSIP_ITEM_OPERA_JULIANNE_WIPE'),
(-3532004,'The wolf\'s going down.','barnes GOSSIP_ITEM_OPERA_WOLF_WIPE'),
(-3532005,'Oh, grandmother, what phat lewts you have.','grandma GOSSIP_ITEM_GRANDMA_THIRD'),

(-3532006,'Control Orc Grunt','orc grunt GOSSIP_ITEM_ORC_GRUNT'),
(-3532007,'Control Orc Wolf','orc wolf GOSSIP_ITEM_ORC_WOLF'),
(-3532008,'Control Summoned Daemon','summoned deamon GOSSIP_ITEM_SUMMONED_DEAMON'),
(-3532009,'Control Orc Warlock','orc warlock GOSSIP_ITEM_ORC_WARLOCK'),
(-3532010,'Control Orc Necrolyte','orc necrolyte GOSSIP_ITEM_ORC_NECROLYTE'),
(-3532011,'Control Warchief Blackhand','warchief blackhand GOSSIP_ITEM_WARCHIEF_BLACKHAND'),
(-3532012,'Control Human Footman','human footman GOSSIP_ITEM_HUMAN_FOOTMAN'),
(-3532013,'Control Human Charger','human charger GOSSIP_ITEM_HUMAN_CHARGER'),
(-3532014,'Control Conjured Water Elemental','conjured water elemental GOSSIP_ITEM_WATER_ELEMENTAL'),
(-3532015,'Control Human Conjurer','human conjurer GOSSIP_ITEM_HUMAN_CONJURER'),
(-3532016,'Control Human Cleric','human cleric GOSSIP_ITEM_HUMAN_CLERIC'),
(-3532017,'Control King Llane','king llane GOSSIP_ITEM_KING_LLANE'),
(-3532018,'Please reset the chess board, we would like to play again.','medivh GOSSIP_ITEM_RESET_BOARD'),
(-3532019,'I''ll nail it!','barnes GOSSIP_ITEM_OPERA_OZ_WIPE'),
(-3532020,'Oh, grandmother, what big ears you have.','grandma GOSSIP_ITEM_GRANDMA_FIRST'),
(-3532021,'Oh, grandmother, what big eyes you have.','grandma GOSSIP_ITEM_GRANDMA_SECOND');

-- -3 534 000 THE BATTLE OF MT. HYJAL
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3534000,'My companions and I are with you, Lady Proudmoore.','jaina GOSSIP_ITEM_JAIN_START'),
(-3534001,'We are ready for whatever Archimonde might send our way, Lady Proudmoore.','jaina GOSSIP_ITEM_ANATHERON'),
(-3534002,'Until we meet again, Lady Proudmoore.','jaina GOSSIP_ITEM_SUCCESS'),
(-3534003,'I am with you, Thrall.','thrall GOSSIP_ITEM_THRALL_START'),
(-3534004,'We have nothing to fear.','thrall GOSSIP_ITEM_AZGALOR'),
(-3534005,'Until we meet again, Thrall.','thrall GOSSIP_ITEM_SUCCESS'),
(-3534006,'I would be grateful for any aid you can provide, Priestess.','tyrande GOSSIP_ITEM_AID');

-- -3 560 000 ESCAPE FROM DURNHOLDE (OLD HILLSBRAD)
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3560000,'We are ready to get you out of here, Thrall. Let\'s go!','thrall GOSSIP_ITEM_START'),
(-3560001,'I need a pack of Incendiary Bombs.','erozion GOSSIP_ITEM_NEED_BOMBS'),
(-3560002,'Taretha cannot see you, Thrall.','thrall GOSSIP_ITEM_SKARLOC1'),
(-3560003,'The situation is rather complicated, Thrall. It would be best for you to head into the mountains now, before more of Blackmoore\'s men show up. We\'ll make sure Taretha is safe.','thrall GOSSIP_ITEM_SKARLOC2'),
(-3560004,'We\'re ready, Thrall.','thrall GOSSIP_ITEM_TARREN_2'),
(-3560005,'Strange wizard?','taretha GOSSIP_ITEM_EPOCH1'),
(-3560006,'We\'ll get you out. Taretha. Don\'t worry. I doubt the wizard would wander too far away.','taretha GOSSIP_ITEM_EPOCH2'),
(-3560007,'Tarren Mill.','thrall GOSSIP_ITEM_TARREN_1');

-- -3 564 000 BLACK TEMPLE
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3564000,'I\'m with you, Akama.','akama(shade) GOSSIP_ITEM_START_ENCOUNTER'),
(-3564001,'I\'m ready, Akama.','akama(illidan) GOSSIP_ITEM_PREPARE'),
(-3564002,'We\'re ready to face Illidan.','akama(illidan) GOSSIP_ITEM_START_EVENT');

-- -3 568 000 ZUL'AMAN
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3568000,'Thanks for the concern, but we intend to explore Zul\'Aman.','harrison jones GOSSIP_ITEM_BEGIN');

--
-- Below just for beautiful view in table, run at own desire
--

-- ALTER TABLE script_texts ORDER BY entry desc;
-- ALTER TABLE gossip_texts ORDER BY entry desc;

--
-- Below contains all waypoints used by escortAI scripts
-- Entry is entry == creature_template.entry
--

TRUNCATE script_waypoint;
INSERT INTO script_waypoint VALUES
(349,0,1,-8769.59,-2185.73,141.975,0,0,0,''),
(349,0,2,-8776.54,-2193.78,140.96,0,0,0,''),
(349,0,3,-8783.29,-2194.82,140.462,0,0,0,''),
(349,0,4,-8792.52,-2188.8,142.078,0,0,0,''),
(349,0,5,-8807.55,-2186.1,141.504,0,0,0,''),
(349,0,6,-8818,-2184.8,139.153,0,0,0,''),
(349,0,7,-8825.81,-2188.84,138.459,0,0,0,''),
(349,0,8,-8827.52,-2199.81,139.622,0,0,0,''),
(349,0,9,-8821.14,-2212.64,143.126,0,0,0,''),
(349,0,10,-8809.18,-2230.46,143.438,0,0,0,''),
(349,0,11,-8797.04,-2240.72,146.548,0,0,0,''),
(349,0,12,-8795.24,-2251.81,146.808,0,0,0,''),
(349,0,13,-8780.16,-2258.62,148.554,0,0,0,''),
(349,0,14,-8762.65,-2259.56,151.144,0,0,0,''),
(349,0,15,-8754.36,-2253.74,152.243,0,0,0,''),
(349,0,16,-8741.87,-2251,154.486,0,0,0,''),
(349,0,17,-8733.22,-2251.01,154.36,0,0,0,''),
(349,0,18,-8717.47,-2245.04,154.686,0,0,0,''),
(349,0,19,-8712.24,-2246.83,154.709,0,0,0,''),
(349,0,20,-8693.84,-2240.41,152.91,0,0,0,''),
(349,0,21,-8681.82,-2245.33,155.518,0,0,0,''),
(349,0,22,-8669.86,-2252.77,154.854,0,0,0,''),
(349,0,23,-8670.56,-2264.69,156.978,0,0,0,''),
(349,0,24,-8676.56,-2269.2,155.411,0,0,0,''),
(349,0,25,-8673.34,-2288.65,157.054,0,0,0,''),
(349,0,26,-8677.76,-2302.56,155.917,0,16000,0,'Corp. Keeshan - Short Break Outside'),
(349,0,27,-8682.46,-2321.69,155.917,0,0,0,''),
(349,0,28,-8690.4,-2331.78,155.971,0,0,0,''),
(349,0,29,-8715.1,-2353.95,156.188,0,0,0,''),
(349,0,30,-8748.04,-2370.7,157.988,0,0,0,''),
(349,0,31,-8780.9,-2421.37,156.109,0,0,0,''),
(349,0,32,-8792.01,-2453.38,142.746,0,0,0,''),
(349,0,33,-8804.78,-2472.43,134.192,0,0,0,''),
(349,0,34,-8841.35,-2503.63,132.276,0,0,0,''),
(349,0,35,-8867.57,-2529.89,134.739,0,0,0,''),
(349,0,36,-8870.67,-2542.08,131.044,0,0,0,''),
(349,0,37,-8922.05,-2585.31,132.446,0,0,0,''),
(349,0,38,-8949.08,-2596.87,132.537,0,0,0,''),
(349,0,39,-8993.46,-2604.04,130.756,0,0,0,''),
(349,0,40,-9006.71,-2598.47,127.966,0,0,0,''),
(349,0,41,-9038.96,-2572.71,124.748,0,0,0,''),
(349,0,42,-9046.92,-2560.64,124.447,0,0,0,''),
(349,0,43,-9066.69,-2546.63,123.11,0,0,0,''),
(349,0,44,-9077.54,-2541.67,121.17,0,0,0,''),
(349,0,45,-9125.32,-2490.06,116.057,0,0,0,''),
(349,0,46,-9145.06,-2442.24,108.232,0,0,0,''),
(349,0,47,-9158.2,-2425.36,105.5,0,0,0,''),
(349,0,48,-9151.92,-2393.67,100.856,0,0,0,''),
(349,0,49,-9165.19,-2376.03,94.8215,0,0,0,''),
(349,0,50,-9187.1,-2360.52,89.9231,0,0,0,''),
(349,0,51,-9235.44,-2305.24,77.9253,0,0,0,''),
(349,0,52,-9264.73,-2292.92,70.0089,0,0,0,''),
(349,0,53,-9277.47,-2296.19,68.0896,0,2500,0,'Corp. Keeshan - quest-finish'),
(349,0,54,-9277.47,-2296.19,68.0896,0,0,0,'Corp. Keeshan - Say Goodbye'),
(467,0,0,-10508.4,1068,55.21,0,0,0,''),
(467,0,1,-10518.3,1074.84,53.96,0,0,0,''),
(467,0,2,-10534.8,1081.92,49.88,0,0,0,''),
(467,0,3,-10546.5,1084.88,50.13,0,0,0,''),
(467,0,4,-10555.3,1084.45,45.75,0,0,0,''),
(467,0,5,-10566.6,1083.53,42.1,0,0,0,''),
(467,0,6,-10575.8,1082.34,39.46,0,0,0,''),
(467,0,7,-10585.7,1081.08,37.77,0,0,0,''),
(467,0,8,-10600.1,1078.19,36.23,0,0,0,''),
(467,0,9,-10608.7,1076.08,35.88,0,0,0,''),
(467,0,10,-10621.3,1073,35.4,0,0,0,''),
(467,0,11,-10638.1,1060.18,33.61,0,0,0,''),
(467,0,12,-10655.9,1038.99,33.48,0,0,0,''),
(467,0,13,-10664.7,1030.54,32.7,0,0,0,''),
(467,0,14,-10708.7,1033.86,33.32,0,0,0,''),
(467,0,15,-10754.4,1017.93,32.79,0,0,0,''),
(467,0,16,-10802.3,1018.01,32.16,0,0,0,''),
(467,0,17,-10832.6,1009.04,32.71,0,0,0,''),
(467,0,18,-10866.6,1006.51,31.71,0,0,0,''),
(467,0,19,-10880,1005.1,32.84,0,0,0,''),
(467,0,20,-10892.5,1001.32,34.46,0,0,0,''),
(467,0,21,-10906.1,997.11,36.15,0,0,0,''),
(467,0,22,-10922.3,1002.23,35.74,0,0,0,''),
(467,0,23,-10936.3,1023.38,36.52,0,0,0,''),
(467,0,24,-10933.3,1052.61,35.85,0,0,0,''),
(467,0,25,-10940.2,1077.66,36.49,0,0,0,''),
(467,0,26,-10957.1,1099.33,36.83,0,0,0,''),
(467,0,27,-10956.5,1119.9,36.73,0,0,0,''),
(467,0,28,-10939.3,1150.75,37.42,0,0,0,''),
(467,0,29,-10915.1,1202.09,36.55,0,0,0,''),
(467,0,30,-10892.6,1257.03,33.37,0,0,0,''),
(467,0,31,-10891.9,1306.66,35.45,0,0,0,''),
(467,0,32,-10896.2,1327.86,37.77,0,0,0,''),
(467,0,33,-10906,1368.05,40.91,0,0,0,''),
(467,0,34,-10910.2,1389.33,42.62,0,0,0,''),
(467,0,35,-10915.4,1417.72,42.93,0,0,0,''),
(467,0,36,-10926.4,1421.18,43.04,0,0,0,'walk here and say'),
(467,0,37,-10952.3,1421.74,43.4,0,0,0,''),
(467,0,38,-10980,1411.38,42.79,0,0,0,''),
(467,0,39,-11006.1,1420.47,43.26,0,0,0,''),
(467,0,40,-11022,1450.59,43.09,0,0,0,''),
(467,0,41,-11025.4,1491.59,43.15,0,0,0,''),
(467,0,42,-11036.1,1508.32,43.28,0,0,0,''),
(467,0,43,-11060.7,1526.72,43.19,0,0,0,''),
(467,0,44,-11072.8,1527.77,43.2,0,5000,0,'say and quest credit'),
(1379,0,1,-5751.12,-3441.01,301.743,0,0,0,''),
(1379,0,2,-5738.58,-3485.14,302.41,0,0,0,''),
(1379,0,3,-5721.62,-3507.85,304.011,0,0,0,''),
(1379,0,4,-5710.21,-3527.97,304.708,0,0,0,''),
(1379,0,5,-5706.92,-3542.89,304.871,0,0,0,''),
(1379,0,6,-5701.53,-3551.24,305.962,0,0,0,''),
(1379,0,7,-5699.53,-3555.69,306.505,0,0,0,''),
(1379,0,8,-5690.56,-3571.98,309.035,0,0,0,''),
(1379,0,9,-5678.61,-3587.17,310.607,0,0,0,''),
(1379,0,10,-5677.05,-3594.35,311.527,0,0,0,''),
(1379,0,11,-5674.39,-3605.19,312.239,0,0,0,''),
(1379,0,12,-5674.45,-3614.39,312.337,0,0,0,''),
(1379,0,13,-5673.05,-3630.56,311.105,0,0,0,''),
(1379,0,14,-5680.34,-3645.44,315.185,0,0,0,''),
(1379,0,15,-5684.46,-3650.05,314.687,0,0,0,''),
(1379,0,16,-5693.9,-3674.14,313.03,0,0,0,''),
(1379,0,17,-5701.43,-3712.54,313.959,0,0,0,''),
(1379,0,18,-5698.79,-3720.88,316.943,0,0,0,''),
(1379,0,19,-5699.95,-3733.63,318.597,0,0,0,'Protecting the Shipment - Ambush'),
(1379,0,20,-5698.61,-3754.74,322.047,0,0,0,''),
(1379,0,21,-5688.68,-3769,323.957,0,0,0,''),
(1379,0,22,-5688.14,-3782.65,322.667,0,0,0,''),
(1379,0,23,-5699.23,-3792.65,322.448,0,30000,0,'Protecting the Shipment - End'),
(1379,0,24,-5700.8,-3792.78,322.588,0,0,0,''),
(1840,0,0,2689.68,-1937.47,72.14,0,0,0,''),
(1840,0,1,2683.11,-1926.82,72.14,0,0,0,''),
(1840,0,2,2678.73,-1919.42,68.86,0,0,0,'escort paused'),
(1842,0,0,2941.75,-1391.82,167.237,0,0,0,'SAY_ESCORT_START'),
(1842,0,1,2940.56,-1393.64,165.943,0,0,0,''),
(1842,0,2,2932.19,-1410.66,165.943,0,0,0,''),
(1842,0,3,2921.81,-1405.09,165.943,0,0,0,''),
(1842,0,4,2916.48,-1402.58,165.943,0,0,0,''),
(1842,0,5,2918.52,-1398.12,165.943,0,0,0,''),
(1842,0,6,2922.8,-1389.49,160.842,0,0,0,''),
(1842,0,7,2924.93,-1385.65,160.842,0,0,0,''),
(1842,0,8,2930.93,-1388.65,160.842,0,0,0,''),
(1842,0,9,2946.7,-1396.65,160.842,0,0,0,''),
(1842,0,10,2948.72,-1392.79,160.842,0,0,0,''),
(1842,0,11,2951.98,-1386.62,155.948,0,0,0,''),
(1842,0,12,2953.84,-1383.33,155.948,0,0,0,''),
(1842,0,13,2951.19,-1381.74,155.948,0,0,0,''),
(1842,0,14,2946.68,-1379.29,152.02,0,0,0,''),
(1842,0,15,2942.79,-1377.66,152.02,0,0,0,''),
(1842,0,16,2935.49,-1392.52,152.02,0,0,0,''),
(1842,0,17,2921.17,-1384.8,152.02,0,0,0,''),
(1842,0,18,2915.33,-1395.35,152.02,0,0,0,''),
(1842,0,19,2926.25,-1401.26,152.028,0,0,0,''),
(1842,0,20,2930.32,-1403.48,150.521,0,0,0,''),
(1842,0,21,2933.94,-1405.36,150.521,0,0,0,''),
(1842,0,22,2929.22,-1415.79,150.504,0,0,0,''),
(1842,0,23,2921.17,-1431.68,150.781,0,0,0,''),
(1842,0,24,2917.47,-1438.78,150.781,0,0,0,''),
(1842,0,25,2913.05,-1453.52,148.098,0,0,0,'SAY_TAELAN_MOUNT'),
(1842,0,26,2913.83,-1474.93,146.224,0,0,0,''),
(1842,0,27,2906.81,-1487.06,146.224,0,0,0,''),
(1842,0,28,2900.64,-1496.57,146.306,0,0,0,''),
(1842,0,29,2885.25,-1501.58,146.02,0,0,0,''),
(1842,0,30,2863.88,-1500.38,146.681,0,0,0,''),
(1842,0,31,2846.51,-1487.18,146.332,0,0,0,''),
(1842,0,32,2823.75,-1490.99,145.782,0,0,0,''),
(1842,0,33,2800.98,-1510.91,145.049,0,0,0,''),
(1842,0,34,2789.49,-1525.21,143.729,0,0,0,''),
(1842,0,35,2776.96,-1542.31,139.435,0,0,0,''),
(1842,0,36,2762.03,-1561.8,133.763,0,0,0,''),
(1842,0,37,2758.74,-1569.6,131.514,0,0,0,''),
(1842,0,38,2765.49,-1588.79,129.721,0,0,0,''),
(1842,0,39,2779.61,-1613.12,129.132,0,0,0,''),
(1842,0,40,2757.65,-1638.03,128.236,0,0,0,''),
(1842,0,41,2741.31,-1659.79,126.457,0,0,0,''),
(1842,0,42,2729.8,-1677.57,126.499,0,0,0,''),
(1842,0,43,2716.78,-1694.65,126.301,0,0,0,''),
(1842,0,44,2706.66,-1709.47,123.42,0,0,0,''),
(1842,0,45,2699.51,-1720.57,120.265,0,0,0,''),
(1842,0,46,2691.98,-1738.47,114.994,0,0,0,''),
(1842,0,47,2690.51,-1757.05,108.764,0,0,0,''),
(1842,0,48,2691.95,-1780.31,99.89,0,0,0,''),
(1842,0,49,2689.34,-1803.26,89.13,0,0,0,''),
(1842,0,50,2697.85,-1820.55,80.681,0,0,0,''),
(1842,0,51,2701.93,-1836.71,73.7,0,0,0,''),
(1842,0,52,2698.09,-1853.87,68.999,0,0,0,''),
(1842,0,53,2693.66,-1870.24,66.882,0,0,0,''),
(1842,0,54,2682.35,-1885.25,66.009,0,0,0,''),
(1842,0,55,2668.23,-1900.8,66.256,0,0,0,'SAY_REACH_TOWER - escort paused'),
(1978,0,0,1406.32,1083.1,52.55,0,0,0,''),
(1978,0,1,1400.49,1080.42,52.5,0,0,0,'SAY_START_2'),
(1978,0,2,1388.48,1083.1,52.52,0,0,0,''),
(1978,0,3,1370.16,1084.02,52.3,0,0,0,''),
(1978,0,4,1359.02,1080.85,52.46,0,0,0,''),
(1978,0,5,1341.43,1087.39,52.69,0,0,0,''),
(1978,0,6,1321.93,1090.51,50.66,0,0,0,''),
(1978,0,7,1312.98,1095.91,47.49,0,0,0,''),
(1978,0,8,1301.09,1102.94,47.76,0,0,0,''),
(1978,0,9,1297.73,1106.35,50.18,0,0,0,''),
(1978,0,10,1295.49,1124.32,50.49,0,0,0,''),
(1978,0,11,1294.84,1137.25,51.75,0,0,0,''),
(1978,0,12,1292.89,1158.99,52.65,0,0,0,''),
(1978,0,13,1290.75,1168.67,52.56,0,2000,0,'quest complete SAY_END'),
(1978,0,14,1287.12,1203.49,52.66,0,5000,0,'SAY_RANE'),
(1978,0,15,1288.3,1203.89,52.68,0,5000,0,'SAY_RANE_REPLY'),
(1978,0,16,1288.3,1203.89,52.68,0,5000,0,'SAY_CHECK_NEXT'),
(1978,0,17,1290.72,1207.44,52.69,0,0,0,''),
(1978,0,18,1297.5,1207.18,53.74,0,0,0,''),
(1978,0,19,1301.32,1220.9,53.74,0,0,0,''),
(1978,0,20,1298.55,1220.43,53.74,0,0,0,''),
(1978,0,21,1297.38,1212.87,58.51,0,0,0,''),
(1978,0,22,1297.8,1210.04,58.51,0,0,0,''),
(1978,0,23,1305.01,1206.1,58.51,0,0,0,''),
(1978,0,24,1310.51,1207.36,58.51,0,5000,0,'SAY_QUINN'),
(1978,0,25,1312.59,1207.21,58.51,0,5000,0,'SAY_QUINN_REPLY'),
(1978,0,26,1312.59,1207.21,58.51,0,30000,0,'SAY_BYE'),
(2713,0,0,-1416.91,-3044.12,36.21,0,0,0,''),
(2713,0,1,-1408.43,-3051.35,37.79,0,0,0,''),
(2713,0,2,-1399.45,-3069.2,31.25,0,0,0,''),
(2713,0,3,-1400.28,-3083.14,27.06,0,0,0,''),
(2713,0,4,-1405.3,-3096.72,26.36,0,0,0,''),
(2713,0,5,-1406.12,-3105.95,24.82,0,0,0,''),
(2713,0,6,-1417.41,-3106.8,16.61,0,0,0,''),
(2713,0,7,-1433.06,-3101.55,12.56,0,0,0,''),
(2713,0,8,-1439.86,-3086.36,12.29,0,0,0,''),
(2713,0,9,-1450.48,-3065.16,12.58,0,5000,0,'SAY_REACH_BOTTOM'),
(2713,0,10,-1456.15,-3055.53,12.54,0,0,0,''),
(2713,0,11,-1459.41,-3035.16,12.11,0,0,0,''),
(2713,0,12,-1472.47,-3034.18,12.44,0,0,0,''),
(2713,0,13,-1495.57,-3034.48,12.55,0,0,0,''),
(2713,0,14,-1524.91,-3035.47,13.15,0,0,0,''),
(2713,0,15,-1549.05,-3037.77,12.98,0,0,0,''),
(2713,0,16,-1555.69,-3028.02,13.64,0,3000,0,'SAY_WATCH_BACK'),
(2713,0,17,-1555.69,-3028.02,13.64,0,5000,0,'SAY_DATA_FOUND'),
(2713,0,18,-1555.69,-3028.02,13.64,0,2000,0,'SAY_ESCAPE'),
(2713,0,19,-1551.19,-3037.78,12.96,0,0,0,''),
(2713,0,20,-1584.6,-3048.77,13.67,0,0,0,''),
(2713,0,21,-1602.14,-3042.82,15.12,0,0,0,''),
(2713,0,22,-1610.68,-3027.42,17.22,0,0,0,''),
(2713,0,23,-1601.65,-3007.97,24.65,0,0,0,''),
(2713,0,24,-1581.05,-2992.32,30.85,0,0,0,''),
(2713,0,25,-1559.95,-2979.51,34.3,0,0,0,''),
(2713,0,26,-1536.51,-2969.78,32.64,0,0,0,''),
(2713,0,27,-1511.81,-2961.09,29.12,0,0,0,''),
(2713,0,28,-1484.83,-2960.87,32.54,0,0,0,''),
(2713,0,29,-1458.23,-2966.8,40.52,0,0,0,''),
(2713,0,30,-1440.2,-2971.2,43.15,0,0,0,''),
(2713,0,31,-1427.85,-2989.15,38.09,0,0,0,''),
(2713,0,32,-1420.27,-3008.91,35.01,0,0,0,''),
(2713,0,33,-1427.58,-3032.53,32.31,0,5000,0,'SAY_FINISH'),
(2713,0,34,-1427.4,-3035.17,32.26,0,0,0,''),
(2768,0,0,-2077.73,-2091.17,9.49,0,0,0,''),
(2768,0,1,-2077.99,-2105.33,13.24,0,0,0,''),
(2768,0,2,-2074.6,-2109.67,14.24,0,0,0,''),
(2768,0,3,-2076.6,-2117.46,16.67,0,0,0,''),
(2768,0,4,-2073.51,-2123.46,18.42,0,2000,0,''),
(2768,0,5,-2073.51,-2123.46,18.42,0,4000,0,''),
(2768,0,6,-2066.6,-2131.85,21.56,0,0,0,''),
(2768,0,7,-2053.85,-2143.19,20.31,0,0,0,''),
(2768,0,8,-2043.49,-2153.73,20.2,0,10000,0,''),
(2768,0,9,-2043.49,-2153.73,20.2,0,20000,0,''),
(2768,0,10,-2043.49,-2153.73,20.2,0,10000,0,''),
(2768,0,11,-2043.49,-2153.73,20.2,0,2000,0,''),
(2768,0,12,-2053.85,-2143.19,20.31,0,0,0,''),
(2768,0,13,-2066.6,-2131.85,21.56,0,0,0,''),
(2768,0,14,-2073.51,-2123.46,18.42,0,0,0,''),
(2768,0,15,-2076.6,-2117.46,16.67,0,0,0,''),
(2768,0,16,-2074.6,-2109.67,14.24,0,0,0,''),
(2768,0,17,-2077.99,-2105.33,13.24,0,0,0,''),
(2768,0,18,-2077.73,-2091.17,9.49,0,0,0,''),
(2768,0,19,-2066.41,-2086.21,8.97,0,6000,0,''),
(2768,0,20,-2066.41,-2086.21,8.97,0,2000,0,''),
(2917,0,0,4675.81,598.615,17.6457,0,0,0,'SAY_REM_START'),
(2917,0,1,4672.84,599.325,16.4176,0,0,0,''),
(2917,0,2,4663.45,607.43,10.4948,0,0,0,''),
(2917,0,3,4655.97,613.761,8.52327,0,0,0,''),
(2917,0,4,4640.8,623.999,8.37705,0,0,0,''),
(2917,0,5,4631.68,630.801,6.415,0,5000,0,'SAY_REM_RAMP1_1'),
(2917,0,6,4633.53,632.476,6.50983,0,0,0,'ambush'),
(2917,0,7,4639.41,637.121,13.3381,0,0,0,''),
(2917,0,8,4642.35,637.668,13.4374,0,0,0,''),
(2917,0,9,4645.08,634.464,13.4372,0,5000,0,'SAY_REM_RAMP1_2'),
(2917,0,10,4642.35,637.585,13.4352,0,0,0,''),
(2917,0,11,4639.63,637.234,13.3398,0,0,0,''),
(2917,0,12,4633.36,632.462,6.48844,0,0,0,''),
(2917,0,13,4624.71,631.724,6.26403,0,0,0,''),
(2917,0,14,4623.53,629.719,6.20134,0,5000,0,'SAY_REM_BOOK'),
(2917,0,15,4623.45,630.37,6.21894,0,0,0,'SAY_REM_TENT1_1'),
(2917,0,16,4622.62,637.222,6.31285,0,0,0,'ambush'),
(2917,0,17,4619.76,637.386,6.31205,0,5000,0,'SAY_REM_TENT1_2'),
(2917,0,18,4620.03,637.368,6.31205,0,0,0,''),
(2917,0,19,4624.15,637.56,6.3139,0,0,0,''),
(2917,0,20,4622.97,634.016,6.29498,0,0,0,''),
(2917,0,21,4616.93,630.303,6.23919,0,0,0,''),
(2917,0,22,4614.55,616.983,5.68764,0,0,0,''),
(2917,0,23,4610.28,610.029,5.44254,0,0,0,''),
(2917,0,24,4601.15,604.112,2.05486,0,0,0,''),
(2917,0,25,4589.62,597.686,1.05715,0,0,0,''),
(2917,0,26,4577.59,592.146,1.12019,0,0,0,'SAY_REM_MOSS (?)'),
(2917,0,27,4569.85,592.177,1.26087,0,5000,0,'EMOTE_REM_MOSS (?)'),
(2917,0,28,4568.79,590.871,1.21134,0,3000,0,'SAY_REM_MOSS_PROGRESS (?)'),
(2917,0,29,4566.72,564.078,1.34308,0,0,0,'ambush'),
(2917,0,30,4568.27,551.958,5.0042,0,0,0,''),
(2917,0,31,4566.73,551.558,5.42631,0,5000,0,'SAY_REM_PROGRESS'),
(2917,0,32,4566.74,560.768,1.70326,0,0,0,''),
(2917,0,33,4573.92,582.566,0.749801,0,0,0,''),
(2917,0,34,4594.21,598.533,1.03406,0,0,0,''),
(2917,0,35,4601.19,604.283,2.06015,0,0,0,''),
(2917,0,36,4609.54,610.845,5.40222,0,0,0,''),
(2917,0,37,4624.8,618.076,5.85154,0,0,0,''),
(2917,0,38,4632.41,623.778,7.28624,0,0,0,''),
(2917,0,39,4645.92,621.984,8.57997,0,0,0,''),
(2917,0,40,4658.67,611.093,8.89175,0,0,0,''),
(2917,0,41,4671.92,599.752,16.0124,0,5000,0,'SAY_REM_REMEMBER'),
(2917,0,42,4676.98,600.65,17.8257,0,5000,0,'EMOTE_REM_END'),
(3439,0,0,1105.09,-3101.25,82.706,0,1000,0,'SAY_STARTUP1'),
(3439,0,1,1103.2,-3104.35,83.113,0,1000,0,''),
(3439,0,2,1107.82,-3106.5,82.739,0,1000,0,''),
(3439,0,3,1104.73,-3100.83,82.747,0,1000,0,''),
(3439,0,4,1103.24,-3106.27,83.133,0,1000,0,''),
(3439,0,5,1112.81,-3106.29,82.32,0,1000,0,''),
(3439,0,6,1112.83,-3108.91,82.377,0,1000,0,''),
(3439,0,7,1108.05,-3115.16,82.894,0,0,0,''),
(3439,0,8,1108.36,-3104.37,82.377,0,5000,0,''),
(3439,0,9,1100.31,-3097.54,83.15,0,0,0,'SAY_STARTUP2'),
(3439,0,10,1100.56,-3082.72,82.768,0,0,0,''),
(3439,0,11,1097.51,-3069.23,82.206,0,0,0,''),
(3439,0,12,1092.96,-3053.11,82.351,0,0,0,''),
(3439,0,13,1094.01,-3036.96,82.888,0,0,0,''),
(3439,0,14,1095.62,-3025.76,83.392,0,0,0,''),
(3439,0,15,1107.66,-3013.53,85.653,0,0,0,''),
(3439,0,16,1119.65,-3006.93,87.019,0,0,0,''),
(3439,0,17,1129.99,-3002.41,91.232,0,7000,0,'SAY_MERCENARY'),
(3439,0,18,1133.33,-2997.71,91.675,0,1000,0,'SAY_PROGRESS_1'),
(3439,0,19,1131.8,-2987.95,91.976,0,1000,0,''),
(3439,0,20,1122.03,-2993.4,91.536,0,0,0,''),
(3439,0,21,1116.61,-2981.92,92.103,0,0,0,''),
(3439,0,22,1102.24,-2994.25,92.074,0,0,0,''),
(3439,0,23,1096.37,-2978.31,91.873,0,0,0,''),
(3439,0,24,1091.97,-2985.92,91.73,0,40000,0,'SAY_PROGRESS_2'),
(3465,0,0,-2095.84,-3650,61.716,0,0,0,''),
(3465,0,1,-2100.19,-3613.95,61.604,0,0,0,''),
(3465,0,2,-2098.55,-3601.56,59.154,0,0,0,''),
(3465,0,3,-2093.8,-3595.23,56.658,0,0,0,''),
(3465,0,4,-2072.58,-3578.83,48.844,0,0,0,''),
(3465,0,5,-2023.86,-3568.15,24.636,0,0,0,''),
(3465,0,6,-2013.58,-3571.5,22.203,0,0,0,''),
(3465,0,7,-2009.81,-3580.55,21.791,0,0,0,''),
(3465,0,8,-2015.3,-3597.39,21.76,0,0,0,''),
(3465,0,9,-2020.68,-3610.3,21.759,0,0,0,''),
(3465,0,10,-2019.99,-3640.16,21.759,0,0,0,''),
(3465,0,11,-2016.11,-3664.13,21.758,0,0,0,''),
(3465,0,12,-1999.4,-3679.44,21.316,0,0,0,''),
(3465,0,13,-1987.46,-3688.31,18.495,0,0,0,''),
(3465,0,14,-1973.97,-3687.67,14.996,0,0,0,''),
(3465,0,15,-1949.16,-3678.05,11.293,0,0,0,''),
(3465,0,16,-1934.09,-3682.86,9.897,0,30000,0,'SAY_GIL_AT_LAST'),
(3465,0,17,-1935.38,-3682.32,10.029,0,1500,0,'SAY_GIL_PROCEED'),
(3465,0,18,-1879.04,-3699.5,6.582,0,7500,0,'SAY_GIL_FREEBOOTERS'),
(3465,0,19,-1852.73,-3703.78,6.875,0,0,0,''),
(3465,0,20,-1812.99,-3718.5,10.572,0,0,0,''),
(3465,0,21,-1788.17,-3722.87,9.663,0,0,0,''),
(3465,0,22,-1767.21,-3739.92,10.082,0,0,0,''),
(3465,0,23,-1750.19,-3747.39,10.39,0,0,0,''),
(3465,0,24,-1729.34,-3776.67,11.779,0,0,0,''),
(3465,0,25,-1716,-3802.4,12.618,0,0,0,''),
(3465,0,26,-1690.71,-3829.26,13.905,0,0,0,''),
(3465,0,27,-1674.7,-3842.4,13.872,0,0,0,''),
(3465,0,28,-1632.73,-3846.11,14.401,0,0,0,''),
(3465,0,29,-1592.73,-3842.23,14.981,0,0,0,''),
(3465,0,30,-1561.61,-3839.32,19.118,0,0,0,''),
(3465,0,31,-1544.57,-3834.39,18.761,0,0,0,''),
(3465,0,32,-1512.51,-3831.72,22.914,0,0,0,''),
(3465,0,33,-1486.89,-3836.64,23.964,0,0,0,''),
(3465,0,34,-1434.19,-3852.7,18.843,0,0,0,''),
(3465,0,35,-1405.79,-3854.49,17.276,0,0,0,''),
(3465,0,36,-1366.59,-3852.38,19.273,0,0,0,''),
(3465,0,37,-1337.36,-3837.83,17.352,0,2000,0,'SAY_GIL_ALMOST'),
(3465,0,38,-1299.74,-3810.69,20.801,0,0,0,''),
(3465,0,39,-1277.14,-3782.79,25.918,0,0,0,''),
(3465,0,40,-1263.69,-3781.25,26.447,0,0,0,''),
(3465,0,41,-1243.67,-3786.33,25.281,0,0,0,''),
(3465,0,42,-1221.88,-3784.12,24.051,0,0,0,''),
(3465,0,43,-1204.01,-3775.94,24.437,0,0,0,''),
(3465,0,44,-1181.71,-3768.93,23.368,0,0,0,''),
(3465,0,45,-1156.91,-3751.56,21.074,0,0,0,''),
(3465,0,46,-1138.83,-3741.81,17.843,0,0,0,''),
(3465,0,47,-1080.1,-3738.78,19.805,0,0,0,'SAY_GIL_SWEET'),
(3465,0,48,-1069.07,-3735.01,19.302,0,0,0,''),
(3465,0,49,-1061.94,-3724.06,21.086,0,0,0,''),
(3465,0,50,-1053.59,-3697.61,27.32,0,0,0,''),
(3465,0,51,-1044.11,-3690.13,24.856,0,0,0,''),
(3465,0,52,-1040.26,-3690.74,25.342,0,0,0,''),
(3465,0,53,-1028.15,-3688.72,23.843,0,7500,0,'SAY_GIL_FREED'),
(3584,0,0,4520.4,420.235,33.5284,0,2000,0,''),
(3584,0,1,4512.26,408.881,32.9308,0,0,0,''),
(3584,0,2,4507.94,396.47,32.9476,0,0,0,''),
(3584,0,3,4507.53,383.781,32.995,0,0,0,''),
(3584,0,4,4512.1,374.02,33.166,0,0,0,''),
(3584,0,5,4519.75,373.241,33.1574,0,0,0,''),
(3584,0,6,4592.41,369.127,31.4893,0,0,0,''),
(3584,0,7,4598.55,364.801,31.4947,0,0,0,''),
(3584,0,8,4602.76,357.649,32.9265,0,0,0,''),
(3584,0,9,4597.88,352.629,34.0317,0,0,0,''),
(3584,0,10,4590.23,350.9,36.2977,0,0,0,''),
(3584,0,11,4581.5,348.254,38.3878,0,0,0,''),
(3584,0,12,4572.05,348.059,42.3539,0,0,0,''),
(3584,0,13,4564.75,344.041,44.2463,0,0,0,''),
(3584,0,14,4556.63,341.003,47.6755,0,0,0,''),
(3584,0,15,4554.38,334.968,48.8003,0,0,0,''),
(3584,0,16,4557.63,329.783,49.9532,0,0,0,''),
(3584,0,17,4563.32,316.829,53.2409,0,0,0,''),
(3584,0,18,4566.09,303.127,55.0396,0,0,0,''),
(3584,0,19,4561.65,295.456,57.0984,0,4000,0,'SAY_THERYLUNE_FINISH'),
(3584,0,20,4551.03,293.333,57.1534,0,2000,0,''),
(3678,0,0,-134.925,125.468,-78.16,0,0,0,''),
(3678,0,1,-125.684,132.937,-78.42,0,0,0,''),
(3678,0,2,-113.812,139.295,-80.98,0,0,0,''),
(3678,0,3,-109.854,157.538,-80.2,0,0,0,''),
(3678,0,4,-108.64,175.207,-79.74,0,0,0,''),
(3678,0,5,-108.668,195.457,-80.64,0,0,0,''),
(3678,0,6,-111.007,219.007,-86.58,0,0,0,''),
(3678,0,7,-102.408,232.821,-91.52,0,0,0,'first corner SAY_FIRST_CORNER'),
(3678,0,8,-92.434,227.742,-90.75,0,0,0,''),
(3678,0,9,-82.456,224.853,-93.57,0,0,0,''),
(3678,0,10,-67.789,208.073,-93.34,0,0,0,''),
(3678,0,11,-43.343,205.295,-96.37,0,0,0,''),
(3678,0,12,-34.676,221.394,-95.82,0,0,0,''),
(3678,0,13,-32.582,238.573,-93.51,0,0,0,''),
(3678,0,14,-42.149,258.672,-92.88,0,0,0,''),
(3678,0,15,-55.257,274.696,-92.83,0,0,0,'circle of flames SAY_CIRCLE_BANISH'),
(3678,0,16,-48.604,287.584,-92.46,0,0,0,''),
(3678,0,17,-47.236,296.093,-90.88,0,0,0,''),
(3678,0,18,-35.618,309.067,-89.73,0,0,0,''),
(3678,0,19,-23.573,311.376,-88.6,0,0,0,''),
(3678,0,20,-8.692,302.389,-87.43,0,0,0,''),
(3678,0,21,-1.237,293.268,-85.55,0,0,0,''),
(3678,0,22,10.398,279.294,-85.86,0,0,0,''),
(3678,0,23,23.108,264.693,-86.69,0,0,0,''),
(3678,0,24,31.996,251.436,-87.62,0,0,0,''),
(3678,0,25,43.374,233.073,-87.61,0,0,0,''),
(3678,0,26,54.438,212.048,-89.5,0,3000,0,'chamber entrance SAY_NARALEX_CHAMBER'),
(3678,0,27,78.794,208.895,-92.84,0,0,0,''),
(3678,0,28,88.392,225.231,-94.46,0,0,0,''),
(3678,0,29,98.758,233.938,-95.84,0,0,0,''),
(3678,0,30,107.248,233.054,-95.98,0,0,0,''),
(3678,0,31,112.825,233.907,-96.39,0,0,0,''),
(3678,0,32,114.634,236.969,-96.04,0,1000,0,'naralex SAY_BEGIN_RITUAL'),
(3678,0,33,127.385,252.279,-90.07,0,0,0,''),
(3678,0,34,121.595,264.488,-91.55,0,0,0,''),
(3678,0,35,115.472,264.253,-91.5,0,0,0,''),
(3678,0,36,99.988,252.79,-91.51,0,0,0,''),
(3678,0,37,96.347,245.038,-90.34,0,0,0,''),
(3678,0,38,82.201,216.273,-86.1,0,0,0,''),
(3678,0,39,75.112,206.494,-84.8,0,0,0,''),
(3678,0,40,27.174,201.064,-72.31,0,0,0,''),
(3678,0,41,-41.114,204.149,-78.94,0,0,0,''),
(3692,0,1,4608.43,-6.32,69.74,0,1000,0,'stand up'),
(3692,0,2,4608.43,-6.32,69.74,0,4000,0,'SAY_START'),
(3692,0,3,4604.54,-5.17,69.51,0,0,0,''),
(3692,0,4,4604.26,-2.02,69.42,0,0,0,''),
(3692,0,5,4607.75,3.79,70.13,0,1000,0,'first ambush'),
(3692,0,6,4607.75,3.79,70.13,0,0,0,'SAY_FIRST_AMBUSH'),
(3692,0,7,4619.77,27.47,70.4,0,0,0,''),
(3692,0,8,4626.28,42.46,68.75,0,0,0,''),
(3692,0,9,4633.13,51.17,67.4,0,0,0,''),
(3692,0,10,4639.67,79.03,61.74,0,0,0,''),
(3692,0,11,4647.54,94.25,59.92,0,0,0,'second ambush'),
(3692,0,12,4682.08,113.47,54.83,0,0,0,''),
(3692,0,13,4705.28,137.81,53.36,0,0,0,'last ambush'),
(3692,0,14,4730.3,158.76,52.33,0,0,0,''),
(3692,0,15,4756.47,195.65,53.61,0,10000,0,'SAY_END'),
(3692,0,16,4608.43,-6.32,69.74,0,1000,0,'bow'),
(3692,0,17,4608.43,-6.32,69.74,0,4000,0,'SAY_ESCAPE'),
(3692,0,18,4608.43,-6.32,69.74,0,4000,0,'SPELL_MOONSTALKER_FORM'),
(3692,0,19,4604.54,-5.17,69.51,0,0,0,''),
(3692,0,20,4604.26,-2.02,69.42,0,0,0,''),
(3692,0,21,4607.75,3.79,70.13,0,0,0,''),
(3692,0,22,4607.75,3.79,70.13,0,0,0,''),
(3692,0,23,4619.77,27.47,70.4,0,0,0,''),
(3692,0,24,4640.33,33.74,68.22,0,0,0,'quest complete'),
(3849,0,0,-250.923,2116.26,81.179,0,0,0,'SAY_FREE_AD'),
(3849,0,1,-255.049,2119.39,81.179,0,0,0,''),
(3849,0,2,-254.129,2123.45,81.179,0,0,0,''),
(3849,0,3,-253.898,2130.87,81.179,0,0,0,''),
(3849,0,4,-249.889,2142.31,86.972,0,0,0,''),
(3849,0,5,-248.205,2144.02,87.013,0,0,0,''),
(3849,0,6,-240.553,2140.55,87.012,0,0,0,''),
(3849,0,7,-237.514,2142.07,87.012,0,0,0,''),
(3849,0,8,-235.638,2149.23,90.587,0,0,0,''),
(3849,0,9,-237.188,2151.95,90.624,0,0,0,''),
(3849,0,10,-241.162,2153.65,90.624,0,0,0,'SAY_OPEN_DOOR_AD'),
(3849,0,11,-241.13,2154.56,90.624,0,2000,0,'SAY_UNLOCK_DOOR_AD'),
(3849,0,12,-241.13,2154.56,90.624,0,3000,0,''),
(3849,0,13,-241.13,2154.56,90.624,0,5000,0,'SAY_POST1_DOOR_AD'),
(3849,0,14,-241.13,2154.56,90.624,0,0,0,'SAY_POST2_DOOR_AD'),
(3849,0,15,-208.764,2141.6,90.6257,0,0,0,''),
(3849,0,16,-206.441,2143.51,90.4287,0,0,0,''),
(3849,0,17,-203.715,2145.85,88.7052,0,0,0,''),
(3849,0,18,-199.199,2144.88,86.501,0,0,0,''),
(3849,0,19,-195.798,2143.58,86.501,0,0,0,''),
(3849,0,20,-190.029,2141.38,83.2712,0,0,0,''),
(3849,0,21,-189.353,2138.65,83.1102,0,0,0,''),
(3849,0,22,-190.304,2135.73,81.5288,0,0,0,''),
(3849,0,23,-207.325,2112.43,81.0548,0,0,0,''),
(3849,0,24,-208.754,2109.9,81.0527,0,0,0,''),
(3849,0,25,-206.248,2108.62,81.0555,0,0,0,''),
(3849,0,26,-202.017,2106.64,78.6836,0,0,0,''),
(3849,0,27,-200.928,2104.49,78.5569,0,0,0,''),
(3849,0,28,-201.845,2101.17,76.9256,0,0,0,''),
(3849,0,29,-202.844,2100.11,76.8911,0,0,0,''),
(3849,0,30,-213.326,2105.83,76.8925,0,0,0,''),
(3849,0,31,-226.993,2111.47,76.8892,0,0,0,''),
(3849,0,32,-227.955,2112.34,76.8895,0,0,0,''),
(3849,0,33,-230.05,2106.64,76.8895,0,0,0,''),
(3850,0,0,-241.817,2122.9,81.179,0,0,0,'SAY_FREE_AS'),
(3850,0,1,-247.139,2124.89,81.179,0,0,0,''),
(3850,0,2,-253.179,2127.41,81.179,0,0,0,''),
(3850,0,3,-253.898,2130.87,81.179,0,0,0,''),
(3850,0,4,-249.889,2142.31,86.972,0,0,0,''),
(3850,0,5,-248.205,2144.02,87.013,0,0,0,''),
(3850,0,6,-240.553,2140.55,87.012,0,0,0,''),
(3850,0,7,-237.514,2142.07,87.012,0,0,0,''),
(3850,0,8,-235.638,2149.23,90.587,0,0,0,''),
(3850,0,9,-237.188,2151.95,90.624,0,0,0,''),
(3850,0,10,-241.162,2153.65,90.624,0,0,0,'SAY_OPEN_DOOR_AS'),
(3850,0,11,-241.13,2154.56,90.624,0,5000,0,'cast'),
(3850,0,12,-241.13,2154.56,90.624,0,0,0,''),
(3850,0,13,-241.13,2154.56,90.624,0,5000,0,'SAY_POST_DOOR_AS'),
(3850,0,14,-241.13,2154.56,90.624,0,2500,0,'cast'),
(3850,0,15,-241.13,2154.56,90.624,0,0,0,'SAY_VANISH_AS'),
(4484,0,0,3178.57,188.52,4.27,0,0,0,'SAY_QUEST_START'),
(4484,0,1,3189.82,198.56,5.62,0,0,0,''),
(4484,0,2,3215.21,185.78,6.43,0,0,0,''),
(4484,0,3,3224.05,183.08,6.74,0,0,0,''),
(4484,0,4,3228.11,194.97,7.51,0,0,0,''),
(4484,0,5,3225.33,201.78,7.25,0,0,0,''),
(4484,0,6,3233.33,226.88,10.18,0,0,0,''),
(4484,0,7,3274.12,225.83,10.72,0,0,0,''),
(4484,0,8,3321.63,209.82,12.36,0,0,0,''),
(4484,0,9,3369.66,226.21,11.69,0,0,0,''),
(4484,0,10,3402.35,227.2,9.48,0,0,0,''),
(4484,0,11,3441.92,224.75,10.85,0,0,0,''),
(4484,0,12,3453.87,220.31,12.52,0,0,0,''),
(4484,0,13,3472.51,213.68,13.26,0,0,0,''),
(4484,0,14,3515.49,212.96,9.76,0,5000,0,'SAY_FIRST_AMBUSH_START'),
(4484,0,15,3516.21,212.84,9.52,0,20000,0,'SAY_FIRST_AMBUSH_END'),
(4484,0,16,3548.22,217.12,7.34,0,0,0,''),
(4484,0,17,3567.57,219.43,5.22,0,0,0,''),
(4484,0,18,3659.85,209.68,2.27,0,0,0,''),
(4484,0,19,3734.9,177.64,6.75,0,0,0,''),
(4484,0,20,3760.24,162.51,7.49,0,5000,0,'SAY_SECOND_AMBUSH_START'),
(4484,0,21,3761.58,161.14,7.37,0,20000,0,'SAY_SECOND_AMBUSH_END'),
(4484,0,22,3801.17,129.87,9.38,0,0,0,''),
(4484,0,23,3815.53,118.53,10.14,0,0,0,''),
(4484,0,24,3894.58,44.88,15.49,0,0,0,''),
(4484,0,25,3972.83,0.42,17.34,0,0,0,''),
(4484,0,26,4026.41,-7.63,16.77,0,0,0,''),
(4484,0,27,4086.24,12.32,16.12,0,0,0,''),
(4484,0,28,4158.79,50.67,25.86,0,0,0,''),
(4484,0,29,4223.48,99.52,35.47,0,5000,0,'SAY_FINAL_AMBUSH_START'),
(4484,0,30,4224.28,100.02,35.49,0,10000,0,'SAY_QUEST_END'),
(4484,0,31,4243.45,117.44,38.83,0,0,0,''),
(4484,0,32,4264.18,134.22,42.96,0,0,0,''),
(4500,0,0,-3132.84,-2880.27,34.7842,0,2500,0,''),
(4500,0,1,-3120.26,-2877.83,34.917,0,0,0,''),
(4500,0,2,-3116.49,-2850.67,34.869,0,0,0,''),
(4500,0,3,-3093.47,-2819.19,34.432,0,0,0,''),
(4500,0,4,-3104.73,-2802.02,33.954,0,0,0,''),
(4500,0,5,-3105.91,-2780.23,34.469,0,0,0,''),
(4500,0,6,-3116.08,-2757.9,34.734,0,0,0,''),
(4500,0,7,-3125.23,-2733.96,33.189,0,0,0,''),
(4508,0,0,2194.38,1791.65,65.48,0,5000,0,''),
(4508,0,1,2188.56,1805.87,64.45,0,0,0,''),
(4508,0,2,2186.2,1836.28,59.859,0,5000,0,'SAY_WILLIX_1'),
(4508,0,3,2163.27,1851.67,56.73,0,0,0,''),
(4508,0,4,2140.22,1845.02,48.32,0,0,0,''),
(4508,0,5,2131.5,1804.29,46.85,0,0,0,''),
(4508,0,6,2096.18,1789.03,51.13,0,3000,0,'SAY_WILLIX_2'),
(4508,0,7,2074.46,1780.09,55.64,0,0,0,''),
(4508,0,8,2055.12,1768.67,58.46,0,0,0,''),
(4508,0,9,2037.83,1748.62,60.27,0,5000,0,'SAY_WILLIX_3'),
(4508,0,10,2037.51,1728.94,60.85,0,0,0,''),
(4508,0,11,2044.7,1711.71,59.71,0,0,0,''),
(4508,0,12,2067.66,1701.84,57.77,0,0,0,''),
(4508,0,13,2078.91,1704.54,56.77,0,0,0,''),
(4508,0,14,2097.65,1715.24,54.74,0,3000,0,'SAY_WILLIX_4'),
(4508,0,15,2106.44,1720.98,54.41,0,0,0,''),
(4508,0,16,2123.96,1732.56,52.27,0,0,0,''),
(4508,0,17,2153.82,1728.73,51.92,0,0,0,''),
(4508,0,18,2163.49,1706.33,54.42,0,0,0,''),
(4508,0,19,2158.75,1695.98,55.7,0,0,0,''),
(4508,0,20,2142.6,1680.72,58.24,0,0,0,''),
(4508,0,21,2118.31,1671.54,59.21,0,0,0,''),
(4508,0,22,2086.02,1672.04,61.24,0,0,0,''),
(4508,0,23,2068.81,1658.93,61.24,0,0,0,''),
(4508,0,24,2062.82,1633.31,64.35,0,0,0,''),
(4508,0,25,2060.92,1600.11,62.41,0,3000,0,'SAY_WILLIX_5'),
(4508,0,26,2063.05,1589.16,63.26,0,0,0,''),
(4508,0,27,2063.67,1577.22,65.89,0,0,0,''),
(4508,0,28,2057.94,1560.68,68.4,0,0,0,''),
(4508,0,29,2052.56,1548.05,73.35,0,0,0,''),
(4508,0,30,2045.22,1543.4,76.65,0,0,0,''),
(4508,0,31,2034.35,1543.01,79.7,0,0,0,''),
(4508,0,32,2029.95,1542.94,80.79,0,0,0,''),
(4508,0,33,2021.34,1538.67,80.8,0,0,0,'SAY_WILLIX_6'),
(4508,0,34,2012.45,1549.48,79.93,0,0,0,''),
(4508,0,35,2008.05,1554.92,80.44,0,0,0,''),
(4508,0,36,2006.54,1562.72,81.11,0,0,0,''),
(4508,0,37,2003.8,1576.43,81.57,0,0,0,''),
(4508,0,38,2000.57,1590.06,80.62,0,0,0,''),
(4508,0,39,1998.96,1596.87,80.22,0,0,0,''),
(4508,0,40,1991.19,1600.82,79.39,0,0,0,''),
(4508,0,41,1980.71,1601.44,79.77,0,0,0,''),
(4508,0,42,1967.22,1600.18,80.62,0,0,0,''),
(4508,0,43,1956.43,1596.97,81.75,0,0,0,''),
(4508,0,44,1954.87,1592.02,82.18,0,3000,0,'SAY_WILLIX_7'),
(4508,0,45,1948.35,1571.35,80.96,0,30000,0,'SAY_WILLIX_END'),
(4508,0,46,1947.02,1566.42,81.8,0,30000,0,''),
(4880,0,0,-2670.22,-3446.19,34.085,0,0,0,''),
(4880,0,1,-2683.96,-3451.09,34.707,0,0,0,''),
(4880,0,2,-2703.24,-3454.82,33.395,0,0,0,''),
(4880,0,3,-2721.61,-3457.41,33.626,0,0,0,''),
(4880,0,4,-2739.98,-3459.84,33.329,0,0,0,''),
(4880,0,5,-2756.24,-3460.52,32.037,0,5000,0,'SAY_STINKY_FIRST_STOP'),
(4880,0,6,-2764.52,-3472.71,33.75,0,0,0,''),
(4880,0,7,-2773.68,-3482.91,32.84,0,0,0,''),
(4880,0,8,-2781.39,-3490.61,32.598,0,0,0,''),
(4880,0,9,-2788.31,-3492.9,30.761,0,0,0,''),
(4880,0,10,-2794.58,-3489.19,31.119,0,5000,0,'SAY_SECOND_STOP'),
(4880,0,11,-2789.43,-3498.04,31.05,0,0,0,''),
(4880,0,12,-2786.97,-3508.17,31.983,0,0,0,''),
(4880,0,13,-2786.77,-3519.95,31.079,0,0,0,''),
(4880,0,14,-2789.36,-3525.02,31.831,0,0,0,''),
(4880,0,15,-2797.95,-3523.69,31.697,0,0,0,''),
(4880,0,16,-2812.97,-3519.84,29.864,0,0,0,''),
(4880,0,17,-2818.33,-3521.4,30.563,0,0,0,''),
(4880,0,18,-2824.77,-3528.73,32.399,0,0,0,''),
(4880,0,19,-2830.7,-3539.88,32.505,0,0,0,''),
(4880,0,20,-2836.24,-3549.96,31.18,0,0,0,''),
(4880,0,21,-2837.58,-3561.05,30.74,0,0,0,''),
(4880,0,22,-2834.45,-3568.26,30.751,0,0,0,''),
(4880,0,23,-2827.35,-3569.81,31.316,0,0,0,''),
(4880,0,24,-2817.38,-3566.96,30.947,0,5000,0,'SAY_THIRD_STOP_1'),
(4880,0,25,-2817.38,-3566.96,30.947,0,2000,0,'SAY_THIRD_STOP_2'),
(4880,0,26,-2817.38,-3566.96,30.947,0,0,0,'SAY_THIRD_STOP_3'),
(4880,0,27,-2818.81,-3579.42,28.525,0,0,0,''),
(4880,0,28,-2820.21,-3590.64,30.269,0,0,0,''),
(4880,0,29,-2820.85,-3593.94,31.15,0,3000,0,''),
(4880,0,30,-2820.85,-3593.94,31.15,0,3000,0,'SAY_PLANT_GATHERED'),
(4880,0,31,-2834.21,-3592.04,33.79,0,0,0,''),
(4880,0,32,-2840.31,-3586.21,36.288,0,0,0,''),
(4880,0,33,-2847.49,-3576.42,37.66,0,0,0,''),
(4880,0,34,-2855.72,-3565.18,39.39,0,0,0,''),
(4880,0,35,-2861.78,-3552.9,41.243,0,0,0,''),
(4880,0,36,-2869.54,-3545.58,40.701,0,0,0,''),
(4880,0,37,-2877.78,-3538.37,37.274,0,0,0,''),
(4880,0,38,-2882.68,-3534.17,34.844,0,0,0,''),
(4880,0,39,-2888.57,-3534.12,34.298,0,4000,0,'SAY_STINKY_END'),
(4880,0,40,-2888.57,-3534.12,34.298,0,0,0,''),
(4962,0,0,-3804.44,-828.048,10.0931,0,0,0,''),
(4962,0,1,-3803.93,-835.772,10.0777,0,0,0,''),
(4962,0,2,-3792.63,-835.671,9.65566,0,0,0,''),
(4962,0,3,-3772.43,-835.346,10.869,0,0,0,''),
(4962,0,4,-3765.94,-840.129,10.8856,0,0,0,''),
(4962,0,5,-3738.63,-830.997,11.0574,0,0,0,''),
(4962,0,6,-3690.22,-862.262,9.96045,0,0,0,''),
(4983,0,0,-3322.65,-3124.63,33.842,0,0,0,''),
(4983,0,1,-3326.34,-3126.83,34.426,0,0,0,''),
(4983,0,2,-3336.98,-3129.61,30.692,0,0,0,''),
(4983,0,3,-3342.6,-3132.15,30.422,0,0,0,''),
(4983,0,4,-3355.83,-3140.95,29.534,0,0,0,''),
(4983,0,5,-3365.83,-3144.28,35.176,0,0,0,''),
(4983,0,6,-3368.9,-3147.27,36.091,0,0,0,''),
(4983,0,7,-3369.36,-3169.83,36.325,0,0,0,''),
(4983,0,8,-3371.44,-3183.91,33.454,0,0,0,''),
(4983,0,9,-3373.82,-3190.86,34.717,0,5000,0,'SAY_OGR_SPOT'),
(4983,0,10,-3368.53,-3198.21,34.926,0,0,0,'SAY_OGR_RET_WHAT'),
(4983,0,11,-3366.27,-3210.87,33.733,0,5000,0,'pause'),
(4983,0,12,-3368.53,-3198.21,34.926,0,0,0,''),
(4983,0,13,-3373.82,-3190.86,34.717,0,0,0,''),
(4983,0,14,-3371.44,-3183.91,33.454,0,0,0,''),
(4983,0,15,-3369.36,-3169.83,36.325,0,0,0,''),
(4983,0,16,-3368.9,-3147.27,36.091,0,0,0,''),
(4983,0,17,-3365.83,-3144.28,35.176,0,0,0,''),
(4983,0,18,-3355.83,-3140.95,29.534,0,0,0,''),
(4983,0,19,-3342.6,-3132.15,30.422,0,0,0,''),
(4983,0,20,-3336.98,-3129.61,30.692,0,0,0,''),
(4983,0,21,-3326.34,-3126.83,34.426,0,0,0,''),
(4983,0,22,-3322.65,-3124.63,33.842,0,0,0,''),
(5391,0,0,-9901.12,-3727.29,22.11,0,3000,0,''),
(5391,0,1,-9909.27,-3727.81,23.25,0,0,0,''),
(5391,0,2,-9935.25,-3729.02,22.11,0,0,0,''),
(5391,0,3,-9945.83,-3719.34,21.68,0,0,0,''),
(5391,0,4,-9963.41,-3710.18,21.71,0,0,0,''),
(5391,0,5,-9972.75,-3690.13,21.68,0,0,0,''),
(5391,0,6,-9989.7,-3669.67,21.67,0,0,0,''),
(5391,0,7,-9989.21,-3647.76,23,0,0,0,''),
(5391,0,8,-9992.27,-3633.74,21.67,0,0,0,''),
(5391,0,9,-10002.3,-3611.67,22.26,0,0,0,''),
(5391,0,10,-9999.25,-3586.33,21.85,0,0,0,''),
(5391,0,11,-10006.5,-3571.99,21.67,0,0,0,''),
(5391,0,12,-10014.3,-3545.24,21.67,0,0,0,''),
(5391,0,13,-10018.9,-3525.03,21.68,0,0,0,''),
(5391,0,14,-10030.2,-3514.77,21.67,0,0,0,''),
(5391,0,15,-10045.1,-3501.49,21.67,0,0,0,''),
(5391,0,16,-10052.9,-3479.13,21.67,0,0,0,''),
(5391,0,17,-10060.7,-3460.31,21.67,0,0,0,''),
(5391,0,18,-10074.7,-3436.85,20.97,0,0,0,''),
(5391,0,19,-10074.7,-3436.85,20.97,0,0,0,''),
(5391,0,20,-10072.9,-3408.92,20.43,0,15000,0,''),
(5391,0,21,-10108,-3406.05,22.06,0,0,0,''),
(5644,0,1,-339.679,1752.04,139.482,0,0,0,''),
(5644,0,2,-328.957,1734.95,139.327,0,0,0,''),
(5644,0,3,-338.29,1731.36,139.327,0,0,0,''),
(5644,0,4,-350.747,1731.12,139.338,0,0,0,''),
(5644,0,5,-365.064,1739.04,139.376,0,0,0,''),
(5644,0,6,-371.105,1746.03,139.374,0,0,0,''),
(5644,0,7,-383.141,1738.62,138.93,0,0,0,''),
(5644,0,8,-390.445,1733.98,136.353,0,0,0,''),
(5644,0,9,-401.368,1726.77,131.071,0,0,0,''),
(5644,0,10,-416.016,1721.19,129.807,0,0,0,''),
(5644,0,11,-437.139,1709.82,126.342,0,0,0,''),
(5644,0,12,-455.83,1695.61,119.305,0,0,0,''),
(5644,0,13,-459.862,1687.92,116.059,0,0,0,''),
(5644,0,14,-463.565,1679.1,111.653,0,0,0,''),
(5644,0,15,-461.485,1670.94,109.033,0,0,0,''),
(5644,0,16,-471.786,1647.34,102.862,0,0,0,''),
(5644,0,17,-477.146,1625.69,98.342,0,0,0,''),
(5644,0,18,-475.815,1615.81,97.07,0,0,0,''),
(5644,0,19,-474.329,1590.01,94.4982,0,0,0,''),
(6176,0,0,253.05,-1459.09,52.09,0,2000,0,'SAY_PROGRESS_1 and pause before running to summon location'),
(6176,0,1,256.87,-1440.35,50.09,0,0,0,''),
(6176,0,2,273.74,-1433.18,50.29,0,0,0,''),
(6176,0,3,297.77,-1436.7,46.96,0,0,0,''),
(6176,0,4,329.59,-1442.08,40.31,0,0,0,''),
(6176,0,5,332.73,-1455.6,42.24,0,2000,0,'pause before walking to summon location'),
(6176,0,6,323.83,-1468.92,42.24,0,2000,0,'pause before truning twards clyclonians spawn location'),
(6176,0,7,323.83,-1468.92,42.24,0,12000,0,'SAY_PROGRESS_2 and Summon Cyclonian, give 10 seconds for summon per spells cast time requirements and 2 seconds extra.'),
(6176,0,8,332.73,-1455.6,42.24,0,0,0,'runs back to spawn location'),
(6176,0,9,329.59,-1442.08,40.31,0,0,0,''),
(6176,0,10,297.77,-1436.7,46.96,0,0,0,''),
(6176,0,11,273.74,-1433.18,50.29,0,0,0,''),
(6176,0,12,256.87,-1440.35,50.09,0,0,0,''),
(6176,0,13,253.05,-1459.09,52.09,0,0,0,''),
(6176,0,14,250.84,-1470.58,55.4491,0,0,0,''),
(6182,0,0,-11480.7,1545.09,49.8986,0,0,0,''),
(6182,0,1,-11466.8,1530.15,50.2636,0,0,0,''),
(6182,0,2,-11465.2,1528.34,50.9544,0,0,0,'entrance hut'),
(6182,0,3,-11463,1525.24,50.9377,0,0,0,''),
(6182,0,4,-11461,1526.61,50.9377,0,5000,0,'pick up rifle'),
(6182,0,5,-11463,1525.24,50.9377,0,0,0,''),
(6182,0,6,-11465.2,1528.34,50.9544,0,0,0,''),
(6182,0,7,-11468.4,1535.08,50.4009,0,15000,0,'hold, prepare for wave1'),
(6182,0,8,-11468.4,1535.08,50.4009,0,15000,0,'hold, prepare for wave2'),
(6182,0,9,-11468.4,1535.08,50.4009,0,10000,0,'hold, prepare for wave3'),
(6182,0,10,-11467.9,1532.46,50.3489,0,0,0,'we are done'),
(6182,0,11,-11466.1,1529.86,50.2094,0,0,0,''),
(6182,0,12,-11463,1525.24,50.9377,0,0,0,''),
(6182,0,13,-11461,1526.61,50.9377,0,5000,0,'deliver rifle'),
(6182,0,14,-11463,1525.24,50.9377,0,0,0,''),
(6182,0,15,-11465.2,1528.34,50.9544,0,0,0,''),
(6182,0,16,-11470.3,1537.28,50.3785,0,0,0,''),
(6182,0,17,-11475.6,1548.68,50.1844,0,0,0,'complete quest'),
(6182,0,18,-11482.3,1557.41,48.6245,0,0,0,''),
(6575,0,0,1945.81,-431.54,16.36,0,0,0,''),
(6575,0,1,1946.21,-436.41,16.36,0,0,0,''),
(6575,0,2,1950.01,-444.11,14.63,0,0,0,''),
(6575,0,3,1956.08,-449.34,13.12,0,0,0,''),
(6575,0,4,1966.59,-450.55,11.27,0,0,0,''),
(6575,0,5,1976.09,-447.51,11.27,0,0,0,''),
(6575,0,6,1983.42,-435.85,11.27,0,0,0,''),
(6575,0,7,1978.17,-428.81,11.27,0,0,0,''),
(6575,0,8,1973.97,-422.08,9.04,0,0,0,''),
(6575,0,9,1963.84,-418.9,6.17,0,0,0,''),
(6575,0,10,1961.22,-422.74,6.17,0,0,0,''),
(6575,0,11,1964.8,-431.26,6.17,0,300000,0,''),
(7780,0,0,261.059,-2757.88,122.553,0,0,0,''),
(7780,0,1,259.812,-2758.25,122.555,0,0,0,'SAY_RIN_FREE'),
(7780,0,2,253.823,-2758.62,122.562,0,0,0,''),
(7780,0,3,241.395,-2769.75,123.309,0,0,0,''),
(7780,0,4,218.916,-2783.4,123.355,0,0,0,''),
(7780,0,5,209.088,-2789.68,122.001,0,0,0,''),
(7780,0,6,204.454,-2792.21,120.62,0,0,0,''),
(7780,0,7,182.013,-2810,113.887,0,0,0,'summon'),
(7780,0,8,164.412,-2825.16,107.779,0,0,0,''),
(7780,0,9,149.728,-2833.7,106.224,0,0,0,''),
(7780,0,10,142.448,-2838.81,109.665,0,0,0,''),
(7780,0,11,133.275,-2845.14,112.606,0,0,0,''),
(7780,0,12,111.247,-2861.07,116.305,0,0,0,''),
(7780,0,13,96.1041,-2874.89,114.397,0,0,0,'summon'),
(7780,0,14,73.3699,-2881.18,117.666,0,0,0,''),
(7780,0,15,58.5792,-2889.15,116.253,0,0,0,''),
(7780,0,16,33.2142,-2906.34,115.083,0,0,0,''),
(7780,0,17,19.5865,-2908.71,117.276,0,7500,0,'SAY_RIN_COMPLETE'),
(7780,0,18,10.2825,-2911.61,118.394,0,0,0,''),
(7780,0,19,-37.5804,-2942.73,117.145,0,0,0,''),
(7780,0,20,-68.5994,-2953.69,116.685,0,0,0,''),
(7780,0,21,-102.054,-2956.97,116.677,0,0,0,''),
(7780,0,22,-135.994,-2955.74,115.788,0,0,0,''),
(7780,0,23,-171.562,-2951.42,115.451,0,0,0,''),
(7784,0,0,-8845.65,-4373.98,43.87,0,5000,0,'SAY_START'),
(7784,0,1,-8840.79,-4373.73,44.24,0,0,0,''),
(7784,0,2,-8837.43,-4373.56,45.6,0,0,0,''),
(7784,0,3,-8832.74,-4373.32,45.68,0,0,0,''),
(7784,0,4,-8829.37,-4373.14,44.33,0,0,0,''),
(7784,0,5,-8817.38,-4372.41,35.58,0,0,0,''),
(7784,0,6,-8803.47,-4371.6,30.34,0,0,0,''),
(7784,0,7,-8795.1,-4365.61,26.08,0,0,0,''),
(7784,0,8,-8766.78,-4367.13,25.15,0,0,0,''),
(7784,0,9,-8755.63,-4367.54,24.63,0,0,0,''),
(7784,0,10,-8754.42,-4365.59,24.15,0,0,0,''),
(7784,0,11,-8728.82,-4353.13,20.9,0,0,0,''),
(7784,0,12,-8706.6,-4356.55,17.93,0,0,0,''),
(7784,0,13,-8679,-4380.23,12.64,0,0,0,''),
(7784,0,14,-8642.96,-4393.82,12.52,0,0,0,''),
(7784,0,15,-8611.19,-4399.11,9.55,0,0,0,''),
(7784,0,16,-8554.87,-4409.32,13.05,0,0,0,''),
(7784,0,17,-8531.64,-4411.96,11.2,0,0,0,''),
(7784,0,18,-8510.4,-4414.38,12.84,0,0,0,''),
(7784,0,19,-8476.92,-4418.34,9.71,0,0,0,''),
(7784,0,20,-8435.89,-4426.74,9.67,0,0,0,''),
(7784,0,21,-8381.89,-4446.4,10.23,0,0,0,''),
(7784,0,22,-8351.15,-4447.79,9.99,0,5000,0,'first ambush SAY_AMBUSH'),
(7784,0,23,-8324.18,-4445.05,9.71,0,0,0,''),
(7784,0,24,-8138.94,-4384.78,10.92,0,0,0,''),
(7784,0,25,-8036.87,-4443.38,9.65,0,0,0,''),
(7784,0,26,-7780.92,-4761.81,9.5,0,0,0,''),
(7784,0,27,-7587.67,-4765.01,8.96,0,0,0,''),
(7784,0,28,-7497.65,-4792.86,10.01,0,0,0,'second ambush SAY_AMBUSH'),
(7784,0,29,-7391.54,-4774.26,12.44,0,0,0,''),
(7784,0,30,-7308.42,-4739.87,12.65,0,0,0,''),
(7784,0,31,-7016.11,-4751.12,10.06,0,0,0,''),
(7784,0,32,-6985.52,-4777.41,10.26,0,0,0,''),
(7784,0,33,-6953.02,-4786,6.32,0,0,0,''),
(7784,0,34,-6940.37,-4831.03,0.67,0,10000,0,'quest complete SAY_END'),
(7806,0,0,495.404,-3478.35,114.837,0,0,0,''),
(7806,0,1,492.705,-3486.11,108.627,0,0,0,''),
(7806,0,2,487.25,-3485.76,107.89,0,0,0,''),
(7806,0,3,476.852,-3489.88,99.985,0,0,0,''),
(7806,0,4,467.212,-3493.36,99.819,0,0,0,''),
(7806,0,5,460.017,-3496.98,104.481,0,0,0,''),
(7806,0,6,439.619,-3500.73,110.534,0,0,0,''),
(7806,0,7,428.326,-3495.87,118.662,0,0,0,''),
(7806,0,8,424.664,-3489.38,121.999,0,0,0,''),
(7806,0,9,424.137,-3470.95,124.333,0,0,0,''),
(7806,0,10,421.791,-3449.24,119.126,0,0,0,''),
(7806,0,11,404.247,-3429.38,117.644,0,0,0,''),
(7806,0,12,335.465,-3430.72,116.456,0,0,0,''),
(7806,0,13,317.16,-3426.71,116.226,0,0,0,''),
(7806,0,14,331.18,-3464,117.143,0,0,0,''),
(7806,0,15,336.394,-3501.88,118.201,0,0,0,''),
(7806,0,16,337.251,-3544.76,117.284,0,0,0,''),
(7806,0,17,337.749,-3565.42,116.797,0,0,0,''),
(7806,0,18,336.011,-3597.36,118.225,0,0,0,''),
(7806,0,19,324.619,-3622.88,119.811,0,0,0,''),
(7806,0,20,308.027,-3648.6,123.047,0,0,0,''),
(7806,0,21,276.325,-3685.74,128.356,0,0,0,''),
(7806,0,22,239.981,-3717.33,131.874,0,0,0,''),
(7806,0,23,224.951,-3730.17,132.125,0,0,0,''),
(7806,0,24,198.708,-3768.29,129.42,0,0,0,''),
(7806,0,25,183.758,-3791.07,128.045,0,0,0,''),
(7806,0,26,178.111,-3801.58,128.37,0,3000,0,'SAY_OOX_DANGER'),
(7806,0,27,162.215,-3827.01,129.424,0,0,0,''),
(7806,0,28,141.665,-3864.52,131.419,0,0,0,''),
(7806,0,29,135.302,-3880.09,132.12,0,0,0,''),
(7806,0,30,122.461,-3910.07,135.605,0,0,0,''),
(7806,0,31,103.376,-3937.73,137.342,0,0,0,''),
(7806,0,32,81.4145,-3958.61,138.469,0,0,0,''),
(7806,0,33,55.3781,-3982,136.52,0,0,0,''),
(7806,0,34,13.9831,-4013.95,126.903,0,0,0,''),
(7806,0,35,-21.658,-4048.71,118.068,0,0,0,''),
(7806,0,36,-52.4431,-4081.21,117.477,0,0,0,''),
(7806,0,37,-102.711,-4116.76,118.666,0,0,0,''),
(7806,0,38,-92.9962,-4135.85,119.31,0,0,0,''),
(7806,0,39,-86.3913,-4153.33,122.502,0,0,0,''),
(7806,0,40,-85.7461,-4163.6,121.892,0,0,0,''),
(7806,0,41,-90.544,-4183.58,117.587,0,0,0,''),
(7806,0,42,-110.224,-4205.86,121.878,0,0,0,''),
(7806,0,43,-115.258,-4211.96,121.878,0,3000,0,'SAY_OOX_DANGER'),
(7806,0,44,-128.595,-4233.34,117.766,0,0,0,''),
(7806,0,45,-135.359,-4258.12,117.562,0,0,0,''),
(7806,0,46,-156.832,-4258.96,120.059,0,0,0,''),
(7806,0,47,-167.12,-4274.1,117.062,0,0,0,''),
(7806,0,48,-176.291,-4287.59,118.721,0,0,0,''),
(7806,0,49,-196.993,-4315.82,117.588,0,0,0,''),
(7806,0,50,-209.329,-4331.67,115.142,0,0,0,''),
(7806,0,51,-232.292,-4356.02,108.543,0,0,0,''),
(7806,0,52,-232.16,-4370.9,102.815,0,0,0,''),
(7806,0,53,-210.271,-4389.9,84.167,0,0,0,''),
(7806,0,54,-187.94,-4407.53,70.987,0,0,0,''),
(7806,0,55,-181.354,-4418.77,64.778,0,0,0,''),
(7806,0,56,-170.53,-4440.44,58.943,0,0,0,''),
(7806,0,57,-141.429,-4465.32,45.963,0,0,0,''),
(7806,0,58,-120.994,-4487.09,32.075,0,0,0,''),
(7806,0,59,-104.135,-4501.84,25.051,0,0,0,''),
(7806,0,60,-84.1547,-4529.44,11.952,0,0,0,''),
(7806,0,61,-88.6989,-4544.63,9.055,0,0,0,''),
(7806,0,62,-100.603,-4575.03,11.388,0,0,0,''),
(7806,0,63,-106.909,-4600.41,11.046,0,0,0,''),
(7806,0,64,-106.832,-4620.5,11.057,0,3000,0,'SAY_OOX_COMPLETE'),
(7807,0,0,-4943.74,1715.74,62.74,0,0,0,'SAY_START'),
(7807,0,1,-4944.93,1706.66,63.16,0,0,0,''),
(7807,0,2,-4942.82,1690.22,64.25,0,0,0,''),
(7807,0,3,-4946.47,1669.62,63.84,0,0,0,''),
(7807,0,4,-4955.93,1651.88,63,0,0,0,''),
(7807,0,5,-4967.58,1643.86,64.31,0,0,0,''),
(7807,0,6,-4978.12,1607.9,64.3,0,0,0,''),
(7807,0,7,-4975.38,1596.16,64.7,0,0,0,''),
(7807,0,8,-4972.82,1581.89,61.75,0,0,0,''),
(7807,0,9,-4958.65,1581.05,61.81,0,0,0,''),
(7807,0,10,-4936.72,1594.89,65.96,0,0,0,''),
(7807,0,11,-4885.69,1598.1,67.45,0,4000,0,'first ambush SAY_AMBUSH'),
(7807,0,12,-4874.2,1601.73,68.54,0,0,0,''),
(7807,0,13,-4816.64,1594.47,78.2,0,0,0,''),
(7807,0,14,-4802.2,1571.92,87.01,0,0,0,''),
(7807,0,15,-4746.4,1576.11,84.59,0,0,0,''),
(7807,0,16,-4739.72,1707.16,94.04,0,0,0,''),
(7807,0,17,-4674.03,1840.44,89.17,0,0,0,''),
(7807,0,18,-4667.94,1864.11,85.18,0,0,0,''),
(7807,0,19,-4668.08,1886.39,81.14,0,0,0,''),
(7807,0,20,-4679.43,1932.32,73.76,0,0,0,''),
(7807,0,21,-4674.17,1946.66,70.83,0,5000,0,'second ambush SAY_AMBUSH'),
(7807,0,22,-4643.94,1967.45,65.27,0,0,0,''),
(7807,0,23,-4595.6,2010.75,52.1,0,0,0,''),
(7807,0,24,-4562.65,2029.28,45.41,0,0,0,''),
(7807,0,25,-4538.56,2032.65,45.28,0,0,0,''),
(7807,0,26,-4531.96,2034.15,48.34,0,0,0,''),
(7807,0,27,-4507.75,2039.32,51.57,0,0,0,''),
(7807,0,28,-4482.74,2045.67,48.15,0,0,0,''),
(7807,0,29,-4460.87,2051.54,45.55,0,0,0,''),
(7807,0,30,-4449.97,2060.03,45.51,0,10000,0,'third ambush SAY_AMBUSH'),
(7807,0,31,-4448.99,2079.05,44.64,0,0,0,''),
(7807,0,32,-4436.64,2134.48,28.83,0,0,0,''),
(7807,0,33,-4429.25,2170.2,15.44,0,0,0,''),
(7807,0,34,-4424.83,2186.11,11.48,0,0,0,''),
(7807,0,35,-4416.71,2209.76,7.36,0,0,0,''),
(7807,0,36,-4405.25,2231.77,5.94,0,0,0,''),
(7807,0,37,-4377.61,2265.45,6.71,0,15000,0,'complete quest SAY_END'),
(7998,0,1,-510.13,-132.69,-152.5,0,0,0,''),
(7998,0,2,-511.099,-129.74,-153.845,0,0,0,''),
(7998,0,3,-511.79,-127.476,-155.551,0,0,0,''),
(7998,0,4,-512.969,-124.926,-156.115,0,5000,0,''),
(7998,0,5,-513.972,-120.236,-156.116,0,0,0,''),
(7998,0,6,-514.388,-115.19,-156.117,0,0,0,''),
(7998,0,7,-514.304,-111.478,-155.52,0,0,0,''),
(7998,0,8,-514.84,-107.663,-154.893,0,0,0,''),
(7998,0,9,-518.994,-101.416,-154.648,0,27000,0,''),
(7998,0,10,-526.998,-98.1488,-155.625,0,0,0,''),
(7998,0,11,-534.569,-105.41,-155.989,0,30000,0,''),
(7998,0,12,-535.534,-104.695,-155.971,0,0,0,''),
(7998,0,13,-541.63,-98.6583,-155.858,0,25000,0,''),
(7998,0,14,-535.092,-99.9175,-155.974,0,0,0,''),
(7998,0,15,-519.01,-101.51,-154.677,0,3000,0,''),
(7998,0,16,-504.466,-97.848,-150.955,0,30000,0,''),
(7998,0,17,-506.907,-89.1474,-151.083,0,23000,0,''),
(7998,0,18,-512.758,-101.902,-153.198,0,0,0,''),
(7998,0,19,-519.988,-124.848,-156.128,0,86400000,0,'this npc should not reset on wp end'),
(8284,0,0,-7007.21,-1749.16,234.182,0,3000,0,'stand up'),
(8284,0,1,-7007.32,-1729.85,234.162,0,0,0,''),
(8284,0,2,-7006.39,-1726.52,234.099,0,0,0,''),
(8284,0,3,-7003.26,-1726.9,234.594,0,0,0,''),
(8284,0,4,-6994.78,-1733.57,238.281,0,0,0,''),
(8284,0,5,-6987.9,-1735.94,240.727,0,0,0,''),
(8284,0,6,-6978.7,-1736.99,241.809,0,0,0,''),
(8284,0,7,-6964.26,-1740.25,241.713,0,0,0,''),
(8284,0,8,-6946.7,-1746.28,241.667,0,0,0,''),
(8284,0,9,-6938.75,-1749.38,240.744,0,0,0,''),
(8284,0,10,-6927,-1768.78,240.744,0,0,0,''),
(8284,0,11,-6909.45,-1791.26,240.744,0,0,0,''),
(8284,0,12,-6898.23,-1804.87,240.744,0,0,0,''),
(8284,0,13,-6881.28,-1821.79,240.744,0,0,0,''),
(8284,0,14,-6867.65,-1832.67,240.706,0,0,0,''),
(8284,0,15,-6850.18,-1839.25,243.006,0,0,0,''),
(8284,0,16,-6829.38,-1847.64,244.19,0,0,0,''),
(8284,0,17,-6804.62,-1857.54,244.209,0,0,0,''),
(8284,0,18,-6776.42,-1868.88,244.142,0,0,0,''),
(8284,0,19,-6753.47,-1876.91,244.17,0,10000,0,'stop'),
(8284,0,20,-6753.47,-1876.91,244.17,0,0,0,'ambush'),
(8284,0,21,-6731.03,-1884.94,244.144,0,0,0,''),
(8284,0,22,-6705.74,-1896.78,244.144,0,0,0,''),
(8284,0,23,-6678.96,-1909.61,244.369,0,0,0,''),
(8284,0,24,-6654.26,-1916.76,244.145,0,0,0,''),
(8284,0,25,-6620.6,-1917.61,244.149,0,0,0,''),
(8284,0,26,-6575.96,-1922.41,244.149,0,0,0,''),
(8284,0,27,-6554.81,-1929.88,244.162,0,0,0,''),
(8284,0,28,-6521.86,-1947.32,244.151,0,0,0,''),
(8284,0,29,-6493.32,-1962.65,244.151,0,0,0,''),
(8284,0,30,-6463.35,-1975.54,244.213,0,0,0,''),
(8284,0,31,-6435.43,-1983.85,244.548,0,0,0,''),
(8284,0,32,-6418.38,-1985.78,246.554,0,0,0,''),
(8284,0,33,-6389.78,-1986.54,246.771,0,30000,0,'quest complete'),
(8516,0,1,2603.18,725.259,54.6927,0,0,0,''),
(8516,0,2,2587.13,734.392,55.231,0,0,0,''),
(8516,0,3,2570.69,753.572,54.5855,0,0,0,''),
(8516,0,4,2558.51,747.66,54.4482,0,0,0,''),
(8516,0,5,2544.23,772.924,47.9255,0,0,0,''),
(8516,0,6,2530.08,797.475,45.97,0,0,0,''),
(8516,0,7,2521.83,799.127,44.3061,0,0,0,''),
(8516,0,8,2502.61,789.222,39.5074,0,0,0,''),
(8516,0,9,2495.25,789.406,39.499,0,0,0,''),
(8516,0,10,2488.07,802.455,42.9834,0,0,0,''),
(8516,0,11,2486.64,826.649,43.6363,0,0,0,''),
(8516,0,12,2492.64,835.166,45.1427,0,0,0,''),
(8516,0,13,2505.02,847.564,47.6487,0,0,0,''),
(8516,0,14,2538.96,877.362,47.6781,0,0,0,''),
(8516,0,15,2546.07,885.672,47.6789,0,0,0,''),
(8516,0,16,2548.02,897.584,47.7277,0,0,0,''),
(8516,0,17,2544.29,909.116,46.2506,0,0,0,''),
(8516,0,18,2523.6,920.306,45.8717,0,0,0,''),
(8516,0,19,2522.69,933.546,47.5769,0,0,0,''),
(8516,0,20,2531.63,959.893,49.4111,0,0,0,''),
(8516,0,21,2540.23,973.338,50.1241,0,0,0,''),
(8516,0,22,2547.21,977.489,49.9759,0,0,0,''),
(8516,0,23,2558.75,969.243,50.7353,0,0,0,''),
(8516,0,24,2575.6,950.138,52.846,0,0,0,''),
(8516,0,25,2575.6,950.138,52.846,0,0,0,''),
(9023,0,1,316.336,-225.528,-77.7258,0,2000,0,'SAY_WINDSOR_START'),
(9023,0,2,322.96,-207.13,-77.87,0,0,0,''),
(9023,0,3,281.05,-172.16,-75.12,0,0,0,''),
(9023,0,4,272.19,-139.14,-70.61,0,0,0,''),
(9023,0,5,283.62,-116.09,-70.21,0,0,0,''),
(9023,0,6,296.18,-94.3,-74.08,0,0,0,''),
(9023,0,7,294.57,-93.11,-74.08,0,0,0,'escort paused - SAY_WINDSOR_CELL_DUGHAL_1'),
(9023,0,8,294.57,-93.11,-74.08,0,10000,0,''),
(9023,0,9,294.57,-93.11,-74.08,0,3000,0,'SAY_WINDSOR_CELL_DUGHAL_3'),
(9023,0,10,314.31,-74.31,-76.09,0,0,0,''),
(9023,0,11,360.22,-62.93,-66.77,0,0,0,''),
(9023,0,12,383.38,-69.4,-63.25,0,0,0,''),
(9023,0,13,389.99,-67.86,-62.57,0,0,0,''),
(9023,0,14,400.98,-72.01,-62.31,0,0,0,'SAY_WINDSOR_EQUIPMENT_1'),
(9023,0,15,404.22,-62.3,-63.5,0,2000,0,''),
(9023,0,16,404.22,-62.3,-63.5,0,1500,0,'open supply door'),
(9023,0,17,407.65,-51.86,-63.96,0,0,0,''),
(9023,0,18,403.61,-51.71,-63.92,0,1000,0,'SAY_WINDSOR_EQUIPMENT_2'),
(9023,0,19,403.61,-51.71,-63.92,0,2000,0,''),
(9023,0,20,403.61,-51.71,-63.92,0,1000,0,'open supply crate'),
(9023,0,21,403.61,-51.71,-63.92,0,1000,0,'update entry to Reginald Windsor'),
(9023,0,22,403.61,-52.71,-63.92,0,4000,0,'SAY_WINDSOR_EQUIPMENT_3'),
(9023,0,23,403.61,-52.71,-63.92,0,4000,0,'SAY_WINDSOR_EQUIPMENT_4'),
(9023,0,24,406.33,-54.87,-63.95,0,0,0,''),
(9023,0,25,403.86,-73.88,-62.02,0,0,0,''),
(9023,0,26,428.8,-81.34,-64.91,0,0,0,''),
(9023,0,27,557.03,-119.71,-61.83,0,0,0,''),
(9023,0,28,573.4,-124.39,-65.07,0,0,0,''),
(9023,0,29,593.91,-130.29,-69.25,0,0,0,''),
(9023,0,30,593.21,-132.16,-69.25,0,0,0,'escort paused - SAY_WINDSOR_CELL_JAZ_1'),
(9023,0,31,593.21,-132.16,-69.25,0,1000,0,''),
(9023,0,32,593.21,-132.16,-69.25,0,3000,0,'SAY_WINDSOR_CELL_JAZ_2'),
(9023,0,33,622.81,-135.55,-71.92,0,0,0,''),
(9023,0,34,634.68,-151.29,-70.32,0,0,0,''),
(9023,0,35,635.06,-153.25,-70.32,0,0,0,'escort paused - SAY_WINDSOR_CELL_SHILL_1'),
(9023,0,36,635.06,-153.25,-70.32,0,3000,0,''),
(9023,0,37,635.06,-153.25,-70.32,0,5000,0,'SAY_WINDSOR_CELL_SHILL_2'),
(9023,0,38,635.06,-153.25,-70.32,0,2000,0,'SAY_WINDSOR_CELL_SHILL_3'),
(9023,0,39,655.25,-172.39,-73.72,0,0,0,''),
(9023,0,40,654.79,-226.3,-83.06,0,0,0,''),
(9023,0,41,622.85,-268.85,-83.96,0,0,0,''),
(9023,0,42,579.45,-275.56,-80.44,0,0,0,''),
(9023,0,43,561.19,-266.85,-75.59,0,0,0,''),
(9023,0,44,547.91,-253.92,-70.34,0,0,0,''),
(9023,0,45,549.2,-252.4,-70.34,0,0,0,'escort paused - SAY_WINDSOR_CELL_CREST_1'),
(9023,0,46,549.2,-252.4,-70.34,0,1000,0,''),
(9023,0,47,549.2,-252.4,-70.34,0,4000,0,'SAY_WINDSOR_CELL_CREST_2'),
(9023,0,48,555.33,-269.16,-74.4,0,0,0,''),
(9023,0,49,554.31,-270.88,-74.4,0,0,0,'escort paused - SAY_WINDSOR_CELL_TOBIAS_1'),
(9023,0,50,554.31,-270.88,-74.4,0,10000,0,''),
(9023,0,51,554.31,-270.88,-74.4,0,4000,0,'SAY_WINDSOR_CELL_TOBIAS_2'),
(9023,0,52,536.1,-249.6,-67.47,0,0,0,''),
(9023,0,53,520.94,-216.65,-59.28,0,0,0,''),
(9023,0,54,505.99,-148.74,-62.17,0,0,0,''),
(9023,0,55,484.21,-56.24,-62.43,0,0,0,''),
(9023,0,56,470.39,-6.01,-70.1,0,0,0,''),
(9023,0,57,452.45,29.85,-70.37,0,1500,0,'SAY_WINDSOR_FREE_1'),
(9023,0,58,452.45,29.85,-70.37,0,15000,0,'SAY_WINDSOR_FREE_2'),
(9502,0,0,847.848,-230.067,-43.614,0,0,0,''),
(9502,0,1,868.122,-223.884,-43.695,0,0,0,'YELL_PHALANX_AGGRO'),
(9503,0,0,885.185,-194.007,-43.4584,0,0,0,''),
(9503,0,1,885.185,-194.007,-43.4584,0,0,0,''),
(9503,0,2,872.764,-185.606,-43.7037,0,5000,0,'b1'),
(9503,0,3,867.923,-188.006,-43.7037,0,5000,0,'b2'),
(9503,0,4,863.296,-190.795,-43.7037,0,5000,0,'b3'),
(9503,0,5,856.14,-194.653,-43.7037,0,5000,0,'b4'),
(9503,0,6,851.879,-196.928,-43.7037,0,15000,0,'b5'),
(9503,0,7,877.035,-187.048,-43.7037,0,0,0,''),
(9503,0,8,891.198,-197.924,-43.6204,0,0,0,'home'),
(9503,0,9,876.935,-189.007,-43.4584,0,0,0,'Nagmara escort'),
(9503,0,10,885.185,-194.007,-43.4584,0,0,0,''),
(9503,0,11,869.124,-202.852,-43.7088,0,0,0,''),
(9503,0,12,869.465,-202.878,-43.4588,0,0,0,''),
(9503,0,13,864.244,-210.826,-43.459,0,0,0,''),
(9503,0,14,866.824,-220.959,-43.4472,0,0,0,''),
(9503,0,15,867.074,-221.959,-43.4472,0,0,0,''),
(9503,0,16,870.419,-225.675,-43.5566,0,0,0,'open door'),
(9503,0,17,872.169,-227.425,-43.5566,0,0,0,''),
(9503,0,18,872.919,-228.175,-43.5566,0,0,0,''),
(9503,0,19,875.919,-230.925,-43.5566,0,0,0,''),
(9503,0,20,876.919,-230.175,-43.5566,0,0,0,''),
(9503,0,21,877.919,-229.425,-43.5566,0,0,0,''),
(9503,0,22,882.395,-225.949,-46.7405,0,0,0,''),
(9503,0,23,885.895,-223.699,-49.2405,0,0,0,''),
(9503,0,24,887.645,-222.449,-49.2405,0,0,0,''),
(9503,0,25,885.937,-223.351,-49.2954,0,0,0,''),
(9503,0,26,887.437,-222.351,-49.2954,0,0,0,''),
(9503,0,27,888.937,-221.601,-49.5454,0,0,0,''),
(9503,0,28,887.687,-220.101,-49.5454,0,0,0,''),
(9503,0,29,886.687,-218.851,-49.5454,0,0,0,''),
(9503,0,30,887.567,-220.04,-49.7059,0,0,0,''),
(9503,0,31,886.567,-218.79,-49.7059,0,0,0,''),
(9503,0,32,886.067,-218.29,-49.7059,0,0,0,''),
(9503,0,33,880.825,-221.389,-49.9562,0,0,0,'stop'),
(9520,0,1,-7699.62,-1444.29,139.87,0,4000,0,'SAY_START'),
(9520,0,2,-7670.67,-1458.25,140.74,0,0,0,''),
(9520,0,3,-7675.26,-1465.58,140.74,0,0,0,''),
(9520,0,4,-7685.84,-1472.66,140.75,0,0,0,''),
(9520,0,5,-7700.08,-1473.41,140.79,0,0,0,''),
(9520,0,6,-7712.55,-1470.19,140.79,0,0,0,''),
(9520,0,7,-7717.27,-1481.7,140.72,0,5000,0,'SAY_PAY'),
(9520,0,8,-7726.23,-1500.78,132.99,0,0,0,''),
(9520,0,9,-7744.61,-1531.61,132.69,0,0,0,''),
(9520,0,10,-7763.08,-1536.22,131.93,0,0,0,''),
(9520,0,11,-7815.32,-1522.61,134.16,0,0,0,''),
(9520,0,12,-7850.26,-1516.87,138.17,0,0,0,'SAY_FIRST_AMBUSH_START'),
(9520,0,13,-7850.26,-1516.87,138.17,0,3000,0,'SAY_FIRST_AMBUSH_END'),
(9520,0,14,-7881.01,-1508.49,142.37,0,0,0,''),
(9520,0,15,-7888.91,-1458.09,144.79,0,0,0,''),
(9520,0,16,-7889.18,-1430.21,145.31,0,0,0,''),
(9520,0,17,-7900.53,-1427.01,150.26,0,0,0,''),
(9520,0,18,-7904.15,-1429.91,150.27,0,0,0,''),
(9520,0,19,-7921.48,-1425.47,140.54,0,0,0,''),
(9520,0,20,-7941.43,-1413.1,134.35,0,0,0,''),
(9520,0,21,-7964.85,-1367.45,132.99,0,0,0,''),
(9520,0,22,-7989.95,-1319.12,133.71,0,0,0,''),
(9520,0,23,-8010.43,-1270.23,133.42,0,0,0,''),
(9520,0,24,-8025.62,-1243.78,133.91,0,0,0,'SAY_SEC_AMBUSH_START'),
(9520,0,25,-8025.62,-1243.78,133.91,0,3000,0,'SAY_SEC_AMBUSH_END'),
(9520,0,26,-8015.22,-1196.98,146.76,0,0,0,''),
(9520,0,27,-7994.68,-1151.38,160.7,0,0,0,''),
(9520,0,28,-7970.91,-1132.81,170.16,0,0,0,'summon Searscale Drakes'),
(9520,0,29,-7927.59,-1122.79,185.86,0,0,0,''),
(9520,0,30,-7897.67,-1126.67,194.32,0,0,0,'SAY_THIRD_AMBUSH_START'),
(9520,0,31,-7897.67,-1126.67,194.32,0,3000,0,'SAY_THIRD_AMBUSH_END'),
(9520,0,32,-7864.11,-1135.98,203.29,0,0,0,''),
(9520,0,33,-7837.31,-1137.73,209.63,0,0,0,''),
(9520,0,34,-7808.72,-1134.9,214.84,0,0,0,''),
(9520,0,35,-7786.85,-1127.24,214.84,0,0,0,''),
(9520,0,36,-7746.58,-1125.16,215.08,0,5000,0,'EMOTE_LAUGH'),
(9520,0,37,-7746.41,-1103.62,215.62,0,0,0,''),
(9520,0,38,-7740.25,-1090.51,216.69,0,0,0,''),
(9520,0,39,-7730.97,-1085.55,217.12,0,0,0,''),
(9520,0,40,-7697.89,-1089.43,217.62,0,0,0,''),
(9520,0,41,-7679.3,-1059.15,220.09,0,0,0,''),
(9520,0,42,-7661.39,-1038.24,226.24,0,0,0,''),
(9520,0,43,-7634.49,-1020.96,234.3,0,0,0,''),
(9520,0,44,-7596.22,-1013.16,244.03,0,0,0,''),
(9520,0,45,-7556.53,-1021.74,253.21,0,0,0,'SAY_LAST_STAND'),
(9537,0,0,854.977,-150.308,-49.671,0,0,0,''),
(9537,0,1,855.816,-149.763,-49.671,0,0,0,'YELL_HURLEY_SPAWN'),
(9537,0,2,882.63,-148.166,-49.7597,0,0,0,''),
(9537,0,3,883.96,-148.087,-49.76,0,0,0,''),
(9537,0,4,896.846,-147.319,-49.7575,0,0,0,''),
(9537,0,5,896.846,-147.319,-49.7575,0,0,0,''),
(9598,0,0,6004.27,-1180.49,376.377,0,0,0,'SAY_ESCORT_START'),
(9598,0,1,6002.51,-1157.29,381.407,0,0,0,''),
(9598,0,2,6029.23,-1139.72,383.127,0,0,0,''),
(9598,0,3,6042.48,-1128.96,386.582,0,0,0,''),
(9598,0,4,6062.82,-1115.52,386.85,0,0,0,''),
(9598,0,5,6089.19,-1111.91,383.105,0,0,0,''),
(9598,0,6,6104.39,-1114.56,380.49,0,0,0,''),
(9598,0,7,6115.08,-1128.57,375.779,0,0,0,''),
(9598,0,8,6119.35,-1147.31,372.518,0,0,0,''),
(9598,0,9,6119,-1176.08,371.072,0,0,0,''),
(9598,0,10,6120.98,-1198.41,373.432,0,0,0,''),
(9598,0,11,6123.52,-1226.64,374.119,0,0,0,''),
(9598,0,12,6127.74,-1246.04,373.574,0,0,0,''),
(9598,0,13,6133.43,-1253.64,369.1,0,0,0,''),
(9598,0,14,6150.79,-1269.15,369.24,0,0,0,''),
(9598,0,15,6155.81,-1275.03,373.627,0,0,0,''),
(9598,0,16,6163.54,-1307.13,376.234,0,0,0,''),
(9598,0,17,6174.8,-1340.89,379.039,0,0,0,''),
(9598,0,18,6191.14,-1371.26,378.453,0,0,0,''),
(9598,0,19,6215.65,-1397.52,376.012,0,0,0,''),
(9598,0,20,6243.78,-1407.68,371.594,0,0,0,''),
(9598,0,21,6280.77,-1408.26,370.554,0,0,0,''),
(9598,0,22,6325.36,-1406.69,370.082,0,0,0,''),
(9598,0,23,6355,-1404.34,370.646,0,0,0,''),
(9598,0,24,6374.68,-1399.18,372.105,0,0,0,''),
(9598,0,25,6395.8,-1367.06,374.91,0,0,0,''),
(9598,0,26,6408.57,-1333.49,376.616,0,0,0,''),
(9598,0,27,6409.08,-1312.17,379.598,0,0,0,''),
(9598,0,28,6418.69,-1277.7,381.638,0,0,0,''),
(9598,0,29,6441.69,-1247.32,387.246,0,0,0,''),
(9598,0,30,6462.14,-1226.32,397.61,0,0,0,''),
(9598,0,31,6478.02,-1216.26,408.284,0,0,0,''),
(9598,0,32,6499.63,-1217.09,419.461,0,0,0,''),
(9598,0,33,6523.17,-1220.78,430.549,0,0,0,''),
(9598,0,34,6542.72,-1217,437.788,0,0,0,''),
(9598,0,35,6557.28,-1211.12,441.452,0,0,0,''),
(9598,0,36,6574.57,-1204.59,443.216,0,0,0,'SAY_EXIT_IRONTREE'),
(9623,0,0,-6383.07,-1964.37,-258.709,0,0,0,'SAY_AME_START'),
(9623,0,1,-6393.65,-1949.57,-261.449,0,0,0,''),
(9623,0,2,-6397.85,-1931.1,-263.366,0,0,0,''),
(9623,0,3,-6397.5,-1921.47,-263.876,0,0,0,''),
(9623,0,4,-6389.63,-1910,-259.601,0,0,0,''),
(9623,0,5,-6380.07,-1905.45,-255.858,0,0,0,''),
(9623,0,6,-6373.44,-1900.28,-254.774,0,0,0,''),
(9623,0,7,-6372.87,-1893.5,-255.678,0,0,0,''),
(9623,0,8,-6379.73,-1877.63,-259.654,0,0,0,''),
(9623,0,9,-6380.26,-1871.14,-260.617,0,0,0,''),
(9623,0,10,-6373.83,-1855.62,-259.566,0,0,0,''),
(9623,0,11,-6368.82,-1847.77,-259.246,0,0,0,''),
(9623,0,12,-6370.9,-1835.04,-260.212,0,0,0,''),
(9623,0,13,-6376.59,-1821.59,-260.856,0,0,0,''),
(9623,0,14,-6381.93,-1810.43,-266.18,0,0,0,''),
(9623,0,15,-6396.71,-1807.12,-269.329,0,0,0,''),
(9623,0,16,-6400.27,-1795.05,-269.744,0,0,0,''),
(9623,0,17,-6402.68,-1747.51,-272.961,0,0,0,''),
(9623,0,18,-6397,-1710.05,-273.719,0,0,0,''),
(9623,0,19,-6388.11,-1676.33,-272.133,0,5000,0,'SAY_AME_PROGRESS'),
(9623,0,20,-6370.71,-1638.64,-272.031,0,0,0,''),
(9623,0,21,-6366.71,-1592.65,-272.201,0,0,0,''),
(9623,0,22,-6333.87,-1534.6,-270.493,0,0,0,''),
(9623,0,23,-6305.36,-1477.91,-269.518,0,0,0,''),
(9623,0,24,-6311.59,-1419.02,-267.622,0,0,0,''),
(9623,0,25,-6330.01,-1400.06,-266.425,0,0,0,''),
(9623,0,26,-6356.02,-1392.61,-267.123,0,0,0,''),
(9623,0,27,-6370.86,-1386.18,-270.218,0,0,0,''),
(9623,0,28,-6381.53,-1369.78,-272.11,0,0,0,''),
(9623,0,29,-6405.38,-1321.52,-271.699,0,0,0,''),
(9623,0,30,-6406.58,-1307.57,-271.802,0,0,0,''),
(9623,0,31,-6386.33,-1286.85,-272.074,0,0,0,''),
(9623,0,32,-6364.25,-1264.71,-269.075,0,0,0,''),
(9623,0,33,-6343.64,-1239.84,-268.364,0,0,0,''),
(9623,0,34,-6335.57,-1202.45,-271.515,0,0,0,''),
(9623,0,35,-6325.62,-1184.46,-270.461,0,0,0,''),
(9623,0,36,-6317.8,-1177.67,-269.792,0,0,0,''),
(9623,0,37,-6303.02,-1180.25,-269.332,0,0,0,'SAY_AME_END'),
(9623,0,38,-6301.98,-1184.79,-269.371,0,1000,0,''),
(9623,0,39,-6297.58,-1186.41,-268.962,0,5000,0,''),
(10096,0,0,604.803,-191.082,-54.0586,0,0,0,'ring'),
(10096,0,1,604.073,-222.107,-52.7438,0,0,0,'first gate'),
(10096,0,2,621.4,-214.499,-52.8145,0,0,0,'hiding in corner'),
(10096,0,3,601.301,-198.557,-53.9503,0,0,0,'ring'),
(10096,0,4,631.818,-180.548,-52.6548,0,0,0,'second gate'),
(10096,0,5,627.39,-201.076,-52.6929,0,0,0,'hiding in corner'),
(10300,0,1,5728.81,-4801.15,778.18,0,0,0,''),
(10300,0,2,5730.22,-4818.34,777.11,0,0,0,''),
(10300,0,3,5728.12,-4835.76,778.15,0,1000,0,'SAY_ENTER_OWL_THICKET'),
(10300,0,4,5718.85,-4865.62,787.56,0,0,0,''),
(10300,0,5,5697.13,-4909.12,801.53,0,0,0,''),
(10300,0,6,5684.2,-4913.75,801.6,0,0,0,''),
(10300,0,7,5674.67,-4915.78,802.13,0,0,0,''),
(10300,0,8,5665.61,-4919.22,804.85,0,0,0,''),
(10300,0,9,5638.22,-4897.58,804.97,0,0,0,''),
(10300,0,10,5632.67,-4892.05,805.44,0,0,0,'Cavern 1 - EMOTE_CHANT_SPELL'),
(10300,0,11,5664.58,-4921.84,804.91,0,0,0,''),
(10300,0,12,5684.21,-4943.81,802.8,0,0,0,''),
(10300,0,13,5724.92,-4983.69,808.25,0,0,0,''),
(10300,0,14,5753.39,-4990.73,809.84,0,0,0,''),
(10300,0,15,5765.62,-4994.89,809.42,0,0,0,'Cavern 2 - EMOTE_CHANT_SPELL'),
(10300,0,16,5724.94,-4983.58,808.29,0,0,0,''),
(10300,0,17,5699.61,-4989.82,808.03,0,0,0,''),
(10300,0,18,5686.8,-5012.17,807.27,0,0,0,''),
(10300,0,19,5691.43,-5037.43,807.73,0,0,0,''),
(10300,0,20,5694.24,-5054.64,808.85,0,0,0,'Cavern 3 - EMOTE_CHANT_SPELL'),
(10300,0,21,5686.88,-5012.18,807.23,0,0,0,''),
(10300,0,22,5664.94,-5001.12,807.78,0,0,0,''),
(10300,0,23,5647.12,-5002.84,807.54,0,0,0,''),
(10300,0,24,5629.23,-5014.88,807.94,0,0,0,''),
(10300,0,25,5611.26,-5025.62,808.36,0,0,0,'Cavern 4 - EMOTE_CHANT_SPELL'),
(10300,0,26,5647.13,-5002.85,807.57,0,0,0,''),
(10300,0,27,5641.12,-4973.22,809.39,0,0,0,''),
(10300,0,28,5622.97,-4953.58,811.12,0,0,0,''),
(10300,0,29,5601.52,-4939.49,820.77,0,0,0,''),
(10300,0,30,5571.87,-4936.22,831.35,0,0,0,''),
(10300,0,31,5543.23,-4933.67,838.33,0,0,0,''),
(10300,0,32,5520.86,-4942.05,843.02,0,0,0,''),
(10300,0,33,5509.15,-4946.31,849.36,0,0,0,''),
(10300,0,34,5498.45,-4950.08,849.98,0,0,0,''),
(10300,0,35,5485.78,-4963.4,850.43,0,0,0,''),
(10300,0,36,5467.92,-4980.67,851.89,0,0,0,'Cavern 5 - EMOTE_CHANT_SPELL'),
(10300,0,37,5498.68,-4950.45,849.96,0,0,0,''),
(10300,0,38,5518.68,-4921.94,844.65,0,0,0,''),
(10300,0,39,5517.66,-4920.82,845.12,0,0,0,'SAY_REACH_ALTAR_1'),
(10300,0,40,5518.38,-4913.47,845.57,0,0,0,''),
(10300,0,41,5511.31,-4913.82,847.17,0,5000,0,'light the spotlights'),
(10300,0,42,5511.31,-4913.82,847.17,0,0,0,'start altar cinematic - SAY_RANSHALLA_ALTAR_2'),
(10300,0,43,5510.36,-4921.17,846.33,0,0,0,''),
(10300,0,44,5517.66,-4920.82,845.12,0,0,0,'escort paused'),
(10427,0,0,-5185.46,-1185.93,45.951,0,0,0,''),
(10427,0,1,-5184.88,-1154.21,45.035,0,0,0,''),
(10427,0,2,-5175.88,-1126.53,43.701,0,0,0,''),
(10427,0,3,-5138.65,-1111.87,44.024,0,0,0,''),
(10427,0,4,-5134.73,-1104.8,47.365,0,0,0,''),
(10427,0,5,-5129.68,-1097.88,49.449,0,2500,0,''),
(10427,0,6,-5125.3,-1080.57,47.033,0,0,0,''),
(10427,0,7,-5146.67,-1053.69,28.415,0,0,0,''),
(10427,0,8,-5147.46,-1027.54,13.818,0,0,0,''),
(10427,0,9,-5139.24,-1018.89,8.22,0,0,0,''),
(10427,0,10,-5121.17,-1013.13,-0.619,0,0,0,''),
(10427,0,11,-5091.92,-1014.21,-4.902,0,0,0,''),
(10427,0,12,-5069.24,-994.299,-4.631,0,0,0,''),
(10427,0,13,-5059.98,-944.112,-5.377,0,0,0,''),
(10427,0,14,-5013.55,-906.184,-5.49,0,0,0,''),
(10427,0,15,-4992.46,-920.983,-4.98,0,5000,0,'SAY_WYVERN'),
(10427,0,16,-4976.35,-1003,-5.38,0,0,0,''),
(10427,0,17,-4958.48,-1033.19,-5.433,0,0,0,''),
(10427,0,18,-4953.35,-1052.21,-10.836,0,0,0,''),
(10427,0,19,-4937.45,-1056.35,-22.139,0,0,0,''),
(10427,0,20,-4908.46,-1050.43,-33.458,0,0,0,''),
(10427,0,21,-4905.53,-1056.89,-33.722,0,0,0,''),
(10427,0,22,-4920.83,-1073.28,-45.515,0,0,0,''),
(10427,0,23,-4933.37,-1082.7,-50.186,0,0,0,''),
(10427,0,24,-4935.31,-1092.35,-52.785,0,0,0,''),
(10427,0,25,-4929.55,-1101.27,-50.637,0,0,0,''),
(10427,0,26,-4920.68,-1100.03,-51.944,0,10000,0,'SAY_COMPLETE'),
(10427,0,27,-4920.68,-1100.03,-51.944,0,0,0,'quest complete'),
(10638,0,0,-4903.52,-1368.34,-52.611,0,5000,0,'SAY_KAN_START'),
(10638,0,1,-4906,-1367.05,-52.611,0,0,0,''),
(10646,0,0,-4792.4,-2137.78,82.423,0,0,0,''),
(10646,0,1,-4813.51,-2141.54,80.774,0,0,0,''),
(10646,0,2,-4828.63,-2154.31,82.074,0,0,0,''),
(10646,0,3,-4833.77,-2149.18,81.676,0,0,0,''),
(10646,0,4,-4846.42,-2136.05,77.871,0,0,0,''),
(10646,0,5,-4865.08,-2116.55,76.483,0,0,0,''),
(10646,0,6,-4888.43,-2090.73,80.907,0,0,0,''),
(10646,0,7,-4893.07,-2085.47,82.094,0,0,0,''),
(10646,0,8,-4907.26,-2074.93,84.437,0,5000,0,'SAY_LAKO_LOOK_OUT'),
(10646,0,9,-4899.9,-2062.14,83.78,0,0,0,''),
(10646,0,10,-4897.76,-2056.52,84.184,0,0,0,''),
(10646,0,11,-4888.33,-2033.18,83.654,0,0,0,''),
(10646,0,12,-4876.34,-2003.92,90.887,0,0,0,''),
(10646,0,13,-4872.23,-1994.17,91.513,0,0,0,''),
(10646,0,14,-4879.57,-1976.99,92.185,0,5000,0,'SAY_LAKO_HERE_COME'),
(10646,0,15,-4879.05,-1964.35,92.001,0,0,0,''),
(10646,0,16,-4874.72,-1956.94,90.737,0,0,0,''),
(10646,0,17,-4869.47,-1952.61,89.206,0,0,0,''),
(10646,0,18,-4842.47,-1929,84.147,0,0,0,''),
(10646,0,19,-4804.44,-1897.3,89.362,0,0,0,''),
(10646,0,20,-4798.07,-1892.38,89.368,0,0,0,''),
(10646,0,21,-4779.45,-1882.76,90.169,0,5000,0,'SAY_LAKO_MORE'),
(10646,0,22,-4762.08,-1866.53,89.481,0,0,0,''),
(10646,0,23,-4766.27,-1861.87,87.847,0,0,0,''),
(10646,0,24,-4782.93,-1852.17,78.354,0,0,0,''),
(10646,0,25,-4793.61,-1850.96,77.658,0,0,0,''),
(10646,0,26,-4803.32,-1855.1,78.958,0,0,0,''),
(10646,0,27,-4807.97,-1854.5,77.743,0,0,0,''),
(10646,0,28,-4837.21,-1848.49,64.488,0,0,0,''),
(10646,0,29,-4884.62,-1840.4,56.219,0,0,0,''),
(10646,0,30,-4889.71,-1839.62,54.417,0,0,0,''),
(10646,0,31,-4893.9,-1843.69,53.012,0,0,0,''),
(10646,0,32,-4903.14,-1872.38,32.266,0,0,0,''),
(10646,0,33,-4910.94,-1879.86,29.94,0,0,0,''),
(10646,0,34,-4920.05,-1880.94,30.597,0,0,0,''),
(10646,0,35,-4924.46,-1881.45,29.292,0,0,0,''),
(10646,0,36,-4966.12,-1886.03,10.977,0,0,0,''),
(10646,0,37,-4999.37,-1890.85,4.43,0,0,0,''),
(10646,0,38,-5007.27,-1891.67,2.771,0,0,0,''),
(10646,0,39,-5013.33,-1879.59,-1.947,0,0,0,''),
(10646,0,40,-5023.33,-1855.96,-17.103,0,0,0,''),
(10646,0,41,-5038.51,-1825.99,-35.821,0,0,0,''),
(10646,0,42,-5048.73,-1809.8,-46.457,0,0,0,''),
(10646,0,43,-5053.19,-1791.68,-57.186,0,0,0,''),
(10646,0,44,-5062.09,-1794.4,-56.515,0,0,0,''),
(10646,0,45,-5052.66,-1797.04,-54.734,0,5000,0,'SAY_LAKO_END'),
(11016,0,0,5004.98,-440.237,319.059,0,4000,0,'SAY_ESCORT_START'),
(11016,0,1,4992.22,-449.964,317.057,0,0,0,''),
(11016,0,2,4988.55,-457.438,316.289,0,0,0,''),
(11016,0,3,4989.98,-464.297,316.846,0,0,0,''),
(11016,0,4,4994.04,-467.754,318.055,0,0,0,''),
(11016,0,5,5002.31,-466.318,319.965,0,0,0,''),
(11016,0,6,5011.8,-462.889,321.501,0,0,0,''),
(11016,0,7,5020.53,-460.797,321.97,0,0,0,''),
(11016,0,8,5026.84,-463.171,321.345,0,0,0,''),
(11016,0,9,5028.66,-476.805,318.726,0,0,0,''),
(11016,0,10,5029.5,-487.131,318.179,0,0,0,''),
(11016,0,11,5031.18,-497.678,316.533,0,0,0,''),
(11016,0,12,5032.72,-504.748,314.744,0,0,0,''),
(11016,0,13,5035,-513.138,314.372,0,0,0,''),
(11016,0,14,5037.49,-521.733,313.221,0,6000,0,'SAY_FIRST_STOP'),
(11016,0,15,5049.06,-519.546,313.221,0,0,0,''),
(11016,0,16,5059.17,-522.93,313.221,0,0,0,''),
(11016,0,17,5062.75,-529.933,313.221,0,0,0,''),
(11016,0,18,5063.9,-538.827,313.221,0,0,0,''),
(11016,0,19,5062.22,-545.635,313.221,0,0,0,''),
(11016,0,20,5061.69,-552.333,313.101,0,0,0,''),
(11016,0,21,5060.33,-560.349,310.873,0,0,0,''),
(11016,0,22,5055.62,-565.541,308.737,0,0,0,''),
(11016,0,23,5049.8,-567.604,306.537,0,0,0,''),
(11016,0,24,5043.01,-564.946,303.682,0,0,0,''),
(11016,0,25,5038.22,-559.823,301.463,0,0,0,''),
(11016,0,26,5039.46,-548.675,297.824,0,0,0,''),
(11016,0,27,5043.44,-538.807,297.801,0,0,0,''),
(11016,0,28,5056.4,-528.954,297.801,0,0,0,''),
(11016,0,29,5064.4,-521.904,297.801,0,0,0,''),
(11016,0,30,5067.62,-512.999,297.196,0,0,0,''),
(11016,0,31,5065.99,-505.329,297.214,0,0,0,''),
(11016,0,32,5062.24,-499.086,297.448,0,0,0,''),
(11016,0,33,5065.09,-492.069,298.054,0,0,0,''),
(11016,0,34,5071.19,-491.173,297.666,0,5000,0,'SAY_SECOND_STOP'),
(11016,0,35,5087.47,-496.478,296.677,0,0,0,''),
(11016,0,36,5095.55,-508.639,296.677,0,0,0,''),
(11016,0,37,5104.3,-521.014,296.677,0,0,0,''),
(11016,0,38,5110.13,-532.123,296.677,0,4000,0,'open equipment chest'),
(11016,0,39,5110.13,-532.123,296.677,0,4000,0,'cast SPELL_STRENGHT_ARKONARIN'),
(11016,0,40,5110.13,-532.123,296.677,0,4000,0,'SAY_EQUIPMENT'),
(11016,0,41,5110.13,-532.123,296.677,0,0,0,'SAY_ESCAPE'),
(11016,0,42,5099.75,-510.823,296.677,0,0,0,''),
(11016,0,43,5091.94,-497.516,296.677,0,0,0,''),
(11016,0,44,5079.38,-486.811,297.638,0,0,0,''),
(11016,0,45,5069.21,-488.77,298.082,0,0,0,''),
(11016,0,46,5064.24,-496.051,297.275,0,0,0,''),
(11016,0,47,5065.08,-505.239,297.361,0,0,0,''),
(11016,0,48,5067.82,-515.245,297.125,0,0,0,''),
(11016,0,49,5064.62,-521.17,297.801,0,0,0,''),
(11016,0,50,5053.22,-530.739,297.801,0,0,0,''),
(11016,0,51,5045.73,-538.311,297.801,0,0,0,''),
(11016,0,52,5039.69,-548.112,297.801,0,0,0,''),
(11016,0,53,5038.78,-557.588,300.787,0,0,0,''),
(11016,0,54,5042.01,-566.749,303.838,0,0,0,''),
(11016,0,55,5050.56,-568.149,306.782,0,0,0,''),
(11016,0,56,5056.98,-564.674,309.342,0,0,0,''),
(11016,0,57,5060.79,-556.801,311.936,0,0,0,''),
(11016,0,58,5059.58,-551.626,313.221,0,0,0,''),
(11016,0,59,5062.83,-541.994,313.221,0,0,0,''),
(11016,0,60,5063.55,-531.288,313.221,0,0,0,''),
(11016,0,61,5057.93,-523.088,313.221,0,0,0,''),
(11016,0,62,5049.47,-519.36,313.221,0,0,0,''),
(11016,0,63,5040.79,-519.809,313.221,0,0,0,''),
(11016,0,64,5034.3,-515.361,313.948,0,0,0,''),
(11016,0,65,5032,-505.532,314.663,0,0,0,''),
(11016,0,66,5029.92,-495.645,316.821,0,0,0,''),
(11016,0,67,5028.87,-487,318.179,0,0,0,''),
(11016,0,68,5028.11,-475.531,318.839,0,0,0,''),
(11016,0,69,5027.76,-465.442,320.643,0,0,0,''),
(11016,0,70,5019.96,-460.892,321.969,0,0,0,''),
(11016,0,71,5009.43,-464.793,321.248,0,0,0,''),
(11016,0,72,4999.57,-468.062,319.426,0,0,0,''),
(11016,0,73,4992.03,-468.128,317.894,0,0,0,''),
(11016,0,74,4988.17,-461.293,316.369,0,0,0,''),
(11016,0,75,4990.62,-447.459,317.104,0,0,0,''),
(11016,0,76,4993.48,-438.643,318.272,0,0,0,''),
(11016,0,77,4995.45,-430.178,318.462,0,0,0,''),
(11016,0,78,4993.56,-422.876,318.864,0,0,0,''),
(11016,0,79,4985.4,-420.864,320.205,0,0,0,''),
(11016,0,80,4976.52,-426.168,323.112,0,0,0,''),
(11016,0,81,4969.83,-429.755,325.029,0,0,0,''),
(11016,0,82,4960.7,-425.44,325.834,0,0,0,''),
(11016,0,83,4955.45,-418.765,327.433,0,0,0,''),
(11016,0,84,4949.7,-408.796,328.004,0,0,0,''),
(11016,0,85,4940.02,-403.222,329.956,0,0,0,''),
(11016,0,86,4934.98,-401.475,330.898,0,0,0,''),
(11016,0,87,4928.69,-399.302,331.744,0,0,0,''),
(11016,0,88,4926.94,-398.436,333.079,0,0,0,''),
(11016,0,89,4916.16,-393.822,333.729,0,0,0,''),
(11016,0,90,4908.39,-396.217,333.217,0,0,0,''),
(11016,0,91,4905.61,-396.535,335.05,0,0,0,''),
(11016,0,92,4897.88,-395.245,337.346,0,0,0,''),
(11016,0,93,4895.21,-388.203,339.295,0,0,0,''),
(11016,0,94,4896.94,-382.429,341.04,0,0,0,''),
(11016,0,95,4901.88,-378.799,342.771,0,0,0,''),
(11016,0,96,4908.09,-380.635,344.597,0,0,0,''),
(11016,0,97,4911.91,-385.818,346.491,0,0,0,''),
(11016,0,98,4910.1,-393.444,348.798,0,0,0,''),
(11016,0,99,4903.5,-396.947,350.812,0,0,0,''),
(11016,0,100,4898.08,-394.226,351.821,0,0,0,''),
(11016,0,101,4891.33,-393.436,351.801,0,0,0,''),
(11016,0,102,4881.2,-395.211,351.59,0,0,0,''),
(11016,0,103,4877.84,-395.536,349.713,0,0,0,''),
(11016,0,104,4873.97,-394.919,349.844,0,5000,0,'SAY_FRESH_AIR'),
(11016,0,105,4873.97,-394.919,349.844,0,3000,0,'SAY_BETRAYER'),
(11016,0,106,4873.97,-394.919,349.844,0,2000,0,'SAY_TREY'),
(11016,0,107,4873.97,-394.919,349.844,0,0,0,'SAY_ATTACK_TREY'),
(11016,0,108,4873.97,-394.919,349.844,0,5000,0,'SAY_ESCORT_COMPLETE'),
(11016,0,109,4873.97,-394.919,349.844,0,1000,0,''),
(11016,0,110,4863.02,-394.521,350.65,0,0,0,''),
(11016,0,111,4848.7,-397.612,351.215,0,0,0,''),
(11832,0,0,7848.39,-2216.36,470.888,0,15000,0,'SAY_REMULOS_INTRO_1'),
(11832,0,1,7848.39,-2216.36,470.888,0,5000,0,'SAY_REMULOS_INTRO_2'),
(11832,0,2,7829.79,-2244.84,463.853,0,0,0,''),
(11832,0,3,7819.01,-2304.34,455.957,0,0,0,''),
(11832,0,4,7931.1,-2314.35,473.054,0,0,0,''),
(11832,0,5,7943.55,-2324.69,477.677,0,0,0,''),
(11832,0,6,7952.02,-2351.14,485.235,0,0,0,''),
(11832,0,7,7963.67,-2412.99,488.953,0,0,0,''),
(11832,0,8,7975.18,-2551.6,490.08,0,0,0,''),
(11832,0,9,7948.05,-2570.83,489.751,0,0,0,''),
(11832,0,10,7947.16,-2583.4,490.066,0,0,0,''),
(11832,0,11,7951.09,-2596.22,489.831,0,0,0,''),
(11832,0,12,7948.27,-2610.06,492.34,0,0,0,''),
(11832,0,13,7928.52,-2625.95,492.448,0,0,0,'escort paused - SAY_REMULOS_INTRO_3'),
(11832,0,14,7948.27,-2610.06,492.34,0,0,0,''),
(11832,0,15,7952.32,-2594.12,490.07,0,0,0,''),
(11832,0,16,7913.99,-2567,488.331,0,0,0,''),
(11832,0,17,7835.45,-2571.1,489.289,0,0,0,'escort paused - SAY_REMULOS_DEFEND_2'),
(11832,0,18,7897.28,-2560.65,487.461,0,0,0,'escort paused'),
(11856,0,0,113.91,-350.13,4.55,0,0,0,''),
(11856,0,1,109.54,-350.08,3.74,0,0,0,''),
(11856,0,2,106.95,-353.4,3.6,0,0,0,''),
(11856,0,3,100.28,-338.89,2.97,0,0,0,''),
(11856,0,4,110.11,-320.26,3.47,0,0,0,''),
(11856,0,5,109.78,-287.8,5.3,0,0,0,''),
(11856,0,6,105.02,-269.71,4.71,0,0,0,''),
(11856,0,7,86.71,-251.81,5.34,0,0,0,''),
(11856,0,8,64.1,-246.38,5.91,0,0,0,''),
(11856,0,9,-2.55,-243.58,6.3,0,0,0,''),
(11856,0,10,-27.78,-267.53,-1.08,0,0,0,''),
(11856,0,11,-31.27,-283.54,-4.36,0,0,0,''),
(11856,0,12,-28.96,-322.44,-9.19,0,0,0,''),
(11856,0,13,-35.63,-360.03,-16.59,0,0,0,''),
(11856,0,14,-58.3,-412.26,-30.6,0,0,0,''),
(11856,0,15,-58.88,-474.17,-44.54,0,0,0,''),
(11856,0,16,-45.92,-496.57,-46.26,0,5000,0,'AMBUSH'),
(11856,0,17,-40.25,-510.07,-46.05,0,0,0,''),
(11856,0,18,-38.88,-520.72,-46.06,0,5000,0,'END'),
(12126,0,0,2631.23,-1917.93,72.59,0,0,0,''),
(12126,0,1,2643.53,-1914.07,71,0,0,0,''),
(12126,0,2,2653.83,-1907.54,69.34,0,0,0,'escort paused'),
(12277,0,1,-1154.87,2708.16,111.123,0,1000,0,'SAY_MELIZZA_START'),
(12277,0,2,-1162.62,2712.86,111.549,0,0,0,''),
(12277,0,3,-1183.37,2709.45,111.601,0,0,0,''),
(12277,0,4,-1245.09,2676.43,111.572,0,0,0,''),
(12277,0,5,-1260.54,2672.48,111.55,0,0,0,''),
(12277,0,6,-1272.71,2666.38,111.555,0,0,0,''),
(12277,0,7,-1342.95,2580.82,111.557,0,0,0,''),
(12277,0,8,-1362.24,2561.74,110.848,0,0,0,''),
(12277,0,9,-1376.56,2514.06,95.6146,0,0,0,''),
(12277,0,10,-1379.06,2510.88,93.3256,0,0,0,''),
(12277,0,11,-1383.14,2489.17,89.009,0,0,0,''),
(12277,0,12,-1395.34,2426.15,88.6607,0,0,0,'SAY_MELIZZA_FINISH'),
(12277,0,13,-1366.23,2317.17,91.8086,0,0,0,''),
(12277,0,14,-1353.81,2213.52,90.726,0,0,0,''),
(12277,0,15,-1354.19,2208.28,88.7386,0,0,0,''),
(12277,0,16,-1354.59,2193.77,77.6702,0,0,0,''),
(12277,0,17,-1367.62,2160.64,67.1482,0,0,0,''),
(12277,0,18,-1379.44,2132.77,64.1326,0,0,0,''),
(12277,0,19,-1404.81,2088.68,61.8162,0,0,0,'SAY_MELIZZA_1'),
(12277,0,20,-1417.15,2082.65,62.4112,0,0,0,''),
(12277,0,21,-1423.28,2074.19,62.2046,0,0,0,''),
(12277,0,22,-1432.99,2070.56,61.7811,0,0,0,''),
(12277,0,23,-1469.27,2078.68,63.1141,0,0,0,''),
(12277,0,24,-1507.21,2115.12,62.3578,0,0,0,''),
(12423,0,0,-9509.72,-147.03,58.74,0,0,0,''),
(12423,0,1,-9517.07,-172.82,58.66,0,0,0,''),
(12427,0,0,-5689.2,-456.44,391.08,0,0,0,''),
(12427,0,1,-5700.37,-450.77,393.19,0,0,0,''),
(12428,0,0,2454.09,361.26,31.51,0,0,0,''),
(12428,0,1,2472.03,378.08,30.98,0,0,0,''),
(12429,0,0,9654.19,909.58,1272.11,0,0,0,''),
(12429,0,1,9642.53,908.11,1269.1,0,0,0,''),
(12430,0,0,161.65,-4779.34,14.64,0,0,0,''),
(12430,0,1,140.71,-4813.56,17.04,0,0,0,''),
(12580,0,0,-8997.63,486.402,96.622,0,0,0,''),
(12580,0,1,-8971.08,507.541,96.349,0,0,0,'SAY_DIALOG_1'),
(12580,0,2,-8953.17,518.537,96.355,0,0,0,''),
(12580,0,3,-8936.33,501.777,94.066,0,0,0,''),
(12580,0,4,-8922.52,498.45,93.869,0,0,0,''),
(12580,0,5,-8907.64,509.941,93.84,0,0,0,''),
(12580,0,6,-8925.26,542.51,94.274,0,0,0,''),
(12580,0,7,-8832.28,622.285,93.686,0,0,0,''),
(12580,0,8,-8824.8,621.713,94.084,0,0,0,''),
(12580,0,9,-8796.46,590.922,97.466,0,0,0,''),
(12580,0,10,-8769.85,607.883,97.118,0,0,0,''),
(12580,0,11,-8737.14,574.741,97.398,0,0,0,'reset jonathan'),
(12580,0,12,-8746.27,563.446,97.399,0,0,0,''),
(12580,0,13,-8745.5,557.877,97.704,0,0,0,''),
(12580,0,14,-8730.95,541.477,101.12,0,0,0,''),
(12580,0,15,-8713.16,520.692,97.227,0,0,0,''),
(12580,0,16,-8677.09,549.614,97.438,0,0,0,''),
(12580,0,17,-8655.72,552.732,96.941,0,0,0,''),
(12580,0,18,-8641.68,540.516,98.972,0,0,0,''),
(12580,0,19,-8620.08,520.12,102.812,0,0,0,''),
(12580,0,20,-8591.09,492.553,104.032,0,0,0,''),
(12580,0,21,-8562.45,463.583,104.517,0,0,0,''),
(12580,0,22,-8548.63,467.38,104.517,0,0,0,'SAY_WINDSOR_BEFORE_KEEP'),
(12580,0,23,-8487.77,391.44,108.386,0,0,0,''),
(12580,0,24,-8455.95,351.225,120.88,0,0,0,''),
(12580,0,25,-8446.87,339.904,121.33,0,0,0,'SAY_WINDSOR_KEEP_1'),
(12580,0,26,-8446.87,339.904,121.33,0,10000,0,''),
(12717,0,0,3346.25,1007.88,3.59,0,0,0,'SAY_MUG_START2'),
(12717,0,1,3367.39,1011.51,3.72,0,0,0,''),
(12717,0,2,3418.64,1013.96,2.905,0,0,0,''),
(12717,0,3,3426.84,1015.1,3.449,0,0,0,''),
(12717,0,4,3437.03,1020.79,2.742,0,0,0,''),
(12717,0,5,3460.56,1024.26,1.353,0,0,0,''),
(12717,0,6,3479.87,1037.96,1.023,0,0,0,''),
(12717,0,7,3490.53,1043.35,3.338,0,0,0,''),
(12717,0,8,3504.28,1047.77,8.205,0,0,0,''),
(12717,0,9,3510.73,1049.79,12.143,0,0,0,''),
(12717,0,10,3514.41,1051.17,13.235,0,0,0,''),
(12717,0,11,3516.94,1052.91,12.918,0,0,0,''),
(12717,0,12,3523.64,1056.3,7.563,0,0,0,''),
(12717,0,13,3531.94,1059.86,6.175,0,0,0,''),
(12717,0,14,3535.48,1069.96,1.697,0,0,0,''),
(12717,0,15,3546.98,1093.49,0.68,0,0,0,''),
(12717,0,16,3549.73,1101.88,-1.123,0,0,0,''),
(12717,0,17,3555.14,1116.99,-4.326,0,0,0,''),
(12717,0,18,3571.94,1132.18,-0.634,0,0,0,''),
(12717,0,19,3574.28,1137.58,3.684,0,0,0,''),
(12717,0,20,3579.31,1137.25,8.205,0,0,0,''),
(12717,0,21,3590.22,1143.65,8.291,0,0,0,''),
(12717,0,22,3595.97,1145.83,6.773,0,0,0,''),
(12717,0,23,3603.65,1146.92,9.763,0,0,0,''),
(12717,0,24,3607.08,1146.01,10.692,0,5000,0,'SAY_MUG_BRAZIER'),
(12717,0,25,3614.52,1142.63,10.248,0,0,0,''),
(12717,0,26,3616.66,1140.84,10.682,0,3000,0,'SAY_MUG_PATROL'),
(12717,0,27,3621.08,1138.11,10.369,0,0,0,'SAY_MUG_RETURN'),
(12717,0,28,3615.48,1145.53,9.614,0,0,0,''),
(12717,0,29,3607.19,1152.72,8.871,0,0,0,''),
(12818,0,0,3347.25,-694.701,159.926,0,0,0,''),
(12818,0,1,3341.53,-694.726,161.125,0,4000,0,''),
(12818,0,2,3338.35,-686.088,163.444,0,0,0,''),
(12818,0,3,3352.74,-677.722,162.316,0,0,0,''),
(12818,0,4,3370.29,-669.367,160.751,0,0,0,''),
(12818,0,5,3381.48,-659.449,162.545,0,0,0,''),
(12818,0,6,3389.55,-648.5,163.652,0,0,0,''),
(12818,0,7,3396.65,-641.509,164.216,0,0,0,''),
(12818,0,8,3410.5,-634.3,165.773,0,0,0,''),
(12818,0,9,3418.46,-631.792,166.478,0,0,0,''),
(12818,0,10,3429.5,-631.589,166.921,0,0,0,''),
(12818,0,11,3434.95,-629.245,168.334,0,0,0,''),
(12818,0,12,3438.93,-618.503,171.503,0,0,0,''),
(12818,0,13,3444.22,-609.294,173.078,0,1000,0,'Ambush 1'),
(12818,0,14,3460.51,-593.794,174.342,0,0,0,''),
(12818,0,15,3480.28,-578.21,176.652,0,0,0,''),
(12818,0,16,3492.91,-562.335,181.396,0,0,0,''),
(12818,0,17,3495.23,-550.978,184.652,0,0,0,''),
(12818,0,18,3496.25,-529.194,188.172,0,0,0,''),
(12818,0,19,3497.62,-510.411,188.345,0,1000,0,'Ambush 2'),
(12818,0,20,3498.5,-497.788,185.806,0,0,0,''),
(12818,0,21,3484.22,-489.718,182.39,0,4000,0,''),
(12858,0,0,1782.63,-2241.11,109.73,0,5000,0,''),
(12858,0,1,1788.88,-2240.17,111.71,0,0,0,''),
(12858,0,2,1797.49,-2238.11,112.31,0,0,0,''),
(12858,0,3,1803.83,-2232.77,111.22,0,0,0,''),
(12858,0,4,1806.65,-2217.83,107.36,0,0,0,''),
(12858,0,5,1811.81,-2208.01,107.45,0,0,0,''),
(12858,0,6,1820.85,-2190.82,100.49,0,0,0,''),
(12858,0,7,1829.6,-2177.49,96.44,0,0,0,''),
(12858,0,8,1837.98,-2164.19,96.71,0,0,0,'prepare'),
(12858,0,9,1839.99,-2149.29,96.78,0,0,0,''),
(12858,0,10,1835.14,-2134.98,96.8,0,0,0,''),
(12858,0,11,1823.57,-2118.27,97.43,0,0,0,''),
(12858,0,12,1814.99,-2110.35,98.38,0,0,0,''),
(12858,0,13,1806.6,-2103.09,99.19,0,0,0,''),
(12858,0,14,1798.27,-2095.77,100.04,0,0,0,''),
(12858,0,15,1783.59,-2079.92,100.81,0,0,0,''),
(12858,0,16,1776.79,-2069.48,101.77,0,0,0,''),
(12858,0,17,1776.82,-2054.59,109.82,0,0,0,''),
(12858,0,18,1776.88,-2047.56,109.83,0,0,0,''),
(12858,0,19,1776.86,-2036.55,109.83,0,0,0,''),
(12858,0,20,1776.9,-2024.56,109.83,0,0,0,'win'),
(12858,0,21,1776.87,-2028.31,109.83,0,60000,0,'stay'),
(12858,0,22,1776.9,-2028.3,109.83,0,0,0,''),
(15420,0,0,9294.78,-6682.51,22.42,0,0,0,''),
(15420,0,1,9298.27,-6667.99,22.42,0,0,0,''),
(15420,0,2,9309.63,-6658.84,22.43,0,0,0,''),
(15420,0,3,9304.43,-6649.31,26.46,0,0,0,''),
(15420,0,4,9298.83,-6648,28.61,0,0,0,''),
(15420,0,5,9291.06,-6653.46,31.83,0,2500,0,''),
(15420,0,6,9289.08,-6660.17,31.85,0,5000,0,''),
(15420,0,7,9291.06,-6653.46,31.83,0,0,0,''),
(16295,0,0,7545.07,-7359.87,162.354,0,4000,0,'SAY_START'),
(16295,0,1,7550.05,-7362.24,162.236,0,0,0,''),
(16295,0,2,7566.98,-7364.32,161.739,0,0,0,''),
(16295,0,3,7578.83,-7361.68,161.739,0,0,0,''),
(16295,0,4,7590.97,-7359.05,162.258,0,0,0,''),
(16295,0,5,7598.35,-7362.82,162.257,0,4000,0,'SAY_PROGRESS_1'),
(16295,0,6,7605.86,-7380.42,161.937,0,0,0,''),
(16295,0,7,7605.3,-7387.38,157.254,0,0,0,''),
(16295,0,8,7606.13,-7393.89,156.942,0,0,0,''),
(16295,0,9,7615.21,-7400.19,157.143,0,0,0,''),
(16295,0,10,7618.96,-7402.65,158.202,0,0,0,''),
(16295,0,11,7636.85,-7401.76,162.145,0,0,0,'SAY_PROGRESS_2'),
(16295,0,12,7637.06,-7404.94,162.207,0,4000,0,''),
(16295,0,13,7636.91,-7412.59,162.366,0,0,0,''),
(16295,0,14,7637.61,-7425.59,162.631,0,0,0,''),
(16295,0,15,7637.82,-7459.06,163.303,0,0,0,''),
(16295,0,16,7638.86,-7470.9,162.517,0,0,0,''),
(16295,0,17,7641.4,-7488.22,157.381,0,0,0,''),
(16295,0,18,7634.46,-7505.45,154.682,0,0,0,'SAY_PROGRESS_3'),
(16295,0,19,7631.91,-7516.95,153.597,0,0,0,''),
(16295,0,20,7622.23,-7537.04,151.587,0,0,0,''),
(16295,0,21,7610.92,-7550.67,149.639,0,0,0,''),
(16295,0,22,7598.23,-7562.55,145.954,0,0,0,''),
(16295,0,23,7588.51,-7577.76,148.294,0,0,0,''),
(16295,0,24,7567.34,-7608.46,146.006,0,0,0,''),
(16295,0,25,7562.55,-7617.42,148.098,0,0,0,''),
(16295,0,26,7561.51,-7645.06,151.245,0,0,0,''),
(16295,0,27,7563.34,-7654.65,151.227,0,0,0,''),
(16295,0,28,7565.53,-7658.3,151.249,0,0,0,''),
(16295,0,30,7579.12,-7662.21,151.652,0,0,0,'quest complete'),
(16295,0,31,7603.77,-7667,153.998,0,0,0,''),
(16295,0,32,7603.77,-7667,153.998,0,4000,0,'SAY_END_1'),
(16295,0,33,7603.77,-7667,153.998,0,8000,0,'SAY_END_2'),
(16295,0,34,7603.77,-7667,153.998,0,0,0,''),
(16295,0,39,7571.16,-7659.12,151.245,0,0,0,''),
(16812,0,0,-10868.3,-1779.84,90.476,0,2500,0,'Open door, begin walking'),
(16812,0,1,-10875.6,-1779.58,90.478,0,0,0,''),
(16812,0,2,-10887.4,-1779.26,90.476,0,0,0,''),
(16812,0,3,-10894.6,-1780.67,90.476,0,0,0,''),
(16812,0,4,-10895,-1782.04,90.476,0,2500,0,'Begin Speech after this'),
(16812,0,5,-10894.6,-1780.67,90.476,0,0,0,'Resume walking (back to spawn point now) after speech'),
(16812,0,6,-10887.4,-1779.26,90.476,0,0,0,''),
(16812,0,7,-10875.6,-1779.58,90.478,0,0,0,''),
(16812,0,8,-10868.3,-1779.84,90.476,0,5000,0,'close door'),
(16812,0,9,-10866.8,-1780.96,90.47,0,2000,0,'Summon mobs, open curtains'),
(16993,0,0,-1137.73,4272.1,14.0485,0,3500,0,''),
(16993,0,1,-1142.87,4251.58,13.9909,0,0,0,''),
(16993,0,2,-1142.67,4225.87,14.3029,0,0,0,''),
(16993,0,3,-1127.21,4213.17,13.6458,0,0,0,''),
(16993,0,4,-1123.65,4205.01,15.2288,0,0,0,''),
(16993,0,5,-1106.34,4201.89,15.9839,0,0,0,''),
(16993,0,6,-1091.46,4200.83,16.7737,0,0,0,''),
(16993,0,7,-1079.59,4201.02,16.7962,0,0,0,''),
(16993,0,8,-1054.96,4198.35,15.2285,0,0,0,''),
(16993,0,9,-1021.06,4189.7,16.3929,0,0,0,''),
(16993,0,10,-1005.45,4188.33,17.9265,0,0,0,''),
(16993,0,11,-973.96,4187.16,24.1454,0,0,0,''),
(16993,0,12,-958.115,4185.98,27.9229,0,2000,0,'Over there - wait'),
(16993,0,13,-958.115,4185.98,27.9229,0,4000,0,'Over there - say & spawn'),
(16993,0,14,-930.922,4216.79,33.6533,0,0,0,''),
(16993,0,15,-909.867,4210.45,40.5747,0,0,0,''),
(16993,0,16,-888.726,4206.29,43.9528,0,0,0,''),
(16993,0,17,-872.329,4210.79,44.0723,0,0,0,''),
(16993,0,18,-859.831,4218.63,44.5452,0,750,0,'Allow me a moment - stop'),
(16993,0,19,-859.831,4218.63,44.5452,0,6000,0,'Allow me a moment - kneel say'),
(16993,0,20,-859.831,4218.63,44.5452,0,1000,0,'stand'),
(16993,0,21,-859.831,4218.63,44.5452,0,4000,0,'Do you hear something'),
(16993,0,22,-834.075,4207.8,46.2378,0,0,0,''),
(16993,0,23,-821.511,4205.95,45.812,0,0,0,''),
(16993,0,24,-808.365,4201.51,45.1883,0,0,0,''),
(16993,0,25,-786.704,4204.68,44.6353,0,0,0,''),
(16993,0,26,-766.773,4208.33,48.118,0,0,0,''),
(16993,0,27,-745.265,4203.63,48.733,0,0,0,''),
(16993,0,28,-724.692,4197.74,51.5662,0,0,0,''),
(16993,0,29,-711.92,4195.35,54.742,0,0,0,''),
(16993,0,30,-698.287,4191.03,57.3717,0,0,0,''),
(16993,0,31,-694.414,4183.79,57.2819,0,0,0,''),
(16993,0,32,-690.789,4173.94,57.7047,0,0,0,''),
(16993,0,33,-687.706,4163.23,59.3383,0,0,0,''),
(16993,0,34,-683.433,4152.94,62.6162,0,0,0,''),
(16993,0,35,-679.359,4146.83,64.3739,0,0,0,''),
(16993,0,36,-668.823,4148.17,64.2382,0,0,0,''),
(16993,0,37,-654.019,4146.35,64.1158,0,0,0,''),
(16993,0,38,-650.826,4138,64.6607,0,3000,0,'Falcon Watch - say'),
(16993,0,39,-650.826,4138,64.6607,0,2000,0,'Falcon Watch - faint'),
(16993,0,40,-650.826,4138,64.6607,0,3000,0,'Falcon Watch - Teleris kneel - complete'),
(16993,0,41,-650.826,4138,64.6607,0,7000,0,'Falcon Watch - Teleris react'),
(17077,0,0,-16.9501,3801.41,95.064,0,5000,0,'EMOTE_WOLF_LIFT_HEAD'),
(17077,0,1,-15.5774,3805.17,94.833,0,2500,0,''),
(17077,0,2,-20.0118,3806.61,92.476,0,5000,0,'EMOTE_WOLF_HOWL'),
(17077,0,3,-18.5947,3816.21,91.482,0,0,0,''),
(17077,0,4,-19.2935,3838.22,85.012,0,0,0,''),
(17077,0,5,-16.5044,3871.03,82.327,0,0,0,''),
(17077,0,6,2.06451,3898.68,85.623,0,0,0,''),
(17077,0,7,16.4039,3921.17,86.024,0,0,0,''),
(17077,0,8,47.3079,3932,83.302,0,0,0,''),
(17077,0,9,90.0672,3942.91,77,0,0,0,''),
(17077,0,10,106.886,3944.39,76.502,0,0,0,''),
(17077,0,11,139.085,3941.9,80.617,0,0,0,''),
(17077,0,12,150.092,3942.78,80.399,0,0,0,''),
(17077,0,13,193.511,3950.4,74.366,0,0,0,''),
(17077,0,14,226.275,3958,73.257,0,0,0,''),
(17077,0,15,246.687,3963.31,76.376,0,0,0,''),
(17077,0,16,264.206,3977.73,83.704,0,0,0,''),
(17077,0,17,279.857,3986.42,88.245,0,0,0,''),
(17077,0,18,304.04,3998.35,95.649,0,0,0,''),
(17077,0,19,328.072,3995.83,104.434,0,0,0,''),
(17077,0,20,347.485,3990.82,113.608,0,0,0,''),
(17077,0,21,351.257,3954.26,125.747,0,0,0,''),
(17077,0,22,345.626,3932.02,132.358,0,0,0,''),
(17077,0,23,347.972,3908.55,135.52,0,0,0,''),
(17077,0,24,351.888,3891.06,139.957,0,0,0,''),
(17077,0,25,346.117,3864.63,146.647,0,0,0,''),
(17077,0,26,330.012,3839.86,154.148,0,0,0,''),
(17077,0,27,297.251,3811.86,166.893,0,0,0,''),
(17077,0,28,290.783,3800.19,172.13,0,0,0,''),
(17077,0,29,288.125,3782.47,180.825,0,0,0,''),
(17077,0,30,296.818,3771.63,184.961,0,0,0,''),
(17077,0,31,305.256,3765.38,185.36,0,0,0,''),
(17077,0,32,311.448,3757.9,184.312,0,0,0,''),
(17077,0,33,325.258,3730.28,184.076,0,0,0,''),
(17077,0,34,341.159,3717.76,183.904,0,0,0,''),
(17077,0,35,365.589,3717.2,183.902,0,0,0,''),
(17077,0,36,387.395,3731.75,183.645,0,0,0,''),
(17077,0,37,396.574,3732.6,179.831,0,0,0,''),
(17077,0,38,404.303,3737.31,180.151,0,0,0,''),
(17077,0,39,410.996,3742.29,183.364,0,0,0,''),
(17077,0,40,434.905,3761.06,186.219,0,0,0,''),
(17077,0,41,460.129,3774.44,186.348,0,0,0,''),
(17077,0,42,467.644,3788.51,186.446,0,0,0,''),
(17077,0,43,491.552,3815.45,189.848,0,0,0,''),
(17077,0,44,496.958,3836.88,193.078,0,0,0,''),
(17077,0,45,502.889,3855.46,194.834,0,0,0,''),
(17077,0,46,508.208,3863.69,194.024,0,0,0,''),
(17077,0,47,528.908,3887.35,189.762,0,0,0,''),
(17077,0,48,527.722,3890.69,189.24,0,0,0,''),
(17077,0,49,524.637,3891.77,189.149,0,0,0,''),
(17077,0,50,519.146,3886.7,190.128,0,60000,0,'SAY_WOLF_WELCOME'),
(17225,0,0,-11033.5,-1784.65,182.284,0,3000,0,''),
(17225,0,1,-11107.6,-1873.36,136.878,0,0,0,''),
(17225,0,2,-11118.7,-1883.65,132.441,0,0,0,''),
(17225,0,3,-11132.9,-1888.12,128.969,0,0,0,''),
(17225,0,4,-11150.3,-1890.54,126.557,0,0,0,''),
(17225,0,5,-11160.6,-1891.63,124.793,0,0,0,''),
(17225,0,6,-11171.5,-1889.45,123.417,0,0,0,''),
(17225,0,7,-11183.5,-1884.09,119.754,0,0,0,''),
(17225,0,8,-11196.2,-1874.01,115.227,0,0,0,''),
(17225,0,9,-11205.6,-1859.66,110.216,0,0,0,''),
(17225,0,10,-11236.5,-1818.03,97.3972,0,0,0,''),
(17225,0,11,-11253.1,-1794.48,93.3101,0,0,0,''),
(17225,0,12,-11254.9,-1787.13,92.5174,0,0,0,''),
(17225,0,13,-11253.3,-1777.08,91.7739,0,0,0,''),
(17225,0,14,-11247.5,-1770.27,92.4183,0,0,0,''),
(17225,0,15,-11238.6,-1766.51,94.6417,0,0,0,''),
(17225,0,16,-11227.6,-1767.22,100.256,0,0,0,''),
(17225,0,17,-11218.4,-1770.55,107.859,0,0,0,''),
(17225,0,18,-11204.8,-1781.77,110.383,0,0,0,''),
(17225,0,19,-11195.8,-1801.07,110.833,0,0,0,''),
(17225,0,20,-11195.8,-1824.66,113.936,0,0,0,''),
(17225,0,21,-11197.1,-1860.01,117.945,0,0,0,''),
(17225,0,22,-11194.6,-1884.23,121.401,0,0,0,''),
(17225,0,23,-11184.2,-1894.78,120.326,0,0,0,''),
(17225,0,24,-11176.9,-1899.84,119.844,0,0,0,''),
(17225,0,25,-11168.1,-1901.77,118.958,0,0,0,''),
(17225,0,26,-11154.9,-1901.66,117.218,0,0,0,''),
(17225,0,27,-11143.2,-1901.22,115.885,0,0,0,''),
(17225,0,28,-11131.2,-1897.59,113.722,0,0,0,''),
(17225,0,29,-11121.3,-1890.25,111.643,0,0,0,''),
(17225,0,30,-11118.2,-1883.83,110.595,0,3000,0,''),
(17225,0,31,-11118.5,-1883.68,91.473,0,0,0,'start combat'),
(17238,0,0,954.21,-1433.72,63,0,0,0,''),
(17238,0,1,972.7,-1438.85,65.56,0,0,0,''),
(17238,0,2,984.79,-1444.15,64.13,0,0,0,''),
(17238,0,3,999,-1451.74,61.2,0,0,0,''),
(17238,0,4,1030.94,-1470.39,63.49,0,25000,0,'SAY_FIRST_STOP'),
(17238,0,5,1030.94,-1470.39,63.49,0,3000,0,'SAY_CONTINUE'),
(17238,0,6,1036.5,-1484.25,64.6,0,0,0,''),
(17238,0,7,1039.11,-1501.22,65.32,0,0,0,''),
(17238,0,8,1038.44,-1522.18,64.55,0,0,0,''),
(17238,0,9,1037.19,-1543.15,62.33,0,0,0,''),
(17238,0,10,1036.79,-1563.88,61.93,0,5000,0,'SAY_FIRST_ATTACK'),
(17238,0,11,1036.79,-1563.88,61.93,0,5000,0,'SAY_PURITY'),
(17238,0,12,1035.61,-1587.64,61.66,0,0,0,''),
(17238,0,13,1035.43,-1612.97,61.54,0,0,0,''),
(17238,0,14,1035.36,-1630.66,61.53,0,0,0,''),
(17238,0,15,1038.85,-1653.02,60.35,0,0,0,''),
(17238,0,16,1042.27,-1669.36,60.75,0,0,0,''),
(17238,0,17,1050.41,-1687.22,60.52,0,0,0,''),
(17238,0,18,1061.15,-1704.45,60.59,0,0,0,''),
(17238,0,19,1073.51,-1716.99,60.65,0,0,0,''),
(17238,0,20,1084.2,-1727.24,60.95,0,0,0,''),
(17238,0,21,1100.71,-1739.89,60.64,0,5000,0,'SAY_SECOND_ATTACK'),
(17238,0,22,1100.71,-1739.89,60.64,0,0,0,'SAY_CLEANSE'),
(17238,0,23,1117.03,-1749.01,60.87,0,0,0,''),
(17238,0,24,1123.58,-1762.29,62.4,0,0,0,''),
(17238,0,25,1123.36,-1769.29,62.83,0,0,0,''),
(17238,0,26,1115.78,-1779.59,62.09,0,0,0,''),
(17238,0,27,1109.56,-1789.78,61.03,0,0,0,''),
(17238,0,28,1094.81,-1797.62,61.22,0,0,0,''),
(17238,0,29,1079.3,-1801.58,64.95,0,0,0,''),
(17238,0,30,1060.24,-1803.4,70.36,0,0,0,''),
(17238,0,31,1047.69,-1804.49,73.92,0,0,0,''),
(17238,0,32,1032.59,-1805.99,76.13,0,0,0,''),
(17238,0,33,1013.6,-1812.36,77.32,0,0,0,''),
(17238,0,34,1007.01,-1814.38,80.48,0,0,0,''),
(17238,0,35,999.93,-1816.39,80.48,0,2000,0,'SAY_WELCOME'),
(17238,0,36,984.72,-1822.05,80.48,0,0,0,''),
(17238,0,37,977.77,-1824.8,80.79,0,0,0,''),
(17238,0,38,975.33,-1824.91,81.24,0,12000,0,'event complete'),
(17238,0,39,975.33,-1824.91,81.24,0,10000,0,'SAY_EPILOGUE_1'),
(17238,0,40,975.33,-1824.91,81.24,0,8000,0,'SAY_EPILOGUE_2'),
(17238,0,41,975.33,-1824.91,81.24,0,30000,0,''),
(17312,0,0,-4781.36,-11054.6,2.475,0,5000,0,'SAY_START'),
(17312,0,1,-4786.9,-11050.3,3.868,0,0,0,''),
(17312,0,2,-4830.3,-11043.2,1.651,0,0,0,''),
(17312,0,3,-4833.82,-11038,1.607,0,0,0,''),
(17312,0,4,-4856.62,-11034.5,1.665,0,0,0,''),
(17312,0,5,-4876.67,-11030.6,1.942,0,0,0,''),
(17312,0,6,-4881.06,-11035.6,5.067,0,0,0,''),
(17312,0,7,-4904.61,-11042.7,10.689,0,0,0,''),
(17312,0,8,-4913.1,-11051,12.655,0,0,0,''),
(17312,0,9,-4924.45,-11059.2,14.604,0,0,0,''),
(17312,0,10,-4939.89,-11066.8,13.77,0,0,0,''),
(17312,0,11,-4951.94,-11067.6,14.174,0,0,0,''),
(17312,0,12,-4971.94,-11064.9,16.977,0,0,0,''),
(17312,0,13,-4995.02,-11068.2,21.874,0,0,0,''),
(17312,0,14,-5017.98,-11055.2,22.739,0,0,0,''),
(17312,0,15,-5036.87,-11039.7,25.646,0,0,0,''),
(17312,0,16,-5064,-11027,27.466,0,0,0,''),
(17312,0,17,-5086.48,-11029.3,28.866,0,0,0,''),
(17312,0,18,-5108.68,-11034.5,29.54,0,0,0,''),
(17312,0,19,-5133.68,-11038.8,29.169,0,0,0,''),
(17312,0,20,-5163.79,-11042.2,28.07,0,4000,0,'SAY_PROGRESS'),
(17312,0,21,-5161.12,-11052.9,31.664,0,0,0,''),
(17312,0,22,-5160.37,-11066.5,31.499,0,0,0,''),
(17312,0,23,-5165.48,-11071.7,27.989,0,0,0,''),
(17312,0,24,-5177.59,-11076.6,21.986,0,0,0,''),
(17312,0,25,-5193.23,-11084.3,20.009,0,0,0,''),
(17312,0,26,-5207.54,-11090.4,21.519,0,0,0,''),
(17312,0,27,-5252.69,-11098.8,15.572,0,0,0,''),
(17312,0,28,-5268.33,-11105.3,12.53,0,0,0,''),
(17312,0,29,-5282.29,-11113.1,7.134,0,0,0,''),
(17312,0,30,-5302.01,-11127.3,6.704,0,0,0,''),
(17312,0,31,-5317.62,-11139.3,4.684,0,0,0,''),
(17312,0,32,-5319.09,-11140.5,5.57,0,0,0,''),
(17312,0,33,-5344.95,-11163.4,6.959,0,2000,0,'SAY_END1'),
(17312,0,34,-5344.95,-11163.4,6.959,0,1000,0,'SAY_DAUGHTER'),
(17312,0,35,-5355.86,-11173.8,6.853,0,2000,0,'EMOTE_HUG'),
(17312,0,36,-5355.86,-11173.8,6.853,0,5000,0,'SAY_END2'),
(17312,0,37,-5355.86,-11173.8,6.853,0,0,0,''),
(17804,0,0,-9054.86,443.58,93.05,0,0,0,''),
(17804,0,1,-9079.33,424.49,92.52,0,0,0,''),
(17804,0,2,-9086.21,419.02,92.32,0,3000,0,''),
(17804,0,3,-9086.21,419.02,92.32,0,1000,0,''),
(17804,0,4,-9079.33,424.49,92.52,0,0,0,''),
(17804,0,5,-9054.38,436.3,93.05,0,0,0,''),
(17804,0,6,-9042.23,434.24,93.37,0,5000,0,'SAY_SIGNAL_SENT'),
(17876,0,0,2230.91,118.765,82.2947,0,2000,0,'open the prison door'),
(17876,0,1,2230.33,114.98,82.2946,0,0,0,''),
(17876,0,2,2233.36,111.057,82.2996,0,0,0,''),
(17876,0,3,2231.17,108.486,82.6624,0,0,0,''),
(17876,0,4,2220.22,114.605,89.4264,0,0,0,''),
(17876,0,5,2215.23,115.99,89.4549,0,0,0,''),
(17876,0,6,2210,106.849,89.4549,0,0,0,''),
(17876,0,7,2205.66,105.234,89.4549,0,0,0,''),
(17876,0,8,2192.26,112.618,89.4549,0,2000,0,'SAY_ARMORER_CALL_GUARDS'),
(17876,0,9,2185.32,116.593,89.4548,0,2000,0,'SAY_TH_ARMORER_HIT'),
(17876,0,10,2182.11,120.328,89.4548,0,3000,0,'SAY_TH_ARMORY_1'),
(17876,0,11,2182.11,120.328,89.4548,0,2000,0,''),
(17876,0,12,2182.11,120.328,89.4548,0,2000,0,''),
(17876,0,13,2182.11,120.328,89.4548,0,2000,0,''),
(17876,0,14,2182.11,120.328,89.4548,0,3000,0,''),
(17876,0,15,2182.11,120.328,89.4548,0,3000,0,'SAY_TH_ARMORY_2'),
(17876,0,16,2189.44,113.922,89.4549,0,0,0,''),
(17876,0,17,2195.63,110.584,89.4549,0,0,0,''),
(17876,0,18,2201.09,115.115,89.4549,0,0,0,''),
(17876,0,19,2204.34,121.036,89.4355,0,0,0,''),
(17876,0,20,2208.66,129.127,87.956,0,0,0,'first ambush'),
(17876,0,21,2193.09,137.94,88.2164,0,0,0,''),
(17876,0,22,2173.39,149.064,87.9227,0,0,0,''),
(17876,0,23,2164.25,137.965,85.0595,0,0,0,'second ambush'),
(17876,0,24,2149.31,125.645,77.0858,0,0,0,''),
(17876,0,25,2142.78,127.173,75.5954,0,0,0,''),
(17876,0,26,2139.28,133.952,73.6386,0,0,0,'third ambush'),
(17876,0,27,2139.54,155.235,67.1269,0,0,0,''),
(17876,0,28,2145.38,167.551,64.8974,0,0,0,'fourth ambush'),
(17876,0,29,2134.28,175.304,67.9446,0,0,0,''),
(17876,0,30,2118.08,187.387,68.8141,0,0,0,''),
(17876,0,31,2105.88,195.461,65.1854,0,0,0,''),
(17876,0,32,2096.77,196.939,65.2117,0,0,0,''),
(17876,0,33,2083.9,209.395,64.8736,0,0,0,''),
(17876,0,34,2063.4,229.509,64.4883,0,0,0,'summon Skarloc'),
(17876,0,35,2063.4,229.509,64.4883,0,10000,0,'SAY_SKARLOC_ENTER'),
(17876,0,36,2063.4,229.509,64.4883,0,5000,0,'attack Skarloc'),
(17876,0,37,2063.4,229.509,64.4883,0,0,0,'gossip after skarloc'),
(17876,0,38,2046.7,251.941,62.7851,0,4000,0,'mount up'),
(17876,0,39,2046.7,251.941,62.7851,0,3000,0,'SAY_TH_MOUNTS_UP'),
(17876,0,40,2011.77,278.478,65.3388,0,0,0,''),
(17876,0,41,2005.08,289.676,66.1179,0,0,0,''),
(17876,0,42,2033.11,337.45,66.0948,0,0,0,''),
(17876,0,43,2070.3,416.208,66.0893,0,0,0,''),
(17876,0,44,2086.76,469.768,65.9182,0,0,0,''),
(17876,0,45,2101.7,497.955,61.7881,0,0,0,''),
(17876,0,46,2133.39,530.933,55.37,0,0,0,''),
(17876,0,47,2157.91,559.635,48.5157,0,0,0,''),
(17876,0,48,2167.34,586.191,42.4394,0,0,0,''),
(17876,0,49,2174.17,637.643,33.9002,0,0,0,''),
(17876,0,50,2179.31,656.053,34.723,0,0,0,''),
(17876,0,51,2183.65,670.941,34.0318,0,0,0,''),
(17876,0,52,2201.5,668.616,36.1236,0,0,0,''),
(17876,0,53,2221.56,652.747,36.6153,0,0,0,''),
(17876,0,54,2238.97,640.125,37.2214,0,0,0,''),
(17876,0,55,2251.17,620.574,40.1473,0,0,0,''),
(17876,0,56,2261.98,595.303,41.4117,0,0,0,''),
(17876,0,57,2278.67,560.172,38.909,0,0,0,''),
(17876,0,58,2336.72,528.327,40.9369,0,0,0,''),
(17876,0,59,2381.04,519.612,37.7312,0,0,0,''),
(17876,0,60,2412.2,515.425,39.2068,0,0,0,''),
(17876,0,61,2452.39,516.174,42.9387,0,0,0,''),
(17876,0,62,2467.38,539.389,47.4992,0,0,0,''),
(17876,0,63,2470.7,554.333,46.6668,0,0,0,''),
(17876,0,64,2478.07,575.321,55.4549,0,0,0,''),
(17876,0,65,2480,585.408,56.6921,0,0,0,''),
(17876,0,66,2482.67,608.817,55.6643,0,0,0,''),
(17876,0,67,2485.62,626.061,58.0132,0,2000,0,'dismount'),
(17876,0,68,2486.91,626.356,58.0761,0,2000,0,'EMOTE_TH_STARTLE_HORSE'),
(17876,0,69,2486.91,626.356,58.0761,0,0,0,'gossip before barn'),
(17876,0,70,2488.58,660.94,57.3913,0,0,0,''),
(17876,0,71,2502.56,686.059,55.6252,0,0,0,''),
(17876,0,72,2502.08,694.36,55.5083,0,0,0,''),
(17876,0,73,2491.46,694.321,55.7163,0,0,0,'enter barn'),
(17876,0,74,2491.1,703.3,55.763,0,0,0,''),
(17876,0,75,2485.64,702.992,55.7917,0,0,0,''),
(17876,0,76,2479.63,696.521,55.7901,0,500,0,''),
(17876,0,77,2479.63,696.521,55.7901,0,1500,0,'spawn mobs'),
(17876,0,78,2476.24,696.204,55.8093,0,500,0,''),
(17876,0,79,2476.24,696.204,55.8093,0,0,0,'start dialogue'),
(17876,0,80,2475.39,695.983,55.8146,0,0,0,''),
(17876,0,81,2477.75,694.473,55.7945,0,0,0,''),
(17876,0,82,2481.27,697.747,55.791,0,0,0,''),
(17876,0,83,2486.31,703.131,55.7861,0,0,0,''),
(17876,0,84,2490.76,703.511,55.7662,0,0,0,''),
(17876,0,85,2491.3,694.792,55.7195,0,0,0,'exit barn'),
(17876,0,86,2502.08,694.36,55.5083,0,0,0,''),
(17876,0,87,2507.99,679.298,56.376,0,0,0,''),
(17876,0,88,2524.79,669.919,54.9258,0,0,0,''),
(17876,0,89,2543.19,665.289,56.2957,0,0,0,''),
(17876,0,90,2566.49,664.354,54.5034,0,0,0,''),
(17876,0,91,2592,664.611,56.4394,0,0,0,''),
(17876,0,92,2614.43,663.806,55.3921,0,2000,0,''),
(17876,0,93,2616.14,665.499,55.161,0,0,0,''),
(17876,0,94,2623.56,666.965,54.3983,0,0,0,''),
(17876,0,95,2629.99,661.059,54.2738,0,0,0,''),
(17876,0,96,2629,656.982,56.0651,0,0,0,'enter the church'),
(17876,0,97,2620.84,633.007,56.03,0,3000,0,'SAY_TH_CHURCH_ENTER'),
(17876,0,98,2620.84,633.007,56.03,0,5000,0,'church ambush'),
(17876,0,99,2620.84,633.007,56.03,0,0,0,'SAY_TH_CHURCH_END'),
(17876,0,100,2622.99,639.178,56.03,0,0,0,''),
(17876,0,101,2628.73,656.693,56.061,0,0,0,''),
(17876,0,102,2630.34,661.135,54.2738,0,0,0,''),
(17876,0,103,2635.38,672.243,54.4508,0,0,0,''),
(17876,0,104,2644.13,668.158,55.3797,0,0,0,''),
(17876,0,105,2646.82,666.74,56.9898,0,0,0,''),
(17876,0,106,2658.22,665.432,57.1725,0,0,0,''),
(17876,0,107,2661.88,674.849,57.1725,0,0,0,''),
(17876,0,108,2656.23,677.208,57.1725,0,0,0,''),
(17876,0,109,2652.28,670.27,61.9353,0,0,0,''),
(17876,0,110,2650.79,664.29,61.9302,0,0,0,'inn ambush'),
(17876,0,111,2660.48,659.409,61.937,0,5000,0,'SAY_TA_ESCAPED'),
(17876,0,112,2660.48,659.409,61.937,0,0,0,'SAY_TH_MEET_TARETHA - gossip before epoch'),
(17876,0,113,2660.48,659.409,61.937,0,0,0,'SAY_EPOCH_ENTER1'),
(17876,0,114,2650.62,666.643,61.9305,0,0,0,''),
(17876,0,115,2652.37,670.561,61.9368,0,0,0,''),
(17876,0,116,2656.05,676.761,57.1727,0,0,0,''),
(17876,0,117,2658.49,677.166,57.1727,0,0,0,''),
(17876,0,118,2659.28,667.117,57.1727,0,0,0,''),
(17876,0,119,2649.71,665.387,57.1727,0,0,0,''),
(17876,0,120,2634.79,672.964,54.4577,0,0,0,'outside inn'),
(17876,0,121,2635.06,673.892,54.4713,0,18000,0,'SAY_EPOCH_ENTER3'),
(17876,0,122,2635.06,673.892,54.4713,0,0,0,'fight begins'),
(17876,0,123,2635.06,673.892,54.4713,0,0,0,'fight ends'),
(17876,0,124,2634.3,661.698,54.4147,0,0,0,'run off'),
(17876,0,125,2652.21,644.396,56.1906,0,0,0,''),
(17877,0,0,231.403,8479.94,17.928,0,3000,0,''),
(17877,0,1,214.645,8469.64,23.121,0,0,0,''),
(17877,0,2,208.538,8463.48,24.738,0,0,0,''),
(17877,0,3,196.524,8446.08,24.814,0,0,0,''),
(17877,0,4,188.186,8431.67,22.625,0,0,0,''),
(17877,0,5,181.196,8420.15,23.73,0,0,0,''),
(17877,0,6,171.919,8406.29,21.844,0,0,0,''),
(17877,0,7,166.613,8396.48,23.585,0,0,0,''),
(17877,0,8,167.237,8386.69,21.546,0,0,0,''),
(17877,0,9,169.401,8372.67,19.599,0,0,0,''),
(17877,0,10,174.148,8342.33,20.409,0,0,0,''),
(17877,0,11,173.195,8324.18,21.126,0,0,0,''),
(17877,0,12,172.415,8310.29,21.702,0,0,0,''),
(17877,0,13,173.233,8298.75,19.564,0,0,0,''),
(17877,0,14,173.984,8287.92,18.839,0,0,0,''),
(17877,0,15,189.984,8266.26,18.5,0,0,0,''),
(17877,0,16,204.057,8256.02,19.701,0,0,0,''),
(17877,0,17,212.95,8248.74,21.583,0,0,0,''),
(17877,0,18,223.152,8240.16,20.001,0,0,0,''),
(17877,0,19,230.73,8232.99,18.99,0,0,0,''),
(17877,0,20,238.261,8223.8,20.72,0,0,0,''),
(17877,0,21,247.651,8214.21,19.146,0,0,0,''),
(17877,0,22,259.231,8207.8,19.278,0,0,0,''),
(17877,0,23,272.36,8204.75,19.98,0,0,0,''),
(17877,0,24,282.211,8202.09,22.09,0,20000,0,'SAY_PREPARE'),
(17877,0,25,282.211,8202.09,22.09,0,0,0,'SAY_CAMP_ENTER'),
(17877,0,26,296.006,8191.64,21.68,0,0,0,''),
(17877,0,27,304.472,8188.05,20.707,0,0,0,''),
(17877,0,28,317.574,8182.04,18.296,0,0,0,''),
(17877,0,29,340.046,8178.78,17.937,0,0,0,''),
(17877,0,30,353.799,8181.22,18.557,0,0,0,''),
(17877,0,31,368.231,8186.32,22.45,0,0,0,''),
(17877,0,32,375.737,8187.03,23.916,0,0,0,''),
(17877,0,33,390.067,8186.64,21.19,0,0,0,''),
(17877,0,34,398.699,8181.82,18.648,0,0,0,''),
(17877,0,35,412.325,8172.61,17.927,0,0,0,''),
(17877,0,36,424.541,8161.96,19.575,0,0,0,''),
(17877,0,37,436.9,8157.41,22.115,0,0,0,''),
(17877,0,38,444.548,8155.41,23.553,0,0,0,''),
(17877,0,39,457.201,8154.23,23.429,0,0,0,''),
(17877,0,40,470.989,8154.14,21.65,0,0,0,''),
(17877,0,41,483.435,8154.15,20.706,0,0,0,''),
(17877,0,42,507.558,8157.52,21.729,0,0,0,''),
(17877,0,43,528.036,8162.03,22.795,0,0,0,''),
(17877,0,44,542.402,8161.1,22.914,0,0,0,''),
(17877,0,45,557.286,8160.27,23.708,0,13000,0,''),
(17877,0,46,557.286,8160.27,23.708,0,0,0,'take the Ark'),
(17877,0,47,539.767,8144.84,22.217,0,0,0,''),
(17877,0,48,531.296,8139.48,22.146,0,0,0,''),
(17877,0,49,509.056,8139.26,20.705,0,0,0,''),
(17877,0,50,499.975,8136.23,20.408,0,0,0,''),
(17877,0,51,485.511,8129.39,22.01,0,0,0,''),
(17877,0,52,474.371,8128.53,22.657,0,0,0,''),
(17877,0,53,460.708,8130.12,20.946,0,0,0,''),
(17877,0,54,449.248,8129.27,21.033,0,0,0,''),
(17877,0,55,433.67,8125.06,18.44,0,0,0,''),
(17877,0,56,412.822,8121.58,17.603,0,0,0,''),
(17877,0,57,391.15,8117.81,17.736,0,0,0,''),
(17877,0,58,379.024,8114.19,17.889,0,0,0,''),
(17877,0,59,365.11,8106.99,18.22,0,0,0,''),
(17877,0,60,352.531,8108.94,17.932,0,0,0,''),
(17877,0,61,340.894,8120.64,17.374,0,0,0,''),
(17877,0,62,328.48,8134.93,18.112,0,0,0,''),
(17877,0,63,317.573,8143.25,20.604,0,0,0,''),
(17877,0,64,311.146,8146.8,21.097,0,0,0,''),
(17877,0,65,299.359,8152.58,18.676,0,0,0,''),
(17877,0,66,276.115,8160.44,17.735,0,0,0,''),
(17877,0,67,262.704,8170.51,17.478,0,0,0,''),
(17877,0,68,243.755,8177.75,17.744,0,0,0,''),
(17877,0,69,233.496,8178.43,17.528,0,0,0,''),
(17877,0,70,219.874,8182.55,19.637,0,0,0,'SAY_AMBUSH - escort paused'),
(17877,0,71,219.874,8182.55,19.637,0,20000,0,'SAY_AMBUSH_CLEARED'),
(17877,0,72,210.978,8193.98,20.777,0,0,0,''),
(17877,0,73,203.699,8213.04,22.768,0,0,0,''),
(17877,0,74,199.246,8225.54,24.847,0,0,0,''),
(17877,0,75,195.064,8239.91,22.64,0,0,0,''),
(17877,0,76,193.198,8253.62,20.083,0,0,0,''),
(17877,0,77,189.151,8264.83,18.714,0,0,0,''),
(17877,0,78,178.814,8281.04,19.07,0,0,0,''),
(17877,0,79,173.952,8293.24,18.533,0,0,0,''),
(17877,0,80,174.399,8305.46,21.006,0,0,0,''),
(17877,0,81,175.124,8319.51,21.626,0,0,0,''),
(17877,0,82,175.69,8339.65,20.375,0,0,0,''),
(17877,0,83,172.754,8362.67,19.181,0,0,0,''),
(17877,0,84,176.465,8379.8,18.445,0,0,0,''),
(17877,0,85,186.433,8393.13,18.933,0,0,0,''),
(17877,0,86,199.438,8407.83,18.763,0,0,0,''),
(17877,0,87,211.874,8422.38,18.785,0,0,0,''),
(17877,0,88,219.9,8436.26,21.927,0,0,0,''),
(17877,0,89,225.062,8450.57,22.832,0,0,0,''),
(17877,0,90,226.942,8464.41,19.822,0,0,0,''),
(17877,0,91,231.403,8479.94,17.928,0,0,0,''),
(17877,0,92,247.625,8483.8,22.464,0,13000,0,''),
(17877,0,93,231.403,8479.94,17.928,0,10000,0,'SAY_ESCORT_COMPLETE'),
(17969,0,0,-930.049,5288.08,23.8484,0,0,0,''),
(17969,0,1,-925.678,5296.48,18.1837,0,0,0,''),
(17969,0,2,-924.297,5299.02,17.7109,0,0,0,''),
(17969,0,3,-928.39,5317.02,18.2086,0,0,0,''),
(17969,0,4,-930.621,5329.92,18.7734,0,0,0,'SAY_AMBUSH1'),
(17969,0,5,-931.49,5357.65,18.0272,0,0,0,'SAY_PROGRESS1'),
(17969,0,6,-934.778,5369.34,22.278,0,0,0,''),
(17969,0,7,-934.522,5373.41,22.8347,0,0,0,''),
(17969,0,8,-937.009,5382.98,22.6991,0,0,0,''),
(17969,0,9,-941.948,5404.14,22.6697,0,0,0,''),
(17969,0,10,-931.244,5415.85,23.064,0,0,0,'at crossroad'),
(17969,0,11,-901.498,5420.32,24.2133,0,0,0,''),
(17969,0,12,-860.312,5415.62,23.6711,0,0,0,''),
(17969,0,13,-777.989,5391.98,23.0017,0,0,0,''),
(17969,0,14,-750.362,5385.79,22.7658,0,0,0,''),
(17969,0,15,-731.339,5382.45,22.5171,0,0,0,''),
(17969,0,16,-681.236,5381.38,22.0502,0,3000,0,'end bridge SAY_AMBUSH2'),
(17969,0,17,-681.236,5381.38,22.0502,0,3000,0,'end bridge SAY_SLAVEBINDER_AMBUSH2'),
(17969,0,18,-637.944,5384.34,22.2056,0,0,0,'SAY_PROGRESS2'),
(17969,0,19,-608.954,5408.72,21.6304,0,0,0,''),
(17969,0,20,-598.134,5413.61,21.4123,0,0,0,''),
(17969,0,21,-571.269,5420.77,21.1849,0,0,0,''),
(17969,0,22,-553.1,5424.62,21.1937,0,0,0,''),
(17969,0,23,-524.745,5443.95,20.977,0,0,0,''),
(17969,0,24,-502.985,5446.28,22.1494,0,0,0,''),
(17969,0,25,-472.464,5449.55,22.5615,0,0,0,''),
(17969,0,26,-454.533,5461.3,22.6028,0,30000,0,'quest complete SAY_END'),
(17982,0,0,-1778.69,-11063.5,77.14,0,0,0,''),
(17982,0,1,-1786.79,-11051.7,77.624,0,0,0,''),
(17982,0,2,-1793.5,-11045.1,76.965,0,0,0,''),
(17982,0,3,-1793.67,-11038.3,76.308,0,0,0,''),
(17982,0,4,-1809.28,-11025.8,68.239,0,0,0,''),
(17982,0,5,-1828.21,-11007.5,67.414,0,0,0,''),
(17982,0,6,-1848.78,-10995.2,65.269,0,0,0,''),
(17982,0,7,-1875.19,-10981.4,61.316,0,0,0,''),
(17982,0,8,-1893.58,-10962.1,61.258,0,0,0,''),
(17982,0,9,-1912.96,-10935.2,61.436,0,0,0,''),
(17982,0,10,-1927.93,-10909.6,62.588,0,0,0,''),
(17982,0,11,-1936.61,-10866.2,66.684,0,0,0,''),
(17982,0,12,-1939.89,-10854,69.186,0,0,0,''),
(17982,0,13,-1936.7,-10839.4,73.829,0,0,0,''),
(17982,0,14,-1936.74,-10817.2,81.554,0,0,0,''),
(17982,0,15,-1942.17,-10803.5,86.075,0,0,0,''),
(17982,0,16,-1962.06,-10791.6,88.658,0,0,0,''),
(17982,0,17,-1973.29,-10780.2,88.985,0,0,0,''),
(17982,0,18,-1976.27,-10763.6,90.655,0,0,0,''),
(17982,0,19,-1964.07,-10745,95.73,0,0,0,''),
(17982,0,20,-1953.44,-10728.2,104.113,0,0,0,''),
(17982,0,21,-1950.74,-10710.5,111.087,0,0,0,''),
(17982,0,22,-1956.33,-10689,110.965,0,5000,0,'SAY_ESCORT_LEGOSO_1'),
(17982,0,23,-1955.62,-10658.6,110.883,0,1000,0,'escort paused, SAY_ESCORT_LEGOSO_2, SAY_ESCORT_LEGOSO_3'),
(17982,0,24,-1976.11,-10688.8,112.68,0,0,0,'SAY_ESCORT_LEGOSO_4'),
(17982,0,25,-1985.78,-10699.4,115.46,0,1000,0,'escort paused, SAY_ESCORT_COUNT_3'),
(17982,0,26,-2000.17,-10676.8,118.616,0,0,0,''),
(17982,0,27,-2016.45,-10657.8,125.049,0,0,0,''),
(17982,0,28,-2033.14,-10641.4,137.672,0,0,0,''),
(17982,0,29,-2039.43,-10628.2,144.266,0,0,0,''),
(17982,0,30,-2032.07,-10609.5,148.143,0,0,0,''),
(17982,0,31,-2017.39,-10608.1,153.232,0,0,0,''),
(17982,0,32,-1989.03,-10613.3,162.852,0,0,0,''),
(17982,0,33,-1975.88,-10616.8,163.837,0,5000,0,'SAY_ESCORT_LEGOSO_5, SAY_ESCORT_LEGOSO_6'),
(17982,0,34,-1957.05,-10596.5,168.726,0,0,0,''),
(17982,0,35,-1944.29,-10580.7,174.467,0,13000,0,'SAY_ESCORT_LEGOSO_7, SAY_ESCORT_LEGOSO_8'),
(17982,0,36,-1936.1,-10581.6,176.737,0,0,0,''),
(17982,0,37,-1915.01,-10581.5,178.105,0,1000,0,'escort paused, SAY_ESCORT_LEGOSO_9, SAY_ESCORT_LEGOSO_10'),
(17982,0,38,-1952.08,-10560.3,177.657,0,4000,0,'SAY_ESCORT_COUNT_3, SAY_ESCORT_COUNT_2, SAY_ESCORT_COUNT_1'),
(17982,0,39,-1952.08,-10560.3,177.657,0,1000,0,'escort paused, SAY_LEGOSO_AGGRO'),
(18209,0,0,-1516.63,8462.39,-4.01942,0,500,0,''),
(18209,0,1,-1530.59,8456.21,-3.97776,0,1500,0,'We must leave'),
(18209,0,2,-1526.25,8450.41,-3.97776,0,0,0,''),
(18209,0,3,-1506.32,8435.58,-2.11936,0,0,0,''),
(18209,0,4,-1495.65,8442.8,0.286346,0,0,0,''),
(18209,0,5,-1480.39,8465.27,0.275359,0,0,0,''),
(18209,0,6,-1464.41,8488.97,3.63549,0,0,0,''),
(18209,0,7,-1433.32,8507.52,7.55011,0,500,0,'Surrounded - say'),
(18209,0,8,-1433.32,8507.52,7.55011,0,2500,0,'Surrounded - spawn'),
(18209,0,9,-1433.32,8507.52,7.55011,0,4500,0,'Up ahead'),
(18209,0,10,-1420.74,8514.73,8.33551,0,0,0,''),
(18209,0,11,-1387.99,8538.25,11.0952,0,0,0,''),
(18209,0,12,-1386.31,8551.87,11.4702,0,5000,0,'Farewell - Complete'),
(18209,0,13,-1417,8603.66,15.5289,0,0,0,''),
(18209,0,14,-1440.22,8636.15,17.5314,0,0,0,''),
(18209,0,15,-1462.38,8672.52,20.4273,0,0,0,''),
(18210,0,0,-1583.63,8564.92,2.08442,0,500,0,'Look out'),
(18210,0,1,-1579.65,8555.47,2.78855,0,0,0,''),
(18210,0,2,-1554.27,8517.98,0.483805,0,0,0,''),
(18210,0,3,-1549.79,8514.52,0.145915,0,0,0,''),
(18210,0,4,-1517.2,8516.44,0.658376,0,500,0,'More Coming - say'),
(18210,0,5,-1517.2,8516.44,0.658376,0,2000,0,'More Coming - spawn'),
(18210,0,6,-1467.36,8492.89,3.12625,0,0,0,''),
(18210,0,7,-1459.1,8490.89,4.27294,0,0,0,''),
(18210,0,8,-1424.02,8512.76,8.08551,0,0,0,''),
(18210,0,9,-1404.68,8522.54,9.60284,0,0,0,''),
(18210,0,10,-1385.26,8542.59,11.2687,0,500,0,'Split up - complete'),
(18210,0,11,-1385.26,8542.59,11.2687,0,5000,0,''),
(18210,0,12,-1329.9,8513.73,12.8272,0,0,0,''),
(18210,0,13,-1303.28,8482.24,14.9539,0,0,0,''),
(18210,0,14,-1278.47,8461.38,16.3372,0,0,0,''),
(18760,0,1,-2267.07,3091.46,13.8271,0,0,0,''),
(18760,0,2,-2270.92,3094.19,13.8271,0,0,0,''),
(18760,0,3,-2279.08,3100.04,13.8271,0,0,0,''),
(18760,0,4,-2290.05,3105.07,13.8271,0,0,0,''),
(18760,0,5,-2297.64,3112.32,13.8271,0,0,0,''),
(18760,0,6,-2303.89,3118.22,13.8231,0,10000,0,'building exit'),
(18760,0,7,-2307.77,3123.47,13.7257,0,0,0,''),
(18760,0,8,-2310.67,3126.2,12.5841,0,0,0,''),
(18760,0,9,-2311.48,3126.98,12.2769,0,0,0,''),
(18760,0,10,-2316.91,3132.13,11.9261,0,0,0,''),
(18760,0,11,-2320.43,3135.54,11.7436,0,0,0,''),
(18760,0,12,-2327.38,3139.36,10.9431,0,0,0,''),
(18760,0,13,-2332.02,3142.05,9.81277,0,0,0,''),
(18760,0,14,-2338.21,3145.32,9.31001,0,0,0,''),
(18760,0,15,-2343.1,3148.91,8.84879,0,0,0,''),
(18760,0,16,-2347.76,3153.15,7.71049,0,0,0,''),
(18760,0,17,-2351.04,3156.12,6.66476,0,0,0,''),
(18760,0,18,-2355.15,3163.18,5.11997,0,0,0,''),
(18760,0,19,-2359.01,3169.83,3.64343,0,0,0,''),
(18760,0,20,-2364.85,3176.81,2.32802,0,0,0,''),
(18760,0,21,-2368.77,3181.69,1.53285,0,0,0,''),
(18760,0,22,-2371.76,3185.11,0.979932,0,0,0,''),
(18760,0,23,-2371.85,3191.89,-0.293048,0,0,0,''),
(18760,0,24,-2370.99,3199.6,-1.10504,0,0,0,'turn left 1'),
(18760,0,25,-2376.24,3205.54,-1.04152,0,0,0,''),
(18760,0,26,-2380.99,3211.61,-1.16891,0,0,0,''),
(18760,0,27,-2384.04,3218.4,-1.15279,0,0,0,''),
(18760,0,28,-2385.41,3226.22,-1.23403,0,0,0,''),
(18760,0,29,-2386.02,3233.89,-1.31723,0,0,0,''),
(18760,0,30,-2384.7,3239.82,-1.51903,0,0,0,''),
(18760,0,31,-2382.98,3247.94,-1.39163,0,0,0,''),
(18760,0,32,-2379.68,3254.22,-1.25927,0,0,0,''),
(18760,0,33,-2375.27,3259.69,-1.22925,0,0,0,''),
(18760,0,34,-2369.62,3264.55,-1.1879,0,0,0,''),
(18760,0,35,-2364.01,3268.32,-1.48348,0,0,0,''),
(18760,0,36,-2356.61,3272.31,-1.5505,0,0,0,''),
(18760,0,37,-2352.3,3274.63,-1.35693,0,0,0,''),
(18760,0,38,-2348.54,3278.04,-1.04161,0,0,0,'turn left 2'),
(18760,0,39,-2347.56,3282.41,-0.75979,0,0,0,''),
(18760,0,40,-2348.29,3288.91,-0.63215,0,0,0,''),
(18760,0,41,-2349.68,3298.84,-1.07864,0,0,0,''),
(18760,0,42,-2351.15,3308.52,-1.38864,0,0,0,''),
(18760,0,43,-2352.2,3317.14,-1.59873,0,0,0,''),
(18760,0,44,-2351.59,3325.51,-1.92624,0,0,0,''),
(18760,0,45,-2350.88,3333.38,-2.32506,0,0,0,''),
(18760,0,46,-2350.05,3342.68,-2.51886,0,0,0,''),
(18760,0,47,-2350.12,3347.32,-2.57528,0,0,0,''),
(18760,0,48,-2348.72,3353.7,-2.72689,0,0,0,''),
(18760,0,49,-2346.53,3360.85,-2.9756,0,0,0,''),
(18760,0,50,-2344.83,3365.46,-3.3311,0,0,0,''),
(18760,0,51,-2342.68,3368.91,-3.74526,0,0,0,''),
(18760,0,52,-2340.25,3371.44,-4.10499,0,0,0,''),
(18760,0,53,-2337.4,3373.47,-4.44362,0,0,0,''),
(18760,0,54,-2332.68,3376.02,-5.19648,0,0,0,''),
(18760,0,55,-2326.69,3379.64,-6.24757,0,0,0,''),
(18760,0,56,-2321.2,3383.98,-7.28247,0,0,0,''),
(18760,0,57,-2317.81,3387.78,-8.40093,0,0,0,''),
(18760,0,58,-2315.3,3392.47,-9.63431,0,0,0,''),
(18760,0,59,-2314.69,3396.6,-10.2031,0,0,0,''),
(18760,0,60,-2315.48,3402.35,-10.8211,0,0,0,'gate'),
(18760,0,61,-2317.55,3409.27,-11.3309,0,5000,0,'Firewing point exit'),
(18760,0,62,-2320.69,3412.99,-11.5207,0,0,0,''),
(18760,0,63,-2326.88,3417.89,-11.6105,0,0,0,''),
(18760,0,64,-2332.73,3421.74,-11.5659,0,0,0,''),
(18760,0,65,-2337.23,3424.89,-11.496,0,0,0,''),
(18760,0,66,-2339.57,3429.17,-11.3782,0,0,0,''),
(18760,0,67,-2341.66,3435.86,-11.3746,0,5000,0,'Wave and transform'),
(18760,0,68,-2342.15,3443.94,-11.2562,0,2000,0,'final destination'),
(18887,0,0,2650.06,665.473,61.9305,0,0,0,''),
(18887,0,1,2652.44,670.761,61.937,0,0,0,''),
(18887,0,2,2655.96,676.913,57.1725,0,0,0,''),
(18887,0,3,2659.4,677.317,57.1725,0,0,0,''),
(18887,0,4,2651.75,664.482,57.1725,0,0,0,''),
(18887,0,5,2647.49,666.595,57.0824,0,0,0,''),
(18887,0,6,2644.37,668.167,55.4182,0,0,0,''),
(18887,0,7,2638.57,671.231,54.52,0,0,0,'start dialogue - escort paused'),
(18887,0,8,2636.56,679.894,54.6595,0,0,0,''),
(18887,0,9,2640.79,689.647,55.3215,0,0,0,''),
(18887,0,10,2639.35,706.777,56.0667,0,0,0,''),
(18887,0,11,2617.7,731.884,55.5571,0,0,0,''),
(19589,0,1,3358.22,3728.25,141.204,0,16000,0,''),
(19589,0,2,3368.05,3715.51,142.057,0,0,0,''),
(19589,0,3,3389.04,3701.21,144.648,0,0,0,''),
(19589,0,4,3419.51,3691.41,146.598,0,0,0,''),
(19589,0,5,3437.83,3699.2,147.235,0,0,0,''),
(19589,0,6,3444.85,3700.89,147.088,0,0,0,''),
(19589,0,7,3449.89,3700.14,148.118,0,12000,0,'first object'),
(19589,0,8,3443.55,3682.09,149.219,0,0,0,''),
(19589,0,9,3452.6,3674.65,150.226,0,0,0,''),
(19589,0,10,3462.6,3659.01,152.436,0,0,0,''),
(19589,0,11,3469.18,3649.47,153.178,0,0,0,''),
(19589,0,12,3475.11,3639.41,157.213,0,0,0,''),
(19589,0,13,3482.26,3617.69,159.126,0,0,0,''),
(19589,0,14,3492.7,3606.27,156.419,0,0,0,''),
(19589,0,15,3493.52,3595.06,156.581,0,0,0,''),
(19589,0,16,3490.4,3588.45,157.764,0,0,0,''),
(19589,0,17,3485.21,3585.69,159.979,0,12000,0,'second object'),
(19589,0,18,3504.68,3594.44,152.862,0,0,0,''),
(19589,0,19,3523.6,3594.48,145.393,0,0,0,''),
(19589,0,20,3537.01,3576.71,135.748,0,0,0,''),
(19589,0,21,3551.73,3573.12,128.013,0,0,0,''),
(19589,0,22,3552.12,3614.08,127.847,0,0,0,''),
(19589,0,23,3536.14,3639.78,126.031,0,0,0,''),
(19589,0,24,3522.94,3646.47,131.989,0,0,0,''),
(19589,0,25,3507.21,3645.69,138.153,0,0,0,''),
(19589,0,26,3485.15,3645.64,137.755,0,0,0,''),
(19589,0,27,3472.18,3633.88,140.352,0,0,0,''),
(19589,0,28,3435.34,3613.69,140.725,0,0,0,''),
(19589,0,29,3417.4,3612.4,141.143,0,12000,0,'third object'),
(19589,0,30,3411.04,3621.14,142.454,0,0,0,''),
(19589,0,31,3404.47,3636.89,144.434,0,0,0,''),
(19589,0,32,3380.55,3657.06,144.332,0,0,0,''),
(19589,0,33,3375,3676.86,145.298,0,0,0,''),
(19589,0,34,3388.87,3685.48,146.818,0,0,0,''),
(19589,0,35,3393.99,3699.4,144.858,0,0,0,''),
(19589,0,36,3354.95,3726.02,141.428,0,0,0,''),
(19589,0,37,3351.4,3722.33,141.4,0,0,0,'home position'),
(19671,0,0,-362.876,-71.333,-0.96,0,5000,0,'SAY_ESCORT_START'),
(19671,0,1,-372.647,-88.728,-0.958,0,0,0,''),
(19671,0,2,-373.163,-114.959,-0.958,0,0,0,''),
(19671,0,3,-373.137,-138.439,-0.958,0,0,0,''),
(19671,0,4,-373.687,-152.964,-0.958,0,0,0,''),
(19671,0,5,-379.091,-158.089,-0.958,0,0,0,''),
(19671,0,6,-381.149,-164.796,-0.958,0,0,0,''),
(19671,0,7,-375.292,-164.111,0.715,0,0,0,'SAY_FIRST_STOP - escort paused'),
(19671,0,8,-375.292,-164.111,0.715,0,1000,0,'SAY_FIRST_STOP_COMPLETE'),
(19671,0,9,-381.149,-164.796,-0.958,0,0,0,''),
(19671,0,10,-374.292,-193.614,-0.967,0,0,0,''),
(19671,0,11,-370.799,-217.796,-0.959,0,0,0,''),
(19671,0,12,-344.132,-222.647,-0.959,0,0,0,''),
(19671,0,13,-310.88,-219.357,-0.945,0,9000,0,'SAY_COLLECTOR_SEARCH'),
(19671,0,14,-299.879,-201.809,-1.181,0,0,0,''),
(19671,0,15,-285.874,-187.791,-0.694,0,0,0,''),
(19671,0,16,-271.884,-164.856,-1.912,0,0,0,''),
(19671,0,17,-260.729,-159.094,-1.19,0,0,0,'SAY_SECOND_STOP - escort paused'),
(19671,0,18,-244.372,-163.136,-0.924,0,0,0,''),
(19671,0,19,-236.428,-185.952,-0.953,0,0,0,''),
(19671,0,20,-210.659,-206.71,0.906,0,0,0,''),
(19671,0,21,-193.375,-219.378,-0.518,0,0,0,''),
(19671,0,22,-171.121,-223.043,-0.955,0,0,0,''),
(19671,0,23,-148.658,-221.031,-0.77,0,0,0,''),
(19671,0,24,-128.15,-215.657,-0.187,0,0,0,''),
(19671,0,25,-93.429,-219.264,-1.32,0,0,0,''),
(19671,0,26,-72.886,-222.278,-0.184,0,0,0,'SAY_THIRD_STOP - escort paused'),
(19671,0,27,-42.343,-224.004,-0.268,0,0,0,''),
(19671,0,28,-15.603,-223.78,0.793,0,0,0,''),
(19671,0,29,-12.975,-223.157,1.811,0,42000,0,'SAY_REST'),
(19671,0,30,-12.975,-223.157,1.811,0,5000,0,'SAY_BREAK_OVER'),
(19671,0,31,-14.898,-222.906,0.786,0,0,0,''),
(19671,0,32,-44.684,-221.592,-0.146,0,0,0,''),
(19671,0,33,-59.746,-211.847,0.216,0,0,0,''),
(19671,0,34,-63.1,-195.288,-0.615,0,0,0,''),
(19671,0,35,-63.218,-191.959,-1.725,0,0,0,''),
(19671,0,36,-67.063,-160.281,-0.955,0,0,0,''),
(19671,0,37,-67.888,-128.704,-1.226,0,0,0,''),
(19671,0,38,-68.226,-107.766,-0.289,0,0,0,''),
(19671,0,39,-68.251,-105.624,-1.631,0,0,0,''),
(19671,0,40,-66.342,-88.147,-1.167,0,0,0,'SAY_XIRAXIS_SPAWN - escort paused'),
(19671,0,41,-67.831,-78.571,-2.114,0,0,0,''),
(19671,0,42,-67.692,-76.665,-0.941,0,0,0,''),
(19671,0,43,-67.624,-56.025,-0.844,0,0,0,'quest complete'),
(19671,0,44,-64.493,-15.776,-0.943,0,0,0,''),
(19685,0,0,-1860.54,5416.99,-10.48,0,2500,0,''),
(19685,0,1,-1855.9,5412.81,-12.427,0,0,0,'SAY_KHAD_SERV_0'),
(19685,0,2,-1845.52,5385.35,-12.427,0,0,0,''),
(19685,0,3,-1815.25,5340.26,-12.427,0,0,0,''),
(19685,0,4,-1799.34,5312.78,-12.427,0,0,0,''),
(19685,0,5,-1780.49,5278.54,-33.877,0,2500,0,'pause'),
(19685,0,6,-1776.06,5270.25,-38.809,0,0,0,''),
(19685,0,7,-1772.22,5262.78,-38.81,0,0,0,''),
(19685,0,8,-1762.2,5261.72,-38.85,0,0,0,''),
(19685,0,9,-1759.24,5259.75,-40.208,0,0,0,''),
(19685,0,10,-1743.43,5259.66,-40.208,0,0,0,''),
(19685,0,11,-1744.36,5251.18,-44.523,0,0,0,''),
(19685,0,12,-1740.12,5240.12,-47.74,0,0,0,''),
(19685,0,13,-1737.64,5238.29,-49.793,0,0,0,''),
(19685,0,14,-1727.41,5233.87,-50.477,0,0,0,''),
(19685,0,15,-1707.49,5230.44,-51.05,0,0,0,''),
(19685,0,16,-1684.12,5223.63,-49.415,0,0,0,''),
(19685,0,17,-1669.97,5221.93,-46.336,0,0,0,''),
(19685,0,18,-1662.87,5221.71,-44.959,0,0,0,''),
(19685,0,19,-1657.17,5225.21,-45.708,0,0,0,''),
(19685,0,20,-1645.03,5238.36,-40.212,0,0,0,''),
(19685,0,21,-1631.66,5252.76,-40.962,0,0,0,''),
(19685,0,22,-1631.37,5276.54,-41.032,0,0,0,''),
(19685,0,23,-1621.73,5298.55,-40.209,0,0,0,''),
(19685,0,24,-1615.5,5298.1,-40.209,0,2500,0,'pause'),
(19685,0,25,-1636.98,5302.68,-40.209,0,0,0,''),
(19685,0,26,-1655.33,5315.74,-40.207,0,0,0,''),
(19685,0,27,-1656.88,5321.65,-40.209,0,0,0,''),
(19685,0,28,-1663.98,5335.21,-46.526,0,0,0,''),
(19685,0,29,-1659.14,5359.13,-45.846,0,0,0,''),
(19685,0,30,-1644.21,5390.89,-45.542,0,0,0,''),
(19685,0,31,-1646.18,5405.27,-44.649,0,0,0,''),
(19685,0,32,-1650.2,5414.54,-46.324,0,0,0,''),
(19685,0,33,-1656.05,5424.68,-40.461,0,0,0,''),
(19685,0,34,-1661.63,5423.93,-40.405,0,0,0,''),
(19685,0,35,-1664.65,5423.66,-38.848,0,0,0,''),
(19685,0,36,-1681.77,5426,-38.809,0,0,0,''),
(19685,0,37,-1729.79,5427.25,-12.445,0,0,0,''),
(19685,0,38,-1735.37,5423.66,-12.427,0,0,0,''),
(19685,0,39,-1741.63,5386.77,-12.427,0,0,0,''),
(19685,0,40,-1764.79,5363.74,-12.427,0,0,0,''),
(19685,0,41,-1816.37,5340.66,-12.427,0,0,0,''),
(19685,0,42,-1880.02,5309.8,-12.427,0,0,0,''),
(19685,0,43,-1887.37,5315.43,-12.427,0,0,0,''),
(19685,0,44,-1888.77,5324.52,-5.146,0,0,0,''),
(19685,0,45,-1888.4,5334.15,0.151,0,0,0,''),
(19685,0,46,-1890.22,5337.66,0.921,0,0,0,''),
(19685,0,47,-1897.54,5323.04,1.256,0,0,0,''),
(19685,0,48,-1900.25,5319.8,0.831,0,0,0,''),
(19685,0,49,-1910.04,5291.26,1.288,0,0,0,''),
(19685,0,50,-1915.22,5275.57,2.502,0,2500,0,'pause'),
(19685,0,51,-1927.23,5273.25,2.703,0,0,0,''),
(19685,0,52,-1926.98,5278.47,0.109,0,0,0,''),
(19685,0,53,-1927.67,5299.21,-12.427,0,0,0,''),
(19685,0,54,-1922.84,5319.26,-12.427,0,0,0,''),
(19685,0,55,-1925.78,5347.41,-12.427,0,0,0,''),
(19685,0,56,-1954.91,5384.23,-12.427,0,0,0,''),
(19685,0,57,-1966.73,5428.2,-12.427,0,0,0,''),
(19685,0,58,-1979.48,5448.42,-12.427,0,0,0,''),
(19685,0,59,-1977.53,5453.86,-12.385,0,0,0,''),
(19685,0,60,-1968.06,5455.78,-4.343,0,0,0,''),
(19685,0,61,-1959.22,5454.9,0.202,0,0,0,''),
(19685,0,62,-1954.63,5457.01,0.9,0,0,0,''),
(19685,0,63,-1967.76,5464.95,1.22,0,2500,0,'pause'),
(19685,0,64,-1952.87,5462.96,0.956,0,0,0,''),
(19685,0,65,-1955.34,5467.12,0.445,0,0,0,''),
(19685,0,66,-1962.03,5472.8,-4.243,0,0,0,''),
(19685,0,67,-1968.01,5480.91,-12.427,0,0,0,''),
(19685,0,68,-1945.9,5515.95,-12.427,0,0,0,''),
(19685,0,69,-1874.87,5549.78,-12.427,0,0,0,''),
(19685,0,70,-1840.64,5544.23,-12.427,0,0,0,''),
(19685,0,71,-1838.96,5536.06,-5.639,0,0,0,''),
(19685,0,72,-1839.58,5525.63,0.193,0,0,0,''),
(19685,0,73,-1837.93,5521.12,0.844,0,0,0,''),
(19685,0,74,-1829.18,5533.43,1.209,0,2500,0,'pause'),
(19685,0,75,-1848.4,5476.07,0.856,0,40000,0,'end'),
(20129,0,0,-8374.93,-4250.21,-204.38,0,5000,0,''),
(20129,0,1,-8374.93,-4250.21,-204.38,0,16000,0,''),
(20129,0,2,-8374.93,-4250.21,-204.38,0,10000,0,''),
(20129,0,3,-8374.93,-4250.21,-204.38,0,2000,0,''),
(20129,0,4,-8439.4,-4180.05,-209.25,0,0,0,''),
(20129,0,5,-8437.82,-4120.84,-208.59,0,10000,0,''),
(20129,0,6,-8437.82,-4120.84,-208.59,0,16000,0,''),
(20129,0,7,-8437.82,-4120.84,-208.59,0,13000,0,''),
(20129,0,8,-8437.82,-4120.84,-208.59,0,18000,0,''),
(20129,0,9,-8437.82,-4120.84,-208.59,0,15000,0,''),
(20129,0,10,-8437.82,-4120.84,-208.59,0,2000,0,''),
(20129,0,11,-8467.26,-4198.63,-214.21,0,0,0,''),
(20129,0,12,-8667.76,-4252.13,-209.56,0,0,0,''),
(20129,0,13,-8703.71,-4234.58,-209.5,0,14000,0,''),
(20129,0,14,-8703.71,-4234.58,-209.5,0,2000,0,''),
(20129,0,15,-8642.81,-4304.37,-209.57,0,0,0,''),
(20129,0,16,-8649.06,-4394.36,-208.46,0,6000,0,''),
(20129,0,17,-8649.06,-4394.36,-208.46,0,18000,0,''),
(20129,0,18,-8649.06,-4394.36,-208.46,0,2000,0,''),
(20129,0,19,-8468.72,-4437.67,-215.45,0,0,0,''),
(20129,0,20,-8427.54,-4426,-211.13,0,0,0,''),
(20129,0,21,-8364.83,-4393.32,-205.91,0,0,0,''),
(20129,0,22,-8304.54,-4357.2,-208.2,0,18000,0,''),
(20129,0,23,-8304.54,-4357.2,-208.2,0,2000,0,''),
(20129,0,24,-8375.42,-4250.41,-205.14,0,5000,0,''),
(20129,0,25,-8375.42,-4250.41,-205.14,0,5000,0,''),
(20281,0,0,3096.42,2801.41,118.149,0,7000,0,'SAY_DRIJYA_START'),
(20281,0,1,3096.52,2801.06,118.128,0,0,0,'SAY_DRIJYA_1'),
(20281,0,2,3100,2796.67,118.118,0,0,0,''),
(20281,0,3,3098.76,2786.17,117.125,0,0,0,''),
(20281,0,4,3087.79,2754.6,115.441,0,0,0,''),
(20281,0,5,3080.72,2730.79,115.93,0,9000,0,'SAY_DRIJYA_2'),
(20281,0,6,3060.24,2731.31,115.122,0,0,0,''),
(20281,0,7,3050.9,2727.82,114.127,0,0,0,''),
(20281,0,8,3050.9,2727.82,114.127,0,8000,0,'SAY_DRIJYA_4'),
(20281,0,9,3055.01,2724.97,113.687,0,0,0,''),
(20281,0,10,3053.78,2718.43,113.684,0,0,0,''),
(20281,0,11,3028.62,2693.38,114.67,0,0,0,''),
(20281,0,12,3022.43,2695.3,113.406,0,0,0,''),
(20281,0,13,3022.43,2695.3,113.406,0,8000,0,'SAY_DRIJYA_5'),
(20281,0,14,3025.46,2700.75,113.514,0,0,0,''),
(20281,0,15,3011.34,2716.78,113.691,0,0,0,''),
(20281,0,16,3010.88,2726.99,114.239,0,0,0,''),
(20281,0,17,3009.18,2729.08,114.324,0,0,0,''),
(20281,0,18,3009.18,2729.08,114.324,0,15000,0,'SAY_DRIJYA_6'),
(20281,0,19,3009.18,2729.08,114.324,0,6000,0,'SPELL_EXPLOSION_VISUAL'),
(20281,0,20,3009.18,2729.08,114.324,0,8000,0,'SAY_DRIJYA_7'),
(20281,0,21,3033.89,2736.44,114.369,0,0,0,''),
(20281,0,22,3071.49,2741.5,116.462,0,0,0,''),
(20281,0,23,3087.79,2754.6,115.441,0,0,0,''),
(20281,0,24,3094.5,2770.2,115.744,0,0,0,''),
(20281,0,25,3103.51,2784.36,116.857,0,0,0,''),
(20281,0,26,3100,2796.67,118.118,0,0,0,''),
(20281,0,27,3096.29,2801.03,118.096,0,0,0,'SAY_DRIJYA_COMPLETE'),
(20415,0,0,2488.77,2184.89,104.64,0,0,0,''),
(20415,0,1,2478.72,2184.77,98.58,0,0,0,''),
(20415,0,2,2473.52,2184.71,99,0,0,0,''),
(20415,0,3,2453.15,2184.96,97.09,0,4000,0,''),
(20415,0,4,2424.18,2184.15,94.11,0,0,0,''),
(20415,0,5,2413.18,2184.15,93.42,0,0,0,''),
(20415,0,6,2402.02,2183.9,87.59,0,0,0,''),
(20415,0,7,2333.31,2181.63,90.03,0,4000,0,''),
(20415,0,8,2308.73,2184.34,92.04,0,0,0,''),
(20415,0,9,2303.1,2196.89,94.94,0,0,0,''),
(20415,0,10,2304.58,2272.23,96.67,0,0,0,''),
(20415,0,11,2297.09,2271.4,95.16,0,0,0,''),
(20415,0,12,2297.68,2266.79,95.07,0,4000,0,''),
(20415,0,13,2297.67,2266.76,95.07,0,4000,0,''),
(20763,0,0,4084.09,2297.25,110.277,0,0,0,''),
(20763,0,1,4107.17,2294.92,106.625,0,0,0,''),
(20763,0,2,4154.13,2296.79,102.331,0,0,0,''),
(20763,0,3,4166.02,2302.82,103.422,0,0,0,''),
(20763,0,4,4195.04,2301.09,113.786,0,0,0,''),
(20763,0,5,4205.25,2297.12,117.992,0,0,0,''),
(20763,0,6,4230.43,2294.64,127.307,0,0,0,''),
(20763,0,7,4238.98,2293.58,129.332,0,0,0,''),
(20763,0,8,4250.18,2293.27,129.009,0,0,0,''),
(20763,0,9,4262.81,2290.77,126.485,0,0,0,''),
(20763,0,10,4265.85,2278.56,128.235,0,0,0,''),
(20763,0,11,4265.61,2265.73,128.452,0,0,0,''),
(20763,0,12,4258.84,2245.35,132.804,0,0,0,''),
(20763,0,13,4247.98,2221.21,137.668,0,0,0,''),
(20763,0,14,4247.97,2213.88,137.721,0,0,0,''),
(20763,0,15,4249.88,2204.26,137.121,0,4000,0,''),
(20763,0,16,4249.88,2204.26,137.121,0,0,0,'SAY_VANGUARD_FINISH'),
(20763,0,17,4252.46,2170.89,137.677,0,3000,0,'EMOTE_VANGUARD_FINISH'),
(20763,0,18,4252.46,2170.89,137.677,0,5000,0,''),
(20802,0,0,4017.86,2325.04,114.029,0,3000,0,'SAY_INTRO'),
(20802,0,1,4006.37,2324.59,111.455,0,0,0,''),
(20802,0,2,3998.39,2326.36,113.164,0,0,0,''),
(20802,0,3,3982.31,2330.26,113.846,0,7000,0,'SAY_STAGING_GROUNDS'),
(20802,0,4,3950.65,2329.25,113.924,0,0,0,'SAY_TOXIC_HORROR'),
(20802,0,5,3939.23,2330.99,112.197,0,0,0,''),
(20802,0,6,3927.86,2333.64,111.33,0,0,0,''),
(20802,0,7,3917.85,2337.7,113.493,0,0,0,''),
(20802,0,8,3907.74,2343.34,114.062,0,0,0,''),
(20802,0,9,3878.76,2378.61,114.037,0,8000,0,'SAY_SALHADAAR'),
(20802,0,10,3863.15,2355.88,114.987,0,0,0,''),
(20802,0,11,3861.24,2344.89,115.201,0,0,0,''),
(20802,0,12,3872.46,2323.11,114.671,0,0,0,'escort paused - SAY_DISRUPTOR'),
(20802,0,13,3863.74,2349.79,115.382,0,0,0,'SAY_FINISH_2'),
(21027,0,0,-2638.89,1358.96,35.9607,0,0,0,''),
(21027,0,1,-2652.62,1354.46,34.8615,0,0,0,''),
(21027,0,2,-2670.7,1348.18,34.446,0,0,0,''),
(21027,0,3,-2690.82,1339.95,34.446,0,0,0,''),
(21027,0,4,-2709.98,1330.77,34.446,0,0,0,''),
(21027,0,5,-2727.74,1322.39,33.3863,0,0,0,''),
(21027,0,6,-2742.53,1314.21,33.6043,0,0,0,''),
(21027,0,7,-2750.69,1308.32,33.5114,0,0,0,''),
(21027,0,8,-2758.5,1290.76,33.2167,0,0,0,'spawn assassin'),
(21027,0,9,-2755.04,1280.85,33.4304,0,0,0,''),
(21027,0,10,-2747.99,1268.58,33.1957,0,0,0,''),
(21027,0,11,-2741.46,1257.92,33.082,0,0,0,''),
(21027,0,12,-2732.63,1245.35,33.6119,0,0,0,''),
(21027,0,13,-2724.68,1235.12,33.3635,0,15000,0,'SAY_WIL_PROGRESS1'),
(21027,0,14,-2724.68,1235.12,33.3635,0,6000,0,'SAY_WIL_FIND_EXIT'),
(21027,0,15,-2746.38,1266.39,33.192,0,0,0,'spawn assassin'),
(21027,0,16,-2746.38,1266.39,33.192,0,0,0,''),
(21027,0,17,-2758.93,1285.13,33.3417,0,0,0,''),
(21027,0,18,-2761.85,1292.31,33.209,0,0,0,''),
(21027,0,19,-2758.87,1300.68,33.2853,0,0,0,''),
(21027,0,20,-2753.93,1307.76,33.4525,0,0,0,''),
(21027,0,21,-2738.61,1316.19,33.483,0,0,0,''),
(21027,0,22,-2727.9,1320.01,33.3811,0,0,0,''),
(21027,0,23,-2709.46,1315.74,33.3018,0,0,0,''),
(21027,0,24,-2704.66,1301.62,32.4633,0,0,0,''),
(21027,0,25,-2704.12,1298.92,32.7682,0,0,0,''),
(21027,0,26,-2691.8,1292.85,33.8526,0,0,0,'spawn assassin'),
(21027,0,27,-2682.88,1288.85,32.9954,0,0,0,''),
(21027,0,28,-2661.87,1279.68,26.6868,0,0,0,''),
(21027,0,29,-2648.94,1270.27,24.1475,0,0,0,''),
(21027,0,30,-2642.51,1262.94,23.5124,0,0,0,'spawn assassin'),
(21027,0,31,-2636.98,1252.43,20.4183,0,0,0,''),
(21027,0,32,-2648.11,1224.98,8.69182,0,0,0,'spawn assassin'),
(21027,0,33,-2658.39,1200.14,5.49224,0,0,0,''),
(21027,0,34,-2668.5,1190.45,3.12741,0,0,0,''),
(21027,0,35,-2685.93,1174.36,5.16392,0,0,0,''),
(21027,0,36,-2701.61,1160.03,5.61131,0,0,0,''),
(21027,0,37,-2714.66,1149.98,4.34237,0,0,0,''),
(21027,0,38,-2721.44,1145,1.91347,0,0,0,''),
(21027,0,39,-2733.96,1143.44,2.62041,0,0,0,'spawn assassin'),
(21027,0,40,-2757.88,1146.94,6.184,0,2000,0,'SAY_WIL_JUST_AHEAD'),
(21027,0,41,-2772.3,1166.05,6.33181,0,0,0,''),
(21027,0,42,-2790.27,1189.94,5.20796,0,0,0,''),
(21027,0,43,-2805.45,1208.66,5.55762,0,0,0,'spawn assassin'),
(21027,0,44,-2820.62,1225.87,6.2661,0,0,0,''),
(21027,0,45,-2831.93,1237.73,5.80851,0,0,0,''),
(21027,0,46,-2842.58,1252.87,6.80748,0,0,0,''),
(21027,0,47,-2846.34,1258.73,7.38617,0,0,0,''),
(21027,0,48,-2847.56,1266.77,8.20879,0,0,0,''),
(21027,0,49,-2841.65,1285.81,7.93322,0,0,0,''),
(21027,0,50,-2841.75,1289.83,6.9903,0,0,0,''),
(21027,0,51,-2861.97,1298.77,6.80733,0,0,0,'spawn assassin'),
(21027,0,52,-2871.4,1302.35,6.80733,0,7500,0,'SAY_WIL_END'),
(22377,0,0,-2770.46,5418.41,-34.538,0,0,0,''),
(22377,0,1,-2778.18,5416.25,-34.538,0,0,0,''),
(22377,0,2,-2816.96,5414.94,-34.529,0,0,0,''),
(22377,0,3,-2827.53,5414.74,-28.265,0,0,0,''),
(22377,0,4,-2841.61,5413.02,-28.261,0,0,0,''),
(22377,0,5,-2863.61,5411.96,-28.262,0,1000,0,'SAY_AKU_AMBUSH_A'),
(22377,0,6,-2874.56,5413.8,-28.26,0,0,0,''),
(22377,0,7,-2878.78,5413.81,-28.261,0,0,0,''),
(22377,0,8,-2892.59,5413.48,-18.784,0,0,0,''),
(22377,0,9,-2896.04,5413.14,-18.589,0,0,0,''),
(22377,0,10,-2896.32,5409.43,-18.45,0,0,0,''),
(22377,0,11,-2896,5396.91,-8.855,0,0,0,''),
(22377,0,12,-2895.73,5386.62,-9.26,0,0,0,''),
(22377,0,13,-2895.32,5367.61,-9.456,0,0,0,''),
(22377,0,14,-2890.31,5353.88,-11.28,0,1000,0,'SAY_AKU_AMBUSH_B'),
(22377,0,15,-2880.42,5334.63,-10.629,0,0,0,''),
(22377,0,16,-2866.39,5314.25,-9.678,0,0,0,''),
(22377,0,17,-2864.75,5277.73,-11.087,0,0,0,''),
(22377,0,18,-2856.33,5255.9,-11.496,0,5000,0,'SAY_AKU_COMPLETE'),
(22424,0,1,-3620.54,4164.57,1.81,0,0,0,'SKYWING_START'),
(22424,0,2,-3624.78,4149.65,7.44,0,0,0,''),
(22424,0,3,-3630.3,4124.84,21.28,0,0,0,''),
(22424,0,4,-3629.14,4093.65,44.35,0,0,0,''),
(22424,0,5,-3626.34,4080.29,52.39,0,0,0,''),
(22424,0,6,-3619.35,4063.86,60.86,0,3000,0,'SAY_SKYWING_TREE_DOWN'),
(22424,0,7,-3615.09,4054.17,62.46,0,0,0,''),
(22424,0,8,-3611.39,4046.6,65.07,0,0,0,''),
(22424,0,9,-3606.68,4040.5,66,0,0,0,''),
(22424,0,10,-3600.88,4038.69,67.14,0,0,0,''),
(22424,0,11,-3597.88,4033.84,68.53,0,0,0,''),
(22424,0,12,-3602.19,4027.89,69.36,0,0,0,''),
(22424,0,13,-3609.85,4028.37,70.78,0,0,0,''),
(22424,0,14,-3613.01,4031.1,72.14,0,0,0,''),
(22424,0,15,-3613.18,4035.63,73.52,0,0,0,''),
(22424,0,16,-3609.84,4039.73,75.25,0,0,0,''),
(22424,0,17,-3604.55,4040.12,77.01,0,0,0,''),
(22424,0,18,-3600.61,4036.03,78.84,0,0,0,''),
(22424,0,19,-3602.63,4029.99,81.01,0,0,0,''),
(22424,0,20,-3608.87,4028.64,83.27,0,0,0,''),
(22424,0,21,-3612.53,4032.74,85.24,0,0,0,''),
(22424,0,22,-3611.08,4038.13,87.31,0,0,0,''),
(22424,0,23,-3605.09,4039.35,89.55,0,0,0,''),
(22424,0,24,-3601.87,4035.44,91.64,0,0,0,''),
(22424,0,25,-3603.08,4030.58,93.66,0,0,0,''),
(22424,0,26,-3608.47,4029.23,95.91,0,0,0,''),
(22424,0,27,-3611.68,4033.35,98.09,0,0,0,''),
(22424,0,28,-3609.51,4038.25,100.45,0,0,0,''),
(22424,0,29,-3604.54,4038.01,102.72,0,0,0,''),
(22424,0,30,-3602.4,4033.48,105.12,0,0,0,''),
(22424,0,31,-3606.17,4029.69,107.63,0,0,0,''),
(22424,0,32,-3609.93,4031.26,109.53,0,0,0,''),
(22424,0,33,-3609.38,4035.86,110.67,0,0,0,''),
(22424,0,34,-3603.58,4043.03,112.89,0,0,0,''),
(22424,0,35,-3600.99,4046.49,111.81,0,0,0,''),
(22424,0,36,-3602.32,4051.77,111.81,0,3000,0,'SAY_SKYWING_TREE_UP'),
(22424,0,37,-3609.55,4055.95,112,0,0,0,''),
(22424,0,38,-3620.93,4043.77,111.99,0,0,0,''),
(22424,0,39,-3622.44,4038.95,111.99,0,0,0,''),
(22424,0,40,-3621.64,4025.39,111.99,0,0,0,''),
(22424,0,41,-3609.62,4015.2,111.99,0,0,0,''),
(22424,0,42,-3598.37,4017.72,111.99,0,0,0,''),
(22424,0,43,-3590.21,4026.62,111.99,0,0,0,''),
(22424,0,44,-3586.55,4034.13,112,0,0,0,''),
(22424,0,45,-3580.39,4033.46,112,0,0,0,''),
(22424,0,46,-3568.83,4032.53,107.16,0,0,0,''),
(22424,0,47,-3554.81,4031.23,105.31,0,0,0,''),
(22424,0,48,-3544.39,4030.1,106.58,0,0,0,''),
(22424,0,49,-3531.91,4029.25,111.7,0,0,0,''),
(22424,0,50,-3523.5,4030.24,112.47,0,0,0,''),
(22424,0,51,-3517.48,4037.42,112.66,0,0,0,''),
(22424,0,52,-3510.4,4040.77,112.92,0,0,0,''),
(22424,0,53,-3503.83,4041.35,113.17,0,0,0,''),
(22424,0,54,-3498.31,4040.65,113.11,0,0,0,''),
(22424,0,55,-3494.05,4031.67,113.11,0,0,0,''),
(22424,0,56,-3487.71,4025.58,113.12,0,0,0,''),
(22424,0,57,-3500.42,4012.93,113.11,0,0,0,''),
(22424,0,58,-3510.86,4010.15,113.1,0,0,0,''),
(22424,0,59,-3518.07,4008.62,112.97,0,0,0,''),
(22424,0,60,-3524.74,4014.55,112.41,0,2000,0,'SAY_SKYWING_JUMP'),
(22424,0,61,-3530.5,4011.11,110.23,0,0,0,''),
(22424,0,62,-3541.68,4011.25,99.732,0,0,0,''),
(22424,0,63,-3537.81,4008.59,92.53,0,0,0,''),
(22424,0,64,-3546.25,4008.81,92.79,0,0,0,''),
(22424,0,65,-3552.07,4006.48,92.84,0,0,0,''),
(22424,0,66,-3556.29,4000.14,92.92,0,0,0,''),
(22424,0,67,-3556.16,3991.24,92.92,0,0,0,''),
(22424,0,68,-3551.48,3984.28,92.91,0,0,0,''),
(22424,0,69,-3542.9,3981.64,92.91,0,0,0,''),
(22424,0,70,-3534.82,3983.98,92.92,0,0,0,''),
(22424,0,71,-3530.58,3989.91,92.85,0,0,0,''),
(22424,0,72,-3529.85,3998.77,92.59,0,0,0,''),
(22424,0,73,-3534.15,4008.45,92.34,0,0,0,''),
(22424,0,74,-3532.87,4012.97,91.64,0,0,0,''),
(22424,0,75,-3530.57,4023.42,86.82,0,0,0,''),
(22424,0,76,-3528.24,4033.91,85.69,0,0,0,''),
(22424,0,77,-3526.22,4043.75,87.26,0,0,0,''),
(22424,0,78,-3523.84,4054.29,92.42,0,0,0,''),
(22424,0,79,-3522.44,4059.06,92.92,0,0,0,''),
(22424,0,80,-3514.26,4060.72,92.92,0,0,0,''),
(22424,0,81,-3507.76,4065.21,92.92,0,0,0,''),
(22424,0,82,-3503.24,4076.63,92.92,0,0,0,'SAY_SKYWING_SUMMON'),
(22424,0,83,-3504.23,4080.47,92.92,0,7000,0,'SPELL_TRANSFORM'),
(22424,0,84,-3504.23,4080.47,92.92,0,20000,0,'SAY_SKYWING_END'),
(22458,0,0,-3739.91,5393.69,-4.213,0,5000,0,'SAY_LE_KEEP_SAFE'),
(22458,0,1,-3733.33,5389.24,-5.331,0,0,0,''),
(22458,0,2,-3728.77,5385.65,-3.704,0,0,0,''),
(22458,0,3,-3717.27,5379.18,-4.4,0,0,0,''),
(22458,0,4,-3705.63,5379.26,-7.711,0,0,0,''),
(22458,0,5,-3688.28,5379.72,-9.4,0,0,0,''),
(22458,0,6,-3649.19,5389.11,-11.917,0,0,0,''),
(22458,0,7,-3612.79,5392.81,-13.655,0,0,0,''),
(22458,0,8,-3574.87,5412.7,-16.543,0,0,0,''),
(22458,0,9,-3564.44,5422.62,-16.104,0,0,0,''),
(22458,0,10,-3553.39,5444.73,-12.184,0,2500,0,'arivve dig site SAY_LE_ARRIVE'),
(22458,0,11,-3557.29,5465.32,-9.282,0,7500,0,'dig 1'),
(22458,0,12,-3548.1,5453.42,-12.282,0,10000,0,'dig 2 SAY_LE_BURIED pause'),
(22458,0,13,-3556.58,5446.48,-11.92,0,0,0,'start returning'),
(22458,0,14,-3564.44,5422.62,-16.104,0,0,0,''),
(22458,0,15,-3574.87,5412.7,-16.543,0,0,0,''),
(22458,0,16,-3612.79,5392.81,-13.655,0,0,0,''),
(22458,0,17,-3649.19,5389.11,-11.917,0,0,0,''),
(22458,0,18,-3688.28,5379.72,-9.4,0,0,0,''),
(22458,0,19,-3705.63,5379.26,-7.711,0,0,0,''),
(22458,0,20,-3717.27,5379.18,-4.4,0,0,0,''),
(22458,0,21,-3728.77,5385.65,-3.704,0,0,0,''),
(22458,0,22,-3733.33,5389.24,-5.331,0,0,0,''),
(22458,0,23,-3739.91,5393.69,-4.213,0,0,0,''),
(22861,0,0,-3567.673,390.162,31.162,0,0,0,''),
(22861,0,1,-3558.926,410.604,29.328,0,0,0,''),
(22861,0,2,-3569.454,408.951,29.623,0,0,0,''),
(22861,0,3,-3552.207,393.217,31.119,0,0,0,''),
(22861,0,4,-3565.558,398.519,30.333,0,0,0,''),
(22861,0,5,-3550.822,406.948,30.070,0,0,0,''),
(22861,0,6,-3573.805,401.071,30.696,0,0,0,''),
(22861,0,7,-3569.454,408.951,29.623,0,0,0,''),
(22861,0,8,-3560.967,404.486,29.785,0,0,0,''),
(22863,0,0,-3567.673,390.162,31.162,0,0,0,''),
(22863,0,1,-3558.926,410.604,29.328,0,0,0,''),
(22863,0,2,-3569.454,408.951,29.623,0,0,0,''),
(22863,0,3,-3552.207,393.217,31.119,0,0,0,''),
(22863,0,4,-3565.558,398.519,30.333,0,0,0,''),
(22863,0,5,-3550.822,406.948,30.070,0,0,0,''),
(22863,0,6,-3573.805,401.071,30.696,0,0,0,''),
(22863,0,7,-3569.454,408.951,29.623,0,0,0,''),
(22863,0,8,-3560.967,404.486,29.785,0,0,0,''),
(22864,0,0,-3567.673,390.162,31.162,0,0,0,''),
(22864,0,1,-3558.926,410.604,29.328,0,0,0,''),
(22864,0,2,-3569.454,408.951,29.623,0,0,0,''),
(22864,0,3,-3552.207,393.217,31.119,0,0,0,''),
(22864,0,4,-3565.558,398.519,30.333,0,0,0,''),
(22864,0,5,-3550.822,406.948,30.070,0,0,0,''),
(22864,0,6,-3573.805,401.071,30.696,0,0,0,''),
(22864,0,7,-3569.454,408.951,29.623,0,0,0,''),
(22864,0,8,-3560.967,404.486,29.785,0,0,0,''),
(22916,0,0,7461.49,-3121.06,438.21,0,7000,0,'SAY_START'),
(22916,0,1,7465.26,-3115.5,439.315,0,0,0,''),
(22916,0,2,7470.03,-3109.29,439.333,0,0,0,''),
(22916,0,3,7473.77,-3104.65,442.366,0,0,0,''),
(22916,0,4,7478.67,-3098.55,443.551,0,0,0,''),
(22916,0,5,7482.78,-3093.35,441.883,0,0,0,''),
(22916,0,6,7486.23,-3089.19,439.698,0,0,0,''),
(22916,0,7,7484.64,-3084.55,439.566,0,0,0,''),
(22916,0,8,7477.09,-3084.43,442.132,0,0,0,''),
(22916,0,9,7470.66,-3084.86,443.194,0,0,0,''),
(22916,0,10,7456.51,-3085.83,438.863,0,0,0,''),
(22916,0,11,7446,-3085.59,438.21,0,0,0,''),
(22916,0,12,7444.6,-3084.1,438.323,0,0,0,''),
(22916,0,13,7445.58,-3080.92,439.374,0,5000,0,'collect 1'),
(22916,0,14,7446.18,-3085.36,438.21,0,5000,0,'SAY_RELIC1'),
(22916,0,15,7453.9,-3086.69,439.454,0,0,0,''),
(22916,0,16,7459.41,-3085.5,439.158,0,0,0,''),
(22916,0,17,7465.9,-3085.01,442.329,0,0,0,''),
(22916,0,18,7472.8,-3084.81,443.085,0,0,0,''),
(22916,0,19,7480.58,-3084.56,440.642,0,0,0,''),
(22916,0,20,7484.59,-3084.71,439.568,0,0,0,''),
(22916,0,21,7491.81,-3090.55,440.052,0,0,0,''),
(22916,0,22,7497.13,-3095.34,437.505,0,0,0,''),
(22916,0,23,7496.61,-3113.62,434.554,0,0,0,''),
(22916,0,24,7501.79,-3123.79,435.347,0,0,0,''),
(22916,0,25,7506.6,-3130.78,434.179,0,0,0,''),
(22916,0,26,7504.53,-3133.46,435.579,0,5000,0,'collect 2'),
(22916,0,27,7505.2,-3130.03,434.151,0,15000,0,'SAY_RELIC2'),
(22916,0,28,7502.04,-3124.44,435.298,0,0,0,''),
(22916,0,29,7495.9,-3113.93,434.538,0,0,0,''),
(22916,0,30,7488.79,-3111.1,434.31,0,0,0,''),
(22916,0,31,7477.81,-3105.37,430.541,0,0,0,'summon'),
(22916,0,32,7471.49,-3092.55,429.006,0,0,0,''),
(22916,0,33,7472.35,-3062.72,428.341,0,0,0,''),
(22916,0,34,7472.26,-3054.92,427.15,0,0,0,''),
(22916,0,35,7475.03,-3053.39,428.672,0,5000,0,'collect 3'),
(22916,0,36,7472.4,-3057.21,426.87,0,5000,0,'SAY_RELIC3'),
(22916,0,37,7472.39,-3062.86,428.301,0,0,0,''),
(22916,0,38,7470.24,-3087.69,429.045,0,0,0,''),
(22916,0,39,7475.24,-3099.03,429.917,0,0,0,''),
(22916,0,40,7484.24,-3109.85,432.719,0,0,0,''),
(22916,0,41,7489.1,-3111.31,434.4,0,0,0,''),
(22916,0,42,7497.02,-3108.54,434.798,0,0,0,''),
(22916,0,43,7497.75,-3097.7,437.031,0,0,0,''),
(22916,0,44,7492.53,-3090.12,440.041,0,0,0,''),
(22916,0,45,7490.43,-3085.44,439.807,0,0,0,''),
(22916,0,46,7501.02,-3069.7,441.875,0,0,0,''),
(22916,0,47,7509.15,-3064.67,445.012,0,0,0,''),
(22916,0,48,7515.78,-3060.16,445.727,0,0,0,''),
(22916,0,49,7516.46,-3058.11,445.682,0,10000,0,'quest credit'),
(23002,0,0,3687.11,-3960.69,31.8726,0,0,0,''),
(23002,0,1,3676.28,-3953.76,29.9396,0,0,0,''),
(23002,0,2,3658.54,-3952.15,30.0414,0,0,0,''),
(23002,0,3,3628.91,-3956.9,29.405,0,0,0,''),
(23002,0,4,3602.54,-3968.16,31.511,0,0,0,''),
(23002,0,5,3564.96,-3978,30.3622,0,0,0,''),
(23002,0,6,3542.47,-3981.81,29.1465,0,0,0,''),
(23002,0,7,3511.34,-3981.25,30.2822,0,0,0,''),
(23002,0,8,3473.45,-3992.67,30.2861,0,0,0,''),
(23002,0,9,3439.1,-4006.73,29.2737,0,0,0,''),
(23002,0,10,3415.66,-4026.24,25.2498,0,0,0,''),
(23002,0,11,3380.88,-4045.38,26.3114,0,0,0,''),
(23002,0,12,3355.23,-4051.42,25.5665,0,0,0,''),
(23002,0,13,3312,-4055.65,28.3297,0,0,0,''),
(23002,0,14,3286.34,-4079.27,28.2464,0,0,0,''),
(23002,0,15,3260.68,-4087.29,31.4043,0,0,0,''),
(23002,0,16,3236.83,-4087.65,32.6894,0,0,0,''),
(23002,0,17,3215.06,-4082.1,32.4181,0,0,0,''),
(23002,0,18,3203.59,-4082.47,32.7436,0,0,0,''),
(23002,0,19,3166.41,-4062.09,33.2357,0,0,0,''),
(23002,0,20,3147.51,-4055.33,33.5683,0,0,0,''),
(23002,0,21,3125.41,-4050.01,34.61,0,0,0,''),
(23002,0,22,3121.16,-4045.07,36.5481,0,0,0,''),
(23002,0,23,3101.54,-4023.78,33.7169,0,0,0,''),
(23002,0,24,3094.16,-4016.89,33.8487,0,0,0,''),
(23002,0,25,3079.57,-4011.01,35.7546,0,0,0,''),
(23002,0,26,3058.83,-4001.71,34.3039,0,0,0,''),
(23002,0,27,3037.83,-3986.6,33.4216,0,0,0,''),
(23002,0,28,3016.93,-3970.83,33.3743,0,0,0,''),
(23002,0,29,2998.05,-3954.89,33.2338,0,0,0,''),
(23002,0,30,2969.35,-3929.27,33.4831,0,0,0,''),
(23002,0,31,2941.23,-3909.56,31.3506,0,0,0,''),
(23002,0,32,2911.42,-3895.07,32.095,0,0,0,''),
(23002,0,33,2892.44,-3875.52,30.8123,0,0,0,''),
(23002,0,34,2870.52,-3858.97,32.1977,0,0,0,''),
(23002,0,35,2865.84,-3836.99,32.1108,0,0,0,''),
(23002,0,36,2850.52,-3814.52,32.8635,0,0,0,''),
(23002,0,37,2836.63,-3796.94,33.1473,0,0,0,''),
(23002,0,38,2820.73,-3780.22,28.6916,0,0,0,''),
(23002,0,39,2795.82,-3770.13,30.1327,0,0,0,''),
(23002,0,40,2773.15,-3765.54,30.2947,0,0,0,''),
(23002,0,41,2742.31,-3761.65,30.1218,0,0,0,''),
(23002,0,42,2708.43,-3748.46,21.2468,0,0,0,''),
(23002,0,43,2661.45,-3741.11,21.9603,0,0,0,''),
(23002,0,44,2623.89,-3735.29,25.8979,0,0,0,''),
(23002,0,45,2585.93,-3728.85,28.5146,0,0,0,''),
(23002,0,46,2554.93,-3730.1,26.6795,0,0,0,''),
(23002,0,47,2538.68,-3721.28,28.1589,0,0,0,''),
(23002,0,48,2508.54,-3708.71,29.6718,0,0,0,''),
(23002,0,49,2474.69,-3710.37,31.0805,0,0,0,''),
(23002,0,50,2456.4,-3698.83,31.6187,0,0,0,''),
(23002,0,51,2430.54,-3701.87,31.0494,0,0,0,''),
(23002,0,52,2390.13,-3681.76,29.5484,0,0,0,''),
(23002,0,53,2357.06,-3673.96,29.8845,0,0,0,''),
(23002,0,54,2330.15,-3672.73,31.1314,0,0,0,''),
(23002,0,55,2302.77,-3665.22,29.411,0,0,0,''),
(23002,0,56,2279.24,-3659.46,29.6247,0,0,0,''),
(23002,0,57,2254.65,-3661.12,29.6984,0,0,0,''),
(23002,0,58,2223.32,-3654.92,31.0149,0,0,0,''),
(23002,0,59,2194.29,-3645.4,32.0417,0,0,0,''),
(23002,0,60,2153.05,-3650.82,31.2292,0,0,0,''),
(23002,0,61,2114.15,-3639.96,31.7371,0,0,0,''),
(23002,0,62,2093.68,-3646.65,31.3745,0,0,0,''),
(23002,0,63,2069.86,-3670.59,30.6172,0,0,0,''),
(23002,0,64,2024.4,-3677.64,29.7682,0,0,0,''),
(23002,0,65,1988.61,-3680.02,31.8937,0,0,0,''),
(23002,0,66,1962.68,-3692.17,32.7811,0,0,0,''),
(23002,0,67,1931.94,-3708.48,31.3641,0,0,0,''),
(23002,0,68,1893.36,-3710.02,33.0193,0,0,0,''),
(23002,0,69,1865.73,-3718.35,32.1664,0,0,0,''),
(23002,0,70,1839.74,-3732.92,32.5322,0,0,0,''),
(23002,0,71,1805.08,-3757.76,32.6295,0,0,0,''),
(23002,0,72,1780.24,-3775.53,30.5931,0,0,0,''),
(23002,0,73,1753.28,-3786.79,30.7445,0,0,0,''),
(23002,0,74,1731.09,-3796.64,36.8866,0,0,0,''),
(23089,0,0,660.22,305.74,271.688,0,0,0,'escort paused - GOSSIP_ITEM_PREPARE'),
(23089,0,1,675.1,343.3,271.688,0,0,0,''),
(23089,0,2,694.01,374.84,271.687,0,0,0,''),
(23089,0,3,706.22,375.75,274.888,0,0,0,''),
(23089,0,4,720.48,370.38,281.3,0,0,0,''),
(23089,0,5,733.3,357.66,292.477,0,0,0,''),
(23089,0,6,740.4,344.39,300.92,0,0,0,''),
(23089,0,7,747.54,329.03,308.509,0,0,0,''),
(23089,0,8,748.24,318.78,311.781,0,0,0,''),
(23089,0,9,752.41,304.31,312.077,0,0,0,'escort paused - SAY_AKAMA_OPEN_DOOR_1'),
(23089,0,10,770.27,304.89,312.35,0,0,0,''),
(23089,0,11,780.18,305.26,319.71,0,0,0,''),
(23089,0,12,791.45,289.27,319.8,0,0,0,''),
(23089,0,13,790.41,262.7,341.42,0,0,0,''),
(23089,0,14,782.88,250.2,341.6,0,0,0,''),
(23089,0,15,765.35,241.4,353.62,0,0,0,''),
(23089,0,16,750.61,235.63,353.02,0,0,0,'escort paused - GOSSIP_ITEM_START_EVENT'),
(23089,0,17,748.87,304.93,352.99,0,0,0,'escort paused - SAY_ILLIDAN_SPEECH_1'),
(23089,0,18,737.92,368.15,352.99,0,0,0,''),
(23089,0,19,749.64,378.69,352.99,0,0,0,''),
(23089,0,20,766.49,371.79,353.63,0,0,0,''),
(23089,0,21,784.98,361.89,341.41,0,0,0,''),
(23089,0,22,791.44,347.1,341.41,0,0,0,''),
(23089,0,23,794.8,319.47,319.75,0,0,0,''),
(23089,0,24,794.34,304.34,319.75,0,0,0,'escort paused - fight illidari elites'),
(23089,0,25,794.8,319.47,319.75,0,0,0,''),
(23089,0,26,791.44,347.1,341.41,0,0,0,''),
(23089,0,27,784.98,361.89,341.41,0,0,0,''),
(23089,0,28,766.49,371.79,353.63,0,0,0,''),
(23089,0,29,749.64,378.69,352.99,0,0,0,''),
(23089,0,30,737.92,368.15,352.99,0,0,0,'escort paused'),
(23340,0,0,-5100.367,646.988,86.75992,0,0,0,''),
(23340,0,1,-5098.652,661.8313,87.08841,0,0,0,''),
(23340,0,2,-5092.219,664.3353,87.73563,0,0,0,''),
(23340,0,3,-5081.346,664.3699,88.98929,0,0,0,'fly on'),
(23340,0,4,-5070.526,664.555,92.49088,0,0,0,''),
(23340,0,5,-5058.811,664.4887,96.62975,0,0,0,''),
(23340,0,6,-5046.153,664.4279,97.79643,0,0,0,'run on, cast Dragonmaw Knockdown: The Aggro Check Aura'),
(23340,0,7,-5021.002,664.601,115.265,0,0,0,''),
(23340,0,8,-4996.027,664.6683,115.2651,0,0,0,''),
(23340,0,9,-4957.755,673.371,115.2651,0,0,0,''),
(23340,0,10,-4922.072,686.9524,115.2651,0,0,0,''),
(23340,0,11,-4892.223,711.1226,115.2651,0,0,0,''),
(23340,0,12,-4899.887,760.2698,115.2651,0,0,0,''),
(23340,0,13,-4938.349,778.5325,115.2651,0,0,0,''),
(23340,0,14,-4971.547,797.5603,115.2651,0,0,0,''),
(23340,0,15,-5006.853,803.2005,115.2651,0,0,0,''),
(23340,0,16,-5052.229,803.8342,115.2651,0,0,0,''),
(23340,0,17,-5084.652,784.2522,115.2651,0,0,0,''),
(23340,0,18,-5112.79,768.5128,115.2651,0,0,0,''),
(23340,0,19,-5131.785,755.4612,115.2651,0,0,0,''),
(23340,0,20,-5156.098,731.316,115.2651,0,0,0,''),
(23340,0,21,-5151.251,703.8534,115.2651,0,0,0,''),
(23340,0,22,-5132.957,672.912,115.2651,0,0,0,''),
(23340,0,23,-5098.931,650.7557,115.2651,0,0,0,''),
(23340,0,24,-5062.084,634.9383,135.515,0,0,0,''),
(23340,0,25,-5027.877,621.5608,129.1817,0,0,0,''),
(23340,0,26,-5011.851,622.0031,127.8948,0,0,0,''),
(23340,0,27,-4977.219,627.5208,123.8948,0,0,0,''),
(23340,0,28,-4955.773,632.8429,106.7004,0,0,0,''),
(23340,0,29,-4959.098,655.7993,100.4226,0,0,0,''),
(23340,0,30,-4990.86,667.564,100.3392,0,0,0,''),
(23340,0,31,-5016.541,664.3353,95.70948,0,0,0,''),
(23340,0,32,-5030.557,664.4094,94.87615,0,0,0,''),
(23340,0,33,-5053.869,664.2513,91.20948,0,0,0,''),
(23340,0,34,-5076.172,664.1518,89.73725,0,0,0,'fly off, complete quest, SAY_MUCKJAW_FINISH'),
(23340,0,35,-5100.444,648.4188,86.75992,0,0,0,''),
(23340,0,36,-5088.555,640.8356,86.57706,1.48353,0,0,''),
(23342,0,0,-5094.403,632.7684,86.1046,0,0,0,''),
(23342,0,1,-5099.95,639.8563,86.36429,0,0,0,''),
(23342,0,2,-5098.756,659.2725,87.07596,0,0,0,''),
(23342,0,3,-5089.76,664.9246,88.03055,0,0,0,''),
(23342,0,4,-5077.378,664.5198,89.23929,0,0,0,'fly on, run on'),
(23342,0,5,-5070.048,664.1371,90.72233,0,0,0,''),
(23342,0,6,-5058.118,664.4636,94.05566,0,0,0,'cast 40984 on self'),
(23342,0,7,-5053.475,664.35,98.57059,0,0,0,''),
(23342,0,8,-5038.57,663.9222,98.57059,0,0,0,''),
(23342,0,9,-5019.736,677.1379,105.154,0,0,0,''),
(23342,0,10,-5005.494,696.0763,105.154,0,0,0,''),
(23342,0,11,-5003.47,736.425,109.7403,0,0,0,''),
(23342,0,12,-5014.967,758.2792,138.2687,0,0,0,''),
(23342,0,13,-5049.924,776.3499,154.991,0,0,0,''),
(23342,0,14,-5088.135,764.1559,147.2965,0,0,0,''),
(23342,0,15,-5109.327,751.0446,147.2965,0,0,0,''),
(23342,0,16,-5139.665,725.494,147.2965,0,0,0,''),
(23342,0,17,-5155.796,699.1519,135.4354,0,0,0,''),
(23342,0,18,-5168.645,673.1464,135.4354,0,0,0,''),
(23342,0,19,-5170.585,645.9178,135.4354,0,0,0,''),
(23342,0,20,-5169.893,609.8694,135.4354,0,0,0,''),
(23342,0,21,-5166.877,572.1507,135.4354,0,0,0,''),
(23342,0,22,-5166.384,546.2206,135.4354,0,0,0,''),
(23342,0,23,-5149.06,514.8846,135.4354,0,0,0,''),
(23342,0,24,-5117.409,493.8354,135.4354,0,0,0,''),
(23342,0,25,-5071.81,485.4799,135.4354,0,0,0,''),
(23342,0,26,-5049.221,487.5898,135.4354,0,0,0,''),
(23342,0,27,-5016.186,497.7139,135.4354,0,0,0,''),
(23342,0,28,-4997.888,513.4749,135.4354,0,0,0,''),
(23342,0,29,-4969.008,530.6617,135.4354,0,0,0,''),
(23342,0,30,-4928.234,535.1053,135.4354,0,0,0,''),
(23342,0,31,-4888.207,519.6169,135.4354,0,0,0,''),
(23342,0,32,-4861.231,501.207,135.4354,0,0,0,''),
(23342,0,33,-4851.031,486.3386,135.4354,0,0,0,''),
(23342,0,34,-4846.359,450.8282,133.6854,0,0,0,''),
(23342,0,35,-4859.994,421.5214,120.2409,0,0,0,''),
(23342,0,36,-4884.146,398.1595,119.4354,0,0,0,''),
(23342,0,37,-4918.608,387.1728,120.0465,0,0,0,''),
(23342,0,38,-4957.875,395.0519,120.0465,0,0,0,''),
(23342,0,39,-4977.369,423.309,107.4076,0,0,0,''),
(23342,0,40,-4999.41,454.0138,107.4076,0,0,0,''),
(23342,0,41,-5015.119,480.192,107.4076,0,0,0,''),
(23342,0,42,-4997.813,519.8029,107.4076,0,0,0,''),
(23342,0,43,-4969.666,535.1463,122.9632,0,0,0,''),
(23342,0,44,-4927.669,545.6583,122.9632,0,0,0,''),
(23342,0,45,-4910.169,580.5968,120.5187,0,0,0,''),
(23342,0,46,-4923.051,609.6332,116.3243,0,0,0,''),
(23342,0,47,-4939.956,638.0411,111.491,0,0,0,''),
(23342,0,48,-4966.525,654.2751,107.3798,0,0,0,''),
(23342,0,49,-4993.766,664.4593,106.2132,0,0,0,''),
(23342,0,50,-5009.622,664.3647,100.2095,0,0,0,''),
(23342,0,51,-5070.048,664.1371,90.72233,0,0,0,''),
(23342,0,52,-5077.378,664.5198,89.23929,0,0,0,'fly off, complete quest, SAY_TROPE_END'),
(23342,0,53,-5089.76,664.9246,88.03055,0,0,0,''),
(23342,0,54,-5098.756,659.2725,87.07596,0,0,0,''),
(23342,0,55,-5100.571,656.3891,87.00992,0,0,0,''),
(23342,0,56,-5100.548,640.0574,86.37918,0,0,0,''),
(23342,0,57,-5082.932,631.0391,86.1046,0,0,0,''),
(23342,0,58,-5081.618,640.9318,86.58853,0,0,0,''),
(23342,0,59,-5081.618,640.9318,86.58853,1.570796,0,0,''),
(23344,0,0,-5084.937,633.847,86.23929,0,0,0,''),
(23344,0,1,-5098.979,634.7803,86.10049,0,0,0,''),
(23344,0,2,-5101.355,648.9661,86.75992,0,0,0,''),
(23344,0,3,-5098.781,663.6365,86.99918,0,0,0,''),
(23344,0,4,-5079.276,664.713,89.1636,0,0,0,''),
(23344,0,5,-5070.444,664.3661,89.46468,0,0,0,''),
(23344,0,6,-5058.834,663.9255,92.7363,0,0,0,''),
(23344,0,7,-5037.865,660.0336,100.0141,0,0,0,''),
(23344,0,8,-5024.242,636.4905,112.4249,0,0,0,''),
(23344,0,9,-5005.374,618.8023,128.8068,0,0,0,''),
(23344,0,10,-4966.559,600.2526,129.0568,0,0,0,''),
(23344,0,11,-4965.978,571.0858,129.0568,0,0,0,''),
(23344,0,12,-4991.398,536.4358,129.0568,0,0,0,''),
(23344,0,13,-5020.616,520.3257,129.0568,0,0,0,''),
(23344,0,14,-5055.504,518.8444,129.0568,0,0,0,''),
(23344,0,15,-5102.8,514.1487,129.0568,0,0,0,''),
(23344,0,16,-5149.532,501.9677,124.2234,0,0,0,''),
(23344,0,17,-5181.648,487.4429,124.2234,0,0,0,''),
(23344,0,18,-5203.604,463.6165,124.2234,0,0,0,''),
(23344,0,19,-5222.085,438.5107,124.2234,0,0,0,''),
(23344,0,20,-5233.957,425.7707,124.2234,0,0,0,''),
(23344,0,21,-5246.468,408.2125,114.3901,0,0,0,''),
(23344,0,22,-5263.944,380.5766,82.77898,0,0,0,''),
(23344,0,23,-5281.137,345.5704,75.14012,0,0,0,''),
(23344,0,24,-5284.635,312.4421,75.14012,0,0,0,''),
(23344,0,25,-5263.003,275.3078,75.14012,0,0,0,''),
(23344,0,26,-5245.181,265.0789,73.25124,0,0,0,''),
(23344,0,27,-5215.76,265.471,73.25124,0,0,0,''),
(23344,0,28,-5205.017,235.1499,76.72346,0,0,0,''),
(23344,0,29,-5209.554,197.7829,76.72346,0,0,0,''),
(23344,0,30,-5208.264,150.2344,76.72346,0,0,0,''),
(23344,0,31,-5191.553,109.1558,93.66789,0,0,0,''),
(23344,0,32,-5182.564,85.73655,107.4735,0,0,0,''),
(23344,0,33,-5168.655,57.20128,127.9457,0,0,0,''),
(23344,0,34,-5135.729,46.99013,139.529,0,0,0,''),
(23344,0,35,-5105.781,50.70128,139.529,0,0,0,''),
(23344,0,36,-5071.623,45.81543,139.529,0,0,0,''),
(23344,0,37,-5034.686,35.1466,139.529,0,0,0,''),
(23344,0,38,-5005.947,1.385308,139.529,0,0,0,''),
(23344,0,39,-5000.307,-36.84798,139.529,0,0,0,''),
(23344,0,40,-5008.465,-64.05198,139.529,0,0,0,''),
(23344,0,41,-5035.053,-104.2141,139.529,0,0,0,''),
(23344,0,42,-5072.071,-126.9249,139.529,0,0,0,''),
(23344,0,43,-5107.338,-132.0435,139.529,0,0,0,''),
(23344,0,44,-5147.941,-120.1514,139.529,0,0,0,''),
(23344,0,45,-5172.304,-102.5539,139.529,0,0,0,''),
(23344,0,46,-5189.557,-64.99957,139.529,0,0,0,''),
(23344,0,47,-5192.558,-46.88466,139.529,0,0,0,''),
(23344,0,48,-5207.221,-7.998264,139.529,0,0,0,''),
(23344,0,49,-5208.898,16.18804,139.529,0,0,0,''),
(23344,0,50,-5210.004,47.67188,139.529,0,0,0,''),
(23344,0,51,-5229.471,71.02235,139.529,0,0,0,''),
(23344,0,52,-5259.859,84.19976,139.529,0,0,0,''),
(23344,0,53,-5280.491,98.11871,139.529,0,0,0,''),
(23344,0,54,-5304.442,119.2904,128.4734,0,0,0,''),
(23344,0,55,-5313.475,160.796,102.8068,0,0,0,''),
(23344,0,56,-5320.646,207.804,102.8068,0,0,0,''),
(23344,0,57,-5315.592,246.9388,102.8068,0,0,0,''),
(23344,0,58,-5282.777,257.4017,102.8068,0,0,0,''),
(23344,0,59,-5234.207,264.51,91.19567,0,0,0,''),
(23344,0,60,-5196.716,279.2937,75.72343,0,0,0,''),
(23344,0,61,-5181.703,301.3474,77.83456,0,0,0,''),
(23344,0,62,-5179.592,316.7443,77.83456,0,0,0,''),
(23344,0,63,-5177.286,343.4835,77.83456,0,0,0,''),
(23344,0,64,-5198.281,388.5124,82.30679,0,0,0,''),
(23344,0,65,-5190.085,423.921,103.7234,0,0,0,''),
(23344,0,66,-5161.914,456.2695,103.7234,0,0,0,''),
(23344,0,67,-5143.627,481.9556,103.7234,0,0,0,''),
(23344,0,68,-5108.331,497.8173,103.7234,0,0,0,''),
(23344,0,69,-5065.657,502.8121,103.7234,0,0,0,''),
(23344,0,70,-5026.661,514.3782,103.7234,0,0,0,''),
(23344,0,71,-4986.503,536.506,103.7234,0,0,0,''),
(23344,0,72,-4954.44,567.9017,103.7234,0,0,0,''),
(23344,0,73,-4956.34,597.6046,103.7234,0,0,0,''),
(23344,0,74,-4974.388,635.569,103.7234,0,0,0,''),
(23344,0,75,-4996.327,664.3044,96.39012,0,0,0,''),
(23344,0,76,-5021.77,663.95,91.90392,0,0,0,''),
(23344,0,77,-5041.207,664.0852,91.32059,0,0,0,''),
(23344,0,78,-5066.215,663.694,89.59836,0,0,0,'fly off, complete quest, SAY_CORLOK_END'),
(23344,0,79,-5080.021,661.6674,89.30286,0,0,0,''),
(23344,0,80,-5085.771,660.9174,88.55286,0,0,0,''),
(23344,0,81,-5090.771,660.1674,88.05286,0,0,0,''),
(23344,0,82,-5096.771,659.4174,87.55286,0,0,0,''),
(23344,0,83,-5097.771,659.1674,87.55286,0,0,0,''),
(23344,0,84,-5099.328,643.6407,86.50735,0,0,0,''),
(23344,0,85,-5092.37,632.1734,86.08287,0,0,0,''),
(23344,0,86,-5092.217,632.455,86.57751,0,0,0,''),
(23344,0,87,-5072.73,632.0778,86.1046,0,0,0,''),
(23344,0,88,-5072.652,632.3533,86.28184,0,0,0,''),
(23344,0,89,-5072.988,640.0335,86.48074,0,0,0,''),
(23345,0,0,-5091.531,631.9266,86.1046,0,0,0,''),
(23345,0,1,-5099.329,638.2125,86.36429,0,0,0,''),
(23345,0,2,-5098.52,660.3553,87.11429,0,0,0,''),
(23345,0,3,-5078.784,664.3688,89.23929,0,0,0,'fly on'),
(23345,0,4,-5070.004,664.1256,89.47318,0,0,0,''),
(23345,0,5,-5045.988,664.5428,90.34837,0,0,0,''),
(23345,0,6,-5020.852,664.3274,91.73727,0,0,0,''),
(23345,0,7,-4988.704,666.3051,92.82061,0,0,0,''),
(23345,0,8,-4951.686,663.5135,100.9675,0,0,0,''),
(23345,0,9,-4922.128,645.6582,103.7175,0,0,0,''),
(23345,0,10,-4914.606,596.9916,103.7175,0,0,0,''),
(23345,0,11,-4939.847,571.1878,103.7175,0,0,0,''),
(23345,0,12,-4969.139,547.8412,103.7175,0,0,0,''),
(23345,0,13,-4993.97,528.6561,103.7175,0,0,0,''),
(23345,0,14,-5002.941,506.9452,103.7175,0,0,0,''),
(23345,0,15,-5004.989,482.9723,103.7175,0,0,0,''),
(23345,0,16,-4994.157,457.0183,103.7175,0,0,0,''),
(23345,0,17,-4982.753,435.6739,103.7175,0,0,0,''),
(23345,0,18,-4968.979,413.1156,103.7175,0,0,0,''),
(23345,0,19,-4952.016,390.8795,103.7175,0,0,0,''),
(23345,0,20,-4918.822,380.1662,86.273,0,0,0,''),
(23345,0,21,-4891.81,384.8297,103.7175,0,0,0,''),
(23345,0,22,-4870.952,388.6259,103.7175,0,0,0,''),
(23345,0,23,-4839.091,373.6963,103.7175,0,0,0,''),
(23345,0,24,-4835.827,344.1341,103.7175,0,0,0,''),
(23345,0,25,-4847.139,297.3308,103.7175,0,0,0,''),
(23345,0,26,-4873.639,255.0166,103.7175,0,0,0,''),
(23345,0,27,-4912.098,234.3047,85.68967,0,0,0,''),
(23345,0,28,-4948.94,231.966,89.38414,0,0,0,''),
(23345,0,29,-4985.909,223.645,109.2452,0,0,0,''),
(23345,0,30,-5005.907,180.5232,103.7175,0,0,0,''),
(23345,0,31,-5002.692,144.4231,93.21744,0,0,0,''),
(23345,0,32,-5000.446,107.8185,97.6619,0,0,0,''),
(23345,0,33,-5001.402,88.90202,97.6619,0,0,0,''),
(23345,0,34,-4992.563,59.60102,97.6619,0,0,0,''),
(23345,0,35,-4973.051,35.04601,97.6619,0,0,0,''),
(23345,0,36,-4950.327,16.39974,97.6619,0,0,0,''),
(23345,0,37,-4919.713,-7.58724,97.6619,0,0,0,''),
(23345,0,38,-4895.118,-24.4617,97.6619,0,0,0,''),
(23345,0,39,-4873.843,-56.46213,97.6619,0,0,0,''),
(23345,0,40,-4878.95,-78.37022,97.6619,0,0,0,''),
(23345,0,41,-4900.977,-96.32227,124.5508,0,0,0,''),
(23345,0,42,-4938.917,-97.65365,140.8841,0,0,0,''),
(23345,0,43,-4947.491,-70.94228,139.2697,0,0,0,''),
(23345,0,44,-4962.078,-45.11686,118.7141,0,0,0,''),
(23345,0,45,-4985.609,-3.707574,104.4363,0,0,0,''),
(23345,0,46,-5007.204,21.71202,104.4363,0,0,0,''),
(23345,0,47,-5035.34,34.8622,104.4363,0,0,0,''),
(23345,0,48,-5077.724,45.16526,83.8252,0,0,0,''),
(23345,0,49,-5122.017,50.87055,85.74186,0,0,0,''),
(23345,0,50,-5163.295,41.71484,112.9919,0,0,0,''),
(23345,0,51,-5185.467,38.44889,155.7974,0,0,0,''),
(23345,0,52,-5215.355,32.12261,192.6029,0,0,0,''),
(23345,0,53,-5251.429,11.90918,192.6029,0,0,0,''),
(23345,0,54,-5270.692,35.87956,192.6029,0,0,0,''),
(23345,0,55,-5269.639,61.32357,192.6029,0,0,0,''),
(23345,0,56,-5229.232,77.38042,192.6029,0,0,0,''),
(23345,0,57,-5199.305,80.3291,192.6029,0,0,0,''),
(23345,0,58,-5162.087,96.18935,163.0474,0,0,0,''),
(23345,0,59,-5116.333,114.7767,156.1029,0,0,0,''),
(23345,0,60,-5104.885,161.9479,144.0197,0,0,0,''),
(23345,0,61,-5106.104,210.7065,141.1308,0,0,0,''),
(23345,0,62,-5100.365,254.993,151.6304,0,0,0,''),
(23345,0,63,-5094.819,294.7229,165.9231,0,0,0,''),
(23345,0,64,-5072.266,323.0579,173.471,0,0,0,''),
(23345,0,65,-5042.428,354.9113,179.3321,0,0,0,''),
(23345,0,66,-5031.137,402.7699,182.737,0,0,0,''),
(23345,0,67,-5023.528,437.5792,182.737,0,0,0,''),
(23345,0,68,-5021.058,461.7069,157.5425,0,0,0,''),
(23345,0,69,-5061.279,480.6051,134.3203,0,0,0,''),
(23345,0,70,-5101.122,489.5711,134.3203,0,0,0,''),
(23345,0,71,-5131.542,478.5534,134.3203,0,0,0,''),
(23345,0,72,-5154.209,459.8275,134.3203,0,0,0,''),
(23345,0,73,-5173.368,424.9651,134.3203,0,0,0,''),
(23345,0,74,-5176.187,388.6364,134.3203,0,0,0,''),
(23345,0,75,-5178.223,359.5666,134.3203,0,0,0,''),
(23345,0,76,-5177.092,334.0616,134.3203,0,0,0,''),
(23345,0,77,-5184.358,290.9243,134.3203,0,0,0,''),
(23345,0,78,-5200.437,273.4439,134.3203,0,0,0,''),
(23345,0,79,-5243.265,262.7923,134.3203,0,0,0,''),
(23345,0,80,-5263.354,272.4469,134.3203,0,0,0,''),
(23345,0,81,-5280.749,294.9872,134.3203,0,0,0,''),
(23345,0,82,-5285.514,322.7867,134.3203,0,0,0,''),
(23345,0,83,-5279.47,359.6388,134.3203,0,0,0,''),
(23345,0,84,-5272.3,381.9901,134.3203,0,0,0,''),
(23345,0,85,-5257.371,401.5872,134.3203,0,0,0,''),
(23345,0,86,-5234.978,422.1708,128.9314,0,0,0,''),
(23345,0,87,-5221.283,434.7353,124.7925,0,0,0,''),
(23345,0,88,-5204.375,446.8191,115.237,0,0,0,''),
(23345,0,89,-5166.356,467.1954,115.237,0,0,0,''),
(23345,0,90,-5123.749,489.6505,115.237,0,0,0,''),
(23345,0,91,-5089.289,501.8938,115.237,0,0,0,''),
(23345,0,92,-5050.138,500.7674,115.237,0,0,0,''),
(23345,0,93,-5022.075,515.1059,115.237,0,0,0,''),
(23345,0,94,-5004.622,526.2526,115.237,0,0,0,''),
(23345,0,95,-4987.251,539.7435,115.237,0,0,0,''),
(23345,0,96,-4967.14,557.4308,115.237,0,0,0,''),
(23345,0,97,-4954.635,576.6056,115.237,0,0,0,''),
(23345,0,98,-4941.903,596.954,115.237,0,0,0,''),
(23345,0,99,-4937.899,622.1005,115.237,0,0,0,''),
(23345,0,100,-4942.416,647.0491,115.237,0,0,0,''),
(23345,0,101,-4955.862,657.9393,105.1536,0,0,0,''),
(23345,0,102,-4987.663,666.5894,95.04252,0,0,0,''),
(23345,0,103,-5012.211,663.7874,93.4317,0,0,0,''),
(23345,0,104,-5029.556,664.0626,92.48726,0,0,0,''),
(23345,0,105,-5046.771,664.192,91.59837,0,0,0,''),
(23345,0,106,-5065.815,664.1027,89.51505,0,0,0,'fly off, complete quest, SAY_ICHMAN_END'),
(23345,0,107,-5097.221,643.8181,86.61429,0,0,0,''),
(23345,0,108,-5082.632,631.6423,86.1046,0,0,0,''),
(23345,0,109,-5065.899,639.8352,86.49668,0,0,0,''),
(23345,0,110,-5066.307,640.2136,86.49668,1.553343,0,0,''),
(23346,0,0,-5078.127,632.7935,86.1046,0,0,0,''),
(23346,0,1,-5096.167,634.1729,86.26175,0,0,0,''),
(23346,0,2,-5099.563,647.3327,86.73929,0,0,0,''),
(23346,0,3,-5096.421,663.5131,87.23123,0,0,0,''),
(23346,0,4,-5078.932,664.5538,89.23929,0,0,0,'fly on'),
(23346,0,5,-5047.585,664.4786,90.09837,0,0,0,''),
(23346,0,6,-5029.147,664.6062,91.84837,0,0,0,''),
(23346,0,7,-5001.704,665.0206,94.57059,0,0,0,''),
(23346,0,8,-4980.508,664.0265,94.57059,0,0,0,''),
(23346,0,9,-4951.832,664.3872,93.03965,0,0,0,''),
(23346,0,10,-4913.112,661.8121,90.53965,0,0,0,''),
(23346,0,11,-4887.881,689.6855,86.73409,0,0,0,''),
(23346,0,12,-4885.2,719.2115,86.73409,0,0,0,''),
(23346,0,13,-4905.209,763.2064,86.73409,0,0,0,''),
(23346,0,14,-4948.712,781.429,78.37299,0,0,0,''),
(23346,0,15,-4977.905,809.7921,95.7341,0,0,0,''),
(23346,0,16,-4988.85,809.7207,89.65078,0,0,0,''),
(23346,0,17,-5011.912,818.0668,89.65078,0,0,0,''),
(23346,0,18,-5051.185,819.7384,89.65078,0,0,0,''),
(23346,0,19,-5083.584,797.4017,89.65078,0,0,0,''),
(23346,0,20,-5114.206,773.3442,72.73411,0,0,0,''),
(23346,0,21,-5143.489,764.9902,65.06745,0,0,0,''),
(23346,0,22,-5185.277,762.5067,65.06745,0,0,0,''),
(23346,0,23,-5213.917,765.2517,65.06745,0,0,0,''),
(23346,0,24,-5257.457,784.7656,65.06745,0,0,0,''),
(23346,0,25,-5278.247,777.8218,65.06745,0,0,0,''),
(23346,0,26,-5294.249,755.3405,65.06745,0,0,0,''),
(23346,0,27,-5296.898,729.1802,65.06745,0,0,0,''),
(23346,0,28,-5289.127,702.0369,65.06745,0,0,0,''),
(23346,0,29,-5273.802,666.1729,62.56745,0,0,0,''),
(23346,0,30,-5267.913,638.2552,52.5119,0,0,0,''),
(23346,0,31,-5260.284,622.6142,56.06746,0,0,0,''),
(23346,0,32,-5245.017,611.9426,66.20634,0,0,0,''),
(23346,0,33,-5200.1,604.6636,86.98518,0,0,0,''),
(23346,0,34,-5181.164,590.6979,89.29072,0,0,0,''),
(23346,0,35,-5185.517,548.6089,94.31851,0,0,0,''),
(23346,0,36,-5167.705,522.7582,94.31851,0,0,0,''),
(23346,0,37,-5137.539,504.2317,94.31851,0,0,0,''),
(23346,0,38,-5102.646,499.6689,94.31851,0,0,0,''),
(23346,0,39,-5064.482,492.9311,94.31851,0,0,0,''),
(23346,0,40,-5035.057,477.9901,104.0685,0,0,0,''),
(23346,0,41,-5001.804,454.6688,104.0685,0,0,0,''),
(23346,0,42,-4978.692,423.2803,104.0685,0,0,0,''),
(23346,0,43,-4968.225,394.6599,104.0685,0,0,0,''),
(23346,0,44,-4970.736,356.3612,97.09627,0,0,0,''),
(23346,0,45,-4981.942,320.5984,96.26293,0,0,0,''),
(23346,0,46,-5000.338,287.576,96.26293,0,0,0,''),
(23346,0,47,-5024.314,263.4618,97.12405,0,0,0,''),
(23346,0,48,-5033.601,245.4317,99.70215,0,0,0,''),
(23346,0,49,-5043.806,220.8815,109.3681,0,0,0,''),
(23346,0,50,-5055.694,189.8815,121.6043,0,0,0,''),
(23346,0,51,-5065.022,177.9086,129.7014,0,0,0,''),
(23346,0,52,-5093.455,175.0507,135.2028,0,0,0,''),
(23346,0,53,-5104.901,192.9338,143.8139,0,0,0,''),
(23346,0,54,-5108.269,222.5996,143.8139,0,0,0,''),
(23346,0,55,-5096.198,260.2229,155.9698,0,0,0,''),
(23346,0,56,-5092.704,300.505,168.0287,0,0,0,''),
(23346,0,57,-5064.827,341.2665,173.6232,0,0,0,''),
(23346,0,58,-5046.666,359.6774,175.4009,0,0,0,''),
(23346,0,59,-5017.936,369.2787,177.6509,0,0,0,''),
(23346,0,60,-4990.092,370.2358,177.6509,0,0,0,''),
(23346,0,61,-4946.644,373.1902,173.2898,0,0,0,''),
(23346,0,62,-4904.017,381.0535,154.401,0,0,0,''),
(23346,0,63,-4873.26,409.159,154.401,0,0,0,''),
(23346,0,64,-4858.19,449.1999,154.401,0,0,0,''),
(23346,0,65,-4860.118,475.3252,154.401,0,0,0,''),
(23346,0,66,-4874.003,522.4359,154.401,0,0,0,''),
(23346,0,67,-4907.657,539.0103,154.401,0,0,0,''),
(23346,0,68,-4937.984,542.9128,154.401,0,0,0,''),
(23346,0,69,-4984.786,534.6582,154.401,0,0,0,''),
(23346,0,70,-5016.347,516.8373,154.401,0,0,0,''),
(23346,0,71,-5045.822,504.1454,154.401,0,0,0,''),
(23346,0,72,-5067.003,496.7763,154.401,0,0,0,''),
(23346,0,73,-5092.522,477.6822,154.401,0,0,0,''),
(23346,0,74,-5113.307,451.8052,150.7898,0,0,0,''),
(23346,0,75,-5145.342,430.1466,148.2621,0,0,0,''),
(23346,0,76,-5159.413,401.4334,136.8176,0,0,0,''),
(23346,0,77,-5177.601,380.3644,135.0954,0,0,0,''),
(23346,0,78,-5177.559,335.6026,122.401,0,0,0,''),
(23346,0,79,-5183.724,292.3144,122.401,0,0,0,''),
(23346,0,80,-5214.583,264.1207,122.401,0,0,0,''),
(23346,0,81,-5238.495,265.3249,113.0954,0,0,0,''),
(23346,0,82,-5270.4,270.1617,113.0954,0,0,0,''),
(23346,0,83,-5295.31,259.1142,113.0954,0,0,0,''),
(23346,0,84,-5311.033,222.1083,113.0954,0,0,0,''),
(23346,0,85,-5342.249,192.5318,113.0954,0,0,0,''),
(23346,0,86,-5347.233,154.9113,113.0954,0,0,0,''),
(23346,0,87,-5320.385,112.0802,113.0954,0,0,0,''),
(23346,0,88,-5278.581,88.2244,113.0954,0,0,0,''),
(23346,0,89,-5258.171,55.24957,113.0954,0,0,0,''),
(23346,0,90,-5251.674,14.11502,113.0954,0,0,0,''),
(23346,0,91,-5249.777,-21.18479,125.651,0,0,0,''),
(23346,0,92,-5257.274,-54.0995,129.7343,0,0,0,''),
(23346,0,93,-5277.006,-99.74707,132.9566,0,0,0,''),
(23346,0,94,-5297.232,-105.6787,130.4566,0,0,0,''),
(23346,0,95,-5340.311,-104.8584,130.4566,0,0,0,''),
(23346,0,96,-5367.746,-96.76975,130.4566,0,0,0,''),
(23346,0,97,-5383.334,-62.23264,130.4566,0,0,0,''),
(23346,0,98,-5365.698,-35.27062,130.4566,0,0,0,''),
(23346,0,99,-5340.349,-18.70963,130.4566,0,0,0,''),
(23346,0,100,-5309.31,9.529188,130.4566,0,0,0,''),
(23346,0,101,-5289.217,14.57964,130.4566,0,0,0,''),
(23346,0,102,-5263.405,19.9974,130.4566,0,0,0,''),
(23346,0,103,-5232.503,13.45378,130.4566,0,0,0,''),
(23346,0,104,-5204.176,-19.43283,130.4566,0,0,0,''),
(23346,0,105,-5182.804,-62.57574,118.0121,0,0,0,''),
(23346,0,106,-5174.803,-84.48155,118.0121,0,0,0,''),
(23346,0,107,-5162.558,-103.8193,118.0121,0,0,0,''),
(23346,0,108,-5131.967,-113.7209,118.0121,0,0,0,''),
(23346,0,109,-5096.79,-121.8593,118.0121,0,0,0,''),
(23346,0,110,-5065.522,-109.8579,118.0121,0,0,0,''),
(23346,0,111,-5042.261,-85.59082,118.0121,0,0,0,''),
(23346,0,112,-5019.137,-62.09039,98.81767,0,0,0,''),
(23346,0,113,-4997.549,-36.64453,92.62322,0,0,0,''),
(23346,0,114,-4968.95,-1.824978,85.90099,0,0,0,''),
(23346,0,115,-4934.683,27.94217,70.40099,0,0,0,''),
(23346,0,116,-4902.898,45.49132,59.95655,0,0,0,''),
(23346,0,117,-4884.461,46.51064,45.45655,0,0,0,''),
(23346,0,118,-4867.73,45.39312,-0.654566,0,0,0,''),
(23346,0,119,-4854.791,31.71137,-4.710121,0,0,0,''),
(23346,0,120,-4852.745,-1.659288,1.817656,0,0,0,''),
(23346,0,121,-4861.769,-29.40929,36.5562,0,0,0,''),
(23346,0,122,-4882.453,-29.94065,74.63494,0,0,0,''),
(23346,0,123,-4910.108,-50.92372,104.1269,0,0,0,''),
(23346,0,124,-4922.273,-66.68522,140.7146,0,0,0,''),
(23346,0,125,-4949.065,-51.4962,135.4091,0,0,0,''),
(23346,0,126,-4952.385,-44.90668,116.6313,0,0,0,''),
(23346,0,127,-4964.531,-33.20681,108.0758,0,0,0,''),
(23346,0,128,-4983.418,4.737739,108.0758,0,0,0,''),
(23346,0,129,-4966.226,46.29297,108.0758,0,0,0,''),
(23346,0,130,-4946.933,79.27724,108.0758,0,0,0,''),
(23346,0,131,-4927.336,105.7801,108.0758,0,0,0,''),
(23346,0,132,-4903.621,139.424,108.0758,0,0,0,''),
(23346,0,133,-4908.835,173.5289,108.0758,0,0,0,''),
(23346,0,134,-4899.304,207.2578,108.0758,0,0,0,''),
(23346,0,135,-4894.789,241.9639,100.548,0,0,0,''),
(23346,0,136,-4876.024,262.596,100.548,0,0,0,''),
(23346,0,137,-4851.944,285.5693,100.548,0,0,0,''),
(23346,0,138,-4845.693,327.7279,100.548,0,0,0,''),
(23346,0,139,-4845.241,359.997,95.88132,0,0,0,''),
(23346,0,140,-4847.69,391.2897,95.88132,0,0,0,''),
(23346,0,141,-4859.135,419.0597,95.88132,0,0,0,''),
(23346,0,142,-4856.898,465.8593,95.88132,0,0,0,''),
(23346,0,143,-4876.195,509.1212,95.88132,0,0,0,''),
(23346,0,144,-4916.561,535.1924,95.88132,0,0,0,''),
(23346,0,145,-4941.459,566.5074,95.88132,0,0,0,''),
(23346,0,146,-4956.068,605.6051,95.88132,0,0,0,''),
(23346,0,147,-4967.994,629.4673,95.88132,0,0,0,''),
(23346,0,148,-4992.872,657.3202,95.88132,0,0,0,''),
(23346,0,149,-5019.961,663.826,95.88132,0,0,0,''),
(23346,0,150,-5049.397,663.9436,98.93688,0,0,0,''),
(23346,0,151,-5085.372,666.438,105.1035,0,0,0,''),
(23346,0,152,-5114.091,670.0516,107.3258,0,0,0,''),
(23346,0,153,-5129.29,676.2471,107.3258,0,0,0,''),
(23346,0,154,-5134.548,693.2084,107.3258,0,0,0,''),
(23346,0,155,-5124.754,712.9388,107.3258,0,0,0,''),
(23346,0,156,-5091.654,711.2447,104.5202,0,0,0,''),
(23346,0,157,-5069.821,674.8909,104.5202,0,0,0,''),
(23346,0,158,-5061.352,667.0403,104.5202,0,0,0,''),
(23346,0,159,-5019.67,666.8051,104.5202,0,0,0,''),
(23346,0,160,-5000.67,667.4341,104.5202,0,0,0,''),
(23346,0,161,-4993.282,669.9588,104.5202,0,0,0,''),
(23346,0,162,-5002.192,664.5203,97.93169,0,0,0,''),
(23346,0,163,-5017.093,664.3544,96.15392,0,0,0,''),
(23346,0,164,-5040.194,664.2045,90.40389,0,0,0,''),
(23346,0,165,-5090.223,663.8318,87.97513,0,0,0,''),
(23346,0,166,-5101.206,660.5425,87.00992,0,0,0,''),
(23346,0,167,-5102.085,639.8577,86.38492,0,0,0,''),
(23346,0,168,-5091.961,630.3558,86.1317,0,0,0,''),
(23346,0,169,-5078.229,633.2795,86.1046,0,0,0,''),
(23346,0,170,-5062.336,632.8517,86.17667,0,0,0,''),
(23346,0,171,-5060.474,640.3013,86.64524,1.500983,0,0,''),
(23348,0,0,-5097.342,638.2053,86.37064,0,0,0,''),
(23348,0,1,-5099.037,662.449,87.04227,0,0,0,''),
(23348,0,2,-5079.384,664.2811,89.15067,0,0,0,'fly on'),
(23348,0,3,-5059.083,664.368,90.95825,0,0,0,''),
(23348,0,4,-5034.28,664.2311,90.95825,0,0,0,''),
(23348,0,5,-5008.98,664.1523,90.95825,0,0,0,''),
(23348,0,6,-4987.987,664.8333,93.12492,0,4000,0,''),
(23348,0,7,-4957.929,667.1135,89.67696,0,0,0,''),
(23348,0,8,-4923.51,679.0427,89.67696,0,0,0,''),
(23348,0,9,-4907.643,683.4996,89.67696,0,0,0,''),
(23348,0,10,-4883.626,694.9488,89.67696,0,0,0,''),
(23348,0,11,-4850.153,676.8022,89.67696,0,0,0,''),
(23348,0,12,-4864.901,632.5569,89.67696,0,0,0,''),
(23348,0,13,-4910.243,633.4714,89.67696,0,0,0,''),
(23348,0,14,-4946.938,659.1007,89.67696,0,0,0,''),
(23348,0,15,-4995.127,667.0613,94.92697,0,0,0,''),
(23348,0,16,-5029.882,666.0309,94.92698,0,0,0,''),
(23348,0,17,-5065.315,666.9732,103.6214,0,0,0,''),
(23348,0,18,-5091.274,666.2161,117.4825,0,0,0,''),
(23348,0,19,-5132.497,678.9468,117.4825,0,0,0,''),
(23348,0,20,-5160.828,695.7098,117.4825,0,0,0,''),
(23348,0,21,-5189.027,715.3826,117.4825,0,0,0,''),
(23348,0,22,-5218.202,743.7205,117.4825,0,0,0,''),
(23348,0,23,-5246.878,753.9114,117.4825,0,0,0,''),
(23348,0,24,-5291.249,736.5722,117.4825,0,0,0,''),
(23348,0,25,-5297.695,704.0183,117.4825,0,0,0,''),
(23348,0,26,-5294.14,669.929,117.4825,0,0,0,''),
(23348,0,27,-5283.434,645.6896,117.4825,0,0,0,''),
(23348,0,28,-5274.705,617.4304,117.4825,0,0,0,''),
(23348,0,29,-5275.441,576.7112,117.4825,0,0,0,''),
(23348,0,30,-5275.686,532.8275,94.37141,0,0,0,''),
(23348,0,31,-5270.501,488.1923,78.17696,0,0,0,''),
(23348,0,32,-5275.354,443.7866,67.01029,0,0,0,''),
(23348,0,33,-5282.691,395.9322,67.01029,0,0,0,''),
(23348,0,34,-5284.521,357.4507,67.01029,0,0,0,''),
(23348,0,35,-5297.132,321.8339,75.31584,0,0,0,''),
(23348,0,36,-5305.334,287.9489,67.01029,0,0,0,''),
(23348,0,37,-5324.948,244.8683,67.01029,0,0,0,''),
(23348,0,38,-5356.357,222.8803,74.17696,0,0,0,''),
(23348,0,39,-5372.028,179.2107,74.17696,0,0,0,''),
(23348,0,40,-5334.379,148.9864,74.17696,0,0,0,''),
(23348,0,41,-5315.291,119.4997,74.17696,0,0,0,''),
(23348,0,42,-5293.327,83.57639,74.17696,0,0,0,''),
(23348,0,43,-5277.183,50.7105,74.17696,0,0,0,''),
(23348,0,44,-5255.611,8.40484,74.17696,0,0,0,''),
(23348,0,45,-5224.429,-18.24121,101.3436,0,0,0,''),
(23348,0,46,-5203.018,-50.26172,113.1214,0,0,0,''),
(23348,0,47,-5177.758,-81.79276,113.1214,0,0,0,''),
(23348,0,48,-5153.055,-109.1681,113.1214,0,0,0,''),
(23348,0,49,-5112.361,-123.955,113.1214,0,0,0,''),
(23348,0,50,-5075.532,-120.1032,113.1214,0,0,0,''),
(23348,0,51,-5034.087,-103.7401,113.1214,0,0,0,''),
(23348,0,52,-4989.264,-83.96908,113.1214,0,0,0,''),
(23348,0,53,-4952.199,-82.11546,113.1214,0,0,0,''),
(23348,0,54,-4930.279,-71.91537,134.939,0,0,0,''),
(23348,0,55,-4903.256,-46.99186,119.5501,0,0,0,''),
(23348,0,56,-4892.428,-14.39844,119.5501,0,0,0,''),
(23348,0,57,-4901.102,29.4554,119.5501,0,0,0,''),
(23348,0,58,-4921.162,50.85612,119.5501,0,0,0,''),
(23348,0,59,-4960.637,51.15321,119.5501,0,0,0,''),
(23348,0,60,-5007.94,44.28179,113.9668,0,0,0,''),
(23348,0,61,-5049.16,46.34722,113.9668,0,0,0,''),
(23348,0,62,-5081.966,51.23449,113.9668,0,0,0,''),
(23348,0,63,-5109.11,52.6926,113.9668,0,0,0,''),
(23348,0,64,-5153.785,53.41374,113.9668,0,0,0,''),
(23348,0,65,-5194.33,78.2347,113.9668,0,0,0,''),
(23348,0,66,-5200.143,112.9766,113.9668,0,0,0,''),
(23348,0,67,-5210.659,155.0445,113.9668,0,0,0,''),
(23348,0,68,-5209.587,202.7329,113.9668,0,0,0,''),
(23348,0,69,-5206.819,249.7953,113.9668,0,0,0,''),
(23348,0,70,-5195.308,281.5933,113.9668,0,0,0,''),
(23348,0,71,-5175.319,312.8564,113.9668,0,0,0,''),
(23348,0,72,-5176.313,350.4632,113.9668,0,0,0,''),
(23348,0,73,-5197.359,384.4846,113.9668,0,0,0,''),
(23348,0,74,-5206.275,401.4015,113.9668,0,0,0,''),
(23348,0,75,-5210.944,427.5983,113.9668,0,0,0,''),
(23348,0,76,-5204.977,464.8688,113.9668,0,0,0,''),
(23348,0,77,-5193.151,501.4104,113.9668,0,0,0,''),
(23348,0,78,-5180.75,540.2638,113.9668,0,0,0,''),
(23348,0,79,-5174.904,567.8201,113.9668,0,0,0,''),
(23348,0,80,-5159.236,594.9044,113.9668,0,0,0,''),
(23348,0,81,-5132.958,612.1032,113.9668,0,0,0,''),
(23348,0,82,-5111.183,618.4528,115.6335,0,0,0,''),
(23348,0,83,-5082.095,643.4512,127.189,0,0,0,''),
(23348,0,84,-5051.162,666.2181,134.5779,0,0,0,''),
(23348,0,85,-5023.218,672.1176,134.5779,0,0,0,''),
(23348,0,86,-4998.408,675.9113,134.5779,0,0,0,''),
(23348,0,87,-4964.067,667.4047,134.5779,0,0,0,''),
(23348,0,88,-4945.452,649.2565,134.5779,0,0,0,''),
(23348,0,89,-4929.717,618.0428,134.5779,0,0,0,''),
(23348,0,90,-4933.029,597.6074,134.5779,0,0,0,''),
(23348,0,91,-4950.765,560.4185,134.5779,0,0,0,''),
(23348,0,92,-4986.156,534.7485,134.5779,0,0,0,''),
(23348,0,93,-5027.694,507.0074,140.5223,0,0,0,''),
(23348,0,94,-5063.99,482.6105,161.0223,0,0,0,''),
(23348,0,95,-5079.088,444.7179,188.5779,0,0,0,''),
(23348,0,96,-5081.959,401.0051,210.8873,0,0,0,''),
(23348,0,97,-5080.922,379.7276,222.7484,0,0,0,''),
(23348,0,98,-5088.472,350.8958,222.7484,0,0,0,''),
(23348,0,99,-5101.865,322.2873,222.7484,0,0,0,''),
(23348,0,100,-5108.479,280.2418,222.7484,0,0,0,''),
(23348,0,101,-5108.403,250.032,222.7484,0,0,0,''),
(23348,0,102,-5116.868,216.9851,222.7484,0,0,0,''),
(23348,0,103,-5109.27,175.0246,222.7484,0,0,0,''),
(23348,0,104,-5088.899,150.6683,222.7484,0,0,0,''),
(23348,0,105,-5060.405,142.9474,222.7484,0,0,0,''),
(23348,0,106,-5048.861,136.8668,222.7484,0,0,0,''),
(23348,0,107,-5028.831,136.0967,222.7484,0,0,0,''),
(23348,0,108,-5014.031,134.3629,222.7484,0,0,0,''),
(23348,0,109,-4976.749,133.0627,190.4706,0,0,0,''),
(23348,0,110,-4939.158,144.4543,190.4706,0,0,0,''),
(23348,0,111,-4909.588,167.5473,190.4706,0,0,0,''),
(23348,0,112,-4901.982,203.8995,160.6373,0,0,0,''),
(23348,0,113,-4923.405,237.4692,163.8317,0,0,0,''),
(23348,0,114,-4957.846,242.4023,167.1373,0,0,0,''),
(23348,0,115,-4979.879,241.2091,167.1373,0,0,0,''),
(23348,0,116,-5010.276,221.4066,167.1373,0,0,0,''),
(23348,0,117,-5046.926,191.8748,167.1373,0,0,0,''),
(23348,0,118,-5085.212,182.271,167.1373,0,0,0,''),
(23348,0,119,-5091.655,219.2357,167.1373,0,0,0,''),
(23348,0,120,-5091.76,256.4972,198.3595,0,0,0,''),
(23348,0,121,-5073.088,284.9821,198.3595,0,0,0,''),
(23348,0,122,-5056.151,305.8941,198.3595,0,0,0,''),
(23348,0,123,-5033.989,340.742,198.3595,0,0,0,''),
(23348,0,124,-5013.551,366.6549,198.3595,0,0,0,''),
(23348,0,125,-4985.13,398.5603,198.3595,0,0,0,''),
(23348,0,126,-4951.698,419.7676,198.3595,0,0,0,''),
(23348,0,127,-4927.77,437.4049,174.8595,0,0,0,''),
(23348,0,128,-4905.905,452.8599,174.8595,0,0,0,''),
(23348,0,129,-4904.514,474.8152,174.8595,0,0,0,''),
(23348,0,130,-4909.353,491.2098,174.8595,0,0,0,''),
(23348,0,131,-4906.713,508.8005,174.8595,0,0,0,''),
(23348,0,132,-4904.04,524.842,174.8595,0,0,0,''),
(23348,0,133,-4903.656,545.8247,174.8595,0,0,0,''),
(23348,0,134,-4910.834,565.4141,174.8595,0,0,0,''),
(23348,0,135,-4923.354,594.0482,147.2484,0,0,0,''),
(23348,0,136,-4936.446,624.7623,130.3039,0,0,0,''),
(23348,0,137,-4970.291,650.181,106.6095,0,0,0,''),
(23348,0,138,-4991.406,664.5876,103.2761,0,0,0,''),
(23348,0,139,-5100.779,656.943,87.00992,0,0,0,''),
(23348,0,140,-5099.944,642.5331,86.43362,0,0,0,''),
(23348,0,141,-5095.807,633.6784,86.23929,0,0,0,''),
(23348,0,142,-5084.066,627.6938,85.9796,0,0,0,''),
(23348,0,143,-5074.522,625.243,85.75792,0,0,0,''),
(23348,0,144,-5074.878,625.4485,85.72105,0,0,0,''),
(23383,0,0,-4109.42,3034.16,344.168,0,5000,0,'SAY_ESCORT_START'),
(23383,0,1,-4113.27,3035.99,344.071,0,0,0,''),
(23383,0,2,-4120.02,3032.22,344.074,0,0,0,''),
(23383,0,3,-4124.41,3026.33,344.151,0,0,0,''),
(23383,0,4,-4128.82,3026.65,344.035,0,0,0,''),
(23383,0,5,-4138.91,3028.95,338.92,0,0,0,''),
(23383,0,6,-4152.59,3031.23,336.913,0,0,0,''),
(23383,0,7,-4169.81,3034.3,342.047,0,0,0,''),
(23383,0,8,-4174.63,3036.04,343.457,0,0,0,''),
(23383,0,9,-4174.4,3044.98,343.862,0,0,0,''),
(23383,0,10,-4176.63,3052.01,344.077,0,0,0,''),
(23383,0,11,-4183.66,3058.9,344.15,0,0,0,''),
(23383,0,12,-4182.92,3065.41,342.574,0,0,0,'ambush'),
(23383,0,13,-4182.06,3070.56,337.644,0,3000,0,'SAY_AMBUSH_END'),
(23383,0,14,-4181.26,3077.13,331.59,0,0,0,''),
(23383,0,15,-4179.99,3086.1,325.571,0,0,0,''),
(23383,0,16,-4178.77,3090.1,323.955,0,0,0,''),
(23383,0,17,-4177.96,3093.87,323.839,0,5000,0,'SAY_ESCORT_COMPLETE'),
(23383,0,18,-4166.25,3106.51,320.961,0,0,0,''),
(23383,0,19,-3718.81,3787.24,302.89,0,5000,0,'SAY_ESCORT_START'),
(23383,0,20,-3714.44,3780.35,302.075,0,0,0,''),
(23383,0,21,-3698.33,3788.04,302.171,0,0,0,''),
(23383,0,22,-3679.36,3780.25,295.077,0,0,0,''),
(23383,0,23,-3654.82,3770.43,301.291,0,0,0,'ambush'),
(23383,0,24,-3656.07,3757.31,301.985,0,3000,0,'SAY_AMBUSH_END'),
(23383,0,25,-3648.83,3743.07,302.173,0,0,0,''),
(23383,0,26,-3659.16,3714.94,281.576,0,5000,0,'SAY_ESCORT_COMPLETE'),
(23383,0,27,-3652.71,3704.63,280.646,0,0,0,''),
(23383,0,28,-3671.51,3385.36,312.956,0,5000,0,'SAY_ESCORT_START'),
(23383,0,29,-3677.74,3379.05,312.136,0,0,0,''),
(23383,0,30,-3667.52,3366.45,312.233,0,0,0,''),
(23383,0,31,-3672.87,3343.52,304.994,0,0,0,'ambush'),
(23383,0,32,-3679.35,3319.01,311.419,0,3000,0,'SAY_AMBUSH_END'),
(23383,0,33,-3692.93,3318.69,312.081,0,0,0,''),
(23383,0,34,-3704.08,3309.56,312.233,0,0,0,''),
(23383,0,35,-3733.99,3315.77,292.093,0,5000,0,'SAY_ESCORT_COMPLETE'),
(23383,0,36,-3730.11,3326.87,290.705,0,0,0,''),
(24358,0,0,121.194,1645.62,42.021,0,0,0,''),
(24358,0,1,132.051,1642.18,42.021,0,5000,0,'SAY_AT_GONG'),
(24358,0,2,120.671,1636.35,42.415,0,0,0,''),
(24358,0,3,120.536,1611.65,43.473,0,10000,0,'SAY_OPEN_ENTRANCE'),
(24358,0,4,120.536,1611.65,43.473,0,0,0,'');

-- EOF

