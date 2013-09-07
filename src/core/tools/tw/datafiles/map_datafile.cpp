/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 *
 * NOTE:
 *		Some parts of this file are stripped and modified
 *		from the original teeworlds source.
 *		See src/core/tw_stripped/README and
 *		src/core/tw_stripped/LICENSE for more information.
 */

#include "map_datafile.h"

#include <base/system.h>

#include <core/shared/datafile.h>
#include <core/shared/io_file.h>

#include <cstring>


TWAT::TwTools::CTwMapDataFileReader::CTwMapDataFileReader() :
	m_dfReader(new CDataFileReader)
{

}

bool TWAT::TwTools::CTwMapDataFileReader::Open(const std::string &path)
{
	m_path = path;

	// check if file exists
	CIOFile tmpIoFile(path, CIOFile::READ);
	if(!tmpIoFile.Exists())
	{
		tmpIoFile.Close();
		return false;
	}

	// setup the datafilereader
	if(!m_dfReader->Open(tmpIoFile))
	{
		tmpIoFile.Close();
		return false;
	}

	// we dont need this anymore
	tmpIoFile.Close();


	// read and check the header information
	TwMapDataFileHeader tmpHeader;
	int bytes = m_dfReader->Read(&tmpHeader, sizeof(TwMapDataFileHeader));

	if(bytes != sizeof(TwMapDataFileHeader))
	{
		DBG("error while read map header (read=%, expected=%)", bytes, sizeof(TwMapDataFileHeader));
		return false;
	}

	if(std::memcmp(tmpHeader.m_sig, "DATA", 4) != 0)
	{
		if((std::memcmp(tmpHeader.m_sig, "ATAD", 4) != 0))
		{
			DBG("map signature string does not match (got=%, expected=DATA or ATAD)", std::string(tmpHeader.m_sig));
			return false;
		}
	}

	if(tmpHeader.m_version != 4)
	{
		DBG("map version does not match (got=%, expected=4)", tmpHeader.m_version);
		return false;
	}



	return true;
}
