/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "datafile.h"


TWAT::CDataFileReader::CDataFileReader(const std::string &path)
{
	this->Open(path);
}

bool TWAT::CDataFileReader::Open(const std::string &path)
{
	m_Stream.open(path, std::ios::in | std::ios::binary);

	if(!m_Stream.is_open())
		return false;

	return true;
}

void TWAT::CDataFileReader::Close()
{
	m_Stream.close();
}

int TWAT::CDataFileReader::Read(int from, int to, unsigned char *buf)
{
	int length = to - from;

	m_Stream.seekg(from);
	m_Stream.read(reinterpret_cast<char *>(buf), length);

	return m_Stream.tellg();
}
