/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_CLIENT_SERVERLIST_H
#define CORE_CLIENT_SERVERLIST_H


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
		TwTools::CMasterList *m_ipList;
		std::vector<TwTools::ServerInfo> m_serverList;

		int m_numServers;
		bool m_useDefaultMasters;


	public:
		CTwServerBrowser();

		// direct read access to m_serverList at index pos
		TwTools::ServerInfo *operator[](int pos){return &m_serverList[pos];}
		int NumServers() const {return m_numServers;}

		void AddMaster(const std::string &ip);
		void UseDefaultMasters(bool b);
		void RefreshList();

	private:
		void ClearAllMasters();

	};
}

#endif // CORE_CLIENT_SERVERLIST_H
