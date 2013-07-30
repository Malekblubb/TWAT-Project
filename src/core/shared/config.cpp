/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "config.h"

#include "io_file.h"
#include "../../base/system.h"
#include <vector>


TWAT::CConfig::CConfig(const std::string &configPath)
{
	m_Path = configPath;
	m_ConfFile = new CIOFile(m_Path, READ);
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

bool TWAT::CConfig::Save()
{
	std::vector<std::string> tmpVec;

	m_ConfFile->Open(m_Path, NEW);
	for(std::map<std::string, int>::iterator i = m_Conf.begin(); i != m_Conf.end(); i++)
	{
		tmpVec.push_back(i->first);
		m_ConfFile->Write(i->first + " " + std::to_string(m_Conf[i->first]) + "\n", APPEND);
	}

	m_ConfFile->Close();
}

bool TWAT::CConfig::CreateConfig()
{
	if(!m_ConfFile->Exists())
	{
		System::DbgLine("%: creating default config file", FUNC);

		m_ConfFile->Create();
		m_ConfFile->Close();
		return false;
	}

	System::DbgLine("%: config file found", FUNC);
	m_ConfFile->Close();
	return true;
}

void TWAT::CConfig::ReadFull()
{
	std::string buf;

	m_ConfFile->Open(m_Path, READ);
	while(m_ConfFile->ReadLine(&buf))
	{
		if(!buf.empty())
		{
			m_Conf[GetVar(buf)] = GetVal(buf);
		}
	}

	m_ConfFile->Close();
}

void TWAT::CConfig::FillDefault()
{
	// set default values
	m_Default["app_language"] = 0;

	m_Default["gra_maximized"] = 0;
	m_Default["gra_fullscreen"] = 0;

	m_Default["ntw_check_for_updates"] = 1;
	m_Default["ntw_auto_refresh_translations"] = 1;
}

void TWAT::CConfig::WriteDefault()
{
	std::vector<std::string> tmpVec;

	m_ConfFile->Open(m_Path, WRITE);
	for(std::map<std::string, int>::iterator i = m_Default.begin(); i != m_Default.end(); i++)
	{
		tmpVec.push_back(i->first);
		m_ConfFile->Write(i->first + " " + std::to_string(m_Default[i->first]) + "\n", APPEND);
	}

	m_ConfFile->Close();
}

std::string TWAT::CConfig::GetVar(const std::string &line) const
{
	return line.substr(0, line.find(" "));
}

int TWAT::CConfig::GetVal(const std::string &line) const
{
	int space = line.find(" ");
	int length = line.length();
	return std::stoi(line.substr(space, length - space));
}
