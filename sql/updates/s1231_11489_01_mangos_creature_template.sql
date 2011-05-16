ALTER TABLE db_version CHANGE COLUMN required_s1201_11452_01_mangos_spell_bonus_data required_s1231_11489_01_mangos_creature_template bit;

UPDATE creature_template SET flags_extra=flags_extra|0x00000400 WHERE npcflag=npcflag|0x10000000;
UPDATE creature_template SET npcflag=npcflag &~ 0x10000000;
