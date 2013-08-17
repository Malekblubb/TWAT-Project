/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "config_storage.h"


namespace TWAT
{
	template<> void CConfigStorage::SetVar<int>(std::string var, int val) {m_storage[var] = std::to_string(val);}
	template<> void CConfigStorage::SetVar<std::string>(std::string var, std::string val){m_storage[var] = val;}

	template<> int CConfigStorage::GetVar<int>(std::string var) {return std::stoi(m_storage[var]);}
	template<> std::string CConfigStorage::GetVar<std::string>(std::string var) {return m_storage[var];}


	void CConfigStorage::GetList(std::string *buf)
	{
		buf->clear();

		for(std::map<std::string, std::string>::iterator i = m_storage.begin(); i != m_storage.end(); i++)
			*buf += i->first + " " + i->second + "\n";
	}
}
