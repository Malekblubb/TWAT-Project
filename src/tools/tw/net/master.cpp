/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */


#include "master.h"

#include "info_decoder.h"
#include "pk_requests.h"
#include <base/system.h>
#include <core/shared/network.h>


TWAT::TwTools::CMasterRequest::CMasterRequest()
{
	m_sock = System::UdpSock();
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
		if((gotLen = this->SendReq(*i, COUNT, recData)) > 0)
		{
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

bool TWAT::TwTools::CMasterRequest::PullList()
{
	int gotLen = 0;
	unsigned char *recData = (unsigned char *)std::malloc(1024);

	for(std::vector<System::CIpAddr *>::iterator i = m_addrs.begin(); i != m_addrs.end(); ++i)
	{
		if((gotLen = this->SendReq(*i, LIST, recData)) > 0)
		{

		}
		else
			DBG("error while connect to master: %", System::IpAddrToStr(*i));
	}

	std::free(recData);
	return true;
}

int TWAT::TwTools::CMasterRequest::SendReq(System::CIpAddr *addr, int req, unsigned char *data)
{
	NetworkPacket *pk;

	switch(req)
	{
	case COUNT: pk = new NetworkPacket(addr, (void *)SERVERBROWSE_GETCOUNT, 8);
		break;
	case LIST: pk = new NetworkPacket(addr, (void *)SERVERBROWSE_GETLIST, 8);
		break;
	default: return -1;
		break;
	}

	CNetworkBase::MakeConnless(pk);
	CNetworkBase::Send(m_sock, pk);
	return CNetworkBase::RecvRaw(m_sock, data, 1024);
}
