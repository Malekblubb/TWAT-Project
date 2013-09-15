/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "twserverbrowser.h"

#include <core/tools/tw/net/master.h>
#include <core/tools/tw/net/server.h>


TWAT::CTwServerBrowser::CTwServerBrowser() :
	m_srvSniffer(new TwTools::CServerSniffer),
	m_masterReq(new TwTools::CMasterRequest),
	m_masterList(new TwTools::CMasterList),
	m_numServers(0),
	m_useDefaultMasters(false),
	m_refreshing(false)
{

}

TWAT::CTwServerBrowser::~CTwServerBrowser()
{
	delete m_srvSniffer;
	delete m_masterReq;
	delete m_masterList;
}

void TWAT::CTwServerBrowser::AddMaster(const std::string &ip)
{
	if(m_useDefaultMasters)
		this->ClearAllMasters();

	m_masterReq->AddServer(ip);
	m_useDefaultMasters = false;
}

void TWAT::CTwServerBrowser::UseDefaultMasters(bool b)
{
	if(!m_useDefaultMasters)
	{
		if(b)
		{
			// set default master servers
			this->ClearAllMasters();

			m_masterReq->AddServer("master1.teeworlds.com:8300");
			m_masterReq->AddServer("master2.teeworlds.com:8300");
			m_masterReq->AddServer("master3.teeworlds.com:8300");
			m_masterReq->AddServer("master4.teeworlds.com:8300");

			m_useDefaultMasters = true;
		}
	}
}

int TWAT::CTwServerBrowser::Refresh()
{
	m_refreshing = true;

	if(m_numSent >= m_expCount)
	{
		if(this->ProcessIncomming() <= 0) // last check before end
			m_refreshing = false;
	}
	else
	{

		if(m_numSent <= m_expCount)
		{
			m_srvSniffer->Connect((*m_masterList)[m_numSent]);
			m_srvSniffer->SendReq();
			++m_numSent;
		}
	}

	this->CalcPercentage();
	return this->ProcessIncomming();
}

void TWAT::CTwServerBrowser::RefreshMasterList()
{
	// reset all
	m_numServers = 0;
	m_numSent = 0;

	// master
	m_masterList->Clear();
	m_masterReq->PullList(m_masterList);
	m_expCount = m_masterList->Size();

	// server
	m_serverList.clear();

	// sniffer buffer
	m_srvSniffer->ClearServerBuffer();
}

int TWAT::CTwServerBrowser::ProcessIncomming()
{
	int num = m_srvSniffer->ProcessIncomming(&m_serverList);
	m_numServers += num;

	return num;
}

void TWAT::CTwServerBrowser::ClearAllMasters()
{
	m_masterReq->ClearServers();
}

void TWAT::CTwServerBrowser::CalcPercentage()
{
	m_percentage = (m_numServers / (float)m_expCount) * 100;
}
