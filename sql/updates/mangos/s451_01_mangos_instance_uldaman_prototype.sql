SET @SGGUID := 7000000; -- spawn_group
SET @CGUID := 7000000; -- creatures

-- Scorpid Group before Enchanting Trainer Annora
DELETE FROM spawn_group WHERE Id IN (7000000, 7000001);
INSERT INTO `spawn_group` (`Id`, `Name`, `Type`, `MaxCount`,  `WorldState`, `Flags`) VALUES 
(@SGGUID, 'Uldaman - Cleft Scorpid Group - Annora', '0', '10', '0', '3'),
(@SGGUID+1, 'Uldaman - Annora', '0', '1', '12002', '0');

DELETE FROM spawn_group_spawn WHERE Id IN (7000000, 7000001);
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
(@SGGUID, @CGUID+205, '0'),
(@SGGUID+1, @CGUID+324, '0');

-- Put Annora into an spawn_group with worldstate, let her spawn when all scorpids are dead
-- add waypoints
UPDATE `creature_template` SET `MovementType`='0' WHERE (`Entry`='11073');
UPDATE `creature` SET `MovementType`='2' WHERE (`guid`='7000324');

DELETE FROM spawn_group_formation WHERE Id = 7000001;
INSERT INTO `spawn_group_formation` (`Id`, `PathId`, `MovementType`, `Comment`) VALUES 
(@SGGUID+1, '11073', '2', 'Uldaman - Annora');

DELETE FROM waypoint_path WHERE PathId = 11073;
INSERT INTO `waypoint_path` (`PathId`, `Point`, `PositionX`, `PositionY`, `PositionZ`, `Orientation`, `WaitTime`, `ScriptId`) VALUES
(11073,1,-164.49715,205.28552,-49.91232,100,0,0),
(11073,2,-164.49715,205.28552,-49.91232,100,0,0),
(11073,3,-164.1184,212.61917,-49.205986,100,1000,3);

DELETE FROM waypoint_path WHERE PathId = 11072;
INSERT INTO `waypoint_path_name` (`PathId`, `Name`) VALUES 
('11072', 'Uldaman - Andora waypoints');

DELETE FROM worldstate_name WHERE Id = 20000;
INSERT INTO `worldstate_name` (`Id`, `Name`) VALUES 
('20000', 'Uldaman - Andora Spawn');

DELETE FROM conditions WHERE condition_entry = 12002;
INSERT INTO `conditions` (`condition_entry`, `type`, `value1`, `value3`, `comments`) VALUES 
('12002', '42', '20000', '1', 'Uldaman - Andora Spawn');

