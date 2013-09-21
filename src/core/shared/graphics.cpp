/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "graphics.h"

#include <sstream>
#include <pnglite/pnglite.h>


int TWAT::CPng::RawDataFromFile(const std::string &path, unsigned char *&buf)
{
	png_t png;

	png_init(0, 0);
	if(png_open_file_read(&png, path.c_str()) != PNG_NO_ERROR)
		return 0;

	// alloc mem
	int len = png.width * png.height * png.bpp;
	buf = new unsigned char[len];

	if(png_get_data(&png, buf) != PNG_NO_ERROR)
		return 0;

	png_close_file(&png);
	return len;
}

bool TWAT::CPng::SaveTo(const std::string &path, int height, int width, unsigned char *data)
{
	png_t png;

	png_init(0, 0);

	if(png_open_file_write(&png, path.c_str()) != PNG_NO_ERROR)
		return false;

	png_set_data(&png, width, height, 8, PNG_TRUECOLOR_ALPHA, data);
	png_close_file(&png);

	return true;
}


TWAT::CColor::CColor() :
	m_r(0),
	m_g(0),
	m_b(0),
	m_a(0)
{

}

TWAT::CColor::CColor(int r, int g, int b, int a) :
	m_r(r),
	m_g(g),
	m_b(b),
	m_a(a)
{

}

TWAT::CColor::CColor(const std::string &hexString) : CColor()
{
	if(!hexString.empty())
	{
		if(hexString.length() == 6)
		{
			std::stringstream stream;
			int hexV;

			stream << hexString;
			stream >> std::hex >> hexV;

			m_r = (hexV >> 16) & 0xff;
			m_g = (hexV >> 8) & 0xff;
			m_b = hexV & 0xff;
			m_a = 255;
		}
	}
}
