/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include <base/app_info.h>
#include <base/system.h>

#include "map.h"
#include "map_datafile.h"

#include <core/shared/graphics.h>

#include <core/tw_stripped/stuff.h>

#include <cstring>


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
	m_data(0),
	m_dataSize(0)
{

}

TWAT::TwTools::CTwMapImage::CTwMapImage(const CTwMapImage &other) :
	m_name(other.m_name),
	m_height(other.m_height),
	m_width(other.m_width),
	m_external(other.m_external),
	m_dataSize(other.m_dataSize)
{
	m_data = new unsigned char[m_dataSize];
	std::memcpy(m_data, other.m_data, m_dataSize);
}

TWAT::TwTools::CTwMapImage::~CTwMapImage()
{
	delete[] m_data;
}

TWAT::TwTools::CTwMapImage &TWAT::TwTools::CTwMapImage::operator =(const CTwMapImage &other)
{
	m_name = other.m_name;
	m_height = other.m_height;
	m_width = other.m_width;
	m_external = other.m_external;
	m_dataSize = other.m_dataSize;

	unsigned char *data = new unsigned char[m_dataSize];
	std::memcpy(data, other.m_data, m_dataSize);

	delete[] m_data;
	m_data = data;

	return *this;
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

void TWAT::TwTools::CTwMapImage::LoadFromData(void *data, int size)
{
	m_dataSize = size;
	m_data = new unsigned char[m_dataSize];
	std::memcpy(m_data, data, m_dataSize);
}

bool TWAT::TwTools::CTwMapImage::LoadFromFile(const std::string &path)
{
	m_dataSize = CPng::RawDataFromFile(path, m_data);

	return true;
}

void TWAT::TwTools::CTwMapImage::Embed()
{
	m_external = false;
}

void TWAT::TwTools::CTwMapImage::MakeExternal()
{
	m_external = true;
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

TWAT::TwTools::CTwMapGroup::~CTwMapGroup()
{
	// free the alloced layers
	for(auto i = m_layers.begin(); i != m_layers.end(); ++i)
	{
		if(i->second->Type() == LAYERTYPE_TILES)
			delete reinterpret_cast<CTwMapLayerTiles *>(i->second);

		else if(i->second->Type() == LAYERTYPE_QUADS)
			delete reinterpret_cast<CTwMapLayerQuads *>(i->second);
	}
}

void TWAT::TwTools::CTwMapGroup::SetName(const std::string &name)
{
	m_name = name;
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

void TWAT::TwTools::CTwMapLayer::SetImage(const CTwMapImage &image)
{
	m_hasImage = true;
	m_image = image;
}


// ----- map tilelayer -----
TWAT::TwTools::CTwMapLayerTiles::CTwMapLayerTiles() :
	m_width(0),
	m_height(0),
	m_tiles(0)
{

}

TWAT::TwTools::CTwMapLayerTiles::CTwMapLayerTiles(const CTwMapLayerTiles &other) :
	m_width(other.m_width),
	m_height(other.m_height)
{
	m_tiles = new CTile[m_width * m_height];
	std::memcpy(m_tiles, other.m_tiles, m_width * m_height);
}

TWAT::TwTools::CTwMapLayerTiles::~CTwMapLayerTiles()
{
	delete[] m_tiles;
}

void TWAT::TwTools::CTwMapLayerTiles::SetTiles(void *data)
{
	m_tiles = new CTile[m_width * m_height];
	std::memcpy(m_tiles, data, m_width * m_height);
}

CTile *TWAT::TwTools::CTwMapLayerTiles::Tile(int index)
{
	if((index >= 0) && (index < m_width * m_height))
		return &m_tiles[index];

	return 0;
}

void TWAT::TwTools::CTwMapLayerTiles::SetSize(int height, int width)
{
	m_height = height;
	m_width = width;
}

void TWAT::TwTools::CTwMapLayerTiles::SetColor(const CColor &color)
{
	m_color = color;
}


// ----- map quadslayer -----
TWAT::TwTools::CTwMapLayerQuads::CTwMapLayerQuads() :
	m_numQuads(0)
{

}

void TWAT::TwTools::CTwMapLayerQuads::AddQuad(const CQuad &quad)
{
	m_quads.push_back(quad);
	++m_numQuads;
}

CQuad *TWAT::TwTools::CTwMapLayerQuads::Quad(int index)
{
	if((index >= 0) && (index < m_numQuads))
		return &m_quads[index];

	return 0;
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
	{
		m_reader->Close();
		return false;
	}


	// get num and start of items
	m_numGroups = m_reader->NumItemsOfType(MAPITEMTYPE_GROUP);
	m_groupsStart = m_reader->StartOfType(MAPITEMTYPE_GROUP);
	m_groups.resize(m_numGroups); // resize vec

	m_numLayers = m_reader->NumItemsOfType(MAPITEMTYPE_LAYER);
	m_layersStart = m_reader->StartOfType(MAPITEMTYPE_LAYER);

	m_numImages = m_reader->NumItemsOfType(MAPITEMTYPE_IMAGE);
	m_imagesStart = m_reader->StartOfType(MAPITEMTYPE_IMAGE);


	this->LoadInfo();
	this->LoadImages();
	this->LoadStructure();

	m_reader->Close(); // close to free data
	m_validMap = true;

	return true;
}

void TWAT::TwTools::CTwMap::Close()
{
	m_reader->Close();
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
				tmpInf->m_MapVersion < 0 ? "" : (char *)m_reader->DataAt(tmpInf->m_MapVersion),
				tmpInf->m_Credits < 0 ? "" : (char *)m_reader->DataAt(tmpInf->m_Credits),
				tmpInf->m_License < 0 ? "" : (char *)m_reader->DataAt(tmpInf->m_License));
}

void TWAT::TwTools::CTwMap::LoadImages()
{
	m_images.clear();

	for(int i = m_imagesStart; i < m_imagesStart + m_numImages; ++i)
	{
		CMapItemImage *imageItem = (CMapItemImage *)m_reader->ItemAt(i);
		CTwMapImage image;

		image.SetSize(imageItem->m_Height, imageItem->m_Width);
		image.SetName((char *)m_reader->DataAt(imageItem->m_ImageName));

		if(!imageItem->m_External)
		{
			image.LoadFromData(m_reader->DataAt(imageItem->m_ImageData), m_reader->UncompressedDataSizeAt(imageItem->m_ImageData));
			image.Embed();
		}
		else
		{
			image.LoadFromFile(std::string(APP_TW_DATA_PATH) + "mapres/" + image.Name() + ".png");
			image.MakeExternal();
		}

		m_images.push_back(image);
	}
}

void TWAT::TwTools::CTwMap::LoadStructure()
{
	for(int i = m_groupsStart; i < m_groupsStart + m_numGroups; ++i)
	{
		CMapItemGroup *groupItem = (CMapItemGroup *)m_reader->ItemAt(i);

		char tmp[12];
		TwStuff::IntsToStr(groupItem->m_aName, 3, tmp);
		m_groups[i - m_groupsStart].SetName(tmp);

		for(int j = 0; j < groupItem->m_NumLayers; ++j)
		{
			CMapItemLayer *layerItem = (CMapItemLayer *)m_reader->ItemAt(m_layersStart + j + groupItem->m_StartLayer);

			if(layerItem->m_Type == LAYERTYPE_TILES)
			{
				CMapItemLayerTilemap *tileLayerItem = (CMapItemLayerTilemap *)layerItem;
				CTwMapLayerTiles *tileLayer = new CTwMapLayerTiles();

				tileLayer->SetType(LAYERTYPE_TILES);
				tileLayer->SetSize(tileLayerItem->m_Height, tileLayerItem->m_Width);
				tileLayer->SetTiles(m_reader->DataAt(tileLayerItem->m_Data));
				tileLayer->SetColor(CColor(tileLayerItem->m_Color.m_r, tileLayerItem->m_Color.m_g, tileLayerItem->m_Color.m_b, tileLayerItem->m_Color.m_a));

				// get name
				char tmp[12];
				TwStuff::IntsToStr(tileLayerItem->m_aName, 3, tmp);
				tileLayer->SetName(tmp);

				if(tileLayerItem->m_Image != -1)
				{
					CMapItemImage *imageItem = (CMapItemImage *)m_reader->ItemAt(m_imagesStart + tileLayerItem->m_Image);
					CTwMapImage image;

					image.SetSize(imageItem->m_Height, imageItem->m_Width);
					image.SetName((char *)m_reader->DataAt(imageItem->m_ImageName));

					if(!imageItem->m_External)
					{
						image.LoadFromData(m_reader->DataAt(imageItem->m_ImageData), m_reader->UncompressedDataSizeAt(imageItem->m_ImageData));
						image.Embed();
					}
					else
					{
						image.LoadFromFile(std::string(APP_TW_DATA_PATH) + "mapres/" + image.Name() + ".png");
						image.MakeExternal();
					}

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

				char tmp[12];
				TwStuff::IntsToStr(quadsLayerItem->m_aName, 3, tmp);
				quadsLayer->SetName(tmp);

				// set quads
				CQuad *quads = (CQuad *)m_reader->DataAt(quadsLayerItem->m_Data);
				for(int q = 0; q < quadsLayerItem->m_NumQuads; ++q)
					quadsLayer->AddQuad(quads[q]);


				if(quadsLayerItem->m_Image != -1)
				{
					CMapItemImage *imageItem = (CMapItemImage *)m_reader->ItemAt(m_imagesStart + quadsLayerItem->m_Image);
					CTwMapImage image;

					image.SetSize(imageItem->m_Height, imageItem->m_Width);
					image.SetName((char *)m_reader->DataAt(imageItem->m_ImageName));

					if(!imageItem->m_External)
					{
						image.LoadFromData(m_reader->DataAt(imageItem->m_ImageData), m_reader->UncompressedDataSizeAt(imageItem->m_ImageData));
						image.Embed();
					}
					else
					{
						image.LoadFromFile(std::string(APP_TW_DATA_PATH) + "mapres/" + image.Name() + ".png");
						image.MakeExternal();
					}

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

void TWAT::TwTools::CTwMap::AddGroup(const CTwMapGroup &group)
{
	m_groups.push_back(group);
}

void TWAT::TwTools::CTwMap::SetGroup(int index, const CTwMapGroup &group)
{
	m_groups[index] = group;
}

TWAT::TwTools::CTwMapGroup *TWAT::TwTools::CTwMap::Group(int index)
{
	if((index >= 0) && (index < (int)m_groups.size()))
		return &m_groups[index];

	return NULL;
}

TWAT::TwTools::CTwMapImage *TWAT::TwTools::CTwMap::Image(int index)
{
	if((index >= 0) && (index < (int)m_images.size()))
		return &m_images[index];

	return NULL;
}
