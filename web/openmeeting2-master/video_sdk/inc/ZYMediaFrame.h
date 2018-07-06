﻿#ifndef __ZYMEDIAFRAME_H__
#define __ZYMEDIAFRAME_H__

#define WM_REPAINT_VIDEO WM_USER+101

#define VIDEO_PACKET_SIZE (RTP_MTU*1-12)
#define AUDIO_PACKET_SIZE (RTP_MTU*1-12)
#define WM_ALARM_MSG		WM_USER+951

#define ZYCOLORSPACE_RGB24		0
#define ZYCOLORSPACE_YV12		1
#define ZYCOLORSPACE_YUY2		2
#define ZYCOLORSPACE_IYUV		3

typedef struct tag_nal_node
{
    uint32_t nLen:28;
    uint32_t type:4;
    char* pData;
}NAL_NODE,*PNAL_NODE;

typedef enum
{
    rtpPayloadSILK_8 = 0,
    rtpPayloadSILK_16 = 1,
    rtpPayloadSILK_32 = 2,
    rtpPayloadMPEG4_XVID = 12,
    rtpPayloadH264 = 19,
    rtpPayloadScreen = 100,
    rtpPayloadWB = 101,
    rtpPayloadCommand = 127,
    rtpPayloadUndefined = 128,
} RTPPayloadType;

// 视音频信息
typedef enum AUDIO_CODEC
{
    PCM_8,
    PCM_11,
    PCM_16,
    PCM_22,
    PCM_32,
    PCM_44,
    SILK_8,
    SILK_16,
    SILK_32
}AUDIO_CODEC;

typedef enum VIDEO_CODEC
{
    MPEG4_XVID,
    H264
}VIDEO_CODEC;

typedef enum VIDEO_SIZE
{
    VIDEO_SIZE_160X120=0,
    VIDEO_SIZE_176X144,
    VIDEO_SIZE_240X176,
    VIDEO_SIZE_320X240,
    VIDEO_SIZE_352X288,
    VIDEO_SIZE_640X480,
    VIDEO_SIZE_704X576,
    VIDEO_SIZE_720X576,
    VIDEO_SIZE_704X288,
    VIDEO_SIZE_800X600,
    VIDEO_SIZE_1280X720,
    VIDEO_SIZE_1920X1080,
    VIDEO_SIZE_240X320
}VIDEO_SIZE;

typedef struct tag_VIDEO_FORMAT
{
    VIDEO_CODEC		videoCodec;
    VIDEO_SIZE		videoSize;
    int				videoFrameRate;
    int				videoQuality;
    bool			bDeinterlace;
}VIDEO_FORMAT, *PVIDEO_FORMAT;

typedef struct tag_AUDIO_FORMAT
{
    AUDIO_CODEC		audioCodec;
    //bool			enableAEC;
}AUDIO_FORMAT, *PAUDIO_FORMAT;

typedef struct tag_MEDIA_FORMAT
{
    VIDEO_FORMAT videoFormat;
    AUDIO_FORMAT audioFormat;
}MEDIA_FORMAT, *PMEDIA_FORMAT;

#define		PLAY_EVENT_TIMESTAMP		1
#define		PLAY_EVENT_OVER				2
#define		PLAY_EVENT_START_BUFFER		3
#define		PLAY_EVENT_STOP_BUFFER		4
#define		PLAY_EVENT_START_SEEK		5
#define		PLAY_EVENT_STOP_SEEK		6
#define		PLAY_EVENT_STOP_THREAD		7
#define		PLAY_EVENT_FILE_ERROR		8
#define		PLAY_EVENT_START_CONNECT	9
#define		PLAY_EVENT_STOP_CONNECT		10

class IVideoWin
{
public:
	virtual HWND GetVideoHWND() = 0;
	//修改视频窗口大小
	virtual bool isFree()= 0;
	virtual void SetFree(bool bFree)= 0;
	virtual void SetUserID(unsigned __int64  ulUserId){};
	virtual uint64_t GetUserID() = 0;
	virtual void SetHidden(bool bHide) = 0;
	virtual void DeliveData(int w,int h,unsigned char* pData)=0;
	virtual void StartRender() = 0;
	virtual void StopRender() = 0;
	virtual void SetUserName(char* strUserName) = 0;
};

class IZYAudioCaptureEvent
{
public:
    virtual void OnZYAVCaptureEvent_AudioData(char* pData, int nLen, AUDIO_CODEC audioCodec) = 0;
    virtual void OnZYAVCaptureEvent_MaxVolume( short nMaxVolume) = 0;
};

class IZYVideoCaptureEvent
{
public:
    virtual void OnZYAVCaptureEvent_VideoData(char* pData, int nLen, bool bKeyFrame, VIDEO_SIZE videoSize, VIDEO_CODEC videoCodec) = 0;
};

class IZYVideoCapture
{
public:
	virtual bool Connect(IVideoWin* iVideoWin, int nVideoDevice, PVIDEO_FORMAT pVideoFormat, int nColorspace) = 0;
	virtual void ReleaseConnections(void) =0;
	virtual void SendVideo(bool bSend) = 0;
	virtual bool IsSendingVideo() = 0;
	virtual int GetHeight(void) = 0;
	virtual int GetWidth(void) = 0;
	virtual void RequireKeyFrame() = 0;
};

class IZYAudioCapture
{
public:
    virtual bool Connect(HWND hWnd, int nAudioDevice, PAUDIO_FORMAT pAudioFormat) = 0;
    virtual void ReleaseConnections(void) = 0;
    virtual void SendAudio(bool bSend) = 0;
    virtual bool IsSendingAudio() = 0;
    virtual void EnableVAD(bool bEnable) = 0;
    virtual bool IsVADEnable(void) = 0;
    virtual void SetVolume(int nVolume) = 0;//0~255
    virtual int GetVolume() = 0;
    virtual void SetMute(bool bMute=true) = 0;
    virtual bool GetMute(void) = 0;
};

class IZYAudioPlayerEvent
{
public:
    //返回最大音量
    virtual void OnZYAVPlayerEvent_MaxVolume(short nMaxVolume) = 0;
    virtual bool OnZYAVPlayerEvent_GetAudioData(char* pAudioData, int& nAudioLen, uint64_t& ulRTPTime, uint64_t& ulDataBufferTime) = 0;
};

class IZYVideoPlayerEvent
{
public:
    virtual bool OnZYAVPlayerEvent_GetVideoData(char* pVideoData, int& nVideoLen, bool& bKeyFrame, bool& bDropFrame, uint64_t& ulRTPTime, uint64_t& ulDataBufferTime) = 0;
};

class IZYVideoPlayer
{
public:
	virtual bool Connect(bool bStartThread, IVideoWin* iVideoWin, PVIDEO_FORMAT pVideoFormat) = 0;
	virtual void ReleaseConnections(void) = 0;	
	virtual int	GetWidth(void) = 0;
	virtual int	GetHeight(void) = 0;
	virtual void DeliverVideoData(char*pData, int nLen, bool bKeyFrame, uint64_t ulTimeStamp) = 0;
};

class  IZYAudioPlayer
{
public:
    virtual bool Connect(bool bStartThread, HWND hWnd, PAUDIO_FORMAT pAudioFormat,int nAudioDevice) = 0;
    virtual void ReleaseConnections() =0;
    virtual bool HasAudio(void) = 0;
    virtual void SetVolume(int nVolume) = 0;/*0-100*/
    virtual int	 GetVolume(void) = 0;/*0-100*/
    virtual void SetMute(bool bMute=true) = 0;
    virtual bool GetMute(void) = 0;
    virtual void SetBalance(int nBalance) = 0;/*-1 left,0 both,1 right*/
    virtual int	 GetBalance(void) = 0;/*-1 left,0 both,1 right*/
    virtual void SetBufferTime(int bBufferTime) = 0;
    virtual int GetBufferTime() = 0;
    virtual void DeliverAudioData(char*pData, int nLen, uint64_t ulTimeStamp) = 0;
};



 bool CreateZYVideoCapture(IZYVideoCapture** ppIZYVideoCapture, IZYVideoCaptureEvent* pEvent);
 bool CreateZYVideoPlayer(IZYVideoPlayer** ppIZYVideoPlayer, IZYVideoPlayerEvent* pEvent);
 bool CreateZYAudioCapture(IZYAudioCapture** ppIZYAudioCapture, IZYAudioCaptureEvent* pEvent);
 bool CreateZYAudioPlayer(IZYAudioPlayer** ppIZYAudioPlayer, IZYAudioPlayerEvent* pEvent);

 int	GetVideoCaptureDeviceCount(void);
 bool	GetVideoCaptureDeviceName(int nVideoCaptureDeviceIndex, char* szVideoCaptureDeviceName);

 int	GetSoundCaptureDeviceCount();
 int	GetSoundCaptureDeviceName2(char szSoundCaptureDeviceName[10][255]);
 void	GetSoundCaptureDeviceName(int nSoundDevice,  char* szSoundCaptureDeviceName);

 int    GetSoudPlayDeviceCount();
 void   GetSoundPlayDeviceName(int nSoundDevice,  char* szSoundPlayDeviceName);

 void GetVideoSize(VIDEO_SIZE videoSize, int& cx, int& cy);
 void GetVideoSize2(int cx, int cy, VIDEO_SIZE& videoSize);

 int GetAudioFrameInterval(AUDIO_CODEC audioCodec);

 void GetStringFromVideoSize(VIDEO_SIZE videoSize, char* pString);
 void GetStringFromVideoCodec(VIDEO_CODEC videoCodec, char* pString);
 void GetStringFromAudioCodec(AUDIO_CODEC audioCodec, char* pString);
#endif
