/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef IO_FILE_H
#define IO_FILE_H


#include <string>
#include <fstream>


namespace TWAT
{
	enum Modes
	{
		// writemodes
		APPEND = 0,
		OVERWRITE,

		// openmodes (text only)
		READ = 0,
		WRITE
	};


	class CIOFile
	{
		std::string m_Path;
		std::fstream m_Stream;

	public:
		// open a file, mode WRITE will append if possible
		CIOFile(const std::string &path, int mode);
		~CIOFile();
		void Close();

		bool Exists() const;
		bool Delete() const;

		// read and write only for TEXT files
		void Write(const std::string &buf, int mode);
		void ReadLine(std::string *buf);
		void Read(int from, int to, std::string *buf);
	};
}

#endif // IO_FILE_H
