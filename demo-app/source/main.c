/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright: https://blog.csdn.net/qq_30155503
  * All rights reserved.
  *
  ******************************************************************************
  */


/** 
 * ���˵�� :��\n
 * �������˼����Ƿֲ㻯��ģ�黯 \n
 * 
 * �����Ϊ����:
 *  ---------------------------------------- 
 * |             PAL : Э������           		| 
 * |----------------------------------------| 
 * |             FAL : ���������           		| 
 * |----------------------------------------| 
 * |             HAL : Ӳ�������      		    | 
 *  ----------------------------------------
 *
 * ģ�黯���:
 *  ------------------------------------------------ 
 * |                         ��                      | 
 * |  -------   -------             -------         | 
 * | | ģ��1 | | ģ��2 |    ...    | ģ��N |        | 
 * |  -------   -------             -------         | 
 *  ------------------------------------------------ 
 *
 */

/*****************************************************************
* ����ͷ�ļ�
******************************************************************/
#include "main.h"
#include "BSP.h"
#include "fal.h"
#include "task.h"
#include "pal.h"
#include "cpuFlash.h"


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
* Desc	:	������
* Input	:
* Output:
* Return:
*****************************************************************/
int main(void)
{

	/* �ж���������ӳ�� */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, FLASH_PAGE_APP_START -NVIC_VectTab_FLASH +FLASH_APP_HEAD_SIZE);


	/* BSP�弶��Դ��ʼ�� */
	BSP_Init();

	printf("\r\n\r\n[%s]: ----------------- Hello app -----------------\r\n", __FUNCTION__);

	/* ���ܲ��ʼ�� */
	fal_Init();

	/* Э����ʼ�� */
	pal_Init();

	
	/* main loop */
	while (1)
	{

		/* ѭ������ */
		Task_EachRound();

		/* �����ȼ����� */
		Deal_HighRank_Task();

		/* �����ȼ����� */
		Deal_MiddleRank_Task();

		/* �����ȼ����� */
		Deal_LowRank_Task();

	}

	//return 0;
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	printf("ERROR: enter Error_Handler !!!\n");
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
