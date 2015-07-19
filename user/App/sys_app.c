#include<stc12c5a60s2.h>
#include "w25qxx.h" 
#include "type_51.h"
#include "Touch.h"
#include "ds1302.h"
#include <string.h>
#include "timer.h"
#include "app.h"
#include "type_51.h"
#include "18b20.h"
#include "ATCmd.h"
#include "led.h"
#include "audio.h"
u8 time[22]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u16 x,y;
bit ATC=0;
extern unsigned char temp[20];
void desktop()
{
	u16 i=0;
	desktop:
	TR0=0;
	LCD_Clear(White);
	show_picture(10,20,145,67,0x00600CA0);
//	LCD_DrawBox(10,20,145,68,0xfe41);//d1
	Show_Str(10,71,"日历",16,0xffff,Nocolor);
	show_picture(160,20,70,67,0x00605886);
//	LCD_DrawBox(160,20,70,68,0x051d);//d2
	Show_Str(160,71,"温度",16,0xffff,0x1111);
	show_picture(10,93,70,68,0x00607D2A);
//	LCD_DrawBox(10,93,70,68,0x3a39);//d3
	Show_Str(10,145,"电话",16,0xffff,Nocolor);
	show_picture(85,93,70,68,0x0060A25A);
//	LCD_DrawBox(85,93,70,68,0xff80);//d4
	Show_Str(85,145,"相册",16,0xffff,Nocolor);
	show_picture(160,93,70,68,0x0060C78A);
//	LCD_DrawBox(160,93,70,68,0xa254);//d5
	Show_Str(160,145,"硬件检测",16,0xffff,Nocolor);
	show_picture(10,166,70,68,0x0060ECBA);
//	LCD_DrawBox(10,166,70,68,0x78ef);//d6
	Show_Str(10,218,"画板",16,0xffff,Nocolor);
	show_picture(85,166,145,68,0x006111EA);
	Show_Str(85,218,"串口助手",16,0xffff,Nocolor);
//	LCD_DrawBox(85,166,145,68,0x8802);//d7
	show_picture(10,239,145,65,0x00615EF2);
	Show_Str(10,288,"SPI助手",16,0xffff,Nocolor);
//	LCD_DrawBox(10,239,145,68,0xbbca);//d8
	show_picture(160,239,70,65,0x0061A894);
	Show_Str(160,288,"LED",16,0xffff,Nocolor);
//	LCD_DrawBox(160,239,70,68,0x2586);//d9
	clock();
	TR0=1;
	while(1)
	{
		x=0;y=0;
		if(i==0x0bff) {clock();i=0;}
		i++;
	Get_Click(&x,&y);
	if(x>=10&&x<=80) x=1;if(x>=85&&x<=155) x=2;if(x>=160&&x<=220) x=3;
	if(y>=30&&y<=88) y=1;if(y>=93&&y<=161) y=2;
	if(y>=166&&y<=234) y=3;if(y>=239&&y<=307) y=4;
	switch(y)
	{
		case 1: switch(x)
						{
							case 1:calendar();break;
							case 2:calendar();break;
							case 3:tempert();break;
						}
						break;
		case 2:switch(x)
						{
							case 1:alert("未开放!",White);break;
							case 2:alert("未开放!",White);break;
							case 3:start_check();goto desktop;break;
						}
						break;
		case 3:switch(x)
						{
							case 1:picbox();break;
							case 2:alert("未开放!",White);break;
							case 3:alert("未开放!",White);break;
						}
						break;
		case 4:switch(x)
						{
							case 1:alert("未开放!",White);break;
							case 2:alert("未开放!",White);break;
							case 3:led();break;
						}
						break;
	}
}
}
void start_logo()
{
	LCD_Clear(White);
	show_picture(60,73,140,174,(u32)0x5f4e50);
	delay_ms(0xfff);
}
void alert(char *s,u16 bcolor)
{
	u8 len;
	Show_Str(0,0,s,16,Red,bcolor);
	delay_ms(0x7ff);
	len=(u8)strlen(s)*8;
	LCD_DrawBox(0,0,len,16,bcolor);
}
void Get_Click(u16 *x,u16 *y)
{
	TP_Read_XY2(x,y); 
	//TP_Draw_Big_Point(*x=*x/Touch_X,*y=*y/Touch_Y,Red);
	*x=*x/15.03-14.85;*y=*y/10.81-17.52;
	if(ATC){ATC=0;AT_DO(temp);}
}
void Get_Click1(u16 *x,u16 *y)
{
	TP_Read_XY2(x,y); 
	//TP_Draw_Big_Point(*x=*x/Touch_X,*y=*y/Touch_Y,Red);
	*x=*x/15.03-14.85;*y=*y/10.81-17.52;
}
void delay_ms(u16 ms)    
{ 
	uint16_t i,j; 
	for( i = 0; i < ms; i++ )
	{ 
		for( j = 0; j < 1000; j++ );
	}
} 
void clock()
{
	gettime(time);
	time[16]='\0';
	GUI_Text(200,0,time+11,Black,White);
}
/*********************
导航栏构造
**********************/
void guidshow()
{
	LCD_DrawLine( 0, 288, 240, 288,White );
	Show_Str(20,288,"←",32,White,Nocolor);
	Show_Str(104,288,"█",32,0xa254,Nocolor);
	LCD_DrawLine( 108, 304, 131,304, White );
	LCD_DrawLine( 120, 293, 120,315, White );
	LCD_DrawLine( 80, 288, 80,320, White );
	LCD_DrawLine( 160, 288, 160,320, White );
	Show_Str(187,288,"〓",32,White,Nocolor);
}
/*********************
导航栏执行
参数:pback 返回键函数指针
pmenu 菜单键函数指针
**********************/
void guiddo(void (*pback)(void),void (*pmenu)(void),x)
{
	if(x<80&&x>0) {Show_Str(20,288,"←",32,White,Blue);pback();}
	if(x>80&&x<160) {Show_Str(104,288,"█",32,0xa254,Blue);LCD_DrawLine( 108, 304, 131,304, White );
		LCD_DrawLine( 120, 293, 120,315, White );LCD_DrawLine( 80, 288, 80,320, White );desktop();}
	if(x>160&&x<240){ Show_Str(187,288,"〓",32,White,Blue);pmenu();}
}
/**********************
温度
**********************/
/*void tempert()
{
	u16 i=0;
	u8 temper[7];
	LCD_Clear(0x051d);
	LCD_DrawBox(45,60,152,50,Blue);
	LCD_DrawEBox(55,70,132,30,Red);
	guidshow();
	while(1)
	{
		if(i==0xff||i==0)
		{
			ReadTemperature(temper);
			Show_Str(56,78,"当前温度:",16,Red,Nocolor);
			GUI_Text(128,78,temper,Red,White);
			i=1;
		}
		i++;
		if(i>0xff) i=0;
		Get_Click(&x,&y);
		if(y>288&&y<320) guiddo(desktop,desktop,x);
	}
}*/

