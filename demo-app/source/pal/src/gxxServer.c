/**
  ******************************************************************************
  * @file			: gxxServer.c
  * @brief			: ����������
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */


/*****************************************************************
* ����ͷ�ļ�
******************************************************************/
#include <stdio.h>
#include <string.h>
#include "gxxServer.h"
#include "public.h"
#include "usart.h"


/*****************************************************************
* �궨��
******************************************************************/

/*****************************************************************
* �ṹ����
******************************************************************/

/*****************************************************************
* ȫ�ֱ�������
******************************************************************/
struct server_Mngr		gSvrMngr = {0};
struct gxxServer_Info	gxxServerInfo = {0};


/*****************************************************************
* �ⲿ��������
******************************************************************/

/*****************************************************************
* ��̬��������
******************************************************************/
static UINT8 	gSvr_InRingBuf[SVR_RECVBUF_LEN] = {0};

/*****************************************************************
* ����ԭ������
******************************************************************/

/*****************************************************************
* ��������
******************************************************************/

/****************************************************************
* Func 	:
* Desc	:	����Э�����ݰ�����
* Input	:
* Output:
* Return:
*****************************************************************/
int gxxSvr_SendPack(INT8U *pPack, UINT16 nPackLen)
{
	struct server_Mngr		*pSvrMngr = &gSvrMngr;
	int		nRet = 0;
	

	nRet = UART_SEND(pSvrMngr->pSvrInfo->ucUart, pPack, nPackLen);

	return nRet;
}

/****************************************************************
* Func 	:
* Desc	:	��ȡЭ�����ݺ���
* Input	:
* Output:
* Return:
*****************************************************************/
int gxxSvr_getProtoData(struct RingBuffer *pRingBuf)
{
	struct server_Mngr		*pSvrMngr = &gSvrMngr;
	UINT8 	ucTempBuf[GXX_PROTO_MAX_LEN];
	UINT16 	nLen = 0;

	// ��ȡ��ԭʼ����
	nLen = UART_READ(pSvrMngr->pSvrInfo->ucUart, ucTempBuf, sizeof(ucTempBuf));
	if(nLen > 0)
	{
		/*ֱ��д���ջ���*/
		RingBufferWrite(&ucTempBuf[0], nLen, pRingBuf);
	}

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	Э�鴦����
* Input	:
* Output:
* Return:
*****************************************************************/
int gxxSvr_protoProcess(struct gxxServer_Info *pSvrInfo, UINT8 *pPack, INT16 usPackLen)
{

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	��Ϊ����������ͨ��Э��������
* Input	:
* Output:
* Return:
*****************************************************************/
void gxxServer_Task(void)
{
	struct server_Mngr		*pSvrMngr = &gSvrMngr;
	INT32		nDataLen = 0;
	int 		nRet = 0;

	/* ��ȡЭ������ */
	gxxSvr_getProtoData(&pSvrMngr->pSvrInfo->RingBuf_In);
	nDataLen =  RingBufferLen(&pSvrMngr->pSvrInfo->RingBuf_In);
	if(nDataLen > 0)
	{
		/* Э������ */
		//nRet = gxxProto_packDetect();
		if(nRet == 0)	// ��⵽����Э���
		{
			/* Э�鴦�� */
			gxxSvr_protoProcess(pSvrMngr->pSvrInfo, pSvrMngr->pSvrInfo->recvBuf, pSvrMngr->pSvrInfo->usRecvLen);
		}
	}

}

/****************************************************************
* Func 	:
* Desc	:	��ʼ������
* Input	:
* Output:
* Return:
*****************************************************************/
int gxxServer_Init(void)
{
	struct server_Mngr		*pSvrMngr = &gSvrMngr;

	/* �ṹ���ʼ�� */
	pSvrMngr->coTaskFlag = 0;
	pSvrMngr->coTaskNum = 0;

	/* ��ʼ��Э��ṹ */
	pSvrMngr->pSvrInfo = &gxxServerInfo;
	memset(pSvrMngr->pSvrInfo, 0, sizeof(struct gxxServer_Info));
	pSvrMngr->pSvrInfo->ucUart = UART_INTTL;
	InitRingBuffer(&pSvrMngr->pSvrInfo->RingBuf_In, SVR_RECVBUF_LEN, gSvr_InRingBuf);


	return 0;
}


