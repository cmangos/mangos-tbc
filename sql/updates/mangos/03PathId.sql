ALTER TABLE creature_movement_template ADD pathId int(11) unsigned NOT NULL DEFAULT '0' COMMENT 'Path ID for entry' AFTER entry, DROP PRIMARY KEY, ADD PRIMARY KEY (entry, pathId, point);


