/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "system.h"

#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>
#include <stdexcept>

// TODO: apple
#if defined(OS_LINUX)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#elif defined(OS_WIN)
#include <windows.h>
#endif


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


TWAT::System::Ip4Addr::Ip4Addr(const std::string &addr, int flag)
{
	if(addr.find(':') == std::string::npos)
		throw std::invalid_argument("argument has invalid format (Ip4Addr)");

	if(flag == NUMERIC)
		if(addr.length() < 9)
			throw std::length_error("argument has invalid length (Ip4Addr)");

	// get ip, port
	m_ip = addr.substr(0, addr.find(':'));
	m_port = std::atoi(addr.substr(addr.find(':') + 1, addr.length() - addr.find(':') - 1).c_str());

	// get ip from hostname
	if(flag == HOSTNAME)
	{
		hostent *host;
		in_addr **addrList;

		host = gethostbyname(m_ip.c_str());
		addrList = (in_addr **)host->h_addr_list;
		m_ip = inet_ntoa(*addrList[0]);
	}
}

int TWAT::System::UdpSock()
{
	return socket(AF_INET, SOCK_DGRAM, 0);
}

ssize_t TWAT::System::UdpSend(int sock, unsigned char *data, size_t dataLen, Ip4Addr *target)
{
	sockaddr_in tmpAddr;

	std::memset(&tmpAddr, 0, sizeof tmpAddr);
	tmpAddr.sin_family = AF_INET;
	tmpAddr.sin_addr.s_addr = inet_addr(target->Ip().c_str());
	tmpAddr.sin_port = htons(target->Port());

	return sendto(sock, data, dataLen, 0, (sockaddr *)&tmpAddr, sizeof tmpAddr);
}

ssize_t TWAT::System::UdpRecv(int sock, unsigned char *buf, size_t bufLen)
{
	return recvfrom(sock, buf, bufLen, 0, NULL, NULL);
}


void TWAT::System::DbgLine(const char *format)
{
	std::cout << format;
}

