ALTER TABLE db_version CHANGE COLUMN required_s2366_01_mangos_spam_records required_s2368_01_mangos_spam_records_length bit;

ALTER TABLE spam_records MODIFY record VARCHAR(512) NOT NULL;

