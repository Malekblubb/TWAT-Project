/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 *
 * NOTE:
 *		Some parts of this file are stripped and modified
 *		from the original teeworlds source and are (c) Magnus Auvinen.
 *		See src/core/tw_stripped/README and
 *		src/core/tw_stripped/LICENSE for more information.
 */

#include "map_datafile.h"

#include <base/system.h>

#include <core/shared/datafile.h>
#include <core/shared/io_file.h>

#include <cstring>
#include <zlib.h>


TWAT::TwTools::CTwMapDataFileReader::CTwMapDataFileReader() :
	m_mapFile(new TwMapDataFile),
	m_dfReader(new CDataFileReader)
{

}

TWAT::TwTools::CTwMapDataFileReader::~CTwMapDataFileReader()
{
	m_dfReader->Close();

	for(unsigned int i = 0; i < m_mapFile->m_compressedDatas.size(); ++i)
		std::free(m_mapFile->m_compressedDatas[i]);

	for(unsigned int i = 0; i < m_mapFile->m_uncompressedDatas.size(); ++i)
	{
		if(m_mapFile->m_uncompressedDatas[i])
			std::free(m_mapFile->m_uncompressedDatas[i]);
	}

	delete m_mapFile;
	delete m_dfReader;
}

bool TWAT::TwTools::CTwMapDataFileReader::Open(const std::string &path)
{
	m_path = path;

	// check if file exists
	CIOFile tmpIoFile(m_path, CIOFile::READ);
	if(!tmpIoFile.Exists())
	{
		tmpIoFile.Close();

		DBG("file not found (path=%)", m_path);
		return false;
	}

	// setup the datafilereader
	if(!m_dfReader->Open(tmpIoFile))
	{
		tmpIoFile.Close();

		DBG("error while open file (path=%)", m_path);
		return false;
	}

	// we dont need this anymore
	tmpIoFile.Close();


	DBG("start processing map datafile (path=%)", m_path);


	// read and check the header
	TwMapDataFileHeader header;
	int headerBytesRead = m_dfReader->Read(&header, sizeof(TwMapDataFileHeader));

	if(headerBytesRead != sizeof(TwMapDataFileHeader))
	{
		DBG("error while read header (read=%, expected=%)", headerBytesRead, sizeof(TwMapDataFileHeader));
		return false;
	}

	if(std::memcmp(header.m_sig, "DATA", 4) != 0)
	{
		if(std::memcmp(header.m_sig, "ATAD", 4) != 0)
		{
			DBG("wrong signature (got=%, expected=DATA or ATAD)", std::string(header.m_sig));
			return false;
		}
	}

	if(header.m_version != 4)
	{
		DBG("wrong version (got=%, expected=4)", header.m_version);
		return false;
	}

	// cpy header
	m_mapFile->m_header = header;


	// file seems to be ok, resize vectors
	m_mapFile->m_info.m_typesInfo.resize(header.m_numItemTypes);
	m_mapFile->m_info.m_itemOffsets.resize(header.m_numItems);
	m_mapFile->m_info.m_compressedDataOffsets.resize(header.m_numRawData);
	m_mapFile->m_info.m_uncompressedDataSizes.resize(header.m_numRawData);
	m_mapFile->m_compressedDatas.resize(header.m_numRawData);

	int fileLength = sizeof(TwMapDataFileHeader) +
			(header.m_numItemTypes * sizeof(TwMapDataFileItemInfo)) +
			(header.m_numItems * sizeof(int)) +
			((header.m_numRawData * sizeof(int)) * 2) +
			(header.m_itemSize + header.m_dataSize);

	// read the item info (type, start, num)
	for(int i = 0; i < header.m_numItemTypes; ++i)
		m_dfReader->Read(&m_mapFile->m_info.m_typesInfo[i], sizeof(TwMapDataFileItemInfo));

	// read the item offsets
	for(int i = 0; i < header.m_numItems; ++i)
		m_dfReader->Read(&m_mapFile->m_info.m_itemOffsets[i], sizeof(int));

	// read the compressed data offsets
	for(int i = 0; i < header.m_numRawData; ++i)
		m_dfReader->Read(&m_mapFile->m_info.m_compressedDataOffsets[i], sizeof(int));

	// read the sizes of the data after uncompressing
	for(int i = 0; i < header.m_numRawData; ++i)
		m_dfReader->Read(&m_mapFile->m_info.m_uncompressedDataSizes[i], sizeof(int));


	// read the items with their data
	for(int i = 0; i < header.m_numItems; ++i)
	{
		// read size_and_id (as one int) and size of the item
		TwMapDataFileItemRaw tmpItem;
		m_dfReader->Read(&tmpItem, sizeof(TwMapDataFileItemRaw));

		TwMapDataFileItemExt tmpItemExt;
		tmpItemExt.m_size = tmpItem.m_size;
		tmpItemExt.m_type = (tmpItem.m_typeAndId >> 16) & 0xff;
		tmpItemExt.m_id = tmpItem.m_typeAndId & 0xff;
		tmpItemExt.m_data = (char *)std::malloc(tmpItemExt.m_size);

		// read item data
		m_dfReader->Read(tmpItemExt.m_data, tmpItemExt.m_size);

		m_mapFile->m_items.push_back(tmpItemExt);
	}

	// read the compressed data
	for(int i = 0; i < header.m_numRawData; ++i)
	{
		int readLen = 0;

		if(i == header.m_numRawData - 1)
			readLen = header.m_dataSize - m_mapFile->m_info.m_compressedDataOffsets[header.m_numRawData - 1];
		else
			readLen = m_mapFile->m_info.m_compressedDataOffsets[i + 1] - m_mapFile->m_info.m_compressedDataOffsets[i];

		m_mapFile->m_compressedDatas[i] = (char *)std::malloc(readLen);
		m_dfReader->Read(m_mapFile->m_compressedDatas[i], readLen);
	}

	if(m_dfReader->Pos() != fileLength)
	{
		// something went wrong

		DBG("error while read compressed data");
		return false;
	}


	DBG("successfully read full file (file_len=%, reader_pos=%)", fileLength, m_dfReader->Pos());
	return true;
}

int TWAT::TwTools::CTwMapDataFileReader::NumData() const
{
	return m_mapFile->m_header.m_numRawData;
}

int TWAT::TwTools::CTwMapDataFileReader::NumItems() const
{
	return m_mapFile->m_header.m_numItems;
}

int TWAT::TwTools::CTwMapDataFileReader::NumItemsOfType(int type) const
{
	int num = 0;

	for(int i = 0; i < m_mapFile->m_header.m_numItems; ++i)
	{
		if(m_mapFile->m_items[i].m_type == type)
			++num;
	}

	return num;
}

int TWAT::TwTools::CTwMapDataFileReader::DataSizeAt(int index) const
{
	if(index == m_mapFile->m_header.m_numRawData - 1)
		return  m_mapFile->m_header.m_dataSize - m_mapFile->m_info.m_compressedDataOffsets[m_mapFile->m_header.m_numRawData - 1];

	return m_mapFile->m_info.m_compressedDataOffsets[index + 1] - m_mapFile->m_info.m_compressedDataOffsets[index];
}

void *TWAT::TwTools::CTwMapDataFileReader::ItemAt(int index) const
{
	return m_mapFile->m_items[index].m_data;
}

void *TWAT::TwTools::CTwMapDataFileReader::DataAt(int index)
{
	if(!m_mapFile->m_uncompressedDatas[index])
	{
		// data wasnt uncompressed yet, uncompressed it
		this->UncompressData(index);
	}

	return m_mapFile->m_uncompressedDatas[index];
}

bool TWAT::TwTools::CTwMapDataFileReader::UncompressData(int index)
{
	m_mapFile->m_uncompressedDatas[index] = (char *)std::malloc(m_mapFile->m_info.m_uncompressedDataSizes[index]);

	unsigned long compressedLen = this->DataSizeAt(index);
	unsigned long uncompressedLen = m_mapFile->m_info.m_uncompressedDataSizes[index];

	int zError = uncompress((Bytef *)m_mapFile->m_uncompressedDatas[index], &uncompressedLen, (Bytef *)m_mapFile->m_compressedDatas[index], compressedLen);
	if(zError != Z_OK)
	{
		DBG("error while uncompress data (index=%, zlib_error=%, compressed_len=%, uncompressed_len=%)", index, zError, compressedLen, uncompressedLen);
		return false;
	}

	return true;
}
