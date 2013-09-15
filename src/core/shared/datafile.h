/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_DATAFILE_H
#define CORE_SHARED_DATAFILE_H


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
		bool Open(const class CIOFile &ioFile);
		void Close();

		bool IsOpen() const;
		long int Pos()  {return m_stream.tellg();}

		int Read(int from, int to, void *buf);
		int Read(void *buf, int length);
		void ResetPos();
	};

}
#endif // DATAFILE_H
