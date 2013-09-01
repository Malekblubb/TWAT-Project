/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_TWSERVERTESTER_H
#define CORE_SHARED_TWSERVERTESTER_H


#include <core/twservertester.h>


namespace TWAT
{
	namespace TwTools
	{
		class CServerSniffer;
		struct ServerInfo;
	}

	class CTwServerTester : public ITwServerTester
	{
		TwTools::CServerSniffer *m_srvSniffer;
		TwTools::ServerInfo *m_srvInfo;
		int m_sentPks;
		int m_lostPks;
		bool m_currentPkLost;
		int m_latency;
		int m_fullSentLen;
		int m_fullRecLen;


	public:
		CTwServerTester();

		bool Reset(const std::string &addr);
		int Ping();

		TwTools::ServerInfo *ServerInfo() const {return m_srvInfo;}
		int NumSentPks() const {return m_sentPks;}
		int NumLostPks() const {return m_lostPks;}
		bool CurrentPkLost() const {return m_currentPkLost;}
		int SentDataLen() const {return m_fullSentLen;}
		int RecDataLen() const {return m_fullRecLen;}
		int CurrentSentDataLen() const;
		int CurrentRecDataLen() const;
	};
}


#endif // CORE_SHARED_TWSERVERTESTER_H
