ALTER TABLE character_db_version CHANGE COLUMN required_105_9680_01_characters_character_stats required_106_9751_01_characters bit;

ALTER TABLE `character_spell` ADD KEY `Idx_spell` (`spell`);
