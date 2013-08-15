/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef SYSTEM_H
#define SYSTEM_H


#include "sys_lookup.h"
#include <string>
#include <iostream>


namespace TWAT
{
	namespace System
	{
		// systemside funcs
		std::string TimeStr(); // returns current timestamp as std::string
		std::string WorkDir(); // returns the path of the main wotking-directory like /home/user/.twat
		std::string Locale(); // returns the locale like "de"


		// network communication
		class Ip4Addr
		{
		public:
			enum Flags
			{
				NUMERIC = 1,
				HOSTNAME = 2
			};

			Ip4Addr(const std::string &addr, int flag = NUMERIC);

			std::string Ip() const {return m_ip;}
			unsigned short Port() const {return m_port;}

		private:
			std::string m_ip;
			unsigned short m_port;
		};

		int UdpSock();
		ssize_t UdpSend(int sock, unsigned char *data, size_t dataLen, Ip4Addr *target);
		ssize_t UdpRecv(int sock, unsigned char *buf, size_t bufLen);



		// stdout-log
		void DbgLine(const char *format);
		template<typename T, typename ... Args> void DbgLine(const char *format, T val, Args ... args)
		{
			std::string tmp = (std::string)format;

			if(tmp.find('\n') == std::string::npos)
			{
				tmp.append("\n");
				format = tmp.c_str();
			}

			for (; *format != '\0'; format++)
			{
				if(*format == '%')
				{
					std::cout << val;
					DbgLine(format + 1, args... ); // recursive call
					return;
				}
				std::cout << *format;
			}
		}
	}
}

#endif // SYSTEM_H
