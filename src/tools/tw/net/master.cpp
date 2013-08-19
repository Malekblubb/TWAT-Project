/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */


#include "master.h"

#include "info_decoder.h"
#include "pk_requests.h"

#include <base/system.h>

#include <core/shared/network.h>

#include <cstring>


void TWAT::TwTools::CMasterList::AddAddr(const std::string &ip)
{
	m_ips.push_back(ip);
}

TWAT::TwTools::CMasterRequest::CMasterRequest()
{
	m_sock = System::UdpSock();
}

TWAT::TwTools::CMasterRequest::~CMasterRequest()
{
	System::SockClose(m_sock);
}

void TWAT::TwTools::CMasterRequest::AddServer(const std::string &addr)
{
	System::CIpAddr *tmpAddr = new System::CIpAddr(addr);
	m_addrs.push_back(tmpAddr);
}

int TWAT::TwTools::CMasterRequest::PullCount()
{
	int count = 0;
	int gotLen = 0;
	unsigned char *recData = (unsigned char *)std::malloc(1024);

	for(std::vector<System::CIpAddr *>::iterator i = m_addrs.begin(); i != m_addrs.end(); ++i)
	{
		std::memset(recData, 0, 1024);

		if((gotLen = this->SendReq(*i, COUNT, recData)) > 0)
		{
			// TODO: CHECK PK

			int tmpCount = CRawInfoDecoder::DecodeCountInfo(recData, gotLen);

			if(tmpCount != -1)
				count += tmpCount;
			else
				DBG("error while decode recved count data from: %", System::IpAddrToStr(*i));
		}
		else
			DBG("error while connect to master: %", System::IpAddrToStr(*i));
	}

	std::free(recData);
	return count;
}

bool TWAT::TwTools::CMasterRequest::PullList(CMasterList *lst)
{
	int gotLen = 0;
	unsigned char *recData = (unsigned char *)std::malloc(2048); // moa space

	for(std::vector<System::CIpAddr *>::iterator i = m_addrs.begin(); i != m_addrs.end(); ++i)
	{
		std::memset(recData, 0, 2048);

		if((gotLen = this->SendReq(*i, LIST, recData)) > 0)
		{
			if(!CRawInfoDecoder::DecodeListInfo(recData, gotLen, lst))
				DBG("error while decode recved list data from: %", System::IpAddrToStr(*i));
		}
		else
			DBG("error while connect to master: %", System::IpAddrToStr(*i));
	}

	std::free(recData);
	return true;
}

int TWAT::TwTools::CMasterRequest::SendReq(System::CIpAddr *addr, int req, unsigned char *data)
{
	CNetworkPacket *pk;
	int bufLen = 0;

	switch(req)
	{
	case COUNT:
		pk = new CNetworkPacket(addr, (char *)SERVERBROWSE_GETCOUNT, 8);
		bufLen = 1024;
		break;
	case LIST:
		pk = new CNetworkPacket(addr, (char *)SERVERBROWSE_GETLIST, 8);
		bufLen = 2048;
		break;
	default: return -1;
		break;
	}

//	CNetworkBase::MakeConnless(pk);
	pk->MakeConnless();
	CNetworkBase::Send(m_sock, pk);
	return CNetworkBase::RecvRaw(m_sock, data, bufLen);
}
