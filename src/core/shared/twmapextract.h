/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_TWMAPEXTRACT_H
#define CORE_SHARED_TWMAPEXTRACT_H


#include <core/twmapextract.h>

#include <vector>


namespace TWAT
{
	namespace TwTools
	{
		class CTwMap;
		class CTwMapImage;
	}

	class CTwMapExtract : public ITwMapExtract
	{
		TwTools::CTwMap *m_map;

		std::vector<TwTools::CTwMapImage> m_images;
		int m_numImages;

	public:
		CTwMapExtract();
		~CTwMapExtract();

		bool Load(const std::string &path);

		bool Save(int index, const std::string &path);
		TwTools::CTwMapImage *ImageAt(int index);

		int NumImages() const {return m_numImages;}

	private:
		void LoadImages();
	};
}


#endif // CORE_SHARED_TWMAPEXTRACT_H
