/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef WINDOWS_CONFIGWINDOW_H
#define WINDOWS_CONFIGWINDOW_H


#include <QWidget>

namespace TWAT
{
	class CConfig;
}

namespace Ui
{
	class configwindow;
}

class configwindow : public QWidget
{
	Q_OBJECT

	TWAT::CConfig *m_conf;
	
public:
	explicit configwindow(QWidget *parent = 0);
	~configwindow();
	
	void Show(TWAT::CConfig *conf);

private:
	void SetupUiElements();

private slots:
	void on_m_widgetConfigTypes_clicked(const QModelIndex &index);

	void on_m_pbStatsUseDefaultMasters_toggled(bool checked);

private:
	Ui::configwindow *m_ui;
};

#endif // WINDOWS_CONFIGWINDOW_H
