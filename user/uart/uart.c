#include"uart.h"
#define S2RI 0x01	//����2�����ж������־λ
#define S2TI 0x02	//����2�����ж������־λ
unsigned char temp[20];
bit flag=0;
unsigned char *p=temp;
/****************���пڳ�ʼ������****************/
void InitUART(bit bite)//9600/115200@32MHZ
{
	AUXR &= 0xF7;		//�����ʲ�����
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T
	if(!bite)	BRT = 0x98;		//9600
	if(bite) BRT = 0xf7;		//115200
	AUXR |= 0x10;		//�������������ʷ�����
	EA =1;	//�����ж�
  IE2 =0x01;	//������2�ж�  ES2=1
}
void UART_SendOneByte(unsigned char c)
{
    S2BUF = c;
    while(!(S2CON&S2TI));  //��S2TI=0���ڴ˵ȴ�
    S2CON&=~S2TI;	  //S2TI=0
}
void UART_SendStr(unsigned char *str)
{
	while(str!=0)
	{
		UART_SendOneByte(str);
		str++;	
	}
}
/************���п�2�жϴ�����*************/
void UART_Interrupt(void) interrupt 8
{
	if(flag==0) p=temp;
	if(S2CON&S2RI)
	{
		flag=1;
		S2CON&=~S2RI;
		*p=S2BUF;
//		UART_SendOneByte(*p);
		p++;
		*p=0;
	} 
}