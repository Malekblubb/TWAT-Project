/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_TWSERVERBROWSER_H
#define CORE_TWSERVERBROWSER_H


#include "core.h"


namespace TWAT
{
	class ITwServerBrowser : public IComponent
	{
		DEF_COMPONENT("twserverbrowser")


	public:
		virtual ~ITwServerBrowser() {}


		virtual void Refresh() = 0;

		virtual void AddMaster(const std::string &ip) = 0;
		virtual void UseDefaultMasters(bool b) = 0;

		virtual bool IsRefreshing() const = 0;
		virtual int ExpCount() const = 0;
		virtual int NumServers() const = 0;
		virtual int RefreshTime() const = 0;
		virtual int PercentageFinished() const = 0;
	};

}

#endif // CORE_TWSERVERBROWSER_H
