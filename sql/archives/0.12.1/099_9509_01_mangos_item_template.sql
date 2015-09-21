ALTER TABLE db_version CHANGE COLUMN required_098_9622_01_mangos_gameobject required_099_9509_01_mangos_item_template bit;

alter table item_template
  add column NonConsumable tinyint(1) UNSIGNED DEFAULT '0' NOT NULL after Duration;
