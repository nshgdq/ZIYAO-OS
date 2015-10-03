#ifndef _APP_H
#define _APP_H
#include "stc12c5a60s2.h"
#include "type_51.h"
void delay_ms(u16 ms);
void start_check();
void start_logo();
void desktop();
void Get_Click(u16 *x,u16 *y);
void alert(char *s,u16 bcolor);
void clock();
void calendar();
void guidshow();
void guiddo(void (*pback)(void),void (*pmenu)(void),x);
void tempert();
void sstmtime();
void picbox();
void led();
void SMsg();
#endif