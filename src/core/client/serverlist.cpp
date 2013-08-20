/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "serverlist.h"

#include <tools/tw/net/master.h>
#include <tools/tw/net/server.h>

#include <base/system.h>


TWAT::CTwServerBrowser::CTwServerBrowser()
{
	m_masterReq = new TwTools::CMasterRequest();
	m_ipList = new TwTools::CMasterList();

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
	TwTools::CMasterList tmpMasterLst;
	TwTools::CServerSniffer tmpSniffer;


	m_numServers = m_masterReq->PullCount();
	m_masterReq->PullList(&tmpMasterLst, m_numServers);
	m_serverList.resize(tmpMasterLst.Size());

	for(unsigned int i = 0; i < m_serverList.size(); ++i)
	{
		tmpSniffer.Connect(tmpMasterLst[i]);
		tmpSniffer.PullInfo(&m_serverList[i]);
	}
}
