#pragma once
#include <QString>
#include <QSettings>
#include <QDesktopServices>  
#include <QDir>


//QStandardPaths
class AppSetting
{
public:
	AppSetting(void);
	~AppSetting(void);
private:
	static AppSetting* m_instance;
public:
	static AppSetting* GetInstance();
public:
	 void Save();
	 void ReadValues();
	 int GetMicIndex();
	 void SetMicIndex(int index);
	 int GetSpeakerIndex();
	 void SetSpeakerIndex(int index);
	 int GetCameraIndex();
	 void SetCameraIndex(int index);
	 QString GetServerAddress();
	 void SetServerAddress(QString serverAddress);

	 QString GetLoginAccount();
	 void SetLoginAccount(QString logAccount);
	 QString GetLoginPWord();
	 void SetLoginPWord(QString logPWord);
	 QString GetLoginNikeName();
	 void SetLoginNikeName(QString logNikeName);

	 int GetLoginRemberAPWordStatus();
	 void SetLoginRemberAPWordStatus(int isTrue);

     int GetLoginStyle();
     void SetLoginStyle(int logStyle);


private:
	 int m_micIndex;  //��˷�
	 int m_speakerIndex; //��������豸�����䣬����֮��
	 int m_cameraIndex;  //����ͷ
	 QString serverUrl; //���÷�������ַ

	 QString loginAccount; //��¼�˺�
	 QString loginPWord;//��¼����
	 QString loginNickName;//��¼�ǳ�

	 int remberAPWord;//�˺ŵ�¼�Ƿ��ס����
   
     int isAccount;//�Ƿ����˺ŵ�¼

	// QDir *inDoc;
	
};

