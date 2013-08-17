#ifndef CORE_SHARED_CONFIG_STORAGE_H
#define CORE_SHARED_CONFIG_STORAGE_H


#include <map>


namespace TWAT
{
	class CConfigStorage
	{
		std::map<std::string, std::string> m_storage;

	public:
		// specification-templates to access the storage as int or string
		template<typename T> void SetVar(std::string var, T val);
		template<typename T> T GetVar(std::string var);


		// generate a list of all elements(config-vars) with their values and store it to "buf"
		void GetList(std::string *buf);
	};
}

#endif // CONFIG_STORAGE_H
