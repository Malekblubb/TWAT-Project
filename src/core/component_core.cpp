/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "component_core.h"


TWAT::CComponentCore::~CComponentCore()
{
	// free all components
	for(auto i = m_components.begin(); i != m_components.end(); ++i)
		delete i->second;
}
