#include "ScriptPCH.h"
#include "CharacterDatabase.h"
#include "QueryResult.h"
#include "Log.h"
#include "DatabaseEnv.h"

#include <thread>
#include <unordered_map>

uint32 max_rank = 10;
uint32 honor_per_rank[] = { 10, 30, 80, 190, 420, 890, 1840, 3770, 7620 };

struct player_honor {
	uint32 kills_today;
	uint32 kills_yesterday;
	uint32 kills_this_week;
	uint32 kills_last_week;
	uint32 kills_lifetime;
	uint32 honor_today;
	uint32 honor_yesterday;
	uint32 honor_this_week;
	uint32 honor_last_week;
	uint32 honor_lifetime;
	uint32 prestige;
	uint32 rank;
};

void AstoriaHonorAddPlayer(Player* plr) {
	CharacterDatabase.PExecute("INSERT INTO character_honor VALUES (%u, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)", plr->GetGUID().GetCounter());
	TC_LOG_INFO("server.worldserver", "[AstoriaHonorSystem]: Adding new entry to character_honor table for player (guid:%u)", plr->GetGUID().GetCounter());
}

void AstoriaHonorLoadPlayer(Player* plr, std::unordered_map<uint32, player_honor>* m) {
	QueryResult res = CharacterDatabase.PQuery("SELECT * FROM character_honor WHERE guid=%u", plr->GetGUID().GetCounter());
	if (!res) {
		TC_LOG_ERROR("server.worldserver", "[AstoriaHonorSystem]: Error querying a player(guid:%u) in character_honor table", plr->GetGUID().GetCounter());
		return;
	}
	Field *f = res->Fetch();
	uint32 kills_today = f[1].GetUInt32();
	uint32 kills_yesterday = f[2].GetUInt32();
	uint32 kills_this_week = f[3].GetUInt32();
	uint32 kills_last_week = f[4].GetUInt32();
	uint32 kills_lifetime = f[5].GetUInt32();
	uint32 honor_today = f[6].GetUInt32();
	uint32 honor_yesterday = f[7].GetUInt32();
	uint32 honor_this_week = f[8].GetUInt32();
	uint32 honor_last_week = f[9].GetUInt32();
	uint32 honor_lifetime = f[10].GetUInt32();
	uint32 prestige = f[11].GetUInt32();
	uint32 rank = f[12].GetUInt32();
	(*m)[plr->GetGUID().GetCounter()] = { kills_today, kills_yesterday, kills_this_week, kills_last_week, kills_lifetime, honor_today, honor_yesterday, honor_this_week, honor_last_week, honor_lifetime, prestige, rank };
	TC_LOG_INFO("server.worldserver", "[AstoriaHonorSystem]: Retrieved information from character_honor table for player (guid:%u)", plr->GetGUID().GetCounter());
}

void AstoriaHonorUpdatePlayer(Player* plr, player_honor* h) {
	CharacterDatabase.PExecute("UPDATE character_honor SET kills_today=%u, kills_yesterday=%u, kills_this_week=%u, kills_last_week=%u, kills_lifetime=%u, honor_today=%u, honor_yesterday=%u, honor_this_week=%u, honor_last_week=%u, honor_lifetime=%u, prestige=%u, rank=%u where guid=%u", h->kills_today, h->kills_yesterday, h->kills_this_week, h->kills_last_week, h->kills_lifetime, h->honor_today, h->honor_yesterday, h->honor_this_week, h->honor_last_week, h->honor_lifetime, h->prestige, h->rank, plr->GetGUID().GetCounter());
	TC_LOG_INFO("server.worldserver", "[AstoriaHonorSystem]: Updated information in character_honor table for player (guid:%u)", plr->GetGUID().GetCounter());
}

class AstoriaHonorSystem : public PlayerScript {
public:
	AstoriaHonorSystem() : PlayerScript("AstoriaHonorSystem") {}
	void OnLogin(Player* plr, bool first) {
		if (first) {
			std::thread(AstoriaHonorAddPlayer, plr).detach();
			this->m_honor[plr->GetGUID().GetCounter()] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
			return;
		}
		std::thread(AstoriaHonorLoadPlayer, plr, &m_honor).detach();
	}
	void OnPVPKill(Player* killer, Player* killed) {
		if (m_honor.find(killer->GetGUID().GetCounter()) == m_honor.end() || m_honor.find(killed->GetGUID().GetCounter()) == m_honor.end()) {
			TC_LOG_ERROR("server.worldserver", "[AstoriaHonorSystem]: Error, at least one player does not have an entry in character_honor table guids:(%u, %u)", killer->GetGUID().GetCounter(), killed->GetGUID().GetCounter());
			TC_LOG_INFO("server.worldserver", "[AstoriaHonorSystem]: %u %s", killer->GetGUID().GetCounter(), m_honor.find(killer->GetGUID().GetCounter()) == m_honor.end() ? "missing" : "found in table");
			TC_LOG_INFO("server.worldserver", "[AstoriaHonorSystem]: %u %s", killed->GetGUID().GetCounter(), m_honor.find(killed->GetGUID().GetCounter()) == m_honor.end() ? "missing" : "found in table");
			return;
		}
		uint32 honor = m_honor[killed->GetGUID().GetCounter()].rank*(m_honor[killed->GetGUID().GetCounter()].rank + 1)/2;
		TC_LOG_INFO("server.worldserver", "Honor gained: guid(%u), %u", killer->GetGUID().GetCounter(), honor);
		m_honor[killer->GetGUID().GetCounter()].honor_lifetime += honor;
		m_honor[killer->GetGUID().GetCounter()].honor_today += honor;
		m_honor[killer->GetGUID().GetCounter()].honor_this_week += honor;
		m_honor[killer->GetGUID().GetCounter()].kills_lifetime++;
		m_honor[killer->GetGUID().GetCounter()].kills_today++;
		m_honor[killer->GetGUID().GetCounter()].kills_this_week++;
		while (m_honor[killer->GetGUID().GetCounter()].honor_lifetime >= m_honor[killer->GetGUID().GetCounter()].prestige*honor_per_rank[max_rank - 1] + honor_per_rank[m_honor[killer->GetGUID().GetCounter()].rank - 1]) {
			if (m_honor[killer->GetGUID().GetCounter()].rank < max_rank)
				m_honor[killer->GetGUID().GetCounter()].rank++;
		}
		std::thread(AstoriaHonorUpdatePlayer, killer, &(m_honor[killer->GetGUID().GetCounter()])).detach();
	}
private:
	std::unordered_map<uint32, player_honor> m_honor;
};

void AddSC_AstoriaHonorSystem() {
	new AstoriaHonorSystem;
}
