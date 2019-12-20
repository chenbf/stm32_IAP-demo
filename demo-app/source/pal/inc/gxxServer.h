/**
  ******************************************************************************
  * @file			: gxxServer.h
  * @brief			: header file
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _GXX_SERVER_H_
#define _GXX_SERVER_H_

/*****************************************************************
* ����ͷ�ļ�
******************************************************************/
#include "typedef.h"
#include "RingBuffer.h"

/*****************************************************************
* �궨��
******************************************************************/


#define SVR_RECVBUF_LEN					1024
#define GXX_PROTO_MAX_LEN				1024				// GXXЭ����󳤶�


/*****************************************************************
* �ṹ��ö�ٶ���
******************************************************************/

struct gxxServer_Info
{
	UINT8						ucUart;							// ���ں�
	UINT8						ucState;						// ״̬ 0-���� 1-����
	struct RingBuffer			RingBuf_In;						// ���ջ��λ�����
	struct RingBuffer			RingBuf_Out;					// ���ͻ��λ�����
	//struct pack_Detect		packDetect;						// Э��������
    UINT8                     	recvBuf[GXX_PROTO_MAX_LEN];		// ���յ�Э���
   	UINT16						usRecvLen;						// packBuf���ݳ���
    INT8U                     	sendBuf[GXX_PROTO_MAX_LEN];		// ��ǰҪ���͵�����
    UINT16						usSendLen;						// packBuf���ݳ���
};

/* ����������ṹ */
struct server_Mngr
{
	UINT8						coTaskFlag;					// Э�����־ 0-�� 1-����
	UINT32						coTaskNum;					// Э��������� (Э���)
	struct gxxServer_Info		*pSvrInfo;					// Э��ͨ�ŷ���˽ṹ
};


/*****************************************************************
* ȫ�ֱ�������
******************************************************************/

/*****************************************************************
* ����ԭ������
******************************************************************/
int gxxSvr_SendPack(INT8U *pPack, UINT16 nPackLen);
void gxxServer_startCoTask(int nTaskNum);
void gxxServer_Task(void);
int gxxServer_Init(void);

#endif
