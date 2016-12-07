ALTER TABLE db_version CHANGE COLUMN required_s2336_01_mangos_mangle required_s2338_01_mangos_item_extraflags bit;

UPDATE item_template SET extraFlags = 1 WHERE extraFlags != 0;