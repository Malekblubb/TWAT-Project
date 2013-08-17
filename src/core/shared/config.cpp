/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "config.h"

#include "io_file.h"
#include <base/system.h>


TWAT::CConfig::CConfig(const std::string &configPath)
{
	m_path = configPath;
	m_confFile = new CIOFile(m_path, READ);
}

void TWAT::CConfig::Init()
{
	// setup the default map
	FillDefault();

	// check if config exists
	if(!CreateConfig())
	{
		// write default content to config
		WriteDefault();
	}

	// read configfile
	ReadFull();
}

void TWAT::CConfig::Save()
{
	std::string buf;

	m_conf.GetList(&buf);

	m_confFile->Open(m_path, NEW);
	m_confFile->Write(buf, OVERWRITE);
	m_confFile->Close();
}

bool TWAT::CConfig::CreateConfig()
{
	if(!m_confFile->Exists())
	{
		DBG("creating default config file");

		m_confFile->Create();
		m_confFile->Close();
		return false;
	}

	DBG("config file found");
	m_confFile->Close();
	return true;
}

void TWAT::CConfig::ReadFull()
{
	std::string buf;

	m_confFile->Open(m_path, READ);

	while(m_confFile->ReadLine(&buf))
	{
		if(!buf.empty())
			m_conf.SetVar<std::string>(this->GetVarFromLine(buf), this->GetValFromLine(buf));
	}

	m_confFile->Close();
}

void TWAT::CConfig::FillDefault()
{
	// set default values
	m_default.SetVar<int>("app_language", 0);

	m_default.SetVar<int>("gra_maximized", 0);
	m_default.SetVar<int>("gra_fullscreen", 0);

	m_default.SetVar<int>("ntw_check_for_updates", 1);
	m_default.SetVar<int>("ntw_auto_refresh_translations", 1);

	m_default.SetVar<int>("ui_menu_expanded", 1);
}

void TWAT::CConfig::WriteDefault()
{
	std::string buf;

	m_default.GetList(&buf);

	m_confFile->Open(m_path, WRITE);
	m_confFile->Write(buf, OVERWRITE);
	m_confFile->Close();
}

std::string TWAT::CConfig::GetVarFromLine(const std::string &line) const
{
	int space = line.find(" ");

	if(space != -1)
		return line.substr(0, space);

	return "INVALID";
}

std::string TWAT::CConfig::GetValFromLine(const std::string &line) const
{
	int space = line.find(" ");
	int length = line.length();

	// TODO: check if value is a digit
	if(space != -1)
		return line.substr(space + 1, length - space - 1);

	return "-1";
}
