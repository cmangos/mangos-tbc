ALTER TABLE db_version CHANGE COLUMN required_s0190_7199_03_mangos_spell_bonus_data required_s0199_7242_01_mangos_spell_bonus_data bit;

DELETE FROM spell_bonus_data WHERE entry IN (34913);
INSERT INTO spell_bonus_data VALUES
 (34913, 0, 0, 0, 'Mage - Molten Armor Triggered');
