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
	m_addr = new System::CIpAddr("0.0.0.0:0");
	m_sock = System::UdpSock(m_addr);
	m_recData = (unsigned char *)std::malloc(1024);
	m_token = 5; // random
}

TWAT::TwTools::CServerSniffer::~CServerSniffer()
{
	std::free(m_recData);
	System::SockClose(m_sock);
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

	this->RecvReq();

	// add non decode stuff
	inf->m_addr = System::IpAddrToStr(m_addr);
	inf->m_latency = m_latency;

	if(!CRawInfoDecoder::DecodeServerInfo(m_recData, m_recLen, m_token, inf))
		return false;

	return true;
}

int TWAT::TwTools::CServerSniffer::TestLatency()
{
	long long start = System::TimeStamp();

	if(!this->SendReq())
		return 999;

	this->RecvReq();

	return (System::TimeStamp() - start) *1000/1000000;
}

bool TWAT::TwTools::CServerSniffer::SendReq()
{
	std::memset(m_recData, 0, 1024);

	CNetworkPacket *sPk = new CNetworkPacket(m_addr, (void *)SERVERBROWSE_GETINFO, sizeof SERVERBROWSE_GETINFO);
	sPk->MakeConnless();
	sPk->AddData(&m_token, 1); // add token

	// send
	m_sentLen = CNetworkBase::Send(m_sock, sPk);

	ServerInfo tmpInfo;
	tmpInfo.m_sentTime = System::TimeStamp();
	m_servers[System::IpAddrToStr(m_addr)] = tmpInfo;

	return true;
}

void TWAT::TwTools::CServerSniffer::RecvReq()
{
	m_recLen = CNetworkBase::RecvRaw(m_sock, m_recData, 1024, 900000);
}

int TWAT::TwTools::CServerSniffer::ProcessIncomming(std::vector<ServerInfo> *buf)
{
	int i = 0;
	while(1)
	{
		unsigned char data[1024];
		System::CIpAddr *from = new System::CIpAddr();
		ssize_t got = CNetworkBase::RecvRaw(m_sock, data, 1024, 5000, from);

		if(got <= 0)
			break;

		ServerInfo inf;
		if(!CRawInfoDecoder::DecodeServerInfo(data, got, m_token, &inf))
			continue;


		inf.m_sentTime = m_servers[System::IpAddrToStr(from)].m_sentTime;
		inf.m_latency = (System::TimeStamp() - inf.m_sentTime)*1000/1000000;
		inf.m_addr = System::IpAddrToStr(from);
		buf->push_back(inf);

		++i;
	}

	return i;
}
