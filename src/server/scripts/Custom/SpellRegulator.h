#include "DatabaseEnv.h"
#include "Log.h"

#ifndef SPELL_REGULATOR_H
#define SPELL_REGULATOR_H

class SpellRegulator
{
public:
  static SpellRegulator* instance()
  {
    static SpellRegulator instance;
    return &instance;
  }

  void Regulate(uint32& damage, uint32 spellId)
  {
    if (RegulatorContainer.find(spellId) == RegulatorContainer.end())
      return;


    float val = RegulatorContainer[spellId];

    if (!val || val == 100.0f)
      return;

    damage = (damage / 100.0f) * val;
  }

  void LoadFromDB()
  {
    RegulatorContainer.clear();
    uint32 msTime = getMSTime();
    QueryResult result = WorldDatabase.Query("SELECT * FROM spellregulator");

    if (!result)
      return;

    uint32 count = 0;
    do{
      Field* fields = result->Fetch();
      RegulatorContainer[fields[0].GetUInt32()] = fields[1].GetFloat();
      ++count;
    } while (result->NextRow());
    TC_LOG_INFO("server.loading", "Loaded %u regulated spells in %u ms", count, GetMSTimeDiffToNow(msTime));
  }

private:
  std::unordered_map<uint32, float> RegulatorContainer; // spellid, percentage
};

#define sSpellRegulator SpellRegulator::instance()

class RegulatorLoader : public WorldScript
{
public:
  RegulatorLoader() : WorldScript("SpellRegulatorLoader") {}

  void OnStartup() override
  {
    sSpellRegulator->LoadFromDB();
  }
};

#endif
