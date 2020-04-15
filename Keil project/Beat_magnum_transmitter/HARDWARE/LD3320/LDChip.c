#include    <stm32f10x.h>
#include "stm32f10x_conf.h"
#include "LDchip.h"
#include "Reg_RW.h"
#include "USER_HARDWARE_CONFIG.h"


u8 nLD_Mode = LD_MODE_IDLE;		
u8 ucRegVal;
extern u8  nAsrStatus;


/***********************************************************
* 名    称：void LD_reset(void)
* 功    能：LD芯片硬件初始化 
**********************************************************/ 
void LD_reset(void)
{
	LD_RST_H();
	LD3320_delay(100);
	LD_RST_L();
	LD3320_delay(100);
	LD_RST_H();
	LD3320_delay(100);
	LD_CS_L();
	LD3320_delay(100);
	LD_CS_H();		
	LD3320_delay(100);
}

/***********************************************************
* 名    称： void LD_Init_Common(void)
* 功    能： 初始化命令
**********************************************************/ 
void LD_Init_Common(void)
{

	LD_ReadReg(0x06);  
	LD_WriteReg(0x17, 0x35); 
	LD3320_delay(5);
	LD_ReadReg(0x06);  

	LD_WriteReg(0x89, 0x03);  
	LD3320_delay(5);
	LD_WriteReg(0xCF, 0x43);   
	LD3320_delay(5);
	LD_WriteReg(0xCB, 0x02);
	
	/*PLL setting*/
	LD_WriteReg(0x11, LD_PLL_11);       
	if (nLD_Mode == LD_MODE_MP3)
	{
		LD_WriteReg(0x1E, 0x00); 
		LD_WriteReg(0x19, LD_PLL_MP3_19);   
		LD_WriteReg(0x1B, LD_PLL_MP3_1B);   
		LD_WriteReg(0x1D, LD_PLL_MP3_1D);
	}
	else
	{
		LD_WriteReg(0x1E,0x00);
		LD_WriteReg(0x19, LD_PLL_ASR_19); 
		LD_WriteReg(0x1B, LD_PLL_ASR_1B);		
	    LD_WriteReg(0x1D, LD_PLL_ASR_1D);
	}
	LD3320_delay(5);
	
	LD_WriteReg(0xCD, 0x04);
	LD_WriteReg(0x17, 0x4c); 
	LD3320_delay(1);
	LD_WriteReg(0xB9, 0x00);
	LD_WriteReg(0xCF, 0x4F); 
	LD_WriteReg(0x6F, 0xFF); 
}

/***********************************************************
* 名    称：void LD_Init_ASR(void)
* 功    能：初始化ASR
**********************************************************/ 	
void LD_Init_ASR(void)
{
	nLD_Mode=LD_MODE_ASR_RUN;
	LD_Init_Common();

	LD_WriteReg(0xBD, 0x00);
	LD_WriteReg(0x17, 0x48);	
	LD3320_delay( 5 );
	LD_WriteReg(0x3C, 0x80);    
	LD_WriteReg(0x3E, 0x07);
	LD_WriteReg(0x38, 0xff);    
	LD_WriteReg(0x3A, 0x07);
	LD_WriteReg(0x40, 0);          
	LD_WriteReg(0x42, 8);
	LD_WriteReg(0x44, 0);    
	LD_WriteReg(0x46, 8); 
	LD3320_delay( 1 );
}

/***********************************************************
* 名    称：void ProcessInt0(void)
* 功    能：识别处理中断函数 
**********************************************************/ 
void ProcessInt0(void)
{
	u8 nAsrResCount=0;

	ucRegVal = LD_ReadReg(0x2B);

			LD_WriteReg(0x29,0) ;
			LD_WriteReg(0x02,0) ;
	
			if((ucRegVal & 0x10) && LD_ReadReg(0xb2)==0x21 && LD_ReadReg(0xbf)==0x35)		
				{	 
						nAsrResCount = LD_ReadReg(0xba);
			
						if(nAsrResCount>0 && nAsrResCount<=4) 
						{
							nAsrStatus=LD_ASR_FOUNDOK; 				
						}
						else
					    {
							nAsrStatus=LD_ASR_FOUNDZERO;
							}	
				}
			else
			 {
					nAsrStatus=LD_ASR_FOUNDZERO;	//执行没有识别
				}

		  LD_WriteReg(0x2b, 0);
		  LD_WriteReg(0x1C,0);
		
			LD_WriteReg(0x29,0);
			LD_WriteReg(0x02,0);
			LD_WriteReg(0x2B,0);
			LD_WriteReg(0xBA,0);	
			LD_WriteReg(0xBC,0);	
			LD_WriteReg(0x08,1);	
			LD_WriteReg(0x08,0);	

}

/***********************************************************
* 名    称：uint8 LD_Check_ASRBusyFlag_b2(void)
* 功    能：检测 ASR 是否忙状态
* 入口参数：flag ---1：空闲状态  
**********************************************************/ 
u8 LD_Check_ASRBusyFlag_b2(void)
{
	u8 j;
	u8 flag = 0;
	for (j=0; j<10; j++)
	{
		if (LD_ReadReg(0xb2) == 0x21)
		{
			flag = 1;
			break;
		}
		LD3320_delay(20);		
	}
	return flag;
}
/***********************************************************
* 名    称： void LD_AsrStart(void)
* 功    能：
* 入口参数：  ASR初始化 
**********************************************************/ 
void LD_AsrStart(void)
{
	LD_Init_ASR();
}
/***********************************************************
* 名    称： uint8 LD_AsrRun(void)
* 功    能： ASR执行函数 
**********************************************************/ 
u8 LD_AsrRun(void)
{
	LD_WriteReg(0x35, MIC_VOL);
	LD_WriteReg(0xB5, Vad_Silence_End);
	LD_WriteReg(0xB6, Vad_Length);
	LD_WriteReg(0x1C, 0x09);
	LD_WriteReg(0xBD, 0x20);
	LD_WriteReg(0x08, 0x01);
	LD3320_delay( 5 );
	LD_WriteReg(0x08, 0x00);
	LD3320_delay( 5);

	if(LD_Check_ASRBusyFlag_b2() == 0)
	{
		return 0;
	}

	LD_WriteReg(0xB2, 0xff);	
	LD_WriteReg(0x37, 0x06);
	LD_WriteReg(0x37, 0x06);
	LD3320_delay( 5);
	LD_WriteReg(0x1C, 0x0b);
	LD_WriteReg(0x29, 0x10);
	
	LD_WriteReg(0xBD, 0x00);   
	return 1;
}

/***********************************************************
* 名    称：uint8 LD_AsrAddFixed(void)
* 功    能：添加识别关键词语
**********************************************************/ 
u8 LD_AsrAddFixed(void)
{
	u8 k, flag;
	u8 nAsrAddLength;

	flag = 1;
	for (k=0; k<DATE_A; k++)
	{			
		if(LD_Check_ASRBusyFlag_b2() == 0)
		{
			flag = 0;
			break;
		}
		
		LD_WriteReg(0xc1, pCode[k] );
		LD_WriteReg(0xc3, 0 );
		LD_WriteReg(0x08, 0x04);
		LD3320_delay(1);
		LD_WriteReg(0x08, 0x00);
		LD3320_delay(1);

		for (nAsrAddLength=0; nAsrAddLength<DATE_B; nAsrAddLength++)
		{
			if (sRecog[k][nAsrAddLength] == 0)
				break;
			LD_WriteReg(0x5, sRecog[k][nAsrAddLength]);
		}
		LD_WriteReg(0xb9, nAsrAddLength);
		LD_WriteReg(0xb2, 0xff);
		LD_WriteReg(0x37, 0x04);
	}	 

    return flag;
}

/***********************************************************
* 名    称： uint8 LD_GetResult(void)
* 功    能： 获取识别结果
**********************************************************/ 
u8 LD_GetResult(void)
{
	return LD_ReadReg(0xc5 );
}



