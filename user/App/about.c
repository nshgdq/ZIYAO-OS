#include "stc12c5a60s2.h"
#include "hx8347d.h"
#include "app.h"
extern u16 x,y;
void SMsg()
{
	LCD_Clear(0x051d);
	Show_Str(88,20,"关于",32,White,Nocolor);
	Show_Str(15,72,"开发: 梁卓华(紫耀风)",16,Black,Nocolor);
	Show_Str(15,88,"联系QQ: ",16,Black,Nocolor);
	Show_Str(15+16*4,88,"869189602",16,Blue,Nocolor);
	Show_Str(15,104,"源码开放:",16,Black,Nocolor);
	Show_Str(15,120,"https://github.com/ziyaofeng",16,Blue,Nocolor);
	Show_Str(15,136,"团队: ",16,Black,Nocolor);
	Show_Str(15+16*3,136,"紫耀",16,Black,Nocolor);
	guidshow();
	while(1)
	{
		Get_Click(&x,&y);
		if(y>288&&y<320) guiddo(desktop,desktop,x);
	}
}
