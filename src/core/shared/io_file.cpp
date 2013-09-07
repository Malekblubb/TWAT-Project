/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "io_file.h"
#include <cstdio>


TWAT::CIOFile::CIOFile(const std::string &path, int mode)
{
	this->Open(path, mode);
}

TWAT::CIOFile::~CIOFile()
{
	m_stream.close();
}

void TWAT::CIOFile::Open(const std::string &path, int mode)
{
	m_path = path;
	m_mode = mode;

	switch(m_mode)
	{
		case READ:
			m_stream.open(m_path, std::ios::in);
			break;
		case WRITE:
			m_stream.open(m_path, std::ios::out | std::ios::app);
			break;
		case NEW:
			m_stream.open(m_path, std::ios::out);
			break;
		default:
			break;
	}
}

void TWAT::CIOFile::Close()
{
	m_stream.close();
}

bool TWAT::CIOFile::Exists() const
{
	if(m_stream.is_open())
		return true;

	return false;
}

bool TWAT::CIOFile::Delete() const
{
	if(std::remove(m_path.c_str()) == 0)
		return true;

	return false;
}

void TWAT::CIOFile::Create()
{
	m_stream.close();
	m_stream.open(m_path, std::ios::out);

	if(m_mode == READ)
	{
		// open again for read access
		m_stream.close();
		m_stream.open(m_path, std::ios::in);
	}
}

void TWAT::CIOFile::Write(const std::string &buf, int mode)
{
	if(mode == OVERWRITE)
	{
		// open new for overwrite
		m_stream.close();
		m_stream.open(m_path, std::ios::out | std::ios::trunc);
	}

	m_stream << buf;
}

bool TWAT::CIOFile::ReadLine(std::string *buf)
{
	if(std::getline(m_stream, *buf) == 0)
		return false;

	return true;
}

void TWAT::CIOFile::Read(int from, int to, std::string *buf)
{
	int length = to - from;
	char tmp;

	m_stream.seekg(from);

	while(length--)
	{
		m_stream.read(&tmp, 1);
		*buf += tmp;
	}
}
