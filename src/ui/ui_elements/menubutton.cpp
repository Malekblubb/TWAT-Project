/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "menubutton.h"


MenuButton::MenuButton(QWidget *parent) : QPushButton(parent)
{
	m_Toggled = false;
}

void MenuButton::enterEvent(QEvent *)
{
	if(this->isChecked() || m_Toggled)
		return;

	this->setIcon((QIcon)ActivePath());
	this->setStyleSheet(this->styleSheet() + "color:#50aefa;");
}

void MenuButton::leaveEvent(QEvent *)
{
	if(this->isChecked() || m_Toggled)
		return;

	this->setIcon((QIcon)DefPath());
	this->setStyleSheet(this->styleSheet() + "color:#7b7b7b;");
}

void MenuButton::mousePressEvent(QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton)
	{
		if(!m_Toggled)
		{
			this->setStyleSheet(this->styleSheet() + "border-right:4px solid #50aefa;color:#50aefa;");
			m_Toggled = true;
		}
		else
		{
			this->setStyleSheet(this->styleSheet() + "border-right:none;color:#7b7b7b;");
			m_Toggled = false;
		}
	}
}
