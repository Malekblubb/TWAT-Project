/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "../windows/mainwindow.h"
//#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
//	TWAT::CClient *client = new TWAT::CClient();

	w.show();
//	client->OnInit();

	return a.exec();
}
