#include "flatprogressbar.h"
#include <QPainter>
#include <QDebug>


FlatProgressBar::FlatProgressBar(QWidget *parent) : QWidget(parent)
{
	ChangeStyle();
}

void FlatProgressBar::ChangeStyle()
{
	this->setStyleSheet("border:1px solid #50aefa;");
}

void FlatProgressBar::GetValues()
{
	m_Height = this->height() - 1;
	m_Max = this->width(); // width = max
	m_Percent = m_Max / 100;
}

void FlatProgressBar::SetValue(int value)
{
	GetValues();
	m_Value = value * m_Percent;
	repaint();
}

void FlatProgressBar::Reset()
{
	m_Value = 2;
	repaint();
}

void FlatProgressBar::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	p.fillRect(20, 1, 20 - 2, m_Height - 1, qRgb(229, 229, 229));
}
