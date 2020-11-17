ALTER TABLE db_version CHANGE COLUMN required_s2414_01_mangos_ability_sets required_s2416_01_mangos_command_ahbot bit;

DELETE FROM command WHERE name LIKE 'ahbot%';
