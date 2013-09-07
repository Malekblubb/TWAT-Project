/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "map.h"

#include "map_datafile.h"


// default constructor to set default values
TWAT::TwTools::CTwMap::CTwMap() :
	m_reader(new CTwMapDataFileReader),
	m_writer(new CTwMapDataFileWriter)
{

}

TWAT::TwTools::CTwMap::CTwMap(const std::string &path) : CTwMap() // call default constructor, thx to c++11
{
	this->Load(path);
}

TWAT::TwTools::CTwMap::~CTwMap()
{

}

bool TWAT::TwTools::CTwMap::Load(const std::string &path)
{
	m_path = path;

	if(!m_reader->Open(m_path))
		return false;


	return true;
}

void TWAT::TwTools::CTwMap::Close()
{

}
