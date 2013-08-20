/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <string>
#include <QMainWindow>


namespace TWAT
{
	class CClient;
}

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void OnInit();
	void OnExit();
	void SetStatus(const std::string &status);

	// slots
private slots:

	void on_m_twMainMenu_clicked(const QModelIndex &index);

	// ----- serverlist -----

	void on_m_pbSrvListRefresh_clicked();

private:
	Ui::MainWindow *m_ui;

protected:
	TWAT::CClient *m_client;
};


#endif // MAINWINDOW_H
