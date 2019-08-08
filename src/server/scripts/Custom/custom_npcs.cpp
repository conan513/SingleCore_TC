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

#include "Creature.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "World.h"
#include "Config.h"
#include "Chat.h"
#include "WorldSession.h"

class npc_rate_xp_modifier : public CreatureScript
{
    public:
        npc_rate_xp_modifier() : CreatureScript("npc_rate_xp_modifier") { }

#define MAX_RATE uint32(10)

        bool OnGossipHello(Player* player, Creature* creature) override
        {
            if (sConfigMgr->GetBoolDefault("Custom.XP.Rate.NPC", true))
            {
                for (uint32 i = 1; i <= MAX_RATE; ++i)
                {
                    if (i == player->GetPersonnalXpRate())
                        continue;

                    if (i == sWorld->getRate(RATE_XP_KILL))
                        continue;

                    std::ostringstream gossipText;
                    gossipText << "Rate x" << i;
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, gossipText.str(), GOSSIP_SENDER_MAIN, i);
                }
            }
            else
            {
                std::ostringstream gossipText;
                gossipText << "The Custom XP Rate NPC |cff4CFF00disabled |ron this server.";
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, gossipText.str(), GOSSIP_SENDER_MAIN, 0);
            }

            if (player->GetPersonnalXpRate())
            {
                std::ostringstream gossipText;
                gossipText << "Default Rate - x" << sWorld->getRate(RATE_XP_KILL);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, gossipText.str(), GOSSIP_SENDER_MAIN, 0);
            }

            SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*uiSender*/, uint32 uiAction) override
        {
            CloseGossipMenuFor(player);
            player->SetPersonnalXpRate(float(std::min(MAX_RATE, uiAction)));
            return true;
        }

        struct customnpc_passivesAI : public ScriptedAI
        {
            customnpc_passivesAI(Creature * creature) : ScriptedAI(creature) { }

            uint32 uiAdATimer;
            //uint32 uiAdBTimer;
            //uint32 uiAdCTimer;

            void Reset()
            {
                uiAdATimer = 1000;
                //uiAdBTimer = 23000;
                //uiAdCTimer = 11000;
            }

            // Speak
            void UpdateAI(uint32 diff)
            {
                if (Player *player = me->SelectNearestPlayer(10))
                {
                    if (uiAdATimer <= diff)
                    {
                        std::ostringstream messageTaunt;
                        messageTaunt << "|cff4CFF00Greetings, " << player->GetName() << "!";
                        player->GetSession()->SendNotification(messageTaunt.str().c_str());
                        //me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                        me->CastSpell(me, 44940);
                        uiAdATimer = 61000;
                    }
                    else
                        uiAdATimer -= diff;

                    /*if (uiAdBTimer <= diff)
                    {
                        std::ostringstream messageTaunt;
                        messageTaunt << "|cff4CFF00I see you, " << player->GetName() << "!";
                        player->GetSession()->SendNotification(messageTaunt.str().c_str());
                        me->HandleEmoteCommand(EMOTE_ONESHOT_CHICKEN);
                        me->CastSpell(me, 74311);
                        uiAdBTimer = 61000;
                    }
                    else
                        uiAdBTimer -= diff;

                    if (uiAdCTimer <= diff)
                    {
                        std::ostringstream messageTaunt;
                        messageTaunt << "|cff4CFF00Hey " << player->GetName() << " Come over here!";
                        player->GetSession()->SendNotification(messageTaunt.str().c_str());
                        me->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
                        me->CastSpell(me, 72339);
                        uiAdCTimer = 61000;
                    }
                    else
                    {
                        uiAdCTimer -= diff;
                    }*/
                }
            }
        };

        // Creature AI
        CreatureAI * GetAI(Creature * creature) const
        {
            return new customnpc_passivesAI(creature);
        }

};

void AddSC_custom_npcs()
{
    new npc_rate_xp_modifier();
}
