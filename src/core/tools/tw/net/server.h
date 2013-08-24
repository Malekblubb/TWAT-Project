/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_TOOLS_TW_NET_SERVER_H
#define CORE_TOOLS_TW_NET_SERVER_H


#include <string>
#include <vector>


namespace TWAT
{
	namespace System
	{
		class CIpAddr;
	}

	namespace TwTools
	{
		struct ClientInfo
		{
			std::string m_name;
			std::string m_clan;
			int m_country;
			int m_score;
			bool m_isPlayer;
		};

		struct ServerInfo
		{
			std::vector<ClientInfo> m_clients;

			std::string m_name;
			std::string m_gameType;
			std::string m_mapName;
			std::string m_version;
			std::string m_addr;

			int m_maxClients;
			int m_numClients;
			int m_maxPlayers;
			int m_numPlayers;
			int m_flags;
			int m_latency;
		};

		class CServerSniffer
		{
			int m_sock;
			System::CIpAddr *m_addr;

			int m_recLen;
			unsigned char *m_recData;
			unsigned char m_token; // token must be only one byte
			long long m_latency;

		public:
			CServerSniffer();
			~CServerSniffer();

			void Clear();
			bool Connect(const std::string &addr);
			bool PullInfo(ServerInfo *inf);

		private:
			bool SendReq();
		};
	}
}

#endif // CORE_TOOLS_TW_NET_SERVER_H
