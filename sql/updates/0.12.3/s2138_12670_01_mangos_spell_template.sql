ALTER TABLE db_version CHANGE COLUMN required_s2128_12654_01_mangos_creature_template_power required_s2138_12670_01_mangos_spell_template bit;

DELETE FROM spell_template WHERE id=21883;
INSERT INTO spell_template VALUES
(21883, 0x00000180, 101, 225,  76,  22,   0,   0, 178904, 0,     0,     'Summon Healed Celebrian Vine');
