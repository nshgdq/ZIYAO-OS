#include <stc12c5a60s2.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit  BEEP=P2^1;//���������Ŷ���
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
	  BEEP=~BEEP;       //���Ƶ��1KHz
	  delay500us();       //��ʱ500us
	}

	for(j=200;j>0;j--)
	{
	  BEEP=~BEEP;       //���Ƶ��500Hz
	  delay500us();       //��ʱ1ms
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


