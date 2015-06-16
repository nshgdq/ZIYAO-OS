#include "timer.h"
#include "hx8347d.h"
#include "ds1302.h"
u8 i;
void Timer_Routine(void) interrupt 1
{
	TL0 = 0xAB;		
	TH0 = 0x2F;	
	if(i==0xff)
	{
		i=0;
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