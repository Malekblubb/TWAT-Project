/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_TOOLS_TW_NET_INFO_DECODER_H
#define CORE_TOOLS_TW_NET_INFO_DECODER_H


#include <string>


namespace TWAT
{
	namespace TwTools
	{
		class CRawInfoDecoder
		{
		public:
			static bool DecodeServerInfo(unsigned char *data, int dataLen, int token, struct ServerInfo *inf);
			static bool DecodeListInfo(unsigned char *data, int dataLen, class CMasterList *lst);
			static int DecodeCountInfo(unsigned char *data, int dataLen);
		};
	}
}


#endif // CORE_TOOLS_TW_NET_INFO_DECODER_H
