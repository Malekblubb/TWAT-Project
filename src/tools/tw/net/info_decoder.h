/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef INFO_DECODER
#define INFO_DECODER



namespace TWAT
{
	namespace TwTools
	{
		class CRawInfoDecoder
		{
		public:
			static bool DecodeServerInfo(unsigned char *data, int dataLen, class ServerInfo *inf);
			static bool DecodeListInfo(unsigned char *data);
			static int DecodeCountInfo(unsigned char *data, int dataLen);
		};
	}
}


#endif // INFO_DECODER
