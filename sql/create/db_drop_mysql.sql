REVOKE ALL PRIVILEGES ON * . * FROM 'mangos'@'localhost';

REVOKE ALL PRIVILEGES ON `tbcmangos` . * FROM 'mangos'@'localhost';

REVOKE GRANT OPTION ON `tbcmangos` . * FROM 'mangos'@'localhost';

REVOKE ALL PRIVILEGES ON `tbccharacters` . * FROM 'mangos'@'localhost';

REVOKE GRANT OPTION ON `tbccharacters` . * FROM 'mangos'@'localhost';

REVOKE ALL PRIVILEGES ON `tbcrealmd` . * FROM 'mangos'@'localhost';

REVOKE GRANT OPTION ON `tbcrealmd` . * FROM 'mangos'@'localhost';

DELETE FROM `user` WHERE CONVERT( User USING utf8 ) = CONVERT( 'mangos' USING utf8 ) AND CONVERT( Host USING utf8 ) = CONVERT( 'localhost' USING utf8 ) ;

DROP DATABASE IF EXISTS `tbcmangos` ;

DROP DATABASE IF EXISTS `tbccharacters` ;

DROP DATABASE IF EXISTS `tbcrealmd` ;
