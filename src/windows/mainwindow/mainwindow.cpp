/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <base/system.h>

#include <core/client/client.h>
#include <core/shared/config.h>
#include <core/shared/network.h>

#include <tools/tw/net/server.h>
#include <tools/tw/net/master.h>

#include <core/client/serverlist.h>


using namespace TWAT;


// Main_ui stuff like MenuBars, Close, Minimize, Maximize buttons in this file.
// Tool specific slots etc. stripped to other files.

// exit, init
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	this->OnInit();
}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::OnInit()
{
	// twat client start
	m_client = new CClient();
	m_client->Init();

	// user settings
	m_ui->m_twMainMenu->expandAll();
}

void MainWindow::OnExit()
{
	// save config
	m_client->m_config->Save();
}

void MainWindow::SetStatus(const std::string &status)
{
	m_ui->m_lbStatusbarStatusText->setText(status.c_str());
}

void MainWindow::on_m_twMainMenu_clicked(const QModelIndex &index)
{
	if(index.parent().isValid())
		m_ui->m_widgetMainStacked->setCurrentIndex(index.parent().row() + index.row());
}

void MainWindow::on_m_pbSrvListRefresh_clicked()
{
	CTwServerBrowser browser;

	browser.UseDefaultMasters(true);
	browser.RefreshList();

	for(int i = 0; i < browser.NumServers(); i++)
		DBG("gametype: %", browser[i]->m_gameType);
}
