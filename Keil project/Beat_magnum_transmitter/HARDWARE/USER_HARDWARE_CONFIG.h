#ifndef USER_HARDWARE_CONFIG_H
#define USER_HARDWARE_CONFIG_H 	

#include "sys.h"

/*************LD3320 端口信息********************
 * RST      PA3
 * CS   	  PA2
 * WR/SPIS  PA0
 * P2/SDCK  PA5
 * P1/SDO   PA6
 * P0/SDI   PA7
 * IRQ      PB1
 * A0				PA4
*****************************************/
/********************NRF24L01信息********************
 * NRF24L01_IRQ         PB6
 * NRF24L01_CSN      	  PB7
 * NRF24L01_CE          PB8
 * NRF24L01_SCK         PB13
 * NRF24L01_MISO        PB14
 * NRF24L01_MOSI        PB15
*****************************************/
/********************按键信息********************
 * KEY_UP(前进)         PA8
 * KEY_DOWN(后退)   	  PA11
 * KEY_LEFT(向左)       PA12
 * KEY_RIGHT(向右)      PA15
 * KEY_STOP(停止)       PB9
*****************************************/

#define PORT_LD_SPI         GPIOA //LD的MOSI\MISO\SCK都在GPIOA上
#define PORT_LD_CE          GPIOA
#define PORT_LD_RST         GPIOA
#define PORT_LD_A0          GPIOA
#define PORT_LD_SPIS        GPIOA
#define PORT_LD_IRQ         GPIOB

#define PIN_LD_SPI_SCK      GPIO_Pin_5
#define PIN_LD_SPI_MISO     GPIO_Pin_6
#define PIN_LD_SPI_MOSI     GPIO_Pin_7
#define PIN_LD_CE           GPIO_Pin_2
#define PIN_LD_RST          GPIO_Pin_3
#define PIN_LD_A0           GPIO_Pin_4
#define PIN_LD_SPIS         GPIO_Pin_0
#define PIN_LD_IRQ          GPIO_Pin_1

#define PORT_NRF24L01       GPIOB
#define PIN_NRF24L01_IRQ    GPIO_Pin_6
#define PIN_NRF24L01_CSN    GPIO_Pin_7
#define PIN_NRF24L01_CE     GPIO_Pin_8
#define PIN_NRF24L01_SCK    GPIO_Pin_13
#define PIN_NRF24L01_MISO   GPIO_Pin_14
#define PIN_NRF24L01_MOSI   GPIO_Pin_15


#define PORT_KEY_MOVE       GPIOA
#define PORT_KEY_STOP       GPIOB
#define PIN_KEY_UP          GPIO_Pin_8
#define PIN_KEY_DOWN        GPIO_Pin_11
#define PIN_KEY_LEFT        GPIO_Pin_12
#define PIN_KEY_RIGHT       GPIO_Pin_15
#define PIN_KEY_STOP        GPIO_Pin_9


#define DATE_A           7     /*识别短语数量*/
#define DATE_B           20		/*单个短语的拼音总长度上限(最大79)*/

//用来对pCode数组进行赋值，有几个短语就需要进行几个宏定义，后面的数字可以自定义，但是建议如下依次增加
#define CODE_YDCF	       1	 /*跃动冲锋*/
#define CODE_QJ	         2	 /*前进*/
#define CODE_T	         3	 /*停*/
#define CODE_HT	         4	 /*后退*/
#define CODE_JS          5   /*加速*/
#define CODE_XZ          6   /*向左*/
#define CODE_XY          7   /*向右*/

#define CLK_IN           8	 /* LD3320使用的晶振频率（单位：Mhz）*/
#define MIC_VOL          0x10 //可以设置 00H-7FH，越小需要距离越近才能识别，对于远处的干扰具有一定的抵抗能力
#define Vad_Silence_End  0x0A //设置LD3320的B5寄存器，每一单位代表10毫秒。表示检测到语音段后连续检测这么长时间的噪声认为是语音结束
#define Vad_Length       0xA  //设置LD3320的B6寄存器，每一单位代表100毫秒。代表检测到语音段后最长允许多久的语音识别

//以下为NRF24L01发送的数据
#define NRF_COMMAND_YDCF  'Y'
#define NRF_COMMAND_QJ    'Q'
#define NRF_COMMAND_T     'T'
#define NRF_COMMAND_HT    'H'
#define NRF_COMMAND_JS    'J'
#define NRF_COMMAND_XZ    'L'
#define NRF_COMMAND_XY    'R' 

//NRF24L01操作线
#define NRF24L01_CE   PBout(8) //24L01片选信号
#define NRF24L01_CSN  PBout(7) //SPI片选信号	   
#define NRF24L01_IRQ  PBin(6)  //IRQ主机数据输入


//*****************************************************************
//*****************************************************************
//以下内容可以不用修改，下面的宏定义依赖于上面内容//
//*****************************************************************
//*****************************************************************
#define KEY_UP      GPIO_ReadInputDataBit(PORT_KEY_MOVE,PIN_KEY_UP)
#define KEY_DOWN    GPIO_ReadInputDataBit(PORT_KEY_MOVE,PIN_KEY_DOWN)
#define KEY_LEFT    GPIO_ReadInputDataBit(PORT_KEY_MOVE,PIN_KEY_LEFT)
#define KEY_RIGHT   GPIO_ReadInputDataBit(PORT_KEY_MOVE,PIN_KEY_RIGHT) 
#define KEY_STOP    GPIO_ReadInputDataBit(PORT_KEY_STOP,PIN_KEY_STOP) 

#define LD_RST_H() GPIO_SetBits(PORT_LD_RST, PIN_LD_RST )
#define LD_RST_L() GPIO_ResetBits(PORT_LD_RST, PIN_LD_RST )

#define LD_CS_H()	GPIO_SetBits(PORT_LD_CE, PIN_LD_CE)
#define LD_CS_L()	GPIO_ResetBits(PORT_LD_CE, PIN_LD_CE)

#define LD_MOSI_H()	GPIO_SetBits(PORT_LD_SPI, PIN_LD_SPI_MOSI)
#define LD_MOSI_L()	GPIO_ResetBits(PORT_LD_SPI, PIN_LD_SPI_MOSI)

#define LD_SCK_H()	GPIO_SetBits(PORT_LD_SPI, PIN_LD_SPI_SCK)
#define LD_SCK_L()	GPIO_ResetBits(PORT_LD_SPI, PIN_LD_SPI_SCK)

#define LD_SPIS_H()  GPIO_SetBits(PORT_LD_SPIS, PIN_LD_SPIS)
#define LD_SPIS_L()  GPIO_ResetBits(PORT_LD_SPIS, PIN_LD_SPIS)

#define LD_MISO      GPIO_ReadInputDataBit(PORT_LD_SPI,PIN_LD_SPI_MISO)

extern u8  sRecog[DATE_A][DATE_B];
extern u8  pCode[DATE_A];
//*****************************************************************
//*****************************************************************

#endif
