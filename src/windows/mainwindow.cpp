/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSizeGrip>

using namespace TWAT;


// Main setup stuff for mainwindow


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



//void MainWindow::on_pushButton_toggled(bool checked)
//{
//	CustonUIElements().ToggleSwitch(ui->pushButton, "app_language");
//}
