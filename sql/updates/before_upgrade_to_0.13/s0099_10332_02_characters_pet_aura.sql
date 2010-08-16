ALTER TABLE character_db_version CHANGE COLUMN required_s0099_10332_02_characters_pet_aura required_s0099_10332_01_characters_character_aura bit;

DELETE FROM `pet_aura` WHERE item_guid <> 0;

ALTER TABLE `pet_aura`
  DROP PRIMARY KEY,
  ADD PRIMARY KEY  (`guid`,`caster_guid`,`spell`,`effect_index`),
  DROP COLUMN `item_guid`;
