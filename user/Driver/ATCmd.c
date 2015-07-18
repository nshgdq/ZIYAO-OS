#include "ATCmd.h"
#include "gui.h"
#include "ds1302.h"
#include "uart.h"
#include "18b20.h"
#include "led.h"
#include<string.h>
#define ATNUM 12		//ATָ�������
//˽�к���
void stime();
void stempert();
void link();
void ATErr();
void SWLED1();
void SWLED2();
void SWLED3();
void OFFLed();
//******************
/**************************
ATָ������͵Ľṹ��		
��һ��ԱΪָ� (������10���ַ�����\0)
�ڶ���ԱΪ��Ӧָ��ĺ�����	
***************************/
typedef struct		 
{
	char at_name[10];
	void (*at_fun)();
}at_cmd;
at_cmd code at[ATNUM]=			//ATָ���б�
{
	{"link",link},
	{"desktop",desktop},
	{"startch",start_check},
	{"picbox",picbox},
	{"tempert",tempert},
	{"calendar",calendar},
	{"stime",stime},
	{"stempert",stempert},
	{"swled1",SWLED1},
	{"swled2",SWLED2},
	{"swled3",SWLED3},
	{"offled",OFFLed}
};
/******************************
��������AT_DO
���ã�����ATָ���ִ�ж�Ӧ����
������at_str ���ڽ��յ���ATָ�
********************************/
void AT_DO(u8 *at_str)
{
	u8 i;
	at_str=at_str+3;//���ָ��ͷ3���ַ�"AT+"
	for(i=0;i<=ATNUM;i++)
	{
		if(i==ATNUM) {ATErr();break;}
		if(strcmp(at_str,at[i].at_name)==0) {at[i].at_fun();break;}
	}
}
/***********************************
��������IsATCmd
����:����ַ����Ƿ�ATָ��(����ͷ�����ַ���AT+)
����ֵ��1 ��   0 ����
*************************************/
bit IsATCmd(u8 *str)
{
	if(*str=='A'&&*(str+1)=='T') return 1;
	return 0;
}
/*************************
������:stime
����:��ȡ��ǰʱ�䲢�Ӵ���
���ͻ���λ��
**************************/
void stime()
{
	extern u8 time[22];
	gettime(time);
	UART_SendStr(time);
	UART_SendStr("\n");
}
/*************************
������:stempert
����:��ȡ��ǰ�¶Ȳ��Ӵ���
���ͻ���λ��
**************************/
void stempert()
{
	u8 temper[7];
	ReadTemperature(temper);
	UART_SendStr(temper+1);
	UART_SendStr("\n");
}
/*************************
������:link
����:��鴮�����ӣ�
�����ӷ���OK
**************************/
void link()
{
	UART_SendStr("OK\n");
}
/*************************
������:ATErr
����:��AT��û���ҵ�ָ��
����
**************************/
void ATErr()
{
	UART_SendStr("Not found!\n");
}
/*************************
������:LED
����:�ı�LED״̬
*************************/
void SWLED1()
{
	SetLed(1,!RedLed(1));
}
void SWLED2()
{
	SetLed(2,!RedLed(2));
}
void SWLED3()
{
	SetLed(3,!RedLed(3));
}
void OFFLed()
{
	SetLed(1,1);
	SetLed(2,1);
	SetLed(3,1);
}