#ifndef ENCOUNTER_GENERATOR_H
#define ENCOUNTER_GENERATOR_H

class EncounterGenerator
{
public:
	static EncounterGenerator* instance()
	{
		static EncounterGenerator instance;
		return &instance;
	};
};

#define sEncounterGenerator EncounterGenerator::instance();

enum EncounterSpell
{
	NAME=5,
	JESUS=2,
};

#endif