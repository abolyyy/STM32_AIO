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
#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void displayDigit(int , int );
void displayNumber(int );

const uint8_t segdig[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const uint8_t segdig_index[4]={0x01,0x02,0x04,0x08};

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();

  while (1)
  {
	  displayNumber(2425);

  }

}

///////////////////////////////////////////////////////////////////////////////////////

void displayDigit(int digit, int value)
{

HAL_GPIO_WritePin(GPIOB , 0X0F , GPIO_PIN_SET );
HAL_GPIO_WritePin(GPIOB , segdig_index[digit-1] , GPIO_PIN_RESET );
//-------------------------------------------------------------------------------

HAL_GPIO_WritePin(GPIOA , 0XFF , GPIO_PIN_RESET );
HAL_GPIO_WritePin(GPIOA , segdig[value] , GPIO_PIN_SET );

}

///////////////////////////////////////////////////////////////////////////////////////

void displayNumber(int number)
{
    int digit1 = number / 1000;
    int digit2 = (number / 100) % 10;
    int digit3 = (number / 10) % 10;
    int digit4 = number % 10;

    displayDigit(1, digit1);
    HAL_Delay(1);
    displayDigit(2, digit2);
    HAL_Delay(1);
    displayDigit(3, digit3);
    HAL_Delay(1);
    displayDigit(4, digit4);
    HAL_Delay(1);
}
///////////////////////////////////////////////////////////////////////////////////////


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, sseg_a_Pin|sseg_b_Pin|sseg_c_Pin|sseg_d_Pin
                          |sseg_e_Pin|sseg_f_Pin|sseg_g_Pin|sseg_point_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, sseg_dig_1_Pin|sseg_dig_2_Pin|sseg_dig_3_Pin|sseg_dig_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : sseg_a_Pin sseg_b_Pin sseg_c_Pin sseg_d_Pin
                           sseg_e_Pin sseg_f_Pin sseg_g_Pin sseg_point_Pin */
  GPIO_InitStruct.Pin = sseg_a_Pin|sseg_b_Pin|sseg_c_Pin|sseg_d_Pin
                          |sseg_e_Pin|sseg_f_Pin|sseg_g_Pin|sseg_point_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : sseg_dig_1_Pin sseg_dig_2_Pin sseg_dig_3_Pin sseg_dig_4_Pin */
  GPIO_InitStruct.Pin = sseg_dig_1_Pin|sseg_dig_2_Pin|sseg_dig_3_Pin|sseg_dig_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

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
