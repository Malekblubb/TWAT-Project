/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "client.h"

#include "../base/app_info.h"
#include <iostream>


TWAT::CClient::CClient()
{

}

void TWAT::CClient::Init()
{
	// start log
	System::DbgLine("%: TWAT version % started. Timestamp: %", FUNC, APP_VERSION, System::TimeStr());


	m_Config = new CConfig(APP_CONF_PATH);
	m_Config->Init();
}
