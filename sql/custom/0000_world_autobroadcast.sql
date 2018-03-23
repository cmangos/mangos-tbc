DROP TABLE IF EXISTS `autobroadcast`;

--
-- Table structure for table `autobroadcast`
--

CREATE TABLE `autobroadcast` (
`id` int(11) NOT NULL AUTO_INCREMENT,
`text` longtext NOT NULL,
PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;

--
-- Data for table `autobroadcast`
--

DELETE FROM `mangos_string` WHERE `entry` = 11000;
INSERT INTO `mangos_string` VALUES (11000, '|cffffcc00[autobroadcast]: |r|cff00ff00%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

DELETE FROM `command` WHERE `name` = 'reload autobroadcast';
INSERT INTO `command` VALUES ('reload autobroadcast', 3, 'Syntax: .reload autobroadcast\nReload autobroadcast table.');