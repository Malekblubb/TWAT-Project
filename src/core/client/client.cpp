/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "client.h"

#include <base/app_info.h>

#include <core/component_core.h>
#include <core/config.h>
#include <core/twserverbrowser.h>

#include <core/shared/config.h>
#include <core/shared/twserverbrowser.h>
#include <core/tools/tw/net/server.h>

#include <iostream>
#include <QDir>


TWAT::CClient::CClient()
{

}

void TWAT::CClient::Init()
{
	// start log
	DBG("TWAT version % started. Timestamp: %", APP_VERSION, System::TimeStr());

	// setup config(-path)
	QDir confDir(APP_WORK_PATH.c_str());
	if(!confDir.exists())
		confDir.mkdir(APP_WORK_PATH.c_str());

	// setup components
	this->SetupComponents();

	// some components have an init fnc
	this->InitComponents();
}

void TWAT::CClient::SetupComponents()
{
	// create core instance
	m_core = CComponentCore::CreateComponentCore();

	// register components
	Core()->RegisterComponent<CConfig>("config");
	Core()->RegisterComponent<CTwServerBrowser>("twserverbrowser");

	// request components
	m_config = Core()->RequestComponent<IConfig>();
	m_twServerBrowser = Core()->RequestComponent<ITwServerBrowser>();
}

void TWAT::CClient::InitComponents()
{
	Config()->Init();
}
