/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "twmapextract.h"

#include <core/tools/tw/datafiles/map.h>

#include <core/tw_stripped/mapitems.h>

#include <pnglite/pnglite.h>


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
	png_t png;

	png_init(0, 0);

	if(png_open_file_write(&png, path.c_str()) != PNG_NO_ERROR)
		return false;

	png_set_data(&png, m_images[index].Width(), m_images[index].Height(), 8, PNG_TRUECOLOR_ALPHA, (unsigned char *)m_images[index].Data());
	png_close_file(&png);

	return true;
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
