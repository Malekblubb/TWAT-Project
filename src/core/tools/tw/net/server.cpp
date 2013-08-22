/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "server.h"

#include "info_decoder.h"
#include "pk_requests.h"

#include <base/system.h>

#include <core/shared/network.h>

#include <cstring>


TWAT::TwTools::CServerSniffer::CServerSniffer()
{
	m_sock = System::UdpSock();
	m_addr = new System::CIpAddr();
	m_recData = (unsigned char *)std::malloc(1024);
	m_token = 5; // random
}

bool TWAT::TwTools::CServerSniffer::Connect(const std::string &addr)
{
	m_addr->SetNewAddr(addr);

	if(m_sock < 0)
		return false;

	if(!m_addr->IsSet())
		return false;

	return true;
}

bool TWAT::TwTools::CServerSniffer::PullInfo(ServerInfo *inf)
{
	if(!this->SendReq()) // refresh
		return false;

	if(!CRawInfoDecoder::DecodeServerInfo(m_recData, m_recLen, m_token, inf))
	{
		DBG("error while decode recved serverinfo from: %", System::IpAddrToStr(m_addr));
		return false;
	}

	// non decode stuff
	inf->m_addr = System::IpAddrToStr(m_addr);
	inf->m_latency = m_latency;

	return true;
}

bool TWAT::TwTools::CServerSniffer::SendReq()
{
	long long start = 0, end = 0;
	m_latency = 999;

	std::memset(m_recData, 0, 1024);

	CNetworkPacket *sPk = new CNetworkPacket(m_addr, (void *)SERVERBROWSE_GETINFO, sizeof SERVERBROWSE_GETINFO);
	sPk->MakeConnless();
	sPk->AddData(&m_token, 1); // add token

	// send, recv, ping
	start = System::TimeStamp();
	CNetworkBase::Send(m_sock, sPk);
	m_recLen = CNetworkBase::RecvRaw(m_sock, m_recData, 1024, m_addr);
	end = System::TimeStamp();
	m_latency = (end - start) / 1000;

	// TODO: check valid recved pk here
	return true;
}

TWAT::TwTools::CServerSniffer::~CServerSniffer()
{
	std::free(m_recData);
	System::SockClose(m_sock);
}
