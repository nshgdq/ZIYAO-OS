/*********************
日历
*********************/
#include "app.h"
#include "Touch.h"
#include "ds1302.h"
//*****************************
extern u8 time[22];
extern void gettime(u8 *);
extern u16 x,y;
extern void Get_Click1(u16 *x,u16 *y);
void t_menu();
void t_alert();
//*********************************
//日历
//*********************************
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
		if(y>288&&y<320) guiddo(desktop,t_menu,x);
	}
}
void t_menu()//菜单
{
	LCD_Clear(0x051d);
	Show_Str(56,0,"时间选项",32,White,Nocolor);
	LCD_DrawLine(0,35,240,35,White);
	Show_Str(0,38,"◆设定系统时间",24,White,Nocolor);
	Show_Str(0,67,"◆闹钟",24,White,Nocolor);
	guidshow();
	while(1)
	{
		Get_Click(&x,&y);
		if(y>288&&y<320) guiddo(calendar,t_menu,x);
		if(y>38&&y<(38+24)) {Show_Str(0,38,"◆设定系统时间",24,White,Blue);sstmtime();}
		if(y>(38+24)&&y<(38+24+24)) {Show_Str(0,67,"◆闹钟",24,White,Blue);t_alert();}
	}
}
/**************
设置系统时间
***************/
void sstmtime()
{
	u8 setime[7]={0,0,0,0,0,0,0},i=1;
	gettime(time);
	LCD_Clear(0x051d);
	Show_Str(24,20,"设置系统时间",32,White,Nocolor);
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
		Get_Click(&x,&y);
		if(y>288&&y<320){guiddo(t_menu,desktop,x);}//???
		if((x>=40&&x<=80)&&(y>=180&&y<=200)){i++;while(!PEN);}  //Next ???
		if((x>=150&&x<=190)&&(y>=180&&y<=200))	//Ok ???
		{
			setime[0]=((time[17]-'0')<<4)|(time[18]-'0');
			setime[1]=((time[14]-'0')<<4)|(time[15]-'0');
			setime[2]=((time[11]-'0')<<4)|(time[12]-'0');
			setime[3]=((time[8]-'0')<<4)|(time[9]-'0');
			setime[4]=((time[5]-'0')<<4)|(time[6]-'0');
			setime[5]=time[20]-'0';
			setime[6]=((time[2]-'0')<<4)|(time[3]-'0');
			Ds1302_Write_Time(setime);//??????
			alert("已设定系统时间!",0x051d);
			while(!PEN);
		}	
		if((x>=100&&x<=140)&&(y>=105&&y<=125))	//? ???
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
		if((x>=100&&x<=140)&&(y>=148&&y<=168))	//? ???
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
/***************
闹钟
***************/
void t_alert()
{
	LCD_Clear(0x051d);
	guidshow();
	while(1)
	{
		Get_Click(&x,&y);
		if(y>288&&y<320) guiddo(t_menu,t_menu,x);
	}
}