/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MenuButton : public QPushButton
{
	bool m_Toggled;

public:
	MenuButton(QWidget *parent = 0);

private:
	QString ActivePath() {return ":/img/icons/" + objectName() + "_active.png";}
	QString DefPath() {return ":/img/icons/" + objectName() + "_def.png";}


protected:
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *e);
};

#endif // MENUBUTTON_H
