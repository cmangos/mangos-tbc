ALTER TABLE db_version CHANGE COLUMN required_139_10171_01_mangos_mangos_string required_s0020_10197_01_mangos_playercreateinfo bit;

ALTER TABLE playercreateinfo
  ADD COLUMN orientation float NOT NULL default '0' AFTER position_z;
