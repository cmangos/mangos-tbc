ALTER TABLE character_db_version CHANGE COLUMN required_s0099_10332_02_characters_pet_aura required_s0114_09136_01_characters_character_ticket bit;

alter table `character_ticket`
    add column `response_text` text CHARSET utf8 COLLATE utf8_general_ci NULL after `ticket_text`;
