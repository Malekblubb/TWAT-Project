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
		CConfig(std::string configPath);

		int CreateConfig();
		int ReadFull();
		bool CheckVar();
		std::string GetValue(std::string var);
		bool Save();

	private:
		void FillDefault();
		void RestoreVar(std::string var);
	};
}

#endif // CONFIG_H
