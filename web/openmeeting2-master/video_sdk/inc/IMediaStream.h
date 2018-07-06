#pragma once
#define PUBLISHER_START   0
#define PUBLISHER_STOP    1
#define RECEIVER_START    2
#define RECEIVER_STOP     3
#define SEND_DATA_AGAIN   4      //���·��Ͱ�

//��������
typedef struct tag_Mix_Audio_Command
{
	unsigned int command;
	unsigned int ulRecvSSRC;
	unsigned int ulRoomID;
}MIX_AUDIO_COMMAND,*PMIX_AUDIO_COMMAND;




class IZYMediaStreamManager
{
public:
	virtual bool Init(char* strServer,HWND eventWnd,unsigned short usRtpPort=6122,unsigned short usMixAudioPort=6121) = 0;
	virtual void DeInit() = 0;
	//����GUID
	virtual uint64_t GetGUID() = 0;
	//������Ƶ����,����ssrc  ,��Ƶ�ɼ���: 8000 16000 32000 ,bMixed �Ƿ�Ϊ����ģʽ
	virtual unsigned int StartAudioSender(unsigned int audio_device,HWND eventWnd,
		unsigned int ulRoomID,int mode = 0,int samplate=8000) = 0;

	virtual void StopAudioSender(unsigned int ulSSRC,unsigned int ulRoomID ,int mode = 0) = 0;
	//������Ƶ����
	virtual unsigned int StartAudioRecver(unsigned int ulSSRC,HWND eventWnd,unsigned int ulRoomID = 0,
		int mode=0,int samplate=8000) = 0;

	virtual void StopAudioRecver(unsigned int ulSSRC,unsigned int ulRoomID ,int mode = 0) = 0;
	//������Ƶ���ͣ�����ulSSRC,�������-1��ʾʧ��
	virtual unsigned int StartVideoSender(unsigned int ulSSRC,unsigned int video_device,IVideoWin* eventWnd,unsigned int ulRoomID ,int mode = 0) = 0;

	virtual void StopVideoSender(unsigned int  ulSSRC,unsigned int ulRoomID,int mode = 0 ) = 0;

	virtual unsigned int StartVideoRecver(unsigned int ulSSRC,IVideoWin* eventWnd,unsigned int ulRoomID,int mode = 0) = 0;

	virtual void StopVideoRecver(unsigned int ulSSRC,unsigned int ulRoomID,int mode = 0) = 0;

	/*****************��������*************************/
	virtual void SetVolume(unsigned int ulSSRC,int nVolume) = 0;

	virtual int GetVolume(unsigned int ulSSRC) = 0;
	//�����Ƿ���
	virtual void SetMute(unsigned int ulSSRC,bool bMute=true) = 0;
	//�õ��Ƿ������þ���
	virtual bool GetMute(unsigned int ulSSRC) = 0;

	virtual bool IsCreate() = 0;

	virtual void RequireKeyFrame(uint32_t ssrc) = 0;
};

class IMediaStreamEvent
{
	public:
		//������Ϣ
		virtual void StreamEvent_OnNetInfo(int delay,int uploadLost,int downloadLost) = 0;
		//�����Ĵ�С,bCapture�Ƿ�Ϊ�ɼ�������ulSSRC���,value ����ֵ
		virtual void StreamEvent_AudioEnergy(bool bCapture,uint32_t ulSSRC,int16_t value) = 0;
		//�õ���һ���ؼ�֡����Ƶ��ʼ������ʾ����
		virtual void StreamEvent_GetFirstKeyFrame(uint32_t ulSSRC) = 0;

};

//ģ����ڣ���������Ƶ��������
bool CreateZYMediaStreamManager(IZYMediaStreamManager ** pIZYMediaStreamManager,IMediaStreamEvent* pStreamEvent);

#define WM_PLAY_VOLUME WM_USER+81
#define WM_CAPTURE_VOLUME WM_USER+82
#define WM_GET_FIRST_FRAME WM_USER+83    //�յ���һ֡
#define WM_NET_INFO WM_USER+84    //�յ���һ֡

class IMediaStream
{
public:
	virtual void Release() = 0;
	virtual void SetVolume(int nVolume) = 0;
	virtual int GetVolume() = 0;
	virtual void SetMute(bool bMute=true)= 0;
	virtual bool GetMute(void) = 0;
	virtual void OnUdpDataArrive(char* pData,int nLen) = 0;
	virtual void OnDataLost(unsigned int ssrc,unsigned int start,unsigned int count) = 0;
	virtual void OnPauseStream(unsigned int ssrc) = 0;
	virtual void OnResumeStream(unsigned int ssrc) = 0;
	virtual void RequireKeyFrame(uint32_t ssrc) = 0;
};

class IVideoLayoutMgr{
public:
	virtual IVideoWin* GetFreeVieoContainer(unsigned int ulSSRC) = 0;
	virtual void RemoveVideo(unsigned int ulSSRC) = 0;
	virtual void LayoutVideo() = 0;   
};

class ITransport
{
public:
	virtual void SendData(char* pData,int nLen) = 0;
	virtual void SendReliableData(char* pData,int nLen) = 0;
};