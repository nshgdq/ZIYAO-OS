#include "timer.h"
#include "hx8347d.h"
#include "gui.h"
#include "uart.h"
#include "atcmd.h"
#include "w25qxx.h"
#include "ds1302.h"
#include "touch.h"
u8 i;
void Timer_Routine(void) interrupt 1
{
	TF0=0;
	TL0 = 0xAB;		
	TH0 = 0x2F;	
	if(i>=0x5f)
	{
		i=0;
		W25Qxx_CS=1;
		CE=0;
		TCS=1;
		if(flag==1)
		{
			flag=0;
			if(IsATCmd(temp)) AT_DO(temp);
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