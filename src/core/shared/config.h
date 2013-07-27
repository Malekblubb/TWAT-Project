#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>


class CConfig
{
	std::vector<std::string> m_Config;

public:
	CConfig();

	int CreateConfig();
	int ReadFull();
	bool CheckVar(std::string var);
	std::string GetValue(std::string var);
};

#endif // CONFIG_H
