/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define LED_RED_Pin GPIO_PIN_5
#define LED_RED_GPIO_Port GPIOA
#define EPD_RSTn_Pin GPIO_PIN_2
#define EPD_RSTn_GPIO_Port GPIOB
#define EPD_PWRn_Pin GPIO_PIN_10
#define EPD_PWRn_GPIO_Port GPIOB
#define EPD_DC_Pin GPIO_PIN_11
#define EPD_DC_GPIO_Port GPIOB
#define EPD_BUSY_Pin GPIO_PIN_8
#define EPD_BUSY_GPIO_Port GPIOA
#define EPD_CSn_Pin GPIO_PIN_15
#define EPD_CSn_GPIO_Port GPIOA
#define EPD_SCK_Pin GPIO_PIN_3
#define EPD_SCK_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_4
#define LED_GREEN_GPIO_Port GPIOB
#define EPD_MOSI_Pin GPIO_PIN_5
#define EPD_MOSI_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
