#ifndef IO_FILE_H
#define IO_FILE_H


#include <string>
#include <fstream>


namespace TWAT
{
	enum WriteModes
	{
		APPEND = 0,
		OVERWRITE
	};


	class CIOFile
	{
		std::string m_Path;
		std::fstream m_Stream;

	public:
		CIOFile(const std::string &path);

		bool Exists();
		bool Delete();

		// read and write only for TEXT files
		void WriteLine(const std::string &line, int mode);
		void ReadLine(std::string *buf);
		void Read(int from, int to, std::string *buf);
	};
}

#endif // IO_FILE_H
