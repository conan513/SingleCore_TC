#ifndef CUSTOMSPELLSYSTEM_H
#define CUSTOMSPELLSYSTEM_H

class CustomSpellSystem
{
public:
	CustomSpellSystem();
	static CustomSpellSystem* instance();
	void LoadFromDB();

	bool isSpellPartOfSystem(uint32 spell);
	int getMaxSpells();

private:
	std::unordered_set<uint32> m_SpellsContainer; // spellid, percentage
	int m_maxSpells;
};

#define sCustomSpellSystem CustomSpellSystem::instance()

class CustomSpellSystemLoader : public WorldScript
{
public:
	CustomSpellSystemLoader() : WorldScript("CustomSpellSystemLoader") {}

	void OnStartup() override
	{
		sCustomSpellSystem->LoadFromDB();
	}
};

#endif