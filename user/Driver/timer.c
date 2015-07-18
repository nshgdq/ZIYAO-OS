#include "timer.h"
#include "hx8347d.h"
#include "gui.h"
#include "uart.h"
#include "atcmd.h"
#include "w25qxx.h"
#include "ds1302.h"
#include "touch.h"
u8 i;
extern bit ATC;
extern unsigned temp[20];
void Timer_Routine(void) interrupt 1
{
	TL0 = 0xAB;		
	TH0 = 0x2F;
	TCS = 1;	
	if(i>=0x5f)
	{
		i=0;
		if(flag==1)
		{
			flag=0;
			if(IsATCmd(temp)) ATC=1;
			else alert(temp,0xffff);
			temp[0]=0;
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