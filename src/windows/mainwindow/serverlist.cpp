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


void MainWindow::RefreshSrvBrowserTable()
{
	QCoreApplication::processEvents(); // unfreeze ui
	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // wait until we got expcount

	if(m_client->m_twSrvBrowser->IsRefreshing())
	{
		this->SetStatus("Refreshing serverlist... 0/" + QString::number(m_client->m_twSrvBrowser->ExpCount()));
		this->ShowStatusIcon(true);

		std::this_thread::sleep_for(std::chrono::milliseconds(m_client->m_twSrvBrowser->ExpCount()) * 3); // wait until we got some srvs

		for(int i = 0; i < m_client->m_twSrvBrowser->NumServers(); ++i)
		{
			QCoreApplication::processEvents(); // unfreeze ui

			QString format = QString("Refreshing serverlist... %1/%2 (%3%)").arg(m_client->m_twSrvBrowser->NumServers()).
					arg(m_client->m_twSrvBrowser->ExpCount()).arg(m_client->m_twSrvBrowser->Percentage());
			this->SetStatus(format);

			if(m_client->m_twSrvBrowser->IsRefreshing())
				std::this_thread::sleep_for(std::chrono::milliseconds(25)); // give him some time to send, rcv, decode, when refreshing

			// add the data to table
			this->AddServerInfoRow(m_client->m_twSrvBrowser->At(i), i);
		}

		QString format = QString("Refreshed %1 servers in %2 seconds").arg(m_client->m_twSrvBrowser->NumServers()).arg(m_client->m_twSrvBrowser->RefreshTime());
		this->SetStatus(format);
	}
	else
		this->SetStatus("Error while refresh serverlist");

	this->ShowStatusIcon(false);
	m_ui->m_pbSrvListRefresh->setEnabled(true);
}

void MainWindow::AddServerInfoRow(TwTools::ServerInfo *inf, int row)
{
	QTableWidgetItem *name = new QTableWidgetItem(inf->m_name.c_str());
	QTableWidgetItem *gametype = new QTableWidgetItem(inf->m_gameType.c_str());
	gametype->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem *map = new QTableWidgetItem(inf->m_mapName.c_str());
	map->setTextAlignment(Qt::AlignCenter);
	QString playerformat = QString("%1/%2").arg(inf->m_numClients).arg(inf->m_maxClients);
	QTableWidgetItem *players = new QTableWidgetItem(playerformat);
	players->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem *ping = new QTableWidgetItem(std::to_string(inf->m_latency).c_str());
	ping->setTextAlignment(Qt::AlignRight);

	m_ui->m_twSrvListList->insertRow(row);
	m_ui->m_twSrvListList->setItem(row, 0, name);
	m_ui->m_twSrvListList->setItem(row, 1, gametype);
	m_ui->m_twSrvListList->setItem(row, 2, map);
	m_ui->m_twSrvListList->setItem(row, 3, players);
	m_ui->m_twSrvListList->setItem(row, 4, ping);
}

void MainWindow::on_m_pbSrvListRefresh_clicked()
{
	m_ui->m_twSrvListList->setRowCount(0);
	m_ui->m_pbSrvListRefresh->setEnabled(false);

	m_workerThread = new std::thread(&CTwServerBrowser::RefreshList, m_client->m_twSrvBrowser);
	m_workerThread->detach();
	this->RefreshSrvBrowserTable();
}

void MainWindow::on_m_twSrvListList_clicked(const QModelIndex &index)
{
	m_ui->m_twSrvListPlayerList->setRowCount(0);
	m_ui->m_twSrvListPlayerList->setColumnWidth(0, 60);

	for(int i = 0; i < m_client->m_twSrvBrowser->At(index.row())->m_numClients; ++i)
	{
		QTableWidgetItem *score = new QTableWidgetItem(QString::number(m_client->m_twSrvBrowser->At(index.row())->m_clients[i].m_score));
		QTableWidgetItem *name = new QTableWidgetItem(m_client->m_twSrvBrowser->At(index.row())->m_clients[i].m_name.c_str());

		m_ui->m_twSrvListPlayerList->insertRow(i);
		m_ui->m_twSrvListPlayerList->setItem(i, 0, score);
		m_ui->m_twSrvListPlayerList->setItem(i, 1, name);
	}
}

void MainWindow::on_m_leSrvListSearchBar_textChanged(const QString &arg1)
{
	for(int i = 0; i < m_ui->m_twSrvListList->rowCount(); ++i)
	{
		// name
		if(m_ui->m_twSrvListList->item(i, 0)->text().toLower().contains(arg1.toLower()))
			m_ui->m_twSrvListList->setCurrentItem(m_ui->m_twSrvListList->item(i, 0));
	}
}
