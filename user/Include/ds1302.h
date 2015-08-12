#ifndef _DS1302_H
#define _DS1302_H
#include <stc12c5a60s2.h>
#include "type_51.h"
//函数定义
void gettime(u8 *buf);
void Ds1302_Write_Time(unsigned char *buf);
void Ds1302_Read_Time(unsigned char *buf);
void Ds1302_Init(void);
void Delay1ms();
//接口定义
sbit CE=P2^7;
sbit SCLK=P0^1;
sbit DIO=P0^3;

#endif