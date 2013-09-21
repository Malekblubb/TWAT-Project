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

	class CColor
	{
		int m_r;
		int m_g;
		int m_b;
		int m_a;

	public:
		CColor();
		CColor(int r, int g, int b, int a = 255);
		CColor(const std::string &hexString);

		void SetRgba(int r, int g, int b, int a = 255);

		int Red() const {return m_r;}
		int Green() const {return m_g;}
		int Blue() const {return m_b;}
		int Alpha() const {return m_a;}
	};

}



#endif // CORE_SHARED_GRAPHICS_H
