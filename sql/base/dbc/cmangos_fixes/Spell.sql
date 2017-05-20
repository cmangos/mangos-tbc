INSERT INTO spell_template(Id,ProcFlags,ProcChance,DurationIndex,Effect1,EffectImplicitTargetA1,EffectRadiusIndex1,EffectApplyAuraName1,EffectMiscValue1,EffectMiscValueB1,EffectTriggerSpell1,IsServerSide,SpellName) VALUES
('11756','384','101','4','76','47','0','0','144064','0','0','1','Summon Gordunni chest (COBALT)'),
('19394','384','101','4','76','47','0','0','177681','0','0','1','Summon Gordunni chest (JUNK)'),
('21387','40','15','21','6','1','0','42','0','0','21388','1','Melt-Weapon trigger aura related used by Ragnaros'),
('21883','384','101','225','76','22','0','0','178904','0','0','1','Summon Healed Celebrian Vine'),
('23363','0','101','21','76','18','0','0','179804','0','0','1','Summon Drakonid Corpse Trigger'),
('25192','0','101','21','76','18','0','0','180619','0','0','1','Summon Ossirian Crystal'),
('26096','0','101','21','76','32','7','0','180794','0','0','1','Jandice Drops Journal'),
('26133','0','101','21','76','18','0','0','180795','0','0','1','Summon Sandworm Base'),
('27627','0','101','21','76','32','14','0','181068','0','0','1','Drop Obsidian'),
('27630','0','101','21','76','32','14','0','181069','0','0','1','Drop Obsidian'),
('31338','0','101','3','28','32','8','0','18120','64','0','1','Summon Ogre'),
('34810','0','101','21','28','42','8','0','20083','64','0','1','Summon Summoned Bloodwarder Mender behind of the caster'),
('34817','0','101','21','28','44','8','0','20078','64','0','1','Summon Summoned Bloodwarder Reservist right of the caster'),
('34818','0','101','21','28','43','8','0','20078','64','0','1','Summon Summoned Bloodwarder Reservist left of the caster'),
('34819','0','101','21','28','41','8','0','20078','64','0','1','Summon Summoned Bloodwarder Reservist front of the caster'),
('35153','0','101','21','28','42','8','0','20405','64','0','1','Summon Nether Charge behind of the caster'),
('35904','0','101','21','28','44','8','0','20405','64','0','1','Summon Nether Charge right of the caster'),
('35905','0','101','21','28','43','8','0','20405','64','0','1','Summon Nether Charge left of the caster'),
('35906','0','101','21','28','41','8','0','20405','64','0','1','Summon Nether Charge front of the caster'),
('37264','0','101','21','28','18','7','0','21729','64','0','1','Power Converters: Summon Electromental (from cata)'),
('37278','0','101','21','28','18','1','0','21737','64','0','1','Power Converters: Summon Mini-Electromental (from cata)'),
('37365','0','101','21','28','18','1','0','21757','64','0','1','Power Converters: Summon Big Flavor Electromental (from cata)'),
('37492','0','0','0','61','0','0','0','13852','0','0','1','BOX O TRICKS EVENT TRIGGER'),
('39240','0','101','4','28','41','8','0','22483','64','0','1','Summon Summon Sand Gnome front of the caster'),
('39241','0','101','4','28','41','8','0','22482','64','0','1','Summon Mature Bone Sifter front of the caster'),
('42456','0','0','9','76','47','0','0','185318','0','0','1','Summon smoke object'),
('42467','0','0','8','76','47','0','0','185319','0','0','1','Summon fire object'),
('44920','0','101','21','6','1','0','56','24941','0','0','1','Model - Shattered Sun Marksman - BE Male Tier 4'),
('44924','0','101','21','6','1','0','56','24945','0','0','1','Model - Shattered Sun Marksman - BE Female Tier 4'),
('44928','0','101','21','6','1','0','56','24949','0','0','1','Model - Shattered Sun Marksman - Draenei Male Tier 4'),
('44932','0','101','21','6','1','0','56','24953','0','0','1','Model - Shattered Sun Marksman - Draenei Female Tier 4'),
('45158','0','101','21','6','1','0','56','25119','0','0','1','Model - Shattered Sun Warrior - BE Female Tier 4'),
('45162','0','101','21','6','1','0','56','25123','0','0','1','Model - Shattered Sun Warrior - BE Male Tier 4'),
('45166','0','101','21','6','1','0','56','25127','0','0','1','Model - Shattered Sun Warrior - Draenei Female Tier 4'),
('45170','0','101','21','6','1','0','56','25131','0','0','1','Model - Shattered Sun Warrior - Draenei Male Tier 4'),
('45787','0','101','21','6','1','0','4','0','0','0','1','Talbuk Tag Sleep');

-- wotlk backport
INSERT INTO spell_template(Id, Attributes, AttributesEx,AttributesEx2,AttributesEx3,ProcFlags,ProcChance,DurationIndex,Effect1,EffectImplicitTargetA1,EffectImplicitTargetB1,EffectRadiusIndex1,EffectApplyAuraName1,EffectMiscValue1,EffectMiscValueB1,EffectTriggerSpell1,IsServerSide,SpellName) VALUES
('38854','384','0','0','0','0','101','3','28','18','0','0','0','22339','64','0','1','summon Redeemet Hatchling'),
('38865','384','0','0','0','0','101','3','28','18','0','0','0','22337','64','0','1','summon Malevolent Hatchling');

-- trap used to tame bear is no longer present in TBC/WOTLK yet still present in trap data
INSERT INTO spell_template (Id, Attributes, CastingTimeIndex, ProcChance, SpellLevel, RangeIndex, EquippedItemClass, Effect1, EffectDieSides1, EffectBaseDice1, EffectDicePerLevel1, EffectImplicitTargetA1, SpellIconID, SpellName, MaxTargetLevel, DmgMultiplier1, DmgMultiplier2, DmgMultiplier3, IsServerSide) VALUES
('9439', '256', '1', '101', '1', '12', '-1', '3', '1', '1', '0', '38', '1', 'Bear Captured in Trap', '60', '1', '1', '1', '1');

-- Feed Captured Animal for q.9440 'Little Morsels' - prevent LOS from cage gameobjects
UPDATE spell_template SET AttributesEx2=AttributesEx2|4 WHERE id IN (29916, 29917);

-- generic proc double attack used in a lot of TBC instances based on sniffs
INSERT INTO spell_template (Id, Category, Attributes, CastingTimeIndex, ProcChance, BaseLevel, SpellLevel, RangeIndex, EquippedItemClass, Effect1, EffectDieSides1, EffectBaseDice1, EffectImplicitTargetA1, SpellIconID, SpellName, DmgClass, PreventionType, DmgMultiplier1, DmgMultiplier2, DmgMultiplier3, IsServerSide) VALUES
('18941', '65', '262416', '1', '101', '14', '14', '1', '-1', '19', '1', '1', '1', '108', 'Double Attack', '2', '2', '1', '1', '1', '1');

-- Spells used in Ragnaros encounter
INSERT INTO `spell_template` (`Id`,`Attributes`,`CastingTimeIndex`,`ProcChance`,`DurationIndex`,`RangeIndex`,`EquippedItemClass`,`Effect1`,`EffectImplicitTargetA1`,`EffectRadiusIndex1`,`EffectMiscValue1`,`SpellIconID`,`SpellName`,`DmgMultiplier1`) VALUES 
('21108','256','1','101','0','13','-1','3','0','16','0','876','Summon Sons of Flame','1'),
('21110','256','1','101','30','13','-1','28','17','16','12143','876','Summon Son of Flame B','1'),
('21111','256','1','101','30','13','-1','28','17','16','12143','876','Summon Son of Flame C','1'),
('21112','256','1','101','30','13','-1','28','17','16','12143','876','Summon Son of Flame D','1'),
('21113','256','1','101','30','13','-1','28','17','16','12143','876','Summon Son of Flame E','1'),
('21114','256','1','101','30','13','-1','28','17','16','12143','876','Summon Son of Flame F','1'),
('21115','256','1','101','30','13','-1','28','17','16','12143','876','Summon Son of Flame G','1'),
('21116','256','1','101','30','13','-1','28','17','16','12143','876','Summon Son of Flame H','1'),
('21117','256','1','101','30','13','-1','28','17','16','12143','876','Summon Son of Flame A','1'),
('21908','256','1','101','0','1','-1','3','1','0','0','1','Lava Burst Randomizer','1');

-- ServerSide 'Fire Shield'
INSERT INTO spell_template (Id,Dispel,Attributes,CastingTimeIndex,ProcChance,BaseLevel,SpellLevel,DurationIndex,RangeIndex,EquippedItemClass,EquippedItemSubClassMask,Effect1,EffectDieSides1,EffectBaseDice1,EffectImplicitTargetA1,EffectApplyAuraName1,EffectAmplitude1,EffectTriggerSpell1,DmgMultiplier1,DmgMultiplier2,DmgMultiplier3,SchoolMask,IsServerSide,SpellName) VALUES
('13377','1','2512','1','101','40','40','21','1','-1','-1','6','1','1','21','23','3000','13376','1','1','1','2','1','Fire Shield');
-- ServerSide 'Hate to 90%'
INSERT INTO spell_template (Id,Attributes,CastingTimeIndex,ProcFlags,ProcChance,DurationIndex,RangeIndex,EquippedItemClass,Effect1,EffectDieSides1,EffectImplicitTargetA1,EffectApplyAuraName1,EffectTriggerSpell1,DmgMultiplier1,DmgMultiplier2,DmgMultiplier3,SchoolMask,IsServerSide,SpellName) VALUES
('19195','464','1','20','100','21','1','-1','6','1','1','42','9204','1','1','1','1','1','Hate to 90%');
-- ServerSide 'Firesworn Eruption Trigger'
INSERT INTO spell_template (Id,Attributes, AttributesEx,CastingTimeIndex,ProcChance,BaseLevel,SpellLevel,DurationIndex,RangeIndex,EquippedItemClass,Effect1,Effect2,EffectDieSides1,EffectImplicitTargetA1,EffectImplicitTargetA2,EffectApplyAuraName1,EffectMiscValue1,EffectMiscValue2,DmgClass,PreventionType,DmgMultiplier1,DmgMultiplier2,SchoolMask,IsServerSide,SpellName) VALUES
('20482','128','268468224','1','101','62','62','21','13','-1','6','108','1','38','38','77','18','18','1','1','1','1','1','1','Firesworn Eruption Trigger');
-- ServerSide 'Immunity'
INSERT INTO spell_template (Id,Attributes, AttributesEx, AttributesEx2, CastingTimeIndex,ProcChance,BaseLevel,SpellLevel,DurationIndex,RangeIndex,StackAmount,EquippedItemClass,Effect1,Effect2,EffectDieSides1,EffectBaseDice1,EffectImplicitTargetA1,EffectImplicitTargetA2,EffectImplicitTargetB1,EffectImplicitTargetB2,EffectRadiusIndex1,EffectRadiusIndex2,EffectApplyAuraName1,EffectApplyAuraName2,EffectMiscValue1,EffectMiscValue2,DmgClass,PreventionType,DmgMultiplier1,DmgMultiplier2,SchoolMask,IsServerSide,SpellName) VALUES
('21087','256','268468360','4','1','101','62','62','30','1','10','-1','6','6','1','5','22','22','7','7','12','12','77','38','17','5','1','1','1','1','1','1','Immunity');
-- ServerSide 'Spawn Vekniss Hatchlings'
INSERT INTO spell_template (Id,Attributes,CastingTimeIndex,ProcChance,DurationIndex,RangeIndex,EquippedItemClass,Effect1,EffectDieSides1,EffectBaseDice1,EffectImplicitTargetA1,EffectRadiusIndex1,EffectMiscValue1,EffectMiscValueB1,DmgMultiplier1,SchoolMask,IsServerSide,SpellName) VALUES
('26630','256','1','101','25','1','-1','28','1','3','17','15','15962','64','1','1','1','Spawn Vekniss Hatchlings');
-- ServerSide 'Spawn Vekniss Hatchlings'
INSERT INTO spell_template (Id,Attributes,CastingTimeIndex,ProcChance,DurationIndex,RangeIndex,EquippedItemClass,Effect1,EffectDieSides1,EffectBaseDice1,EffectImplicitTargetA1,EffectRadiusIndex1,EffectMiscValue1,EffectMiscValueB1,DmgMultiplier1,SchoolMask,IsServerSide,SpellName) VALUES
('26631','256','1','101','25','1','-1','28','1','3','17','15','15962','64','1','1','1','Spawn Vekniss Hatchlings');
-- ServerSide 'Spawn Vekniss Hatchlings'
INSERT INTO spell_template (Id,Attributes,CastingTimeIndex,ProcChance,DurationIndex,RangeIndex,EquippedItemClass,Effect1,EffectDieSides1,EffectBaseDice1,EffectImplicitTargetA1,EffectRadiusIndex1,EffectMiscValue1,EffectMiscValueB1,DmgMultiplier1,SchoolMask,IsServerSide,SpellName) VALUES
('26632','256','1','101','25','1','-1','28','1','3','17','15','15962','64','1','1','1','Spawn Vekniss Hatchlings');

