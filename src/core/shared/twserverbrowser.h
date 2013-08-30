/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_TWSERVERBROWSER_H
#define CORE_SHARED_TWSERVERBROWSER_H


#include <core/twserverbrowser.h>

#include <string>
#include <vector>


namespace TWAT
{
	namespace TwTools
	{
		class CMasterRequest;
		class CServerSniffer;
		struct ServerInfo;
	}


	class CTwServerBrowser : public ITwServerBrowser
	{
		TwTools::CServerSniffer *m_srvSniffer;
		TwTools::CMasterRequest *m_masterReq;
		std::vector<TwTools::ServerInfo> m_serverList;

		int m_expCount; // expected count from masterserver
		int m_numServers; // num "real" servers
		int m_percentage;
		bool m_useDefaultMasters;
		bool m_refreshing;
		bool m_finishedSrv;
		long long m_refreshTime;


	public:
		CTwServerBrowser();

		// direct read access to m_serverList at index pos
		TwTools::ServerInfo *At(int pos) {return &m_serverList[pos];}

		int ExpCount() const {return m_expCount;}
		int NumServers() const {return m_numServers;}
		int PercentageFinished() const {return m_percentage;}
		int RefreshTime() const {return m_refreshTime;}
		bool IsRefreshing() const {return m_refreshing;}

		void AddMaster(const std::string &ip);
		void UseDefaultMasters(bool b);

		void Refresh();

	private:
		void ClearAllMasters();
		void CalcPercentage();
	};
}

#endif // CORE_SHARED_TWSERVERBROWSER_H
