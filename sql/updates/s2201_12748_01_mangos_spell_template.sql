ALTER TABLE db_version CHANGE COLUMN required_s2171_12759_01_mangos_spell_chain required_s2201_12748_01_mangos_spell_template bit;

DELETE FROM spell_template WHERE id IN (11756,19394);
INSERT INTO spell_template VALUES
(11756, 0x00000180, 101,   4,  76,  47,   0,   0, 144064, 0,     0,     'Summon Gordunni chest (COBALT)'),
(19394, 0x00000180, 101,   4,  76,  47,   0,   0, 177681, 0,     0,     'Summon Gordunni chest (JUNK)');
