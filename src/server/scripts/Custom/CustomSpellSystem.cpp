#include "CustomSpellSystem.h"
#include "DatabaseEnv.h"
#include "Log.h"

CustomSpellSystem::CustomSpellSystem()
{
	// this needs to be changed probably
	m_maxSpells = 9999999999;
}

CustomSpellSystem* CustomSpellSystem::instance()
{
	static CustomSpellSystem instance;
	return &instance;
}

void CustomSpellSystem::LoadFromDB()
{
	m_SpellsContainer.clear();
	uint32 msTime = getMSTime();
	QueryResult result = WorldDatabase.Query("SELECT spellID FROM custom_spell_system");

	if (!result)
		return;

	uint32 count = 0;
	do {
		Field* fields = result->Fetch();
		m_SpellsContainer.insert(fields[0].GetFloat());
		++count;
	} while (result->NextRow());

	TC_LOG_INFO("server.loading", "Loaded %u spells in %u ms", count, GetMSTimeDiffToNow(msTime));
}

bool CustomSpellSystem::isSpellPartOfSystem(uint32 spell)
{
	return m_SpellsContainer.find(spell) != m_SpellsContainer.end();
}

int CustomSpellSystem::getMaxSpells()
{
	return m_maxSpells;
}

void AddSC_CustomSpellSystem()
{
	new CustomSpellSystemLoader;
};
