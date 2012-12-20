ALTER TABLE db_version CHANGE COLUMN required_s0806_xxxxx_01_mangos_spell_threat required_s0808_9539_01_mangos_spell_bonus_data bit;

DELETE FROM spell_bonus_data WHERE entry IN (46567);
INSERT INTO spell_bonus_data VALUES
(46567, 0,      0,       0,     'Item - Goblin Rocket Launcher');
