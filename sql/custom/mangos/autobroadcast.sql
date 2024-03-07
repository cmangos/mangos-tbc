DROP TABLE IF EXISTS `autobroadcast`;
CREATE TABLE IF NOT EXISTS `autobroadcast` (
  `id` tinyint unsigned NOT NULL AUTO_INCREMENT,
  `content` text,
  `ratio` smallint unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3;

INSERT INTO tbcmangos.mangos_string
(entry, content_default, content_loc1, content_loc2, content_loc3, content_loc4, content_loc5, content_loc6, content_loc7, content_loc8)
VALUES(10000, '|cffff0000[Server Announce]:|r %s', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);