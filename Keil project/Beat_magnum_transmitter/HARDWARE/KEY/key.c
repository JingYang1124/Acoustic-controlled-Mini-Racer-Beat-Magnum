#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "USER_HARDWARE_CONFIG.h"

extern u8  tmp_buf[33];	

//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	GPIO_InitStructure.GPIO_Pin  = PIN_KEY_UP|PIN_KEY_DOWN|PIN_KEY_LEFT|PIN_KEY_RIGHT;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(PORT_KEY_MOVE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = PIN_KEY_STOP;
	GPIO_Init(PORT_KEY_STOP, &GPIO_InitStructure);
}

void KEY_Scan(void)
{	 
  
	if(KEY_UP==0||KEY_DOWN==0||KEY_LEFT==0||KEY_RIGHT==0||KEY_STOP==0)
	{
		delay_ms(10);//去抖动 
		if(KEY_UP==0)tmp_buf[0] = NRF_COMMAND_QJ;
		else if(KEY_DOWN==0)tmp_buf[0]= NRF_COMMAND_HT;
		else if(KEY_LEFT==0)tmp_buf[0]= NRF_COMMAND_XZ;
		else if(KEY_RIGHT==0)tmp_buf[0]= NRF_COMMAND_XY;
		else if(KEY_STOP==0)tmp_buf[0]= NRF_COMMAND_T;
	}   

}
