/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_CLIENT_CLIENT_H
#define CORE_CLIENT_CLIENT_H


namespace TWAT
{
	class CClient
	{
	public:
		CClient();
		void Init();


		class CConfig *m_config;

		class CCore *m_core;

		class ITwServerBrowser *m_twServerBrowser;


		class CCore *Core() {return m_core;}
		class ITwServerBrowser *ServerBrowser() {return m_twServerBrowser;}

	private:
		void SetupComponents();
	};
}

#endif // CORE_CLIENT_CLIENT_H
