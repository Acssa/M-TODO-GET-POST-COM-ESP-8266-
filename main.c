/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

//#define  link "GET /.well-known/smart-configuration HTTP/1.1\r\nHost:http://cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\r\nAccept:application/fhir+json\r\nContent-Encoding:gzip/ deflate\r\nContent-Type: application/json\r\nConection: close\r\n\r\n"

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART6_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t Rx_data[2000];
uint8_t Rx_data2[200];

void bufclear(uint8_t *buf){

 uint16_t len =strlen (buf);
 for(int i=0; i<len; i++){
	 Rx_data[i] = '\0';


 }

}

uint8_t  request0[]= "GET /.well-known/smart-configuration HTTP/1.1\r\nHost:http://cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\r\nAccept:application/fhir+json\r\nContent-Encoding:gzip/ deflate\r\nContent-Type: application/json\r\nConection: close\r\n\r\n";
uint8_t  request1[]= "GET /auth/register HTTP/1.1\r\nHost:http://cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\r\nContent-Type: application/json\r\n\r\n";
uint8_t  request2[]= "GET /auth/login HTTP/1.1\r\nHost:http://cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\r\nContent-Type: application/json\r\n\r\n";
uint8_t newtoken[500];

uint8_t data[1000];
uint8_t data2[1000];
uint8_t data3[1000];
uint8_t data4[1000];
uint8_t data5[1000];
/* USER CODE END 0 */


/**
  * @brief  The application entry point.
  * @retval int
  */

void rodaComandoAT(uint8_t* comandoAT, uint32_t delay){
	uint8_t *local;

	int local_size=0, size=0;
	size = sizeof(comandoAT);
	local = comandoAT;
	while(*comandoAT++)
		local_size++;
//	huart6 eh porta do esp
//	huart2 eh a serial pra poder debugar/ler o que ta acontecendo
	  HAL_UART_Transmit(&huart6, local, local_size, HAL_MAX_DELAY);
	  HAL_UART_Receive(&huart6, Rx_data, 2000, delay);
	  HAL_UART_Transmit(&huart2, Rx_data, strlen(Rx_data), HAL_MAX_DELAY);

	  if(delay==12500){
	  //strcpy (newtoken, Rx_data);
	  uint16_t lentoken=strlen(Rx_data);
	  uint16_t j=0;
	  for(int i=0; i<lentoken; i++){
        if(Rx_data[i]==':'&& Rx_data[i+1]=='"'){

        	while(Rx_data[i+2]!='"'){
        	newtoken[j]=Rx_data[i+2];
        	i++;
        	j++;
        	}
        	i=lentoken;
        	newtoken[j]='\0';
        }

	  }
	  HAL_UART_Transmit(&huart2, newtoken, strlen(newtoken), HAL_MAX_DELAY);
	  }

	  bufclear(Rx_data);
}


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
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */

	  rodaComandoAT("AT\r\n", 6000);
//testa comunicação
      rodaComandoAT("AT+RST\r\n", 6000);
//habilita modo estação
  	  rodaComandoAT("AT+CWMODE=1\r\n", 6000);
//verifica as redes disponiveis
  	  rodaComandoAT("AT+CWLAP\r\n", 6000);
//conecta em uma rede
  	  rodaComandoAT("AT+CWJAP=\"Acssa\",\"acssa2022\"\r\n", 10000);
//modo conec. unica
   	 rodaComandoAT("AT+CIPMUX=0\r\n", 10000);
//modo de tranmicao: 0 = modo normal, 1 = modo de transmicao transparente
   	 rodaComandoAT("AT+CIPMODE=0\r\n", 6000);
//endereco IP e MAC do modulo
   	 rodaComandoAT("AT+CIFSR\r\n", 6000);
//transforma url em endereco IP
   //	rodaComandoAT("AT+CIPDOMAIN=\"hapi.fhir.org\"\r\n", 12000);

////CONEXAO COM O IP DO SERV
//   	rodaComandoAT("AT+CIPSTART=\"TCP\",\"cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\",80\r\n", 10000);
//    HAL_Delay(2000);
//
////TESTE GET well-know
//    int len = strlen(request0);
//
////Envia o tamanho da string do get
//  	sprintf(data, "AT+CIPSEND=%d\r\n", len);
//  	rodaComandoAT(data, 6000);
//  	HAL_UART_Transmit(&huart2, request0, strlen(request0), HAL_MAX_DELAY);
//  	rodaComandoAT(request0, 6000);
//
////CONEXAO COM O IP DO SERV
//  	rodaComandoAT("AT+CIPSTART=\"TCP\",\"cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\",80\r\n", 10000);
//  	HAL_Delay(2000);
//
////TESTE GET auth-register
//    int len2= strlen(request1);
//  	sprintf(data2, "AT+CIPSEND=%d\r\n", len2);
//  	rodaComandoAT(data2, 12000);
// 	HAL_UART_Transmit(&huart2, request1, strlen(request1), HAL_MAX_DELAY);
//  	rodaComandoAT(request1, 12000);
//
////CONEXAO COM O IP DO SERV
//  	rodaComandoAT("AT+CIPSTART=\"TCP\",\"cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\",80\r\n", 10000);
//  	HAL_Delay(2000);
//
//// TESTE GET auth-login
//    int len3= strlen(request2);
//  	sprintf(data3, "AT+CIPSEND=%d\r\n", len3);
//  	rodaComandoAT(data3, 12000);
// 	HAL_UART_Transmit(&huart2, request2, strlen(request2), HAL_MAX_DELAY);
//  	rodaComandoAT(request2, 12000);

//CONEXAO COM O IP DO SERV
  	rodaComandoAT("AT+CIPSTART=\"TCP\",\"cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\",80\r\n", 10000);
  	HAL_Delay(2000);

// TESTE POST auth-token
   uint8_t json[]= "{\n  \"client_id\": \"device-1\",\n  \"code\": \"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjbGllbnRfaWQiOiJkZXZpY2UtMSIsImNsaWVudF9zZWNyZXQiOiJkZXZpY2UtNTEzNjk0MiIsInNjb3BlIjoiYWxsLyouY3J1ZHMiLCJncmFudF90eXBlIjoiY2xpZW50X2NyZWRlbnRpYWxzIn0.-FOFWE5f5tfFelGfGBQxCsHjhqFpaNMkmrwdGxFFVbw\"\n}";
   int tamanho= strlen(json);
   uint8_t request3[1000];
   sprintf(request3, "POST /auth/token HTTP/1.1\r\nHost: http://cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\r\nConnection: close \r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", tamanho, json);
  	  //uint8_t  request3[]= "POST /auth/login HTTP/1.1\r\nHost:http://cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\r\nConnection: close \r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s";

   int len4= strlen(request3);
   sprintf(data4, "AT+CIPSEND=%d\r\n", len4);
   rodaComandoAT(data4, 12000);
   HAL_UART_Transmit(&huart2, request3, strlen(request3), HAL_MAX_DELAY);
   rodaComandoAT(request3, 12500);

//CONEXAO COM O IP DO SERV
   rodaComandoAT("AT+CIPSTART=\"TCP\",\"cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\",80\r\n", 10000);
   HAL_Delay(2000);

// TESTE POST access_token
   uint8_t json2[]= "{\n  \"id\": 1,\n  \"resourceType\": \"Patient\"\n}";
   int tamanho2= strlen(json2);
   uint8_t request4[1000];
   sprintf(request4, "POST  /Patient  HTTP/1.1\r\nHost: http://cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com\r\nConnection: close\r\nAuthorization: Bearer %s\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s",newtoken, tamanho2, json2);

   int len5= strlen(request4);
   sprintf(data5, "AT+CIPSEND=%d\r\n", len5);
   rodaComandoAT(data5, 12000);
   HAL_UART_Transmit(&huart2, request4, strlen(request4), HAL_MAX_DELAY);
   rodaComandoAT(request4, 12000);

//CONEXAO COM O IP DO SERV
//   rodaComandoAT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n", 10000);
//  HAL_Delay(2000);
//
//    //TESTE POST Thingspeak
//      uint8_t json[]= "{\n  \"headers\":\"false\",\n  \"api_key\": \"WBL8G0DSE46DZJ6S\",\n  \"field1\": 10\n}";
//      int tamanho= strlen(json);
//      uint8_t postts[1000];
//      sprintf(postts, "POST /update.json HTTP/1.1\r\nHost: api.thingspeak.com\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", tamanho, json);
//      int len4= strlen(postts);
//      sprintf(data4, "AT+CIPSEND=%d\r\n", len4);
//      rodaComandoAT(data4, 12000);
//      HAL_UART_Transmit(&huart2, postts, strlen(postts), HAL_MAX_DELAY);
//      rodaComandoAT(postts, 12000);






//FECHA O CANAL DE COMUNICAÇÃO
 //	 rodaComandoAT("AT+CIPCLOSE=0\r\n", 6000);

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

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

