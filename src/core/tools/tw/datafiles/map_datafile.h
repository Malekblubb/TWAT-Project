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

#ifndef CORE_TOOLS_TW_DATAFILES_MAP_DATAFILE_H
#define CORE_TOOLS_TW_DATAFILES_MAP_DATAFILE_H


#include <string>


namespace TWAT
{
	class CDataFileReader;

	namespace TwTools
	{
		// raw map-datafile access

		struct TwMapDataFileHeader
		{
			char m_sig[4];
			int m_version;
			int m_size;
			int m_swaplen;
			int m_numItemTypes;
			int m_numItems;
			int m_numRawData;
			int m_itemSize;
			int m_dataSize;
		};

		struct TwMapDataFile
		{

		};

		class CTwMapDataFileReader
		{
			CDataFileReader *m_dfReader;
			std::string m_path;

		public:
			CTwMapDataFileReader();

			bool Open(const std::string &path);
			void Close();
		};

		class CTwMapDataFileWriter
		{

		};
	}
}



#endif // CORE_TOOLS_TW_DATAFILES_MAP_DATAFILE_H
