/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef TOOLS_TW_NET_MASTER_H
#define TOOLS_TW_NET_MASTER_H


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
		class CMasterRequest
		{
			enum Reqs
			{
				COUNT = 0,
				LIST
			};

			int m_sock;
			std::vector<System::CIpAddr *> m_addrs;

		public:
			CMasterRequest();

			void AddServer(const std::string &addr);
			int PullCount();
			bool PullList();

		private:
			int SendReq(System::CIpAddr *addr, int req, unsigned char *data);

		};
	}
}

#endif // TOOLS_TW_NET_MASTER_H
