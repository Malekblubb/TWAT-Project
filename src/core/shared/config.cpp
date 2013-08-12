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
	m_confFile->Open(m_path, NEW);

//	for(std::map<std::string, std::string>::iterator i = m_conf.begin(); i != m_conf.end(); i++)
//		if(i->first != "INVALID") // check for an invalid setting
//			m_confFile->Write(i->first + " " + i->second + "\n", APPEND);

	m_confFile->Close();
}

bool TWAT::CConfig::CreateConfig()
{
	if(!m_confFile->Exists())
	{
		System::DbgLine("%: creating default config file", FUNC);

		m_confFile->Create();
		m_confFile->Close();
		return false;
	}

	System::DbgLine("%: config file found", FUNC);
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
		{
			m_conf.SetVar<std::string>(this->GetVar(buf), this->GetVal(buf));
		}
	}

	m_confFile->Close();
}

void TWAT::CConfig::FillDefault()
{
	// set default values
	m_default.SetVar<int>("APP_LANGUAGE", 0);

	m_default.SetVar<int>("GRA_MAXIMIZED", 0);
	m_default.SetVar<int>("GRA_FULLSCREEN", 0);

	m_default.SetVar<int>("NTW_CHECK_FOR_UPDATES", 1);
	m_default.SetVar<int>("NTW_AUTO_REFRESH_TRANSLATIONS", 1);

	m_default.SetVar<int>("UI_MENU_EXPANDED", 1);
}

void TWAT::CConfig::WriteDefault()
{
	m_confFile->Open(m_path, WRITE);

//	for(std::map<std::string, std::string>::iterator i = m_default.begin(); i != m_default.end(); i++)
//		m_confFile->Write(i->first + " " + i->second + "\n", APPEND);

	m_confFile->Close();
}

std::string TWAT::CConfig::GetVar(const std::string &line) const
{
	int space = line.find(" ");

	if(space != -1)
		return line.substr(0, space);

	return "INVALID";
}

int TWAT::CConfig::GetVal(const std::string &line) const
{
	int space = line.find(" ");
	int length = line.length();

	// TODO: check if value is a digit
	if(space != -1)
		return std::stoi(line.substr(space, length - space));

	return std::stoi("-1");
}
