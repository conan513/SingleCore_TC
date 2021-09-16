#include "DatabaseEnv.h"
#include "Log.h"

#ifndef MOB_REGULATOR_H
#define MOB_REGULATOR_H

class MobRegulator
{
public:
	static MobRegulator* instance()
	{
		static MobRegulator instance;
		return &instance;
	}

	void RegulateDamage(uint32& damage, uint32 creatureTemplateEntry)
	{
		if (RegulatorContainer.find(creatureTemplateEntry) == RegulatorContainer.end())
			return;

		float val = RegulatorContainer[creatureTemplateEntry];

		if (!val || val == 100.0f)
			return;

		damage = (damage / 100.0f) * val;
	}

	void LoadFromDB()
	{
		RegulatorContainer.clear();
		uint32 msTime = getMSTime();
		QueryResult result = WorldDatabase.Query("SELECT * FROM mobregulator");

		if (!result)
			return;

		uint32 count = 0;
		do{
			Field* fields = result->Fetch();
			RegulatorContainer[fields[0].GetUInt32()] = fields[1].GetFloat();
			++count;
		} while (result->NextRow());
		TC_LOG_INFO("server.loading", "Loaded %u regulated creatures in %u ms", count, GetMSTimeDiffToNow(msTime));
	}

private:
	std::unordered_map<uint32, float> RegulatorContainer; // spellid, percentage
};

#define sMobRegulator MobRegulator::instance()

class MobRegulatorLoader : public WorldScript
{
public:
	MobRegulatorLoader() : WorldScript("MobRegulatorLoader") {}

	void OnStartup() override
	{
		sMobRegulator->LoadFromDB();
	}
};

#endif

/*
CREATE TABLE IF NOT EXISTS `mobregulator` (
`mobId` int(11) unsigned NOT NULL,
`dmgPercentage` float NOT NULL DEFAULT '100',
PRIMARY KEY (`mobId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

*/
