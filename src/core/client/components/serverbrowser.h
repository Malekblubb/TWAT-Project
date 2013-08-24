/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_CLIENT_COMPONENTS_SERVERBROWSER_H
#define CORE_CLIENT_COMPONENTS_SERVERBROWSER_H


#include <string>
#include <vector>


namespace TWAT
{
	namespace TwTools
	{
		class CMasterRequest;
		class CMasterList;
		struct ServerInfo;
	}


	class CTwServerBrowser
	{
		TwTools::CMasterRequest *m_masterReq;
		std::vector<TwTools::ServerInfo> m_serverList;

		int m_expCount; // expected count from masterserver
		int m_numServers; // num "real" servers
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
		int RefreshTime() const {return m_refreshTime;}
		bool IsRefreshing() const {return m_refreshing;}

		void AddMaster(const std::string &ip);
		void UseDefaultMasters(bool b);

		void RefreshList();

	private:
		void ClearAllMasters();

	};
}

#endif // CORE_CLIENT_COMPONENTS_SERVERBROWSER_H
