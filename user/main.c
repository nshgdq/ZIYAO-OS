/*********************************************************
8λ���ݽӿڵĲ�����HX8347D�������̣�
ʹ����������ֻ�����W25Qxx.c W25Qxx.h type_51.h�ļ�������ӦIO�ڼ���
**********************************************************/

#include "stc12c5a60s2.h"
#include "w25qxx.h" 
#include "type_51.h"
#include "Touch.h"
#include "ds1302.h"
#include <string.h>
#include "timer.h"
#include "GUI.h"
#include "18b20.h"
#include "usart.h"
//��������



void main()
{
//	u8 code setime[7]={0x04,0x08,0x23,0x01,0x06,0x01,0x15};
	LCD_Initializtion();	
	font_init();		//�ֿ��ʼ��
	TP_Init();
	Ds1302_Init();
	Timer0Init();
	InitUART(0);
//	Ds1302_Write_Time(setime);//�趨ϵͳʱ��
	start_check();
	start_logo();
//	while(1)
//	{
//		
//	}
	
	desktop();
}




