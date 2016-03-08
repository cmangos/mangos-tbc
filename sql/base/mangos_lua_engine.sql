
DROP TABLE IF EXISTS lua_scripts;
CREATE TABLE `lua_scripts` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `script` text NOT NULL,
  `status` enum('Enabled','Disabled') NOT NULL DEFAULT 'Disabled',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS lua_map_scripts;
CREATE TABLE `lua_map_scripts` (
  `map_id` int(10) unsigned NOT NULL,
  `script_id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`map_id`,`script_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
