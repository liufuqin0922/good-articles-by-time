#ifndef EVENTCENTER_H
#define EVENTCENTER_H

#include <QtGui/QWidget>
#include "stdafx.h"
#include <map>
#include <QTimer>
class EventCenter : public QWidget,public IMeetingFrameEvent,public IMediaStreamEvent
{
	Q_OBJECT

public:
	EventCenter(QWidget *parent = 0, Qt::WFlags flags = 0);
	~EventCenter();
public:
	static EventCenter*GetInstance();
	void setRoomId(unsigned int roomId){ m_roomId = roomId;};
private:
	static EventCenter* m_instahce;
public:
	virtual void On_MeetingEvent_ShareCursor(float x,float y);

	virtual void On_MeetingEvent_StopShareCursor();

	virtual void On_MeetingEvent_EnterRoom_Result(uint32_t status,char *msg);
	//�����û���¼���
	virtual void On_MeetingEvent_Login_Result(uint32_t status,char *msg);
	//�û�����
	virtual void On_MeetingEvent_Member_Online(uint64_t ulUserID,char*strUserName,
		uint32_t userType,uint32_t userRoomType);      //�û�����
	//�û�����
	virtual void On_MeetingEvent_Member_Offline(uint64_t ulUserID);     //�û�����
	//�յ��ı�������Ϣ
	virtual void On_MeetingEvent_Text_Msg(uint64_t ulUserID,char*strMsg, 
		int font_size =14,unsigned long fontFlat = 0,unsigned long color = 0,char *familly = "");

	//֪ͨ����㱻���óɷ�����
	virtual void On_MeetingEvent_SetAsSpeaker(uint64_t ulUserID,bool bSet);
	//֪ͨ����㱻���ó�Ϊ����
	virtual void On_MeetingEvent_SetAsShower(uint64_t ulUserID,bool bSet);
	//֪ͨ����㱻���ó�Ϊ����Ա
	virtual void On_MeetingEvent_SetAsAdmin(uint64_t ulUserID,bool bSet);
	//֪ͨ�����˻��߹���Ա������ͨ�û������˷���
	virtual void On_MeetingEvent_ApplySpeaker(uint64_t fromUserID);
	//֪ͨ������û�ȡ���˷�������
	virtual void On_MeetingEvent_CancelApplySpeaker(uint64_t fromUserID);
	//֪ͨ����㣬�û���ɫ�ı���
	virtual void On_MeetingEvent_UserRole_Change(uint64_t ulUserID,int role);
	//֪ͨ���������Ƶ
	virtual void On_MeetingEvent_RecvMyVideo(uint64_t sessionID,uint32_t channelID);
	//֪ͨ���������Ƶ
	virtual void On_MeetingEvent_CloseMyVideo(uint64_t sessionID,uint32_t channelID);
	// ����״̬;
	virtual void OnNetEvent(uint32_t code,const char* msg="");
	//�õ������б�
	virtual void On_MeetingEvent_GetRoomList(uint32_t total);

	virtual void On_MeetingEvent_UpdateUI();

	//����ģʽ���˱仯
	virtual void On_MeetingEvent_SpeakMode_Change(int mode);

	virtual void On_MeetingEvent_RoomMode_Change(int mode);

	virtual void On_MeetingEvent_SetAsBigVideo(uint64_t sessionID);

	virtual void StreamEvent_OnNetInfo(int delay,int uploadLost,int downloadLost);
	//�����Ĵ�С,bCapture�Ƿ�Ϊ�ɼ�������ulSSRC���,value ����ֵ
	virtual void StreamEvent_AudioEnergy(bool bCapture,uint32_t ulSSRC,int16_t value);
	//�õ���һ���ؼ�֡����Ƶ��ʼ������ʾ����
	virtual void StreamEvent_GetFirstKeyFrame(uint32_t ulSSRC);

	virtual void On_MeetingEvent_OpenDoc(std::string strUrl,int index,int total);

	virtual void On_MeetingEvent_CloseDoc();

	virtual void On_MeetingEvent_StartVideoMonitor() ;
	virtual void On_MeetingEvent_StopVideoMonitor() ;
	//��ͣ������Ƶ
	virtual void On_MeetingEvent_PauseVideo();
	//�ָ�������Ƶ
	virtual void On_MeetingEvent_ResumeVideo() ;

	virtual void On_MeetingEvent_RecvUserVideoSSRC(uint32_t ssrc,uint64_t sessionId,char* userName);

	virtual void On_MeetingEvent_UpdateSoft(std::string url);
signals:
	void EventLoginSuccess();
	void EventLoginFailed();
	void EventRecvRemoteVideo(unsigned long long sessionID);
	void EventAddUser();
	void EventDelUser();
	void EventGetRoomList(int total);
	void EventUpdateUI();

	void EventSetSpeaker(bool bSet);
	void EventSpeakModeChange(int mode);
	void EventRoomModeChange(int mode);
	void EventUserOffline(unsigned long long sessionID);
	void EventOnStreamNetInfo(int delay,int uploadLost,int downloadLost);
	void EventSetAsBigVideo(unsigned long long sessionID);
	void EventEnterRoom(unsigned int result);
	void EventOpenDoc(QString url,int index,int total);
	void EventCloseDoc();
	void EventCloseRemoteCursor();
	void EventShowRemoteCursor(float x,float y);
	void EventOnStartVideoMonitor();
	void EventOnStopVideoMonitor();
	void EventRecvVideoSSRC(unsigned long long sessionId,unsigned int ssrc);
	void EventUpdateSoft(QString url);
	void EventNetEvent(unsigned int code);
	//sean add
	//void getMessageEvent();
	void getMessageEvent(unsigned long long ulUserID,QString* strMsg, 
		int font_size,unsigned long fontFlat,unsigned long color,QString *familly);

public slots:
	void OnRecvRemoteVideo(unsigned long long sessionID);
	void OnUpdateUI();
	void OnSetSpeaker(bool bSet);
	void OnSpeakModeChange(int mode);
	void OnRoomModeChange(int mode);
	void OnUserOffline(unsigned long long sessionID);
	void OnSetAsBigVideo(unsigned long long sessionID);
	void OnEnterRoom(unsigned int result);
	void On_UI_StartVideoMonitor();
	void On_UI_StopVideoMonitor();
	void On_UI_RecvVideoSSRC(unsigned long long sessionID,unsigned int ssrc);
	void On_UI_UpdateSoft(QString url);
	void On_UI_NetEvent(unsigned int code);
	void On_UI_LoginSuccess();
	void OnReConnectTimer();
protected:
	virtual bool winEvent (MSG* msg, long *result);
	QTimer* m_reConnectTimer;
	bool m_bInRoom;
	unsigned int m_roomId;
};

#endif // EVENTCENTER_H
