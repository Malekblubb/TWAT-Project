/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "twmapextract.h"

#include <core/tools/tw/datafiles/map.h>

#include <core/tw_stripped/mapitems.h>

#include <core/shared/graphics.h>


TWAT::CTwMapExtract::CTwMapExtract() :
	m_map(new TwTools::CTwMap),
	m_numImages(0)
{

}

TWAT::CTwMapExtract::~CTwMapExtract()
{
	delete m_map;
}

bool TWAT::CTwMapExtract::Load(const std::string &path)
{
	if(!m_map->Load(path))
		return false;

	m_numImages = 0;

	// load images
	this->LoadImages();

	return true;
}

bool TWAT::CTwMapExtract::Save(int index, const std::string &path)
{
	return CPng::SaveTo(path, m_images[index].Height(), m_images[index].Width(), m_images[index].Data());
}

TWAT::TwTools::CTwMapImage *TWAT::CTwMapExtract::ImageAt(int index)
{
	return &m_images[index];
}

void TWAT::CTwMapExtract::LoadImages()
{
	m_images.clear();

	for(int i = 0; i < m_map->NumImages(); ++i)
	{
//		if(!m_map->Image(i)->External())
		{
			TwTools::CTwMapImage img = *m_map->Image(i);

			++m_numImages;
			m_images.push_back(img);
		}
	}
}
