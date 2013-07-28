#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>


namespace TWAT
{
	namespace System
	{
		// systemside funcs
		std::string TimeStr(); // returns current timestamp as std::string
		std::string WorkDir(); // return the path of the main wotking-directory like /home/user/twat
		std::string Locale(); // returns

		// stdout-log
		void DbgLine(const char *format);
		template<typename T, typename ... Args> void DbgLine(const char *format, T val, Args ... args);
	}
}

#endif // SYSTEM_H
