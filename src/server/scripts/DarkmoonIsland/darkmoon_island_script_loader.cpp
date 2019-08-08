/*
 * Copyright (C) 2017-2019 AshamaneProject <https://github.com/AshamaneProject>
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
void AddSC_darkmoon_canon();
void AddSC_darkmoon_island();
void AddSC_darkmoon_rabbit();
void AddSC_darkmoon_tonk();
void AddSC_darkmoon_whack_gnoll();
void AddSC_darkmoon_ring_toss();
void AddSC_darkmoon_teleport();
void AddSC_darkmoon_selina();
void AddSC_darkmoon_shot_gallery();
void AddSC_darkmoon_spells();
void AddSC_darkmoon_items();

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddDarkmoonIslandScripts()
{
    AddSC_darkmoon_canon();
    AddSC_darkmoon_island();
    AddSC_darkmoon_rabbit();
    AddSC_darkmoon_tonk();
    AddSC_darkmoon_whack_gnoll();
	AddSC_darkmoon_ring_toss();
	AddSC_darkmoon_teleport();
	AddSC_darkmoon_selina();
	AddSC_darkmoon_shot_gallery();
	AddSC_darkmoon_spells();
	AddSC_darkmoon_items();
}
