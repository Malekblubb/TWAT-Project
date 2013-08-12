#ifndef CONFIG_STORAGE_H
#define CONFIG_STORAGE_H


#include <map>

namespace TWAT
{
	class CConfigStorage
	{
		std::map<std::string, std::string> m_storage;

	public:
		template<typename T> void SetVar(std::string var, T val);
		template<typename T> T GetVar(std::string var);
	};
}

#endif // CONFIG_STORAGE_H
