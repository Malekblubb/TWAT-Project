/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "io_file.h"
#include <string>
#include <map>


namespace TWAT
{
	class CConfig
	{
		std::string m_Path;
		std::map<std::string, int> m_Default;
		CIOFile *m_ConfFile;

	public:
		std::map<std::string, int> m_Conf;

		CConfig(const std::string &configPath);

		void Init();
		bool Save();

	private:
		bool CreateConfig();
		void ReadFull();
		void FillDefault();
		void WriteDefault();

		// functions to get the Variable and the Value of a configline like "variable 1"
		std::string GetVar(const std::string &line) const;
		int GetVal(const std::string &line) const;
	};
}

#endif // CONFIG_H
