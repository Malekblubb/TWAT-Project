/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CLIENT_H
#define CLIENT_H


#include "shared/config.h"
#include "shared/config_vars.h"


namespace TWAT
{
	class CClient
	{
		CConfig *m_Config;

	public:
		CClient();
		void OnInit();


	};
}

#endif // CLIENT_H
