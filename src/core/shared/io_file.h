/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_SHARED_IO_FILE_H
#define CORE_SHARED_IO_FILE_H


#include <string>
#include <fstream>


namespace TWAT
{
	class CIOFile
	{
		std::string m_path;
		int m_mode;
		std::fstream m_stream;

	public:
		// open a file, mode WRITE will append if possible
		CIOFile(const std::string &path, int mode);
		~CIOFile();

		void Open(const std::string &path, int mode);
		void Close();

		std::string Path() const {return m_path;}
		bool Exists() const;
		bool Delete() const;
		void Create();

		// read and write only for TEXT files
		void Write(const std::string &buf, int mode);
		bool ReadLine(std::string *buf);
		void Read(int from, int to, std::string *buf);


		enum Modes
		{
			// writemodes
			APPEND = 0,
			OVERWRITE,

			// openmodes (text only, Exists() and Delete() also for non text-files)
			READ = 0,
			WRITE,
			NEW
		};
	};
}

#endif // IO_FILE_H
