/****************************************************
»­°å
***************************************************/
#include "app.h"
#include "hx8347d.h"
#include "touch.h"
extern u16 x,y;
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