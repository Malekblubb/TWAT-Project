/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_TWMAPEXTRACT_H
#define CORE_TWMAPEXTRACT_H


#include "component_core.h"


namespace TWAT
{
	namespace TwTools
	{
		class CTwMapImage;
	}

	class ITwMapExtract : public IComponent
	{
		DEF_COMPONENT("twmapextract")

	public:
		virtual ~ITwMapExtract() {}

		virtual bool Load(const std::string &path) = 0;
		virtual bool Save(int index, const std::string &path) = 0;

		virtual TWAT::TwTools::CTwMapImage *ImageAt(int index) = 0;
		virtual int NumImages() const = 0;
	};
}

#endif // CORE_TWMAPEXTRACT_H
