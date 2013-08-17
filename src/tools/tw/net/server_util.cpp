/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "server_util.h"

#include "info_decoder.h"
#include "pk_requests.h"
#include <base/system.h>
#include <core/shared/network.h>

#include <cstring>


bool TWAT::TwTools::CServerSniffer::Connect(const std::string &addr)
{
	m_sock = System::UdpSock();
	m_addr = new System::CIpAddr(addr);
	m_recData = (unsigned char *)std::malloc(1024);

	if(m_sock < 0)
		return false;

	if(!m_addr->IsSet())
		return false;

	return true;
}

bool TWAT::TwTools::CServerSniffer::PullInfo(ServerInfo *inf)
{
	this->SendReq(); // refresh
	return CRawInfoDecoder::DecodeServerInfo(m_recData, m_recLen, inf);
}

void TWAT::TwTools::CServerSniffer::SendReq()
{
	std::memset(m_recData, 0, 1024);

	NetworkPacket *sPk = new NetworkPacket(m_addr, (void *)SERVERBROWSE_GETINFO, 9);
	CNetworkBase::MakeConnless(sPk);
	CNetworkBase::Send(m_sock, sPk);
	m_recLen = CNetworkBase::RecvRaw(m_sock, m_recData, 1024);
}

TWAT::TwTools::CServerSniffer::~CServerSniffer()
{
	std::free(m_recData);
}
