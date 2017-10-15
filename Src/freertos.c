/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "stm32f4xx_hal.h"
#include "sys.h"
#include "uart.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId Task_LEDHandle;

/* USER CODE BEGIN Variables */
osThreadId Task_usartHandle;
osThreadId Task_WIFIHandle;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void Func_LED(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void Func_usart(void const * argument);
void Func_WIFI(void const * argument);
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Task_LED */
  osThreadDef(Task_LED, Func_LED, osPriorityNormal, 0, 128);
  Task_LEDHandle = osThreadCreate(osThread(Task_LED), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  osThreadDef(Task_usart, Func_usart, osPriorityNormal, 0, 128);
  Task_LEDHandle = osThreadCreate(osThread(Task_usart), NULL);
  osThreadDef(Task_WIFI, Func_WIFI, osPriorityNormal, 0, 128);
  Task_LEDHandle = osThreadCreate(osThread(Task_WIFI), NULL);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Func_LED function */
void Func_LED(void const * argument)
{
  /* USER CODE BEGIN Func_LED */
  /* Infinite loop */
  for(;;)
  {
//    HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
//    osDelay(500);
//    HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
//    osDelay(500);
    
    osDelay(1);
  }
  /* USER CODE END Func_LED */
}

/* USER CODE BEGIN Application */
void Func_usart(void const * argument)
{
  /* USER CODE BEGIN Func_LED */
  
	u8 len;
  u8 m[20] = "AT";
  
  LCD_ShowString(30,40,210,24,24,"Explorer STM32F4");	
		LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
		LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
 		      					 
		LCD_ShowString(30,130,200,12,12,"2014/5/4");	
  /* Infinite loop */
  for(;;)
  {
    if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//���ͽ��յ�������
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}
    osDelay(1);
    
  }
  
  /* USER CODE END Func_LED */
}
 

void Func_WIFI(void const * argument)
{
  /* USER CODE BEGIN Func_LED */
	u8 length;
  u8 key;
  /* Infinite loop */
  for(;;)
  {
    if(USART3_RX_STA&0x8000)
		{					   
			length=USART3_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			HAL_UART_Transmit(&huart3,(uint8_t*)USART3_RX_BUF,length,1000);	//���ͽ��յ�������
			while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
			printf("\r\n\r\n");//���뻻��
			USART3_RX_STA=0;
		}
    //HAL_UART_Transmit(&huart3,(uint8_t*)m ,3,1000);
    key=KEY_Scan(0);            //����ɨ��
     printf("%d",key);
				switch(key)
				{				 
					case  WKUP_PRES:	//����LED0,LED1�������
								HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
								HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
								break;
					case  KEY2_PRES:	//����LED0��ת
								 HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
								break;
					case  KEY1_PRES:	//����LED1��ת	 
								 HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
								break;
					case  KEY0_PRES:	//ͬʱ����LED0,LED1��ת 
								 HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
								 HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
								break;
			}
        
    osDelay(1);
    
    
  }
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
