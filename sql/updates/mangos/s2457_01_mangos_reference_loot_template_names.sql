ALTER TABLE db_version CHANGE COLUMN required_s2456_01_mangos_aggro_range required_s2457_01_mangos_reference_loot_template_names bit;

CREATE TABLE `reference_loot_template_names` (
  `entry` int unsigned NOT NULL DEFAULT '0',
  `name` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`entry`)
)COMMENT='Reference Loot Template Names';

