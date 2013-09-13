/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include <base/system.h>

#include "map.h"

#include "map_datafile.h"

#include <core/tw_stripped/mapitems.h>


// ----- map info -----
TWAT::TwTools::CTwMapInfo::CTwMapInfo()
{
	this->Clear();
}

void TWAT::TwTools::CTwMapInfo::Clear()
{
	m_author = "";
	m_version = "";
	m_credits = "";
	m_license = "";
}

void TWAT::TwTools::CTwMapInfo::SetAuthor(const std::string &author)
{
	m_author = author;
}

void TWAT::TwTools::CTwMapInfo::SetVersion(const std::string &version)
{
	m_version = version;
}

void TWAT::TwTools::CTwMapInfo::SetCredits(const std::string &credits)
{
	m_credits = credits;
}

void TWAT::TwTools::CTwMapInfo::SetLicense(const std::string &license)
{
	m_license = license;
}


// ----- map image -----
TWAT::TwTools::CTwMapImage::CTwMapImage() :
	m_height(0),
	m_width(0),
	m_external(false),
	m_data(0)
{

}

void TWAT::TwTools::CTwMapImage::SetName(const std::string &name)
{
	m_name = name;
}

void TWAT::TwTools::CTwMapImage::SetSize(int height, int width)
{
	m_height = height;
	m_width = width;
}

void TWAT::TwTools::CTwMapImage::SetData(void *data)
{
	m_data = data;
}


// ----- map group -----
TWAT::TwTools::CTwMapGroup::CTwMapGroup() :
	m_offsetX(0),
	m_offsetY(0),
	m_paraX(0),
	m_paraY(0),
	m_numLayers(0)
{

}

void TWAT::TwTools::CTwMapGroup::SetLayer(int index, CTwMapLayer *layer)
{
	if((index >= 0) && (layer->Type()) != LAYERTYPE_INVALID)
	{
		++m_numLayers;
		m_layers[index] = layer;
	}
}

int TWAT::TwTools::CTwMapGroup::NumTilesLayers()
{
	int num = 0;

	if(!m_layers.empty())
	{
		for(unsigned int i = 0; i < m_layers.size(); ++i)
			if(m_layers[i]->Type() == LAYERTYPE_TILES)
				++num;

		return num;
	}

	return 0;
}

int TWAT::TwTools::CTwMapGroup::NumQuadsLayers()
{
	int num = 0;

	if(!m_layers.empty())
	{
		for(unsigned int i = 0; i < m_layers.size(); ++i)
			if(m_layers[i]->Type() == LAYERTYPE_QUADS)
				++num;

		return num;
	}

	return 0;
}

// ----- map layer -----
TWAT::TwTools::CTwMapLayer::CTwMapLayer() :
	m_type(LAYERTYPE_INVALID),
	m_hasImage(false)
{

}

void TWAT::TwTools::CTwMapLayer::SetType(int type)
{
	m_type = type;
}

void TWAT::TwTools::CTwMapLayer::SetName(const std::string &name)
{
	m_name = name;
}

void TWAT::TwTools::CTwMapLayer::SetImage(CTwMapImage image)
{
	m_hasImage = true;
	m_image = image;
}


// ----- map tilelayer -----
void TWAT::TwTools::CTwMapLayerTiles::SetSize(int height, int width)
{
	m_height = height;
	m_width = width;
}


// ----- map quadslayer -----
TWAT::TwTools::CTwMapLayerQuads::CTwMapLayerQuads() :
	m_numQuads(0)
{

}


// ----- main map access -----
// default constructor to set default values
TWAT::TwTools::CTwMap::CTwMap() :
	m_reader(new CTwMapDataFileReader),
	m_writer(new CTwMapDataFileWriter),
	m_validMap(false),
	m_numGroups(0),
	m_groupsStart(0),
	m_numLayers(0),
	m_layersStart(0),
	m_numImages(0),
	m_imagesStart(0)
{

}

TWAT::TwTools::CTwMap::CTwMap(const std::string &path) : CTwMap() // call default constructor, thx to c++11
{
	this->Load(path);
}

TWAT::TwTools::CTwMap::~CTwMap()
{
	delete m_reader;
	delete m_writer;
}

bool TWAT::TwTools::CTwMap::Load(const std::string &path)
{
	m_path = path;

	// process the raw file
	if(!m_reader->Open(m_path))
		return false;


	// get num and start of items
	m_numGroups = m_reader->NumItemsOfType(MAPITEMTYPE_GROUP);
	m_groupsStart = m_reader->StartOfType(MAPITEMTYPE_GROUP);

	m_numLayers = m_reader->NumItemsOfType(MAPITEMTYPE_LAYER);
	m_layersStart = m_reader->StartOfType(MAPITEMTYPE_LAYER);

	m_numImages = m_reader->NumItemsOfType(MAPITEMTYPE_IMAGE);
	m_imagesStart = m_reader->StartOfType(MAPITEMTYPE_IMAGE);


	this->LoadInfo();
	this->LoadStructure();


	m_validMap = true;
	return true;
}

void TWAT::TwTools::CTwMap::Close()
{

}

void TWAT::TwTools::CTwMap::LoadInfo()
{
	int start = m_reader->StartOfType(MAPITEMTYPE_INFO);

	// info item not found in map
	if (start < 0)
		return;

	CMapItemInfo *tmpInf = (CMapItemInfo *)m_reader->ItemAt(start);

	// check for unset info
	this->SetInfo(
				tmpInf->m_Author < 0 ? "" : (char *)m_reader->DataAt(tmpInf->m_Author),
				tmpInf->m_Version < 0 ? "" : (char *)m_reader->DataAt(tmpInf->m_Version),
				tmpInf->m_Credits < 0 ? "" : (char *)m_reader->DataAt(tmpInf->m_Credits),
				tmpInf->m_License < 0 ? "" : (char *)m_reader->DataAt(tmpInf->m_License));
}

void TWAT::TwTools::CTwMap::LoadStructure()
{	
	// resize vec
	m_groups.resize(m_numGroups);

	for(int i = m_groupsStart; i < m_groupsStart + m_numGroups; ++i)
	{
		CMapItemGroup *groupItem = (CMapItemGroup *)m_reader->ItemAt(i);

		for(int j = 0; j < groupItem->m_NumLayers; ++j)
		{
			CMapItemLayer *layerItem = (CMapItemLayer *)m_reader->ItemAt(m_layersStart + j + groupItem->m_StartLayer);

			if(layerItem->m_Type == LAYERTYPE_TILES)
			{
				CMapItemLayerTilemap *tileLayerItem = (CMapItemLayerTilemap *)layerItem;
				CTwMapLayerTiles *tileLayer = new CTwMapLayerTiles();

				tileLayer->SetType(LAYERTYPE_TILES);
				tileLayer->SetSize(tileLayerItem->m_Height, tileLayerItem->m_Width);

				if(tileLayerItem->m_Image != -1)
				{
					CMapItemImage *imageItem = (CMapItemImage *)m_reader->ItemAt(m_imagesStart + tileLayerItem->m_Image);
					CTwMapImage image;

					image.SetSize(imageItem->m_Height, imageItem->m_Width);
					image.SetName((char *)m_reader->DataAt(imageItem->m_ImageName));
					image.SetData(m_reader->DataAt(imageItem->m_ImageData));

					// add the image to layer
					tileLayer->SetImage(image);
				}


				// add the layer with the info to map
				m_groups[i - m_groupsStart].SetLayer(j, tileLayer);

			}
			else if(layerItem->m_Type == LAYERTYPE_QUADS)
			{
				CMapItemLayerQuads *quadsLayerItem = (CMapItemLayerQuads *)layerItem;
				CTwMapLayerQuads *quadsLayer = new CTwMapLayerQuads();

				quadsLayer->SetType(LAYERTYPE_QUADS);

				if(quadsLayerItem->m_Image != -1)
				{
					CMapItemImage *imageItem = (CMapItemImage *)m_reader->ItemAt(m_imagesStart + quadsLayerItem->m_Image);
					CTwMapImage image;

					image.SetSize(imageItem->m_Height, imageItem->m_Width);
					image.SetName((char *)m_reader->DataAt(imageItem->m_ImageName));
					image.SetData(m_reader->DataAt(imageItem->m_ImageData));

					quadsLayer->SetImage(image);
				}

				m_groups[i - m_groupsStart].SetLayer(j, quadsLayer);
			}
		}
	}
}

void TWAT::TwTools::CTwMap::SetInfo(const std::string &author, const std::string &version, const std::string &credits, const std::string &license)
{
	m_mapInfo.SetAuthor(author);
	m_mapInfo.SetVersion(version);
	m_mapInfo.SetCredits(credits);
	m_mapInfo.SetLicense(license);
}

TWAT::TwTools::CTwMapGroup *TWAT::TwTools::CTwMap::Group(int index)
{
	if(index >= 0)
		return &m_groups[index];

	return new CTwMapGroup();
}
