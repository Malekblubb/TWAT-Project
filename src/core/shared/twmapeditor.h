/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_TWMAPEDITOR_H
#define CORE_SHARED_TWMAPEDITOR_H


#include <core/twmapeditor.h>


namespace TWAT
{
	namespace TwTools
	{
		class CTwMap;
	}

	class CTwMapEditor : public ITwMapEditor
	{
		TwTools::CTwMap *m_map;

	public:
		CTwMapEditor();
		~CTwMapEditor();

		bool Load(const std::string &path);

	};
}


#endif // CORE_SHARED_TWMAPEDITOR_H
