/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows/configwindow.h>

#include <base/system.h>

#include <core/client/client.h>
#include <core/shared/config.h>
#include <core/shared/config_storage.h>

#include <core/shared/twserverbrowser.h>
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
	m_client = CClient::CreateClient();
	Client()->Init();

	// load user settings
	this->LoadConfVars();

	// change non-designer properties
	this->ChangeUiElements();
}

void MainWindow::OnExit()
{
	// save config
	Client()->Config()->Save();

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
	if(Client()->Config()->Store()->GetVar<int>("ui_menu_expanded"))
		m_ui->m_twMainMenu->expandAll();

	if(Client()->Config()->Store()->GetVar<int>("utl_use_default_masters"))
		m_client->ServerBrowser()->UseDefaultMasters(true);
}

void MainWindow::ChangeUiElements()
{
	m_ui->m_twSrvListList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_m_twMainMenu_clicked(const QModelIndex &index)
{
	if(index.parent().isValid())
		m_ui->m_swMain->setCurrentIndex(index.parent().row() + index.row());
}

void MainWindow::on_m_pbBottomMenuSettings_clicked()
{
	m_confWidow->Show(Client()->Core());
}
