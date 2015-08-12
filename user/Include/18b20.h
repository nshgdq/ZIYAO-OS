#ifndef __DS18B20_H__
#define __DS18B20_H__

#include<stc12c5a60s2.h>     //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include<intrins.h>

#define uchar unsigned char
#define uint   unsigned int;
/*------------------------------------------------
                    �˿ڶ���
------------------------------------------------*/
sbit DQ=P0^0;//ds18b20 �˿�
/*------------------------------------------------
                  ��������
------------------------------------------------*/
void ReadTemperature(uchar *temper);
bit Init_DS18B20(void);
unsigned char ReadOneChar(void);
void WriteOneChar(unsigned char dat);
unsigned int Read18b20(void);
#endif
