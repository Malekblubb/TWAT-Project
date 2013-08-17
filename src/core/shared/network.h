/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_NETWORK_H
#define CORE_SHARED_NETWORK_H


#include <string>


namespace TWAT
{
	namespace System
	{
		class CIpAddr;
	}

	enum
	{
		PKFLAG_CONNLESS = 1
	};

	struct NetworkPacketLabel
	{
		System::CIpAddr *m_addr;
		int m_flags;
		int m_dataSize;
	};

	struct NetworkPacket
	{
		NetworkPacketLabel m_label;
		void *m_data;

		NetworkPacket(System::CIpAddr *addr, void *data, int dataLen, int flags = PKFLAG_CONNLESS);
		NetworkPacket(int dataLen); // setup for recv
		~NetworkPacket();
	};

	class CNetworkBase
	{
	public:
		static void MakeConnless(NetworkPacket *pk);

		static ssize_t Send(int sock, NetworkPacket *pk);
		static ssize_t Recv(int sock, NetworkPacket *pk, System::CIpAddr *fromAddr = 0);
		static ssize_t RecvRaw(int sock, unsigned char *data, int dataLen, System::CIpAddr *fromAddr = 0);
	};
}


#endif // NETWORK_H
