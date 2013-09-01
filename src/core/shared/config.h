/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_CONFIG_H
#define CORE_SHARED_CONFIG_H


#include <core/config.h>


namespace TWAT
{
	class CConfig : public IConfig
	{
		std::string m_path;
		class CConfigStorage *m_default;
		class CIOFile *m_confFile;

	public:
		class CConfigStorage *m_conf;

		CConfig();
		void Init();
		void Save();
		class CConfigStorage *Store() {return m_conf;}

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



#endif // CORE_SHARED_CONFIG_H
