ALTER TABLE character_db_version CHANGE COLUMN required_s0224_10503_02_characters_gameobject_respawn required_s0384_10664_01_characters_arena_team_stats bit;

ALTER TABLE arena_team_stats
  CHANGE COLUMN games  games_week   int(10) unsigned NOT NULL default '0',
  CHANGE COLUMN wins   wins_week    int(10) unsigned NOT NULL default '0',
  CHANGE COLUMN played games_season int(10) unsigned NOT NULL default '0',
  CHANGE COLUMN wins2  wins_season  int(10) unsigned NOT NULL default '0';
