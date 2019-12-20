/**
  ******************************************************************************
  * @file           : usart.h
  * @brief          : header file
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _USART_H_
#define _USART_H_

/*****************************************************************
* ����ͷ�ļ�
******************************************************************/
#include "stm32f1xx_hal.h"
#include "typedef.h"

/*****************************************************************
* �궨��
******************************************************************/
#define UART_BUFSIZE_RX 		512
#define UART_BUFSIZE_TX 		512

#define UART_INTTL				1
#define UART_DEBUG				5

#define UART_MAX_CNT			2		// UART����

/*****************************************************************
* �ṹ��ö�ٶ���
******************************************************************/
struct uart_data
{
	UINT8 		ucRxBuf[UART_BUFSIZE_RX];		// ���ջ��λ�����
	//UINT8 		ucTxBuf[UART_BUFSIZE_TX];		// ���ͻ�����
	UINT16 		usRdPos;						// ���ν��ջ�������λ��
	UINT16 		usWrPos;						// ���ν��ջ�����дλ��
	UINT16 		usLen;							// ���ݳ���
	UINT8		ucIT_flag;						// �жϿ�����־ 0-�ɹ�����
};

/*****************************************************************
* ȫ�ֱ�������
******************************************************************/

/*****************************************************************
* ����ԭ������
******************************************************************/
int UART_SEND(UINT8 ucUartNum, UINT8 *pData, UINT16 usLen);
int UART_READ(UINT8 ucUartNum, UINT8 *pBuf, UINT16 usSize);

void MX_USART1_UART_Init(void);
void MX_UART5_Init(void);
void MX_UART_Init(void);
void printHex(char *pBuff, int nlen, char *pTempBuf);


#endif
