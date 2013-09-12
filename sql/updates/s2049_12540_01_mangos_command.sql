ALTER TABLE db_version CHANGE COLUMN required_s2034_12522_01_mangos_db_script_string required_s2049_12540_01_mangos_command bit;

UPDATE `command` SET help = 'Syntax: .account create $account $password [$expansion]\r\n\r\nCreate account and set password to it. Optionally, you may also set another expansion for this account than the defined default value.' WHERE name = 'account create';
