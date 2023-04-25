DELETE FROM creature_template WHERE entry IN (100601);
INSERT INTO creature_template (Entry, Name, SubName, MinLevel, MaxLevel, ModelId1, ModelId2, ModelId3, ModelId4, Faction, Scale, Family, CreatureType, InhabitType, RegenerateStats, RacialLeader, NpcFlags, UnitFlags, DynamicFlags, ExtraFlags, CreatureTypeFlags, SpeedWalk, SpeedRun, Detection, CallForHelp, Pursuit, Leash, Timeout, UnitClass, `Rank`, HealthMultiplier, PowerMultiplier, DamageMultiplier, DamageVariance, ArmorMultiplier, ExperienceMultiplier, MinLevelHealth, MaxLevelHealth, MinLevelMana, MaxLevelMana, MinMeleeDmg, MaxMeleeDmg, MinRangedDmg, MaxRangedDmg, Armor, MeleeAttackPower, RangedAttackPower, MeleeBaseAttackTime, RangedBaseAttackTime, DamageSchool, MinLootGold, MaxLootGold, LootId, PickpocketLootId, SkinningLootId, KillCredit1, KillCredit2, MechanicImmuneMask, SchoolImmuneMask, ResistanceHoly, ResistanceFire, ResistanceNature, ResistanceFrost, ResistanceShadow, ResistanceArcane, PetSpellDataId, MovementType, TrainerType, TrainerSpell, TrainerClass, TrainerRace, TrainerTemplateId, VendorTemplateId, EquipmentTemplateId, GossipMenuId, AIName, ScriptName) VALUES
('100601','Dual Specialization Crystal','','1','1','11659','11659','11659','11659','35','1','0','7','3','3','0','1','0','0','0','0','1','1.14286','20','0','0','0','0','1','0','1','1','1','1','1','1','42','42','0','0','2','2','0','0','7','11','0','2000','2000','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','npc_custom_dualspec');

DELETE FROM creature WHERE id IN (100601);
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecsmin`, `spawntimesecsmax`, `spawndist`, `MovementType`) VALUES (100601, 0, 1, 0, -8988.56, 849.754, 29.621, 2.27687, 25, 25, 0, 0);
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecsmin`, `spawntimesecsmax`, `spawndist`, `MovementType`) VALUES (100601, 1, 1, 0, 1471.63, -4216.46, 58.9942, 4.35778, 25, 25, 0, 0);

SET @STRING_ENTRY := 12000;
DELETE FROM `mangos_string` WHERE `entry` BETWEEN  @STRING_ENTRY+0 AND @STRING_ENTRY+21;
INSERT INTO `mangos_string` (`entry`, `content_default`) VALUES
(@STRING_ENTRY+0, 'Dual Specialization allows you to quickly switch between two different talent builds and action bars.'),
(@STRING_ENTRY+1, 'The cost is '),
(@STRING_ENTRY+2, 'Change my specialization.'),
(@STRING_ENTRY+3, 'You don\'t have enough money to unlock dual specialization.'),
(@STRING_ENTRY+4, 'Are you sure you would like to activate your second specialization for '),
(@STRING_ENTRY+5, ' gold? This will allow you to quickly switch between two different talent builds and action bars.'),
(@STRING_ENTRY+6, 'You are already on that spec.'),
(@STRING_ENTRY+7, '[Activate] '),
(@STRING_ENTRY+8, '[Rename] '),
(@STRING_ENTRY+9, 'Unnamed'),
(@STRING_ENTRY+10, ' (active)'),
(@STRING_ENTRY+11, 'You are in combat and cannot switch spec at this time.'),
(@STRING_ENTRY+12, 'You must exit the instance to re-spec.'),
(@STRING_ENTRY+13, 'You are mounted and cannot switch spec at this time.'),
(@STRING_ENTRY+14, 'You are dead and cannot switch spec at this time.'),
(@STRING_ENTRY+15, 'You must unlock the dual talent specialization feature first.'),
(@STRING_ENTRY+16, 'Current level is less than ten - you cannot switch spec at this time.'),
(@STRING_ENTRY+17, '|cFF0041FF[Activate] '),
(@STRING_ENTRY+18, '|cFFCC00CC[Rename] '),
(@STRING_ENTRY+19, 'Are you sure you wish to switch your talent specialization? It will log you out from the world.'),
(@STRING_ENTRY+20, 'Purchase Dual Talent Specialization'),
(@STRING_ENTRY+21, 'Can not create dual spec item!');

SET @TEXT_ID := 50700;
DELETE FROM `npc_text` WHERE `ID` BETWEEN @TEXT_ID AND @TEXT_ID+1;
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES
(@TEXT_ID, 'Dual Specialization allows you to quickly switch between two different talent builds and action bars. It requires logout to switch specialization.'),
(@TEXT_ID+1, 'Dual Specialization allows you to quickly switch between two different talent builds and action bars. It requires logout to switch specialization.');

-- item
UPDATE `item_template` SET `ScriptName`='item_custom_dualspec' WHERE  `entry`=17731;