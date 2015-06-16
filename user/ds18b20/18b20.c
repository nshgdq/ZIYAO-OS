/*-----------------------------------------------
功能：18B20单线温度传感器在1602液晶显示
------------------------------------------------*/
#include"18b20.h"
#include<stdio.h>
#include<string.h>
/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)//@32MHz
{
	unsigned char i;	
	for(t=t*2+5;t>0;t--)
	{
		i = 5;
		while (--i);
	}
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
 unsigned char i, j;
	for(t=t;t>0;t--)
	{
		_nop_();
		_nop_();
		i = 32;
		j = 28;
		do
		{
			while (--j);
		} while (--i);
	}
}

/*------------------------------------------------
                    18b20初始化
------------------------------------------------*/
bit Init_DS18B20(void)
{
 bit dat=0;
 DQ = 1;    //DQ复位
 DelayUs2x(5);   //稍做延时
 DQ = 0;         //单片机将DQ拉低
 DelayUs2x(200); //精确延时 大于 480us 小于960us
 DelayUs2x(200);
 DQ = 1;        //拉高总线
 DelayUs2x(50); //15~60us 后 接收60-240us的存在脉冲
 dat=DQ;        //如果x=0则初始化成功, x=1则初始化失败
 DelayUs2x(25); //稍作延时返回
 return dat;
}

/*------------------------------------------------
                    读取一个字节
------------------------------------------------*/
unsigned char ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
 {
  DQ = 0; // 给脉冲信号
  dat>>=1;
  DQ = 1; // 给脉冲信号
  if(DQ)
   dat|=0x80;
  DelayUs2x(25);
 }
 return(dat);
}
/*------------------------------------------------
                    写入一个字节
------------------------------------------------*/
void WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ = 0;
  DQ = dat&0x01;
  DelayUs2x(25);
  DQ = 1;
  dat>>=1;
 }
DelayUs2x(25);
}

/*------------------------------------------------
                    读取温度
------------------------------------------------*/
unsigned int Read18b20(void)
{
unsigned char a=0;
unsigned int b=0;
unsigned int t=0;
Init_DS18B20();
WriteOneChar(0xCC); // 跳过读序号列号的操作
WriteOneChar(0x44); // 启动温度转换
DelayMs(10);
Init_DS18B20();
WriteOneChar(0xCC); //跳过读序号列号的操作 
WriteOneChar(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
a=ReadOneChar();   //低位
b=ReadOneChar();   //高位
b<<=8;
t=a+b;

return(t);
}
void ReadTemperature(uchar *temper)
{
	unsigned int temp;
	float temperature;
	temp=Read18b20();
	temperature=(float)temp*0.0625;
	sprintf(temper,"%7.3f",temperature);//打印温度值
}