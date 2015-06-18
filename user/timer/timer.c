#include "timer.h"
#include "hx8347d.h"
#include "ds1302.h"
#include "gui.h"
#include "uart.h"
u8 i;
void Timer_Routine(void) interrupt 1
{
	TL0 = 0xAB;		
	TH0 = 0x2F;	
	if(i>=0x5f)
	{
		i=0;
		if(flag==1)
		{
			flag=0;
			GUI_Text(0, 0,temp,Red,0xffff);
		}
	}
	i++;
}

void Timer0Init(void)		//20ms@32MHz
{
	TMOD |= 0x01;	
	TL0 = 0xAB;		
	TH0 = 0x2F;			
	ET0 = 1 ;
	EA = 1;
	TR0 = 0;	
}