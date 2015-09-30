#include <stc12c5a60s2.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit  BEEP=P2^1;//蜂鸣器引脚定义
void delay500us()		//@32MHz
{
	unsigned char i, j;

	i = 16;
	j = 141;
	do
	{
		while (--j);
	} while (--i);
}
void beep()
{
	uchar j;
	for(j=200;j>0;j--)
	{
	  BEEP=~BEEP;       //输出频率1KHz
	  delay500us();       //延时500us
	}

	for(j=200;j>0;j--)
	{
	  BEEP=~BEEP;       //输出频率500Hz
	  delay500us();       //延时1ms
	  delay500us();
	}
}
void nbeep(int t)
{
  while(t)
  {
		beep();
		t--;
  }
}


