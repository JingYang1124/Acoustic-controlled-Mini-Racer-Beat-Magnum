#include "delay.h"
#include "sys.h"
#include "24l01.h" 	 
#include "Key.h"

extern void LD3320_main(void);
extern void LD3320_Init(void); 

	u16 t=0;	
	u8 tmp_buf[33];		
	u8  Send_State;
 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	 			
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
 	NRF24L01_Init();     //初始化NRF24L01 
	LD3320_Init();	     //初始化LD3320
	KEY_Init();	


	NRF24L01_TX_Mode(); //设置NRF24L01为发送模式
  
	for(t=0;t<32;t++)//初始化NRF24L01发送信息
	{
			tmp_buf[t]='A';	
	}	 
	tmp_buf[32]=0;//加入结束符		
	
	while (1)
  {
		LD3320_main();	
    KEY_Scan();		
		Send_State = NRF24L01_TxPacket(tmp_buf);		
	}
	 
}


