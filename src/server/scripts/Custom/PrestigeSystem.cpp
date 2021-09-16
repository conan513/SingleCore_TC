#include "ScriptMgr.h"
#include "Pet.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"
#include "Chat.h"
#include "DatabaseEnv.h"

static const int GOSSIP_MENU = 68;
static const int UPGRADE_TOKEN_ENTRY = 49927;
static const int UPGRADE_TOKEN_COST = 1;
static const int STATS_PER_RANK = 25;

enum Menu
{
	MENU_MAIN = 99,
	MENU_PRESTIGE_PERKS = 100,
	MENU_WHAT_IS_PRESTIGE = 101,
	MENU_RESET_POINTS = 102,
	MENU_RESET_POINTS_ACTIVE = 103,
};

class IconHelper
{
public:
	IconHelper() {}

	static std::string buildIconString(std::string iconString)
	{
		std::string iconPrefix = "|TInterface/ICONS/";
		std::string iconSuffix = ":30|t";

		return iconPrefix + iconString + iconSuffix;
	}
};

class MenuHelper
{
public:
	static int getStatMenuEntry(int statID) { return menuMod + statID; }
	static int getStatIDFromMenuEntry(int menuEntry) { return menuEntry - menuMod; }

	static int getStatPurchaseMenuEntry(int statID) { return purchaseMod + statID; }
	static int getStatIDFromPurchaseMenuEntry(int purchaseEntry) { return purchaseEntry - purchaseMod; }

private:
		static const int menuMod = 90000;
		static const int purchaseMod = 100000;
};

class StatHelper
{
public:
	static void SetStatAmount(int charguid, int statID, int amount)
	{
		WorldDatabase.PQuery("DELETE FROM custom_prestige_system_character WHERE charguid=%u AND stat=%u", charguid, statID);
		WorldDatabase.PQuery("INSERT INTO custom_prestige_system_character VALUES (%u, %u, %u)", charguid, statID, amount);
	}

	static int GetStatAmount(int charguid, int statID)
	{
		QueryResult result = WorldDatabase.PQuery("SELECT * FROM custom_prestige_system_character WHERE charguid=%u AND stat=%u", charguid, statID);
		if (!result) return 0;

		Field* fields = result->Fetch();
		return fields[2].GetUInt32();
	}
};



class PrestigeStat
{
public:
	PrestigeStat(int _id, std::string _name, std::string _icon, int _spellID, int _rank)
	{
		id = _id;
		name = _name;
		icon = _icon;
		spellID = _spellID;
		rank = _rank;
	}

	int getID() { return id;  }
	std::string getName() { return name;  }
	std::string getIcon() { return icon;  }
	int getSpellID() { return spellID;  }
	int getRank() { return rank;  }

private:
	int id;
	std::string name;
	std::string icon;
	int spellID;
	int rank;
};

class PrestigeCharacterRow
{
public:
	PrestigeCharacterRow(int _charGUID, int _statID, int _amount)
	{
		charGUID = _charGUID;
		statID = _statID;
		amount = _amount;
	}

	int getCharGUID() { return charGUID; }
	int getStatID() { return statID; }
	int getAmount() { return amount; }

private:
	int charGUID;
	int statID;
	int amount;
};

class PrestigeStatsContainer
{
public:
	PrestigeStatsContainer()
	{
		QueryResult result = WorldDatabase.PQuery("SELECT * FROM custom_prestige_system_stats");
		if (!result) return;

		do
		{
			Field* fields = result->Fetch();

			int id = fields[0].GetInt32();
			std::string name = fields[1].GetString();
			std::string icon = fields[2].GetString();
			int spellID = fields[3].GetUInt32();
			int rank = fields[4].GetUInt32();

			PrestigeStat stat(id, name, icon, spellID, rank);
			stats.push_back(stat);
		} while (result->NextRow());
	}

	std::vector<PrestigeStat> getStats() { return stats;  }
	PrestigeStat getStat(int statID) 
	{
		for (int i = 0; i < stats.size(); i++)
			if (statID == stats.at(i).getID())
				return stats.at(i);
	}

protected:
	std::vector<PrestigeStat> stats;
};

class PlayerPrestigeStatsContainer : public PrestigeStatsContainer
{
public:
	PlayerPrestigeStatsContainer(Player* player) : PrestigeStatsContainer()
	{
		//Set all stats to 0
		for (std::vector<PrestigeStat>::iterator it = stats.begin(); it != stats.end(); ++it)
		{
			PrestigeStat stat = *it;
			statsAmount[stat.getID()] = 0;
		}

		//Set correct stat amounts for stats in DB
		int charGUID = getPlayerCharacterGUID(player);
		std::vector<PrestigeCharacterRow> rows = getCharacterData(charGUID);

		for (std::vector<PrestigeCharacterRow>::iterator rowIt = rows.begin(); rowIt != rows.end(); ++rowIt)
		{
			PrestigeCharacterRow row = *rowIt;

			statsAmount[row.getStatID()] = row.getAmount();
		}
	};

	std::map<int, int> getStatsAmount() { return statsAmount; }

private:
	std::vector<PrestigeCharacterRow> getCharacterData(int characterGUID)
	{
		std::vector<PrestigeCharacterRow> characterRows;

		QueryResult prestigeResult = WorldDatabase.PQuery("SELECT * FROM custom_prestige_system_character WHERE charguid=%u ORDER BY stat ASC;", characterGUID);
		if (!prestigeResult) return characterRows;

		do
		{
			Field* fields = prestigeResult->Fetch();

			int charGUID = fields[0].GetInt32();
			int statID = fields[1].GetInt32();
			int amount = fields[2].GetInt32();

			PrestigeCharacterRow row(charGUID, statID, amount);
			characterRows.push_back(row);
		} while (prestigeResult->NextRow());

		return characterRows;
	}

	int getPlayerCharacterGUID(Player* player)
	{
		QueryResult charResult = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE name='%s'", player->GetName());
		return charResult->Fetch()[0].GetUInt32();
	}

private:
	std::map<int, int> statsAmount;
};

class PlayerHelper
{
public:
	static int getPlayerCharacterGUID(Player* player)
	{
		QueryResult charResult = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE name='%s'", player->GetName());
		return charResult->Fetch()[0].GetUInt32();
	}

	static int getTotalStatPointsSpent(int charguid)
	{
		QueryResult result = WorldDatabase.PQuery("SELECT sum(amount) FROM custom_prestige_system_character WHERE charguid=%u", charguid);
		if (!result) return 0;

		Field* fields = result->Fetch();
		return fields[0].GetInt32();
	}

	static void removePrestigeStats(Player* player)
	{
		removePrestigeStatsAuras(player);
		removePrestigeStatsDB(player);
	}

	static void addPrestigeStatsAuras(Player* player)
	{
		PlayerPrestigeStatsContainer container(player);
		std::vector<PrestigeStat> stats = container.getStats();

		for (std::vector<PrestigeStat>::iterator it = stats.begin(); it != stats.end(); ++it)
		{
			PrestigeStat stat = *it;
			std::map<int, int> statsAmount = container.getStatsAmount();
			bool hasKey = statsAmount.find(stat.getID()) != statsAmount.end();
			
			if (hasKey && container.getStatsAmount()[stat.getID()] > 0)
			{
				for (int i = 0; i < container.getStatsAmount()[stat.getID()] * STATS_PER_RANK; i++)
					player->AddAura(stat.getSpellID(), player);
			}
		}
	}

	static void removePrestigeStatsAuras(Player* player)
	{
		PrestigeStatsContainer container;
		std::vector<PrestigeStat> stats = container.getStats();

		for (std::vector<PrestigeStat>::iterator it = stats.begin(); it != stats.end(); ++it)
		{
			PrestigeStat stat = *it;

			Unit* unitPlayer = (Unit*)player;
			unitPlayer->RemoveAurasDueToSpell(stat.getSpellID());
		}
	}

private:
	static void removePrestigeStatsDB(Player* player)
	{
		QueryResult result = WorldDatabase.PQuery("DELETE FROM custom_prestige_system_character WHERE charguid=%u", PlayerHelper::getPlayerCharacterGUID(player));
	}
};

class PrestigeSystemMenu
{
public:
	PrestigeSystemMenu() {}

	//Sends MENU_MAIN
	static void sendMain(Player* player, Creature* creature)
	{
		player->PlayerTalkClass->ClearMenus();
		std::string totalPoints = std::to_string(PlayerHelper::getTotalStatPointsSpent(PlayerHelper::getPlayerCharacterGUID(player)));

		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, IconHelper::buildIconString("Achievement_reputation_argentcrusader") + " Prestige Level: " + totalPoints, GOSSIP_SENDER_MAIN, MENU_MAIN, "", 0);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, IconHelper::buildIconString("Inv_shield_48") + " Prestige Perks", GOSSIP_SENDER_MAIN, MENU_PRESTIGE_PERKS, "", 0);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, IconHelper::buildIconString("Inv_Misc_QuestionMark") + " What is prestige?", GOSSIP_SENDER_MAIN, MENU_WHAT_IS_PRESTIGE, "", 0);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, IconHelper::buildIconString("Inv_gizmo_02") + " Reset Points", GOSSIP_SENDER_MAIN, MENU_RESET_POINTS, "", 0);

		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
	}

	//Sends MENU_PRESTIGE_PERKS
	static void sendPrestigePerks(Player* player, Creature* creature)
	{
		player->PlayerTalkClass->ClearMenus();

		PlayerPrestigeStatsContainer statContainer(player);
		std::vector<PrestigeStat> stats = statContainer.getStats();

		for (std::vector<PrestigeStat>::iterator it = stats.begin(); it != stats.end(); ++it)
		{
			PrestigeStat stat = *it;

			int currentRank = statContainer.getStatsAmount()[stat.getID()];
			int maxRank = stat.getRank();

			std::string msg = IconHelper::buildIconString(stat.getIcon()) + " " + stat.getName() + " " + std::to_string(currentRank) + "/" + std::to_string(maxRank);
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, msg, GOSSIP_SENDER_MAIN, MenuHelper::getStatMenuEntry(stat.getID()), "", 0);
		}

		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "Return", GOSSIP_SENDER_MAIN, MENU_MAIN, "", 0);
		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
	}

	//Sends MENU_WHAT_IS_PRESTIGE
	static void sendWhatIsPrestige(Player* player, Creature* creature)
	{
		player->PlayerTalkClass->ClearMenus();

		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "In order to purchase Prestige Perks you need an Upgrade Token, each upgrade costs 1 Upgrade Token. Upgrade Tokens spent inside Prestige Perks increases certain stats to best suit your needs and playstyle.", GOSSIP_SENDER_MAIN, MENU_WHAT_IS_PRESTIGE, "", 0);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "Return", GOSSIP_SENDER_MAIN, MENU_MAIN, "", 0);
		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
	}

	//Sends MENU_RESET_POINTS
	static void sendResetPoints(Player* player, Creature* creature)
	{
		player->PlayerTalkClass->ClearMenus();

		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "Resetting your Prestige Points will restore all previous spent Upgrade Tokens allowing you to reallocate them for the price of 10000 gold.", GOSSIP_SENDER_MAIN, MENU_RESET_POINTS, "", 0);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "Reset", GOSSIP_SENDER_MAIN, MENU_RESET_POINTS_ACTIVE, "Accepting will reset all prestige points and return all tokens.", 100000000);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "Return", GOSSIP_SENDER_MAIN, MENU_MAIN, "", 0);

		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
	}

	static void sendResetPointsActive(Player* player, Creature* creature)
	{
		player->PlayerTalkClass->ClearMenus();

		int totalStatPoints = PlayerHelper::getTotalStatPointsSpent(PlayerHelper::getPlayerCharacterGUID(player));

		if (totalStatPoints > 0 && player->AddItem(UPGRADE_TOKEN_ENTRY, totalStatPoints))
		{
			PlayerHelper::removePrestigeStats(player);
			player->SaveToDB();
		}

		player->PlayerTalkClass->ClearMenus();
		sendMain(player, creature);
	}

	static void handleNonDefinedMenu(Player* player, Creature* creature, uint32 action)
	{
		//Stats secondary page only eligible if stat has ID between 90000 and 91000
		if (action > 90000 && action < 91000)
			handleStatSecondaryMenu(player, creature, action);

		if (action > 100000 && action < 1001000)
			handleStatPurchaseMenu(player, creature, action);
	}

	static void handleStatSecondaryMenu(Player* player, Creature* creature, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		int statID = MenuHelper::getStatIDFromMenuEntry(action);
		PrestigeStatsContainer container;
		PrestigeStat stat = container.getStat(statID);

		std::string msg = "Choosing this perk increases your " + stat.getName() + " by " + std::to_string(STATS_PER_RANK) + " per point.";

		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, msg, GOSSIP_SENDER_MAIN, action, "", 0);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_MONEY_BAG, "Buy for 1 Upgrade Token", GOSSIP_SENDER_MAIN, MenuHelper::getStatPurchaseMenuEntry(statID), "", 0);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "Return", GOSSIP_SENDER_MAIN, MENU_PRESTIGE_PERKS, "", 0);

		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
	}

	static void handleStatPurchaseMenu(Player* player, Creature* creature, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		if (player->HasItemCount(UPGRADE_TOKEN_ENTRY, UPGRADE_TOKEN_COST))
		{
			int statID = MenuHelper::getStatIDFromPurchaseMenuEntry(action);
			PrestigeStatsContainer container;
			PrestigeStat stat = container.getStat(statID);

			int playerGUID = PlayerHelper::getPlayerCharacterGUID(player);
			int currentRank = StatHelper::GetStatAmount(playerGUID, statID);

			if (stat.getRank() >= currentRank + 1)
			{
				player->DestroyItemCount(UPGRADE_TOKEN_ENTRY, UPGRADE_TOKEN_COST, true);
				StatHelper::SetStatAmount(playerGUID, statID, currentRank + 1);

				PlayerHelper::removePrestigeStatsAuras(player);
				PlayerHelper::addPrestigeStatsAuras(player);
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "You upgraded " + stat.getName() + " by 1 rank", GOSSIP_SENDER_MAIN, action, "", 0);
			}
			else
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "You already have the highest rank of " + stat.getName(), GOSSIP_SENDER_MAIN, action, "", 0);
			}
		}
		else
		{
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "You do not have enough upgrade tokens!", GOSSIP_SENDER_MAIN, action, "", 0);
		}

		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_DOT, "Return", GOSSIP_SENDER_MAIN, MENU_PRESTIGE_PERKS, "", 0);
		player->PlayerTalkClass->SendGossipMenu(GOSSIP_MENU, creature->GetGUID());
	}
};

class PrestigeSystemGossip : public ScriptedAI
{
public:
	PrestigeSystemGossip(Creature* creature) : ScriptedAI(creature) { }

	bool OnGossipHello(Player* player) override
	{
		player->PlayerTalkClass->ClearMenus();
		PrestigeSystemMenu::sendMain(player, me);
		return true;
	}

	bool OnGossipSelect(Player* player, uint32 sender, uint32 gossipDef) override
	{
        auto action = player->PlayerTalkClass->GetGossipOptionSender(gossipDef);
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{
		case MENU_MAIN:
			PrestigeSystemMenu::sendMain(player, me);
			break;
		case MENU_PRESTIGE_PERKS:
			PrestigeSystemMenu::sendPrestigePerks(player, me);
			break;
		case MENU_WHAT_IS_PRESTIGE:
			PrestigeSystemMenu::sendWhatIsPrestige(player, me);
			break;
		case MENU_RESET_POINTS:
			PrestigeSystemMenu::sendResetPoints(player, me);
			break;
		case MENU_RESET_POINTS_ACTIVE:
			PrestigeSystemMenu::sendResetPointsActive(player, me);
			break;
		default:
			PrestigeSystemMenu::handleNonDefinedMenu(player, me, action);
			break;
		}

		return true;
	}
};

class PrestigeSystemPlayer : public PlayerScript
{
public:
	PrestigeSystemPlayer() : PlayerScript("PrestigeSystemPlayer") {}
	
	void OnLogin(Player* player, bool firstLogin) override
	{
		PlayerHelper::addPrestigeStatsAuras(player);
	}
};

void AddSC_PrestigeSystem()
{
	RegisterCreatureAI(PrestigeSystemGossip);
	new PrestigeSystemPlayer();
}
