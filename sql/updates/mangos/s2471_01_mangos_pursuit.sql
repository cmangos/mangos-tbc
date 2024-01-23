ALTER TABLE db_version CHANGE COLUMN required_s2470_01_mangos_worldstate_expression_spawn_group required_s2471_01_mangos_pursuit bit;

UPDATE creature_template SET Pursuit=15000 WHERE Pursuit=0;


