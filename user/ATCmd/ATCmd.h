#ifndef _ATCmd_H
#define _ATCmd_H
#include "stc12c5a60s2.h"
#include "type_51.h"
bit IsATCmd(u8 *str);
void AT_DO(u8 *at_str);
#endif