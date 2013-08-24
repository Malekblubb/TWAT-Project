/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_TOOLS_TW_NET_MASTER_H
#define CORE_TOOLS_TW_NET_MASTER_H


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
		class CMasterList
		{
			std::vector<std::string> m_ips;
			int m_chunkSize;

		public:
			CMasterList();
			std::string operator[](int pos) {return m_ips[pos];}

			void AddAddr(const std::string &ip);
			void AddChunkSize(int size);
			int Size() const {return m_ips.size();}
			int ChunkSize() const {return m_chunkSize;}
		};

		class CMasterRequest
		{
			enum Reqs
			{
				COUNT = 0,
				LIST
			};

			int m_sock;
			std::vector<System::CIpAddr *> m_addrs;
			System::CIpAddr *m_addr;

		public:
			CMasterRequest();
			~CMasterRequest();

			void AddServer(const std::string &addr);
			void ClearServers();

			int PullCount();
			bool PullList(CMasterList *lst);
		};
	}
}

#endif // CORE_TOOLS_TW_NET_MASTER_H
