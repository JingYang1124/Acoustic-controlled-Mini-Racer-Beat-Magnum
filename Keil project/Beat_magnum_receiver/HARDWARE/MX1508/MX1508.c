#include "MX1508.h"
#include "USER_HARDWARE_CONFIG.h"

void MX1508_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = PIN_INA1|PIN_INB1|PIN_INA2|PIN_INB2;	  			 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz    		 
 GPIO_Init(PORT_MX1508, &GPIO_InitStructure);	  
	
 GPIO_ResetBits(PORT_MX1508,PIN_INA1); 
 GPIO_ResetBits(PORT_MX1508,PIN_INB1);
 GPIO_ResetBits(PORT_MX1508,PIN_INA2);
 GPIO_ResetBits(PORT_MX1508,PIN_INB2);	
}
 
