/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <base/system.h>

#include <core/shared/twservertester.h>

#include <core/client/client.h>

#include <core/tools/tw/net/server.h>

#include <QMessageBox>
#include <QTimer>

using namespace TWAT;


CUiTestServer::CUiTestServer(Ui::MainWindow *ui, MainWindow *window) : m_ui(ui), m_mainWindow(window)
{
	m_timer = new QTimer();

	m_plotX.resize(1);
	m_plotY.resize(1);

	connect(this, SIGNAL(TestStart()), this, SLOT(StartTest()));
	connect(this, SIGNAL(TestStop()), this, SLOT(StopTest()));
	connect(m_timer, SIGNAL(timeout()), this, SLOT(RefreshStatistics()));
}

void CUiTestServer::OnSrvListSwitch(const QString &ip)
{
	m_ui->m_leTestSrvTargetIp->setText(ip);

	emit TestStart();
}

void CUiTestServer::OnStartClicked()
{
	emit TestStart();
}

void CUiTestServer::OnStopClicked()
{
	emit TestStop();
}

void CUiTestServer::StartTest()
{
	m_ip = m_ui->m_leTestSrvTargetIp->text();

	if(m_mainWindow->Client()->TwServerTester()->Reset(m_ip.toStdString()))
	{
		m_mainWindow->SetStatus(QString("Testing server %1...").arg(m_ip));
		m_mainWindow->ShowStatusIcon(true);

		this->SetUpUiInfos();
		this->Reset();

		m_timer->start(1000);
	}
	else
		QMessageBox::warning(m_mainWindow, "Error", "Can't connect to this server");

}

void CUiTestServer::StopTest()
{
	m_timer->stop();
	m_mainWindow->SetStatus("Testing stoped");
	m_mainWindow->ShowStatusIcon(false);
}

void CUiTestServer::SetUpUiInfos()
{
	m_ui->m_lbTestSrvStartTimeVar->setText(System::TimeStr().c_str());
	m_ui->m_lbTestSrvServerMod->setText(m_mainWindow->Client()->TwServerTester()->ServerInfo()->m_gameType.c_str());
	m_ui->m_lbTestSrvServerVersion->setText(m_mainWindow->Client()->TwServerTester()->ServerInfo()->m_version.c_str());
}

void CUiTestServer::RefreshStatistics()
{
	m_currentPing = m_mainWindow->Client()->TwServerTester()->Ping();

	this->RefreshUiInfos();
	++m_numPks;
}

void CUiTestServer::RefreshUiInfos()
{
	// refresh plot
	m_plotX[0] = m_numPks;
	m_plotY[0] = m_currentPing;

	m_ui->m_widgetTestSrvPlot->graph(0)->addData(m_plotX, m_plotY);
	m_ui->m_widgetTestSrvPlot->replot();
	m_ui->m_widgetTestSrvPlot->xAxis->setRange(m_numPks - 60, m_numPks); // scroll vertical

	// scroll horizontal
	if(m_currentPing > 500 || m_currentPing == 0) // massive jumps
		m_ui->m_widgetTestSrvPlot->yAxis->setRange(0, m_currentPing);
	else
		m_ui->m_widgetTestSrvPlot->yAxis->setRange( m_currentPing -10, m_currentPing + 20); // scroll horizontal


	// refresh labels
	m_ui->m_lbTestSrvDataSentVar->setText(QString::number(m_mainWindow->Client()->TwServerTester()->SentDataLen()));
	m_ui->m_lbTestSrvDataReceivedVar->setText(QString::number(m_mainWindow->Client()->TwServerTester()->RecDataLen()));

	m_ui->m_lbTestSrvSentPksVar->setText(QString::number(m_mainWindow->Client()->TwServerTester()->NumSentPks()));
	m_ui->m_lbTestSrvLostPksVar->setText(QString::number(m_mainWindow->Client()->TwServerTester()->NumLostPks()));


	// refresh packetlist
	this->AddPacketEntry(OUT, m_mainWindow->Client()->TwServerTester()->CurrentSentDataLen(), 0);
	this->AddPacketEntry(IN, m_mainWindow->Client()->TwServerTester()->CurrentRecDataLen(), m_currentPing);
}

void CUiTestServer::AddPacketEntry(int inOut, int dataLen, int latency)
{
	QString path = inOut ? ":/img/icons/down.png" : ":/img/icons/up.png";
	QTableWidgetItem *inOutItem = new QTableWidgetItem(QIcon(path), QString::number(m_numPks));
	QTableWidgetItem *dataLenItem = new QTableWidgetItem(QString::number(dataLen));
	dataLenItem->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem *latencyItem = new QTableWidgetItem(QString::number(latency));
	latencyItem->setTextAlignment(Qt::AlignRight);

	m_ui->m_twTestSrvPks->insertRow(0);
	m_ui->m_twTestSrvPks->setItem(0, 0, inOutItem);
	m_ui->m_twTestSrvPks->setItem(0, 1, dataLenItem);
	m_ui->m_twTestSrvPks->setItem(0, 2, latencyItem);
}

void CUiTestServer::Reset()
{
	m_numPks = 0;
	m_ui->m_twTestSrvPks->setRowCount(0);

	// reset plot
	m_ui->m_widgetTestSrvPlot->clearGraphs();
	m_ui->m_widgetTestSrvPlot->addGraph();
	m_ui->m_widgetTestSrvPlot->graph(0)->setPen(QPen(QColor(80, 174, 250)));
}
