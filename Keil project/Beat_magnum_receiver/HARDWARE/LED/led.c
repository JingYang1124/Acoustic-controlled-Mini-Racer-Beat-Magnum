#include "led.h"
#include "USER_HARDWARE_CONFIG.h"

void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(PORT_LED, &GPIO_InitStructure);					 
 GPIO_SetBits(PORT_LED,GPIO_Pin_13);				
}
 
