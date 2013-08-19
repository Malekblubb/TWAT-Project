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

	class CNetworkPacket
	{
	public:
		NetworkPacketLabel m_label;
		unsigned char *m_data;

		CNetworkPacket(System::CIpAddr *addr, void *data, int dataLen, int flags = PKFLAG_CONNLESS);
		CNetworkPacket(int dataLen); // setup for recv
		~CNetworkPacket();

		void MakeConnless();
		void AddData(unsigned char *data, int dataLen);
	};

	class CNetworkBase
	{
	public:
		static void MakeConnless(CNetworkPacket *pk);

		static ssize_t Send(int sock, CNetworkPacket *pk);
		static ssize_t Recv(int sock, CNetworkPacket *pk, System::CIpAddr *fromAddr = 0);
		static ssize_t RecvRaw(int sock, unsigned char *data, int dataLen, System::CIpAddr *fromAddr = 0);
	};
}


#endif // NETWORK_H
