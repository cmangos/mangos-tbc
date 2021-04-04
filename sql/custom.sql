/**
 *	NPC EQUIPMENT
 */

REPLACE INTO creature_equip_template (entry, equipentry1, equipentry2, equipentry3)
VALUES
(200199, 18353, 6236, 0), -- clara
(200200, 33494, 0, 0), -- druid staff
(200201, 31303, 0, 0), -- hunter
(200202, 29981, 0, 0), -- mage
(200203, 17182, 0, 0), -- paladin
(200204, 34199, 0, 0), -- priest
(200205, 28572, 28572, 0), -- rogue
(200206, 32003, 32003, 0), -- shaman
(200207, 30021, 0, 0), -- warlock
(200208, 19019, 22819, 0); -- warrior: thunder fury + shield of condemnation

/**
 *	TRAINERS
 */

UPDATE creature_template SET EquipmentTemplateId = 200200 WHERE Entry = 26324; -- druid trainer
UPDATE creature_template SET EquipmentTemplateId = 200201 WHERE Entry = 26325; -- hunter trainer
UPDATE creature_template SET EquipmentTemplateId = 200202 WHERE Entry = 26326; -- mage trainer
UPDATE creature_template SET EquipmentTemplateId = 200203 WHERE Entry = 26327; -- paladin trainer
UPDATE creature_template SET EquipmentTemplateId = 200204 WHERE Entry = 26328; -- priest trainer
UPDATE creature_template SET EquipmentTemplateId = 200205 WHERE Entry = 26329; -- rogue trainer
UPDATE creature_template SET EquipmentTemplateId = 200206 WHERE Entry = 26330; -- shaman trainer
UPDATE creature_template SET EquipmentTemplateId = 200207 WHERE Entry = 26331; -- shaman trainer
UPDATE creature_template SET EquipmentTemplateId = 200208 WHERE Entry = 26332; -- warrior trainer

REPLACE INTO creature_template (entry, NAME, subname, minlevel, maxlevel, modelid1, faction, creaturetype, npcflags, unitflags, 
	extraflags, unitclass, trainertype, TrainerClass, trainertemplateid, vendortemplateid, EquipmentTemplateId)
VALUES
(995070, "Mining Trainer", "Clara's Company", 70,70,23593,35,7,145,37376,2,1,2,0,1011,0, 0),
(995071, "Blacksmithing Trainer", "Clara's Company", 70,70,1288,35,7,145,32768,2,1,2,0,1063,0, 514),
(995072, "Engineering Trainer", "Clara's Company", 70,70,24761,35,7,145,0,2,1,2,0,1001,0, 0),
(995073, "Jewelcrafting Trainer", "Clara's Company", 70,70,24731,35,7,145,4608,2,1,2,0,1091,0, 0),
(995074, "Tailoring Trainer", "Clara's Company", 70,70,22910,35,7,145,4608,2,1,2,0,1081,0, 0),
(995075, "Enchanting Trainer", "Clara's Company", 70,70,22917,35,7,145,512,2,1,2,0,1041,0, 0),
(995076, "Skinning Trainer", "Clara's Company", 70,70,22909,35,7,17,145,2,1,2,0,1021,0, 0),
(995077, "Leatherworking Trainer", "Clara's Company", 70,70,22911,35,7,145,4608,2,1,2,0,1071,0, 0),
(995078, "Herbalism Trainer", "Clara's Company", 70,70,22916,35,7,17,512,2,1,2,0,1031,0, 0),
(995079, "Alchemy Trainer", "Clara's Company", 70,70,22912,35,7,145,0,2,1,2,0,1054,0, 0),
(995080, "First Aid Trainer", "Clara's Company", 70,70,22908,35,7,145,4608,2,1,2,0,1100,0, 0),
(995081, "Fishing Trainer", "Clara's Company", 70,70,23548,35,7,145,0,2,1,2,0,1120,0, 0),
(995082, "Cooking Trainer", "Clara's Company", 70,70,22913,35,7,145,4608,2,1,2,0,1110,0, 0),
(995083, "Weapon Master", "Clara's Company", 70,70,22915,35,7,19,37376,2,1,2,0,1201,0, 0),
(995084, "Riding Trainer", "Clara's Company", 70,70,22907,35,7,18,4608,2,1,1,0,1131,0, 0),
(995095, "Pet Trainer", "Clara's Company", 70,70,22907,35,7,19,4608,2,1,3,3,100,0, 0);

/**
 *	CLARA'S COMPANY
 */

REPLACE INTO creature_template (entry, NAME, subname, minlevel, maxlevel, modelid1, faction, 
	creaturetype, npcflags, unitflags, unitclass, EquipmentTemplateId)
VALUES
(909000, "Clara", "Auction House", 58, 58, 4558, 35, 7, 2097152, 36864, 1, 200199),
(909001, "John", "Clara's Company", 41, 41, 308, 35, 7, 0, 0, 1, 55250),
(909002, "William", "Clara's Company", 44, 44, 308, 35, 7, 0, 0, 1, 2267),
(909003, "Henry", "Clara's Company", 41, 49, 89, 35, 7, 0, 0, 1, 0),
(909004, "Kodo Carrier", "Clara's Company", 70, 70, 7933, 35, 7, 0, 0, 1, 0);

/**
 *	AUCTION HOUSE
 */

DELETE FROM tbccharacters.item_instance WHERE owner_guid = 1;
DELETE FROM tbccharacters.auction WHERE itemowner = 1;

INSERT INTO tbccharacters.item_instance (
	`guid`, `owner_guid`, `itemEntry`, `creatorGuid`, 
	`giftCreatorGuid`, `count`, `duration`, `charges`, 
	`flags`, `enchantments`, `randomPropertyId`, `durability`, 
	`itemTextId`)
SELECT 
A.entry, 1, A.entry, 0,
0, 1, 0, 0, 
0, 0, 0, A.MaxDurability,
0 
FROM tbcmangos.item_template AS A 
WHERE A.quality >= 4
OR entry in (
	5175,5176,5177,5178 -- shaman quest totems
);

INSERT INTO tbccharacters.auction (
	`id`,`houseid`, `itemguid`, `item_template`, `item_count`, 
	`item_randompropertyid`, `itemowner`, `buyoutprice`, `time`, 
	`buyguid`, `lastbid`, `startbid`, `deposit`)
SELECT A.guid, 7, A.guid, A.itemEntry, 1,
0, 1, 100, 2147483648,
0, 0, 100, 10
FROM tbccharacters.item_instance AS A WHERE `owner_guid` = 1;

