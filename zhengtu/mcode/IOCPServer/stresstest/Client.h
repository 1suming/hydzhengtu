#pragma once
#include <Windows.h>
#include "FS_Engine.h"
#include "BinaryStream.h"

extern WORD wDisProb;	// �Ͽ��ĸ���
extern WORD wRecProb;	// �����ĸ���

struct STotalInfo 
{
	double dwSendCount;
	double dwMinTick;
	double dwMaxTick;
	double dwTotalTick;
	double dwReceiveCnt;
	double dwInvalidPackCnt;
	double dwCurElapse;
	double dwRecFailNum;

	STotalInfo()
	{
		dwSendCount = 0;
		dwMinTick = 0xFFFFFFFF;
		dwMaxTick = 0;
		dwTotalTick = 0;
		dwReceiveCnt = 0;
		dwCurElapse = 0;
		dwRecFailNum = 0;
		dwInvalidPackCnt = 0;
	}
};


#include <list>
using namespace std;

class CClient
{
public:
	CClient(void);
	virtual ~CClient(void);

	// ��Ϸ��ʼ��������0�˳���Ϸ
	BOOL Init(const char* strSrvIP, UINT nPort, STotalInfo* pTotalInfo);

	// ����
	BOOL Reconnect();
	
	// �����������ݰ�
	DWORD HandleNetPack();

	// ���Ͳ��԰�
	void SendTestPack(int iSize);
	void SendTestPack1();

	FSClient* GetClientNet() {return m_pClient;}
	


private:
	FSClient *m_pClient;	//����

	char m_szIP[20];
	UINT m_nPort;
	STotalInfo* m_pTotalInfo;
	CBinaryStream binStream;
};




