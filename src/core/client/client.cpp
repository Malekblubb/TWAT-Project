/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "client.h"

#include <base/app_info.h>

#include <core/component_core.h>
#include <core/config.h>
#include <core/twmapextract.h>
#include <core/twserverbrowser.h>
#include <core/twservertester.h>

#include <core/shared/config.h>
#include <core/shared/twmapextract.h>
#include <core/shared/twserverbrowser.h>
#include <core/shared/twservertester.h>

#include <core/tools/tw/net/server.h>

#include <iostream>
#include <QDir>


TWAT::CClient::CClient()
{

}

TWAT::CClient::~CClient()
{
	delete m_core;
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
	Core()->RegisterComponent<CTwMapExtract>("twmapextract");
	Core()->RegisterComponent<CTwServerBrowser>("twserverbrowser");
	Core()->RegisterComponent<CTwServerTester>("twservertester");

	// request components
	m_config = Core()->RequestComponent<IConfig>();
	m_twMapExtract = Core()->RequestComponent<ITwMapExtract>();
	m_twServerBrowser = Core()->RequestComponent<ITwServerBrowser>();
	m_twServerTester = Core()->RequestComponent<ITwServerTester>();
}

void TWAT::CClient::InitComponents()
{
	Config()->Init();
}
