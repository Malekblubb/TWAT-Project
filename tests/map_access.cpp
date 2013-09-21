/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include <iostream>

#include <core/tools/tw/datafiles/map.h>
#include <core/tw_stripped/mapitems.h>

using namespace std;
using namespace TWAT::TwTools;


int main()
{
	CTwMap twMap;
	twMap.Load("/home/hax/.teeworlds/maps/test2.map");


	if(twMap.IsValid())
	{
		cout << "Author: " << twMap.Info().Author() << endl;
		cout << "Version: " << twMap.Info().Version() << endl;
		cout << "Credits: " << twMap.Info().Credits() << endl;
		cout << "License: " << twMap.Info().License() << endl << endl;


		for(int g = 0; g < twMap.NumGroups(); ++g)
		{
			CTwMapGroup *tmpGroup = twMap.Group(g);

			cout << "[" << tmpGroup->Name() << " " << g << "]" << endl;

			for(int l = 0; l < tmpGroup->NumLayers(); ++l)
			{
				CTwMapLayer *tmpLayer = tmpGroup->Layer<CTwMapLayer>(l);

				if(tmpLayer->Type() == LAYERTYPE_TILES)
				{
					CTwMapLayerTiles *tmpTilesLayer = tmpGroup->Layer<CTwMapLayerTiles>(l);

					cout << "	[" << tmpTilesLayer->Name() << " " << l << " (" << tmpTilesLayer->Height() << "x" << tmpTilesLayer->Width() << ")]" << endl;

					if(tmpTilesLayer->HasImage())
					{
						CTwMapImage *tmpImage = tmpTilesLayer->Image();

						cout << "		[Image \"" << tmpImage->Name() << "\" (" << tmpImage->Height() << "x" << tmpImage->Width() << ")]" << endl;
					}
				}

				if(tmpLayer->Type() == LAYERTYPE_QUADS)
				{
					CTwMapLayerQuads *tmpQuadsLayer = tmpGroup->Layer<CTwMapLayerQuads>(l);

					cout << "	[" << tmpQuadsLayer->Name() << " " << l << "]" << endl;

					if(tmpQuadsLayer->HasImage())
					{
						CTwMapImage *tmpImage = tmpQuadsLayer->Image();

						cout << "		[Image \"" << tmpImage->Name() << "\" (" << tmpImage->Height() << "x" << tmpImage->Width() << ")]" << endl;
					}
				}
			}
		}
	}
}
