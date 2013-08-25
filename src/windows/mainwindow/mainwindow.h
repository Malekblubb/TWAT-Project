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

protected:
	// ----- main -----
	void closeEvent(QCloseEvent *);
	void OnInit();
	void OnExit();
	void SetStatus(const QString &text);
	void ShowStatusIcon(bool b);
	void LoadConfVars();
	void ChangeUiElements();

	// ----- serverbrowser -----
	void RefreshSrvBrowserTable();
	void AddServerInfoRow(TWAT::TwTools::ServerInfo *inf, int row);


	// slots
private slots:
	// ----- main; menu etc. -----
	void on_m_twMainMenu_clicked(const QModelIndex &index);
	void on_m_pbBottomMenuSettings_clicked();

	// ----- serverbrowser -----
	void on_m_pbSrvListRefresh_clicked();
	void on_m_twSrvListList_clicked(const QModelIndex &index);
	void on_m_leSrvListSearchBar_textChanged(const QString &arg1);

private:
	Ui::MainWindow *m_ui;
	class configwindow *m_confWidow;

protected:
	TWAT::CClient *m_client;

	std::thread *m_workerThread; // thread for async (ui/core) work
};

#endif // WINDOWS_MAINWINDOW_MAINWINDOW_H
