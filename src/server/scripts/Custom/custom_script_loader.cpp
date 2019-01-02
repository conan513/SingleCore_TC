/*
 * Copyright (C) 2008-2019 TrinityCore <https://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// This is where scripts' loading functions should be declared:
void AddSC_custom_npcs();
void AddSC_solocraft();
void AddSC_FireWorksOnLevelUp();
void AddSC_Player_Boa();
void AddSC_gon_playerscripts();
void AddSC_login_script();
void AddSC_announce_login();
void AddSC_Boss_Announcer();
void AddSC_XpWeekend();
void AddSC_RandomEnchantsScript();
void AddSC_Dynamic_Resurrections();
void AddSC_Duel_Reset();
void AddSC_skip_pandaren();
void AddSC_skip_worgen();
void AddSC_skip_goblin();
void AddSC_MoneyForKillsScripts();
void AddSC_player_session_checks();
void AddSC_CongratsOnLevelScripts();
void AddSC_WhoLoggedScripts();
void AddSC_spp_module_announcer();
void AddSC_cs_world_chat();
void AddSC_quest_complete_command();
void AddSC_Death_Announcer();
void AddSC_AutoReviveScripts();
void AddSC_BGRewardScripts();
void AddSC_premium_account();
void AddSC_LFG_SoloMode();
void AddSC_PvPScripts();
void AddSC_custom_feed_pet_heal();
void AddSC_dynamic_xp_rate();
void AddSC_save_on_levelup();
void AddSC_custom_starting();

// ADM declaration begin
// ADM declaration end

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCustomScripts()
{
    AddSC_custom_npcs();
    AddSC_solocraft();
    AddSC_FireWorksOnLevelUp();
    AddSC_Player_Boa();
    AddSC_gon_playerscripts();
    AddSC_login_script();
    AddSC_announce_login();
    AddSC_Boss_Announcer();
    AddSC_XpWeekend();
    AddSC_RandomEnchantsScript();
    AddSC_Dynamic_Resurrections();
    AddSC_Duel_Reset();
    AddSC_skip_pandaren();
    AddSC_skip_worgen();
    AddSC_skip_goblin();
    AddSC_MoneyForKillsScripts();
    AddSC_player_session_checks();
    AddSC_CongratsOnLevelScripts();
    AddSC_WhoLoggedScripts();
    AddSC_spp_module_announcer();
    AddSC_cs_world_chat();
    AddSC_quest_complete_command();
	AddSC_Death_Announcer();
    AddSC_AutoReviveScripts();
    AddSC_BGRewardScripts();
    AddSC_premium_account();
    AddSC_LFG_SoloMode();
    AddSC_PvPScripts();
    AddSC_custom_feed_pet_heal();
    AddSC_dynamic_xp_rate();
    AddSC_save_on_levelup();
    AddSC_custom_starting();
	
    // ADM call begin
    // ADM call end
}
