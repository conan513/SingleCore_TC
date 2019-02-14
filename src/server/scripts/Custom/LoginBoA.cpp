#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "SharedDefines.h"
#include "World.h"
#define Welcome_Name "Blood Lust"

class Player_Boa : public PlayerScript
{

public:
    Player_Boa() : PlayerScript("Player_Boa") { }

    void OnLogin(Player* player, bool firstLogin) override
    {
		if (sConfigMgr->GetBoolDefault("Login.BoA", true))
		{
        if (!firstLogin) // Run script only on first login
            return;
        std::ostringstream ss;
        ss << "|cffFF0000["<<Welcome_Name<<"]|r Welcome " << player->GetName() << " to the server! ";
        sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
        uint32 shoulders = 0, chest = 0, trinkett = 0, weapon = 0, weapon2 = 0, weapon3 = 0, shield = 0, shoulders2 = 0, chest2 = 0, trinkett2 = 0, bag = 0;

        bag = 41600;
        switch (player->getClass())
        {
                case CLASS_WARRIOR:
                //Warrior
				shoulders = 93893;
                chest = 93892;
                trinkett = 122361;
                weapon = 122389;
				shield = 122391;
				shoulders2 = 122355;
				chest2 = 122381;
				weapon2 = 42943;
                break;
                case CLASS_PALADIN:
                //Paladin
                shoulders = 69890;
                chest = 69889;
                trinkett = 42991;
                weapon = 69893;
				shield = 122391;
				shoulders2 = 42951;
				chest2 = 48683;
				trinkett2 = 42992;
				weapon2 = 42948;
                break;
                case CLASS_HUNTER:
                //Hunter
                shoulders = 42950;
                chest = 48677;
                trinkett = 42991;
                weapon = 42943;
                weapon2 = 42946;
				weapon3 = 44093;
                break;
                case CLASS_ROGUE:
                //Rogue
                shoulders = 42952;
                chest = 48689;
                trinkett = 42991;
                weapon = 42944;
                weapon2 = 42944;
                break;
                case CLASS_PRIEST:
                //Priest
                shoulders = 42985;
                chest = 48691;
                trinkett = 42992;
                weapon = 42947;
                break;
                case CLASS_DEATH_KNIGHT:
                //Death Knight
                shoulders = 42949;
                chest = 48685;
                trinkett = 42991;
                weapon = 42945;
                break;
                case CLASS_SHAMAN:
                //Shaman
                shoulders = 122375;
                chest = 48683;
                trinkett = 122362;
                weapon = 122367;
				shield = 122392;
                shoulders2 = 122374;
                chest2 = 122379;
                weapon2 = 122385;
                break;
                case CLASS_MAGE:
                //Mage
                shoulders = 42985;
                chest = 48691;
                trinkett = 42992;
                weapon = 42947;
                break;
                case CLASS_WARLOCK:
                //Warlock
                shoulders = 42985;
                chest = 48691;
                trinkett = 42992;
                weapon = 42947;
                break;
                case CLASS_DRUID:
                //Druid
                shoulders = 42984;
                chest = 48687;
                trinkett = 42992;
                weapon = 42948;
                shoulders2 = 42952;
                chest2 = 48689;
                trinkett2 = 42991;
                weapon2 = 48718;
                break;
                default:
                return;
            }
            switch(player->getClass())
                {
                    case CLASS_WARRIOR:
                        player->AddItem(shoulders, 1);
						player->AddItem(chest, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(weapon, 1);
						player->AddItem(shield, 1);
                        player->AddItem(shoulders2, 1);
						player->AddItem(chest2, 1);
						player->AddItem(weapon2, 1);
                        player->AddItem(bag, 4);
                        break;
					case CLASS_PALADIN:
                        player->AddItem(shoulders, 1);
						player->AddItem(chest, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(weapon, 1);
						player->AddItem(shield, 1);
                        player->AddItem(shoulders2, 1);
						player->AddItem(chest2, 1);
                        player->AddItem(trinkett2, 2);
                        player->AddItem(weapon2, 1);
                        player->AddItem(bag, 4);
                        break;
					case CLASS_HUNTER:
                        player->AddItem(shoulders, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(chest, 1);
                        player->AddItem(weapon, 1);
                        player->AddItem(weapon2, 1);
						player->AddItem(weapon3, 1);
                        player->AddItem(bag, 4);
                        break;
                    case CLASS_ROGUE:
                        player->AddItem(shoulders, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(chest, 1);
                        player->AddItem(weapon, 1);
                        player->AddItem(weapon2, 1);
                        player->AddItem(bag, 4);
                        break;
                    case CLASS_DRUID:
                        player->AddItem(shoulders, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(chest, 1);
                        player->AddItem(weapon, 1);
                        player->AddItem(shoulders2, 1);
                        player->AddItem(chest2, 1);
                        player->AddItem(trinkett2, 2);
                        player->AddItem(weapon2, 1);
                        player->AddItem(bag, 4);
                        break;
                    case CLASS_SHAMAN:
                        player->AddItem(shoulders, 1);
						player->AddItem(chest, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(weapon, 1);
						player->AddItem(shield, 1);
                        player->AddItem(shoulders2, 1);
                        player->AddItem(chest2, 1);
                        player->AddItem(weapon2, 2);
                        player->AddItem(bag, 4);
                        break;
                    default:
                        player->AddItem(shoulders, 1);
                        player->AddItem(trinkett, 2);
                        player->AddItem(chest, 1);
                        player->AddItem(weapon, 1);
            player->AddItem(bag, 4);
                    }
            }
		}	
};

void AddSC_Player_Boa()
{
    new Player_Boa();
}
