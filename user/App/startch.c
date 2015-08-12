#include "app.h"
#include "hx8347d.h"
#include "ds1302.h"
#include "18b20.h"
#include "led.h"
#include "audio.h"
extern u8 time[22];
extern void gettime(u8 *);
void start_check()
{
	u8 temper[7];
	LCD_Clear(Black);
	GUI_Text(0,0,"Hardware Check Running",Green,Black);
	GUI_Text(0,16,"*******Flash Check*******",Green,Black);
	switch(W25Qxx_ReadID())
	{
		case W25Q80:Show_Str(0,32,"W25Q80",16,Red,White);break;
		case W25Q16:Show_Str(0,32,"W25Q16",16,Red,White);break;
		case W25Q32:Show_Str(0,32,"W25Q32",16,Red,White);break;
		case W25Q64:Show_Str(0,32,"W25Q64",16,Red,White);break;	
		case W25Q128:Show_Str(0,32,"W25Q128",16,Red,White);break;	
		default:GUI_Text(0,32,"Flash Error",Red,White);delay_ms(0xfff);break;
	}
	delay_ms(0xff);
	Show_Str(0,48,"****时钟检测****",16,Green,Black);
	Show_Str(0,64,"读取时间中...",16,Red,White);
	gettime(time);
	Show_Str(0,80,time,16,Red,White);
	delay_ms(0xff);
	Show_Str(0,96,"****温度检测****",16,Green,Black);
	Show_Str(0,112,"读取温度中...",16,Red,White);
	ReadTemperature(temper);
	delay_ms(0x7ff);
	ReadTemperature(temper);
	Show_Str(0,128,"当前温度:",16,Green,Nocolor);
	GUI_Text(80,128,temper,Red,White);
	Show_Str(0,144,"****LED检测****",16,Green,Black);
	LED1=0;
	Show_Str(0,160,"LED1 亮",16,Red,White);
	delay_ms(0x5ff);
	LED2=0;
	Show_Str(0,160,"LED2 亮",16,Red,White);
	delay_ms(0x5ff);
	LED3=0;
	Show_Str(0,160,"LED3 亮",16,Red,White);
	delay_ms(0x5ff);
	InitLed();
	Show_Str(0,160,"LED  关",16,Red,White);
	delay_ms(0x5ff);
	Show_Str(0,176,"****蜂鸣器检测****",16,Green,Black);
	Show_Str(0,192,"警报3声",16,Red,White);
	beep(3);
	delay_ms(0xfff);
}