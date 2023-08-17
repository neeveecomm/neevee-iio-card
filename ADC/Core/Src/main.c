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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t ADC_VAL[21];
float Voltage;
void CH_Select1(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_10;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select2(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_11;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select3(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_12;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select4(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_13;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select5(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select6(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select7(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_3;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select8(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_4;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select9(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_5;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select10(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_6;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}void CH_Select11(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_7;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select12(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_14;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select13(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_15;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select14(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_9;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select15(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_14;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select16(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_15;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select17(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_4;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select18(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_5;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select19(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_6;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select20(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_7;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}
void CH_Select21(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_8;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
}


/* USER CODE END 0 */
void channel1(void)
{
	          CH_Select1();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[0]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(2000*ADC_VAL[0]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel2(void)
{
	          CH_Select2();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[1]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[1]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel3(void)
{
	          CH_Select3();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[2]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[2]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel4(void)
{
	          CH_Select4();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[3]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[3]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel5(void)
{
	          CH_Select5();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[4]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[4]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel6(void)
{
	          CH_Select6();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[5]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[5]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel7(void)
{
	          CH_Select7();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[6]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[6]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel8(void)
{
	          CH_Select8();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[7]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[7]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel9(void)
{
	          CH_Select9();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[8]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[8]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel10(void)
{
	          CH_Select10();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[9]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[9]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel11(void)
{
	          CH_Select11();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[10]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[10]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel12(void)
{
	          CH_Select12();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[11]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[11]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel13(void)
{
	          CH_Select13();
	          HAL_ADC_Start(&hadc1);
		 	  HAL_ADC_PollForConversion(&hadc1,10);
		 	  ADC_VAL[12]=HAL_ADC_GetValue(&hadc1);
		 	  HAL_ADC_Stop(&hadc1);
		 	  Voltage=(float)(ADC_VAL[12]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel14(void)
{
	          CH_Select14();
	          HAL_ADC_Start(&hadc3);
		 	  HAL_ADC_PollForConversion(&hadc3,10);
		 	  ADC_VAL[13]=HAL_ADC_GetValue(&hadc3);
		 	  HAL_ADC_Stop(&hadc3);
		 	  Voltage=(float)(ADC_VAL[13]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel15(void)
{
	          CH_Select15();
	          HAL_ADC_Start(&hadc3);
		 	  HAL_ADC_PollForConversion(&hadc3,10);
		 	  ADC_VAL[14]=HAL_ADC_GetValue(&hadc3);
		 	  HAL_ADC_Stop(&hadc3);
		 	  Voltage=(float)(ADC_VAL[14]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel16(void)
{
	          CH_Select16();
	          HAL_ADC_Start(&hadc3);
		 	  HAL_ADC_PollForConversion(&hadc3,1000);
		 	  ADC_VAL[15]=HAL_ADC_GetValue(&hadc3);
		 	  HAL_ADC_Stop(&hadc3);
		 	  Voltage=(float)(ADC_VAL[15]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel17(void)
{
	          CH_Select17();
	          HAL_ADC_Start(&hadc3);
		 	  HAL_ADC_PollForConversion(&hadc3,10);
		 	  ADC_VAL[16]=HAL_ADC_GetValue(&hadc3);
		 	  HAL_ADC_Stop(&hadc3);
		 	  Voltage=(float)(ADC_VAL[16]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel18(void)
{
	          CH_Select18();
	          HAL_ADC_Start(&hadc3);
		 	  HAL_ADC_PollForConversion(&hadc3,10);
		 	  ADC_VAL[17]=HAL_ADC_GetValue(&hadc3);
		 	  HAL_ADC_Stop(&hadc3);
		 	  Voltage=(float)(ADC_VAL[17]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel19(void)
{
	          CH_Select19();
	          HAL_ADC_Start(&hadc3);
		 	  HAL_ADC_PollForConversion(&hadc3,10);
		 	  ADC_VAL[18]=HAL_ADC_GetValue(&hadc3);
		 	  HAL_ADC_Stop(&hadc3);
		 	  Voltage=(float)(ADC_VAL[18]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel20(void)
{
	          CH_Select20();
	          HAL_ADC_Start(&hadc3);
		 	  HAL_ADC_PollForConversion(&hadc3,10);
		 	  ADC_VAL[19]=HAL_ADC_GetValue(&hadc3);
		 	  HAL_ADC_Stop(&hadc3);
		 	  Voltage=(float)(ADC_VAL[19]*3.3)/4095;
		 	  HAL_Delay(50);
}
void channel21(void)
{
	          CH_Select21();
	          HAL_ADC_Start(&hadc3);
		 	  HAL_ADC_PollForConversion(&hadc3,10);
		 	  ADC_VAL[20]=HAL_ADC_GetValue(&hadc3);
		 	  HAL_ADC_Stop(&hadc3);
		 	  Voltage=(float)(ADC_VAL[20]*3.3)/4095;
		 	  HAL_Delay(50);
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	    channel1();
	  	channel2();
	  	channel3();
	  	channel4();
	  	channel5();
	  	channel6();
	  	channel7();
	  	channel8();
	  	channel9();
	  	channel10();
	  	channel11();
	  	channel12();
	  	channel13();
	  	channel14();
	  	channel15();
	  	channel16();
	  	channel17();
	  	channel18();
	  	channel19();
	  	channel20();
	  	channel21();




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
  RCC_OscInitStruct.PLL.PLLN = 167;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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

//  ADC_ChannelConfTypeDef sConfig = {0};

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
  hadc1.Init.NbrOfConversion = 13;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
}
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_10;
//  sConfig.Rank = 1;
//  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_11;
//  sConfig.Rank = 2;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_12;
//  sConfig.Rank = 3;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_13;
//  sConfig.Rank = 4;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_1;
//  sConfig.Rank = 5;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_2;
//  sConfig.Rank = 6;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_3;
//  sConfig.Rank = 7;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_4;
//  sConfig.Rank = 8;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_5;
//  sConfig.Rank = 9;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_6;
//  sConfig.Rank = 10;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_7;
//  sConfig.Rank = 11;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_14;
//  sConfig.Rank = 12;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_15;
//  sConfig.Rank = 13;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN ADC1_Init 2 */
//
//  /* USER CODE END ADC1_Init 2 */
//
//}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
 void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

//  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ENABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 8;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
}
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_9;
//  sConfig.Rank = 1;
//  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_14;
//  sConfig.Rank = 2;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_15;
//  sConfig.Rank = 3;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_4;
//  sConfig.Rank = 4;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_5;
//  sConfig.Rank = 5;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_6;
//  sConfig.Rank = 6;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_7;
//  sConfig.Rank = 7;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_8;
//  sConfig.Rank = 8;
//  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN ADC3_Init 2 */
//
//  /* USER CODE END ADC3_Init 2 */
//
//}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
 void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
}
  /* USER CODE END Error_Handler_Debug */


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
