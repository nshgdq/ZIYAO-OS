/*********************************************************
8位数据接口的彩屏（HX8347D）的例程，
使用其他彩屏只需包含W25Qxx.c W25Qxx.h type_51.h文件，改相应IO口即可
**********************************************************/

#include "stc12c5a60s2.h"
#include "w25qxx.h" 
#include "type_51.h"
#include "Touch.h"
#include "ds1302.h"
#include <string.h>
#include "timer.h"
#include "GUI.h"
#include "18b20.h"
sbit wien=P0^4;
//函数声明



void main()
{
//	u8 code setime[7]={0x04,0x08,0x23,0x01,0x06,0x01,0x15};
	wien = 0;
	LCD_Initializtion();	
	font_init();		//字库初始化
	TP_Init();
	Ds1302_Init();
	Timer0Init();
//	Ds1302_Write_Time(setime);//设定系统时间
	start_check();
	wien = 1;
	start_logo();
//	while(1)
//	{
//		
//	}
	
	desktop();
}




