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
	void OnExit();
	
protected:
	// move window without border
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void on_pbMainClose_clicked();

	void on_pbMainMaximize_clicked();

	void on_pbMainMinimize_clicked();

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
