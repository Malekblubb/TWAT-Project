/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>


namespace TWAT
{
	class CConfig
	{
		std::string m_Path;
		std::map<std::string, std::string> m_Conf;
		std::map<std::string, std::string> m_Default;

	public:
		CConfig(const std::string &configPath);

		int CreateConfig();
		void ReadFull();
		bool CheckVar();
		std::string GetValue(const std::string &var);
		bool Save();

	private:
		void FillDefault();
		void RestoreVar(const std::string &var);
	};
}

#endif // CONFIG_H
