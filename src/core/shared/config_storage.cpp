#include "config_storage.h"


namespace TWAT
{
	template<> void CConfigStorage::SetVar<int>(std::string var, int val) {m_storage[var] = std::to_string(val);}
	template<> void CConfigStorage::SetVar<std::string>(std::string var, std::string val) {m_storage[var] = val;}

	template<> int CConfigStorage::GetVar<int>(std::string var) {return std::stoi(m_storage[var]);}
	template<> std::string CConfigStorage::GetVar<std::string>(std::string var) {return m_storage[var];}
}
