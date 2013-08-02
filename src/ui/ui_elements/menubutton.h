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
	bool m_Active;

public:
	enum
	{
		NO_BORDER = 0,
		BORDER
	};

	MenuButton(QWidget *parent = 0);

	void SetColor(int border);
	void ResetColor();

	bool isActive() const {return m_Active;}
	void setActive(bool active) {m_Active = active;}

private:
	QString ActivePath() const {return ":/img/icons/" + objectName() + "_active.png";}
	QString DefPath() const {return ":/img/icons/" + objectName() + "_def.png";}

	void Hover();
	void Leave();


public:
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *e);
};

#endif // MENUBUTTON_H
