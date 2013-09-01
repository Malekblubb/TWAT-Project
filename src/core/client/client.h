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

	private:
		class CComponentCore *m_core;
		class IConfig *m_config;
		class ITwServerBrowser *m_twServerBrowser;
		class ITwServerTester *m_twServerTester;

	public:
		class CComponentCore *Core() const {return m_core;}
		class IConfig *Config() const {return m_config;}
		class ITwServerBrowser *TwServerBrowser() const {return m_twServerBrowser;}
		class ITwServerTester *TwServerTester() const {return m_twServerTester;}

	private:
		void SetupComponents();
		void InitComponents();
	};
}

#endif // CORE_CLIENT_CLIENT_H
