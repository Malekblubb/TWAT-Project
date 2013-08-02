/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "menubutton.h"
#include <QDebug>


MenuButton::MenuButton(QWidget *parent) : QPushButton(parent)
{
	m_Active = false;
}

void MenuButton::Hover()
{
	if(!this->isActive())
		this->SetColor(NO_BORDER);
}

void MenuButton::Leave()
{
	if(!this->isActive())
		this->ResetColor();
}

void MenuButton::SetColor(int border)
{
	if(border)
		this->setStyleSheet(this->styleSheet() + "border-right:4px solid #50aefa;color:#50aefa;");
	else
		this->setStyleSheet(this->styleSheet() + "color:#50aefa;");

	this->setIcon(QIcon(ActivePath()));
}

void MenuButton::ResetColor()
{
	this->setStyleSheet(this->styleSheet() + "border-right:none;color:#7b7b7b;");
	this->setIcon(QIcon(DefPath()));
}

void MenuButton::enterEvent(QEvent *)
{
	this->Hover();
}

void MenuButton::leaveEvent(QEvent *)
{
	this->Leave();
}

void MenuButton::mousePressEvent(QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton)
		emit clicked();
}
