#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"
#include "stm32l0xx_hal.h"

void EPD_W21_Init(void)
{
	EPD_W21_BS_0;		// 4 wire spi mode selected
	EPD_W21_RST_0;		// Module reset
	driver_delay_xms(10000);
	EPD_W21_RST_1;
	driver_delay_xms(10000);
}	

//unsigned int IC_SWITCH;
//unsigned char vcom;
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


void EpdDisplay(){	
	EPD_W21_Init();
	//driver_delay_xms(80000);	  //wait for fresh reset
	EPD_W21_WriteCMD(0x01); 
	EPD_W21_WriteDATA(0x07);	    //??????
        EPD_W21_WriteDATA(0x00);
	EPD_W21_WriteDATA(0x08);
	EPD_W21_WriteDATA(0x00);
        EPD_W21_WriteCMD(0x06);         //boost??
        EPD_W21_WriteDATA(0x07);
        EPD_W21_WriteDATA(0x07);
        EPD_W21_WriteDATA(0x07);
        EPD_W21_WriteCMD(0x04);         //?? 
        lcd_chkstatus();                //??????
        driver_delay_xms(300000);  
        EPD_W21_WriteCMD(0X00);
	EPD_W21_WriteDATA(0xcf);		//???????
	EPD_W21_WriteCMD(0X50);
	EPD_W21_WriteDATA(0x37);
        EPD_W21_WriteCMD(0x30);			//PLL??
        EPD_W21_WriteDATA(0x39);		      
        EPD_W21_WriteCMD(0x61);			//????
        EPD_W21_WriteDATA(0xC8);		//200??	 
        EPD_W21_WriteDATA(0x00);		//200?? 
        EPD_W21_WriteDATA(0xC8);
        EPD_W21_WriteCMD(0x82);			//vcom??
        EPD_W21_WriteDATA(0x0E);				   
        lut_bw();
	lut_red();
	pic_display();
        EPD_W21_WriteCMD(0x12);              
        lcd_chkstatus();
	driver_delay_xms(300000);	  //wait for fresh display
	EPD_W21_WriteCMD(0X50);
	EPD_W21_WriteDATA(0x17);		//BD floating
	EPD_W21_WriteCMD(0x82); 		//to solve Vcom drop    
        EPD_W21_WriteDATA(0x00);		
	EPD_W21_WriteCMD(0x01);			//power setting      
        EPD_W21_WriteDATA(0x02);		//gate switch to external
        EPD_W21_WriteDATA(0x00);
        EPD_W21_WriteDATA(0x00); 
        EPD_W21_WriteDATA(0x00); 
	driver_delay_xms(1500);			//delay 1.5S
	EPD_W21_WriteCMD(0X02);			//power off
	driver_delay_xms(40000);
}

void pic_display(void)
{
	EPD_W21_WriteCMD(0x10);
	Ultrachip(); 
	EPD_W21_WriteCMD(0x13);
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
	EPD_W21_WriteCMD(0x20);
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_vcom0[count]);}
	
	EPD_W21_WriteCMD(0x21);
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_w[count]);}   
	
	EPD_W21_WriteCMD(0x22);
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_b[count]);}    
	
	EPD_W21_WriteCMD(0x23);
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_g1[count]);}    
	
	EPD_W21_WriteCMD(0x24);
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_g2[count]);}          
}

void lut_red(void)
{
	unsigned int count;
	EPD_W21_WriteCMD(0x25);
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_vcom1[count]);}
	
	EPD_W21_WriteCMD(0x26);
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_red0[count]); }  
	
	EPD_W21_WriteCMD(0x27);
	for(count=0;count<15;count++)	     
		{EPD_W21_WriteDATA(lut_red1[count]); }   
}

void lcd_chkstatus(void)
{
	unsigned char busy;
	while(1)
  	{	 
     if(isEPD_W21_BUSY==0) break;
  	}       
   driver_delay_xms(2000);                       
}
