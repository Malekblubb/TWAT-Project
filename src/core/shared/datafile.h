/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef DATAFILE_H
#define DATAFILE_H


#include <fstream>
#include <string>


namespace TWAT
{
	class CDataFileReader
	{
		std::string m_path;
		std::ifstream m_stream;

	public:
		CDataFileReader() {}
		CDataFileReader(const std::string &path);

		bool Open(const std::string &path);
		void Close();

		int Read(int from, int to, unsigned char *buf);
	};

}
#endif // DATAFILE_H
