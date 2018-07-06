#include "MeetingRoomWordWdg.h"

MeetingRoomWordWdg* MeetingRoomWordWdg::r_instance = NULL;
MeetingRoomWordWdg* MeetingRoomWordWdg::GetInstance(){
	if (r_instance == NULL)
	{
		r_instance = new MeetingRoomWordWdg();

	}
	return r_instance;
}

MeetingRoomWordWdg::MeetingRoomWordWdg(QWidget *parent,CommonWndFlags WndFlag)
	: CCommonWidget(parent, WndFlag, Qt::Dialog)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	CreateSystemTitle(ui.leftLayout);
	CreateSystemButton(ui.rightLayout,enum_GGWndCloseButtonHint);
	SetTitle(L"��������������");

	connect(ui.okBtn,SIGNAL(clicked()),this,SLOT(OnOK()));
	connect(ui.cancelBtn,SIGNAL(clicked()),this,SLOT(OnCancel()));
	connect(this, SIGNAL(OnClose()), this, SLOT(OnClose()));
	connect(ui.roomWordLineEdit,SIGNAL(returnPressed()),this,SLOT(OnOK()));

}

MeetingRoomWordWdg::~MeetingRoomWordWdg()
{

}
void MeetingRoomWordWdg::OnOK(){

	if(ui.roomWordLineEdit->text()!="")
	{
		PROOM_INFO roomInfo = g_pMeetingFrame->GetRoomInfo(indexRow);
		if(ui.roomWordLineEdit->text() == QString::fromUtf8(roomInfo->strPassword))
		{
			
			emit toEnterRoomWithRoomId(roomInfo->ulRoomID);
			close();
		}
		else
		{
			ui.tipLabel->setText("�������");
		}

	}
	else
	{
		ui.tipLabel->setText("���벻��Ϊ��");
	}
}
void MeetingRoomWordWdg::OnCancel(){
	close();
}
void MeetingRoomWordWdg::OnClose(){

	close();
}
