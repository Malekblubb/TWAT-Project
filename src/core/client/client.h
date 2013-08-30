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

		static CClient *CreateClient() {return new CClient();}


		class CComponentCore *m_core;
		class IConfig *m_config;
		class ITwServerBrowser *m_twServerBrowser;

		class CComponentCore *Core() {return m_core;}
		class IConfig *Config() {return m_config;}
		class ITwServerBrowser *ServerBrowser() {return m_twServerBrowser;}

	private:
		void SetupComponents();
		void InitComponents();
	};
}

#endif // CORE_CLIENT_CLIENT_H
