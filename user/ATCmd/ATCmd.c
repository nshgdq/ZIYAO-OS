#include "ATCmd.h"
#include "gui.h"
#include<string.h>
#define ATNUM 5		//AT指令的数量
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
	{"desktop",desktop},
	{"startch",start_check},
	{"picbox",picbox},
	{"tempert",tempert},
	{"calendar",calendar}
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
	for(i=0;i<ATNUM;i++)
	{
		if(strcmp(at_str,at[i].at_name)==0) at[i].at_fun();
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