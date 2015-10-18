/**********************
温度
**********************/
#include "app.h"
#include "hx8347d.h"
#include "18b20.h"
#include "stdio.h"
#include "audio.h"
#include "touch.h"
void Get_Click1(u16 *x,u16 *y);
extern u16 x,y;
void tempert()
{
	static float	mintmp,maxtmp,tmp;
	u16 i=0;
	u8 temper[7];
	bit edit=1;
	LCD_Clear(0x051d);
	LCD_DrawBox(45,60,152,50,Blue);
	LCD_DrawEBox(55,70,132,30,Red);
	Show_Str(56,78,"当前温度:",16,Red,Nocolor);
	Show_Str(45,110,"温度报警：",16,Black,Nocolor);
	Show_Str(45,152,"温度超出范围将报警!",16,Red,Nocolor);
	LCD_DrawBox(56,180,40,20,0xc618);
	Show_Str(71,183,">",16,Black,Nocolor);
	LCD_DrawEBox(56,180,40,20,Blue);
	LCD_DrawBox(98,180,40,20,0xc618);
	Show_Str(113,183,"+",16,Black,Nocolor);
	LCD_DrawEBox(98,180,40,20,Blue);
	LCD_DrawBox(140,180,40,20,0xc618);
	Show_Str(155,183,"-",16,Black,Nocolor);
	LCD_DrawEBox(140,180,40,20,Blue);
	guidshow();
	mintmp=25.000;
	maxtmp=32.000;
reflesh:
	sprintf(temper,"%7.3f",maxtmp);
	if(!edit) GUI_Text(120,129,temper,Green,Black);
	else GUI_Text(120,129,temper,Red,White);
	sprintf(temper,"%7.3f",mintmp);
	if(edit) GUI_Text(45,129,temper,Green,Black);
	else GUI_Text(45,129,temper,Red,White);
	while(1)
	{
		if(i==0xff||i==0)
		{
			tmp=(float)Read18b20()*0.0625;
			sprintf(temper,"%7.3f",tmp);
			GUI_Text(128,78,temper,Red,White);
			i=1;
		}
		i++;
		if((tmp<mintmp)||(tmp>maxtmp)) {beep();i=0xff;}
		if(i>=0xff) i=0;
		Get_Click1(&x,&y);
		if(y>=180&&y<=200)
		{
			while(!PEN);
			if(x>=56&&x<=96){edit=!edit;goto reflesh;}
			if(x>=98&&x<=138)
			{
				if(edit){mintmp+=0.5;goto reflesh;}
				else{maxtmp+=0.5;goto reflesh;}
			}
			if(x>=140&&x<=180)
			{
				if(edit){mintmp-=0.5;goto reflesh;}
				else{maxtmp-=0.5;goto reflesh;}
			}
		}
		if(y>288&&y<320) guiddo(desktop,desktop,x);
	}
}