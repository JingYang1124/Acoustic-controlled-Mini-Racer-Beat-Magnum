
#include  <stm32f10x.h>
#include "stm32f10x_conf.h"
#include "sys.h"
#include "LDchip.h"
#include "Reg_RW.h"
#include "USER_HARDWARE_CONFIG.h"

#define LD3320_NOP LD3320_delay(1)

/***********************************************************
* 名    称：void LD_WriteReg(uint8 data1,uint8 data2)
* 功    能： 写ld3320寄存器
**********************************************************/ 
void LD_WriteReg( unsigned char address, unsigned char data)
{
	u8 i = 0;
	u8 command = 0x04;
	
	LD_CS_L();

	LD_SPIS_L();

	LD3320_NOP;
	
	for (i=0;i < 8; i++)
	{
		if ((command & 0x80) == 0x80)
			LD_MOSI_H();
		else
			LD_MOSI_L();
			LD3320_NOP;
			LD_SCK_L();
			command = (command << 1);
			LD3320_NOP;
			LD_SCK_H();
	}
	
	for (i=0;i < 8; i++)
	{
		if ((address & 0x80) == 0x80)
			LD_MOSI_H();
		else
			LD_MOSI_L();
			LD3320_NOP;
			LD_SCK_L();
			address = (address << 1);
			LD3320_NOP;
			LD_SCK_H();
	}
	
	for (i=0;i < 8; i++)
	{
		if ((data & 0x80) == 0x80)
			LD_MOSI_H();
		else
			LD_MOSI_L();
			LD3320_NOP;
			LD_SCK_L();
			data = (data << 1);
			LD3320_NOP;
			LD_SCK_H();
	}
	LD3320_NOP;
	LD_CS_H();
}
/***********************************************************
* 名    称：uint8 LD_ReadReg(uint8 reg_add)
* 功    能：读ld3320寄存器
**********************************************************/ 
u8 LD_ReadReg(u8 address )
{
	u8 i = 0;
	u8 temp = 0;
	u8 data = 0;
	u8 command = 0x05;
	
	LD_CS_L();
	LD_SPIS_L();

	LD3320_NOP;
	
	for (i=0;i < 8; i++)
	{
		if ((command & 0x80) == 0x80)
			LD_MOSI_H();
		else
			LD_MOSI_L();
			LD3320_NOP;
			LD_SCK_L();
			command = (command << 1);
			LD3320_NOP;
			LD_SCK_H();
	}

	for (i=0;i < 8; i++)
	{
		if ((address & 0x80) == 0x80)
			LD_MOSI_H();
		else
			LD_MOSI_L();
			LD3320_NOP;
			LD_SCK_L();
			address = (address << 1);
			LD3320_NOP;
			LD_SCK_H();
	}
	LD3320_NOP;
	
	for(i = 0;i < 8;i++)
	{
		data = (data << 1);
		temp = LD_MISO;
		LD3320_NOP;
		LD_SCK_L();
		if(temp == 1)
			data |= 0x01;
		LD3320_NOP;
		LD_SCK_H();
	}
	LD3320_NOP;
	LD_CS_H();

	return(data);
}



