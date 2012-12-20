ALTER TABLE db_version CHANGE COLUMN required_s0038_10251_01_mangos_command required_s0039_10244_01_mangos_command bit;

DELETE FROM command WHERE name = 'stable';
INSERT INTO command (name, security, help) VALUES
('stable',3,'Syntax: .stable\r\n\r\nShow your pet stable.');
