/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_TOOLS_TW_DATAFILES_MAP_H
#define CORE_TOOLS_TW_DATAFILES_MAP_H


#include <string>
#include <map>
#include <vector>


namespace TWAT
{
	namespace TwTools
	{
		// extended map access


		class CTwMapInfo
		{
			std::string m_author;
			std::string m_version;
			std::string m_credits;
			std::string m_license;

		public:
			CTwMapInfo();
			void Clear();

			// setters
			void SetAuthor(const std::string &author);
			void SetVersion(const std::string &version);
			void SetCredits(const std::string &credits);
			void SetLicense(const std::string &license);

			// getters
			std::string Author() const {return m_author;}
			std::string Version() const {return m_version;}
			std::string Credits() const {return m_credits;}
			std::string License() const {return m_license;}
		};

		class CTwMapImage
		{
			std::string m_name;
			int m_height;
			int m_width;
			bool m_external;
			void *m_data;

		public:
			CTwMapImage();

			// setters
			void SetName(const std::string &name);
			void SetSize(int height, int width);
			void SetData(void *data);

			// getters
			std::string Name() const {return m_name;}
			int Height() const {return m_height;}
			int Width() const {return m_width;}
			bool External() const {return m_external;}
			void *Data() const {return m_data;}
		};

		class CTwMapLayer
		{
			int m_type;
			bool m_hasImage;
			std::string m_name;
			CTwMapImage m_image;

		public:
			CTwMapLayer();

			// setters
			void SetType(int type);
			void SetName(const std::string &name);
			void SetImage(CTwMapImage image);

			// getters
			int Type() const {return m_type;}
			bool HasImage() const {return m_hasImage;}
			std::string Name() const {return m_name;}
			CTwMapImage *Image() {return &m_image;}
		};

		class CTwMapTile
		{

		};

		class CTwMapLayerTiles : public CTwMapLayer
		{
			int m_width;
			int m_height;

		public:
			// setters
			void SetSize(int height, int width);

			// getters
			int Height() const {return m_height;}
			int Width() const {return m_width;}
		};

		class CTwMapQuad
		{

		};

		class CTwMapLayerQuads : public CTwMapLayer
		{
			int m_numQuads;

			std::map<int, CTwMapQuad> m_quads;

		public:
			CTwMapLayerQuads();

			void SetQuad(int index, CTwMapQuad quad);

			int NumQuads() const {return m_numQuads;}
		};

		class CTwMapGroup
		{
			int m_offsetX;
			int m_offsetY;
			int m_paraX;
			int m_paraY;

			int m_numLayers;

			std::map<int, CTwMapLayer *> m_layers;

		public:
			CTwMapGroup();

			// setters
			void SetOffsetX(int offset);
			void SetOffsetY(int offset);
			void SetParaX(int para);
			void SetParaY(int para);

			// getters
			int OffsetX() const {return m_offsetX;}
			int OffsetY() const {return m_offsetY;}
			int ParaX() const {return m_paraX;}
			int ParaY() const {return m_paraY;}
			int NumLayers() const {return m_numLayers;}


			// layer inerface
			int NumTilesLayers();
			int NumQuadsLayers();

			void SetLayer(int index, CTwMapLayer *layer);
			template<typename LayerType> LayerType *Layer(int index)
			{
				if(index >= 0 && (m_layers.find(index) != m_layers.end()))
					return reinterpret_cast<LayerType *>(m_layers[index]); // return the requested layer addr

				return new LayerType(); // return a newly created obj with the default info
			}
		};


		class CTwMap
		{
			// datafile access variables
			class CTwMapDataFileReader *m_reader;
			class CTwMapDataFileWriter *m_writer;

			// map variables
			CTwMapInfo m_mapInfo;
			std::vector<CTwMapGroup> m_groups;

			bool m_validMap;
			std::string m_path;

			int m_numGroups;
			int m_groupsStart;
			int m_numLayers;
			int m_layersStart;
			int m_numImages;
			int m_imagesStart;




		public:
			CTwMap();
			CTwMap(const std::string &path);
			~CTwMap();

			// loads a map from the given path
			//		returns:
			//				true:	on success
			//				false:	on failure
			bool Load(const std::string &path);

			// closes the map and writes down the changes
			void Close();


			// setters

			// getters
			bool IsValid() const {return m_validMap;}
			std::string Path() const {return m_path;}



			// interfaces
			// info
			void SetInfo(const std::string &author, const std::string &version, const std::string &credits, const std::string &license);
			CTwMapInfo Info() const {return m_mapInfo;}

			// groups
			CTwMapGroup *Group(int index);
			int NumGroups() const {return m_numGroups;}


		private:
			// loads the info of the map (author, license...)
			// is called from this->Load
			void LoadInfo();

			// builds the main map structure
			// is called from this->Load
			void LoadStructure();

		public:


		};
	}
}

#endif // CORE_TOOLS_TW_DATAFILES_MAP_H
