/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
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

void AddSC_SpellRegulator();
void AddSC_MobRegulator();
void AddSC_MapRegulator();
void AddSC_regulatorcs();
void AddSC_Transmogrification();
void AddSC_HighRiskSystems();
void AddSC_Custom_Rates();
void AddSC_npc_rank_trainer();
void AddSC_race_npc();
void AddSC_AstoriaHonorSystem();
void AddSC_CustomSpellSystem();
void AddSC_PrestigeSystem();

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCustomScripts()
{
	AddSC_SpellRegulator();
	AddSC_MobRegulator();
	AddSC_MapRegulator();
	AddSC_regulatorcs();
//	AddSC_CustomSpellSystem();
	AddSC_Transmogrification();
//	AddSC_PrestigeSystem();
	AddSC_HighRiskSystems();
	AddSC_Custom_Rates();
	AddSC_npc_rank_trainer();
	AddSC_race_npc();
	AddSC_AstoriaHonorSystem();
}
