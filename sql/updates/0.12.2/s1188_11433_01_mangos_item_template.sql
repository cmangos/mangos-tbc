ALTER TABLE db_version CHANGE COLUMN required_s1180_xxxxx_01_mangos_spell_bonus_data required_s1188_11433_01_mangos_item_template bit;

UPDATE item_template
  SET ScriptName = '' WHERE ScriptName = 'internalItemHandler';

