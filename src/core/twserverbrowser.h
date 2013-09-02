/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_TWSERVERBROWSER_H
#define CORE_TWSERVERBROWSER_H


#include "component_core.h"


namespace TWAT
{
	namespace TwTools
	{
		class ServerInfo;
	}

	class ITwServerBrowser : public IComponent
	{
		DEF_COMPONENT("twserverbrowser")


	public:
		virtual ~ITwServerBrowser() {}


		virtual bool Refresh() = 0;

		virtual void AddMaster(const std::string &ip) = 0;
		virtual void UseDefaultMasters(bool b) = 0;

		virtual TwTools::ServerInfo *At(int pos) = 0;

		virtual bool IsRefreshing() const = 0;
		virtual int ExpCount() const = 0;
		virtual int NumServers() const = 0;
		virtual int RefreshTime() const = 0;
		virtual int PercentageFinished() const = 0;

		virtual void RefreshMasterList() = 0;
	};

}

#endif // CORE_TWSERVERBROWSER_H
