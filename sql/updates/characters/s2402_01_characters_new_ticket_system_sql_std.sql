ALTER TABLE character_db_version CHANGE COLUMN required_s2401_01_characters_new_ticket_system required_s2402_01_characters_new_ticket_system_sql_std bit;

--
-- Apply standard compliant structure for table `gm_tickets`
--

ALTER TABLE `gm_tickets` MODIFY COLUMN `created` bigint(40) unsigned NOT NULL;
ALTER TABLE `gm_tickets` MODIFY COLUMN `updated` bigint(40) unsigned NOT NULL DEFAULT 0;
ALTER TABLE `gm_tickets` MODIFY COLUMN `seen` bigint(40) unsigned NOT NULL DEFAULT 0;
ALTER TABLE `gm_tickets` MODIFY COLUMN `answered` bigint(40) unsigned NOT NULL DEFAULT 0;
ALTER TABLE `gm_tickets` MODIFY COLUMN `closed` bigint(40) unsigned NOT NULL DEFAULT 0;
ALTER TABLE `gm_tickets` MODIFY COLUMN `conclusion` varchar(255) NOT NULL DEFAULT '';
ALTER TABLE `gm_tickets` MODIFY COLUMN `notes` varchar(10000) NOT NULL DEFAULT '';

