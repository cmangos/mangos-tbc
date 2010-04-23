ALTER TABLE character_db_version CHANGE COLUMN required_091_9339_01_characters_group required_066_8409_01_characters_guild bit;

ALTER TABLE group_member
  CHANGE COLUMN `groupId` `leaderGuid` int(11) unsigned NOT NULL;

UPDATE `group_member`,`groups` SET `group_member`.`leaderGuid` = `groups`.`leaderGuid` WHERE `group_member`.`leaderGuid` = `groups`.`groupId`;

ALTER TABLE groups
  DROP COLUMN `groupId`;

ALTER TABLE groups
  DROP INDEX `leaderGuid`,
  ADD PRIMARY KEY (`leaderGuid`);
