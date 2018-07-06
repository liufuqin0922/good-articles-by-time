#include "ModifyPassWord.h"
#include <QDebug>
#include <QRegExp>
#include "SeanAnimation.h"

ModifyPassWord * ModifyPassWord::m_instance = NULL;
ModifyPassWord *ModifyPassWord::GetInstance(){

	if (m_instance == NULL)
	{
		m_instance = new ModifyPassWord();
	}
	return m_instance;
}

ModifyPassWord::ModifyPassWord(QWidget *parent,CommonWndFlags WndFlag)
	: CCommonWidget(parent, WndFlag, Qt::Dialog)
	
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	CreateSystemTitle(ui.hBoxTitle);
	CreateSystemButton(ui.hBoxSysBtn,enum_GGWndCloseButtonHint);
	SetTitle(L"����������");
	connect(ui.btnOk,SIGNAL(clicked()),this,SLOT(OnOK()));
	connect(ui.btnCancel,SIGNAL(clicked()),this,SLOT(OnCancel()));
	connect(this, SIGNAL(OnClose()), this, SLOT(OnClose()));
	
	ui.lastPassword->clear();
	ui.newPassword->clear();
	ui.againPassword->clear();

}

ModifyPassWord::~ModifyPassWord()
{

}

void ModifyPassWord::judeLastPasswordIsRight(){

}

void ModifyPassWord::judeNewPasswordFormatIsRight(){

	
}

void ModifyPassWord::judePasswordKeepSame(){

	
}
//�ر�
void ModifyPassWord::OnClose()
{
	close();
}
//ȷ��
void ModifyPassWord::OnOK()
{


	QRegExp exp1("[a-z][A-Z][0-9]");  
	bool valid=exp1.isValid();//����true  

	QRegExp rx;
	rx.setPatternSyntax(QRegExp::RegExp);
	rx.setCaseSensitivity(Qt::CaseSensitive); //��Сд����
	rx.setPattern(QString("^[A-Za-z0-9]+$")); //ƥ�����д�Сд��ĸ��������ɵ��ַ���

	QString lastWord = ui.lastPassword->text();
	QString newWord = ui.newPassword->text();
	QString aginWord = ui.againPassword->text();

	if (lastWord.length()==0)
	{
		startAnimation("���벻��Ϊ��");
		return;
	}


	//���ص�ֵΪfalse����Ϊs�к���@�ַ�
	if (newWord.length()==0)
	{
		startAnimation("�����벻��Ϊ��");
		return;
	}
	else if(!rx.exactMatch(newWord))
	{
		startAnimation("�������������� ��������ĸ������");
		ui.againPassword->clear();
		return;
		
	}

	if(aginWord.length() == 0){
		startAnimation("���ٴ���������");
		return;
	}else if ( newWord.compare(aginWord)!= 0)
	{
		startAnimation("������������벻һ�£����������룡");
		ui.againPassword->clear();
		return;
	}


	close();
}
//ȡ��
void ModifyPassWord::OnCancel()
{
	close();
}

void ModifyPassWord::startAnimation(QString str){

	SeanAnimation *animation = new SeanAnimation(this);
	animation->parentWdg = this;
	animation->setTiptitleWithString(str);
	animation->setAttribute(Qt::WA_ShowModal,true);
	animation->show();
	
}
