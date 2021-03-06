/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef WINDOWS_MAINWINDOW_MAINWINDOW_H
#define WINDOWS_MAINWINDOW_MAINWINDOW_H


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

	// exit
	void FreeAll();

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
	class configwindow *m_confWidow;

	// ui components
	friend class CUiExtractImages;
	friend class CUiServerList;
	friend class CUiTestServer;
	class CUiExtractImages *m_uiExtractImages;
	class CUiServerList *m_uiServerList;
	class CUiTestServer *m_uiTestServer;

	// twat client
	TWAT::CClient *m_client;
	TWAT::CClient *Client() const {return m_client;}
};

class CUiExtractImages : public QObject
{
	Q_OBJECT

	MainWindow *m_mainWindow;

	QString m_mapPath;
	class QGraphicsScene *m_scene;

	enum SaveModes
	{
		ALL = 0,
		SELECTED
	};

public:
	CUiExtractImages(MainWindow *window);
	~CUiExtractImages();


signals:
	void Load();
	void Save(int mode);


private slots:
	void OnLoadClicked();
	void OnBrowseClicked();
	void OnListEntryClicked(const QModelIndex &index);
	void OnSaveSelectedClicked();
	void OnSaveAllClicked();

	void OnLoad();
	void OnSave(int mode);

private:
	void RefreshUiInfos();
};

class CUiServerList : public QObject
{
	Q_OBJECT

	MainWindow *m_mainWindow;

	QTimer *m_timer;
	int m_lastServerPos;
	int m_currentGot;

public:
	CUiServerList(MainWindow *window);
	~CUiServerList();

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

	MainWindow *m_mainWindow;

	QString m_ip;
	QTimer *m_timer;
	int m_timerTickSpeed;
	bool m_wasRunning;
	bool m_runs;
	int m_currentPing;
	int m_numPks;

	enum
	{
		OUT = 0,
		IN
	};

public:
	CUiTestServer(MainWindow *window);

signals:
	void TestStart();
	void TestPause();

private slots:
	void OnSrvListSwitch(const QString &ip);

	void OnStartClicked();
	void OnPauseClicked();

	void StartTest();
	void PauseTest();
	void RefreshStatistics();

private:
	void RefreshUiInfos();
	void SetUpUiInfos();
	void AddPacketEntry(int inOut, int dataLen, int latency);
	void Reset();
};

#endif // WINDOWS_MAINWINDOW_MAINWINDOW_H
