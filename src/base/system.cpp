/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "system.h"

#include <chrono>
#include <ctime>
#include <iostream>


std::string TWAT::System::TimeStr()
{
	auto timePoint = std::chrono::system_clock::now();
	std::time_t timeNow = std::chrono::system_clock::to_time_t(timePoint);
	std::string tmpTime = std::ctime(&timeNow);

	// cut away \n, don't know why it is there
	if(tmpTime.find('\n') != std::string::npos)
		tmpTime = tmpTime.erase(tmpTime.find('\n'));

	return tmpTime;
}

std::string TWAT::System::WorkDir()
{
	std::string tmp;

#if defined(OS_LINUX) || defined(OS_MAC)
	tmp = std::getenv("HOME");
	tmp += "/.twat/";
#else
	tmp = std::getenv("APPDATA");
	tmp += "\\.twat\\";
#endif

	return tmp;
}

std::string TWAT::System::Locale()
{
	std::string locPre;

#if defined (OS_LINUX)
	std::locale loc("");
	locPre = loc.name();
#endif

#if defined(OS_WIN)
	int iId = GetSystemDefaultLCID();

	if(iId == 1031 || iId == 2055 || iId == 3079 || iId == 4103 || iId == 5127)
		locPre = "de";
	else
		locPre = "unknown";
#endif

	return locPre.substr(0, 2);
}

void TWAT::System::DbgLine(const char *format)
{
	std::cout << format;
}

