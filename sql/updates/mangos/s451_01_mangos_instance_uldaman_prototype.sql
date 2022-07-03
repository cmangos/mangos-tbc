SET @SGGUID := 7000000; -- spawn_group
SET @CGUID := 7000000; -- creatures

-- Scorpid Group before Enchanting Trainer ' Annora'
DELETE FROM spawn_group WHERE Id = @SGGUID;
INSERT INTO `spawn_group` (`Id`, `Name`, `Type`, `MaxCount`, `Flags`) VALUES 
(@SGGUID, 'Uldaman - Cleft Scorpid Group - Annora', '0', '10', '3');

DELETE FROM spawn_group_spawn WHERE Id = @SGGUID;
INSERT INTO `spawn_group_spawn` (`Id`, `Guid`, `SlotId`) VALUES 
(@SGGUID, @CGUID+203, '0'),
(@SGGUID, @CGUID+207, '0'),
(@SGGUID, @CGUID+201, '0'),
(@SGGUID, @CGUID+206, '0'),
(@SGGUID, @CGUID+202, '0'),
(@SGGUID, @CGUID+200, '0'),
(@SGGUID, @CGUID+209, '0'),
(@SGGUID, @CGUID+204, '0'),
(@SGGUID, @CGUID+208, '0'),
(@SGGUID, @CGUID+205, '0');

-- Delete Annora, gets spawned via core
DELETE FROM creature WHERE guid = 7000324;
UPDATE `creature_template` SET `MovementType`='0' WHERE (`Entry`='11073');