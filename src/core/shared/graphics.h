/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_GRAPHICS_H
#define CORE_SHARED_GRAPHICS_H


#include <string>


namespace TWAT
{
	class CPng
	{
	public:
		static int RawDataFromFile(const std::string &path, unsigned char *&buf);
		static bool SaveTo(const std::string &path, int height, int width, unsigned char *data);
	};
}



#endif // CORE_SHARED_GRAPHICS_H
