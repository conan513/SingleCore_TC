#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "SpellHistory.h"
#include "WorldSession.h"

class Duel_Reset : public PlayerScript
{
public:
	Duel_Reset() : PlayerScript("Duel_Reset"){}
	bool UsingPreDuelInfo = true; // CHange this to false if you want a full reset.

	struct MyData
	{
		uint64 resethealth;
		uint64 resetPower;
		uint64 resetEnergy;
		uint64 resetRage;
	};

	std::unordered_map<ObjectGuid, MyData> playerData;
	void GetInfoPreDuel(Player* playerwin, Player* playerlose)
	{
		playerData[playerwin->GetGUID()].resethealth = playerwin->GetHealth();
		playerData[playerwin->GetGUID()].resetPower = playerwin->GetPower(playerwin->getPowerType());
		playerData[playerlose->GetGUID()].resethealth = playerlose->GetHealth();
		playerData[playerlose->GetGUID()].resetPower = playerlose->GetPower(playerlose->getPowerType());
	
	}
	void DoFullReset(Player* playerwin, Player* playerlose)
	{
		playerData[playerwin->GetGUID()].resethealth = playerwin->GetMaxHealth();
		playerData[playerwin->GetGUID()].resetPower = playerwin->GetMaxPower(playerlose->getPowerType());
		playerData[playerlose->GetGUID()].resethealth = playerlose->GetMaxHealth();
		playerData[playerlose->GetGUID()].resetPower = playerlose->GetMaxPower(playerwin->getPowerType());
	}

	void OnDuelStart(Player* playerwin, Player* playerlose)
	{
		if (sConfigMgr->GetBoolDefault("Duel.Reset.Enable", true))
		{
			if (!UsingPreDuelInfo)
			{
				DoFullReset(playerwin, playerlose);
			}
			if (UsingPreDuelInfo)
			{
				GetInfoPreDuel(playerwin, playerlose);
			}
		}
	}

	void OnDuelEnd(Player* playerwin, Player* playerlose, DuelCompleteType /*type*/)
	{
		if (sConfigMgr->GetBoolDefault("Duel.Reset.Enable", true))
		{
			playerwin->SetHealth(playerData[playerwin->GetGUID()].resethealth);
			playerwin->SetPower(playerwin->getPowerType(), playerData[playerwin->GetGUID()].resetPower);
			playerlose->SetHealth(playerData[playerlose->GetGUID()].resethealth);
			playerlose->SetPower(playerlose->getPowerType(), playerData[playerlose->GetGUID()].resetPower);

			if (!UsingPreDuelInfo)
			{
				playerwin->GetSession()->SendNotification("Your Health & Mana has been reset.");
				playerlose->GetSession()->SendNotification("Your Health & Mana has been reset.");
				playerwin->GetSpellHistory()->ResetAllCooldowns();
			}
			else
			{
				playerwin->GetSession()->SendNotification("Your Health & Mana has been reset to what they were before the duel!");
				playerlose->GetSession()->SendNotification("Your Health & Mana has been reset to what they were before the duel!");
			}
			playerData.erase(playerwin->GetGUID());
			playerData.erase(playerlose->GetGUID());
		}
	}
};

void AddSC_Duel_Reset()
{
	new Duel_Reset;
}
