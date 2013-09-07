/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "system.h"
#include "sys_lookup.h"

#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cerrno>

// TODO: apple
#if defined(OS_LINUX)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#elif defined(OS_WIN)
#include <windows.h>
#endif


long long TWAT::System::TimeStamp()
{
	return (long long)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()
			+ (long long)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

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

TWAT::System::CIpAddr::CIpAddr()
{
	m_isSet = false;
}

TWAT::System::CIpAddr::CIpAddr(const std::string &addr)
{
	this->SetNewAddr(addr);
}

void TWAT::System::CIpAddr::SetNewAddr(const std::string &addr)
{
	m_isSet = false;

	if(addr.find(':') == std::string::npos)
		return;

	if(addr.length() < 9)
		return;

	// get ip, port
	m_ip = addr.substr(0, addr.find(':'));
	m_port = std::atoi(addr.substr(addr.find(':') + 1, addr.length() - addr.find(':') - 1).c_str());

	// always try to get ip from hostname
	hostent *host;
	in_addr **addrList;

	host = gethostbyname(m_ip.c_str());

	if(host != 0)
	{
		addrList = (in_addr **)host->h_addr_list;
		m_ip = inet_ntoa(*addrList[0]);
		m_isSet = true;
	}
	else
	{
		// unable to get hosts ip -> not reachable?
		m_fallbackHostname = m_ip;
		m_ip = "0.0.0.0";
		m_port = 0;
		m_isSet = false;
	}
}

std::string TWAT::System::IpAddrToStr(CIpAddr *addr)
{
	if(addr->IsSet())
		return addr->Ip() + ":" + std::to_string(addr->Port());

	return "Unknown host (" + addr->Fallback() + ")";
}

std::string TWAT::System::RawIpToStr(int ipVer, unsigned char *data)
{
	char tmp[INET6_ADDRSTRLEN];
	int af = 0;

	if(ipVer == IP4)
		af = AF_INET;
	else if(ipVer == IP6)
		af = AF_INET6;

	if(inet_ntop(af, data, tmp, sizeof tmp))
	{
		if(ipVer == IP4)
			return (std::string)tmp;

		else if(ipVer == IP6)
			return "[" + (std::string)tmp + "]";
	}

	return "Invalid data passed";
}

int TWAT::System::UdpSock(CIpAddr *bindAddr)
{
	int tmpSock = socket(AF_INET, SOCK_DGRAM, 0);

	if(tmpSock > 0)
	{
		if(bindAddr != 0)
		{
			sockaddr_in tmpAddr;

			tmpAddr.sin_family = AF_INET;
			tmpAddr.sin_port = htons(bindAddr->Port());
			tmpAddr.sin_addr.s_addr = inet_addr(bindAddr->Ip().c_str());


			if(bind(tmpSock, (sockaddr *)&tmpAddr, sizeof tmpAddr) < 0)
			{
				System::SockClose(tmpSock);
				return -1;
			}
		}

		fcntl(tmpSock, F_SETFL, O_NONBLOCK);


		return tmpSock;
	}

	return -1;
}

void TWAT::System::SockClose(int sock)
{
	close(sock);
}

ssize_t TWAT::System::UdpSend(int sock, unsigned char *data, size_t dataLen, CIpAddr *target)
{
	sockaddr_in tmpAddr;

	std::memset(&tmpAddr, 0, sizeof tmpAddr);
	tmpAddr.sin_family = AF_INET;
	tmpAddr.sin_addr.s_addr = inet_addr(target->Ip().c_str());
	tmpAddr.sin_port = htons(target->Port());

	return sendto(sock, data, dataLen, 0, (sockaddr *)&tmpAddr, sizeof tmpAddr);
}

ssize_t TWAT::System::UdpRecv(int sock, unsigned char *buf, size_t bufLen, int timeout, CIpAddr *fromAddr)
{
	sockaddr_in senderInfo;
	socklen_t senderInfoSize = sizeof senderInfo;
	ssize_t got = -1;
	std::stringstream stream;
	char addrBuf[INET_ADDRSTRLEN];
	long long to = System::TimeStamp() + timeout;

	bzero(&senderInfo, sizeof senderInfo);
	std::memset(buf, 0, bufLen);


	// idea from https://github.com/fisted
	while(System::TimeStamp() < to) // loop until we got data or timeout
	{
		errno = 0;

		got = recvfrom(sock, buf, bufLen, 0, (sockaddr *)&senderInfo, &senderInfoSize);

		if((errno == EWOULDBLOCK) || (errno == EAGAIN))
			continue;

		else
			break;
	}

	if(fromAddr != 0)
	{
		// get sender info
		inet_ntop(AF_INET, &senderInfo.sin_addr, addrBuf, INET_ADDRSTRLEN);
		stream << addrBuf << ":" << htons(senderInfo.sin_port);
		fromAddr->SetNewAddr(stream.str());
	}

	return got;
}


void TWAT::System::DbgLine(std::string fnc, const char *format)
{
	if((std::string)fnc != "")
	{
		int offset = fnc.find("TWAT");
		fnc = fnc.substr(offset, fnc.find('(') - offset);
		std::cout << "[" << fnc << "] " << format << std::endl;
	}

	else
		std::cout << format;
}

