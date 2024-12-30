
#include "main.h"
#include "usb_host.h"
#define ARM_MATH_CM4		// Define Coretex M4 architecture
#include "arm_math.h"		// Include advanced math header


I2C_HandleTypeDef hi2c1;

I2S_HandleTypeDef hi2s2;
DMA_HandleTypeDef hdma_i2s2_ext_rx;
DMA_HandleTypeDef hdma_spi2_tx;

SPI_HandleTypeDef hspi1;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2S2_Init(void);
void MX_USB_HOST_Process(void);


#define FILTER_LENGTH 101			// Filter length
#define FRAME_LENGTH_FLOAT 512		// Processing frame length
#define FRAME_LENGTH_U16 2048		// integer frame length ( one data = 2 integers * 2 ) left & right

static float LPF_coeffs[FILTER_LENGTH] = {		// LPF coefficients
		   0.000509052345141,
		   0.000371467877138,
		  -0.000000000000000,
		  -0.000421930966378,
		  -0.000653272863360,
		  -0.000512505037478,
		   0.000000000000000,
		   0.000647601620055,
		   0.001037034522740,
		   0.000831895989141,
		  -0.000000000000000,
		  -0.001070425301757,
		  -0.001713651304070,
		  -0.001368728488021,
		   0.000000000000000,
		   0.001733043896939,
		   0.002746633796917,
		   0.002170588290959,
		  -0.000000000000000,
		  -0.002689952801760,
		  -0.004219324720115,
		  -0.003301670957015,
		   0.000000000000000,
		   0.004019046406006,
		   0.006254446687866,
		   0.004859383930577,
		  -0.000000000000000,
		  -0.005845867111595,
		  -0.009055859070559,
		  -0.007010511370258,
		   0.000000000000000,
		   0.008398982088119,
		   0.013006613956334,
		   0.010078810760424,
		  -0.000000000000000,
		  -0.012154177342397,
		  -0.018935270880269,
		  -0.014794326344006,
		   0.000000000000000,
		   0.018292964523664,
		   0.029020686598050,
		   0.023206828997117,
		  -0.000000000000000,
		  -0.030731760980923,
		  -0.051313387567824,
		  -0.043981293968470,
		   0.000000000000000,
		   0.074379480369694,
		   0.158501841074448,
		   0.224767270549089,
		   0.249880485591675,
		   0.224767270549089,
		   0.158501841074448,
		   0.074379480369694,
		   0.000000000000000,
		  -0.043981293968470,
		  -0.051313387567824,
		  -0.030731760980923,
		  -0.000000000000000,
		   0.023206828997117,
		   0.029020686598050,
		   0.018292964523664,
		   0.000000000000000,
		  -0.014794326344006,
		  -0.018935270880269,
		  -0.012154177342397,
		  -0.000000000000000,
		   0.010078810760424,
		   0.013006613956334,
		   0.008398982088119,
		   0.000000000000000,
		  -0.007010511370258,
		  -0.009055859070559,
		  -0.005845867111595,
		  -0.000000000000000,
		   0.004859383930577,
		   0.006254446687866,
		   0.004019046406006,
		   0.000000000000000,
		  -0.003301670957015,
		  -0.004219324720115,
		  -0.002689952801760,
		  -0.000000000000000,
		   0.002170588290959,
		   0.002746633796917,
		   0.001733043896939,
		   0.000000000000000,
		  -0.001368728488021,
		  -0.001713651304070,
		  -0.001070425301757,
		  -0.000000000000000,
		   0.000831895989141,
		   0.001037034522740,
		   0.000647601620055,
		   0.000000000000000,
		  -0.000512505037478,
		  -0.000653272863360,
		  -0.000421930966378,
		  -0.000000000000000,
		   0.000371467877138,
		   0.000509052345141
};

static float HPF_coeffs[FILTER_LENGTH] = {		// HPF coefficients
		   0.000509052345141,
		  -0.000371467877138,
		  -0.000000000000000,
		   0.000421930966378,
		  -0.000653272863360,
		   0.000512505037478,
		  -0.000000000000000,
		  -0.000647601620055,
		   0.001037034522740,
		  -0.000831895989141,
		   0.000000000000000,
		   0.001070425301757,
		  -0.001713651304070,
		   0.001368728488021,
		  -0.000000000000000,
		  -0.001733043896939,
		   0.002746633796917,
		  -0.002170588290959,
		  -0.000000000000000,
		   0.002689952801760,
		  -0.004219324720115,
		   0.003301670957015,
		  -0.000000000000000,
		  -0.004019046406006,
		   0.006254446687867,
		  -0.004859383930577,
		  -0.000000000000000,
		   0.005845867111595,
		  -0.009055859070559,
		   0.007010511370258,
		  -0.000000000000000,
		  -0.008398982088119,
		   0.013006613956334,
		  -0.010078810760424,
		  -0.000000000000000,
		   0.012154177342397,
		  -0.018935270880269,
		   0.014794326344006,
		  -0.000000000000000,
		  -0.018292964523664,
		   0.029020686598050,
		  -0.023206828997117,
		  -0.000000000000000,
		   0.030731760980923,
		  -0.051313387567825,
		   0.043981293968471,
		  -0.000000000000000,
		  -0.074379480369694,
		   0.158501841074448,
		  -0.224767270549090,
		   0.249880485591676,
		  -0.224767270549090,
		   0.158501841074448,
		  -0.074379480369694,
		  -0.000000000000000,
		   0.043981293968471,
		  -0.051313387567825,
		   0.030731760980923,
		  -0.000000000000000,
		  -0.023206828997117,
		   0.029020686598050,
		  -0.018292964523664,
		  -0.000000000000000,
		   0.014794326344006,
		  -0.018935270880269,
		   0.012154177342397,
		  -0.000000000000000,
		  -0.010078810760424,
		   0.013006613956334,
		  -0.008398982088119,
		  -0.000000000000000,
		   0.007010511370258,
		  -0.009055859070559,
		   0.005845867111595,
		  -0.000000000000000,
		  -0.004859383930577,
		   0.006254446687867,
		  -0.004019046406006,
		  -0.000000000000000,
		   0.003301670957015,
		  -0.004219324720115,
		   0.002689952801760,
		  -0.000000000000000,
		  -0.002170588290959,
		   0.002746633796917,
		  -0.001733043896939,
		  -0.000000000000000,
		   0.001368728488021,
		  -0.001713651304070,
		   0.001070425301757,
		   0.000000000000000,
		  -0.000831895989141,
		   0.001037034522740,
		  -0.000647601620055,
		  -0.000000000000000,
		   0.000512505037478,
		  -0.000653272863360,
		   0.000421930966378,
		  -0.000000000000000,
		  -0.000371467877138,
		   0.000509052345141
};

arm_fir_instance_f32 fir_instance_left, fir_instance_right;			// Filter instance

//FIR state size = processing frame length + filter length - 1
float fir_state_left [FRAME_LENGTH_FLOAT + FILTER_LENGTH - 1];		// Left filter
float fir_state_right [FRAME_LENGTH_FLOAT + FILTER_LENGTH - 1];		// Right filter


uint16_t rxBuf[FRAME_LENGTH_U16*2];					// ADC buffer for left & right (Two buffers for half and full complete callback)
uint16_t txBuf[FRAME_LENGTH_U16*2];					// DAC buffer for left & right (Two buffers for half and full complete callback)
float left_buf_in [FRAME_LENGTH_FLOAT];				// Filter input buffer for left
float right_buf_in [FRAME_LENGTH_FLOAT];				// Filter input buffer for right
float left_buf_out [FRAME_LENGTH_FLOAT];				// Filter output buffer for left
float right_buf_out [FRAME_LENGTH_FLOAT];				// Filter output buffer for right

uint8_t state = 0;			// ADC/DAC state for half or full complete callback


int main(void)
{
	int offset_read_ptr;					// Read pointer offset
	int buf_ptr;

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_HOST_Init();
  MX_I2S2_Init();

	arm_fir_init_f32(&fir_instance_left, FILTER_LENGTH, &LPF_coeffs[0], &fir_state_left[0], FRAME_LENGTH_FLOAT);			// Init. for left FIR filter
	arm_fir_init_f32(&fir_instance_right, FILTER_LENGTH, &HPF_coeffs[0], &fir_state_right[0], FRAME_LENGTH_FLOAT);		// Init. for right FIR filter
	HAL_I2SEx_TransmitReceive_DMA(&hi2s2, txBuf, rxBuf,FRAME_LENGTH_U16);			// DMA setting (CAREFUL in DMA size!!!)



  while (1)
  {

    MX_USB_HOST_Process();
	if (state != 0) {					// If ADC/DAC is not ready, do nothing


		if (state == 1)   {				// In half complete call back
			offset_read_ptr = 0;
		}

		else if (state == 2) {			// In full complete call back
			offset_read_ptr = FRAME_LENGTH_U16;
		}

		buf_ptr = 0;

		//Bring data from ADC buffer to floating buffer (2*16bit integer -> one floating data)
		for (int i=offset_read_ptr; i<offset_read_ptr+FRAME_LENGTH_U16; i=i+4) {
			left_buf_in[buf_ptr] = (float) ((int) (rxBuf[i]<<16)|rxBuf[i+1]);
			right_buf_in[buf_ptr] = (float) ((int) (rxBuf[i+2]<<16)|rxBuf[i+3]);
			buf_ptr++;
		}


		//DO FIR
		arm_fir_f32 (&fir_instance_left, &left_buf_in[0], &left_buf_out[0],FRAME_LENGTH_FLOAT);
		arm_fir_f32 (&fir_instance_right, &right_buf_in[0], &right_buf_out[0],FRAME_LENGTH_FLOAT);

		//modulation
		for (int i = 0 ; i < FRAME_LENGTH_FLOAT ; i++) {
			right_buf_out[i] = pow(-1, i)*right_buf_out[i];
		}
		buf_ptr = 0;

		//Send data to DAC buffer to integer buffer (one floating data -> 2*16bit integer)
		for (int i=offset_read_ptr; i<offset_read_ptr+FRAME_LENGTH_U16; i=i+4) {
			txBuf[i] =  (((int)left_buf_out[buf_ptr])>>16)&0xFFFF;
			txBuf[i+1] = ((int)left_buf_out[buf_ptr])&0xFFFF;
			txBuf[i+2] = (((int)right_buf_out[buf_ptr])>>16)&0xFFFF;
			txBuf[i+3] = ((int)right_buf_out[buf_ptr])&0xFFFF;
			buf_ptr++;
		}

		state = 0;

	}


  }

}
void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef *hi2s){

	state = 1;			// Half complete callback state

}

void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef *hi2s){

	state = 2;			// Full complete callback state

}

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
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2S2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S2_Init(void)
{

  /* USER CODE BEGIN I2S2_Init 0 */

  /* USER CODE END I2S2_Init 0 */

  /* USER CODE BEGIN I2S2_Init 1 */

  /* USER CODE END I2S2_Init 1 */
  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_48K;
  hi2s2.Init.CPOL = I2S_CPOL_LOW;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S2_Init 2 */

  /* USER CODE END I2S2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
  /* DMA1_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2S3_WS_Pin */
  GPIO_InitStruct.Pin = I2S3_WS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(I2S3_WS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : I2S3_MCK_Pin I2S3_SCK_Pin I2S3_SD_Pin */
  GPIO_InitStruct.Pin = I2S3_MCK_Pin|I2S3_SCK_Pin|I2S3_SD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

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
