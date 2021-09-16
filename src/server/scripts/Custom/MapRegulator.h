#include "DatabaseEnv.h"
#include "Log.h"

#ifndef MAP_REGULATOR_H
#define MAP_REGULATOR_H

struct MapRegulatorStruct
{
	uint32 mapId;
	float dmgPercentage;
	float hpPercentage;
	float spelldmgPercentage;
};

class MapRegulator
{
public:
	static MapRegulator* instance()
	{
		static MapRegulator instance;
		return &instance;
	}

	void RegulateDamage(uint32& damage, uint32 mapId)
	{
		if (RegulatorContainer.find(mapId) == RegulatorContainer.end())
			return;

		float val = RegulatorContainer[mapId]->dmgPercentage;

		Regulate(damage, val);
	}

	void RegulateSpellDamage(uint32& damage, uint32 mapId) { 
		if (RegulatorContainer.find(mapId) == RegulatorContainer.end())
			return;

		float val = RegulatorContainer[mapId]->spelldmgPercentage;

		Regulate(damage, val);
	}

	void RegulateHealth(uint32& health, uint32 mapId)
	{
		if (RegulatorContainer.find(mapId) == RegulatorContainer.end())
			return;

		float val = RegulatorContainer[mapId]->hpPercentage;

		Regulate(health, val);
	}

	void Regulate(uint32& number, uint32 val)
	{
		if (!val || val == 100.0f)
			return;

		number = (number / 100.0f) * val;
	}

	void LoadFromDB()
	{
		RegulatorContainer.clear();
		uint32 msTime = getMSTime();
		QueryResult result = WorldDatabase.Query("SELECT * FROM mapregulator");

		if (!result)
			return;

		uint32 count = 0;
		do{
			Field* fields = result->Fetch();
			MapRegulatorStruct* mapstruct = new MapRegulatorStruct();
			mapstruct->mapId = fields[0].GetUInt32();
			mapstruct->dmgPercentage = fields[1].GetFloat();
			mapstruct->hpPercentage = fields[2].GetFloat();
			mapstruct->spelldmgPercentage = fields[3].GetFloat();
			RegulatorContainer[fields[0].GetUInt32()] = mapstruct;
			++count;
		} while (result->NextRow());
		TC_LOG_INFO("server.loading", "Loaded %u regulated map creatures in %u ms", count, GetMSTimeDiffToNow(msTime));
	}

private:
	std::unordered_map<uint32, MapRegulatorStruct*> RegulatorContainer; // spellid, percentage
};

#define sMapRegulator MapRegulator::instance()

class MapRegulatorLoader : public WorldScript
{
public:
	MapRegulatorLoader() : WorldScript("MapRegulatorLoader") {}

	void OnStartup() override
	{
		sMapRegulator->LoadFromDB();
	}
};

#endif

/*
CREATE TABLE IF NOT EXISTS `MapRegulator` (
`mapId` int(11) unsigned NOT NULL,
`dmgPercentage` float NOT NULL DEFAULT '100',
`hpPercentage` float NOT NULL DEFAULT '100',
`spelldmgPercentage` float NOT NULL DEFAULT '100',
PRIMARY KEY (`mapId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

*/
