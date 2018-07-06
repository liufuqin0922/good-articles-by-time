#include "SeanProgressBar.h"
#include <QPainter>
#include <QDebug>
SeanProgressBar::SeanProgressBar(QWidget *parent)
	: QWidget(parent)
{
	vValue = 0;

	

	
}

SeanProgressBar::~SeanProgressBar()
{

}

void SeanProgressBar::getSoundVulume(int voiceValue)
{
  vValue = voiceValue;
  update();
}
void SeanProgressBar::paintEvent(QPaintEvent *event){

	//qDebug()<<"vValue == "<<vValue;
	QPainter painter(this);
	QPen pen;

	pen.setColor(QColor(220,220,220));  //���û���ɫ
	painter.setPen(pen);  //ѡ�񻭱�
	pen.setBrush(Qt::gray);//�����ɫ
	pen.setStyle(Qt::SolidLine);//������ʽ
	pen.setCapStyle(Qt::RoundCap); 
	painter.begin(this);
	for (int i = 0;i < 25;i ++)
	{
		painter.drawRoundRect(8*i,0,3,18,40,40);//
	}
	pen.setColor(QColor(0,191,255));
	painter.setPen(pen); 
	pen.setBrush(Qt::darkBlue);
	pen.setStyle(Qt::SolidLine); 
	pen.setCapStyle(Qt::RoundCap); 
	vValue = vValue/3.2676/4;
	for (int j = 0;j < vValue;j ++)
	{
		painter.drawRoundRect(8*j,0,3,18,40,40);//Բ�Ǿ���,99,99
	
	}
	

	painter.end(); 
}


