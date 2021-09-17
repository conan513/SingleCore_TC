#include "Player.h"
#include "Creature.h"
#include "AccountMgr.h"
#include "ScriptMgr.h"
#include "Define.h"
#include "Map.h"
#include "Pet.h"
#include "Item.h"
#include "Chat.h"
#include "WorldSession.h"
#include "DBCStores.h"
#include "GameObject.h"
#include "LootMgr.h"
#include "Bag.h"

#include <G3D/Box.h>
#include <G3D/CoordinateFrame.h>
#include <G3D/Quat.h>

#define SPELL_SICKNESS 15007
#define GOB_CHEST 179697

void ReskillCheck(Player* killer, Player* killed)
{
	// if killer have same ip as killed or if player kill self dont spawn chest
	if (killer->GetSession()->GetRemoteAddress() == killed->GetSession()->GetRemoteAddress() || killer->GetGUID() == killed->GetGUID())
		return;

	// if player have sickness, dont drop loot
	if (killed->HasAura(SPELL_SICKNESS))
		return;

	// if player is above 5 levels or more, dont drop loot
	if (killer->GetLevel() - 5 >= killed->GetLevel())
		return;

	// dont drop if player is killed in arena or battleground
	if (killed->GetMap()->IsBattlegroundOrArena())
		return;

	// if player is in sanctuary zone dont drop loot
	AreaTableEntry const* area = sAreaTableStore.LookupEntry(killed->GetAreaId());
	AreaTableEntry const* area2 = sAreaTableStore.LookupEntry(killer->GetAreaId());

	if (area->IsSanctuary() || area2->IsSanctuary())
		return;
}

class HighRiskSystem : public PlayerScript
{
public:
	HighRiskSystem() : PlayerScript("HighRiskSystem") {}

	void OnPVPKill(Player* killer, Player* killed)
	{
		ReskillCheck(killer, killed);

		if (!killed->IsAlive())
		{
			uint32 prev = 0;
			uint32 count = 0;
			Position pos = killed->GetPosition();
            QuaternionData rot = QuaternionData::fromEulerAnglesZYX(pos.GetOrientation(), 0.f, 0.f);
			if (GameObject* go = killer->SummonGameObject(GOB_CHEST, pos, rot, Seconds(300), GO_SUMMON_TIMED_DESPAWN))
			{
				killer->AddGameObject(go);
				go->SetOwnerGUID(ObjectGuid::Empty);

				/* Equipment Set first */

				for (uint8 i = urand(0, 17); i < EQUIPMENT_SLOT_END; ++i)
				{
					if (Item* pItem = killed->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
					{
						if (pItem->GetTemplate() && (!pItem->IsEquipped() || pItem->GetTemplate()->Quality < ITEM_QUALITY_UNCOMMON))
							continue;

						uint8 slot = pItem->GetSlot();
						ChatHandler(killed->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());
						LootStoreItem storeItem = LootStoreItem(pItem->GetEntry(), 0, 100, 0, LOOT_MODE_DEFAULT, 0, 1, 1);
						go->loot.AddItem(storeItem);
						killed->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
						prev = i;
						count++;
						break;
					}
				}

				for (uint8 i = urand(0, 17); i < EQUIPMENT_SLOT_END; ++i)
				{
					if (!roll_chance_i(70))
						break;

					if (Item* pItem = killed->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
					{
						if (pItem->GetTemplate() && (!pItem->IsEquipped() || pItem->GetTemplate()->Quality < ITEM_QUALITY_UNCOMMON))
							continue;

						if (prev == i)
							continue;

						uint8 slot = pItem->GetSlot();
						ChatHandler(killed->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());
						LootStoreItem storeItem = LootStoreItem(pItem->GetEntry(), 0, 100, 0, LOOT_MODE_DEFAULT, 0, 1, 1);
						go->loot.AddItem(storeItem);
						killed->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
						prev = 0;
						count++;
						break;
					}
				}

				/* Main bag and bagpacks */

				for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
				{
					if (Item* pItem = killed->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
					{
						if (count >= 2)
							break;

						if (pItem->GetTemplate() && pItem->GetTemplate()->Quality < ITEM_QUALITY_UNCOMMON)
							continue;

						uint8 slot = pItem->GetSlot();
						ChatHandler(killed->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());
						LootStoreItem storeItem = LootStoreItem(pItem->GetEntry(), 0, 100, 0, LOOT_MODE_DEFAULT, 0, 1, 1);
						go->loot.AddItem(storeItem);
						killed->DestroyItemCount(pItem->GetEntry(), pItem->GetCount(), true, false);
						count++;
						break;
					}
				}

				//Other bags:
				for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
				{
					if (Bag* bag = killed->GetBagByPos(i))
					{
						for (uint32 j = 0; j < bag->GetBagSize(); ++j)
						{
							if (Item* pItem = killed->GetItemByPos(i, j))
							{
								if (count >= 2)
									break;

								if (pItem->GetTemplate() && pItem->GetTemplate()->Quality < ITEM_QUALITY_UNCOMMON)
									continue;

								uint8 slot = pItem->GetSlot();
								ChatHandler(killed->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());
								LootStoreItem storeItem = LootStoreItem(pItem->GetEntry(), 0, 100, 0, LOOT_MODE_DEFAULT, 0, 1, 1);
								go->loot.AddItem(storeItem);
								killed->DestroyItemCount(pItem->GetEntry(), pItem->GetCount(), true, false);
								count++;
								break;
							}
						}
					}
				}
			}
		}
	}
};

void AddSC_HighRiskSystems()
{
	new HighRiskSystem();
}
