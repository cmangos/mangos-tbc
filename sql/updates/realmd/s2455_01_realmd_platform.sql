ALTER TABLE realmd_db_version CHANGE COLUMN required_s2433_01_realmd_anticheat required_s2455_01_realmd_platform bit;

ALTER TABLE account ADD COLUMN `platform` VARCHAR(4) NOT NULL DEFAULT '0' AFTER `os`;


