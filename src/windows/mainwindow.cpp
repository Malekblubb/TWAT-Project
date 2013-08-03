/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace TWAT;


// MainUI stuff like MenuBars, Close, Minimize, Maximize buttons in this file.
// Tool specific slots etc. stripped to other files.

// exit, init
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent, Qt::FramelessWindowHint), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_Client = new CClient();
	m_Client->Init();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::OnExit()
{
	// save config
	m_Client->m_Config->Save();
}


// right corner window buttons
void MainWindow::on_pbMainClose_clicked()
{
	this->OnExit();
	qApp->exit(0);
}

void MainWindow::on_pbMainMaximize_clicked()
{
	if(this->isMaximized())
		this->showNormal();
	else
		this->showMaximized();
}

void MainWindow::on_pbMainMinimize_clicked()
{
	this->showMinimized();
}


// move window without border
void MainWindow::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_DragPoint = event->globalPos();
		event->accept();
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton)
	{
		move(event->globalPos() - m_DragPoint);
		event->accept();
	}
}


// left menu, main stacked widget navigation
void MainWindow::ResetMenuButtons()
{
	if(ui->pbMenuPlayDemo->isActive()) {ui->pbMenuPlayDemo->ResetColor(); ui->pbMenuPlayDemo->setActive(false);}

	if(ui->pbMenuConvertDemo->isActive()) {ui->pbMenuConvertDemo->ResetColor(); ui->pbMenuConvertDemo->setActive(false);}

	if(ui->pbMenuExtractImages->isActive()) {ui->pbMenuExtractImages->ResetColor(); ui->pbMenuExtractImages->setActive(false);}

	if(ui->pbMenuModifyMap->isActive()) {ui->pbMenuModifyMap->ResetColor(); ui->pbMenuModifyMap->setActive(false);}

	if(ui->pbMenuCreateLan->isActive()) {ui->pbMenuCreateLan->ResetColor(); ui->pbMenuCreateLan->setActive(false);}

	if(ui->pbMenuCreate247->isActive()) {ui->pbMenuCreate247->ResetColor(); ui->pbMenuCreate247->setActive(false);}

	if(ui->pbMenuMasterServer->isActive()) {ui->pbMenuMasterServer->ResetColor(); ui->pbMenuMasterServer->setActive(false);}

	if(ui->pbMenuTwatServer->isActive()) {ui->pbMenuTwatServer->ResetColor(); ui->pbMenuTwatServer->setActive(false);}
}

void MainWindow::on_widgetMainStacked_currentChanged()
{
	ResetMenuButtons();
}

void MainWindow::on_pbMenuPlayDemo_clicked()
{
	ui->widgetMainStacked->setCurrentIndex(0);
	ui->pbMenuPlayDemo->setActive(true);
	ui->pbMenuPlayDemo->SetColor(MenuButton::BORDER);
}

void MainWindow::on_pbMenuConvertDemo_clicked()
{
	ui->widgetMainStacked->setCurrentIndex(1);
	ui->pbMenuConvertDemo->setActive(true);
	ui->pbMenuConvertDemo->SetColor(MenuButton::BORDER);
}

void MainWindow::on_pbMenuExtractImages_clicked()
{
	ui->widgetMainStacked->setCurrentIndex(2);
	ui->pbMenuExtractImages->setActive(true);
	ui->pbMenuExtractImages->SetColor(MenuButton::BORDER);
}

void MainWindow::on_pbMenuModifyMap_clicked()
{
	ui->widgetMainStacked->setCurrentIndex(3);
	ui->pbMenuModifyMap->setActive(true);
	ui->pbMenuModifyMap->SetColor(MenuButton::BORDER);
}

void MainWindow::on_pbMenuCreateLan_clicked()
{
	ui->widgetMainStacked->setCurrentIndex(4);
	ui->pbMenuCreateLan->setActive(true);
	ui->pbMenuCreateLan->SetColor(MenuButton::BORDER);
}

void MainWindow::on_pbMenuCreate247_clicked()
{
	ui->widgetMainStacked->setCurrentIndex(5);
	ui->pbMenuCreate247->setActive(true);
	ui->pbMenuCreate247->SetColor(MenuButton::BORDER);
}

void MainWindow::on_pbMenuMasterServer_clicked()
{
	ui->widgetMainStacked->setCurrentIndex(6);
	ui->pbMenuMasterServer->setActive(true);
	ui->pbMenuMasterServer->SetColor(MenuButton::BORDER);
}

void MainWindow::on_pbMenuTwatServer_clicked()
{
	ui->widgetMainStacked->setCurrentIndex(7);
	ui->pbMenuTwatServer->setActive(true);
	ui->pbMenuTwatServer->SetColor(MenuButton::BORDER);
}
