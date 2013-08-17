/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "info_decoder.h"
#include "server_util.h"

#include <core/tw_stripped/packer.h>


bool TWAT::TwTools::CRawInfoDecoder::DecodeServerInfo(unsigned char *data, int dataLen, ServerInfo *inf)
{
	if(dataLen < 14)
		return false;

	CUnpacker up;
	int tok = 0;

	up.Reset((unsigned char*)data + 14, dataLen - 14);
	tok = std::stoi(up.GetString());
	inf->m_version = up.GetString();

	if(inf->m_version.substr(0, 3) != "0.6")
		return false;

	inf->m_name = up.GetString();
	inf->m_mapName = up.GetString();
	inf->m_gameType = up.GetString();
	inf->m_flags = std::stoi(up.GetString());
	inf->m_numPlayers = std::stoi(up.GetString());
	inf->m_maxPlayers = std::stoi(up.GetString());
	inf->m_numClients = std::stoi(up.GetString());
	inf->m_maxClients = std::stoi(up.GetString());


	for(int i = 0; i < inf->m_numClients; i++)
	{
		ClientInfo tmpCl;

		tmpCl.m_name = up.GetString();
		tmpCl.m_clan = up.GetString();
		tmpCl.m_country = std::stoi(up.GetString());
		tmpCl.m_score = std::stoi(up.GetString());
		tmpCl.m_isPlayer = std::stoi(up.GetString());

		inf->m_clients.push_back(tmpCl);
	}

	return true;
}

bool TWAT::TwTools::CRawInfoDecoder::DecodeListInfo(unsigned char *data)
{

}

int TWAT::TwTools::CRawInfoDecoder::DecodeCountInfo(unsigned char *data, int dataLen)
{
	// pk-data: {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, s, i, z, 2, count_data_high, count_data_low} = 16

	if(dataLen < 16)
		return -1;

	// decode like: high * 255 + high + low
	return (data[14] * 0xff + data[14]) + data[15];
}
