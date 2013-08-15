/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "network.h"

#include <cstring>


TWAT::NetworkPacket::NetworkPacket(System::Ip4Addr *addr, void *data, int dataLen, int flags)
{
	// setup infolabel
	if(flags&PKFLAG_CONNLESS)
	{
		this->m_label.m_dataSize = dataLen + 6; // add space for connless-header
		this->m_label.m_flags |= PKFLAG_CONNLESS;
	}
	else
		this->m_label.m_dataSize = dataLen;

	this->m_label.m_addr = addr;

	// copy data
	this->m_data = std::malloc(this->m_label.m_dataSize);
	std::memcpy(m_data, data, dataLen);
}

TWAT::NetworkPacket::NetworkPacket(int dataLen)
{
	this->m_data = std::malloc(dataLen);
	this->m_label.m_dataSize = dataLen;
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

void TWAT::CNetworkBase::SendConnless(int sock, NetworkPacket *pk)
{
	System::UdpSend(sock, (unsigned char *)pk->m_data, pk->m_label.m_dataSize, pk->m_label.m_addr);
}

ssize_t TWAT::CNetworkBase::Send(int sock, NetworkPacket *pk)
{

}

ssize_t TWAT::CNetworkBase::Recv(int sock, NetworkPacket *pk)
{
	return System::UdpRecv(sock, (unsigned char *)pk->m_data, pk->m_label.m_dataSize);
}
