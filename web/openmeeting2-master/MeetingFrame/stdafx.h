// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>
#include <tchar.h>
#include "typedef.h"

//��Ƶ���ͷ�ļ�
#include "ZYMediaFrame.h"
#include "IMediaStream.h"

#include "Poco/HashMap.h"
#include "Poco/Exception.h"
#include <map>
using Poco::HashMap;

typedef HashMap<uint64_t,void*> UINT_VOID_MAP;
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

void AA_UTF82W(wchar_t* strDest, char* strUTF8, int nMaxLen);
void  AA_W2UTF8(char* strUTF8, const wchar_t* strSource, int nMaxLen);
void AA_W2A(const wchar_t* strWide, char* strAsc);
void  AA_A2W(const char* strAsc, wchar_t* strWide);

//0 ��ת��1������  2��p2p
extern uint32_t kAudioMode ;

void LogTrace(LPCTSTR pszFormat, ...);