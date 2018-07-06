#ifndef WDGNETINFO_H
#define WDGNETINFO_H

#include <QObject>
#include <QWidget>
class WdgNetInfo : public QWidget
{
	Q_OBJECT

public:
	WdgNetInfo(QWidget *parent = 0);
	~WdgNetInfo();

private:
	static WdgNetInfo * m_instance;
public:
	static WdgNetInfo * GetInstance();

	public slots:
		void OnNetInfo(int delay,int uploadLost,int downloadLost);
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void enterEvent ( QEvent * event );
	void leaveEvent ( QEvent * event );
private:
	int m_delay;            //������ʱ������
	int m_uploadLost;       //���ж������ٷ���
	int m_downloadLost;     //���ж���
};

#endif // WDGNETINFO_H
