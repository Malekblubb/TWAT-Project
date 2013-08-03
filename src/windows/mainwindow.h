/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QPushButton>
#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>
#include "../core/client.h"


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void OnExit();
	void ResetMenuButtons();
	
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void on_pbMainClose_clicked();

	void on_pbMainMaximize_clicked();

	void on_pbMainMinimize_clicked();

	void on_widgetMainStacked_currentChanged();

	void on_pbMenuPlayDemo_clicked();

	void on_pbMenuConvertDemo_clicked();

	void on_pbMenuExtractImages_clicked();

	void on_pbMenuModifyMap_clicked();

	void on_pbMenuCreateLan_clicked();

	void on_pbMenuCreate247_clicked();

	void on_pbMenuMasterServer_clicked();

	void on_pbMenuTwatServer_clicked();

private:
	Ui::MainWindow *ui;
	QPoint m_DragPoint;

protected:
	TWAT::CClient *m_Client;
};


// some custom ui element funcs
class CustomUIElements : public MainWindow
{
	Q_OBJECT

public slots:
	void ToggleSwitch(QPushButton *btn, std::string settingKey);
};


#endif // MAINWINDOW_H
