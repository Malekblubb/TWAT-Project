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

#ifndef CORE_TOOLS_TW_DATAFILES_MAP_DATAFILE_H
#define CORE_TOOLS_TW_DATAFILES_MAP_DATAFILE_H


#include <string>
#include <vector>
#include <map>


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

		struct TwMapDataFileItemInfo
		{
			int m_type;
			int m_start;
			int m_num;
		};

		struct TwMapDataFileItemRaw
		{
			int m_typeAndId;
			int m_size;
		};

		struct TwMapDataFileItemExt
		{
			int m_type;
			int m_id;
			int m_size;
			char *m_data;
		};

		struct TwMapDataFileInfo
		{
			std::vector<TwMapDataFileItemInfo> m_typesInfo;
			std::vector<int> m_itemOffsets;
			std::vector<int> m_compressedDataOffsets;
			std::vector<int> m_uncompressedDataSizes;
		};

		struct TwMapDataFile
		{
			TwMapDataFileHeader m_header;
			TwMapDataFileInfo m_info;

			std::vector<TwMapDataFileItemExt> m_items;
			std::vector<char *> m_compressedDatas;
			std::map<int, char *> m_uncompressedDatas;
		};

		class CTwMapDataFileReader
		{
			TwMapDataFile *m_mapFile;

			CDataFileReader *m_dfReader;
			std::string m_path;

		public:
			CTwMapDataFileReader();
			~CTwMapDataFileReader();

			bool Open(const std::string &path);
			void Close();


			int NumData() const;
			int NumItems() const;
			int NumItemsOfType(int type) const;
			int StartOfType(int type) const;

			int DataSizeAt(int index) const;

			void *ItemAt(int index) const;
			void *DataAt(int index);

		private:
			bool UncompressData(int index);
		};

		class CTwMapDataFileWriter
		{

		};
	}
}



#endif // CORE_TOOLS_TW_DATAFILES_MAP_DATAFILE_H
