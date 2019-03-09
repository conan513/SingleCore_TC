/*
<--------------------------------------------------------------------------->
- Developer: Funnygirl, Mireno, Trix'
- Complete: 100%
- ScriptName: 'Beastmaster_Trainer'
- Developed: 06/03/2016
- Updated: 10/30/2018
<--------------------------------------------------------------------------->
*/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "Globals/ObjectMgr.h"

void CreatePet(Player* player, Creature* creature, uint32 entry)
{
    if (player->getClass() != CLASS_HUNTER)
    {
        creature->MonsterWhisper("I can only train Hunters in the way of the beast.", player, false);
        player->GetSession()->SendNotification("%s , you are not a Hunter!", player->GetName());
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    Map *map = player->GetMap();
    // Creature* creatureTarget = (Creature*)entry;
    Creature* creatureTarget = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() - 2, player->GetPositionZ(), player->GetOrientation(), TEMPSPAWN_TIMED_OOC_DESPAWN, 10); // TEMPSPAWN_TIMED_OOC_DESPAWN, 0
    if (!creatureTarget) return;

    // Caster must be player, checked in Spell::CheckCast
    // Spell can be triggered, we need to check original caster prior to caster
    // Player* player = (Player*)GetAffectiveCaster();

    Pet* pet = new Pet(HUNTER_PET);

    if (!pet->CreateBaseAtCreature(creatureTarget))
    {
        delete pet;
        return;
    }

    pet->SetOwnerGuid(player->GetObjectGuid());
    pet->setFaction(player->getFaction());

    uint32 spell_id = 13481;
    SpellEntry const* spellInfo = GetSpellStore()->LookupEntry<SpellEntry>(spell_id);
    pet->SetUInt32Value(UNIT_CREATED_BY_SPELL, spell_id);

    if (player->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
    {
        pet->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
        pet->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_PLAYER_CONTROLLED_DEBUFF_LIMIT);
    }
    else
        pet->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_CREATURE_DEBUFF_LIMIT);

    if (player->IsImmuneToNPC())
        pet->SetImmuneToNPC(true);

    if (player->IsImmuneToPlayer())
        pet->SetImmuneToPlayer(true);

    if (player->IsPvP())
        pet->SetPvP(true);

    uint32 pet_number = sObjectMgr.GeneratePetNumber();
    pet->GetCharmInfo()->SetPetNumber(pet_number, true);

    uint32 level = creatureTarget->getLevel();
    pet->InitStatsForLevel(level);

    pet->SetHealthPercent(creatureTarget->GetHealthPercent());

    // destroy creature object
    creatureTarget->ForcedDespawn();

    // prepare visual effect for levelup
    pet->SetUInt32Value(UNIT_FIELD_LEVEL, level - 1);

    // add pet object to the world
    pet->GetMap()->Add((Creature*)pet);
    pet->AIM_Initialize();

    pet->AI()->SetReactState(REACT_DEFENSIVE);

    // visual effect for levelup
    pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());
    pet->InitStatsForLevel(player->getLevel());
    // enable rename and abandon prompt
    pet->SetByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_RENAMED);
    pet->SetByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_ABANDONED);
    // happiness
    pet->SetPower(POWER_HAPPINESS, 10480000);
    // loyalty
    pet->SetByteValue(UNIT_FIELD_BYTES_1, 1, 6);

    // this enables pet details window (Shift+P)
    pet->InitPetCreateSpells();

    pet->LearnPetPassives();
    pet->CastPetAuras(true);
    pet->CastOwnerTalentAuras();
    pet->UpdateAllStats();

    pet->SetRequiredXpForNextLoyaltyLevel();

    // caster have pet now
    player->SetPet(pet);

    player->PetSpellInitialize();
    // pet->SetTP(350);
    pet->SetTP(player->getLevel() * 5);
    pet->SavePetToDB(PET_SAVE_AS_CURRENT);

    // make sure player has all training spells
    player->learnSpell(27348, true); // bite
    player->learnSpell(28343, true); // charge
    player->learnSpell(27347, true); // claw
    player->learnSpell(27346, true); // cower
    player->learnSpell(23112, true); // dash
    player->learnSpell(23150, true); // dive
    player->learnSpell(35324, true); // fire breath
    player->learnSpell(24599, true); // furious howl
    player->learnSpell(35308, true); // gore
    player->learnSpell(25017, true); // lightning breath
    player->learnSpell(35391, true); // poison spit
    player->learnSpell(24455, true); // prowl
    player->learnSpell(27361, true); // scorpid poison
    player->learnSpell(27349, true); // screech
    player->learnSpell(26065, true); // spell shield
    player->learnSpell(27366, true); // thunderstomp
    player->learnSpell(35348, true); // warp
    player->learnSpell(27350, true); // arcane res
    player->learnSpell(27353, true); // shadow res
    player->learnSpell(27351, true); // fire res
    player->learnSpell(27352, true); // frost res
    player->learnSpell(27354, true); // nature res
    player->learnSpell(27362, true); // natural armor
    player->learnSpell(27364, true); // great stamina
    player->learnSpell(35700, true); // avoidance
    player->learnSpell(25077, true); // cobra reflexes

    player->CLOSE_GOSSIP_MENU();
    creature->MonsterWhisper("You have learned a way of the beast, congratulations.", player, false);

}

bool GossipHello_Npc_Beastmaster(Player* player, Creature* m_creature)
{
    if (player->getClass() != CLASS_HUNTER)
    {
        m_creature->MonsterWhisper("I can only train Hunters in the way of the beast.", player, false);
        player->GetSession()->SendNotification("%s , you are not a Hunter!", player->GetName());
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_hunter_beasttaming:26:26:-15:0|t|r Give me Pet.", GOSSIP_SENDER_MAIN, 2000);
    player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_hunter_beastcall:26:26:-15:0|t|r Stable your pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
    player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_hunter_beasttraining:26:26:-15:0|t|r Pet Food.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
    // player->ADD_GOSSIP_ITEM(5, "|cff00ff00|TInterface\\icons\\Inv_scroll_03:26:26:-15:0|t|r Reset pet talent points", GOSSIP_SENDER_MAIN, 5555);
    player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_spy:26:26:-15:0|t|r Close.", GOSSIP_SENDER_MAIN, 150);
    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
    return true;
}

bool GossipSelect_Npc_Beastmaster(Player* player, Creature* m_creature, uint32 /*sender*/, uint32 action)
{
    player->PlayerTalkClass->ClearMenus();

    switch (action)
    {

    case 100:
        player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_hunter_beasttaming:26:26:-15:0|t|r Give me Pet.", GOSSIP_SENDER_MAIN, 2000);
        player->ADD_GOSSIP_ITEM(4, "|cff00ff00|cff00ff00|TInterface\\icons\\Ability_hunter_beastcall:26:26:-15:0|t|r Stable your pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
        player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_hunter_beasttraining:26:26:-15:0|t|r Pet Food.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
        // player->ADD_GOSSIP_ITEM(5, "|cff00ff00|TInterface\\icons\\Inv_scroll_03:26:26:-15:0|t|r Reset pet talent points", GOSSIP_SENDER_MAIN, 5555);
        player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_spy:26:26:-15:0|t|r Close.", GOSSIP_SENDER_MAIN, 150);

        // learn players all training spells:
        player->learnSpell(27348, true); // bite
        player->learnSpell(28343, true); // charge
        player->learnSpell(27347, true); // claw
        player->learnSpell(27346, true); // cower
        player->learnSpell(23112, true); // dash
        player->learnSpell(23150, true); // dive
        player->learnSpell(35324, true); // fire breath
        player->learnSpell(24599, true); // furious howl
        player->learnSpell(35308, true); // gore
        player->learnSpell(25017, true); // lightning breath
        player->learnSpell(35391, true); // poison spit
        player->learnSpell(24455, true); // prowl
        player->learnSpell(27361, true); // scorpid poison
        player->learnSpell(27349, true); // screech
        player->learnSpell(26065, true); // spell shield
        player->learnSpell(27366, true); // thunderstomp
        player->learnSpell(35348, true); // warp
        player->learnSpell(27350, true); // arcane res
        player->learnSpell(27353, true); // shadow res
        player->learnSpell(27351, true); // fire res
        player->learnSpell(27352, true); // frost res
        player->learnSpell(27354, true); // nature res
        player->learnSpell(27362, true); // natural armor
        player->learnSpell(27364, true); // great stamina
        player->learnSpell(35700, true); // avoidance
        player->learnSpell(25077, true); // cobra reflexes

        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        break;

        // Close
    case 150:
        player->CLOSE_GOSSIP_MENU();
        break;
        // Stable master
    case GOSSIP_OPTION_STABLEPET:
        player->GetSession()->SendStablePet(m_creature->GetObjectGuid());
        break;
        // Food vendor
    case GOSSIP_OPTION_VENDOR:
        player->GetSession()->SendListInventory(m_creature->GetObjectGuid());
        break;
        // Reset Pet Talent Points
    case 5555:
        player->CLOSE_GOSSIP_MENU();
        /*
        if (player->GetPet())
        // player->resetTalents();
        player->CanTrainAndResetTalentsOf(pet); // this
        else
        ChatHandler(player->GetSession()).PSendSysMessage("You do not have a pet!"); */
        break;
    case 2000:
        if (player->GetPet())
        {
            m_creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", player, false);
            player->CLOSE_GOSSIP_MENU();
            return false;
        }
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_cat:26:26:-15:0|t|r Bangalash.", GOSSIP_SENDER_MAIN, 2001);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_wolf:26:26:-15:0|t|r Wolf.", GOSSIP_SENDER_MAIN, 2012);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_turtle:26:26:-15:0|t|r Turtle.", GOSSIP_SENDER_MAIN, 3001);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_bear:26:26:-15:0|t|r Bear.", GOSSIP_SENDER_MAIN, 3002);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_gorilla:26:26:-15:0|t|r Gorilla.", GOSSIP_SENDER_MAIN, 3003);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_vulture:26:26:-15:0|t|r Carrion Bird.", GOSSIP_SENDER_MAIN, 1002);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_ravager:26:26:-15:0|t|r Ravager.", GOSSIP_SENDER_MAIN, 1003);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Spell_nature_guardianward:26:26:-15:0|t|r Serpent.", GOSSIP_SENDER_MAIN, 1004);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_scorpid:26:26:-15:0|t|r Scorpid.", GOSSIP_SENDER_MAIN, 1005);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_spider:26:26:-15:0|t|r Spider.", GOSSIP_SENDER_MAIN, 1006);
        player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_spy:26:26:-15:0|t|r Close.", GOSSIP_SENDER_MAIN, 150);
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, m_creature->GetObjectGuid());
        break;

        // =====================================================================================================================================

    case 1001: // Bat
        CreatePet(player, m_creature, 8602);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1002: // Bird, Rock
        CreatePet(player, m_creature, 5430); // 23051
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1003: // Ravager
        CreatePet(player, m_creature, 22123); // 19349
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1004: // Serpent
        CreatePet(player, m_creature, 5349);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1005: // Scorpid
        CreatePet(player, m_creature, 4696);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 1006: // Spider
        CreatePet(player, m_creature, 18467);
        player->CLOSE_GOSSIP_MENU();
        break;
        // ============================================
    case 2001: // Bangalash
        CreatePet(player, m_creature, 731);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2002: // Tiger - cat
        CreatePet(player, m_creature, 21723); // 772
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2003: // Boar
        CreatePet(player, m_creature, 157); // 1984
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2004: // Crab
        CreatePet(player, m_creature, 3106); //
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2005: // Crokolisk
        CreatePet(player, m_creature, 4344); //
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2006: // Dragonhawk
        CreatePet(player, m_creature, 20749); //
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2007: // Owl
        CreatePet(player, m_creature, 22265); //
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2008: // Raptor
        CreatePet(player, m_creature, 22052); //
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2009: // Talonstrider
        CreatePet(player, m_creature, 2955); //
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2010: // Hyena
        CreatePet(player, m_creature, 5426); // 3425
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2011: // Mountain Lion Prowl
        CreatePet(player, m_creature, 2406); //
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2012: // Wolf
        CreatePet(player, m_creature, 20330); // 1131
        player->CLOSE_GOSSIP_MENU();
        break;
    case 2013: // Amani Elder Lynx
        CreatePet(player, m_creature, 24530); //
        player->CLOSE_GOSSIP_MENU();
        break;
        // ============================================
    case 3001: // Turtle
        CreatePet(player, m_creature, 14123);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 3002: // Bear
        CreatePet(player, m_creature, 7443);
        player->CLOSE_GOSSIP_MENU();
        break;
    case 3003: // Gorila
        CreatePet(player, m_creature, 1114);
        player->CLOSE_GOSSIP_MENU();
        break;
    }
    return true;
}

void AddSC_Npc_Beastmaster()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_beastmaster";
    newscript->pGossipHello = &GossipHello_Npc_Beastmaster;
    newscript->pGossipSelect = &GossipSelect_Npc_Beastmaster;
    newscript->RegisterSelf();
}
