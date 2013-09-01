/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef TWSERVERTESTER_H
#define TWSERVERTESTER_H


#include "component_core.h"


namespace TWAT
{
	namespace TwTools
	{
		struct ServerInfo;
	}

	class ITwServerTester : public IComponent
	{
		DEF_COMPONENT("twservertester")

	public:
		virtual bool Reset(const std::string &addr) = 0;
		virtual int Ping() = 0;

		virtual TwTools::ServerInfo *ServerInfo() const = 0;
		virtual int NumSentPks() const = 0;
		virtual int NumLostPks() const = 0;
		virtual bool CurrentPkLost() const = 0;
		virtual int SentDataLen() const = 0;
		virtual int RecDataLen() const = 0;
		virtual int CurrentSentDataLen() const = 0;
		virtual int CurrentRecDataLen() const = 0;
	};
}


#endif // TWSERVERTESTER_H
