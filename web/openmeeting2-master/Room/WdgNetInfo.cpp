#include "WdgNetInfo.h"
#include <QPainter>
#include <QDebug>
WdgNetInfo * WdgNetInfo::m_instance = NULL;;
WdgNetInfo * WdgNetInfo::GetInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new WdgNetInfo();
	}
	return m_instance;
}
WdgNetInfo::WdgNetInfo(QWidget *parent)
	: QWidget(parent)
{
	m_delay = 0;
	m_uploadLost = 0;
	m_downloadLost = 0;
	setWindowFlags(Qt::FramelessWindowHint);//�����widget�ı������ͱ߿�ȥ��
	//setAttribute(Qt::WA_TranslucentBackground);
	this->setGeometry(0,0,122,60);
}

WdgNetInfo::~WdgNetInfo()
{

}

void WdgNetInfo::OnNetInfo(int delay,int uploadLost,int downloadLost)
{
	m_delay = delay;
	m_uploadLost  = uploadLost;
	m_downloadLost = downloadLost;
	qDebug()<<"**OnStream Netinfo delay:"<<delay<<"send lost:"<<uploadLost<<"recv lost:"<<downloadLost;
	update();
}

void WdgNetInfo::paintEvent ( QPaintEvent * event )
{
	QPainter painter(this);
	QPen pen;
	pen.setColor(QColor(102,0,0));  //���û���Ϊ��ɫ
	painter.setPen(pen);  //ѡ�񻭱�
	painter.drawRect(2,2,118,56);
	painter.fillRect(3,3,117,55,QColor(239,255,191));
	pen.setColor(QColor(0,0,0));  //���û���Ϊ��ɫ
	painter.setPen(pen);  //ѡ�񻭱�
	//���ж�����:%2,���ж�����:%3
	painter.drawText(16,17,QString("������ʱ: %1����").arg(m_delay));
	painter.drawText(16,34,QString("���ж�����: %1%").arg(m_uploadLost));
	painter.drawText(16,51,QString("���ж�����: %1%").arg(m_downloadLost));
	painter.end(); 
}

void WdgNetInfo::mousePressEvent(QMouseEvent *event)
{
	this->hide();
}

void WdgNetInfo::enterEvent ( QEvent * event )
{
	this->show();
}

void WdgNetInfo::leaveEvent ( QEvent * event )
{
	this->hide();
}