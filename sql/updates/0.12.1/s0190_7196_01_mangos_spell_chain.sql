ALTER TABLE db_version CHANGE COLUMN required_s0150_10427_02_mangos_spell_proc_event required_s0190_7196_01_mangos_spell_chain bit;

DELETE FROM spell_chain WHERE first_spell IN (44203,42231);
INSERT INTO spell_chain VALUES
/*Tranquility*/
(44203,    0,44203,1,0),
(44205,44203,44203,2,0),
(44206,44205,44203,3,0),
(44207,44206,44203,4,0),
(44208,44207,44203,5,0),

/*Hurricane*/
(42231,    0,42231,1,0),
(42232,42231,42231,2,0),
(42233,42232,42231,3,0),
(42230,42233,42231,4,0);
