/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_CLIENT_H
#define CORE_CLIENT_H


namespace TWAT
{
	class CClient
	{
	public:
		CClient();
		class CConfig *m_config;

	public:
		void Init();
	};
}

#endif // CLIENT_H
