ALTER TABLE db_version CHANGE COLUMN required_s2369_01_mangos_spell_affect required_s2370_01_mangos_creatures bit;

UPDATE creature SET spawntimesecsmax = spawntimesecsmin WHERE spawntimesecsmax < spawntimesecsmin;
