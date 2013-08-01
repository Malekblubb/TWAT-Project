#include "mainwindow.h"
#include "ui_mainwindow.h"



void CustomUIElements::ToggleSwitch(QPushButton *btn, std::string settingKey)
{
	if(btn->isChecked())
		btn->setIcon(QIcon(":/img/ui_elements/switch_on.png"));

	else
		btn->setIcon(QIcon(":/img/ui_elements/switch_off.png"));

	m_Client->m_Config->m_Conf[settingKey] = btn->isChecked();
}
