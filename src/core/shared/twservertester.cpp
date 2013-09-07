/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "twservertester.h"

#include <core/tools/tw/net/server.h>



TWAT::CTwServerTester::CTwServerTester()
{
	m_srvSniffer = new TwTools::CServerSniffer();
	m_srvInfo = new TwTools::ServerInfo();
}

bool TWAT::CTwServerTester::Reset(const std::string &addr)
{
	m_sentPks = 0;
	m_lostPks = 0;
	m_latency = 999;
	m_fullSentLen = 0;
	m_fullRecLen = 0;
	m_currentPkLost = false;

	if(m_srvSniffer->Connect(addr))
		return m_srvSniffer->PullInfo(m_srvInfo); // pull info only one time

	return false;
}

int TWAT::CTwServerTester::Ping()
{
	m_currentPkLost = false;

	// latency
	if((m_latency = m_srvSniffer->TestLatency()) >= 500)
	{
		// no lost, but unplayable

		++m_lostPks;
		m_currentPkLost = true;
	}
	++m_sentPks;

	// datalen
	if(m_latency != 999)
		m_fullRecLen += m_srvSniffer->RecLen();
	m_fullSentLen += m_srvSniffer->SentLen();

	return m_latency;
}

int TWAT::CTwServerTester::CurrentSentDataLen() const
{
	return m_srvSniffer->SentLen();
}

int TWAT::CTwServerTester::CurrentRecDataLen() const
{
	return m_srvSniffer->RecLen();
}
