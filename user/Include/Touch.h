﻿#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "type_51.h"
#include "hx8347d.h"

#define TP_PRES_DOWN 0x80  //触屏被按下	  
#define TP_CATH_PRES 0x40  //有按键按下了 	  

extern void delay_ms(u16 ms);

//触摸屏控制器
typedef struct
{
	u8 (*init)(void);			//初始化触摸屏控制器
	u8 (*scan)(u8);				//扫描触摸屏.0,屏幕扫描;1,物理坐标;	 
	void (*adjust)(void);		//触摸屏校准
	u16 x0;						//原始坐标(第一次按下时的坐标)
	u16 y0;
	u16 x; 						//当前坐标(此次扫描时,触屏的坐标)
	u16 y;						   	    
	u8  sta;					//笔的状态 
								//b7:按下1/松开0; 
	                            //b6:0,没有按键按下;1,有按键按下.         			  
////////////////////////触摸屏校准参数/////////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
//touchtype=0的时候,适合左右为X坐标,上下为Y坐标的TP.
//touchtype=1的时候,适合左右为Y坐标,上下为X坐标的TP.
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//触屏控制器在touch.c里面定义

//与触摸屏芯片连接引脚	   

sbit  DOUT =	P0^3;  //  MISO   
sbit  TDIN =	P0^2;  //  MOSI
sbit  TCLK =	P0^1;  //  SCLK
sbit  PEN  =	P2^5;  //  INT
sbit  TCS  =	P2^6;  //  CS 
 

void TP_Write_Byte(u8 num);						//向控制芯片写入一个数据
u16 TP_Read_AD(u8 CMD);							//读取AD转换值
u16 TP_Read_XOY(u8 xy);							//带滤波的坐标读取(X/Y)
u8 TP_Read_XY(u16 *x,u16 *y);					//双方向读取(X+Y)
u8 TP_Read_XY2(u16 *x,u16 *y);					//带加强滤波的双方向坐标读取
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//画一个坐标校准点
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);	//画一个大点
u8 TP_Scan(u8 tp);								//扫描
void TP_Adjust(void);							//触摸屏校准
u8 TP_Init(void);								//初始化
void TP_Default_Adj(void);
																 		  
#endif

















