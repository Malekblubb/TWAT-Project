/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "graphics.h"


#include <cstring>
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
