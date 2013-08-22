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
	TwTools::ServerInfo inf;
	int tmpCount = 0;

	tmpCount = m_masterReq->PullCount();
	m_masterReq->PullList(&masterList, tmpCount);
	m_serverList.clear();

	for(int i = 0; i < masterList.Size(); ++i)
	{
		if(sniffer.Connect(masterList[i]))
			if(sniffer.PullInfo(&inf))
				m_serverList.push_back(inf);
	}

	m_numServers = m_serverList.size();
}
