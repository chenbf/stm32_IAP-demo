/******************************************************************
 ** �ļ���:RingBuffer.h
 ** Copyright (c) 2012 �㶫������ͨ�Źɷ����޹�˾Ƕ��ʽ�����
 
 ** ������: ����
 ** ��  ��: 2013-02-25
 ** ��  ��: ���λ��������ܵ�ͷ�ļ�
 ** ��  ��: V1.0

 ** �޸���:
 ** ��  ��:
 ** �޸�����:
 ** ��  ��: 
******************************************************************/

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

/*****************************************************************
* ����ͷ�ļ�(���������Ҫ��H�ļ��������������H�ļ�)
******************************************************************/



#ifdef __cplusplus 
extern "C" { 
#endif 
	

/** 
 * @ingroup C_RINGBUFFER ���λ���
 * 
 * @{ 
 */ 

/*****************************************************************
* �궨��
******************************************************************/

#define    min(a,b)      (((a) < (b)) ? (a) : (b))
#define    max(a,b)  (((a) > (b)) ? (a) : (b)) 

/*****************************************************************
* �ṹ����
******************************************************************/

/** @brief ���������ݽṹ*/      
struct RingBuffer
{
    unsigned char	 *pBuffer;			//< ������
	unsigned char	 *pHead;			//< ���ݿ�ʼָ��
	unsigned char	 *pTail;			//< ���ݽ���ָ��
	unsigned char	 *pEndbuffer;		//< ������β��
	int				 nBufferLen;		//< ����������
   //OS_MUTEX  lock;              //< ��
};

/*****************************************************************
* ȫ�ֱ�������
******************************************************************/

/*****************************************************************
* ����ԭ������
******************************************************************/

int InitRingBuffer(struct RingBuffer *pRingBuffer, int nBufferLen,unsigned char	 *pBuffer);
int DeInitRingBuffer(struct RingBuffer *pRingBuffer);
int RingBufferRead(unsigned char *pBuffer, int nLen,struct RingBuffer *pRingBuffer);
int RingBufferWrite(unsigned char *pBuffer, int nLen, struct RingBuffer *pRingBuffer);
int RingBufferReadMax(struct RingBuffer *pRingBuffer);
int RingBufferWriteMax(struct RingBuffer *pRingBuffer);
int RingBufferReadAdj(struct RingBuffer *pRingBuffer, int nSize);
int RingBufferWriteAdj(struct RingBuffer *pRingBuffer, int nSize);
int RingBufferFlush(struct RingBuffer *pRingBuffer);
int RingBufferLen(struct RingBuffer *pRingBuffer);
int RingBufferEmptyLen(struct RingBuffer *pRingBuffer);

/*****************************************************************
* ����˵��
******************************************************************/

/* @} C_RINGBUFFER */ 

#ifdef __cplusplus 
} 
#endif  
#endif

