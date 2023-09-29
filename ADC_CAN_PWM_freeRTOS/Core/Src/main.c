/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;

CAN_HandleTypeDef hcan1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim9;
TIM_HandleTypeDef htim12;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC3_Init(void);
static void MX_CAN1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM8_Init(void);
static void MX_TIM9_Init(void);
static void MX_TIM12_Init(void);
/* USER CODE BEGIN PFP */
static void ADC_Task(void* parameter);
static void task1_handler(void* parameters);
static void LED_Task(void* parameters);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

TaskHandle_t ADC_Handle;

uint16_t ADC_VAL[21];

float Voltage;


CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint8_t TxData[8];
uint8_t RxData[8];

uint32_t TxMailbox;

int datacheck = 0;

uint8_t receivedopertion = 0;
uint8_t receivedID = 0;
TaskHandle_t ledHandle;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	printf("button pressed\n");
	if(GPIO_Pin == USER_Btn_Pin)
	{
		TxData[0]=250;
		TxData[1]=10;

		if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
		{
			printf("msg NOT sent \n into the error_handler\n");
		    Error_Handler();
		}
		  HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
		  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		printf("msg sent\n");
	}
}


static void task1_handler(void* parameters)
{
    while (1)
    {
        if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) != GPIO_PIN_RESET)
        {
            HAL_GPIO_EXTI_Callback(USER_Btn_Pin);
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay the task for 100 milliseconds
    	taskYIELD();
    }
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData);

    if (RxHeader.DLC == 8)
    {
    	receivedopertion = RxData[0];
    	receivedID = RxData[1];
    	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    	xTaskNotifyFromISR(ledHandle, 0, eNoAction, &xHigherPriorityTaskWoken);
    	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

static void LED_Task(void* parameters)
{
    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // Wait for a notification

        printf("Task notified\n");

//      // Toggle LEDs based on receivedBlinkCount and receivedDelay
//        for (int i = 0; i < receivedBlinkCount; i++)
//        {
//            printf("Rxdata %d, %d\n", receivedDelay, receivedBlinkCount);
//            HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
//            HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
//            HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
//            vTaskDelay(pdMS_TO_TICKS(receivedDelay));
//        }
        if(RxData[0] == 0x01)
        {
        	TxData[0] = 0;
        	TxData[1] = 0;
        	TxData[2] = (uint8_t) TIM1->CCR1;
        	TxData[3] = 0;
        	TxData[4] = 0;
        	TxData[5] = 0;
        	TxData[6] = 0x81;
        	TxData[7] = 0;
        	if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
        	{
        		printf("msg NOT sent \n into the error_handler\n");
        		Error_Handler();
        	}
        	printf("Read req from CAN BUS (%d, %d, %d, %d, %d, %d, %d, %d)\n",TxData[0],TxData[1],TxData[2],TxData[3],TxData[4],TxData[5],TxData[6],TxData[7]);
        }

        else if (RxData[0] == 0x02)
        {
        	TxData[0] = RxData[0];
        	TxData[1] = RxData[1];
        	TxData[2] = RxData[2];
        	TxData[3] = RxData[3];
        	TxData[4] = RxData[4];
        	TxData[5] = RxData[5];
        	TxData[6] = 0x82;
        	TxData[7] = RxData[7];

        	printf("Write req from CAN BUS (%d, %d, %d, %d, %d, %d, %d, %d)\n",TxData[0],TxData[1],TxData[2],TxData[3],TxData[4],TxData[5],TxData[6],TxData[7]);

        	if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
        	{
        		printf("msg NOT sent \n into the error_handler\n");
        		Error_Handler();
        	}
        }
        else
        {
        	printf("Operation does not match \n");
        }

    }
}


void CH_Select1(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_1;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select2(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_2;
	  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select3(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_3;
	  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select4(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_4;
	  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select5(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_5;
	  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select6(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_10;
	  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select7(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_11;
	  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select8(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_12;
	  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select9(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_13;
	  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select10(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_14;
	  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select11(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_15;
		  sConfig.Rank = 1;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select12(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_4;
	  sConfig.Rank = 2;
	  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select13(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_5;
	  sConfig.Rank = 2;

    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select14(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_6;
	  sConfig.Rank = 2;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select15(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_7;
	  sConfig.Rank = 2;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select16(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	 sConfig.Channel = ADC_CHANNEL_8;
	  sConfig.Rank = 2;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select17(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_9;
	  sConfig.Rank = 2;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
//void CH_Select18(void)
//{
//	ADC_ChannelConfTypeDef sConfig = {0};
//    sConfig.Channel = ADC_CHANNEL_5;
//    sConfig.Rank = 2;
//    sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
//    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//    {
//       Error_Handler();
//    }
//}
//void CH_Select19(void)
//{
//	ADC_ChannelConfTypeDef sConfig = {0};
//    sConfig.Channel = ADC_CHANNEL_6;
//    sConfig.Rank = 2;
//    sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
//    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//    {
//       Error_Handler();
//    }
//}
//void CH_Select20(void)
//{
//	ADC_ChannelConfTypeDef sConfig = {0};
//    sConfig.Channel = ADC_CHANNEL_7;
//    sConfig.Rank = 2;
//    sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
//    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//    {
//       Error_Handler();
//    }
//}
//void CH_Select21(void)
//{
//	ADC_ChannelConfTypeDef sConfig = {0};
//    sConfig.Channel = ADC_CHANNEL_8;
//    sConfig.Rank = 2;
//    sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
//    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//    {
//       Error_Handler();
//    }
//}
//

static void ADC_Task(void* parameter)
{
	while(1)
	{
        CH_Select1();
        HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,1000);
	 	ADC_VAL[0]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[0]*3.3)/4095;
	 	TIM1->CCR1=ADC_VAL[0];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select2();
        HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,10);
	 	ADC_VAL[1]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[1]*3.3)/4095;
	 	TIM1->CCR2=ADC_VAL[1];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select3();
        HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,10);
	 	ADC_VAL[2]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[2]*3.3)/4095;
	 	TIM1->CCR3=ADC_VAL[2];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select4();
        HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,10);
	 	ADC_VAL[3]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[3]*3.3)/4095;
	 	TIM1->CCR4=ADC_VAL[3];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select5();
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1,10);
        ADC_VAL[4]=HAL_ADC_GetValue(&hadc1);
        vTaskDelay(pdMS_TO_TICKS(50));
        HAL_ADC_Stop(&hadc1);
        Voltage=(float)(ADC_VAL[4]*3.3)/4095;
        TIM3->CCR1=ADC_VAL[4];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

	 	CH_Select6();
	 	HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,10);
	 	ADC_VAL[5]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[5]*3.3)/4095;
	 	TIM3->CCR2=ADC_VAL[5];
        //vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select7();
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1,10);
        ADC_VAL[6]=HAL_ADC_GetValue(&hadc1);
        vTaskDelay(pdMS_TO_TICKS(50));
        HAL_ADC_Stop(&hadc1);
        Voltage=(float)(ADC_VAL[6]*3.3)/4095;
        TIM3->CCR3=ADC_VAL[6];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select8();
        HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,10);
	 	ADC_VAL[7]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[7]*3.3)/4095;
	 	TIM3->CCR4=ADC_VAL[7];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select9();
        HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,10);
	 	ADC_VAL[8]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[8]*3.3)/4095;
	 	TIM4->CCR1=ADC_VAL[8];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select10();
        HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,10);
	 	ADC_VAL[9]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[9]*3.3)/4095;
	 	TIM4->CCR2=ADC_VAL[9];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select11();
        HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,10);
		ADC_VAL[10]=HAL_ADC_GetValue(&hadc1);
		vTaskDelay(pdMS_TO_TICKS(50));
		HAL_ADC_Stop(&hadc1);
		Voltage=(float)(ADC_VAL[10]*3.3)/4095;
	 	TIM4->CCR3=ADC_VAL[10];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select12();
        HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,10);
	 	ADC_VAL[11]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[11]*3.3)/4095;
	 	TIM4->CCR4=ADC_VAL[11];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select13();
        HAL_ADC_Start(&hadc1);
	 	HAL_ADC_PollForConversion(&hadc1,10);
	 	ADC_VAL[12]=HAL_ADC_GetValue(&hadc1);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc1);
	 	Voltage=(float)(ADC_VAL[12]*3.3)/4095;
	 	TIM8->CCR1=ADC_VAL[12];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select14();
        HAL_ADC_Start(&hadc3);
	 	HAL_ADC_PollForConversion(&hadc3,10);
	 	ADC_VAL[13]=HAL_ADC_GetValue(&hadc3);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc3);
	 	Voltage=(float)(ADC_VAL[13]*3.3)/4095;
	 	TIM8->CCR2=ADC_VAL[13];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select15();
        HAL_ADC_Start(&hadc3);
	 	HAL_ADC_PollForConversion(&hadc3,10);
	 	ADC_VAL[14]=HAL_ADC_GetValue(&hadc3);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc3);
	 	Voltage=(float)(ADC_VAL[14]*3.3)/4095;
	 	TIM9->CCR1=ADC_VAL[14];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select16();
        HAL_ADC_Start(&hadc3);
	 	HAL_ADC_PollForConversion(&hadc3,1000);
	 	ADC_VAL[15]=HAL_ADC_GetValue(&hadc3);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc3);
	 	Voltage=(float)(ADC_VAL[15]*3.3)/4095;
	 	TIM9->CCR2=ADC_VAL[15];
	 	//vTaskDelay(pdMS_TO_TICKS(100));

        CH_Select17();
        HAL_ADC_Start(&hadc3);
	 	HAL_ADC_PollForConversion(&hadc3,10);
	 	ADC_VAL[16]=HAL_ADC_GetValue(&hadc3);
	 	vTaskDelay(pdMS_TO_TICKS(50));
	 	HAL_ADC_Stop(&hadc3);
	 	Voltage=(float)(ADC_VAL[16]*3.3)/4095;
	 	TIM12->CCR2=ADC_VAL[16];
	 	//vTaskDelay(pdMS_TO_TICKS(100));
//
//        CH_Select18();
//        HAL_ADC_Start(&hadc3);
//	 	HAL_ADC_PollForConversion(&hadc3,10);
//	 	ADC_VAL[17]=HAL_ADC_GetValue(&hadc3);
//	 	vTaskDelay(pdMS_TO_TICKS(50));
//	 	HAL_ADC_Stop(&hadc3);
//	 	Voltage=(float)(ADC_VAL[17]*3.3)/4095;
//	 	//vTaskDelay(pdMS_TO_TICKS(100));
//
//	 	CH_Select19();
//		HAL_ADC_Start(&hadc3);
//		HAL_ADC_PollForConversion(&hadc3,10);
//		ADC_VAL[18]=HAL_ADC_GetValue(&hadc3);
//		vTaskDelay(pdMS_TO_TICKS(50));
//		HAL_ADC_Stop(&hadc3);
//		Voltage=(float)(ADC_VAL[18]*3.3)/4095;
//
//        CH_Select20();
//        HAL_ADC_Start(&hadc3);
//	 	HAL_ADC_PollForConversion(&hadc3,10);
//	 	ADC_VAL[19]=HAL_ADC_GetValue(&hadc3);
//	 	vTaskDelay(pdMS_TO_TICKS(50));
//	 	HAL_ADC_Stop(&hadc3);
//	 	Voltage=(float)(ADC_VAL[19]*3.3)/4095;
//
//        CH_Select21();
//        HAL_ADC_Start(&hadc3);
//	 	HAL_ADC_PollForConversion(&hadc3,10);
//	 	ADC_VAL[20]=HAL_ADC_GetValue(&hadc3);
//	 	vTaskDelay(pdMS_TO_TICKS(50));
//	 	HAL_ADC_Stop(&hadc3);
//	 	Voltage=(float)(ADC_VAL[20]*3.3)/4095;
//	 	vTaskDelay(pdMS_TO_TICKS(100));
	}
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	BaseType_t status;

	TaskHandle_t task1_handle;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC3_Init();
  MX_CAN1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_TIM9_Init();
  MX_TIM12_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  TIM1->CCR1=ADC_VAL[0];
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
  TIM1->CCR2=ADC_VAL[1];
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
  TIM1->CCR3=ADC_VAL[2];
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
  TIM1->CCR4=ADC_VAL[3];
  /*       __________________________________________________________________     */

  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  TIM3->CCR1=ADC_VAL[4];
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
  TIM3->CCR2=ADC_VAL[5];
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
  TIM3->CCR3=ADC_VAL[6];
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
  TIM3->CCR4=ADC_VAL[7];
  /*       __________________________________________________________________     */

  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
  TIM4->CCR1=ADC_VAL[8];
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
  TIM4->CCR2=ADC_VAL[9];
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
  TIM4->CCR3=ADC_VAL[10];
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
  TIM4->CCR4=ADC_VAL[11];
  /*       __________________________________________________________________     */

  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
  TIM8->CCR1=ADC_VAL[12];
  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
  TIM8->CCR2=ADC_VAL[13];
  /*       __________________________________________________________________     */
  HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
  TIM9->CCR1=ADC_VAL[14];
  HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
  TIM9->CCR2=ADC_VAL[15];
  HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);
  TIM12->CCR2=ADC_VAL[16];

  if(HAL_CAN_Start(&hcan1) != HAL_OK)
  {
	  Error_Handler();
  }

  if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
	  Error_Handler();
  }

  TxHeader.DLC = 8;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.StdId = 0x446;

  status = xTaskCreate(ADC_Task, "Task-ADC", 200, NULL, 2, &ADC_Handle);

  configASSERT(status == pdPASS);

  status = xTaskCreate(task1_handler, "Task-1", 200, NULL, 2, &task1_handle);

  configASSERT(status == pdPASS);

  status = xTaskCreate(LED_Task, "LED_Task", 200, NULL, 2, &ledHandle);

  configASSERT(status == pdPASS);

  vTaskStartScheduler();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 11;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
//  sConfig.Channel = ADC_CHANNEL_1;
//  sConfig.Rank = 1;
//  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_2;
//  sConfig.Rank = 2;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_3;
//  sConfig.Rank = 3;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_4;
//  sConfig.Rank = 4;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_5;
//  sConfig.Rank = 5;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_10;
//  sConfig.Rank = 6;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_11;
//  sConfig.Rank = 7;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_12;
//  sConfig.Rank = 8;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_13;
//  sConfig.Rank = 9;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_14;
//  sConfig.Rank = 10;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_15;
//  sConfig.Rank = 11;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ENABLE;
  hadc3.Init.ContinuousConvMode = ENABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 6;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_4;
//  sConfig.Rank = 1;
//  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_5;
//  sConfig.Rank = 2;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_6;
//  sConfig.Rank = 3;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_7;
//  sConfig.Rank = 4;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_8;
//  sConfig.Rank = 5;
//  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_9;
//  sConfig.Rank = 6;
//  sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 5;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_15TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  CAN_FilterTypeDef filter;

      filter.FilterActivation = CAN_FILTER_ENABLE;
      filter.FilterBank = 0;//18;
      filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
      filter.FilterIdHigh = 0x0000;//0x103<<5;
      filter.FilterIdLow = 0x0000;
      filter.FilterMaskIdHigh = 0x0000;//0x103<<5;
      filter.FilterMaskIdLow = 0x0000;
      filter.FilterMode = CAN_FILTERMODE_IDMASK;
      filter.FilterScale = CAN_FILTERSCALE_32BIT;
      filter.SlaveStartFilterBank = 0;//20;

      if(HAL_CAN_ConfigFilter(&hcan1, &filter) != HAL_OK)
      {
    	  Error_Handler();
      }

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 0;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 65535;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */
  HAL_TIM_MspPostInit(&htim8);

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 0;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 65535;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */
  HAL_TIM_MspPostInit(&htim9);

}

/**
  * @brief TIM12 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM12_Init(void)
{

  /* USER CODE BEGIN TIM12_Init 0 */

  /* USER CODE END TIM12_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM12_Init 1 */

  /* USER CODE END TIM12_Init 1 */
  htim12.Instance = TIM12;
  htim12.Init.Prescaler = 0;
  htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim12.Init.Period = 65535;
  htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM12_Init 2 */

  /* USER CODE END TIM12_Init 2 */
  HAL_TIM_MspPostInit(&htim12);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : STLK_RX_Pin STLK_TX_Pin */
  GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PG6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_SOF_Pin USB_ID_Pin USB_DM_Pin USB_DP_Pin */
  GPIO_InitStruct.Pin = USB_SOF_Pin|USB_ID_Pin|USB_DM_Pin|USB_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_VBUS_Pin */
  GPIO_InitStruct.Pin = USB_VBUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_VBUS_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM5 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM5) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
