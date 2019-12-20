/******************************************************************
 ** �ļ���:RingBuffer.c
 ** Copyright (c) 2012 �㶫������ͨ�Źɷ����޹�˾Ƕ��ʽ�����
 
 ** ������: ����
 ** ��  ��: 2013-02-25
 ** ��  ��: ʵ�ֻ��λ��������ܣ���ͷ��д����β����,֧��һ���̶߳���һ���߳�д
            ���Ҫ֧�ֶ���߳�д���������ⲿ�û����ơ�
 ** ��  ��: V1.0

 ** �޸���:
 ** ��  ��:
 ** �޸�����:
 ** ��  ��: 
******************************************************************/

/*****************************************************************
* ����ͷ�ļ�
******************************************************************/

//#include "includes.h"

#include "RingBuffer.h"

//#include "memPool.h"

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus 
extern "C" { 
#endif 

/** 
 * @addtogroup Go_COMMON
 * @{ 
 */ 
 
/** 
 * @defgroup C_RINGBUFFER ���λ���
 * 
 * @brief \n
 * \n
 * @{ 
 */ 

/*****************************************************************
* �궨��
******************************************************************/

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

/******************************************************************/
/**
* ��ջ�����\n 

* @param[in/out] pRingBuffer �������ṹָ��
* @return ���ز������
*   - 1   �ɹ�
*   - -1  ʧ��

* @author:         
* @date           

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferFlush(struct RingBuffer *pRingBuffer)
{
    //CPU_TS ts;
	 //OS_ERR err;
     /*�����Ϸ����ж�*/
     if( NULL == pRingBuffer )
     {
         return -1;
     }
     /*����*/
     //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);

     pRingBuffer->pHead = pRingBuffer->pBuffer;
     pRingBuffer->pTail = pRingBuffer->pBuffer;
     
     /*����*/
     //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

     return 1;
}

/******************************************************************/
/**
* ��ȡ���������ݳ���\n 

* @param[in] pRingBuffer �������ṹָ��

* @return
*  - ��-1 �������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferLen(struct RingBuffer *pRingBuffer)
{
    int nDataLen;
     //CPU_TS ts;
	 //OS_ERR err;

    if( NULL == pRingBuffer )
    {
        return -1;
    }

    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    nDataLen = (pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->pHead - pRingBuffer->pTail)
           :(pRingBuffer->nBufferLen + (pRingBuffer->pHead - pRingBuffer->pTail));
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

    return nDataLen;
}

/******************************************************************/
/**
* ��ȡ���������ݳ���\n 

* @param[in] pRingBuffer �������ṹָ��

* @return
*  - ��-1 �������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferEmptyLen(struct RingBuffer *pRingBuffer)
{
    int nDataLen;
     //CPU_TS ts;
	 //OS_ERR err;

    if( NULL == pRingBuffer )
    {
        return -1;
    }

    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    nDataLen = (pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->nBufferLen  - (pRingBuffer->pHead - pRingBuffer->pTail))
           :(pRingBuffer->pTail - pRingBuffer->pHead);
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

    return nDataLen;

}

/******************************************************************/
/**
* ��ȡ���ɶ�����\n 

* @param[in] pRingBuffer  Ringbufָ��

* @return
*  - ��-1 ����ʵ�ʿɶ���������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferReadMax(struct RingBuffer *pRingBuffer)
{
    int nReadMax;
    int nDataLen;
    int nLineLen;
     //CPU_TS ts;
	 //OS_ERR err;

    if(NULL == pRingBuffer)
    {
        return -1;
    }

    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    nDataLen = ( pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->pHead - pRingBuffer->pTail)
           :(pRingBuffer->nBufferLen + (pRingBuffer->pHead - pRingBuffer->pTail));

	nLineLen = pRingBuffer->pEndbuffer - pRingBuffer->pTail;

	nReadMax = min(nLineLen, nDataLen);

    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

    return nReadMax;
}

/******************************************************************/
/**
* ��ȡ����д����\n 

* @param[in] pRingBuffer  Ringbufָ��

* @return
*  - ��-1 ����ʵ�ʿ�д��������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWriteMax(struct RingBuffer *pRingBuffer)
{
    int nWriteMax;
    int nWriteLen;
    int nLineLen;
    int nDataLen;
     //CPU_TS ts;
	 //OS_ERR err;

    if(NULL == pRingBuffer)
    {
        return -1;
    }
    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    nDataLen = ( pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->pHead - pRingBuffer->pTail)
           :(pRingBuffer->nBufferLen + (pRingBuffer->pHead - pRingBuffer->pTail));

	nWriteLen = pRingBuffer->nBufferLen - nDataLen - 1;

	nLineLen = pRingBuffer->pEndbuffer - pRingBuffer->pHead;

    nWriteMax = min(nWriteLen, nLineLen);
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);

	return nWriteMax;
}

/******************************************************************/
/**
* �����λ���������\n 

* @param[out] pBuffer      ���ݽ��ջ���
* @param[in]  nLen         ���ݽ��ջ��峤��
* @param[in]  pRingBuffer  ���λ�������

* @return
*  - ��-1 ���سɹ���ȡ�����ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferRead(unsigned char *pBuffer, int nLen,struct RingBuffer *pRingBuffer)
{
	 int nReadByte;
     int nReadLen;
     unsigned char *pData;
     //CPU_TS ts;
	 //OS_ERR err;

     /*�����Ϸ����ж�*/
     if( NULL == pBuffer || NULL == pRingBuffer )
	 {
		 return -1;
	 }
	
     /*ѭ����ȡ������*/
	 nReadByte = 0;
     pData = pBuffer;

	 while (nLen > 0) 
     {
		  nReadLen = RingBufferReadMax(pRingBuffer);
		  nReadLen = min(nReadLen, nLen);
		  if (nReadLen <= 0) 
          {
			  break;
		  }

		  memcpy(pData, pRingBuffer->pTail, nReadLen);
		  pData += nReadLen;
		  nLen -= nReadLen;
		  nReadByte += nReadLen;

          /*����β��*/
          //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
          pRingBuffer->pTail += nReadLen;
		  if(pRingBuffer->pTail >= pRingBuffer->pEndbuffer)
          {
			  pRingBuffer->pTail  = pRingBuffer->pBuffer;
		  }
          //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);
	 }
	 return nReadByte;
}

/******************************************************************/
/**
* ���λ�����д��ֻ֧��һ���߳�д\n 

* @param[in]  pBuffer      Ҫд�뻷�λ�����������
* @param[in]  nLen         Ҫд�����ݵ��ֽ���
* @param[in]  pRingBuffer  ���λ�������

* @return
*  - ��-1 ���سɹ�д������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWrite(unsigned char *pBuffer, int nLen, struct RingBuffer *pRingBuffer)
{
	 int nWriteByte;
     int nWriteLen;
     int nDataLen;
     unsigned char *pData;

     //CPU_TS ts;
	 //OS_ERR err;
 
     /*�����Ϸ����ж�*/
     if( NULL == pBuffer || NULL == pRingBuffer )
	 {
		 return -1;
	 }

     /*д����������*/
	 nWriteByte = 0;
     pData = pBuffer;

     nDataLen = RingBufferLen(pRingBuffer);
     if(0 == nDataLen)
     {
          RingBufferFlush(pRingBuffer);
     }

	 while (nLen > 0) 
     {
		nWriteLen = RingBufferWriteMax(pRingBuffer);
		nWriteLen = min(nWriteLen, nLen);

		if (nWriteLen <= 0) 
        {
			return nWriteByte;
		}

		memcpy(pRingBuffer->pHead,pData, nWriteLen);
		pData += nWriteLen;
		nLen -= nWriteLen;
		nWriteByte += nWriteLen;
        /*����ͷ��*/
        //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
        pRingBuffer->pHead += nWriteLen;
		if (pRingBuffer->pHead >= pRingBuffer->pEndbuffer) 
        {
			 pRingBuffer->pHead = pRingBuffer->pBuffer;
		}
        //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);
	}

	return nWriteByte;

}

/******************************************************************/
/**
* ������λ��\n 

* @param[in]  pRingBuffer  ���λ�������
* @param[in]  nSize        �Ѷ�����

* @return
*  - 1   �ɹ�
*  - -1  ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferReadAdj(struct RingBuffer *pRingBuffer, int nSize)
{
		//CPU_TS ts;
		//OS_ERR err;

    /*�Ϸ����ж�*/
    if(NULL == pRingBuffer)
    {
        return -1;
    }
    /*������λ��*/
    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
		pRingBuffer->pTail += nSize;
		if(pRingBuffer->pTail >= pRingBuffer->pEndbuffer) 
    {
			pRingBuffer->pTail -= pRingBuffer->nBufferLen;
		}
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);
    return 1;
}

/******************************************************************/
/**
* ����дλ��\n 

* @param[in]  pRingBuffer  ���λ�������
* @param[in]  nSize        ��д����

* @return
*  - 0   �ɹ�
*  - -1  ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWriteAdj(struct RingBuffer *pRingBuffer, int nSize)
{
		//CPU_TS ts;
		//OS_ERR err;
	
    /*�Ϸ����ж�*/
    if(NULL == pRingBuffer)
    {
        return -1;
    }

    /*����дλ��*/
    //OSMutexPend(&pRingBuffer->lock, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    pRingBuffer->pHead += nSize;
	if ( pRingBuffer->pHead >= pRingBuffer->pEndbuffer)
    {
		pRingBuffer->pHead -= pRingBuffer->nBufferLen;
	}
    //OSMutexPost(&pRingBuffer->lock, OS_OPT_POST_NONE, &err);
    return 1;
}

/******************************************************************/
/**
* ��ʼ�����λ�����\n 

* @param[in]  pRingBuffer  ���λ�������
* @param[in]  nBufferLen   ���ݻ���������

* @return
*  - 1  ���سɹ���ȡ�����ݳ���
*  - -1 ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:������
* @par Date:2017-07-27
* @par Description:ȥ����̬����/�ͷ��ڴ�;���Ӳ���pBuffer(��̬��������ָ��)
*/
/******************************************************************/
int InitRingBuffer(struct RingBuffer *pRingBuffer, int nBufferLen,unsigned char	 *pBuffer)
{
	//OS_ERR err;

	/*�����Ϸ����ж�*/
	if((NULL == pRingBuffer)||(NULL == pBuffer))
	{
		return (-1);
	}

	/*��̬���ٻ�����*/
	//pRingBuffer->pBuffer = malloc(nBufferLen); 

	/*��̬�󶨻�����ָ�뵽RingBuffer�ṹ��*/
	pRingBuffer->pBuffer = pBuffer;
	
	if(NULL == pRingBuffer->pBuffer)
	{
		return (-1);
	}
	pRingBuffer->nBufferLen = nBufferLen;
	pRingBuffer->pHead = pRingBuffer->pBuffer;
	pRingBuffer->pTail = pRingBuffer->pBuffer;
	pRingBuffer->pEndbuffer = &pRingBuffer->pBuffer[nBufferLen];

	//pthread_mutex_init(&pRingBuffer->lock,NULL);
	//OSMutexCreate(&pRingBuffer->lock, "RingBuffer", &err);
	//if(err != OS_ERR_NONE)
	//{
		//return (-1);
	//}

	return (1);

}

/******************************************************************/
/**
* �ͷŻ��λ�����,���øú���ʱ������ȷ��û���������߳�ʹ�øû���\n
* ����Դͨ����ϵͳ���������̺߳���á�\n 

* @param[in]  pRingBuffer  ���λ�������

* @return
*  - 1  ���سɹ���ȡ�����ݳ���
*  - -1 ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:������
* @par Date:2017-07-27
* @par Description:ȥ����̬����/�ͷ��ڴ�
*/
/******************************************************************/
int DeInitRingBuffer(struct RingBuffer *pRingBuffer)
{
		 //OS_ERR err;
	
     /*�����Ϸ����ж�*/
     if(NULL == pRingBuffer)
     {
          return (-1);
     }

     /*��ջ���������*/
     RingBufferFlush(pRingBuffer);

	 /*ȡ����ʵ��������RingBuffer�ṹ���ָ���*/
	 if(pRingBuffer->pBuffer != NULL)
	 {
		  //free(pRingBuffer->pBuffer);
		  pRingBuffer->pBuffer = NULL;
	 }

     //pthread_mutex_destroy(&pRingBuffer->lock);
	 //OSMutexDel(&pRingBuffer->lock, OS_OPT_DEL_NO_PEND, &err);
	 //if(err != OS_ERR_NONE)
	 //{
	//		return (-1);
	 //}
	 return(1);
}

/* @} C_RINGBUFFER */ 
/* @} Go_COMMON */

#ifdef __cplusplus 
} 
#endif  

