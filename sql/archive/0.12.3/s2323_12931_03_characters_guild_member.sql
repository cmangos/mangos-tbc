ALTER TABLE character_db_version CHANGE COLUMN required_s2323_12931_02_characters_guild_bank_tab required_s2323_12931_03_characters_guild_member bit;

ALTER TABLE `guild_member` CHANGE `pnote` `pnote` varchar(31) NOT NULL DEFAULT '';
ALTER TABLE `guild_member` CHANGE `offnote` `offnote` varchar(31) NOT NULL DEFAULT '';
