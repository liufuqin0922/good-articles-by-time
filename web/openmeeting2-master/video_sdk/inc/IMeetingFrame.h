#pragma once

//�ͻ�������
enum ClientType
{
	kClientType_Windows,
	kClientType_Android,
	kClienttype_ios
};

//��¼���
enum LoginResult
{
	kLoginResult_NoUser,                     //�û�������
	kLoginResult_Password_NotCorrect,        //�������
	kLoginResult_Meeting_NoRoom,             //����Ŵ���
	kLoginResult_Meeting_NotAuth,            //û��Ȩ�޽���
	kLoginResult_LoginServer_NotConnect,      //��¼������û��������
	kLoginResult_Meeting_SUCCESS,
	kLoginResult_MeetingServer_NotConnect,
	kLoginResult_Meeting_RoomPwd_NOTCorrent   //�������벻��ȷ
};

typedef struct tag_Room_Info
{
	uint32_t ulRoomID;             //�����
	uint32_t speakMode;            //������������
	uint32_t roomMode;             //�������� 1���飬2ֱ��   
	uint32_t ulIsPublic;           //�Ƿ񹫿�
	uint32_t bMixAudio;          //�Ƿ���÷���������ģʽ
	uint32_t sampleRate;         //��Ƶ�����ʣ�Ĭ��8000
	uint32_t defaultVideoSize;    //��������Ƶ��С
	uint64_t bigVideoUser;        //���᳡���û�ID
	uint64_t startTime;           //��ʼʱ��
	uint64_t endTime;             //����ʱ��
	uint32_t maxUser;
	uint32_t onlineUser;          //�����û���
	char strAdminPwd[64];         //����Ա����
	char strPassword[64];        //��������
	char  strRoomName[256];      //������ 
}ROOM_INFO,*PROOM_INFO;


//ͨ����������Ƶ����Ƶ��ssrc,Ϊ0����û��
typedef struct tag_Media_Channel
{
	uint32_t isEmpty;      //�Ƿ�Ϊ��
	uint32_t ulAudioSSRC;
	uint32_t ulVideoSSRC;
}Media_Channel,*PMedia_Channel;

typedef struct tag_Client_Online_User_Info
{
	uint64_t sessionID;
	char strHeadImg[64];    //�û���¼�ʺ�
	char strUserName[64];       //�û���
	unsigned char userRole;             //�û�����  1 ������ 2  ��ͨ�û�
	unsigned char clientType; //�ͻ�������
	uint32_t ulAudioSSRC;
	uint32_t ulVideoSSRC;
}Client_Online_User_Info,*PClient_Online_User_Info;

//������Ϣ�ṹ��
typedef struct tag_Msg_Item
{
	uint64_t ulUserID;
	char userName[64];
	char msg[1024*4];
	int font_size;
	unsigned long fontFlat;  //б�壬���壬�»��ߵ�
	unsigned long color;
    char familly[32];
}MsgItem,*PMsgItem;

#define WM_RECV_REMOTE_VIDEO WM_USER+10
#define WM_PUBLISH_AV        WM_USER+11

#define NET_EVENT_CONNECT_SUCCESS    0  //���ӷ������ɹ�
#define NET_EVENT_LOST_CONNECTION    1  //����
#define NET_EVENT_TIME_OUT           2  //���ӷ�������ʱ
#define NET_EVENT_JSON_ERROR         3  //json ���ݽ�������


#define LOGIN_SUCESS                0
#define LOGIN_NO_USER               1
#define LOGIN_DB_ERROR              2
#define LOGIN_PASSWORD_ERROR        3

#define CLIENT_TYPE_WINDOWS         1
#define CLIENT_TYPE_ANDROID         2
#define CLIENT_TYPE_IPHONE          3
#define CLIENT_TYPE_IPAD            4


/************************************************************************/
/* 
					��Ƶ�����ܽӿ�                                                                    
*/
/************************************************************************/

//�������õײ㹦�ܽӿ�
class IMeetingFrame{

	/*****************��¼��ע��********************/
public:
	virtual void Release() = 0;
	virtual bool Login(char* strUserName,char* strPassword,uint32_t ulRoomID,bool bEncrypt = true) = 0;
	virtual void LoginWithRoomNo(const char* strUserName, const char* strRoomPassword,uint32_t clientType,uint32_t u32RoomID) = 0;
	virtual bool Logout() = 0;
	//���뷿�� uiRoomID ����ţ�strRoomPwd �����뱣���ķ�����Ҫ���룬strToken,�û���¼�ɹ���᷵��һ��Tokenֵ
	virtual bool EnterRoom(uint32_t uiRoomID,char *strRoomPwd = "",char*strToken="") = 0;
	virtual void LeaveRoom() = 0;
	
	/************************************************************************/
	/*        ��Ƶ,����                                                     */
	/************************************************************************/
	virtual void UpdateVideoLayout() = 0;
	//������Ƶ������
	virtual void StartRecvRemoteVideo(uint64_t ulUserID,uint32_t ulChannelID,IVideoWin*videoWin) = 0;
	virtual void StartRecvRemoteAudio(uint64_t ulUserID) = 0;
	virtual void StopRecvRemoteVideo(uint64_t ulUserID) = 0;
	virtual void StopRecvRemoteAudio(uint64_t ulUserID) = 0;

	virtual void StartRecvRemoteVideo2(uint64_t sessionId,uint32_t ssrc,IVideoWin*videoWin) = 0;
	virtual void StopRecvRemoteVideo2(uint32_t ssrc) = 0;
	//������Ƶ����
	virtual void StartPublishVideo(uint64_t ulToUserID,uint32_t ulChannelID,IVideoWin*videoWin) = 0;
	virtual void StartPublishAudio(uint64_t ulToUserID,uint32_t ulChannelID) = 0;
	virtual void StopPublishVideo(uint32_t ulChannelID) = 0;
	virtual void StopPublishAudio(uint32_t ulChannelID) = 0;

	virtual uint32_t StartPublishVideo2(uint64_t ulToUserID,uint32_t ulChannelID,IVideoWin*videoWin) = 0;
	virtual void StopPublishVideo2(uint32_t ulChannelID) = 0;
	//ֹͣ���е�����Ƶ�������������ĺͽ��յ�
	virtual void StopAllMediaStream() = 0;
    //��������

	//¼������
    virtual void SetMicMute(bool bMute, int ulChannelID = 0) = 0;
	virtual void SetMicVolume(int nVolume, int ulChannelID = 0) = 0;
	
	//��������
    virtual void SetSpeakerMute(bool bMute) = 0;
	virtual void SetSpeakerVolume(int nVolume) = 0;
	//�Ƿ���������Ƶ
	virtual bool HasStartAudio() = 0;
	virtual bool HasStartVideo() = 0;
	/************************************************************************/
	/* �ı�����                                                             */
	/************************************************************************/

	virtual void SendTextMsg(uint64_t ulUserID,char* msg,int font_size =14,unsigned long fontFlag = 0,unsigned long color = 0,char *familly = 0) = 0;
	/************************************************************************/
	/* ��������                                                             */
	/************************************************************************/
	virtual char* GetUserName(uint64_t ulUserID) = 0;   //�õ��û�����ulUserID = 0 ������
	virtual uint64_t GetMySessionID() = 0;
	virtual void GetLocalDateTime(TCHAR* pstrTemp) = 0;
	//�õ��װ�Url
	virtual char* GetAdminPassword() = 0;            //�õ�����������
	virtual int GetUserRole(uint64_t ulUserID) = 0;               //�õ��û�����������ڵĽ�ɫ
	virtual int GetOrgiUserRoomType(uint64_t ulUserID) = 0;               //�õ��û�����������ڵĽ�ɫ
	virtual int GetUserType(uint64_t ulUserID) = 0;                   //�õ��û�����
	/************************************************************************/
	/*   Ȩ����ؽӿ�                                                       */
	/************************************************************************/
	virtual bool ApplySpeaker() = 0;   //���뷢��
	virtual bool CancelApplySpeaker() = 0;
	virtual void SetAsSpeaker(uint64_t ulUserID,bool bSet) = 0;  //����Ϊ������,bSetΪ�������ã�bSetΪfalseʱȡ��
	virtual void SetAsAdmin(uint64_t ulUserID,bool bSet) = 0;
	virtual void SetAsBigVideo(uint64_t ulUserID) = 0;
	//���������������� 1 ���ɷ��� 2 ��f2���� 3 �����˵�������
	virtual void SetSpeakMode(int mode) = 0;
	//���÷������� 1 ����ģʽ 2 ֱ��ģʽ
	virtual void SetRoomMode(int mode) = 0;
	virtual int  GetRoomMode() = 0;
	virtual void SetIVideoLayoutMgr(IVideoLayoutMgr* layout_mgr) = 0;
    //�������Ƿ��������Ƶ
	virtual bool SpeakerAllowVideo() = 0;
	//����������
	virtual void ReConnect() = 0;
	
	//�õ������û���
	virtual int GetUserCount() = 0;
	//�õ��û����ԣ��û�������ɫ
	virtual  bool GetUser(int index,PClient_Online_User_Info pUserInfo) = 0;
	//�õ������б�
	virtual void GetRoomList() = 0;

	virtual PROOM_INFO GetRoomInfo(int index) = 0;
	virtual bool GetCurrentRoomInfo(PROOM_INFO pRoomInfo) = 0;
	//�õ�������Ϣ
	virtual PMsgItem GetChatMsgItem(int index) = 0;

	virtual void RequireKeyFrame(uint32_t ssrc) = 0;

	//֪ͨ�����ڳ�Ա���ĵ�
	virtual void OpenDoc(std::string strUrl,int index,int total) = 0;
	virtual void CloseDoc() = 0;
	//������
	virtual void ShareCursor(float x,float y) = 0;
	//ֹͣ������
	virtual void StopShareCursor() = 0;
	virtual char* GetBaseUrl() = 0;

	/*************��Ƶ������*****************/
	virtual void StartVideoMonitor() = 0;
	virtual void StopVideoMonitor() = 0;
	//��ͣ������Ƶ
	virtual void PauseVideo(uint64_t userId) = 0;
	//�ָ�������Ƶ
	virtual void ResumeVideo(uint64_t userId) = 0;
	//�����ҵ���Ƶ��Ÿ������ˣ��Է������鿴
	virtual void SendVideoSSRCToAdmin(uint64_t userId,uint32_t ssrc) = 0;
	//�õ��汾��
	virtual int GetVersion() = 0;
};

//�ײ㷵����������Ϣ
class IMeetingFrameEvent{
public:
	//���ĵ�
	virtual void On_MeetingEvent_OpenDoc(std::string strUrl,int index,int total) = 0;

	virtual void On_MeetingEvent_CloseDoc() = 0;

	virtual void On_MeetingEvent_ShareCursor(float x,float y) = 0;

	virtual void On_MeetingEvent_StopShareCursor() = 0;

	virtual void On_MeetingEvent_EnterRoom_Result(uint32_t status,char *msg) = 0;
	//�����û���¼���
	virtual void On_MeetingEvent_Login_Result(uint32_t status,char *msg) = 0;
	//�û�����
	virtual void On_MeetingEvent_Member_Online(uint64_t ulUserID,char*strUserName,uint32_t userType,uint32_t userRoomType) = 0;      //�û�����
	//�û�����
	virtual void On_MeetingEvent_Member_Offline(uint64_t ulUserID) = 0;     //�û�����
	//�յ��ı�������Ϣ
	virtual void On_MeetingEvent_Text_Msg(uint64_t ulUserID,char*strMsg, int font_size =14,unsigned long fontFlat = 0,unsigned long color = 0,char *familly = "") = 0;
	//֪ͨ����㱻���óɷ�����
	virtual void On_MeetingEvent_SetAsSpeaker(uint64_t ulUserID,bool bSet) = 0;
	//֪ͨ����㱻���ó�Ϊ����
	virtual void On_MeetingEvent_SetAsShower(uint64_t ulUserID,bool bSet) = 0;
	//֪ͨ����㱻���ó�Ϊ����Ա
	virtual void On_MeetingEvent_SetAsAdmin(uint64_t ulUserID,bool bSet) = 0;
	//֪ͨ�����˻��߹���Ա������ͨ�û������˷���
	virtual void On_MeetingEvent_ApplySpeaker(uint64_t fromUserID) = 0;
	//֪ͨ������û�ȡ���˷�������
	virtual void On_MeetingEvent_CancelApplySpeaker(uint64_t fromUserID) = 0;
	//֪ͨ����㣬�û���ɫ�ı���
	virtual void On_MeetingEvent_UserRole_Change(uint64_t ulUserID,int role) = 0;
	//֪ͨ���������Ƶ
	virtual void On_MeetingEvent_RecvMyVideo(uint64_t sessionID,uint32_t channelID) = 0;

	virtual void On_MeetingEvent_CloseMyVideo(uint64_t sessionID,uint32_t channelID) = 0;

	//���ó����᳡
	virtual void On_MeetingEvent_SetAsBigVideo(uint64_t sessionID) = 0;

	// ����״̬;
	virtual void OnNetEvent(uint32_t code,const char* msg="") = 0;

	virtual void On_MeetingEvent_GetRoomList(uint32_t total) = 0;

	virtual void On_MeetingEvent_UpdateUI() = 0;	//���½���
	
	//����ģʽ���˱仯
	virtual void On_MeetingEvent_SpeakMode_Change(int mode) = 0;

	virtual void On_MeetingEvent_RoomMode_Change(int mode) = 0;

	/*************��Ƶ������*****************/
	virtual void On_MeetingEvent_StartVideoMonitor() = 0;
	virtual void On_MeetingEvent_StopVideoMonitor() = 0;
	//��ͣ������Ƶ
	virtual void On_MeetingEvent_PauseVideo() = 0;
	//�ָ�������Ƶ
	virtual void On_MeetingEvent_ResumeVideo() = 0;
	
	virtual void On_MeetingEvent_RecvUserVideoSSRC(uint32_t ssrc,uint64_t sessionId,char* userName)=0;

	//�������
	virtual void On_MeetingEvent_UpdateSoft(std::string url) = 0;
    
};
//strServer�����ַ����ʽ 192.168.1.1:7082
bool CreateMeetingFrame(IMeetingFrame** pMeetingFrame,IMeetingFrameEvent* pEvent,HWND mainHWND,
	IMediaStreamEvent* pStreamEvent,std::string strServer);