DROP TABLE IF EXISTS `dbscript_string`;
RENAME TABLE `db_script_string` TO `dbscript_string`;

ALTER TABLE conditions
ADD comments varchar(300) AFTER value2;


