/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "twmapeditor.h"

#include <core/tools/tw/datafiles/map.h>


TWAT::CTwMapEditor::CTwMapEditor() :
	m_map(new TwTools::CTwMap)
{

}

TWAT::CTwMapEditor::~CTwMapEditor()
{
	delete m_map;
}

bool TWAT::CTwMapEditor::Load(const std::string &path)
{
	if(!m_map->Load(path))
		return false;


}
