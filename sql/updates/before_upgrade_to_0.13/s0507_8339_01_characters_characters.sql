ALTER TABLE character_db_version CHANGE COLUMN required_s0507_8339_01_characters_characters required_s0386_10662_01_characters_item_loot bit;

ALTER TABLE characters
  bgid int(10) unsigned NOT NULL default '0' AFTER arena_pending_points,
  bgteam int(10) unsigned NOT NULL default '0' AFTER bgid,
  bgmap int(10) unsigned NOT NULL default '0' AFTER bgteam,
  bgx float NOT NULL default '0' AFTER bgmap,
  bgy float NOT NULL default '0' AFTER bgx,
  bgz float NOT NULL default '0' AFTER bgy,
  bgo float NOT NULL default '0' AFTER bgz;
