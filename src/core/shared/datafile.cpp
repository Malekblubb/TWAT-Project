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
	m_stream.open(path, std::ios::in | std::ios::binary);

	if(!m_stream.is_open())
		return false;

	return true;
}

void TWAT::CDataFileReader::Close()
{
	m_stream.close();
}

int TWAT::CDataFileReader::Read(int from, int to, unsigned char *buf)
{
	int length = to - from;

	m_stream.seekg(from);
	m_stream.read(reinterpret_cast<char *>(buf), length);

	return m_stream.tellg();
}
