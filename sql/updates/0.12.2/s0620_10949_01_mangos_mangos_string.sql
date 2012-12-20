ALTER TABLE db_version CHANGE COLUMN required_s0616_8770_01_mangos_quest_template required_s0620_10949_01_mangos_mangos_string bit;

UPDATE mangos_string SET content_default='Scripting library not found or not accessible.' WHERE entry=1166;
