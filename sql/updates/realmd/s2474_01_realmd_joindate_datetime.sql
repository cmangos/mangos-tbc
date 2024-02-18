ALTER TABLE realmd_db_version CHANGE COLUMN required_s2455_01_realmd_platform required_s2474_01_realmd_joindate_datetime bit;

ALTER TABLE `account` MODIFY joindate DATETIME NOT NULL DEFAULT NOW();


