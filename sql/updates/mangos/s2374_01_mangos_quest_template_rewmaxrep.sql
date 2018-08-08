ALTER TABLE db_version CHANGE COLUMN required_s2373_01_mangos_creature_waypoint_refurbishing required_s2374_01_mangos_quest_template_rewmaxrep bit;

ALTER TABLE quest_template
MODIFY RewMaxRepValue1 mediumint(9) NOT NULL DEFAULT '42999',
MODIFY RewMaxRepValue2 mediumint(9) NOT NULL DEFAULT '42999',
MODIFY RewMaxRepValue3 mediumint(9) NOT NULL DEFAULT '42999',
MODIFY RewMaxRepValue4 mediumint(9) NOT NULL DEFAULT '42999',
MODIFY RewMaxRepValue5 mediumint(9) NOT NULL DEFAULT '42999';
UPDATE quest_template SET RewMaxRepValue1=42999 WHERE RewMaxRepValue1=0;
UPDATE quest_template SET RewMaxRepValue2=42999 WHERE RewMaxRepValue2=0;
UPDATE quest_template SET RewMaxRepValue3=42999 WHERE RewMaxRepValue3=0;
UPDATE quest_template SET RewMaxRepValue4=42999 WHERE RewMaxRepValue4=0;
UPDATE quest_template SET RewMaxRepValue5=42999 WHERE RewMaxRepValue5=0;


