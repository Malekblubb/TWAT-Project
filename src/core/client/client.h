/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_CLIENT_CLIENT_H
#define CORE_CLIENT_CLIENT_H


namespace TWAT
{
	// CClient:
	//		wrapper to access components, etc...

	class CClient
	{
	public:
		CClient();
		class CConfig *m_config;
		class CTwServerBrowser *m_twSrvBrowser;

	public:
		void Init();
	};
}

#endif // CORE_CLIENT_CLIENT_H
