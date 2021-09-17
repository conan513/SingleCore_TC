#include "ScriptMgr.h"
#include "Chat.h"
#include "Language.h"
#include "CharacterDatabase.h"
#include "DatabaseEnv.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "World.h"
#include "RBAC.h"
#include "WorldSession.h"
#include "Player.h"
#include "World.h"

class CustomRates
{
public:
	static void DeleteRateFromDB(uint64 guid, CharacterDatabaseStatements statement)
	{
        CharacterDatabase.PExecute("DELETE FROM character_xp_rate WHERE guid = %u", guid);
	}

	static int32 GetXpRateFromDB(const Player *player)
	{
		CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_INDIVIDUAL_XP_RATE);
		stmt->setUInt32(0, player->GetGUID());
		PreparedQueryResult result = CharacterDatabase.Query(stmt);

		if (result)
			return static_cast<int32>((*result)[0].GetUInt32());

		return -1;
	}

	static void SaveXpRateToDB(const Player *player, uint32 rate, bool update)
	{
		if (update)
		{
            CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_INDIVIDUAL_XP_RATE);
			stmt->setUInt32(0, rate);
			stmt->setUInt32(1, player->GetGUID());
			CharacterDatabase.Execute(stmt);
		}
		else
		{
            CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_INDIVIDUAL_XP_RATE);
			stmt->setUInt32(0, player->GetGUID());
			stmt->setUInt32(1, rate);
			CharacterDatabase.Execute(stmt);
		}
	}
};

class add_del_rates : public PlayerScript
{
public:
	add_del_rates() : PlayerScript("add_del_rates") { }

	void OnDelete(ObjectGuid guid, uint32 /*accountId*/) override
	{
		CustomRates::DeleteRateFromDB(guid.GetCounter(), CHAR_DEL_INDIVIDUAL_XP_RATE);
	}

	void OnLogin(Player* player, bool firstLogin) override
	{
		// show custom XP rate on login
		int32 rate = CustomRates::GetXpRateFromDB(player);

		if (rate == -1)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("|TInterface/ICONS/trade_engineering:10|t|CFF7BBEF7[Astoria Rates]|r: Your default XP rate was set to 4. You can change via NPC!");
			CustomRates::SaveXpRateToDB(player, 4, false);
		}

		if (rate != -1 && player->GetLevel() != sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
		{
			uint32 uRate = static_cast<uint32>(rate);
			player->SetCustomXpRate(uRate);

			if (sWorld->getBoolConfig(CONFIG_PLAYER_INDIVIDUAL_XP_RATE_SHOW_ON_LOGIN))
			{
				if (uRate)
					ChatHandler(player->GetSession()).PSendSysMessage("|TInterface/ICONS/trade_engineering:10|t|CFF7BBEF7[Astoria Rates]|r: Your XP rate was set to %u. You can change via NPC!", uRate);
				else
					ChatHandler(player->GetSession()).SendSysMessage("|TInterface/ICONS/trade_engineering:10|t|CFF7BBEF7[Astoria Rates]|r: Your XP rate was set to 0. You won't gain any XP anymore.");
			}
		}
	}
};

class npc_rate : public ScriptedAI
{
public:
	npc_rate(Creature* creature) : ScriptedAI(creature) {}

	bool OnGossipHello(Player* player) override
	{
		AddGossipItemFor(player, 0, "Change my XP rate", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, "", 0, true);
		AddGossipItemFor(player, 0, "Show my current XP rate", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		AddGossipItemFor(player, 0, "Nevermind", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

		player->PlayerTalkClass->SendGossipMenu(907, me->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player* player, uint32 /*sender*/, uint32 gossipDef) override
	{
		player->PlayerTalkClass->ClearMenus();
        auto action = player->PlayerTalkClass->GetGossipOptionAction(gossipDef);
		if (action == GOSSIP_ACTION_INFO_DEF + 2)
		{
			// show custom XP rate
			int32 rate = CustomRates::GetXpRateFromDB(player);

			if (rate != -1 && player->GetLevel() != sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
			{
				uint32 uRate = static_cast<uint32>(rate);
				if (uRate)
					ChatHandler(player->GetSession()).PSendSysMessage("|TInterface/ICONS/trade_engineering:10|t|CFF7BBEF7[Astoria Rates]|r: Your XP rate was set to %u.", uRate);
			}
			CloseGossipMenuFor(player);
		}

		if (action == GOSSIP_ACTION_INFO_DEF + 3)
		{
			// This will close a gossip menu
			CloseGossipMenuFor(player);
		}

		return true;
	}

	bool OnGossipSelectCode(Player* player, uint32 senders, uint32 gossipDef, char const* code) override
	{
		player->PlayerTalkClass->ClearMenus();
		CloseGossipMenuFor(player);
        auto sender = player->PlayerTalkClass->GetGossipOptionSender(gossipDef);
        auto action = player->PlayerTalkClass->GetGossipOptionAction(gossipDef);

		if (sender == GOSSIP_SENDER_MAIN)
		{
			if (action == GOSSIP_ACTION_INFO_DEF + 1)
			{
				if (sWorld->getIntConfig(CONFIG_CUSTOM_RATE_XP_ENABLED) == 0)
				{
					ChatHandler(player->GetSession()).PSendSysMessage("Custom Rate xp is disabled");
					player->SetCustomXpRate(1);
					return false;
				}

				// already at max level, no point
				if (player->GetLevel() == sWorld->getIntConfig(CONFIG_CUSTOM_XP_LEVEL))
				{
					ChatHandler(player->GetSession()).PSendSysMessage("|TInterface/ICONS/trade_engineering:10|t|CFF7BBEF7[Astoria Rates]|r: You are already at maximum level.");
					return false;
				}

				// no arguments, show current XP rate
				if (!*code)
				{
					ChatHandler(player->GetSession()).PSendSysMessage("|TInterface/ICONS/trade_engineering:10|t|CFF7BBEF7[Astoria Rates]|r: You must specify a value, your current XP rate is %u.", player->GetCustomXpRate());
					return false;
				}

				// extract value
				int rate = atoi((char*)code);
				int maxRate = sWorld->getIntConfig(CONFIG_PLAYER_MAXIMUM_INDIVIDUAL_XP_RATE);
				if (rate < 0 || rate > maxRate)
				{
					ChatHandler(player->GetSession()).PSendSysMessage("|TInterface/ICONS/trade_engineering:10|t|CFF7BBEF7[Astoria Rates]|r: Invalid rate specified, must be in interval [0,%i].", maxRate);
					return false;
				}

				// set player custom XP rate and save it in DB for later use
				uint32 uRate = static_cast<uint32>(rate);
				player->SetCustomXpRate(uRate);
				int32 rateFromDB = CustomRates::GetXpRateFromDB(player);
				if (rateFromDB == -1)
					CustomRates::SaveXpRateToDB(player, uRate, false);
				else
					CustomRates::SaveXpRateToDB(player, uRate, true);

				// show a message indicating custom XP rate change
				if (uRate == 0)
					ChatHandler(player->GetSession()).PSendSysMessage("|TInterface/ICONS/trade_engineering:10|t|CFF7BBEF7[Astoria Rates]|r: You have set your XP rate to 0. You won't gain any XP anymore.");
				else
					ChatHandler(player->GetSession()).PSendSysMessage("|TInterface/ICONS/trade_engineering:10|t|CFF7BBEF7[Astoria Rates]|r: You have set your XP rate to %u.", uRate);
			}
			return true;
		}
		return true;
	}
};

void AddSC_Custom_Rates()
{
	new add_del_rates();
	RegisterCreatureAI(npc_rate);
}
