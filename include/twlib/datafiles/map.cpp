/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "map.h"


TwLib::Map::CMapReader::CMapReader(const std::string &path)
{
	this->Open(path);
}

int TwLib::Map::CMapReader::Open(const std::string &path)
{
	if(!m_Reader.Open(path)) // open via TWAT::CDataFileReader
		return INVALID_FILE;


	// check header
	MapHeader h;

	if(this->ReadHeader(&h) != sizeof(MapHeader))
		return INVALID_FILE;

	if((h.m_Signature[0] != 'D') ||( h.m_Signature[1] != 'A') || (h.m_Signature[2] != 'T') || (h.m_Signature[3] != 'A'))
		if((h.m_Signature[0] != 'A') || (h.m_Signature[1] != 'T') || (h.m_Signature[2] != 'A') || (h.m_Signature[3] != 'D'))
			return WRONG_SIG;

	if(h.m_Version != 4)
		return WRONG_VER;

	return 0;
}
