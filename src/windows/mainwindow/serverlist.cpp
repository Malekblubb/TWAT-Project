/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <base/system.h>

#include <core/client/client.h>
#include <core/client/components/serverbrowser.h>

#include <core/tools/tw/net/server.h>

using namespace TWAT;


void MainWindow::RefreshSrvBrowserUiList()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // wait until we got expcount

	if(m_client->m_twSrvBrowser->IsRefreshing())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(m_client->m_twSrvBrowser->ExpCount()) * 3); // wait until we got some srvs

		for(int i = 0; i < m_client->m_twSrvBrowser->NumServers(); ++i)
		{
			QCoreApplication::processEvents(); // unfreeze ui

			if(m_client->m_twSrvBrowser->IsRefreshing()) // give him some time to send, rcv, decode, when refreshing
				std::this_thread::sleep_for(std::chrono::milliseconds(25));


			// add the data to table
			QTableWidgetItem *name = new QTableWidgetItem(m_client->m_twSrvBrowser->At(i)->m_name.c_str());
			QTableWidgetItem *gametype = new QTableWidgetItem(m_client->m_twSrvBrowser->At(i)->m_gameType.c_str());
			QTableWidgetItem *map = new QTableWidgetItem(m_client->m_twSrvBrowser->At(i)->m_mapName.c_str());
			QString format = QString("%1/%2").arg(m_client->m_twSrvBrowser->At(i)->m_numClients).arg(m_client->m_twSrvBrowser->At(i)->m_maxClients);
			QTableWidgetItem *players = new QTableWidgetItem(format);
			QTableWidgetItem *ping = new QTableWidgetItem(std::to_string(m_client->m_twSrvBrowser->At(i)->m_latency).c_str());

			m_ui->m_twSrvListList->insertRow(i);
			m_ui->m_twSrvListList->setItem(i, 0, name);
			m_ui->m_twSrvListList->setItem(i, 1, gametype);
			m_ui->m_twSrvListList->setItem(i, 2, map);
			m_ui->m_twSrvListList->setItem(i, 3, players);
			m_ui->m_twSrvListList->setItem(i, 4, ping);
		}

		QString format = QString("Refreshed %1 servers in %2 seconds").arg(m_client->m_twSrvBrowser->NumServers()).arg(m_client->m_twSrvBrowser->RefreshTime());
		this->SetStatus(format);
		this->ShowStatusIcon(false);
		m_ui->m_pbSrvListRefresh->setEnabled(true);
	}
}

void MainWindow::on_m_pbSrvListRefresh_clicked()
{
	m_ui->m_twSrvListList->setRowCount(0);
	m_ui->m_pbSrvListRefresh->setEnabled(false);
	this->SetStatus("Refreshing serverlist...");
	this->ShowStatusIcon(true);

	m_workerThread = new std::thread(&CTwServerBrowser::RefreshList, m_client->m_twSrvBrowser);
	m_workerThread->detach();
	this->RefreshSrvBrowserUiList();
}

void MainWindow::on_m_twSrvListList_clicked(const QModelIndex &index)
{
	m_ui->m_lwSrvListPlayers->clear();

	for(int i = 0; i < m_client->m_twSrvBrowser->At(index.row())->m_numClients; ++i)
	{
		m_ui->m_lwSrvListPlayers->addItem(m_client->m_twSrvBrowser->At(index.row())->m_clients[i].m_name.c_str());
	}
}
