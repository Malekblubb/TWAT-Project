/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "info_decoder.h"

#include "server.h"
#include "master.h"

#include <base/system.h>

#include <core/tw_stripped/packer.h>

#include <cstring>


bool TWAT::TwTools::CRawInfoDecoder::DecodeServerInfo(unsigned char *data, int dataLen, int token, ServerInfo *inf)
{
	inf->m_isValid = false;

	if(dataLen < 14)
		return false;

	CUnpacker up;
	up.Reset((unsigned char*)data + 14, dataLen - 14);

	std::string tok  = up.GetString();
	if(tok != std::to_string(token))
		return false;
	

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

	for(int i = 0; i < inf->m_numClients; ++i)
	{
		ClientInfo tmpCl;

		tmpCl.m_name = up.GetString();
		tmpCl.m_clan = up.GetString();
		tmpCl.m_country = std::stoi(up.GetString());
		tmpCl.m_score = std::stoi(up.GetString());
		tmpCl.m_isPlayer = std::stoi(up.GetString());

		inf->m_clients.push_back(tmpCl);
	}

	inf->m_isValid = true;
	return true;
}

bool TWAT::TwTools::CRawInfoDecoder::DecodeListInfo(unsigned char *data, int dataLen, CMasterList *lst)
{
	// pk-data:		{255, 255, 255, 255, 255, 255, 255, 255, 255, 255, l, i, s, 2, addr_data[num_packs]}

	// addr_data:	Ip4: {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 255, 255, ip[0], ip[1], ip[2], ip[3], port[0], port[1]}
	//				Ip6: {ip, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip, port[0], port[1]}

	// port decode: port[1] * 0xff + port[1] + port[2]

	if(dataLen < 14)
		return false; // invalid data

	static unsigned char ip4Spacer[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff};
	std::string addr;
	int chunkSize = 0;

	for(int i = 14; i < dataLen; i += 18)
	{
		++chunkSize;

		bool isIp4 = std::memcmp(data + i, ip4Spacer, sizeof ip4Spacer) == 0 ? true : false;

		// process ip
		if(isIp4)
			addr = System::RawIpToStr(System::IP4, data + i + 12);
		else
			addr = System::RawIpToStr(System::IP6, data + i); // TODO: test this


		// process port
		int port = (int)(data[i + 16] * 0xff + data[i + 16]) + (int)data[i + 17];
		addr += ":" + std::to_string(port);

		lst->AddAddr(addr);
	}

	// most time one chunk contains 75 ip adresses
	lst->AddChunkSize(chunkSize);

	return true;
}

int TWAT::TwTools::CRawInfoDecoder::DecodeCountInfo(unsigned char *data, int dataLen)
{
	// pk-data: {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, s, i, z, 2, count_data_high, count_data_low} = 16

	if(dataLen < 16)
		return -1;

	// decode like: high * 255 + high + low
	return (data[14] * 0xff + data[14]) + data[15];
}
