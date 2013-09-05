/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef WINDOWS_MAINWINDOW_MAINWINDOW_H
#define WINDOWS_MAINWINDOW_MAINWINDOW_H


#include <thread>
#include <string>
#include <QMainWindow>


namespace TWAT
{
	class CClient;

	namespace TwTools
	{
		struct ServerInfo;
	}
}

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	// main
	void OnInit();
	void OnExit();
	void closeEvent(QCloseEvent *);

	// setup
	void SetUpUiComponents();
	void ConnectUiAndComponents();
	void LoadConfVars();
	void ChangeUiElements();
	void ResetVars();

public:
	void SetStatus(const QString &text);
	void HideStatus();
	void ShowStatusIcon(bool b);

private slots:
	void on_m_twMainMenu_clicked(const QModelIndex &index);
	void on_m_pbBottomMenuSettings_clicked();

private:
	int m_numNeedsStatusIcon;

	Ui::MainWindow *m_ui;
	TWAT::CClient *m_client;

	class configwindow *m_confWidow;

	class CUiServerList *m_uiServerList;
	class CUiTestServer *m_uiTestServer;

public:
	TWAT::CClient *Client() const {return m_client;}

	std::thread *m_workerThread; // thread for async (ui/core) work
};

class CUiServerList : public QObject
{
	Q_OBJECT

	Ui::MainWindow *m_ui;
	MainWindow *m_mainWindow;
	QTimer *m_timer;

public:
	CUiServerList(Ui::MainWindow *ui, MainWindow *window);

signals:
	void RefreshStart();
	void RefreshEnd();
	void TestServerRequest(const QString &ip);


private slots:
	void OnRefreshStart();
	void OnRefreshEnd();

	void OnRefreshClicked();
	void OnTableEntryClicked(const QModelIndex &index);
	void OnTestServerClicked();

	void Refresh();
	void RefreshTable();
	void Search(const QString &text);

private:
	void AddServerInfoRow(TWAT::TwTools::ServerInfo *inf, int row);
};

class CUiTestServer : public QObject
{
	Q_OBJECT

	Ui::MainWindow *m_ui;
	MainWindow *m_mainWindow;
	QString m_ip;
	QTimer *m_timer;

	int m_currentPing;
	int m_numPks;
	QVector<double> m_plotX;
	QVector<double> m_plotY;

	enum
	{
		OUT = 0,
		IN
	};

public:
	CUiTestServer(Ui::MainWindow *ui, MainWindow *window);

signals:
	void TestStart();
	void TestStop();

private slots:
	void OnSrvListSwitch(const QString &ip);

	void OnStartClicked();
	void OnStopClicked();

	void StartTest();
	void StopTest();
	void RefreshStatistics();

private:
	void RefreshUiInfos();
	void SetUpUiInfos();
	void AddPacketEntry(int inOut, int dataLen, int latency);
	void Reset();
};

#endif // WINDOWS_MAINWINDOW_MAINWINDOW_H
