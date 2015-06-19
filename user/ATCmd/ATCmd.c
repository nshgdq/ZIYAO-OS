#include "ATCmd.h"
#include "gui.h"
#include "ds1302.h"
#include "uart.h"
#include "18b20.h"
#include<string.h>
#define ATNUM 7		//ATָ�������
//˽�к���
void stime();
void stempert();
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
	{"desktop",desktop},
	{"startch",start_check},
	{"picbox",picbox},
	{"tempert",tempert},
	{"calendar",calendar},
	{"stime",stime},
	{"stempert",stempert},
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
	for(i=0;i<ATNUM;i++)
	{
		if(strcmp(at_str,at[i].at_name)==0) at[i].at_fun();
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
���ܻ�ȡ��ǰʱ�䲢�Ӵ���
���ͻ���λ��
**************************/
void stime()
{
	extern u8 time[22];
	gettime(time);
	UART_SendStr(time);
}
/*************************
������:stempert
���ܻ�ȡ��ǰʱ�䲢�Ӵ���
���ͻ���λ��
**************************/
void stempert()
{
	u8 temper[7];
	ReadTemperature(temper);
	UART_SendStr(temper);
}