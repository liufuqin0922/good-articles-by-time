#include "Meetinglistwdg.h"
#include <QDebug>
#include <QList>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QScrollBar>
#include "SeanTableViewDelegate.h"
#include "../Room/RoomWdg.h"
#include "../stdafx.h"
#include "MeetingDetailDelegate.h"
#include "../eventcenter.h"

MeetingListWdg *MeetingListWdg::t_instance = NULL;
MeetingListWdg *MeetingListWdg::GetTableViewInstance(){

	if (t_instance == NULL)
	{
		t_instance = new MeetingListWdg();
	}
	return t_instance;

}

MeetingListWdg::MeetingListWdg(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	QFile qssFile(":/qss/login.qss");
	QString qss;
	qssFile.open(QFile::ReadOnly);
	if(qssFile.isOpen())
	{  
		qss = QString(qssFile.readAll());
		this->setStyleSheet(qss);
		qssFile.close();
	}

	setWindowFlags(Qt::FramelessWindowHint);//�����widget�ı������ͱ߿�ȥ��
	setAttribute(Qt::WA_TranslucentBackground);

	ui.backLabel->setPixmap(QPixmap(":/login/login/login_bg1.png"));
	ui.backLabel->setScaledContents(true); //


	QLabel *tBackImage = new QLabel(this);
	ui.tBackImage->setGeometry(4,85,442,250);
	ui.tBackImage->setPixmap(QPixmap(":/login/login/whiteImage.png"));

	connect(ui.closeBtn,SIGNAL(clicked()),this,SLOT(close()));
	connect(MeetingRoomWordWdg::GetInstance(),SIGNAL(toEnterRoomWithRoomId(uint32_t)),this,SLOT(getRoomIdToEnterRoom(uint32_t)));
	InitDeviceList();
}
MeetingListWdg::~MeetingListWdg()
{
}

void MeetingListWdg::InitDeviceList()
{
	//qDebug()<<"MeetingListModel::GetInstance()``1111 == "<<MeetingListModel::GetInstance()->m_total;
	// setmodel ����
	ui.myTableView->setModel(MeetingListModel::GetInstance());
	//������btn�Զ���
	ButtonDelegate *btnDelegate = new ButtonDelegate(this);
	ui.myTableView->viewport()->installEventFilter(btnDelegate);
	ui.myTableView->setItemDelegateForColumn(4,btnDelegate);

	MeetingDetailDelegate *mDelegate  =  new MeetingDetailDelegate(this);
	ui.myTableView->viewport()->installEventFilter(mDelegate);
	ui.myTableView->setItemDelegateForColumn(1,mDelegate);


	//����cell��ʽ
	SeanTableViewDelegate *seanDelegate = new SeanTableViewDelegate(ui.myTableView);
	ui.myTableView->setItemDelegate(seanDelegate);
	//btn����¼�
	connect(btnDelegate,SIGNAL(sendTableViewNumberRowAndWorth(int,int)),this,SLOT(getFromButtonDelegateWithRowAndBool(int,int)));

	for(int i = 0 ; i < 5;i ++)
	{
		ui.myTableView->horizontalHeader()->setResizeMode(i,QHeaderView::Fixed);
		if (i == 1)
		{
			ui.myTableView->setColumnWidth(i,180);
		}else if (i == 4)
		{
			ui.myTableView->setColumnWidth(i,80);
		}
		else{
			ui.myTableView->setColumnWidth(i,(this->width()-180-80)/3 - 3);
		}
		
		
	}

	ui.myTableView->setSelectionBehavior(QAbstractItemView::SelectRows);/*ѡ��ĳ��*/
	//ui.myTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.myTableView->verticalHeader()->hide();/*���ش�ֱͷ*/
	ui.myTableView->horizontalHeader()->setClickable(false);/*��view�������Ӧ*/
	ui.myTableView->setStyleSheet("selection-background-color:lightgray;"); //����ѡ�б���ɫ
	ui.myTableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color::lightgray;}"); //���ñ�ͷ����ɫ
}


/*��delegate��������¼�������*/
void MeetingListWdg::getFromButtonDelegateWithRowAndBool(int row,int isBool){

	qDebug()<<"MeetingListWdg --- row"<<row<<"and--isBool"<<isBool;
	if(g_pMeetingFrame!=NULL)
	{
		//���뷿��1
		PROOM_INFO roomInfo = g_pMeetingFrame->GetRoomInfo(row);
		if(roomInfo!=NULL)
		{
			if (isBool == 1)
			{
				qDebug()<<"roomInfo.strPassword == "<<roomInfo->strPassword;
				MeetingRoomWordWdg::GetInstance()->indexRow = row;
				MeetingRoomWordWdg::GetInstance()->show();
				//return;
			}
			else{
				g_pMeetingFrame->EnterRoom(roomInfo->ulRoomID);
				EventCenter::GetInstance()->setRoomId(roomInfo->ulRoomID);
				this->hide();
				RoomWdg::GetInstance()->CenterWindow();
				RoomWdg::GetInstance()->showMaximized();
			}
		}
		
	}
 
}
void MeetingListWdg::getRoomIdToEnterRoom(uint32_t roomId){

	g_pMeetingFrame->EnterRoom(roomId);
	EventCenter::GetInstance()->setRoomId(roomId);
	this->hide();
	RoomWdg::GetInstance()->CenterWindow();
	RoomWdg::GetInstance()->showMaximized();
}

void MeetingListWdg::mouseMoveEvent(QMouseEvent *event){

	if (mouse_pressed)
	{
		QPoint movePoint = event->globalPos();
		this->move(movePoint - mouse_movePoint);
	}
}

void MeetingListWdg::mousePressEvent(QMouseEvent *event){

	if (event->button() == Qt::LeftButton)
	{
		mouse_pressed = true;
		mouse_movePoint = event->pos();
	}
}

void MeetingListWdg::mouseReleaseEvent(QMouseEvent *event){

	mouse_pressed = false;

}



