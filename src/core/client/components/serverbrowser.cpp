/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "serverbrowser.h"

#include <base/system.h>

#include <core/tools/tw/net/master.h>
#include <core/tools/tw/net/server.h>


TWAT::CTwServerBrowser::CTwServerBrowser()
{
	m_masterReq = new TwTools::CMasterRequest();

	m_numServers = 0;
	m_useDefaultMasters = false;
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

void TWAT::CTwServerBrowser::ClearAllMasters()
{
	m_masterReq->ClearServers();
}

void TWAT::CTwServerBrowser::RefreshList()
{
	TwTools::CMasterList masterList;
	TwTools::CServerSniffer sniffer;
	long long start = 0, end = 0;

	start = System::TimeStamp();

	m_refreshing = true;
	m_expCount = m_masterReq->PullCount();
	m_masterReq->PullList(&masterList);
	m_serverList.clear();
	m_numServers = 0;
	m_serverList.resize(m_expCount);

	for(int i = 0; i < masterList.Size(); ++i)
	{
		sniffer.Connect(masterList[i]);
		if(sniffer.PullInfo(&m_serverList[i]))
			++m_numServers;
	}

	end = System::TimeStamp();
	m_refreshTime = (end - start) / (long long)1000000;
	m_refreshing = false;
}
