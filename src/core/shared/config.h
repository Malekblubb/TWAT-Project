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
		CConfigStorage m_conf;
		CIOFile *m_confFile;

	public:
		enum SettingList
		{
			APP_LANGUAGE = 0,

			GRA_MAXIMIZED = 100,
			GRA_FULLSCREEN,

			NTW_CHECK_FOR_UPDATES = 200,
			NTW_AUTO_REFRESH_TRANSLATIONS,

			UI_MENU_EXPANDED = 300
		};

		CConfig(const std::string &configPath);
		void Init();
		void Save();

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
