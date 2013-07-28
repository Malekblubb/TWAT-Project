/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "config.h"


TWAT::CConfig::CConfig(const std::string &configPath)
{
	m_Path = configPath;
}

int TWAT::CConfig::CreateConfig()
{

}

void TWAT::CConfig::ReadFull()
{

}

bool TWAT::CConfig::CheckVar()
{

}

std::string TWAT::CConfig::GetValue(const std::string &var)
{

}

bool TWAT::CConfig::Save()
{

}

void TWAT::CConfig::FillDefault()
{
	// set default values
	m_Default["ntw_check_for_updates"] = "1";
}

void TWAT::CConfig::RestoreVar(const std::string &var)
{

}
