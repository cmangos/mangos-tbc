ALTER TABLE db_version CHANGE COLUMN required_s2374_01_mangos_quest_template_rewmaxrep required_s2375_01_mangos_kaelweapons_update bit;
-- Update Advisors
update mangos.creature_template set Detection = 0, ExtraFlags = 2562  where entry = 20064;
update mangos.creature_template set Detection = 0, ExtraFlags = 2562  where entry = 20063;
update mangos.creature_template set Detection = 0, ExtraFlags = 2562  where entry = 20062;
update mangos.creature_template set Detection = 0, ExtraFlags = 2562  where entry = 20060;
update mangos.creature_template set Detection = 60 where entry = 19622;

-- Update Weapons
update mangos.creature_template set FactionAlliance = 16, FactionHorde = 16 where entry = 21271;
update mangos.creature_template set FactionAlliance = 16, FactionHorde = 16 where entry = 21268;
update mangos.creature_template set FactionAlliance = 16, FactionHorde = 16 where entry = 21269;
update mangos.creature_template set FactionAlliance = 16, FactionHorde = 16 where entry = 21270;
update mangos.creature_template set FactionAlliance = 16, FactionHorde = 16 where entry = 21273;
update mangos.creature_template set FactionAlliance = 16, FactionHorde = 16 where entry = 21272;
update mangos.creature_template set FactionAlliance = 16, FactionHorde = 16, ExtraFlags = 131072  where entry = 21274;

