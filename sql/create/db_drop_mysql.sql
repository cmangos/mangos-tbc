REVOKE ALL ON `tbcmangos`.* FROM 'mangos'@'localhost';

REVOKE ALL ON `tbccharacters`.* FROM 'mangos'@'localhost';

REVOKE ALL ON `tbcrealmd`.* FROM 'mangos'@'localhost';

DROP USER 'mangos'@'localhost';

DROP DATABASE IF EXISTS `tbcmangos`;

DROP DATABASE IF EXISTS `tbccharacters`;

DROP DATABASE IF EXISTS `tbcrealmd`;
