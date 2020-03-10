ALTER TABLE character_db_version CHANGE COLUMN required_s2401_01_characters_new_ticket_system required_s2402_01_characters_new_ticket_system_sql_std bit;

--
-- Apply standard compliant structure for table `gm_tickets`
--

ALTER TABLE `gm_tickets` MODIFY COLUMN `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `gm_tickets` MODIFY COLUMN `updated` timestamp NOT NULL DEFAULT 0;
ALTER TABLE `gm_tickets` MODIFY COLUMN `seen` timestamp NOT NULL DEFAULT 0;
ALTER TABLE `gm_tickets` MODIFY COLUMN `answered` timestamp NOT NULL DEFAULT 0;
ALTER TABLE `gm_tickets` MODIFY COLUMN `closed` timestamp NOT NULL DEFAULT 0;
ALTER TABLE `gm_tickets` MODIFY COLUMN `closed` timestamp NOT NULL DEFAULT 0;
ALTER TABLE `gm_tickets` MODIFY COLUMN `conclusion` varchar(255) NOT NULL DEFAULT '';
ALTER TABLE `gm_tickets` MODIFY COLUMN `notes` varchar(10000) NOT NULL DEFAULT '';

