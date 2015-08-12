#include "led.h"
void InitLed()
{
	LED1=1;
	LED2=1;
	LED3=1;
}
void SetLed(u8 led,bit stat)
{
	switch(led)
	{
		case 1:LED1=stat;break;
		case 2:LED2=stat;break;
		case 3:LED3=stat;break;
	}
}
bit RedLed(u8 led)
{
	switch(led)
	{
		case 1:return LED1;break;
		case 2:return LED2;break;
		case 3:return LED3;break;
	}
}