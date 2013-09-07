/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_TOOLS_TW_DATAFILES_MAP_H
#define CORE_TOOLS_TW_DATAFILES_MAP_H


#include <string>


namespace TWAT
{
	namespace TwTools
	{
		// extended map access

		class CTwMapGroup
		{

		};

		class CTwMapLayer
		{
			int m_type;

			int m_height;
			int m_width;

		public:
			// setters
			void SetSize(int height, int width);

			// getters
			int Height() const {return m_height;}
			int Width() const {return m_width;}
		};

		class CTwMapLayerTiles : public CTwMapLayer
		{

		};

		class CTwMapLayerQuads : public CTwMapLayer
		{

		};


		class CTwMap
		{
			class CTwMapDataFileReader *m_reader;
			class CTwMapDataFileWriter *m_writer;

			std::string m_path;

		public:
			CTwMap();
			CTwMap(const std::string &path);
			~CTwMap();

			// loades a map from the given path
			//		returns:
			//				true:	on success
			//				false:	on failure
			bool Load(const std::string &path);

			// closes the map and writes down the changes
			void Close();


			enum CTwMapLayerTypes
			{
				LAYERTYPE_INVALID = 0,
				LAYERTYPE_GAME,
				LAYERTYPE_TILES,
				LAYERTYPE_QUADS
			};
		};
	}
}

#endif // CORE_TOOLS_TW_DATAFILES_MAP_H
