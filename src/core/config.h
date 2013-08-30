/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_CONFIG_H
#define CORE_CONFIG_H


#include "component_core.h"


namespace TWAT
{
	class CConfigStorage;

	class IConfig : public IComponent
	{
		DEF_COMPONENT("config")

	public:
		virtual ~IConfig() {}

		virtual void Init() = 0;
		virtual void Save() = 0;

		virtual CConfigStorage *Store() = 0;
	};
}


#endif // CORE_CONFIG_H
