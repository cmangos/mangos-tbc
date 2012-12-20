ALTER TABLE db_version CHANGE COLUMN required_s0298_7196_02_mangos_spell_bonus_data required_s0308_7560_01_mangos_gameobject_template bit;

ALTER TABLE gameobject_template
  ADD COLUMN IconName varchar(100) NOT NULL default '' AFTER name;
