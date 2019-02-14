/*
Single Player Project
*/

#include "Config.h"
#include "Chat.h"
#include "Log.h"

namespace {

    class spp_module_announcer : public PlayerScript 
	{

    public:
        spp_module_announcer() : PlayerScript("spp_module_announcer")
        {
        }

        // Announce Modules
        void OnLogin(Player *player, bool /*firstLogin*/) override
        {
            if (sConfigMgr->GetBoolDefault("Module.Announcer.Enable", true))
            {
                if (sConfigMgr->GetBoolDefault("Solocraft.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00SoloCraft |rmodule is active.");
                }
                
				if (sConfigMgr->GetBoolDefault("Login.Announcer.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00LoginAnnouncer |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("Boss.Announcer.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00BossKillAnnouncer |rmodule is active.");
                }
			    
				if (sConfigMgr->GetBoolDefault("DoubleXP.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00DoubleXPWeekend |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("Duel.Reset.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00DuelReset |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("FireWorksOnLevelUp", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00FireWorksOnMaxLevel |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("Login.BoA", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00Login.BoA |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("Reset.on.login", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00ResetOnLogin |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("Dungeon.Checkpoints.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00DungeonCheckpoints |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("Skip.Worgen.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00SkipWorgen |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("Skip.Goblin.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00SkipGoblin |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("Disallow.Multiple.Client", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00DisallowMultipleClient |rmodule is active.");
                }		
				
				if (sConfigMgr->GetBoolDefault("Hardcore.Mode.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00HardcoreMode |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("MFK.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00MoneyForKill |rmodule is active.");
                }
				
				if (sConfigMgr->GetBoolDefault("Congrats.On.Level.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00CongratsOnLevel |rmodule is active.");
                }
				
                if (sConfigMgr->GetBoolDefault("ImmortalMode.PVE.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00Immortal Mode (PVE) |rmodule is active.");
                }
				
                if (sConfigMgr->GetBoolDefault("ImmortalMode.PVP.Enable", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00Immortal Mode (PVP) |rmodule is active.");
                }
				
                if (sConfigMgr->GetBoolDefault("KilledByCreature.Announcer", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00KilledByCreature Announcer |rmodule is active.");
                }
								
                if (sConfigMgr->GetBoolDefault("LFG.SoloMode", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00LFG SoloMode |rmodule is active.");
                }
                
                if (sConfigMgr->GetBoolDefault("PvPChest", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00PvPChest |rmodule is active.");
                }

                if (sConfigMgr->GetBoolDefault("Custom.GainHonorOnGuardKill", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00GainHonorOnGuardKill |rmodule is active.");
                }
				
                if (sConfigMgr->GetBoolDefault("Custom.GainHonorOnEliteKill", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00GainHonorOnEliteKill |rmodule is active.");
                }
								
                if (sConfigMgr->GetBoolDefault("Feed.Pet.Heal", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00Feed Pet Heal |rmodule is active.");
                }
				
                if (sConfigMgr->GetBoolDefault("Save.On.LevelUp", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00Save On LevelUp |rmodule is active.");
                }
				
                if (sConfigMgr->GetBoolDefault("Force.Starting.Level", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00Force Starting Level |rmodule is active.");
                }
				
                if (sConfigMgr->GetBoolDefault("Force.Teleport", true))
                {
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00Force Teleport |rmodule is active.");
                }
            }
            ChatHandler(player->GetSession()).SendSysMessage("This server based on |cffFF0000Single Player Project - Cataclysm |rrepack.");
            ChatHandler(player->GetSession()).SendSysMessage("Website:|cffADD8E6 https://www.patreon.com/conan513 |r");
        }
    };
}

class PrepareToPlay : public WorldScript
{
public:
	PrepareToPlay() : WorldScript("PrepareToPlay") {}

	void OnStartup() override
	{
        TC_LOG_INFO("server.loading", ".");
		TC_LOG_INFO("server.loading", ">> Loaded custom scripts:");
        if (sConfigMgr->GetBoolDefault("Solocraft.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Solocraft");
        }
        if (sConfigMgr->GetBoolDefault("Login.Announcer.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Login Announcer");
        }
        if (sConfigMgr->GetBoolDefault("Boss.Announcer.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Boss Announcer");
        }
        if (sConfigMgr->GetBoolDefault("DoubleXP.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Double XP Weekend");
        }
        if (sConfigMgr->GetBoolDefault("Duel.Reset.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Duel Reset");
        }
        if (sConfigMgr->GetBoolDefault("FireWorksOnLevelUp", true))
        {
            TC_LOG_INFO("server.loading", "- FireWorksOnLevelUp");
        }
        if (sConfigMgr->GetBoolDefault("Login.BoA", true))
        {
            TC_LOG_INFO("server.loading", "- Login.BoA");
        }
        if (sConfigMgr->GetBoolDefault("Reset.on.login", true))
        {
            TC_LOG_INFO("server.loading", "- Reset on login");
        }
        if (sConfigMgr->GetBoolDefault("Dungeon.Checkpoints.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Dungeon Checkpoints");
        }
        if (sConfigMgr->GetBoolDefault("Skip.Worgen.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Skip Worgen starting area");
        }
        if (sConfigMgr->GetBoolDefault("Skip.Goblin.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Skip Goblin starting area");
        }
        if (sConfigMgr->GetBoolDefault("Disallow.Multiple.Client", true))
        {
            TC_LOG_INFO("server.loading", "- Disallow Multiple Client");
        }
        if (sConfigMgr->GetBoolDefault("Hardcore.Mode.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Hardcore Mode");
        }
        if (sConfigMgr->GetBoolDefault("MFK.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Money for Kill");
        }
        if (sConfigMgr->GetBoolDefault("Congrats.On.Level.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Congrats on Level");
        }
        if (sConfigMgr->GetBoolDefault("ImmortalMode.PVE.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Immortal Mode (PVE)");
        }
        if (sConfigMgr->GetBoolDefault("ImmortalMode.PVP.Enable", true))
        {
            TC_LOG_INFO("server.loading", "- Immortal Mode (PVP)");
        }
        if (sConfigMgr->GetBoolDefault("KilledByCreature.Announcer", true))
        {
            TC_LOG_INFO("server.loading", "- KilledByCreature Announcer");
        }
        if (sConfigMgr->GetBoolDefault("LFG.SoloMode", true))
        {
            TC_LOG_INFO("server.loading", "- LFG SoloMode");
        }
        if (sConfigMgr->GetBoolDefault("PvPChest", true))
        {
            TC_LOG_INFO("server.loading", "- PvPChest");
        }
        if (sConfigMgr->GetBoolDefault("Custom.GainHonorOnGuardKill", true))
        {
            TC_LOG_INFO("server.loading", "- GainHonorOnGuardKill");
        }
        if (sConfigMgr->GetBoolDefault("Custom.GainHonorOnEliteKill", true))
        {
            TC_LOG_INFO("server.loading", "- GainHonorOnEliteKill");
        }
        if (sConfigMgr->GetBoolDefault("Feed.Pet.Heal", true))
        {
            TC_LOG_INFO("server.loading", "- Feed Pet Heal");
        }
        if (sConfigMgr->GetBoolDefault("Save.On.LevelUp", true))
        {
            TC_LOG_INFO("server.loading", "- Save on LevelUp");
        }
        if (sConfigMgr->GetBoolDefault("Force.Teleport", true))
        {
            TC_LOG_INFO("server.loading", "- Force Teleport");
        }
        if (sConfigMgr->GetBoolDefault("Force.Starting.Level", true))
        {
            TC_LOG_INFO("server.loading", "- Force Starting Level");
        }
        TC_LOG_INFO("server.loading", ".");
        TC_LOG_INFO("server.loading", "Now you ready to play.");
	}
};

void AddSC_spp_module_announcer() {
    new spp_module_announcer();
    new PrepareToPlay();
}
