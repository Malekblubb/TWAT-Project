/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */


#ifndef BASE_APP_INFO_H
#define BASE_APP_INFO_H


#include "system.h"


// some main infos
namespace TWAT
{
#define TWAT_SRV_IP "37.221.194.71"

#define APP_VERSION "1.0.0a"
#define APP_WORK_PATH System::WorkDir()
#define APP_CONF_PATH APP_WORK_PATH + "config.cfg"
#define APP_BIN_PATH APP_WORK_PATH + "bin"
#define APP_HTTP_PATH ""
}


#endif // BASE_APP_INFO_H
