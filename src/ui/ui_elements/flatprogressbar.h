#ifndef FLATPROGRESSBAR_H
#define FLATPROGRESSBAR_H


#include <QWidget>


class FlatProgressBar : public QWidget
{

	int m_Max, m_Height, m_Percent, m_Value;

public:
	FlatProgressBar(QWidget *parent = 0);

private:
	void ChangeStyle();
	void GetValues();

public slots:
	void SetValue(int value);
	void Reset();

protected:
	void paintEvent(QPaintEvent *);
};

#endif // FLATPROGRESSBAR_H
