#include "client.h"

#include "../base/app_info.h"
#include <iostream>



TWAT::CClient::CClient()
{
	// setup
	m_Config = new CConfig(APP_CONF_PATH);
}

void TWAT::CClient::OnInit()
{
	// check first start and other

}
