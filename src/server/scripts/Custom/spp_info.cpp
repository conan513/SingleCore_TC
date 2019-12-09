/*
Single Player Project
*/

#include "Config.h"
#include "Chat.h"
#include "Log.h"

namespace {

    class spp_info : public PlayerScript 
	{

    public:
        spp_info() : PlayerScript("spp_info")
        {
        }

        // Informations ingame
        void OnLogin(Player *player, bool /*firstLogin*/) override
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server based on |cffFF0000Single Player Project - WotLK with npcbots |rrepack.");
            ChatHandler(player->GetSession()).SendSysMessage("Website:|cffADD8E6 spp-forum.de |r");
        }
    };
}

class PrepareToPlay : public WorldScript
{
public:
	PrepareToPlay() : WorldScript("PrepareToPlay") {}

	void OnStartup() override
	{
        TC_LOG_INFO("server.loading", " ");
        TC_LOG_INFO("server.loading", "##############################################");
        TC_LOG_INFO("server.loading", "# Single Player Project - WotLK with npcbots #");
        TC_LOG_INFO("server.loading", "# Website: spp-forum.de                      #");
        TC_LOG_INFO("server.loading", "##############################################");
        TC_LOG_INFO("server.loading", " ");
        TC_LOG_INFO("server.loading", "You can find the full game here: https://www.warmane.com");
        TC_LOG_INFO("server.loading", "Change realmlist address in realmlist.wtf file to 127.0.0.1 or to a custom server address.");
        TC_LOG_INFO("server.loading", " ");
        TC_LOG_INFO("server.loading", "Included softwares:");
        TC_LOG_INFO("server.loading", "- TrinityCore        https://github.com/TrinityCore/TrinityCore");
        TC_LOG_INFO("server.loading", "- Notepad++          https://notepad-plus-plus.org");
        TC_LOG_INFO("server.loading", "- 7zip               https://www.7-zip.org");
        TC_LOG_INFO("server.loading", "- MariaDB            https://mariadb.org");
        TC_LOG_INFO("server.loading", "- Wget for Windows   http://gnuwin32.sourceforge.net/packages/wget.htm");
        TC_LOG_INFO("server.loading", " ");
        TC_LOG_INFO("server.loading", "SPP Tools:");
        TC_LOG_INFO("server.loading", "- Account_Creator:   you can create normal and admin accounts there");
        TC_LOG_INFO("server.loading", "- Server_IP_Changer: use it to change the server IP address (works with Hamachi or Internet address too)");
        TC_LOG_INFO("server.loading", " ");
        TC_LOG_INFO("server.loading", "Use .npcbot command ingame as an admin character to spawn npcbots.");
        TC_LOG_INFO("server.loading", "You need to restart the server to get it working after you spawned enough bots into the world.");
        TC_LOG_INFO("server.loading", " ");
        TC_LOG_INFO("server.loading", "Now you ready to play.");
	}
};

void AddSC_spp_info() {
    new spp_info();
    new PrepareToPlay();
}
