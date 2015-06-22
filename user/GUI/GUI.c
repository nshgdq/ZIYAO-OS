#include<stc12c5a60s2.h>
#include "w25qxx.h" 
#include "type_51.h"
#include "Touch.h"
#include "ds1302.h"
#include <string.h>
#include "timer.h"
#include "GUI.h"
#include "type_51.h"
#include "18b20.h"
#include "ATCmd.h"
#include "led.h"
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
							case 1:alert("电话功能未开放！",White);break;
							case 2:alert("相册功能未开放！",White);break;
							case 3:start_check();goto desktop;break;
						}
						break;
		case 3:switch(x)
						{
							case 1:picbox();break;
							case 2:alert("串口助手未开放！",White);break;
							case 3:alert("串口助手未开放！",White);break;
						}
						break;
		case 4:switch(x)
						{
							case 1:alert("SPI助手未开放",White);break;
							case 2:alert("SPI助手未开放",White);break;
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
	Show_Str(0,128,"当前温度：",16,Green,Nocolor);
	GUI_Text(80,128,temper,Red,White);
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
日历
*********************/
void calendar()
{
	u16 i=0;
	gettime(time);
	time[7]='\0';
	LCD_Clear(0x051d);
	LCD_DrawBox(60,60,120,20,Yellow);
	LCD_DrawBox(60,80,120,104,White);
	GUI_Text(61,61,time,Red,Nocolor);
	Show_Str(150,61,"周",16,Red,Nocolor);
	GUI_Text(166,61,time+20,Red,Nocolor);
	time[10]='\0';
	Show_Str(105,110,time+8,32,Red,Nocolor);
	guidshow();
	while(1)
	{
		if(i==0xbff||i==0)
		{
			gettime(time);
			time[16]='\0';
			GUI_Text(100,150,time+11,Red,White);
			i=1;
		}
		i++;
		Get_Click(&x,&y);
		if(y>288&&y<320) guiddo(desktop,sstmtime,x);
	}
}
/**************
设定系统时间
***************/
void sstmtime()
{
	u8 setime[7]={0,0,0,0,0,0,0},i=1;
	gettime(time);
	LCD_Clear(0x051d);
	Show_Str(24,20,"设定系统时间",32,White,Nocolor);
	GUI_Text(40,128,time,Red,White);
	LCD_DrawBox(100,105,40,20,0xc618);
	Show_Str(115,108,"▲",16,Black,Nocolor);
	LCD_DrawEBox(100,105,40,20,Blue);
	LCD_DrawBox(100,148,40,20,0xc618);
	Show_Str(115,153,"▼",16,Black,Nocolor);
	LCD_DrawEBox(100,148,40,20,Blue);
	LCD_DrawBox(40,180,40,20,0xc618);
	GUI_Text(42,182,"Next",Black,Nocolor);
	LCD_DrawEBox(40,180,40,20,Blue);
	LCD_DrawBox(170,180,40,20,0xc618);
	GUI_Text(185,182,"Ok",Black,Nocolor);
	LCD_DrawEBox(170,180,40,20,Blue);
	guidshow();
	time[4]=time[7]=time[10]=time[13]=time[16]=time[19]=0;
	while(1)
	{
		switch(i)
		{
			case 1:GUI_Text(40,128,time,Green,Black);GUI_Text(40+8*20,128,time+20,Red,White);break;
			case 2:GUI_Text(40+8*5,128,time+5,Green,Black);GUI_Text(40,128,time,Red,White);break;
			case 3:GUI_Text(40+8*8,128,time+8,Green,Black);GUI_Text(40+8*5,128,time+5,Red,White);break;
			case 4:GUI_Text(40+8*11,128,time+11,Green,Black);GUI_Text(40+8*8,128,time+8,Red,White);break;
			case 5:GUI_Text(40+8*14,128,time+14,Green,Black);GUI_Text(40+8*11,128,time+11,Red,White);break;
			case 6:GUI_Text(40+8*17,128,time+17,Green,Black);GUI_Text(40+8*14,128,time+14,Red,White);break;
			case 7:GUI_Text(40+8*20,128,time+20,Green,Black);GUI_Text(40+8*17,128,time+17,Red,White);break;
		}
		Get_Click1(&x,&y);
		if(y>288&&y<320){guiddo(calendar,desktop,x);}//导航栏
		if((x>=40&&x<=80)&&(y>=180&&y<=200)){i++;while(!PEN);}  //Next 键操作
		if((x>=150&&x<=190)&&(y>=180&&y<=200))	//Ok 键操作
		{
			setime[0]=((time[17]-'0')<<4)|(time[18]-'0');
			setime[1]=((time[14]-'0')<<4)|(time[15]-'0');
			setime[2]=((time[11]-'0')<<4)|(time[12]-'0');
			setime[3]=((time[8]-'0')<<4)|(time[9]-'0');
			setime[4]=((time[5]-'0')<<4)|(time[6]-'0');
			setime[5]=time[20]-'0';
			setime[6]=((time[2]-'0')<<4)|(time[3]-'0');
			Ds1302_Write_Time(setime);//设定系统时间
			alert("已设定系统时间！",0x051d);
			while(!PEN);
		}	
		if((x>=100&&x<=140)&&(y>=105&&y<=125))	//▲ 键操作
		{
			switch(i)
			{
				case 1:time[3]++;if(time[3]>'9') {time[3]='0';time[2]++;}if(time[2]>'9') time[2]='0';break;
				case 2:time[6]++;if(time[6]>'2'&&time[5]=='1') {time[6]='1';time[5]='0';}if(time[6]>'9') {time[5]++;time[6]='0';}break;
				case 3:time[9]++;if(time[9]>'1'&&time[8]=='3') {time[9]='1';time[8]='0';}if(time[9]>'9') {time[8]++;time[9]='0';}break;
				case 4:time[12]++;if(time[12]>'3'&&time[11]=='2') {time[12]='0';time[11]='0';}if(time[12]>'9') {time[11]++;time[12]='0';}break;
				case 5:time[15]++;if(time[15]>'9'&&time[14]=='5') {time[15]='0';time[14]='0';}if(time[15]>'9') {time[14]++;time[15]='0';}break;
				case 6:time[18]++;if(time[18]>'9'&&time[17]=='5') {time[18]='0';time[17]='0';}if(time[18]>'9') {time[17]++;time[18]='0';}break;
				case 7:time[20]++;if(time[20]>'7') time[20]='1';
			}
			while(!PEN);
		}	
		if((x>=100&&x<=140)&&(y>=148&&y<=168))	//▼ 键操作
		{
			switch(i)
			{
				case 1:if(time[3]=='0'&&time[2]=='0') {time[3]='9';time[2]='9';} if(time[3]=='0'&&time[2]!='0') {time[3]='9'+1;time[2]--;} time[3]--;break;
				case 2:if(time[6]=='1'&&time[5]=='0') {time[6]='2'+1;time[5]='1';} if(time[6]=='0'&&time[5]!='0') {time[6]='9'+1;time[5]--;} time[6]--;break;
				case 3:if(time[9]=='1'&&time[8]=='0') {time[9]='1'+1;time[8]='3';} if(time[9]=='0'&&time[8]!='0') {time[9]='9'+1;time[8]--;} time[9]--;break;
				case 4:if(time[12]=='0'&&time[11]=='0') {time[12]='3'+1;time[11]='2';} if(time[12]=='0'&&time[11]!='0') {time[12]='9'+1;time[11]--;} time[12]--;break;
				case 5:if(time[15]=='0'&&time[14]=='0') {time[15]='9'+1;time[14]='5';} if(time[15]=='0'&&time[14]!='0') {time[15]='9'+1;time[14]--;} time[15]--;break;
				case 6:if(time[18]=='0'&&time[17]=='0') {time[18]='9'+1;time[17]='5';} if(time[18]=='0'&&time[17]!='0') {time[18]='9'+1;time[17]--;} time[18]--;break;
				case 7:if(time[20]=='1')time[20]='7'+1;time[20]--;
			}
			
			while(!PEN);
		}
		if (i>7) i=1;
	}
}
/*********************
导航栏构造及执行
**********************/
void guidshow()
{
	LCD_DrawLine( 0, 288, 240, 288,White );
	Show_Str(20,288,"←",32,White,Nocolor);
	Show_Str(104,288,"■",32,0xa254,Nocolor);
	LCD_DrawLine( 108, 304, 131,304, White );
	LCD_DrawLine( 120, 293, 120,315, White );
	LCD_DrawLine( 80, 288, 80,320, White );
	LCD_DrawLine( 160, 288, 160,320, White );
	Show_Str(187,288,"〓",32,White,Nocolor);
}
/*********************
导航栏执行
参数：pback 返回键点击调用函数的指针
pmenu 菜单键点击调用函数的指针
**********************/
void guiddo(void (*pback)(void),void (*pmenu)(void),x)
{
	if(x<80&&x>0) {Show_Str(20,288,"←",32,White,Blue);pback();}
	if(x>80&&x<160) {Show_Str(104,288,"■",32,0xa254,Blue);LCD_DrawLine( 108, 304, 131,304, White );
		LCD_DrawLine( 120, 293, 120,315, White );LCD_DrawLine( 80, 288, 80,320, White );desktop();}
	if(x>160&&x<240){ Show_Str(187,288,"〓",32,White,Blue);pmenu();}
}
/**********************
温度
**********************/
void tempert()
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
			Show_Str(56,78,"当前温度：",16,Red,Nocolor);
			GUI_Text(128,78,temper,Red,White);
			i=1;
		}
		i++;
		if(i>0xff) i=0;
		Get_Click(&x,&y);
		if(y>288&&y<320) guiddo(desktop,desktop,x);
	}
}
/****************************************************
画板
***************************************************/
void picbox()
{
	u16 color=Red;
	LCD_Clear(0x051d);
	LCD_DrawBox(0,0,240,288,White);
	LCD_DrawBox(0,264,240,24,0x051d);
	LCD_DrawBox(0,264,24,24,White);
	LCD_DrawBox(24,264,24,24,Black);
	LCD_DrawBox(48,264,24,24,Grey);
	LCD_DrawBox(72,264,24,24,Blue);
	LCD_DrawBox(96,264,24,24,Red);
	LCD_DrawBox(120,264,24,24,Magenta);
	LCD_DrawBox(144,264,24,24,Green);
	LCD_DrawBox(168,264,24,24,Cyan);
	LCD_DrawBox(192,264,24,24,Yellow);
	LCD_DrawBox(216,264,24,24,0xb723);
	guidshow();
	while(1)
	{
		Get_Click(&x,&y);
		if((y>0&&y<264)) TP_Draw_Big_Point(x,y,color);
		if(y>288&&y<320) guiddo(desktop,desktop,x);
		if(y>264&&y<288) 
			switch((u8)(x/24))
			{
				case 0:color=White;  break;
				case 1:color=Black; break;
				case 2:color=Grey;   break;
				case 3:color=Blue;   break;
				case 4:color=Red;    break;
				case 5:color=Magenta;break;
				case 6:color=Green;  break;
				case 7:color=Cyan;   break;
				case 8:color=Yellow; break;
				case 9:color=0xb723;break;
			}
	}
}
/*****
LED
*****/
void led()
{
	unsigned char ctr=0;
	LCD_Clear(0x051d);
	Show_Str(65,10,"LED控制",32,White,Nocolor);
	guidshow();
	GUI_Text(30,50,"LED1",White,Nocolor);
	GUI_Text(30,120,"LED2",White,Nocolor);
	GUI_Text(30,190,"LED3",White,Nocolor);
	while(1)
	{
		if(RedLed(1)){
			LCD_DrawBox(70,50,150,60,Blue);
			Show_Str(30,76,"关",16,Blue,0x051d);	
		}else{
			LCD_DrawBox(70,50,150,60,Green);
			Show_Str(30,76,"开",16,Red,0x051d);
		}
		if(RedLed(2)){
			LCD_DrawBox(70,120,150,60,Blue);
			Show_Str(30,146,"关",16,Blue,0x051d);
		}else {
			LCD_DrawBox(70,120,150,60,Red);
			Show_Str(30,146,"开",16,Red,0x051d);
		}
		if(RedLed(3)){
			LCD_DrawBox(70,190,150,60,Blue);
			Show_Str(30,216,"关",16,Blue,0x051d);
		}else {
			LCD_DrawBox(70,190,150,60,Yellow);	
			Show_Str(30,216,"开",16,Red,0x051d);
		}
		Get_Click(&x,&y);
		while(!PEN);
		if(y>288&&y<320) guiddo(desktop,desktop,x);
		if((x>30&&x<210)&&(y>50&&y<110)) SetLed(1,!RedLed(1));
		if((x>30&&x<210)&&(y>120&&y<180)) SetLed(2,!RedLed(2));
		if((x>30&&x<210)&&(y>190&&y<250)) SetLed(3,!RedLed(3));
	}
}