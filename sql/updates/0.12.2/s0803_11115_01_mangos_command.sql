ALTER TABLE db_version CHANGE COLUMN required_s0794_xxxxx_01_mangos_spell_threat required_s0803_11115_01_mangos_command bit;

DELETE FROM command WHERE name IN ('gm online','gm setview');

INSERT INTO command (name, security, help) VALUES
('gm setview',1,'Syntax: .gm setview\r\n\r\nSet farsight view on selected unit. Select yourself to set view back.');

