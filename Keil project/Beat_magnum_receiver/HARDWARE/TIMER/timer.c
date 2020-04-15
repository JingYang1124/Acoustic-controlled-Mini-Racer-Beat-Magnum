#include "timer.h"
#include "led.h"
#include "USER_HARDWARE_CONFIG.h"

extern char INA1_PWM;
extern char INB1_PWM;
extern char INA2_PWM;
extern char INB2_PWM;

void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = arr - 1; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc - 1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM2, ENABLE);  //TIMx					 
}

void TIM2_IRQHandler(void)   //TIM2
{
	static int PWM_count = 1;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  
		
		if(PWM_count <= INA1_PWM)
			INA1 = 1;
		else 
			INA1 = 0;
		
		if(PWM_count <= INB1_PWM)
			INB1 = 1;
		else 
			INB1 = 0;
		
		if(PWM_count <= INA2_PWM)
			INA2 = 1;
		else 
			INA2 = 0;
		
		if(PWM_count <= INB2_PWM)
			INB2 = 1;
		else 
			INB2 = 0;
		
		PWM_count ++;
		if(PWM_count > 100)
			PWM_count = 1;
		//--------------------------------------------------------------------------//	
	}
}

