/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_CLIENT_H
#define CORE_CLIENT_H


#include <core/shared/config.h>


namespace TWAT
{
	class CClient
	{
	public:
		CClient();
		CConfig *m_config;

	public:
		void Init();


	};
}

#endif // CLIENT_H
