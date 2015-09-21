ALTER TABLE character_db_version CHANGE COLUMN required_s0201_7255_01_characters_characters required_s0216_7307_01_characters_arena_team_member bit;

ALTER TABLE arena_team_member
  ADD PRIMARY KEY  (arenateamid,guid);
