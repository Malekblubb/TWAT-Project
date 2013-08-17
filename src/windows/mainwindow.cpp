/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <core/shared/network.h>
#include <tools/tw/net/server_util.h>
#include <tools/tw/net/master.h>
#include <base/system.h>

using namespace TWAT;


// Main_ui stuff like MenuBars, Close, Minimize, Maximize buttons in this file.
// Tool specific slots etc. stripped to other files.

// exit, init
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	this->OnInit();

	//	int sock = System::UdpSock();
	//	System::CIpAddr *addr = new System::CIpAddr("83.133.105.76:2222");
	//	System::CIpAddr *from = new System::CIpAddr();

	//	NetworkPacket *pk = new NetworkPacket(addr, (void *)SERVERBROWSE_GETINFO, 9);
	//	NetworkPacket *recPk = new NetworkPacket(1024);

	//	CNetworkBase::MakeConnless(pk);
	//	CNetworkBase::Send(sock, pk);
	//	std::cout << CNetworkBase::Recv(sock, recPk, from) << (unsigned char*)recPk->m_data<< std::endl;

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

void MainWindow::on_m_twMainMenu_clicked(const QModelIndex &index)
{
	m_ui->m_widgetMainStacked->setCurrentIndex(index.parent().row() + index.row());
}

void MainWindow::on_pushButton_2_clicked()
{
}
