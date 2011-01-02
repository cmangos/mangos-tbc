ALTER TABLE db_version CHANGE COLUMN required_s0612_xxxxx_02_mangos_spell_chain required_s0616_8770_01_mangos_quest_template bit;

ALTER TABLE quest_template
  CHANGE COLUMN QuestLevel QuestLevel smallint(6) NOT NULL DEFAULT 0;
