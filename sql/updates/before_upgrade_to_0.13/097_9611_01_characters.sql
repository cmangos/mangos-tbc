ALTER TABLE character_db_version CHANGE COLUMN required_097_9611_01_characters required_091_9339_01_characters_group bit;

ALTER TABLE `group_member`            DROP INDEX `Idx_memberGuid`;
ALTER TABLE `guild_eventlog`          DROP INDEX `Idx_PlayerGuid1`;
ALTER TABLE `guild_eventlog`          DROP INDEX `Idx_PlayerGuid2`;
ALTER TABLE `guild_bank_eventlog`     DROP INDEX `Idx_PlayerGuid`;
ALTER TABLE `petition_sign`           DROP INDEX `Idx_playerguid`;
ALTER TABLE `petition_sign`           DROP INDEX `Idx_ownerguid`;
ALTER TABLE `guild_eventlog`          DROP INDEX `Idx_LogGuid`;
ALTER TABLE `guild_bank_eventlog`     DROP INDEX `Idx_LogGuid`;
ALTER TABLE `guild_bank_item`         DROP INDEX `Idx_item_guid`;
ALTER TABLE `corpse`                  DROP INDEX `Idx_player`;
ALTER TABLE `corpse`                  DROP INDEX `Idx_time`;
ALTER TABLE `guild_rank`              DROP INDEX `Idx_rid`;
