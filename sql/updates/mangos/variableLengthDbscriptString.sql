DROP TABLE IF EXISTS `dbscript_string_template`;
CREATE TABLE `dbscript_string_template` (
  `id` int(11) unsigned NOT NULL COMMENT 'Id of template' AUTO_INCREMENT,
  `string_id` int(11) NOT NULL DEFAULT '0' COMMENT 'db_script_string id',
  PRIMARY KEY (`id`,`string_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT='DBScript system';

ALTER TABLE dbscripts_on_creature_death ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;
ALTER TABLE dbscripts_on_creature_movement ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;
ALTER TABLE dbscripts_on_event ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;
ALTER TABLE dbscripts_on_go_template_use ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;
ALTER TABLE dbscripts_on_go_use ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;
ALTER TABLE dbscripts_on_gossip ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;
ALTER TABLE dbscripts_on_promo_code_use ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;
ALTER TABLE dbscripts_on_quest_end ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;
ALTER TABLE dbscripts_on_quest_start ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;
ALTER TABLE dbscripts_on_spell ADD COLUMN datalong3 INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER datalong2;

UPDATE dbscripts_on_creature_death SET datalong=0 WHERE command=0;
UPDATE dbscripts_on_creature_movement SET datalong=0 WHERE command=0;
UPDATE dbscripts_on_event SET datalong=0 WHERE command=0;
UPDATE dbscripts_on_go_template_use SET datalong=0 WHERE command=0;
UPDATE dbscripts_on_go_use SET datalong=0 WHERE command=0;
UPDATE dbscripts_on_gossip SET datalong=0 WHERE command=0;
UPDATE dbscripts_on_promo_code_use SET datalong=0 WHERE command=0;
UPDATE dbscripts_on_quest_end SET datalong=0 WHERE command=0;
UPDATE dbscripts_on_quest_start SET datalong=0 WHERE command=0;
UPDATE dbscripts_on_spell SET datalong=0 WHERE command=0;


