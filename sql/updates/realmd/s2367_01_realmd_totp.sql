ALTER TABLE realmd_db_version CHANGE COLUMN required_s2325_01_realmd required_s2367_01_realmd_totp bit;

ALTER TABLE account ADD COLUMN token text AFTER locale;
