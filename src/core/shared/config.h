/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CONFIG_H
#define CONFIG_H


#include "config_storage.h"
#include "io_file.h"
#include <string>


namespace TWAT
{
	class CConfig
	{
		std::string m_path;
		CConfigStorage m_default;
		CIOFile *m_confFile;

	public:
		CConfigStorage m_conf; // TODO: maybe better to write a small wrapper to access config instead of making it public?

		CConfig(const std::string &configPath);
		void Init();
		void Save();

	private:
		bool CreateConfig();
		void ReadFull();
		void FillDefault();
		void WriteDefault();

		// functions to get the Variable and the Value of a configline like "variable 1"
		std::string GetVarFromLine(const std::string &line) const;
		std::string GetValFromLine(const std::string &line) const;
	};
}



#endif // CONFIG_H
