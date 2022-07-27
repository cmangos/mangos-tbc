/*
5.0
Transmogrification 3.3.5a - Gossip menu
By Rochet2

ScriptName for NPC:
Creature_Transmogrify

TODO:
Make DB saving even better (Deleting)? What about coding?

Fix the cost formula
-- Too much data handling, use default costs

Are the qualities right?
Blizzard might have changed the quality requirements.
(TC handles it with stat checks)

Cant transmogrify rediculus items // Foereaper: would be fun to stab people with a fish
-- Cant think of any good way to handle this easily, could rip flagged items from cata DB
*/

#include "Bag.h"
#include "Transmogrification.h"
#define sTransmogrifier  sTransmogrification
#define GTS session->GetAcoreString // dropped translation support, no one using?

void ShowTransmogItems(Player* player, Creature* creature, uint8 slot) // Only checks bags while can use an item from anywhere in inventory
{
	WorldSession* session = player->GetSession();
	Item* oldItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
	if (oldItem)
	{
		uint32 limit = 0;
		uint32 price = sTransmogrifier->GetSpecialPrice(oldItem->GetProto());
		price *= sTransmogrifier->GetScaledCostModifier();
		price += sTransmogrifier->GetCopperCost();
		std::ostringstream ss;
		ss << std::endl;
		if (sTransmogrifier->GetRequireToken())
			ss << std::endl << std::endl << sTransmogrifier->GetTokenAmount() << " x " << sTransmogrifier->GetItemLink(sTransmogrifier->GetTokenEntry(), session);

		for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
		{
			if (limit > MAX_OPTIONS)
				break;
			Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
			if (!newItem)
				continue;
			if (!sTransmogrifier->CanTransmogrifyItemWithItem(player, oldItem->GetProto(), newItem->GetProto()))
				continue;
			if (sTransmogrifier->GetFakeEntry(oldItem->GetObjectGuid()) == newItem->GetEntry())
				continue;
			++limit;
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, ss.str(), price, false);
		}

		for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
		{
			const auto bag = dynamic_cast<Bag*>(player->GetItemByPos(INVENTORY_SLOT_BAG_0, i));
			if (!bag)
				continue;
			for (uint32 j = 0; j < bag->GetBagSize(); ++j)
			{
				if (limit > MAX_OPTIONS)
					break;
				Item* newItem = player->GetItemByPos(i, j);
				if (!newItem)
					continue;
				if (!sTransmogrifier->CanTransmogrifyItemWithItem(player, oldItem->GetProto(), newItem->GetProto()))
					continue;
				if (sTransmogrifier->GetFakeEntry(oldItem->GetObjectGuid()) == newItem->GetEntry())
					continue;
				++limit;
				player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, sTransmogrifier->GetItemIcon(newItem->GetEntry(), 30, 30, -18, 0) + sTransmogrifier->GetItemLink(newItem, session), slot, newItem->GetObjectGuid().GetCounter(), "Using this item for transmogrify will bind it to you and make it non-refundable and non-tradeable.\nDo you wish to continue?\n\n" + sTransmogrifier->GetItemIcon(newItem->GetEntry(), 40, 40, -15, -10) + sTransmogrifier->GetItemLink(newItem, session) + ss.str(), price, false);
			}
		}
	}

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Remove transmogrification", EQUIPMENT_SLOT_END + 3, slot, "Remove transmogrification from the slot?", 0, false);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Update menu", EQUIPMENT_SLOT_END, slot);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Back...", EQUIPMENT_SLOT_END + 1, 0);
	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetObjectGuid());
}

bool OnGossipHello(Player* player, Creature* creature)
{
	WorldSession* session = player->GetSession();
	if (sTransmogrifier->GetEnableTransmogInfo())
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "How does transmogrification work?", EQUIPMENT_SLOT_END + 9, 0);
	for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
	{
		if (const char* slotName = sTransmogrifier->GetSlotName(slot, session))
		{
			Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
			uint32 entry = newItem ? sTransmogrifier->GetFakeEntry(newItem->GetObjectGuid()) : 0;
			std::string icon = entry ? sTransmogrifier->GetItemIcon(entry, 30, 30, -18, 0) : sTransmogrifier->GetSlotIcon(slot, 30, 30, -18, 0);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, slotName, EQUIPMENT_SLOT_END, 0);
		}
	}
#ifdef PRESETS
	//if (sTransmogrifier->GetEnableSets())
	//	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Manage sets", EQUIPMENT_SLOT_END + 4, 0);
#endif
	//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Remove all transmogrifications", EQUIPMENT_SLOT_END + 2, 0, "Remove transmogrifications from all equipped items?", 0, false);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Update menu", EQUIPMENT_SLOT_END + 1, 0);
	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetObjectGuid());
	return true;
}

bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
	player->GetPlayerMenu()->ClearMenus();
	WorldSession* session = player->GetSession();
	switch (sender)
	{
	case EQUIPMENT_SLOT_END: // Show items you can use
		ShowTransmogItems(player, creature, action);
		break;
	case EQUIPMENT_SLOT_END + 1: // Main menu
		OnGossipHello(player, creature);
		break;
	case EQUIPMENT_SLOT_END + 2: // Remove Transmogrifications
	{
		bool removed = false;
		auto trans = CharacterDatabase.BeginTransaction();
		for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
		{
			if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
			{
				if (!sTransmogrifier->GetFakeEntry(newItem->GetObjectGuid()))
					continue;
				sTransmogrifier->DeleteFakeEntry(player, slot, newItem);
				removed = true;
			}
		}
		if (removed)
		{
			session->SendAreaTriggerMessage("%s", LANG_ERR_UNTRANSMOG_OK);
			CharacterDatabase.CommitTransaction();
		}
		else
			session->SendNotification(LANG_ERR_UNTRANSMOG_NO_TRANSMOGS);
		OnGossipHello(player, creature);
	} break;
	case EQUIPMENT_SLOT_END + 3: // Remove Transmogrification from single item
	{
		if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, action))
		{
			if (sTransmogrifier->GetFakeEntry(newItem->GetObjectGuid()))
			{
				sTransmogrifier->DeleteFakeEntry(player, action, newItem);
				session->SendAreaTriggerMessage("%s", LANG_ERR_UNTRANSMOG_OK);
			}
			else
				session->SendNotification(LANG_ERR_UNTRANSMOG_NO_TRANSMOGS);
		}
		OnGossipSelect(player, creature, EQUIPMENT_SLOT_END, action);
	} break;
#ifdef PRESETS
	case EQUIPMENT_SLOT_END + 4: // Presets menu
	{
		if (!sTransmogrifier->GetEnableSets())
		{
			OnGossipHello(player, creature);
			return true;
		}
		if (sTransmogrifier->GetEnableSetInfo())
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "How do sets work?", EQUIPMENT_SLOT_END + 10, 0);
		for (Transmogrification::presetIdMap::const_iterator it = sTransmogrifier->presetByName[player->GetObjectGuid()].begin(); it != sTransmogrifier->presetByName[player->GetObjectGuid()].end(); ++it)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "zz?" /*it->second*/, EQUIPMENT_SLOT_END + 6, it->first);

		if (sTransmogrifier->presetByName[player->GetObjectGuid()].size() < sTransmogrifier->GetMaxSets())
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Save set", EQUIPMENT_SLOT_END + 8, 0);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Back...", EQUIPMENT_SLOT_END + 1, 0);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetObjectGuid());
	} break;
	case EQUIPMENT_SLOT_END + 5: // Use preset
	{
		if (!sTransmogrifier->GetEnableSets())
		{
			OnGossipHello(player, creature);
			return true;
		}
		// action = presetID
		for (Transmogrification::slotMap::const_iterator it = sTransmogrifier->presetById[player->GetObjectGuid()][action].begin(); it != sTransmogrifier->presetById[player->GetObjectGuid()][action].end(); ++it)
		{
			if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, it->first))
				sTransmogrifier->PresetTransmog(player, item, it->second, it->first);
		}
		OnGossipSelect(player, creature, EQUIPMENT_SLOT_END + 6, action);
	} break;
	case EQUIPMENT_SLOT_END + 6: // view preset
	{
		if (!sTransmogrifier->GetEnableSets())
		{
			OnGossipHello(player, creature);
			return true;
		}
		// action = presetID
		for (Transmogrification::slotMap::const_iterator it = sTransmogrifier->presetById[player->GetObjectGuid()][action].begin(); it != sTransmogrifier->presetById[player->GetObjectGuid()][action].end(); ++it)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "zzz"/*sTransmogrifier->GetItemIcon(it->second, 30, 30, -18, 0) + sTransmogrifier->GetItemLink(it->second, session)*/, sender, action);

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Use this set", EQUIPMENT_SLOT_END + 5, action, "Using this set for transmogrify will bind transmogrified items to you and make them non-refundable and non-tradeable.\nDo you wish to continue?\n\n" + sT->presetByName[player->GetObjectGuid()][action], 0, false);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Delete set", EQUIPMENT_SLOT_END + 7, action, "Are you sure you want to delete " + sT->presetByName[player->GetObjectGuid()][action] + "?", 0, false);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Back...", EQUIPMENT_SLOT_END + 4, 0);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetObjectGuid());
	} break;
	case EQUIPMENT_SLOT_END + 7: // Delete preset
	{
		if (!sTransmogrifier->GetEnableSets())
		{
			OnGossipHello(player, creature);
			return true;
		}
		// action = presetID
		CharacterDatabase.PExecute("DELETE FROM `custom_transmogrification_sets` WHERE Owner = %u AND PresetID = %u", player->GetObjectGuid(), action);
		sTransmogrifier->presetById[player->GetObjectGuid()][action].clear();
		sTransmogrifier->presetById[player->GetObjectGuid()].erase(action);
		sTransmogrifier->presetByName[player->GetObjectGuid()].erase(action);

		OnGossipSelect(player, creature, EQUIPMENT_SLOT_END + 4, 0);
	} break;
	case EQUIPMENT_SLOT_END + 8: // Save preset
	{
		if (!sTransmogrifier->GetEnableSets() || sTransmogrifier->presetByName[player->GetObjectGuid()].size() >= sTransmogrifier->GetMaxSets())
		{
			OnGossipHello(player, creature);
			return true;
		}
		uint32 cost = 0;
		bool canSave = false;
		for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
		{
			if (!sTransmogrifier->GetSlotName(slot, session))
				continue;
			if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
			{
				uint32 entry = sTransmogrifier->GetFakeEntry(newItem->GetObjectGuid());
				if (!entry)
					continue;
				const ItemPrototype* temp = sObjectMgr.GetItemPrototype(entry);
				if (!temp)
					continue;
				if (!sTransmogrifier->SuitableForTransmogrification(player, temp)) // no need to check?
					continue;
				cost += sTransmogrifier->GetSpecialPrice(temp);
				canSave = true;
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "zzzu"/*sTransmogrifier->GetItemIcon(entry, 30, 30, -18, 0) + sTransmogrifier->GetItemLink(entry, session)*/, EQUIPMENT_SLOT_END + 8, 0);
			}
		}
		if (canSave)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Save set", 0, 0, "Insert set name", cost * sT->GetSetCostModifier() + sT->GetSetCopperCost(), true);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Update menu", sender, action);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Back...", EQUIPMENT_SLOT_END + 4, 0);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetObjectGuid());
	} break;
	case EQUIPMENT_SLOT_END + 10: // Set info
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Back...", EQUIPMENT_SLOT_END + 4, 0);
		player->SEND_GOSSIP_MENU(sTransmogrifier->GetSetNpcText(), creature->GetObjectGuid());
	} break;
#endif
	case EQUIPMENT_SLOT_END + 9: // Transmog info
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Back...", EQUIPMENT_SLOT_END + 1, 0);
		player->SEND_GOSSIP_MENU(sTransmogrifier->GetTransmogNpcText(), creature->GetObjectGuid());
	} break;
	default: // Transmogrify
	{
		if (!sender && !action)
		{
			OnGossipHello(player, creature);
			return true;
		}
		// sender = slot, action = display
		TransmogAcoreStrings res = sTransmogrifier->Transmogrify(player, ObjectGuid(HIGHGUID_ITEM, action), sender);
		if (res == LANG_ERR_TRANSMOG_OK)
			session->SendAreaTriggerMessage("%s", LANG_ERR_TRANSMOG_OK);
		else
			session->SendNotification(res);
		// OnGossipSelect(player, creature, EQUIPMENT_SLOT_END, sender);
		// ShowTransmogItems(player, creature, sender);
		player->CLOSE_GOSSIP_MENU();
	} break;
	}
	return true;
}

#ifdef PRESETS
bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
{
	player->GetPlayerMenu()->ClearMenus();
	if (sender || action)
		return true; // should never happen
	if (!sTransmogrifier->GetEnableSets())
	{
		OnGossipHello(player, creature);
		return true;
	}
	std::string name(code);
	if (name.find('"') != std::string::npos || name.find('\\') != std::string::npos)
		player->GetSession()->SendNotification(LANG_PRESET_ERR_INVALID_NAME);
	else
	{
		for (uint8 presetID = 0; presetID < sTransmogrifier->GetMaxSets(); ++presetID) // should never reach over max
		{
			if (sTransmogrifier->presetByName[player->GetObjectGuid()].find(presetID) != sTransmogrifier->presetByName[player->GetObjectGuid()].end())
				continue; // Just remember never to use presetByName[pGUID][presetID] when finding etc!

			int32 cost = 0;
			std::map<uint8, uint32> items;
			for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
			{
				if (!sTransmogrifier->GetSlotName(slot, player->GetSession()))
					continue;
				if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
				{
					uint32 entry = sTransmogrifier->GetFakeEntry(newItem->GetObjectGuid());
					if (!entry)
						continue;
					const ItemPrototype* temp = sObjectMgr.GetItemPrototype(entry);
					if (!temp)
						continue;
					if (!sTransmogrifier->SuitableForTransmogrification(player, temp))
						continue;
					cost += sTransmogrifier->GetSpecialPrice(temp);
					items[slot] = entry;
				}
			}
			if (items.empty())
				break; // no transmogrified items were found to be saved
			cost *= sTransmogrifier->GetSetCostModifier();
			cost += sTransmogrifier->GetSetCopperCost();
			if (player->GetMoney() < cost)
			{
				player->GetSession()->SendNotification(LANG_ERR_TRANSMOG_NOT_ENOUGH_MONEY);
				break;
			}

			std::ostringstream ss;
			for (std::map<uint8, uint32>::iterator it = items.begin(); it != items.end(); ++it)
			{
				ss << uint32(it->first) << ' ' << it->second << ' ';
				sTransmogrifier->presetById[player->GetObjectGuid()][presetID][it->first] = it->second;
			}
			sTransmogrifier->presetByName[player->GetObjectGuid()][presetID] = name; // Make sure code doesnt mess up SQL!
			CharacterDatabase.PExecute("REPLACE INTO `custom_transmogrification_sets` (`Owner`, `PresetID`, `SetName`, `SetData`) VALUES (%u, %u, \"%s\", \"%s\")", player->GetObjectGuid(), uint32(presetID), name.c_str(), ss.str().c_str());
			if (cost)
				player->ModifyMoney(-cost);
			break;
		}
	}
	//OnGossipSelect(player, creature, EQUIPMENT_SLOT_END+4, 0);
	player->CLOSE_GOSSIP_MENU(); // Wait for SetMoney to get fixed, issue #10053
	return true;
}
#endif

std::map<uint64, std::map<uint32, Item*> > Items;
bool GossipHello_TransmogNPC(Player* pPlayer, Creature* pUnit)
{
	pPlayer->GetPlayerMenu()->ClearMenus();

	if (sTransmogrifier->GetEnableTransmogInfo())
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "How does transmogrification work?", EQUIPMENT_SLOT_END + 9, 0);

	// Only show the menu option for items that you have equipped
	for (uint8 Slot = EQUIPMENT_SLOT_START; Slot < EQUIPMENT_SLOT_END; Slot++)
	{
		// No point in checking for tabard, shirt, necklace, rings or trinkets
		if (Slot == EQUIPMENT_SLOT_NECK || Slot == EQUIPMENT_SLOT_FINGER1 || Slot == EQUIPMENT_SLOT_FINGER2 || Slot == EQUIPMENT_SLOT_TRINKET1 || Slot == EQUIPMENT_SLOT_TRINKET2 || Slot == EQUIPMENT_SLOT_TABARD || Slot == EQUIPMENT_SLOT_BODY)
			continue;

		// Only show the menu option for transmogrifiers that you have per slot
		if (Item* pEquippedItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, Slot))
		{
			// Only show the menu option if there is a transmogrifying option available
			bool has_option = false;

			if (!has_option)
			{
				// Check in main inventory
				for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
				{
					if (Item* pTransmogrifier = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
					{
						if (!sTransmogrifier->CanTransmogrifyItemWithItem(pPlayer, pEquippedItem->GetProto(), pTransmogrifier->GetProto()))
							continue;

						has_option = true;
						break;
					}
				}
			}
			if (!has_option)
			{
				// Check in the other bags
				for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
				{
					if (const auto pBag = dynamic_cast<Bag*>(pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i)))
					{
						for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
						{
							if (Item* pTransmogrifier = pBag->GetItemByPos(static_cast<uint8>(j)))
							{
								if (!sTransmogrifier->CanTransmogrifyItemWithItem(pPlayer, pEquippedItem->GetProto(), pTransmogrifier->GetProto()))
									continue;

								has_option = true;
								break;
							}
						}
					}

					// If we find a suitable mog in the first bag then there's no point in checking the rest
					if (has_option)
						break;
				}
			}
			if (!has_option)
			{
				// Check in the bank's main inventory
				for (uint8 i = BANK_SLOT_ITEM_START; i < BANK_SLOT_ITEM_END; ++i)
				{
					if (Item* pTransmogrifier = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
					{
						if (!sTransmogrifier->CanTransmogrifyItemWithItem(pPlayer, pEquippedItem->GetProto(), pTransmogrifier->GetProto()))
							continue;

						has_option = true;
						break;
					}
				}
			}
			if (!has_option)
			{
				// Check in the bank's other bags
				for (uint8 i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; ++i)
				{
					if (const auto pBag = dynamic_cast<Bag*>(pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i)))
					{
						for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
						{
							if (Item* pTransmogrifier = pBag->GetItemByPos(static_cast<uint8>(j)))
							{
								if (!sTransmogrifier->CanTransmogrifyItemWithItem(pPlayer, pEquippedItem->GetProto(), pTransmogrifier->GetProto()))
									continue;

								has_option = true;
								break;
							}
						}
					}

					if (has_option)
						break;
				}
			}

			if (has_option)
			{
				std::string SlotName = sTransmogrifier->GetSlotName(Slot, pPlayer->GetSession());
				if (SlotName.length() > 0)
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, SlotName.c_str(), EQUIPMENT_SLOT_END, Slot);
			}
		}
	}

	// Remove all transmogrifiers
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Remove all transmogrifications.", EQUIPMENT_SLOT_END + 2, 0);
	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pUnit->GetObjectGuid());

	return true;
}

bool GossipSelect_TransmogNPC(Player* pPlayer, Creature* pUnit, const uint32 sender, const uint32 aSlot)
{
	pPlayer->GetPlayerMenu()->ClearMenus();
	// Display the available transmofrifiers inside the options
	if (sender == EQUIPMENT_SLOT_END)
	{
		if (Item* pEquippedItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, static_cast<uint8>(aSlot)))
		{
			const ObjectGuid EquippedItemGUID = pEquippedItem->GetObjectGuid();
			if (ItemPrototype const* equippedProto = pEquippedItem->GetProto())
			{
				std::string yourItem;
				const std::string equip_name = equippedProto->Name1;
				yourItem = pPlayer->GetSession()->GetMangosString(LANG_MENU_YOUR_ITEM) + equip_name;
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, yourItem.c_str(), sender, aSlot);
			}

			const uint64 PlayerGUID = pPlayer->GetObjectGuid();
			Items[PlayerGUID].clear();
			for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; i++)
				if (Item* pItemTransmogrifier = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
					if (sTransmogrifier->CanTransmogrifyItemWithItem(pPlayer, pEquippedItem->GetProto(), pItemTransmogrifier->GetProto()) && sTransmogrification->GetFakeEntry(pEquippedItem->GetObjectGuid()) != pItemTransmogrifier->GetEntry())
						if (Items[PlayerGUID].find(pItemTransmogrifier->GetProto()->DisplayInfoID) == Items[PlayerGUID].end())
						{
							Items[PlayerGUID][pItemTransmogrifier->GetProto()->DisplayInfoID] = pItemTransmogrifier;
							pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, pItemTransmogrifier->GetProto()->Name1, aSlot + 100, pItemTransmogrifier->GetProto()->DisplayInfoID);
						}

			for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; i++)
				if (const auto pBag = dynamic_cast<Bag*>(pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i)))
					for (uint32 j = 0; j < pBag->GetBagSize(); j++)
						if (Item* pItemTransmogrifier = pBag->GetItemByPos(static_cast<uint8>(j)))
							if (sTransmogrifier->CanTransmogrifyItemWithItem(pPlayer, pEquippedItem->GetProto(), pItemTransmogrifier->GetProto()) && sTransmogrification->GetFakeEntry(pEquippedItem->GetObjectGuid()) != pItemTransmogrifier->GetEntry())
								if (Items[PlayerGUID].find(pItemTransmogrifier->GetProto()->DisplayInfoID) == Items[PlayerGUID].end())
								{
									Items[PlayerGUID][pItemTransmogrifier->GetProto()->DisplayInfoID] = pItemTransmogrifier;
									pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, pItemTransmogrifier->GetProto()->Name1, aSlot + 100, pItemTransmogrifier->GetProto()->DisplayInfoID);
								}

			for (uint8 i = BANK_SLOT_ITEM_START; i < BANK_SLOT_ITEM_END; i++)
				if (Item* pItemTransmogrifier = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
					if (sTransmogrifier->CanTransmogrifyItemWithItem(pPlayer, pEquippedItem->GetProto(), pItemTransmogrifier->GetProto()) && sTransmogrification->GetFakeEntry(pEquippedItem->GetObjectGuid()) != pItemTransmogrifier->GetEntry())
						if (Items[PlayerGUID].find(pItemTransmogrifier->GetProto()->DisplayInfoID) == Items[PlayerGUID].end())
						{
							Items[PlayerGUID][pItemTransmogrifier->GetProto()->DisplayInfoID] = pItemTransmogrifier;
							pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, pItemTransmogrifier->GetProto()->Name1, aSlot + 100, pItemTransmogrifier->GetProto()->DisplayInfoID);
						}

			for (uint8 i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; i++)
				if (const auto pBag = dynamic_cast<Bag*>(pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i)))
					for (uint32 j = 0; j < pBag->GetBagSize(); j++)
						if (Item* pItemTransmogrifier = pBag->GetItemByPos(static_cast<uint8>(j)))
							if (sTransmogrifier->CanTransmogrifyItemWithItem(pPlayer, pEquippedItem->GetProto(), pItemTransmogrifier->GetProto()) && sTransmogrification->GetFakeEntry(pEquippedItem->GetObjectGuid()) != pItemTransmogrifier->GetEntry())
								if (Items[PlayerGUID].find(pItemTransmogrifier->GetProto()->DisplayInfoID) == Items[PlayerGUID].end())
								{
									Items[PlayerGUID][pItemTransmogrifier->GetProto()->DisplayInfoID] = pItemTransmogrifier;
									pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, pItemTransmogrifier->GetProto()->Name1, aSlot + 100, pItemTransmogrifier->GetProto()->DisplayInfoID);
								}

			// Remove the transmogrifier on the current item
			bool hasTransmogOptions = !Items[PlayerGUID].empty();
			bool hasTransmog = false;
			if (const uint32 FakeEntry = sTransmogrification->GetFakeEntry(EquippedItemGUID))
			{
				hasTransmog = true;
				if (ItemPrototype const* pItem = sObjectMgr.GetItemPrototype(FakeEntry))
				{
					const std::string item_name = pItem->Name1;
					const std::string illusion = pPlayer->GetSession()->GetMangosString(LANG_MENU_REMOVE) + item_name;
					//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, pPlayer->GetSession()->GetMangosString(LANG_MENU_OPTIONS), sender, aSlot);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, illusion.c_str(), EQUIPMENT_SLOT_END + 3, aSlot);
				}
			}
			else
			{
				if (Items[PlayerGUID].empty())
				{
					pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetSession()->GetMangosString(LANG_MENU_NO_SUITABLE_ITEMS));
					GossipHello_TransmogNPC(pPlayer, pUnit);
					return true;
				}
			}

			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, pPlayer->GetSession()->GetMangosString(LANG_MENU_BACK), EQUIPMENT_SLOT_END + 1, 0);
			if (hasTransmog && !hasTransmogOptions)
				pPlayer->SEND_GOSSIP_MENU(sTransmogrifier->GetSetNpcAlreadyText(), pUnit->GetObjectGuid());
			else if (hasTransmog && hasTransmogOptions)
				pPlayer->SEND_GOSSIP_MENU(sTransmogrifier->GetSetNpcAlreadyAltText(), pUnit->GetObjectGuid());
			else
				pPlayer->SEND_GOSSIP_MENU(sTransmogrifier->GetNpcSelectLookText(), pUnit->GetObjectGuid());
		}
		else
			GossipHello_TransmogNPC(pPlayer, pUnit);
	}
	// Go back to main menu
	else if (sender == EQUIPMENT_SLOT_END + 1)
		GossipHello_TransmogNPC(pPlayer, pUnit);
	// Remove all transmogrifications
	else if (sender == EQUIPMENT_SLOT_END + 2)
	{
		bool removed = false;
		for (uint8 Slot = EQUIPMENT_SLOT_START; Slot < EQUIPMENT_SLOT_END; ++Slot)
		{
			if (Item* pEquippedItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, Slot))
			{
				ObjectGuid EquippedItemGUID = pEquippedItem->GetObjectGuid();
				if (!sTransmogrification->GetFakeEntry(EquippedItemGUID))
					continue;

				sTransmogrification->DeleteFakeEntry(pPlayer, Slot, pEquippedItem);
				removed = true;
			}
		}
		if (removed)
		{
			pPlayer->GetSession()->SendAreaTriggerMessage("%s", pPlayer->GetSession()->GetMangosString(LANG_ERR_UNTRANSMOG_OK));

			uint32 selfVisualSpell = 24085;
			uint32 npcToPlayerSpell = 14867;
			pUnit->CastSpell(pPlayer, npcToPlayerSpell, TRIGGERED_OLD_TRIGGERED);
			pPlayer->CastSpell(pPlayer, selfVisualSpell, TRIGGERED_OLD_TRIGGERED);
		}
		else
			pPlayer->GetSession()->SendNotification(LANG_ERR_UNTRANSMOG_NO_TRANSMOGS);

		GossipHello_TransmogNPC(pPlayer, pUnit);
	}
	// Remove transmogrification on a single equipped item
	else if (sender == EQUIPMENT_SLOT_END + 3)
	{
		bool removed = false;
		if (Item* pEquippedItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, static_cast<uint8>(aSlot)))
		{
			const ObjectGuid EquippedItemGUID = pEquippedItem->GetObjectGuid();
			if (sTransmogrification->GetFakeEntry(EquippedItemGUID))
			{
				sTransmogrification->DeleteFakeEntry(pPlayer, static_cast<uint8>(aSlot), pEquippedItem);
				removed = true;
			}
		}
		const std::string SlotName = sTransmogrifier->GetSlotName(static_cast<uint8>(aSlot), pPlayer->GetSession());
		if (removed)
		{
			pPlayer->GetSession()->SendAreaTriggerMessage("%s (%s)", pPlayer->GetSession()->GetMangosString(LANG_ERR_UNTRANSMOG_SINGLE_OK), SlotName.c_str());

			uint32 selfVisualSpell = 24085;
			uint32 npcToPlayerSpell = 14867;
			pUnit->CastSpell(pPlayer, npcToPlayerSpell, TRIGGERED_OLD_TRIGGERED);
			pPlayer->CastSpell(pPlayer, selfVisualSpell, TRIGGERED_OLD_TRIGGERED);
		}
		else
			pPlayer->GetSession()->SendAreaTriggerMessage("%s (%s)", pPlayer->GetSession()->GetMangosString(LANG_ERR_UNTRANSMOG_SINGLE_NO_TRANSMOGS), SlotName.c_str());

		GossipHello_TransmogNPC(pPlayer, pUnit);
	}
	// Update all transmogrifications
	else if (sender == EQUIPMENT_SLOT_END + 4)
	{
		sTransmogrification->ApplyAll(pPlayer);
		pPlayer->GetSession()->SendAreaTriggerMessage("Your appearance was refreshed");
		GossipHello_TransmogNPC(pPlayer, pUnit);
	}
	// Info about transmogrification
	else if (sender == EQUIPMENT_SLOT_END + 9)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetSession()->GetMangosString(LANG_MENU_BACK), EQUIPMENT_SLOT_END + 1, 0);
		pPlayer->SEND_GOSSIP_MENU(sTransmogrifier->GetTransmogNpcText(), pUnit->GetObjectGuid());
	}
	// Check cost
	else if (sender >= 100)
	{
		// The cost is the vendor sell price of the transmogrifier or 1 Gold
		const uint64 PlayerGUID = pPlayer->GetObjectGuid();
		if (Item* pItemTransmogrifier = Items[PlayerGUID][aSlot])
		{
			if (ItemPrototype const* protoItemTransmogrifier = pItemTransmogrifier->GetProto())
			{
				// Display transaction
				Item* pItemTransmogrified = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, static_cast<uint8>(sender - 100));
				if (!pItemTransmogrified)
				{
					GossipHello_TransmogNPC(pPlayer, pUnit);
					return true;
				}
				if (ItemPrototype const* protoItemTransmogrified = pItemTransmogrified->GetProto())
				{
					std::string nameItemTransmogrified = protoItemTransmogrified->Name1;
					std::string before = pPlayer->GetSession()->GetMangosString(LANG_MENU_BEFORE) + nameItemTransmogrified;
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, before.c_str(), sender, aSlot);
				}

				// get cost
				uint32 cost = sTransmogrifier->GetSpecialPrice(pItemTransmogrified->GetProto());
				cost *= sTransmogrifier->GetScaledCostModifier();
				cost += sTransmogrifier->GetCopperCost();

				std::string nameItemTransmogrifier = protoItemTransmogrifier->Name1;
				std::string after = pPlayer->GetSession()->GetMangosString(LANG_MENU_AFTER) + nameItemTransmogrifier;
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, after.c_str(), sender, aSlot);

				// Display cost
				std::string s_cost;
				s_cost = pPlayer->GetSession()->GetMangosString(LANG_MENU_COST_IS) + sTransmogrifier->FormatPrice(cost);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, s_cost.c_str(), sender, aSlot);

				// Only show confirmation button if player has enough money
				if (pPlayer->GetMoney() > cost)
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, pPlayer->GetSession()->GetMangosString(LANG_MENU_CONFIRM), sender - 100, aSlot);
				else
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, pPlayer->GetSession()->GetMangosString(LANG_ERR_TRANSMOG_NOT_ENOUGH_MONEY), sender, aSlot);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, pPlayer->GetSession()->GetMangosString(LANG_MENU_BACK), EQUIPMENT_SLOT_END, pItemTransmogrified->GetSlot());
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, pPlayer->GetSession()->GetMangosString(LANG_MENU_MAIN_MENU), EQUIPMENT_SLOT_END + 1, 0);
				pPlayer->SEND_GOSSIP_MENU(sTransmogrifier->GetSetNpcConfirmText(), pUnit->GetObjectGuid());
			}
		}
	}
	else
	{
		const uint64 PlayerGUID = pPlayer->GetObjectGuid();
		if (!Items[PlayerGUID][aSlot])
			return false;

		// sender = slot, action = display
		TransmogAcoreStrings res = sTransmogrifier->Transmogrify(pPlayer, Items[PlayerGUID][aSlot]->GetObjectGuid(), static_cast<uint8>(sender));
		if (res == LANG_ERR_TRANSMOG_OK)
		{
			uint32 selfVisualSpell = 24085;
			uint32 npcToPlayerSpell = 14867;
			pUnit->CastSpell(pPlayer, npcToPlayerSpell, TRIGGERED_OLD_TRIGGERED);
			pPlayer->CastSpell(pPlayer, selfVisualSpell, TRIGGERED_OLD_TRIGGERED);
			//pPlayer->GetSession()->SendAreaTriggerMessage("Successfully casted an illusion on your %s", sTransmogrifier->GetSlotName(static_cast<uint8>(sender), pPlayer->GetSession()));
			pPlayer->GetSession()->SendAreaTriggerMessage("%s (%s)", pPlayer->GetSession()->GetMangosString(LANG_ERR_TRANSMOG_OK), sTransmogrifier->GetSlotName(static_cast<uint8>(sender), pPlayer->GetSession()));
			GossipHello_TransmogNPC(pPlayer, pUnit);
		}
		else
		{
			pPlayer->GetSession()->SendNotification(res);
			GossipHello_TransmogNPC(pPlayer, pUnit);
		}
		Items[PlayerGUID].clear();
		GossipHello_TransmogNPC(pPlayer, pUnit);
	}
	return true;
}

void AddSC_Transmog()
{
	auto newscript = new Script;
	newscript->Name = "npc_transmogrifier";
	newscript->pGossipHello = &GossipHello_TransmogNPC;
	newscript->pGossipSelect = &GossipSelect_TransmogNPC;
	newscript->RegisterSelf(false);
}