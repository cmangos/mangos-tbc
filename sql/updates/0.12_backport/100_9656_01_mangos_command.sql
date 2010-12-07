ALTER TABLE db_version CHANGE COLUMN required_099_9636_01_mangos_item_template required_100_9656_01_mangos_command bit;

DELETE FROM command WHERE name IN ('list talents');
INSERT INTO command VALUES
('list talents',3,'Syntax: .list talents\r\n\r\nShow list all really known (as learned spells) talent rank spells for selected player or self.');
