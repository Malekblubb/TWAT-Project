/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_TWMAPEDITOR_H
#define CORE_TWMAPEDITOR_H


#include "component_core.h"


namespace TWAT
{
	class ITwMapEditor : public IComponent
	{
		DEF_COMPONENT("twmapeditor")

	public:
		virtual ~ITwMapEditor() {}

		virtual bool Load(const std::string &path) = 0;
	};
}

#endif // CORE_TWMAPEDITOR_H
