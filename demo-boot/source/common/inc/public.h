/*****************************************************************
** �ļ��� : public.h
** 2015-2016 �����˿Ƽ����Źɷ����޹�˾ Co.Ltd
 
** ������: ���
** ��  ��: 2017-02-21
** ��  ��: 
** ��  ��: 

** �޸���:
** ��  ��:
** �޸�����:
** ��  ��: 
******************************************************************/

#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#ifdef __cplusplus 
extern "C" { 
#endif
 
/*****************************************************************
*  ����ͷ�ļ������������Ҫ��H�ļ��������������H�ļ���
******************************************************************/
#include "typedef.h"

/** 
 * @ingroup C_PUBLIC  ��������
 * @{ 
 */ 

/*****************************************************************
* �궨��
******************************************************************/
#define MIN(x,y)		((x)>(y) ? (y) : (x))

#define MAX(x,y)		((x)>(y) ? (x) : (y))

#define NETCONN_UP_ALIGN(size, align) (((INT16U)(size) + (align) - 1) & (~((align) - 1))) ///���϶���
#define NETCONN_ALIGN(size, align) (((UINT16)(size) ) & (~((align) - 1)))    ///< ���¶���

/*****************************************************************
* �ṹ����
******************************************************************/

/*****************************************************************
* ȫ�ֱ�������
******************************************************************/

/*****************************************************************
* ��̬��������
******************************************************************/

/*****************************************************************
* ����ԭ������
******************************************************************/
UINT16 crc16(UINT16 crc, UINT8 const *buffer, INT32 len);
void hextobcd(INT8U *pData);


#ifdef __cplusplus 
} 
#endif

#endif

/* @} C_PUBLIC */ 
