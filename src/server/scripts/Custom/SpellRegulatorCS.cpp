#include "ScriptPCH.h"
#include "SpellRegulator.h"
#include "Chat.h"

class spellregulatorcs : public CommandScript
{
public:
	spellregulatorcs() : CommandScript("spellregulatorcs") {}

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> SRCommandTable =
        {
			{"reloadsr", rbac::RBAC_PERM_COMMAND_RELOAD, true, &HandleReloadSR, "" }
		};
		return SRCommandTable;
	}

	static bool HandleReloadSR(ChatHandler* handler, char const* args)
	{
		sSpellRegulator->LoadFromDB();
		return true;
	}
};

void AddSC_spellregulatorcs()
{
	new spellregulatorcs();
}
