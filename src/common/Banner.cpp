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

#include "Banner.h"
#include "GitRevision.h"
#include "StringFormat.h"

void Trinity::Banner::Show(char const* applicationName, void(*log)(char const* text), void(*logExtraInfo)())
{
    log(" ");
    log("###############################################################################");
    log(" ");
    log("  SSSSs   Ss                SSs            SSSSSs");
    log(" Ss   Ss                     Ss           Ss    Ss");
    log("Ss     S  Ss Ss           SS Ss  SSSSS   Ss         SSSSs   Ss SSs   SSSSSs");
    log(" Ss      SSs Sssss    SSSSSs Ss Ss    Ss Ss        Ss   Ss  SSSs Ss Ss    Ss");
    log("  SSSSs   Ss Ss  Ss  Ss   Ss Ss Ss    Ss Ss       Ss     Ss Ss      Ss    Ss");
    log("      Ss  Ss Ss   Ss Ss   Ss Ss SSSSSS   Ss       Ss     Ss Ss      SSSSSSs");
    log(" S     Ss Ss Ss   Ss Ss   Ss Ss Ss       Ss       Ss     Ss Ss      Ss");
    log(" Ss   Ss  Ss Ss   Ss  SSSSSs Ss Ss     s  Ss    S  Ss   Ss  Ss      Ss");
    log("  SSSSs   Ss Ss   Ss      Ss Ss  SSSSSs    SSSSS    SSSSs   Ss       SSSSSSs");
    log("                          Ss");
    log("                      SSSSs                    <<< Based on AshamaneCore >>>");
    log(" ");
    log(" https://github.com/AshamaneProject/AshamaneCore ");
	log("###############################################################################");
	log(" ");

    if (logExtraInfo)
        logExtraInfo();
}
