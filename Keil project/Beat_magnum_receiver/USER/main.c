#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "24l01.h"
#include "MX1508.h"
#include "USER_HARDWARE_CONFIG.h"

#define RC_STOP  0
#define RC_RUN_F 1
#define RC_RUN_B 2


char RunState = RC_STOP;
	
char INA1_PWM = 0;//Right wheel go backward
char INB1_PWM = 0;//Right wheel go forward
char INA2_PWM = 0;//Left wheel go forward
char INB2_PWM = 0;//Left wheel go backward

	u16 t=0;	
	u8 tmp_buf[33];		
	u8  Send_State;

	float HCSR_Value;

 int main(void)
 {
	u8 silentcount = 0;
 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();
	MX1508_Init();
	TIM2_Int_Init(5,7200);    // New time base: 72M / 7200 = 10000Hz; Every inttrupt time gap: 1/10000Hz * 5 = 0.5ms  	   	 

	NRF24L01_Init();    		//初始化NRF24L01 
	LED0 = 0;
	NRF24L01_RX_Mode();		  
			
	for(t=0;t<32;t++)
	{
		tmp_buf[t]='A';	
	}	  
	tmp_buf[32]=0;//加入结束符		 
	while(1)
	{			
		
		if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
			{
				silentcount = 0;
				tmp_buf[32]=0;//加入字符串结束符
				if(tmp_buf[0] == NRF_COMMAND_YDCF) //“跃动冲锋” 亮灯
				{
					LED0=!LED0;
				}
				if(tmp_buf[0] == NRF_COMMAND_T)    //“停”
				{
					RunState = RC_STOP;
					INA1_PWM = 0;
					INB1_PWM = 0;
					INA2_PWM = 0;
					INB2_PWM = 0;
				}
				if(tmp_buf[0] == NRF_COMMAND_QJ)   //“前进”
				{
					if(RunState == RC_STOP || RunState == RC_RUN_F)
					{
						INA1_PWM = 0;
						INB1_PWM = 70;
						INA2_PWM = 70;
						INB2_PWM = 0;
						RunState = RC_RUN_F;
					}
				}
				if(tmp_buf[0] == NRF_COMMAND_JS)   //“加速”
				{
					if(RunState == RC_STOP || RunState == RC_RUN_F)
					{
						INA1_PWM = 0;
						INB1_PWM = 95;
						INA2_PWM = 95;
						INB2_PWM = 0;
						RunState = RC_RUN_F;
					}
				}
				if(tmp_buf[0] == NRF_COMMAND_HT)   //“后退”
				{
					if(RunState == RC_STOP)
					{
						INA1_PWM = 70;
						INB1_PWM = 0;
						INA2_PWM = 0;
						INB2_PWM = 70;
						RunState = RC_RUN_B;
					}
				}
				if(tmp_buf[0] == NRF_COMMAND_XZ)   //“向左”
				{
					if(RunState == RC_STOP || RunState == RC_RUN_F)
					{
						INA1_PWM = 0;
						INB1_PWM = 80;
						INA2_PWM = 45;
						INB2_PWM = 0;
						RunState = RC_RUN_F;
					}
				}
				if(tmp_buf[0] == NRF_COMMAND_XY)   //“向右”
				{
					if(RunState == RC_STOP || RunState == RC_RUN_F)
					{
						INA1_PWM = 0;
						INB1_PWM = 45;
						INA2_PWM = 80;
						INB2_PWM = 0;
						RunState = RC_RUN_F;
					}
				}
			}
			else
			{
					silentcount ++;
					if(silentcount == 20)  //连续20次循环没有接收到遥控信息，则自动停止
					{
						RunState = RC_STOP;
						INA1_PWM = 0;
						INB1_PWM = 0;
						INA2_PWM = 0;
						INB2_PWM = 0;
						silentcount = 0;
					}
					delay_ms(10);	  
			}
	}	 
 }

