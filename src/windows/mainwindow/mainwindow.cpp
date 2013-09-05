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
#include <core/shared/twservertester.h>

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
	// setup the ui components
	this->SetUpUiComponents();

	// connect ui signals with component slots
	this->ConnectUiAndComponents();

	// twat client start
	m_client = CClient::CreateClient();
	Client()->Init();

	// load user settings
	this->LoadConfVars();

	// change non-designer properties
	this->ChangeUiElements();

	// reset vars to default
	this->ResetVars();
}

void MainWindow::OnExit()
{
	// save config
	Client()->Config()->Save();
}

void MainWindow::SetUpUiComponents()
{
	m_uiServerList = new CUiServerList(m_ui, this);
	m_uiTestServer = new CUiTestServer(m_ui, this);
}

void MainWindow::ConnectUiAndComponents()
{
	connect(m_ui->m_pbSrvListRefresh, SIGNAL(clicked()), m_uiServerList, SLOT(OnRefreshClicked()));
	connect(m_ui->m_twSrvListList, SIGNAL(clicked(QModelIndex)), m_uiServerList, SLOT(OnTableEntryClicked(QModelIndex)));
	connect(m_ui->m_leSrvListSearchBar, SIGNAL(textChanged(QString)), m_uiServerList, SLOT(Search(QString)));
	connect(m_ui->m_pbSrvListTestCon, SIGNAL(clicked()), m_uiServerList, SLOT(OnTestServerClicked()));
	connect(m_uiServerList, SIGNAL(TestServerRequest(QString)), m_uiTestServer, SLOT(OnSrvListSwitch(QString)));

	connect(m_ui->m_pbTestSrvStart, SIGNAL(clicked()), m_uiTestServer, SLOT(OnStartClicked()));
	connect(m_ui->m_pbTestSrvStop, SIGNAL(clicked()), m_uiTestServer, SLOT(OnStopClicked()));
}

void MainWindow::LoadConfVars()
{
	if(Client()->Config()->Store()->GetVar<int>("ui_menu_expanded"))
		m_ui->m_twMainMenu->expandAll();

	if(Client()->Config()->Store()->GetVar<int>("utl_use_default_masters"))
		m_client->TwServerBrowser()->UseDefaultMasters(true);
}

void MainWindow::ChangeUiElements()
{
	m_ui->m_twSrvListList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	// srvtest plot
	m_ui->m_widgetTestSrvPlot->setBackground(QBrush(QColor(m_ui->m_swMain->palette().base().color())));
	m_ui->m_widgetTestSrvPlot->xAxis->setLabel("Seconds");
	m_ui->m_widgetTestSrvPlot->xAxis->setLabelColor(QColor(181, 181, 181));
	m_ui->m_widgetTestSrvPlot->xAxis->setTickLabelColor(QColor(181, 181, 181));
	m_ui->m_widgetTestSrvPlot->xAxis->setBasePen(QPen(QColor(181, 181, 181)));
	m_ui->m_widgetTestSrvPlot->xAxis->setTicks(false);
	m_ui->m_widgetTestSrvPlot->yAxis->setRange(0, 60);
	m_ui->m_widgetTestSrvPlot->yAxis->setLabel("Ping (ms)");
	m_ui->m_widgetTestSrvPlot->yAxis->setLabelColor(QColor(181, 181, 181));
	m_ui->m_widgetTestSrvPlot->yAxis->setTickLabelColor(QColor(181, 181, 181));
	m_ui->m_widgetTestSrvPlot->yAxis->setBasePen(QPen(QColor(181, 181, 181)));
	m_ui->m_widgetTestSrvPlot->yAxis->setTicks(false);
	m_ui->m_widgetTestSrvPlot->yAxis->setRange(0, 60);
	m_ui->m_widgetTestSrvPlot->setInteraction(QCP::iRangeDrag, true);
	m_ui->m_widgetTestSrvPlot->setInteraction(QCP::iRangeZoom, true);
	m_ui->m_widgetTestSrvPlot->axisRect()->setRangeZoomFactor(2);
}

void MainWindow::ResetVars()
{
	m_numNeedsStatusIcon = 0;
}

void MainWindow::SetStatus(const QString &text)
{
	m_ui->m_lbStatusbarStatusText->setText(text);
}

void MainWindow::ShowStatusIcon(bool b)
{
	if(b)
	{
		++m_numNeedsStatusIcon;

		QMovie *m = new QMovie(":/img/animated/loading.gif");
		m->start();
		m_ui->m_lbStatusbarIcon->setMovie(m);
		m_ui->m_lbStatusbarIcon->show();
	}
	else
	{
		--m_numNeedsStatusIcon;

		if(m_numNeedsStatusIcon > 0)
			return;

		m_ui->m_lbStatusbarIcon->hide();
	}
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
