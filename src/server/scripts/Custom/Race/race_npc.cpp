#include "ScriptedGossip.h"
#include "DatabaseEnv.h"
#include "Chat.h"

#define RACIAL_MAX 10

enum Racials
{
	RACIAL_HUMAN = 754,
	RACIAL_ORC = 125,
	RACIAL_DWARF = 101,
	RACIAL_NIGHT = 126,
	RACIAL_UNDEAD = 220,
	RACIAL_TAUREN = 124,
	RACIAL_GNOME = 753,
	RACIAL_TROLL = 733,
	RACIAL_BLOOD = 756,
	RACIAL_DRANEI = 760
};

std::string GetRaceNameById(uint32 id)
{
	std::string sClass = "";
	switch (id)
	{
	case RACIAL_HUMAN:         sClass = "Human ";        break;
	case RACIAL_ORC:         sClass = "Orc ";           break;
	case RACIAL_DWARF:          sClass = "Dwarf ";           break;
	case RACIAL_NIGHT:           sClass = "NightElf ";          break;
	case RACIAL_UNDEAD:          sClass = "Undead ";         break;
	case RACIAL_TAUREN:    sClass = "Tauren ";             break;
	case RACIAL_GNOME:          sClass = "Gnome ";          break;
	case RACIAL_TROLL:            sClass = "Troll ";           break;
	case RACIAL_BLOOD:         sClass = "BloodElf ";        break;
	case RACIAL_DRANEI:           sClass = "Dranei ";          break;
	}
	return sClass;
}

uint32 racial[] = { 754, 125, 101, 126, 220, 124, 753, 733, 756, 760 };
uint32 hackfixed[] = { 28877, 822, 28730, 50613, 25046, 28875, 6562, 59221, 59542, 20573, 20574, 65222, 20575, 20576, 54562, 21563, 33697, 33702, 20572 };

class CustomRacial
{
public:
	static void DeleteRacialFromDB(uint64 guid)
	{
		CharacterDatabase.PExecute("DELETE FROM character_racial WHERE guid = %u", guid);
	}

	static int32 GetRacialFromDB(const Player* player)
	{
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_INDIVIDUAL_RACIAL);
		stmt->setUInt32(0, player->GetGUID());
		PreparedQueryResult result = CharacterDatabase.Query(stmt);

		if (result)
			return static_cast<int32>((*result)[0].GetUInt32());

		return -1;
	}

	static int32 GetOrcRacialFromDB(const Player* player)
	{
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_ORC_SEL_INDIVIDUAL_RACIAL);
		stmt->setUInt32(0, player->GetGUID());
		PreparedQueryResult result = CharacterDatabase.Query(stmt);

		if (result)
			return static_cast<int32>((*result)[0].GetUInt32());

		return -1;
	}

	static void SaveRacialToDB(const Player* player, uint32 rate, bool update)
	{
		if (update)
		{
            CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_INDIVIDUAL_RACIAL);
			stmt->setUInt32(0, rate);
			stmt->setUInt32(1, player->GetGUID());
			CharacterDatabase.Execute(stmt);
		}
		else
		{
            CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_INDIVIDUAL_RACIAL);
			stmt->setUInt32(0, player->GetGUID());
			stmt->setUInt32(1, rate);
			CharacterDatabase.Execute(stmt);
		}
	}

	static void SaveOrcRacialToDB(const Player* player, uint32 orc)
	{
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_ORC_INDIVIDUAL_RACIAL);
		stmt->setUInt32(0, orc);
		stmt->setUInt32(1, player->GetGUID());
		CharacterDatabase.Execute(stmt);
	}
};

void LearnCustomRacial(Player* player, uint32 option)
{
	switch (option)
	{
	case 1:
		player->SetSkill(RACIAL_HUMAN, 0, 1, 1);
		ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Human |cff3060B5racials!");
		break;
	case 2:
		//player->SetSkill(RACIAL_ORC, 0, 1, 1, true);
		player->LearnSpell(20573, true, RACIAL_ORC);
		player->LearnSpell(20574, true, RACIAL_ORC);
		if (player->GetClass() == CLASS_SHAMAN)
			player->LearnSpell(65222, true, RACIAL_ORC);
		else if (player->GetClass() == CLASS_WARLOCK)
			player->LearnSpell(20575, true, RACIAL_ORC);
		else if (player->GetClass() == CLASS_HUNTER)
			player->LearnSpell(20576, true, RACIAL_ORC);
		else if (player->GetClass() == CLASS_DEATH_KNIGHT)
			player->LearnSpell(54562, true, RACIAL_ORC);
		else if (player->GetClass() == CLASS_WARRIOR || player->GetClass() == CLASS_PALADIN || player->GetClass() == CLASS_ROGUE || player->GetClass() == CLASS_PRIEST || player->GetClass() == CLASS_MAGE || player->GetClass() == CLASS_DRUID)
			player->LearnSpell(21563, true, RACIAL_ORC);
		break;
	case 3:
		player->SetSkill(RACIAL_DWARF, 0, 1, 1);
		ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Dwarf |cff3060B5racials!");
		break;
	case 4:
		player->SetSkill(RACIAL_NIGHT, 0, 1, 1);
		ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Night Elf |cff3060B5racials!");
		break;
	case 5:
		player->SetSkill(RACIAL_UNDEAD, 0, 1, 1);
		ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Undead |cff3060B5racials!");
		break;
	case 6:
		player->SetSkill(RACIAL_TAUREN, 0, 1, 1);
		ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Tauren |cff3060B5racials!");
		break;
	case 7:
		player->SetSkill(RACIAL_GNOME, 0, 1, 1);
		ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Gnome |cff3060B5racials!");
		break;
	case 88:
		player->SetSkill(RACIAL_TROLL, 0, 1, 1);
		ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Troll |cff3060B5racials!");
		break;
	case 9:
		player->LearnSpell(28877, true, RACIAL_BLOOD);
		player->LearnSpell(822, true, RACIAL_BLOOD);
		if (player->GetPowerType() == POWER_MANA)
			player->LearnSpell(28730, true, RACIAL_BLOOD);
		else if (player->GetPowerType() == POWER_RUNIC_POWER)
			player->LearnSpell(50613, true, RACIAL_BLOOD);
		else
			player->LearnSpell(25046, true, RACIAL_BLOOD);
		ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Blood Elf |cff3060B5racials!");
		break;
	case 10:
		//player->SetSkill(RACIAL_DRANEI, 0, 1, 1, true);
		player->LearnSpell(28875, true, RACIAL_DRANEI);
		player->LearnSpell(6562, true, RACIAL_DRANEI);
		player->LearnSpell(59221, true, RACIAL_DRANEI);
		player->LearnSpell(59542, true, RACIAL_DRANEI);
		ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Draenei |cff3060B5racials!");
		break;
	default:
		break;
	}
}

void SaveRacialOption(Player* player, uint32 option)
{
	int32 rateFromDB = CustomRacial::GetRacialFromDB(player);
	if (rateFromDB == -1)
		CustomRacial::SaveRacialToDB(player, option, false);
	else
		CustomRacial::SaveRacialToDB(player, option, true);
}

struct race_npc : public ScriptedAI
{
public:
    race_npc(Creature* creature) : ScriptedAI(creature) {}

	bool OnGossipHello(Player* player) override
	{
		for (int i = 0; i < RACIAL_MAX; i++)
		{
			if (player->HasSkill(racial[i]))
			{
				std::stringstream status;
				status << "|cff3060B5Actually you have the|r " << GetRaceNameById(racial[i]).c_str() << "|cff3060B5racials!\n";
				AddGossipItemFor(player, 0, status.str().c_str(), GOSSIP_SENDER_MAIN, 0);
			}
		}

		if (player->HasSpell(20573))
		{
			std::stringstream status;
			status << "|cff3060B5Actually you have the|r " << "Orc " << "|cff3060B5racials!\n";
			AddGossipItemFor(player, 0, status.str().c_str(), GOSSIP_SENDER_MAIN, 0);
		}

		if (player->HasSpell(28877))
		{
			std::stringstream status;
			status << "|cff3060B5Actually you have the|r " << "Blood Elf " << "|cff3060B5racial!\n";
			AddGossipItemFor(player, 0, status.str().c_str(), GOSSIP_SENDER_MAIN, 0);
		}

		if (player->HasSpell(6562))
		{
			std::stringstream status;
			status << "|cff3060B5Actually you have the|r " << "Dranei " << "|cff3060B5racials!\n";
			AddGossipItemFor(player, 0, status.str().c_str(), GOSSIP_SENDER_MAIN, 0);
		}

		AddGossipItemFor(player, 0, "Human Racials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		AddGossipItemFor(player, 0, "Orc Racials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		AddGossipItemFor(player, 0, "Dwarf Racials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		AddGossipItemFor(player, 0, "NightElf Racials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		AddGossipItemFor(player, 0, "Undead Racials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
		AddGossipItemFor(player, 0, "Tauren Racials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
		AddGossipItemFor(player, 0, "Gnome Racials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
		AddGossipItemFor(player, 0, "Troll Racials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
		AddGossipItemFor(player, 0, "BloodElf Racials.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
		AddGossipItemFor(player, 0, "Draenei Racials.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);

		AddGossipItemFor(player, 0, "Don't change my Racials for now.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 103);

		player->PlayerTalkClass->SendGossipMenu(907, me->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player* player, uint32 /*sender*/, uint32 actions) override
	{
        uint32 action = player->PlayerTalkClass->GetGossipOptionAction(actions);

		if (action < GOSSIP_ACTION_INFO_DEF + 99 && action != 0 && !player->HasItemCount(60002, 1)) // check item here
		{
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You don't have enough Soul Points to change your racials!");
			CloseGossipMenuFor(player);
			return false;
		}

		ClearGossipMenuFor(player);

		if (action < GOSSIP_ACTION_INFO_DEF + 99 && action != 0)
		{
			for (int i = 0; i < RACIAL_MAX; i++)
			{
				if (player->HasSkill(racial[i]))
					player->SetSkill(racial[i], 0, 0, 0);
			}

			for (int i = 0; i < 19; i++)
			{
				if (player->HasSpell(hackfixed[i]))
					player->RemoveSpell(hackfixed[i]);
			}

			player->DestroyItemCount(60002, 1, true); // item destroyed here
		}

		if (action < GOSSIP_ACTION_INFO_DEF + 99 && action != 0 && action != GOSSIP_ACTION_INFO_DEF + 2)
		{
			CloseGossipMenuFor(player);
			player->SaveToDB();
		}

		switch (action)
		{
		case GOSSIP_ACTION_INFO_DEF + 1:
			player->SetSkill(RACIAL_HUMAN, 0, 1, 1);
			SaveRacialOption(player, 1);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Human |cff3060B5racials!");
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			//player->SetSkill(RACIAL_ORC, 0, 1, 1, true);
			player->LearnSpell(20573, true, RACIAL_ORC);
			player->LearnSpell(20574, true, RACIAL_ORC);
			if (player->GetClass() == CLASS_SHAMAN)
				player->LearnSpell(65222, true, RACIAL_ORC);
			else if (player->GetClass() == CLASS_WARLOCK)
				player->LearnSpell(20575, true, RACIAL_ORC);
			else if (player->GetClass() == CLASS_HUNTER)
				player->LearnSpell(20576, true, RACIAL_ORC);
			else if (player->GetClass() == CLASS_DEATH_KNIGHT)
				player->LearnSpell(54562, true, RACIAL_ORC);
			else if (player->GetClass() == CLASS_WARRIOR || player->GetClass() == CLASS_PALADIN || player->GetClass() == CLASS_ROGUE || player->GetClass() == CLASS_PRIEST || player->GetClass() == CLASS_MAGE || player->GetClass() == CLASS_DRUID)
				player->LearnSpell(21563, true, RACIAL_ORC);
			SaveRacialOption(player, 2);
			AddGossipItemFor(player, 0, "Blood Fury - Increases melee attack power by 6 and your spell damage by 5. Lasts 15 sec.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
			AddGossipItemFor(player, 0, "Blood Fury - Increases your spell power by 5. Lasts 15 sec.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 101);
			AddGossipItemFor(player, 0, "Blood Fury - Increases attack power by 6. Lasts 15 sec.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 102);
			player->PlayerTalkClass->SendGossipMenu(907, me->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			player->SetSkill(RACIAL_DWARF, 0, 1, 1);
			SaveRacialOption(player, 3);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Dwarf |cff3060B5racials!");
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
            player->SetSkill(RACIAL_NIGHT, 0, 1, 1);
			SaveRacialOption(player, 4);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r NightElf |cff3060B5racials!");
			break;
		case GOSSIP_ACTION_INFO_DEF + 5:
			player->SetSkill(RACIAL_UNDEAD, 0, 1, 1);
			SaveRacialOption(player, 5);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Undead |cff3060B5racials!");
			break;
		case GOSSIP_ACTION_INFO_DEF + 6:
			player->SetSkill(RACIAL_TAUREN, 0, 1, 1);
			SaveRacialOption(player, 6);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Tauren |cff3060B5racials!");
			break;
		case GOSSIP_ACTION_INFO_DEF + 7:
			player->SetSkill(RACIAL_GNOME, 0, 1, 1);
			SaveRacialOption(player, 7);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Gnome |cff3060B5racials!");
			break;
		case GOSSIP_ACTION_INFO_DEF + 8:
			player->SetSkill(RACIAL_TROLL, 0, 1, 1);
			SaveRacialOption(player, 8);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Troll |cff3060B5racials!");
			break;
		case GOSSIP_ACTION_INFO_DEF + 9:
			player->LearnSpell(28877, true, RACIAL_BLOOD);
			player->LearnSpell(822, true, RACIAL_BLOOD);
			if (player->GetPowerType() == POWER_MANA)
				player->LearnSpell(28730, true, RACIAL_BLOOD);
			else if (player->GetPowerType() == POWER_RUNIC_POWER)
				player->LearnSpell(50613, true, RACIAL_BLOOD);
			else
				player->LearnSpell(25046, true, RACIAL_BLOOD);
			SaveRacialOption(player, 9);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r BloodElf |cff3060B5racials!");
			break;
		case GOSSIP_ACTION_INFO_DEF + 10:
			//player->SetSkill(RACIAL_DRANEI, 0, 1, 1, true);
			player->LearnSpell(28875, true, RACIAL_DRANEI);
			player->LearnSpell(6562, true, RACIAL_DRANEI);
			player->LearnSpell(59221, true, RACIAL_DRANEI);
			player->LearnSpell(59542, true, RACIAL_DRANEI);
			SaveRacialOption(player, 10);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Draenei |cff3060B5racials!");
			break;
		case GOSSIP_ACTION_INFO_DEF + 100:
			player->LearnSpell(33697, true, RACIAL_ORC);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Orc |cff3060B5racials!");
			CustomRacial::SaveOrcRacialToDB(player, 1);
			CloseGossipMenuFor(player);
			break;
		case GOSSIP_ACTION_INFO_DEF + 101:
			player->LearnSpell(33702, true, RACIAL_ORC);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Orc |cff3060B5racials!");
			CustomRacial::SaveOrcRacialToDB(player, 2);
			CloseGossipMenuFor(player);
			break;
		case GOSSIP_ACTION_INFO_DEF + 102:
			player->LearnSpell(20572, true, RACIAL_ORC);
			ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Orc |cff3060B5racials!");
			CustomRacial::SaveOrcRacialToDB(player, 3);
			CloseGossipMenuFor(player);
			break;
		case GOSSIP_ACTION_INFO_DEF + 103:
			CloseGossipMenuFor(player);
			break;
		default:
			break;
		}
		return true;

	}
};

class PS_race : public PlayerScript
{
public:
	PS_race() : PlayerScript("PS_race") { }

	void OnDelete(ObjectGuid guid, uint32 /*accountId*/) override
	{
		CustomRacial::DeleteRacialFromDB(guid.GetCounter());
	}

	void OnLogin(Player* player, bool /*firstLogin*/) override
	{
		int32 option = CustomRacial::GetRacialFromDB(player);

		if (option != -1)
		{
			for (int i = 0; i < RACIAL_MAX; i++)
			{
				if (player->HasSkill(racial[i]))
					player->SetSkill(racial[i], 0, 0, 0);
			}

			for (int i = 0; i < 19; i++)
			{
				if (player->HasSpell(hackfixed[i]))
					player->RemoveSpell(hackfixed[i]);
			}

			uint32 uOption = static_cast<uint32>(option);
			LearnCustomRacial(player, uOption);

			if (uOption == 2)
			{
				int32 orc = CustomRacial::GetOrcRacialFromDB(player);
				uint32 uOrc = static_cast<uint32>(option);

				switch (uOrc)
				{
				case 1:
					player->LearnSpell(33697, true, RACIAL_ORC);
					break;
				case 2:
					player->LearnSpell(33702, true, RACIAL_ORC);
					break;
				case 3:
					player->LearnSpell(20572, true, RACIAL_ORC);
					break;
				default:
					break;
				}
				ChatHandler(player->GetSession()).PSendSysMessage("|cff3060B5You have learned the|r Orc |cff3060B5racials!");
			}
		}
	}
};

void AddSC_race_npc()
{
	RegisterCreatureAI(race_npc);
	new PS_race();
}
