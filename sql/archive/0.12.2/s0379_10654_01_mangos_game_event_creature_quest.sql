ALTER TABLE db_version CHANGE COLUMN required_s0378_xxxxx_01_mangos_spell_proc_event required_s0379_10654_01_mangos_game_event_creature_quest bit;

ALTER TABLE game_event_creature_quest DROP PRIMARY KEY;
ALTER TABLE game_event_creature_quest ADD PRIMARY KEY (id,quest,event);
