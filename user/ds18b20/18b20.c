/*-----------------------------------------------
���ܣ�18B20�����¶ȴ�������1602Һ����ʾ
------------------------------------------------*/
#include"18b20.h"
#include<stdio.h>
#include<string.h>
/*------------------------------------------------
 uS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
 �������� T=tx2+5 uS 
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
 mS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
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
                    18b20��ʼ��
------------------------------------------------*/
bit Init_DS18B20(void)
{
 bit dat=0;
 DQ = 1;    //DQ��λ
 DelayUs2x(5);   //������ʱ
 DQ = 0;         //��Ƭ����DQ����
 DelayUs2x(200); //��ȷ��ʱ ���� 480us С��960us
 DelayUs2x(200);
 DQ = 1;        //��������
 DelayUs2x(50); //15~60us �� ����60-240us�Ĵ�������
 dat=DQ;        //���x=0���ʼ���ɹ�, x=1���ʼ��ʧ��
 DelayUs2x(25); //������ʱ����
 return dat;
}

/*------------------------------------------------
                    ��ȡһ���ֽ�
------------------------------------------------*/
unsigned char ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
 {
  DQ = 0; // �������ź�
  dat>>=1;
  DQ = 1; // �������ź�
  if(DQ)
   dat|=0x80;
  DelayUs2x(25);
 }
 return(dat);
}
/*------------------------------------------------
                    д��һ���ֽ�
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
                    ��ȡ�¶�
------------------------------------------------*/
unsigned int Read18b20(void)
{
unsigned char a=0;
unsigned int b=0;
unsigned int t=0;
Init_DS18B20();
WriteOneChar(0xCC); // ����������кŵĲ���
WriteOneChar(0x44); // �����¶�ת��
DelayMs(10);
Init_DS18B20();
WriteOneChar(0xCC); //����������кŵĲ��� 
WriteOneChar(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
a=ReadOneChar();   //��λ
b=ReadOneChar();   //��λ
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
	sprintf(temper,"%7.3f",temperature);//��ӡ�¶�ֵ
}