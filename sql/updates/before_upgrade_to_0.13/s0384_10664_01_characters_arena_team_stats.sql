ALTER TABLE character_db_version CHANGE COLUMN required_s0384_10664_01_characters_arena_team_stats required_s0224_10503_02_characters_gameobject_respawn bit;

ALTER TABLE arena_team_stats
  CHANGE COLUMN games_week   games  int(10) unsigned NOT NULL default '0',
  CHANGE COLUMN wins_week    wins   int(10) unsigned NOT NULL default '0',
  CHANGE COLUMN games_season played int(10) unsigned NOT NULL default '0',
  CHANGE COLUMN wins_season  wins2  int(10) unsigned NOT NULL default '0';
