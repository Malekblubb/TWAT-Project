/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_TWSERVERBROWSER_H
#define CORE_SHARED_TWSERVERBROWSER_H


#include <core/twserverbrowser.h>

#include <vector>
#include <map>


namespace TWAT
{
	namespace TwTools
	{
		class CMasterRequest;
		class CMasterList;
		class CServerSniffer;
		struct ServerInfo;
	}


	class CTwServerBrowser : public ITwServerBrowser
	{
		TwTools::CServerSniffer *m_srvSniffer;
		TwTools::CMasterRequest *m_masterReq;
		TwTools::CMasterList *m_masterList;
		std::vector<TwTools::ServerInfo> m_serverList;

		int m_expCount; // expected count from masterserver
		int m_numServers; // num "real" servers
		int m_numSent;
		int m_percentage;
		bool m_useDefaultMasters;
		bool m_refreshing;

		long long m_refreshTime;


	public:
		CTwServerBrowser();
		~CTwServerBrowser();

		int Refresh();
		void RefreshMasterList();

		void AddMaster(const std::string &ip);
		void UseDefaultMasters(bool b);

		// direct read access to m_serverList at index pos
		TwTools::ServerInfo *At(int pos) {return &m_serverList[pos];}
		int ExpCount() const {return m_expCount;}
		int NumServers() const {return m_numServers;}
		int PercentageFinished() const {return m_percentage;}
		int RefreshTime() const {return m_refreshTime;}
		bool IsRefreshing() const {return m_refreshing;}


	private:
		int ProcessIncomming();
		void ClearAllMasters();
		void CalcPercentage();
	};
}

#endif // CORE_SHARED_TWSERVERBROWSER_H
