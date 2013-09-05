/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "network.h"
#include <base/system.h>
#include <cstring>


TWAT::CNetworkPacket::CNetworkPacket(System::CIpAddr *addr, void *data, int dataLen, int flags)
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
	m_data = (unsigned char*)std::malloc(m_label.m_dataSize);
	std::memset(m_data, 0, m_label.m_dataSize);
	std::memcpy(m_data, data, dataLen);
}

TWAT::CNetworkPacket::CNetworkPacket(int dataLen)
{
	m_data = (unsigned char *)std::malloc(dataLen);
	m_label.m_dataSize = dataLen;
}

TWAT::CNetworkPacket::~CNetworkPacket()
{
	std::free(m_data);
}

void TWAT::CNetworkPacket::MakeConnless()
{
	// check if packet has connless flag
	if(m_label.m_flags&PKFLAG_CONNLESS)
	{
		// make connless
		unsigned char tmp[m_label.m_dataSize + 6];

		for(int i = 0; i < 6; i++)
			tmp[i] = 0xff;

		std::memcpy(&tmp[6], m_data, m_label.m_dataSize);
		std::memset(m_data, 0, m_label.m_dataSize);
		std::memcpy(m_data, tmp, m_label.m_dataSize);
	}
}

void TWAT::CNetworkPacket::AddData(unsigned char *data, int dataLen)
{
	if(dataLen < 1)
		return;

	unsigned char tmp[m_label.m_dataSize + dataLen];

	std::memcpy(tmp, m_data, m_label.m_dataSize); // copy old data
	std::memcpy(tmp + m_label.m_dataSize, data, dataLen); // add new data at end

	std::memset(m_data, 0, m_label.m_dataSize + dataLen); // clear out member data
	std::memcpy(m_data, tmp, m_label.m_dataSize + dataLen); // set new member data

	// set new len to info-label
	m_label.m_dataSize += dataLen;
}

ssize_t TWAT::CNetworkBase::Send(int sock, CNetworkPacket *pk)
{
	if(pk->m_label.m_flags&PKFLAG_CONNLESS)
		return System::UdpSend(sock, (unsigned char *)pk->m_data, pk->m_label.m_dataSize, pk->m_label.m_addr);

	// TODO: some other send stuff
	return System::UdpSend(sock, (unsigned char *)pk->m_data, pk->m_label.m_dataSize, pk->m_label.m_addr);
}

ssize_t TWAT::CNetworkBase::Recv(int sock, CNetworkPacket *pk, System::CIpAddr *fromAddr)
{
	ssize_t got = System::UdpRecv(sock, (unsigned char *)pk->m_data, pk->m_label.m_dataSize, 0, fromAddr);

	// set new size to pk-label
	pk->m_label.m_dataSize = got;

	return got;
}

ssize_t TWAT::CNetworkBase::RecvRaw(int sock, unsigned char *data, int dataLen, int timeout, System::CIpAddr *fromAddr)
{
	return System::UdpRecv(sock, (unsigned char *)data, dataLen, timeout, fromAddr);
}
