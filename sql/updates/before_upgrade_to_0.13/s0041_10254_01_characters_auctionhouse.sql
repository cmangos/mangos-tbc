ALTER TABLE character_db_version CHANGE COLUMN required_s0041_10254_01_characters_auctionhouse required_114_9849_01_characters_saved_variables bit;

DROP TABLE IF EXISTS auctionhouse;
RENAME TABLE auction TO auctionhouse;

ALTER TABLE auctionhouse
  ADD COLUMN location tinyint(3) unsigned NOT NULL DEFAULT '3' AFTER deposit;

ALTER TABLE auctionhouse
  ADD COLUMN auctioneerguid int(11) unsigned NOT NULL DEFAULT '0' AFTER id;

UPDATE auctionhouse SET  location = houseid;

ALTER TABLE auctionhouse
  DROP COLUMN houseid;
