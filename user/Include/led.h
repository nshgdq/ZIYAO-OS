#ifndef _LED_H
#define _LED_H
#include "type_51.h"
//********************
sbit LED1=P0^5;
sbit LED2=P0^6;
sbit LED3=P0^7;
//********************
#define ON 0
#define OFF 1
//********************
void InitLed();
void SetLed(u8 led,bit stat);
bit RedLed(u8 led);
//*********************
#endif