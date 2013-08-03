/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include <windows/mainwindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	w.show();

	return a.exec();
}
