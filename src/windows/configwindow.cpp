/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "configwindow.h"
#include "ui_configwindow.h"

#include <core/shared/config.h>

using namespace TWAT;


configwindow::configwindow(QWidget *parent) : QWidget(parent),  m_ui(new Ui::configwindow)
{
	m_ui->setupUi(this);
}

configwindow::~configwindow()
{
	delete m_ui;
}

void configwindow::Show(TWAT::CConfig *conf)
{
	this->show();
	m_conf = conf;

	this->SetupUiElements();
}

void configwindow::SetupUiElements()
{
	m_ui->m_pbGeneralCheckForUpdates->setChecked(m_conf->m_conf.GetVar<int>("ntw_check_for_updates"));
	m_ui->m_pbGeneralAutoRefreshTranslations->setChecked(m_conf->m_conf.GetVar<int>("ntw_auto_refresh_translations"));
	m_ui->m_pbGeneralAutoExpandMenu->setChecked(m_conf->m_conf.GetVar<int>("ui_menu_expanded"));

	m_ui->m_pbStatsUseDefaultMasters->setChecked(m_conf->m_conf.GetVar<int>("utl_use_default_masters"));
}

void configwindow::on_m_widgetConfigTypes_clicked(const QModelIndex &index)
{
	m_ui->m_swSettings->setCurrentIndex(index.row());
}

void configwindow::on_m_pbStatsUseDefaultMasters_toggled(bool checked)
{
	m_conf->m_conf.SetVar<int>("utl_use_default_masters", checked);
}
