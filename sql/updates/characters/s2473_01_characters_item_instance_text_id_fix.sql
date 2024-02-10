ALTER TABLE character_db_version CHANGE COLUMN required_s2452_01_characters_fishingSteps required_s2473_01_characters_item_instance_text_id_fix bit;


-- did not correspond to core load and item_text column and packet field width
ALTER TABLE item_instance MODIFY `itemTextId` INT UNSIGNED NOT NULL DEFAULT 0;

