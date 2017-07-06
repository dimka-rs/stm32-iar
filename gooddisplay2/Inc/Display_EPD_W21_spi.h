#ifndef _MCU_SPI_H_
#define _MCU_SPI_H_

#define EPD_W21_SPI_SPEED 0x02

//#define EPD_W21_VPP_0	P4 &= ~0x80
//#define EPD_W21_VPP_1	P4 |= 0x80

/* PB5 */
#define EPD_W21_MOSI_0	GPIOB->BRR = GPIO_PIN_5;
#define EPD_W21_MOSI_1	GPIOB->BSRR = GPIO_PIN_5;

/* PB3 */
#define EPD_W21_CLK_0	GPIOB->BRR = GPIO_PIN_3
#define EPD_W21_CLK_1	GPIOB->BSRR = GPIO_PIN_3

/* PA15 */
#define EPD_W21_CS_0	GPIOA->BRR = GPIO_PIN_15
#define EPD_W21_CS_1	GPIOA->BSRR = GPIO_PIN_15

/* PB 11 */
#define EPD_W21_DC_0	GPIOB->BRR = GPIO_PIN_11
#define EPD_W21_DC_1	GPIOB->BSRR = GPIO_PIN_11

/* PB2 */
#define EPD_W21_RST_0	GPIOB->BRR = GPIO_PIN_2
#define EPD_W21_RST_1	GPIOB->BSRR = GPIO_PIN_2

#define EPD_W21_BS_0	GPIOB->BRR = GPIO_PIN_10; //PWR
//#define EPD_W21_BS_1	P2 |= 0x01

/* PA8 */
#define isEPD_W21_BUSY HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) // for solomen solutions


extern void driver_delay_us(unsigned int xus);
extern void driver_delay_xms(unsigned long xms);

void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
void EPD_W21_WriteCMD_p1(unsigned char command,unsigned char para);
void EPD_W21_WriteCMD_p2(unsigned char command,unsigned char para1,unsigned char para2);
void EPD_W21_Write(unsigned char *value, unsigned char datalen);
void EPD_W21_WriteDispRam(unsigned char XSize,unsigned int YSize,unsigned char *Dispbuff);
void EPD_W21_WriteDispRamMono(unsigned char XSize,unsigned int YSize,unsigned char dispdata);
void EPD_W21_WriteDispRamVGray4(unsigned char XSize,unsigned int YSize);
void EPD_W21_WriteDispRamHGray4(unsigned char XSize,unsigned int YSize);
void EPD_W21_WriteDispRamChessboardMono(unsigned char XSize,unsigned int YSize,unsigned char Mode);
void EPD_W21_WriteDispRamVline(unsigned char XSize,unsigned int YSize);
void EPD_W21_WriteDispRamHline(unsigned char XSize,unsigned int YSize);
void EPD_W21_WriteDispRamDotArray(unsigned char XSize,unsigned int YSize);

#endif  //#ifndef _MCU_SPI_H_

/***********************************************************
						end file
***********************************************************/
