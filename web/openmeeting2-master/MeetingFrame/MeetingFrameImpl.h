#ifndef MEETINGFRAMEIMPL_H_
#define MEETINGFRAMEIMPL_H_

#include "IMeetingFrame.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadTarget.h"
#include "Poco/Event.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"


using Poco::Thread;
using Poco::Runnable;
using Poco::ThreadTarget;
using Poco::Event;
using Poco::RunnableAdapter;
using Poco::Mutex;

#include "Poco/DateTime.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/Exception.h"
#include "Poco/AutoPtr.h"
#include "Poco/Exception.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Poco/Path.h"
#include "FrameInifile.h"
#include <queue>
using Poco::Path;
//using Poco::Util::XMLConfiguration;
//using Poco::Util::AbstractConfiguration;
using Poco::AutoPtr;
using Poco::NotImplementedException;
using Poco::NotFoundException;

using Poco::Timestamp;
using Poco::DateTime;
using Poco::Timespan;
using Poco::AssertionViolationException;

using namespace std;

class MeetingFrameImpl:public IMeetingFrame
{
public:
	
	~MeetingFrameImpl(void);
private:
	MeetingFrameImpl();
	static MeetingFrameImpl * m_instance;

public:
	static MeetingFrameImpl* GetInstance();
	void SetIMeetingFrameEvent(IMeetingFrameEvent* pEvent);
	
public:
	bool Init(HWND mainHWND,IMediaStreamEvent* pStreamEvent,std::string strServer);
	virtual bool Login(char* strUserName,char* strPassword,uint32_t ulRoomID,bool bEncrypt = true);
	virtual void LoginWithRoomNo(const char* strUserName, const char* strRoomPassword,uint32_t clientType,uint32_t u32RoomID);
	virtual bool Logout();
	virtual bool ApplySpeaker() ;   //���뷢��
	virtual bool CancelApplySpeaker();
	virtual void Release() ;
	virtual void UpdateVideoLayout();
	virtual void StartRecvRemoteVideo(uint64_t ulUserID,uint32_t ulChannelID,IVideoWin*videoWin);
	virtual void StartRecvRemoteAudio(uint64_t ulUserID);
	virtual void StopRecvRemoteVideo(uint64_t ulUserID) ;
	virtual void StopRecvRemoteAudio(uint64_t ulUserID) ;
	virtual void StartRecvRemoteVideo2(uint64_t sessionId,uint32_t ssrc,IVideoWin*videoWin);
	virtual void StopRecvRemoteVideo2(uint32_t ssrc) ;

	virtual void StartPublishVideo(uint64_t ulToUserID,uint32_t ulChannelID,IVideoWin*videoWin);
	virtual void StartPublishAudio(uint64_t ulToUserID,uint32_t ulChannelID);
	virtual void StopPublishVideo(uint32_t ulChannelID);
	virtual void StopPublishAudio(uint32_t ulChannelID);

	virtual uint32_t StartPublishVideo2(uint64_t ulToUserID,uint32_t ulChannelID,IVideoWin*videoWin);
	virtual void StopPublishVideo2(uint32_t ulChannelID);

	virtual void StartVideoMonitor();
	virtual void StopVideoMonitor();
	//��ͣ������Ƶ
	virtual void PauseVideo(uint64_t userId);
	//�ָ�������Ƶ
	virtual void ResumeVideo(uint64_t userId);
	//�����ҵ���Ƶ��Ÿ������ˣ��Է������鿴
	virtual void SendVideoSSRCToAdmin(uint64_t userId,uint32_t ssrc);


	virtual void StopAllMediaStream();

	virtual void SendTextMsg(uint64_t ulUserID,char* msg,int font_size =14,unsigned long fontFlag = 0,unsigned long color = 0,char *familly = 0);

	virtual void SetAsSpeaker(uint64_t ulUserID,bool bSet);  //����Ϊ������,bSetΪ�������ã�bSetΪflashʱȡ��
	virtual void SetAsAdmin(uint64_t ulUserID,bool bSet);  //����Ϊ����Ա
	
	virtual void SetAsBigVideo(uint64_t ulUserID);
	virtual void GiveGift(uint64_t ulToUserID,uint32_t type);  //������
	virtual void ShowHandclap() ;  //����
	virtual char* GetUserName(uint64_t ulUserID) ;

	virtual void SetIVideoLayoutMgr(IVideoLayoutMgr* layout_mgr);

	virtual void GetLocalDateTime(TCHAR* pstrTemp);

	virtual bool EnterRoom(uint32_t uiRoomID,char *strRoomPwd = "",char*strToken="");
	virtual void LeaveRoom();
	virtual void ReConnect();
	virtual char* GetAdminPassword();            //�õ�����������

	virtual int GetUserRole(uint64_t ulUserID) ;               //�õ��û�����������ڵĽ�ɫ
	virtual int GetOrgiUserRoomType(uint64_t ulUserID) { return m_orgi_user_role;};               //�õ��û�����������ڵĽ�ɫ
	virtual int GetUserType(uint64_t ulUserID) ;                   //�õ��û�����
	virtual uint64_t GetMySessionID();
	virtual void GetRoomList();

	//�������
	virtual void SetMicMute(bool bMute, int ulChannelID = 0);
	virtual void SetMicVolume(int nVolume, int ulChannelID = 0) ;
	//��������
	virtual void SetSpeakerMute(bool bMute) ;
	virtual void SetSpeakerVolume(int nVolume) ;

	virtual bool SpeakerAllowVideo();


	//�õ������û���
	virtual int GetUserCount();
	//�õ��û����ԣ��û�������ɫ
	virtual bool GetUser(int index,PClient_Online_User_Info pUserInfo);

	virtual PROOM_INFO GetRoomInfo(int index);

    virtual bool GetCurrentRoomInfo(PROOM_INFO pRoomInfo);

	virtual void SetSpeakMode(int mode);

	virtual void OpenDoc(std::string strUrl,int index,int total);
	virtual void CloseDoc();
	virtual int GetVersion(){ return m_Version;};
	//������
	virtual void ShareCursor(float x,float y);
	//ֹͣ������
	virtual void StopShareCursor();

	virtual void SetRoomMode(int mode);

	virtual bool HasStartAudio();
	virtual bool HasStartVideo();
	virtual int  GetRoomMode();
	//�õ�������Ϣ
	virtual PMsgItem GetChatMsgItem(int index);

	virtual void RequireKeyFrame(uint32_t ssrc);

	virtual char* GetBaseUrl(){return m_strBaseUrl;};

public:
	void OnSetAsShowerThread();
public:
	//�ص�����Ӧ����
	int  OnRecvRemoteAudio(uint64_t ulRemoteUserID , unsigned long ulChannelID, uint32_t ulSSRC);
	void OnCloseRemoteAudio(uint64_t ulRemoteUserID,uint32_t ulChannelID);
	int  OnRecvRemoteVideo(uint64_t ulRemoteUserID ,unsigned long ulChannelID, uint32_t ulSSRC);
	void OnCloseRemoteVideo(uint64_t ulRemoteUserID,uint32_t ulChannelID);
	
	void OnSetAsBigVideo(uint64_t ulUserID);
	void OnSetAsAdmin(uint64_t ulRemoteUserID,bool bSet);
	void OnSetAsSpeaker(uint64_t ulRemoteUserID,bool bSet);
	void OnSetAsShower(uint64_t ulRemoteUserID,bool bSet);
	void OnApplySpeaker(uint64_t ulFromUserID);
	void OnCancelApplySpeaker(uint64_t ulFromUserID);

	void On_MeetingEvent_Enter_Room_Result(uint32_t status,char *pData);
	void On_MeetingEvent_Login_Result(uint32_t status, char* msg);
	void On_MeetingEvent_Member_Online(uint64_t  sessionID,char*strUserName,char*strUserAccount,uint32_t clientType,uint32_t userRole);      //�û�����
	void On_MeetingEvent_Member_Offline(uint64_t sessionID);     //�û�����
	void On_MeetingEvent_SpeakMode_Change(int mode);
	void On_MeetingEvent_RoomMode_Change(int mode);
	void On_MeetingEvent_RequireKeyFrame(uint32_t ssrc);

	void OnStartVideoMonitor();
	void OnStopVideoMonitor();
	void OnPauseVideo();
	void OnResumeVideo();
	void OnRecvVideoSSRC(uint64_t userId,uint32_t ssrc);
public:
	virtual HWND GetVideoHWND(){return m_mainHWND;};
	
private:
	PClient_Online_User_Info FindOnlineUser(uint64_t ulUserID);
private:
	//���������
	IMeetingFrameEvent* m_pEvent;
	IMediaStreamEvent* m_pStreamEvent;
	//ý����
	IZYMediaStreamManager *m_pIZYMediaStreamManager;
	HWND m_mainHWND;
	Mutex m_Mutex;

	int m_videoIndex;
	Thread thr;
	uint32_t m_ulMixAudioSSRC;
	uint32_t m_ulAudioPlaySSRC;
	
	uint32_t m_orgi_user_role;    //�û�Ԥ�ý�ɫ
	UINT_VOID_MAP m_mapOnlineUser;    //�����û��б�
	PROOM_INFO m_pRoomInfo;
	Client_Online_User_Info m_myUserInfo;
	Mutex m_VideoListMutex;
	queue<uint64_t> m_RecvVideoList;
	Mutex m_AudioListMutex;
	queue<uint64_t> m_RecvAudioList;
	bool m_bStartAudio;
	bool m_bStartVideo;
	bool m_bShareDoc;
	//�Ƿ��ڹ㲥ģʽ
	bool m_bBroadcast;
	//�Ƿ��ڼ��ģʽ
	bool m_bVideoMonitor;
	bool m_bHasStartVideo2;
	int m_Version;
	
public:
	char m_strBaseUrl[256];
	char m_strMediaHost[64];
	uint16_t m_RtpMediaPort;
	uint16_t m_MixAudioPort;
};

#endif /* MEETINGFRAMEIMPL_H_ */
