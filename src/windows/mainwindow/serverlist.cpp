/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <core/client/client.h>

#include <core/shared/twserverbrowser.h>

#include <core/tools/tw/net/server.h>

#include <QTimer>

using namespace TWAT;


CUiServerList::CUiServerList(Ui::MainWindow *ui, MainWindow *window) : m_ui(ui), m_mainWindow(window)
{
	m_timer = new QTimer();

	connect(m_timer, SIGNAL(timeout()), this, SLOT(RefreshTable())); // refresh table when timer timed out
	connect(this, SIGNAL(TableRefreshed(bool)), this, SLOT(OnRefreshFinished(bool)));
}

void CUiServerList::OnRefreshClicked()
{
	m_mainWindow->SetStatus("Refreshing serverlist...");
	m_mainWindow->ShowStatusIcon(true);
	m_ui->m_twSrvListList->setRowCount(0);
	m_ui->m_pbSrvListRefresh->setEnabled(false);

	m_timer->start(5000);
	m_mainWindow->m_workerThread = new std::thread(&ITwServerBrowser::Refresh, m_mainWindow->Client()->TwServerBrowser());
}

void CUiServerList::RefreshTable()
{
	m_timer->stop();

	// TODO: maybe rework this one day...
	if(m_mainWindow->Client()->TwServerBrowser()->IsRefreshing())
	{
		for(int i = 0; i < m_mainWindow->Client()->TwServerBrowser()->NumServers(); ++i)
		{
			QCoreApplication::processEvents(); // unfreeze ui

			if(m_mainWindow->Client()->TwServerBrowser()->IsRefreshing())
				std::this_thread::sleep_for(std::chrono::milliseconds(25)); // give him some time to send, rcv, decode, when refreshing

			m_ui->m_lbSrvListStatus->setText(QString("Refreshed %1/%2 servers (%3%)").
											 arg(m_mainWindow->Client()->TwServerBrowser()->NumServers()).
											 arg(m_mainWindow->Client()->TwServerBrowser()->ExpCount()).
											 arg(m_mainWindow->Client()->TwServerBrowser()->PercentageFinished()));

			// add the data to table
			this->AddServerInfoRow(m_mainWindow->Client()->TwServerBrowser()->At(i), i);
		}
		emit TableRefreshed(true);
	}
	else
		emit TableRefreshed(false);
}

void CUiServerList::AddServerInfoRow(TwTools::ServerInfo *inf, int row)
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

void CUiServerList::OnRefreshFinished(bool success)
{
	if(success)
		m_ui->m_lbSrvListStatus->setText(QString("Refreshed %1 servers in %2 seconds").
								arg(m_mainWindow->Client()->TwServerBrowser()->NumServers()).
								arg(m_mainWindow->Client()->TwServerBrowser()->RefreshTime()));

	else
		m_ui->m_lbSrvListStatus->setText("Refresh failed");

	m_mainWindow->SetStatus("Servers refreshed");
	m_mainWindow->ShowStatusIcon(false);
	m_ui->m_pbSrvListRefresh->setEnabled(true);
	m_mainWindow->m_workerThread->join();
}

void CUiServerList::OnTableEntryClicked(const QModelIndex &index)
{
	// server info
	m_ui->m_lbSrvListServerInfoIpVar->setText(m_mainWindow->Client()->TwServerBrowser()->At(index.row())->m_addr.c_str());
	m_ui->m_lbSrvListServerInfoVersionVar->setText(m_mainWindow->Client()->TwServerBrowser()->At(index.row())->m_version.c_str());


	// player info
	m_ui->m_twSrvListPlayerList->setRowCount(0);
	m_ui->m_twSrvListPlayerList->setColumnWidth(0, 60);

	for(int i = 0; i < m_mainWindow->Client()->TwServerBrowser()->At(index.row())->m_numClients; ++i)
	{
		QTableWidgetItem *score = new QTableWidgetItem(QString::number(m_mainWindow->Client()->TwServerBrowser()->At(index.row())->m_clients[i].m_score));
		QTableWidgetItem *name = new QTableWidgetItem(m_mainWindow->Client()->TwServerBrowser()->At(index.row())->m_clients[i].m_name.c_str());

		m_ui->m_twSrvListPlayerList->insertRow(i);
		m_ui->m_twSrvListPlayerList->setItem(i, 0, score);
		m_ui->m_twSrvListPlayerList->setItem(i, 1, name);
	}
}

void CUiServerList::OnTestServerClicked()
{
	if(!m_ui->m_twSrvListList->selectedItems().empty())
	{
		// switch page
		m_ui->m_swMain->setCurrentIndex(9);
		m_ui->m_twMainMenu->setCurrentIndex(m_ui->m_twMainMenu->indexAt(QPoint(9, 0)));

		emit TestServerRequest(m_mainWindow->Client()->TwServerBrowser()->At(m_ui->m_twSrvListList->selectedItems().at(0)->row())->m_addr.c_str());
	}
	else
	{

	}
}

void CUiServerList::Search(const QString &text)
{
	for(int i = 0; i < m_ui->m_twSrvListList->rowCount(); ++i)
	{
		// name
		if(m_ui->m_twSrvListList->item(i, 0)->text().toLower().contains(text.toLower()))
			m_ui->m_twSrvListList->setCurrentItem(m_ui->m_twSrvListList->item(i, 0));
	}
}
