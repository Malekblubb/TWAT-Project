/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include <core/shared/datafile.h>

#include <string>

#ifndef MAP_H
#define MAP_H


namespace TwLib
{
	namespace Map
	{
		enum MapErrors
		{
			WRONG_SIG = -1,
			WRONG_VER = -2,
			INVALID_SIZE = -3,
			INVALID_FILE = -4
		};


		// map structure
		struct MapHeader
		{
			char m_Signature[4];
			int m_Version;
			int m_Size;
			int m_Swaplen;
			int m_NumItemTypes;
			int m_NumItems;
			int m_NumRawData;
			int m_ItemSize;
			int m_DataSize;
		};

		class CMapReader
		{
			TWAT::CDataFileReader m_Reader;

		public:
			CMapReader(const std::string &path);

			int Open(const std::string &path);


		private:
			// reads from 0 to 36 (header end)
			// should return 36 if everything goes right
			int ReadHeader(MapHeader *header) {return m_Reader.Read(0, 36, (unsigned char *)header);}
		};
	}
}


#endif // MAP_H
