#ifndef _uart_h
#define _uart_h
#include"stc12c5a60s2.h"
void InitUART(bit);
void UART_SendOneByte(unsigned char c);
void UART_SendStr(unsigned char *str);
extern bit flag;
#endif