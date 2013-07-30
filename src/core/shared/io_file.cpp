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
	m_Stream.close();
}

void TWAT::CIOFile::Open(const std::string &path, int mode)
{
	m_Path = path;
	m_Mode = mode;

	switch(m_Mode)
	{
		case READ:
			m_Stream.open(m_Path, std::ios::in);
			break;
		case WRITE:
			m_Stream.open(m_Path, std::ios::out | std::ios::app);
			break;
		case NEW:
			m_Stream.open(m_Path, std::ios::out);
			break;
		default:
			break;
	}
}

void TWAT::CIOFile::Close()
{
	m_Stream.close();
}

bool TWAT::CIOFile::Exists() const
{
	if(m_Stream.is_open())
		return true;

	return false;
}

bool TWAT::CIOFile::Delete() const
{
	if(std::remove(m_Path.c_str()) == 0)
		return true;

	return false;
}

void TWAT::CIOFile::Create()
{
	m_Stream.close();
	m_Stream.open(m_Path, std::ios::out);

	if(m_Mode == READ)
	{
		// open again for read access
		m_Stream.close();
		m_Stream.open(m_Path, std::ios::in);
	}
}

void TWAT::CIOFile::Write(const std::string &buf, int mode)
{
	if(mode == OVERWRITE)
	{
		// open new for overwrite
		m_Stream.close();
		m_Stream.open(m_Path, std::ios::out | std::ios::trunc);
	}

	m_Stream << buf;
}

bool TWAT::CIOFile::ReadLine(std::string *buf)
{
	if(std::getline(m_Stream, *buf) == 0)
		return false;

	return true;
}

void TWAT::CIOFile::Read(int from, int to, std::string *buf)
{
	int length = to - from;
	char *tmp = (char *)std::malloc(1);

	m_Stream.seekg(from);

	while(length--)
	{
		m_Stream.read(tmp, 1);
		*buf += (std::string)tmp;
	}

	std::free(tmp);
}
