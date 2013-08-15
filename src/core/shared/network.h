/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include <base/system.h>


#ifndef NETWORK_H
#define NETWORK_H


namespace TWAT
{
	enum
	{
		PKFLAG_CONNLESS = 1
	};

	struct NetworkPacketLabel
	{
		System::Ip4Addr *m_addr;
		int m_flags;
		int m_dataSize;
	};

	struct NetworkPacket
	{
		NetworkPacketLabel m_label;
		void *m_data;

		NetworkPacket(System::Ip4Addr *addr, void *data, int dataLen, int flags = PKFLAG_CONNLESS);
		NetworkPacket(int dataLen); // setup for recv
		~NetworkPacket();
	};

	class CNetworkBase
	{
	public:
		void MakeConnless(NetworkPacket *pk);

		void SendConnless(int sock, NetworkPacket *pk);
		ssize_t Send(int sock, NetworkPacket *pk);
		ssize_t Recv(int sock, NetworkPacket *pk);
	};
}


#endif // NETWORK_H
