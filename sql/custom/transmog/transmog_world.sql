SET
@Entry = 190010,
@Name = "Magister Stellaria";
DELETE FROM `creature_template` WHERE `entry` = 190010;

INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `GossipMenuId`, `minlevel`, `maxlevel`, `Expansion`, `faction`, `NpcFlags`, `scale`, `rank`, `DamageSchool`, `MeleeBaseAttackTime`, `RangedBaseAttackTime`, `unitClass`, `unitFlags`, `CreatureType`, `CreatureTypeFlags`, `lootid`, `PickpocketLootId`, `SkinningLootId`, `AIName`, `MovementType`, `RacialLeader`, `RegenerateStats`, `MechanicImmuneMask`, `ExtraFlags`, `ScriptName`) VALUES
(@Entry, 2240, 0, @Name, "Transmogrifier", NULL, 0, 80, 80, 2, 35, 1, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 0, 1, 0, 0, 'npc_transmogrifier');

SET @TEXT_ID := 601083;
DELETE FROM `npc_text` WHERE `ID` BETWEEN @TEXT_ID AND @TEXT_ID+5;
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES
(@TEXT_ID, 'Transmogrification allows you to change how your items look like without changing the stats of the items.\r\nItems used in transmogrification are no longer refundable, tradeable and are bound to you.\r\n\r\nNot everything can be transmogrified with eachother.\r\nRestrictions include but are not limited to:\r\nOnly armor and weapons can be transmogrified\r\nGuns, bows and crossbows can be transmogrified with eachother\r\nFishing poles can not be transmogrified\r\nYou must be able to equip both items used in the process.\r\n\r\nTransmogrifications stay on your items as long as you own them.\r\nIf you try to put the item in guild bank or mail it to someone else, the transmogrification is stripped.\r\n\r\nYou can also remove transmogrifications for free at the transmogrifier.'),
(@TEXT_ID+1, 'You can save your own transmogrification sets.\r\n\r\nTo save, first you must transmogrify your equipped items.\r\nThen when you go to the set management menu and go to save set menu,\r\nall items you have transmogrified are displayed so you see what you are saving.\r\nIf you think the set is fine, you can click to save the set and name it as you wish.\r\n\r\nTo use a set you can click the saved set in the set management menu and then select use set.\r\nIf the set has a transmogrification for an item that is already transmogrified, the old transmogrification is lost.\r\nNote that same transmogrification restrictions apply when trying to use a set as in normal transmogrification.\r\n\r\nTo delete a set you can go to the set\'s menu and select delete set.'),
(@TEXT_ID+2, 'Select desired look for this slot.'),
(@TEXT_ID+3, 'Check price and click Confirm to change item look!'),
(@TEXT_ID+4, 'This item is already transmogrified.\r\nClick Remove to restore original look!'),
(@TEXT_ID+5, 'This item is already transmogrified.\r\nClick Remove to restore original look,\r\n\or select a different one!');

SET @STRING_ENTRY := 11100;
DELETE FROM `mangos_string` WHERE `entry` BETWEEN  @STRING_ENTRY+0 AND @STRING_ENTRY+29;
INSERT INTO `mangos_string` (`entry`, `content_default`) VALUES
(@STRING_ENTRY+0, 'Item successfully transmogrified.'),
(@STRING_ENTRY+1, 'Equipment slot is empty.'),
(@STRING_ENTRY+2, 'Invalid source item selected.'),
(@STRING_ENTRY+3, 'Source item does not exist.'),
(@STRING_ENTRY+4, 'Destination item does not exist.'),
(@STRING_ENTRY+5, 'Selected items are invalid.'),
(@STRING_ENTRY+6, 'You don''t have  enough money.'),
(@STRING_ENTRY+7, 'You don''t have enough tokens.'),
(@STRING_ENTRY+8, 'Destination item already has this transmogrification.'),
(@STRING_ENTRY+9, 'All your transmogrifications were removed.'),
(@STRING_ENTRY+10, 'Item transmogrifications were removed.'),
(@STRING_ENTRY+11, 'No transmogrification found.'),
(@STRING_ENTRY+12, 'No transmogrification found on this item.'),
(@STRING_ENTRY+13, 'Invalid name inserted.'),
(@STRING_ENTRY+14, 'Showing transmogrifieded items, relog to update the current area.'),
(@STRING_ENTRY+15, 'Hiding transmogrifieded items, relog to update the current area.'),
(@STRING_ENTRY+16, 'The selected Item is not suitable for transmogrification.'),
(@STRING_ENTRY+17, 'The selected Item cannot be used for transmogrification of the target player.'),
(@STRING_ENTRY+18, 'You have no suitable items in your inventory.'),
(@STRING_ENTRY+19, 'Remove: '),
(@STRING_ENTRY+20, '< [Back]'),
(@STRING_ENTRY+21, '< [Main Menu]'),
(@STRING_ENTRY+22, 'Before: '), 
(@STRING_ENTRY+23, 'After:'),
(@STRING_ENTRY+24, 'Cost is '),
(@STRING_ENTRY+25, 'Confirm'),
(@STRING_ENTRY+26, 'Your item: '),
(@STRING_ENTRY+27, 'Transmog: '),
(@STRING_ENTRY+28, 'Possible transmogrifications:'),
(@STRING_ENTRY+29, 'Options:');

DELETE FROM `command` WHERE `name` IN ('transmog', 'transmog add', 'transmog add set');
INSERT INTO `command` (`name`, `security`, `help`) VALUES
('transmog', 0, 'Syntax: .transmog <on/off>\nAllows seeing transmogrified items and the transmogrifier NPC.'),
('transmog add', 1, 'Syntax: .transmog add $player $item\nAdds an item to a player\'s appearance collection.'),
('transmog add set', 1, 'Syntax: .transmog add set $player $itemSet\nAdds items of an ItemSet to a player\'s appearance collection.');