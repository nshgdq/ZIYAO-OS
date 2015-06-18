#include"uart.h"
#define S2RI 0x01	//串口2接收中断请求标志位
#define S2TI 0x02	//串口2发送中断请求标志位
unsigned char temp;
/****************串行口初始化函数****************/
void InitUART(bit bite)//9600/115200@32MHZ
{
	AUXR &= 0xF7;		//波特率不倍速
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	if(!bite)	BRT = 0x98;		//9600
	if(bite) BRT = 0xf7;		//115200
	AUXR |= 0x10;		//启动独立波特率发生器
	EA =1;	//开总中断
  IE2 =0x01;	//开串口2中断  ES2=1
}
void UART_SendOneByte(unsigned char c)
{
    S2BUF = c;
    while(!(S2CON&S2TI));  //若S2TI=0，在此等待
    S2CON&=~S2TI;	  //S2TI=0
}
/************串行口2中断处理函数*************/
void UART_Interrupt(void) interrupt 8
{
	if(S2CON&S2RI)
	{
		S2CON&=~S2RI;
		temp=S2BUF;
		UART_SendOneByte(temp);
	} 
}