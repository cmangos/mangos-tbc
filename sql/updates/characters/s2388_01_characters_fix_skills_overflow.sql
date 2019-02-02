ALTER TABLE character_db_version CHANGE COLUMN required_s2387_01_characters_weapon_skills_fix_tbc required_s2388_01_characters_fix_skills_overflow bit;

UPDATE `character_skills` SET `value` = `max` WHERE `value` > `max`;
