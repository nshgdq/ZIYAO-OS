#include "ATCmd.h"
#include "app.h"
#include "ds1302.h"
#include "uart.h"
#include "18b20.h"
#include "led.h"
#include<string.h>
#define ATNUM 12		//AT指令的数量
//私有函数
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
AT指令的类型的结构体		
第一成员为指令串 (不超过10个字符，含\0)
第二成员为对应指令的函数名	
***************************/
typedef struct		 
{
	char at_name[10];
	void (*at_fun)();
}at_cmd;
at_cmd code at[ATNUM]=			//AT指令列表
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
函数名：AT_DO
作用：查阅AT指令串并执行对应函数
参数：at_str 串口接收到的AT指令串
********************************/
void AT_DO(u8 *at_str)
{
	u8 i;
	at_str=at_str+3;//清除指令头3个字符"AT+"
	for(i=0;i<=ATNUM;i++)
	{
		if(i==ATNUM) {ATErr();break;}
		if(strcmp(at_str,at[i].at_name)==0) {at[i].at_fun();break;}
	}
}
/***********************************
函数名：IsATCmd
作用:检查字符串是否AT指令(串开头三个字符是AT+)
返回值：1 是   0 不是
*************************************/
bit IsATCmd(u8 *str)
{
	if(*str=='A'&&*(str+1)=='T') return 1;
	return 0;
}
/*************************
函数名:stime
功能:获取当前时间并从串口
发送回上位机
**************************/
void stime()
{
	extern u8 time[22];
	gettime(time);
	UART_SendStr(time);
	UART_SendStr("\n");
}
/*************************
函数名:stempert
功能:获取当前温度并从串口
发送回上位机
**************************/
void stempert()
{
	u8 temper[7];
	ReadTemperature(temper);
	UART_SendStr(temper+1);
	UART_SendStr("\n");
}
/*************************
函数名:link
功能:检查串口连接，
已连接返回OK
**************************/
void link()
{
	UART_SendStr("OK\n");
}
/*************************
函数名:ATErr
功能:查AT表没有找到指令
报错！
**************************/
void ATErr()
{
	UART_SendStr("Not found!\n");
}
/*************************
函数名:LED
功能:改变LED状态
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