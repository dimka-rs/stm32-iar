#include "main.h"

/* USER CODE BEGIN Includes */
#include "stm32l0xx_hal.h"
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"	
//#include "stm32f10x_gpio.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void lcd_chkstatus(void);
void lut_red(void);
void lut_bw(void);
void Ultrachip_red(void);
void Ultrachip(void);
void master_uc8154_init(void);
void Ultrachip_red1(void);
void Ultrachip1(void);
void pic_display(void);
unsigned char  EPD_W21_ReadDATA(void);
void driver_delay_us(unsigned int xus)
{
	for(;xus>1;xus--);
}

void driver_delay_xms(unsigned long xms)	
{	
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
	{
        for(i=0; i<256; i++);
    }
}

void pic_display(void)
{
	EPD_W21_WriteCMD(0x10); // DATA START TRANSMISSION 1 (DTM1)     (R10H) 
	Ultrachip();
	EPD_W21_WriteCMD(0x13); // DATA START TRANSMISSION 2 (DTM2)     (R13H) 
	Ultrachip_red();
}

void Ultrachip(void)
{
	unsigned int i;
	for(i=0;i<10000;i++)	     
	{
		EPD_W21_WriteDATA(G_Ultrachip[i]);  
	}  
	driver_delay_xms(2);	              
} 

void Ultrachip_red(void)
{
    unsigned int i;
    for(i=0;i<5000;i++)	     
	{
		EPD_W21_WriteDATA(G_Ultrachip[i]);  //G_Ultrachip_red[i]
	}  
	driver_delay_xms(2);     	     
}


void lut_bw(void)
{
	unsigned int count;
	EPD_W21_WriteCMD(0x20); // VCOM1 LUT (LUTC1)     (R20H) 
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_vcom0[count]);}
	
	EPD_W21_WriteCMD(0x21); // White LUT (LUTW)
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_w[count]);}   
	
	EPD_W21_WriteCMD(0x22); // Black LUT (LUTB) 
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_b[count]);}    
	
	EPD_W21_WriteCMD(0x23); // Gray1 LUT (LUTG1)
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_g1[count]);}    
	
	EPD_W21_WriteCMD(0x24); // Gray2 LUT (LUTG2)
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_g2[count]);}          
}

void lut_red(void)
{
	unsigned int count;
	EPD_W21_WriteCMD(0x25); // Vcom2 LUT (LUTC2) 
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_vcom1[count]);}
	
	EPD_W21_WriteCMD(0x26); // Red0 LUT (LUTR0)
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_red0[count]); }  
	
	EPD_W21_WriteCMD(0x27); // Red1 LUT (LUTR1)
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_red1[count]); }   
}

void lcd_chkstatus(void)
{
  //unsigned char busy;
  while(1)
  {	 
    if(isEPD_W21_BUSY==0) break;
  }       
  driver_delay_xms(2000);                       
}
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
  EPD_W21_Init();
  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
  while (1)
  {
    //driver_delay_xms(80000);	  //wait for fresh reset
    EPD_W21_WriteCMD(0x01); //  Power Setting (PWR)
    EPD_W21_WriteDATA(0x07); 
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0x08);
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteCMD(0x06); //  BOOSTER SOFT START (BTST)
    EPD_W21_WriteDATA(0x07);
    EPD_W21_WriteDATA(0x07);
    EPD_W21_WriteDATA(0x07);
    EPD_W21_WriteCMD(0x04);  // POWER ON (PON)
    lcd_chkstatus();
    driver_delay_xms(300000);  
    EPD_W21_WriteCMD(0X00); // Panel Setting (PSR) 
    EPD_W21_WriteDATA(0xcf); 
    EPD_W21_WriteCMD(0X50); // Vcom and data interval setting (CDI)
    EPD_W21_WriteDATA(0x37);
    EPD_W21_WriteCMD(0x30); // PLL control (PLL)
    EPD_W21_WriteDATA(0x39); 		      
    EPD_W21_WriteCMD(0x61); // Resolution setting (TRES) 
    EPD_W21_WriteDATA(0xC8);		//200??	 
    EPD_W21_WriteDATA(0x00);		//200?? 
    EPD_W21_WriteDATA(0xC8);
    EPD_W21_WriteCMD(0x82); //  VCM_DC Setting (VDCS) 
    EPD_W21_WriteDATA(0x0E);				   
    lut_bw();
    lut_red();
    pic_display();
    EPD_W21_WriteCMD(0x12); // Display Refresh (DRF) 
    lcd_chkstatus();
    driver_delay_xms(300000);	  //wait for fresh display
    EPD_W21_WriteCMD(0X50); // Vcom and data interval setting (CDI)
    EPD_W21_WriteDATA(0x17);		//BD floating
    EPD_W21_WriteCMD(0x82); // VCM_DC Setting (VDCS)  to solve Vcom drop    
    EPD_W21_WriteDATA(0x00);		
    EPD_W21_WriteCMD(0x01); //  Power Setting (PWR)
    EPD_W21_WriteDATA(0x02);		//gate switch to external
    EPD_W21_WriteDATA(0x00);
    EPD_W21_WriteDATA(0x00); 
    EPD_W21_WriteDATA(0x00); 
    driver_delay_xms(1500);			//delay 1.5S
    EPD_W21_WriteCMD(0X02); // Power OFF (POF)
    driver_delay_xms(40000);
    while(1);
  }


}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, EPD_RSTn_Pin|EPD_PWRn_Pin|EPD_DC_Pin|EPD_SCK_Pin 
                          |EPD_MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EPD_CSn_GPIO_Port, EPD_CSn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : LED_RED_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_RED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : EPD_RSTn_Pin EPD_PWRn_Pin EPD_DC_Pin EPD_SCK_Pin 
                           EPD_MOSI_Pin */
  GPIO_InitStruct.Pin = EPD_RSTn_Pin|EPD_PWRn_Pin|EPD_DC_Pin|EPD_SCK_Pin 
                          |EPD_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : EPD_BUSY_Pin */
  GPIO_InitStruct.Pin = EPD_BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(EPD_BUSY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EPD_CSn_Pin */
  GPIO_InitStruct.Pin = EPD_CSn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(EPD_CSn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

}
/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
