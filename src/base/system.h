/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef BASE_SYSTEM_H
#define BASE_SYSTEM_H


#include <string>
#include <iostream>


namespace TWAT
{
	namespace System
	{
		// systemside funcs
		long long TimeStamp();
		std::string TimeStr(); // returns current timestamp as std::string

		std::string SystemAppDir();
		std::string WorkDir(); // returns the path of the main wotking-directory like /home/user/.twat
		std::string TwDir();
		std::string Locale(); // returns the locale like "de"


		// TODO: ipv6 stuff
		// network communication
		class CIpAddr
		{
			std::string m_fallbackHostname;
			std::string m_ip;
			unsigned short m_port;
			bool m_isSet;

		public:
			CIpAddr();
			CIpAddr(const std::string &addr);

			void SetNewAddr(const std::string &addr);

			std::string Fallback() const {return m_fallbackHostname;}
			std::string Ip() const {return m_ip;}
			unsigned short Port() const {return m_port;}
			bool IsSet() const {return m_isSet;}
		};

		enum IpVer
		{
			IP4 = 0,
			IP6
		};

		std::string IpAddrToStr(CIpAddr *addr);
		std::string RawIpToStr(int ipVer, unsigned char *data);

		int UdpSock(CIpAddr *bindAddr = 0);
		void SockClose(int sock);
		ssize_t UdpSend(int sock, unsigned char *data, size_t dataLen, CIpAddr *target);
		ssize_t UdpRecv(int sock, unsigned char *buf, size_t bufLen, int timeout, CIpAddr *fromAddr);


		// stdout-log
		void DbgLine(std::string fnc, const char *format);
		template<typename T, typename ... Args> void DbgLine(std::string fnc, const char *format, T val, Args ... args)
		{
			std::string tmp = (std::string)format;

			if(tmp.find('\n') == std::string::npos)
			{
				int offset = fnc.find("TWAT");
				int br = fnc.find('(');

				if((offset != std::string::npos) && (br != std::string::npos))
					fnc = fnc.substr(offset, br - offset);

				tmp.append("\n");
				tmp = "[" + (std::string)fnc + "] " + tmp;
				format = tmp.c_str();
			}

			for (; *format != '\0'; format++)
			{
				if(*format == '%')
				{
					std::cout << val;
					DbgLine("", format + 1, args... ); // recursive call
					return;
				}
				std::cout << *format;
			}
		}
#define DBG(...)System::DbgLine(__PRETTY_FUNCTION__, __VA_ARGS__)
	}
}

#endif // BASE_SYSTEM_H
