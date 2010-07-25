ALTER TABLE character_db_version CHANGE COLUMN required_114_9849_01_characters_saved_variables required_s0041_10254_01_characters_auctionhouse bit;

ALTER TABLE auctionhouse
  ADD COLUMN houseid int(11) unsigned NOT NULL default '0' AFTER id;

UPDATE auctionhouse SET houseid = location;

ALTER TABLE auctionhouse
  DROP COLUMN auctioneerguid,
  DROP COLUMN location;

DROP TABLE IF EXISTS auction;
RENAME TABLE auctionhouse TO auction;
