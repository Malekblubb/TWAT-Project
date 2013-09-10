/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "datafile.h"
#include "io_file.h"


TWAT::CDataFileReader::CDataFileReader(const std::string &path)
{
	this->Open(path);
}

bool TWAT::CDataFileReader::Open(const std::string &path)
{
	m_stream.open(path, std::ios::in | std::ios::binary);

	if(!m_stream.is_open())
		return false;

	return true;
}

bool TWAT::CDataFileReader::Open(const CIOFile &ioFile)
{
	return this->Open(ioFile.Path());
}

void TWAT::CDataFileReader::Close()
{
	m_stream.close();
}

int TWAT::CDataFileReader::Read(int from, int to, void *buf)
{
	int length = to - from;
	long int startPos = 0;

	m_stream.seekg(from);
	startPos = m_stream.tellg();

	m_stream.read(reinterpret_cast<char *>(buf), length);

	return m_stream.tellg() - startPos;
}

int TWAT::CDataFileReader::Read(void *buf, int length)
{
	long int startPos = m_stream.tellg();

	m_stream.read(reinterpret_cast<char *>(buf), length);

	return m_stream.tellg() - startPos; // return the length not the position
}

void TWAT::CDataFileReader::ResetPos()
{
	m_stream.seekg(0);
}
