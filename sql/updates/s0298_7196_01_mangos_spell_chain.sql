ALTER TABLE db_version CHANGE COLUMN required_s0283_7472_01_mangos_mangos_string required_s0298_7196_01_mangos_spell_chain bit;

DELETE FROM spell_chain WHERE spell_id IN (5672, 6371, 6372, 10460, 10461, 25566);
INSERT INTO spell_chain (spell_id, prev_spell, first_spell, rank, req_spell) VALUES
/* Healing Stream */
(5672,0,5672, 1,0),
(6371,5672,5672,2,0),
(6372,6371,5672,3,0),
(10460,6372,5672,4,0),
(10461,10460,5672,5,0),
(25566,10461,5672,6,0);
