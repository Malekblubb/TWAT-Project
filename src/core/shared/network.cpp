/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "network.h"
#include <base/system.h>
#include <cstring>


TWAT::NetworkPacket::NetworkPacket(System::CIpAddr *addr, void *data, int dataLen, int flags)
{
	// setup infolabel
	if(flags&PKFLAG_CONNLESS)
	{
		m_label.m_dataSize = dataLen + 6; // add space for connless-header
		m_label.m_flags |= PKFLAG_CONNLESS;
	}
	else
		m_label.m_dataSize = dataLen;

	m_label.m_addr = addr;

	// copy data
	m_data = std::malloc(m_label.m_dataSize);
	std::memcpy(m_data, data, dataLen);
}

TWAT::NetworkPacket::NetworkPacket(int dataLen)
{
	m_data = std::malloc(dataLen);
	m_label.m_dataSize = dataLen;
}

TWAT::NetworkPacket::~NetworkPacket()
{
	std::free(m_data);
}


void TWAT::CNetworkBase::MakeConnless(NetworkPacket *pk)
{
	// check if packet has connless flag
	if(pk->m_label.m_flags&PKFLAG_CONNLESS)
	{
		// make connless
		unsigned char tmp[pk->m_label.m_dataSize + 6];

		for(int i = 0; i < 6; i++)
			tmp[i] = 0xff;

		std::memcpy(&tmp[6], pk->m_data, pk->m_label.m_dataSize);
		std::memset(pk->m_data, 0, pk->m_label.m_dataSize);
		std::memcpy(pk->m_data, tmp, pk->m_label.m_dataSize);
	}
}

ssize_t TWAT::CNetworkBase::Send(int sock, NetworkPacket *pk)
{
	if(pk->m_label.m_flags&PKFLAG_CONNLESS)
		return System::UdpSend(sock, (unsigned char *)pk->m_data, pk->m_label.m_dataSize, pk->m_label.m_addr);

	// TODO: some other send stuff
	return System::UdpSend(sock, (unsigned char *)pk->m_data, pk->m_label.m_dataSize, pk->m_label.m_addr);
}

ssize_t TWAT::CNetworkBase::Recv(int sock, NetworkPacket *pk, System::CIpAddr *fromAddr)
{
	ssize_t got = System::UdpRecv(sock, (unsigned char *)pk->m_data, pk->m_label.m_dataSize, fromAddr);

	// set new size to pk-label
	pk->m_label.m_dataSize = got;

	return got;
}

ssize_t TWAT::CNetworkBase::RecvRaw(int sock, unsigned char *data, int dataLen, System::CIpAddr *fromAddr)
{
	return System::UdpRecv(sock, (unsigned char *)data, dataLen, fromAddr);
}
