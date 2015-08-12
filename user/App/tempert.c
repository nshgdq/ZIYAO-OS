/**********************
温度
**********************/
#include "app.h"
#include "hx8347d.h"
#include "18b20.h"
extern u16 x,y;
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
			Show_Str(56,78,"当前温度:",16,Red,Nocolor);
			GUI_Text(128,78,temper,Red,White);
			i=1;
		}
		i++;
		if(i>0xff) i=0;
		Get_Click(&x,&y);
		if(y>288&&y<320) guiddo(desktop,desktop,x);
	}
}