

#include "stc12c5a60s2.h"
#include "w25qxx.h" 
#include "type_51.h"
#include "Touch.h"
#include "ds1302.h"
#include <string.h>
#include "timer.h"
#include "app.h"
#include "18b20.h"
#include "uart.h"
#include "led.h"
//函数声明



void main()
{
//	u8 code setime[7]={0x04,0x08,0x23,0x01,0x06,0x01,0x15};
	LCD_Initializtion();	
	font_init();		//字库初始化
	TP_Init();
	Ds1302_Init();
	Timer0Init();
	InitUART(0);
	InitLed();
//	Ds1302_Write_Time(setime);//设定系统时间
	start_check();
	start_logo();
//	while(1)
//	{
//		
//	}
	
	desktop();
}




