/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows/configwindow.h>
//#include "ui_configwindow.h"

#include <base/system.h>

#include <core/client/client.h>
#include <core/shared/config.h>

#include <core/client/components/serverbrowser.h>
#include <core/tools/tw/net/server.h>
#include <QMovie>
using namespace TWAT;


// Main_ui stuff like MenuBars, Close, Minimize, Maximize buttons in this file.
// Tool specific slots etc. stripped to other files.

// exit, init
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow), m_confWidow(new configwindow)
{
	// setup ui
	m_ui->setupUi(this);

	this->OnInit();
}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
	this->OnExit();
}

void MainWindow::OnInit()
{
	// twat client start
	m_client = new CClient();
	m_client->Init();

	// load user settings
	this->LoadConfVars();
}

void MainWindow::OnExit()
{
	// save config
	m_client->m_config->Save();

}

void MainWindow::SetStatus(const QString &text)
{
	m_ui->m_lbStatusbarStatusText->setText(text);
}

void MainWindow::ShowStatusIcon(bool b)
{
	if(b)
	{
		QMovie *m = new QMovie(":/img/animated/loading.gif");
		m->start();
		m_ui->m_lbStatusbarIcon->setMovie(m);
		m_ui->m_lbStatusbarIcon->show();
	}
	else
		m_ui->m_lbStatusbarIcon->hide();
}

void MainWindow::LoadConfVars()
{
	if(m_client->m_config->m_conf.GetVar<int>("ui_menu_expanded"))
		m_ui->m_twMainMenu->expandAll();

	if(m_client->m_config->m_conf.GetVar<int>("utl_use_default_masters"))
		m_client->m_twSrvBrowser->UseDefaultMasters(true);
}

void MainWindow::on_m_twMainMenu_clicked(const QModelIndex &index)
{
	if(index.parent().isValid())
		m_ui->m_swMain->setCurrentIndex(index.parent().row() + index.row());
}

void MainWindow::on_m_pbBottomMenuSettings_clicked()
{
	m_confWidow->Show(m_client->m_config);
}
