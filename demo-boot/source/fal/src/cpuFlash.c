/**
  ******************************************************************************
  * @file           : cpuFlash.c
  * @brief          : cpu�ڲ�flash
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
#include <string.h>
#include "cpuFlash.h"
#include "gpio.h"


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
* �ⲿ��������
******************************************************************/

/*****************************************************************
* ��̬��������
******************************************************************/

/*****************************************************************
* ����ԭ������
******************************************************************/

/*****************************************************************
* ��������
******************************************************************/

/****************************************************************
* Func 	:
* Desc	:	��ȡCPU�ڲ�flash
* Input	:
* Output:
* Return:
*****************************************************************/
INT32 cpuflash_read(UINT32 unStartAddr, UINT8 *pData, UINT16 usSize)
{

	if(pData == NULL)
		return -1;

	memcpy(pData, (INT8U *)unStartAddr, usSize);

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	д��CPU�ڲ�flash (Ҫ��erase����д)
* Input	:
* Output:
* Return:
*****************************************************************/
INT32 cpuflash_write(UINT32 unStartAddr, UINT8 *pData, UINT16 usSize)
{
	INT32 	i = 0;
    INT32 	nRet = 0;
    UINT16 	usTemp1 = 0;
    UINT16 	usTemp2 = 0;
    UINT16 	usTempALL = 0;

	
    if(usSize%2 != 0)
    {
        usSize += 1;
    }

	HAL_FLASH_Unlock();		// unlock
	
    for(i=0; i<usSize/2; i++)
    {
		usTemp1 = *pData;
		usTemp2 = *(pData+1);
		usTempALL = ((usTemp1&0X00FF) | ((usTemp2<<8)&0XFF00));
		//usTemp = ((*pData>>8)&0X00FF) | (*(pData+1)&0XFF00);
		//usTemp = *(INT16U *)pData;/*����ᵼ��Ӳ������*/
		nRet = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, unStartAddr, usTempALL);
		if(nRet != HAL_OK)
		{
			HAL_FLASH_Lock();		// lock
			printf("ERROR: %s: program[%d %d] failed-code[%d]\n", __FUNCTION__, usTemp1, usTemp2, nRet);
			return -1;
		}
	
		unStartAddr += 2;
		pData += 2;
	}

    HAL_FLASH_Lock();		// lock

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	����CPU�ڲ�flash(��ҳ)
* Input	:
* Output:
* Return:
*****************************************************************/
INT32 cpuflash_erase(UINT32 unStartAddr, UINT32 unEndAddr)
{
	FLASH_EraseInitTypeDef	stEraseInit;
	UINT32		ucPageErr = 0;
    UINT32  	unTempAddr = 0;
	INT32		nRet = 0;


	HAL_FLASH_Unlock();		// unlock

	for(unTempAddr=unStartAddr; unTempAddr<=unEndAddr; unTempAddr+=FLASH_PAGE_SIZE)
	{
		stEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
		stEraseInit.PageAddress = unTempAddr;
		stEraseInit.NbPages = 1;
		nRet = HAL_FLASHEx_Erase(&stEraseInit, &ucPageErr);
		if(nRet != HAL_OK)
		{
			HAL_FLASH_Lock();
			return -1;
		}
		GPIO_feedDog();
	}

    HAL_FLASH_Lock();		// lock

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	ʹ�ܶ���������
* Input	:
* Output:
* Return:
*****************************************************************/
void cpuflash_enableReadProtect(void)
{
  FLASH_OBProgramInitTypeDef OBInit;
  
  __HAL_FLASH_PREFETCH_BUFFER_DISABLE();
  
  HAL_FLASHEx_OBGetConfig(&OBInit);
  if(OBInit.RDPLevel == OB_RDP_LEVEL_0)
  {
  	printf("%s: ------------ set ----------\n", __FUNCTION__);
    OBInit.OptionType = OPTIONBYTE_RDP;
    OBInit.RDPLevel = OB_RDP_LEVEL_1;
    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();
    HAL_FLASHEx_OBProgram(&OBInit);
    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
	//HAL_FLASH_OB_Launch();
  }
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();

}

/****************************************************************
* Func 	:
* Desc	:	ʧ�ܶ���������
* Input	:
* Output:
* Return:
*****************************************************************/
void cpuflash_disableReadProtect(void)
{
  FLASH_OBProgramInitTypeDef OBInit;
  
  __HAL_FLASH_PREFETCH_BUFFER_DISABLE();
  
  HAL_FLASHEx_OBGetConfig(&OBInit);
  if(OBInit.RDPLevel == OB_RDP_LEVEL_1)
  {
	  printf("%s: ------------ set ----------\n", __FUNCTION__);
    OBInit.OptionType = OPTIONBYTE_RDP;
    OBInit.RDPLevel = OB_RDP_LEVEL_0;
    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();
    HAL_FLASHEx_OBProgram(&OBInit);
    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
	//HAL_FLASH_OB_Launch();
  }
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();

}

/****************************************************************
* Func 	:
* Desc	:	��ʼ������
* Input	:
* Output:
* Return:
*****************************************************************/
int cpuflash_Init(void)
{

	/* ����������-��bootloader�������� */
	//cpuflash_enableReadProtect();

	return 0;
}


