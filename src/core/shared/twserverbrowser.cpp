/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "twserverbrowser.h"

#include <base/system.h>

#include <core/tools/tw/net/master.h>
#include <core/tools/tw/net/server.h>


TWAT::CTwServerBrowser::CTwServerBrowser()
{
	m_srvSniffer = new TwTools::CServerSniffer();
	m_masterReq = new TwTools::CMasterRequest();
	m_masterList = new TwTools::CMasterList();

	m_numServers = 0;
	m_useDefaultMasters = false;
	m_refreshing = false;
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

bool TWAT::CTwServerBrowser::Refresh()
{
	if(m_numServers == m_expCount)
		return false;

	m_srvSniffer->Connect((*m_masterList)[m_numServers]);
	m_srvSniffer->PullInfo(&m_serverList[m_numServers]);
	++m_numServers;

	this->CalcPercentage();

	return true;
}

void TWAT::CTwServerBrowser::RefreshMasterList()
{
	// reset all
	m_numServers = 0;

	// master
	m_masterList->Clear();
	m_masterReq->PullList(m_masterList);
	m_expCount = m_masterList->Size();

	// server
	m_serverList.clear();
	m_serverList.resize(m_expCount);
}

void TWAT::CTwServerBrowser::ClearAllMasters()
{
	m_masterReq->ClearServers();
}

void TWAT::CTwServerBrowser::CalcPercentage()
{
	m_percentage = (m_numServers / (float)m_expCount) * 100;
}
