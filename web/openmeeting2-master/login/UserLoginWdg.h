#ifndef USERLOGINWDG_H
#define USERLOGINWDG_H

#include <QWidget>
#include "ui_UserLoginWdg.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QLineEdit>
#include "MeetingListModel/Meetinglistwdg.h"
#include "MeetingLoadingWidget.h"
#include "..//Setting/SeanAnimation.h"


class UserLoginWdg :public QWidget
{
	Q_OBJECT

public:
	UserLoginWdg(QWidget *parent = 0);
	~UserLoginWdg();

public:
	enum LOGIN_TYPE
	{
		LOGIN_TYPE_USER,       //�ʺŵ�¼
		LOGIN_TYPE_ROOMNO      //����ŵ�¼
	};
	
public:
	static UserLoginWdg * m_instance;
	static UserLoginWdg * GetInstance();
	void initGodsAnyThingBySean();
	LOGIN_TYPE GetLoginType(){ return m_loginType;};

	QString logType;
	QString roomNum;
	QString userId;
	QString passWord;
	bool isWeb;

	int re_status;

protected slots:
		void OnClose();
private:
	Ui::UserLoginWdg ui;
	QLineEdit *acccountLineEdit;
	QLineEdit *passWordLineEdit;
	QLineEdit *nikeNameLineEdit;

	QWidget *contentWidget;
	MeetingListWdg *meetListWdg;
	MeetingLoadingWidget *loadWidget;



	QPoint mouse_movePoint;
	bool mouse_pressed;
	void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//��ӵ�¼�ȴ�
	void addLoadingWidget();
	//�жϵ�¼״̬
	bool judgeLoadingStatus(LOGIN_TYPE loinType,QString userNme,QString passWord,QString nikeName);
	void loginAnimation(QString animationStr);
	

public slots:
		void countBtnClicked();
		void meetingBtnClicked();

		void setBtnClicked();//����
		void loginBtnClicked();//��¼

		void checkBoxClicked(int status);/*checkboxѡ��*/

		void getSignalToHiddenLoadWidget();
		//��¼ʧ��
		void OnLoginFailed();
		//��¼�ɹ�
		void OnLoginSuccess();

		void OnGetRoomList(int total);

private:
	LOGIN_TYPE m_loginType;
	SeanAnimation *animation;
signals:

	void loginFromWebWithUserId();
	void loginFromWebWithMeetingRoom();

	void loginFromWebToLogin();
};

#endif // USERLOGINWDG_H
