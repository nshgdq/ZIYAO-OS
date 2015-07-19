/*****
LED
*****/
#include "touch.h"
#include "app.h"
#include "led.h"
extern u16 x,y;
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