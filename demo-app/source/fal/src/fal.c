/**
  ******************************************************************************
  * @file           : fal.c
  * @brief          : ���ܲ� - functional layer
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
#include "BSP.h"
#include "fal.h"
#include "cpuFlash.h"
#include "public.h"



/*****************************************************************
* �궨��
******************************************************************/
#define IS_NVIC_VECTTAB(VECTTAB) (((VECTTAB) == SRAM_BASE) || \
										  ((VECTTAB) == FLASH_BASE))
										  
#define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)

/*****************************************************************
* �ṹ����
******************************************************************/

/*****************************************************************
* ȫ�ֱ�������
******************************************************************/

/*****************************************************************
* �ⲿ��������
******************************************************************/
extern TIM_HandleTypeDef htim3;

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
* Desc	:	�ж���������ӳ��
* Input	:	flash�ж�������ַ(һ��Ϊ0x08000000U)��ƫ�Ƶ�ַ(flash������д��ַ���NVIC_VectTabƫ��)
* Output:
* Return:
*****************************************************************/
void NVIC_SetVectorTable(UINT32 NVIC_VectTab, UINT32 Offset)
{
  /* Check the parameters */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));

  SCB->VTOR = NVIC_VectTab | (Offset & (UINT32)0x1FFFFF80);
}

/****************************************************************
* Func 	:
* Desc	:	����APP
* Input	:	APP���е�ַ
* Output:
* Return:
*****************************************************************/
void loadAPP(INT32U unLoadAddr)
{
	void (*fnJump2APP)(void);
	INT32U	unJumpAddr;
	
	if(((*(__IO INT32U *)unLoadAddr) & 0x2FFE0000) == 0x20000000)	/* ���ջ����ַ�Ƿ�Ϸ� */
	{
		printf("%s: ----------------------> run APP addr: 0x%x\r\n", __FUNCTION__, unLoadAddr);

		/* �û���������5~8�ֽ�Ϊ����ʼ��ַ(��λ��ַ) */
		unJumpAddr = *(__IO INT32U *)(unLoadAddr + 4);
		fnJump2APP = (void (*)(void))unJumpAddr;
		/* ��ʼ��APP��ջָ��(�û���������ǰ4���ֽ����ڴ��ջ����ַ) */
		__set_MSP(*(__IO INT32U *)unLoadAddr);
		fnJump2APP();
	}
	else
	{
		printf("ERROR: %s: Stack top address is not valid! Can not run func!\r\n", __FUNCTION__);
		while(1);
	}
}

/****************************************************************
* Func 	:
* Desc	:	ǿ�Ƽ���APP
* Input	:	��������ַ��APP����ַ��APP���е�ַ
* Output:
* Return:
*****************************************************************/
int force_loadAPP(UINT32 unParamAddr, UINT32 unAppAddr, UINT32 unAppRunOffset)
{
	struct param_info		stParams = {0};

	printf("%s: ----------> enter ...\n", __FUNCTION__);

	/* ��������-�ж�����APP/����? */
	memset(&stParams, 0, sizeof(struct param_info));
	cpuflash_read(unParamAddr, (UINT8 *)&stParams, sizeof(struct param_info));


	stParams.usStartFlag = BOOT_FLAG_FORCE_RUNAPP;		// ��λ-ǿ������
	cpuflash_erase(unParamAddr, unParamAddr);
	cpuflash_write(unParamAddr, (UINT8 *)&stParams, sizeof(struct param_info));

	HAL_TIM_Base_Stop_IT(&htim3);	// ??? �����ж���ת����-ԭ��δ��
	loadAPP(unAppAddr +unAppRunOffset);

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	����flash����������
* Input	:	��������ַ��APP��ַ��APP���е�ַ
* Output:
* Return:
*****************************************************************/
int check_paramInfo(UINT32 unParamAddr)
{
	struct param_info		stParams = {0};

	/* ��ȡ���� */
	memset(&stParams, 0, sizeof(struct param_info));
	cpuflash_read(unParamAddr, (UINT8 *)&stParams, sizeof(struct param_info));
	if(stParams.usStartFlag == BOOT_FLAG_FORCE_RUNAPP)		// ǿ�������ɹ�-��λ��������
	{
		stParams.usStartFlag = BOOT_FLAG_NORMAL_RUNAPP;
		printf("%s: ------------ set param flag to normal run APP ------------\n", __FUNCTION__);
		
		/* д����� */
		cpuflash_erase(unParamAddr, unParamAddr);
		cpuflash_write(unParamAddr, (UINT8 *)&stParams, sizeof(struct param_info));
	}

	return 0;
}

/****************************************************************
* Func 	:
* Desc	:	��ʼ��FAL��
* Input	:
* Output:
* Return:
*****************************************************************/
int  fal_Init(void)
{

	/* cpu�ڲ�flash��ʼ�� */
	cpuflash_Init();

	/* ������ */
	check_paramInfo(FLASH_PAGE_PARAM_START);

	return 0;
}


