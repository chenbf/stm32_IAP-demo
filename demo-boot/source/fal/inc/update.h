/**
  ******************************************************************************
  * @file           : update.h
  * @brief          : header file
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _UPDATE_H_
#define _UPDATE_H_

/*****************************************************************
* ����ͷ�ļ�
******************************************************************/
#include "stm32f1xx_hal.h"
#include "typedef.h"

/*****************************************************************
* �궨��
******************************************************************/

/* bootloader������־ */
#define BOOT_FLAG_NORMAL_RUNAPP		0x0A		// ��������APP
#define BOOT_FLAG_WAIT_UPGRADE		0x0B		// �ȴ�����
#define BOOT_FLAG_FORCE_RUNAPP		0x0F		// ǿ������APP

/*****************************************************************
* �ṹ��ö�ٶ���
******************************************************************/

typedef enum 
{
	UPD_STA_IDLE,
	UPD_STA_ING,
	UPD_STA_OK,
	UPD_STA_FAILED,
}Update_Status;

/* flash��������Ϣ�ṹ */
struct param_info
{
	UINT16		usStartFlag;				// ������־ 0x0A-����APP 0x0B-�ȴ����� 0x0F-��ǿ��������
};

/* �����ļ�ͷ��APP��Ϣ */
struct APP_headinfo
{
	UINT32	unVersion;				// APP�汾��
	UINT32	unCrcCheck;				// CRCУ����
	UINT32	unAPPSize;	            // APP�����С
	UINT32	unCreateTime;			// ����ʱ��
	UINT32	unLoadAddr;				// ���ص�ַ
};


/*****************************************************************
* ȫ�ֱ�������
******************************************************************/

/*****************************************************************
* ����ԭ������
******************************************************************/
int update_packDataHandle(UINT16 usSeq, UINT8 *pData, UINT16 usDatalen, struct APP_headinfo *pstAPPHead);
Update_Status update_getStatus(void);

int update_Init(void);


#endif
