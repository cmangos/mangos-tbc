ALTER TABLE creature CHANGE spawntimesecs spawntimesecsmin INT(10) UNSIGNED DEFAULT 120 NOT NULL COMMENT 'Creature respawn time minimum';
ALTER TABLE gameobject CHANGE spawntimesecs spawntimesecsmin INT(11) DEFAULT 0 NOT NULL COMMENT 'Gameobject respawn time minimum';

ALTER TABLE creature ADD spawntimesecsmax INT(10) UNSIGNED DEFAULT 120 NOT NULL COMMENT 'Creature respawn time maximum' AFTER spawntimesecsmin;
ALTER TABLE gameobject ADD spawntimesecsmax INT(11) DEFAULT 0 NOT NULL COMMENT 'Gameobject respawn time maximum' AFTER spawntimesecsmin;


