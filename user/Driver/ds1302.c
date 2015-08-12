#include "INTRINS.H"
#include "ds1302.h"
void Delay1ms()		//@32MHz
{
	unsigned char i, j;

	i = 32;
	j = 29;
	do
	{
		while (--j);
	} while (--i);
}

void gettime(u8 *buf)
{
	u8 temp[7];
	Ds1302_Read_Time(temp);
	buf[0]='2'; //��
	buf[1]='0';
	buf[2]=(temp[6]>>4)+'0';
	buf[3]=(temp[6]&0x0f)+'0';
	buf[4]='/';
	buf[5]=(temp[4]>>4)+'0';//��
	buf[6]=(temp[4]&0x0f)+'0';
	buf[7]='/';
	buf[8]=(temp[3]>>4)+'0';//��
	buf[9]=(temp[3]&0x0f)+'0';
	buf[10]='/';
	buf[11]=(temp[2]>>4)+'0';//ʱ
	buf[12]=(temp[2]&0x0f)+'0';
	buf[13]=':';
	buf[14]=(temp[1]>>4)+'0';//��
	buf[15]=(temp[1]&0x0f)+'0';
	buf[16]=':';
	buf[17]=(temp[0]>>4)+'0';//��
	buf[18]=(temp[0]&0x0f)+'0';
	buf[19]='/';
	buf[20]=(temp[5]&0x0f)+'0';//��
	buf[21]='\0';
}
void delay40us()		//@32MHz
{
	unsigned char i, j;

	i = 2;
	j = 59;
	do
	{
		while (--j);
	} while (--i);
}
/**************************************
��DS1302��ĳ����ַд������
**************************************/
void Write1302 (unsigned char addr,unsigned char dat)
      { 
       unsigned char i,temp; 
       CE=0; 				//CE ����Ϊ�ͣ� ���ݴ�����ֹ 
				Delay1ms();
       SCLK=0;                       //����ʱ������ 
				Delay1ms();
       CE = 1;                       //CE ����Ϊ�ߣ��߼�������Ч 
	Delay1ms();                  //��ӵ�
       for ( i=8; i>0; i-- )         //ѭ��8����λ���͵�ַ  
       {      
              SCLK = 0; 				  //sclk�����ش���
							Delay1ms();
              temp = addr; 
              DIO = (bit)(temp&0x01);    //ÿ�δ�����ֽ� 
							Delay1ms();
              addr >>= 1;                //����һλ 
			  Delay1ms();				 //��ӵ�
              SCLK = 1; 
			 Delay1ms();				 //��ӵ�
       } 
//�������� 
       for ( i=8; i>0; i-- ) 
       {      
              SCLK = 0; 
							Delay1ms();
              temp = dat; 
              DIO = (bit)(temp&0x01);  
							Delay1ms();		         
              dat >>= 1;                    
			  Delay1ms();				 //��ӵ�
              SCLK = 1; 
			  Delay1ms();				 //��ӵ�
       } 
              CE = 0;          
			  } 
   									
/**************************************
��DS1302ĳ��ַ�ĵ�����
**************************************/
unsigned char Read1302 ( unsigned char addr ) 
{ 
       unsigned char i,temp; 	//	,dat1,dat2
       CE=0;  
				Delay1ms();
       SCLK=0; 
				Delay1ms();
       CE = 1;   
			  Delay1ms();				 //��ӵ�
       //���͵�ַ 
	for ( i=8; i>0; i-- )             //ѭ��8����λ 
       {      
              SCLK = 0; 
							Delay1ms();
//              temp = addr; 
              DIO = (bit)(addr&0x01);    //ÿ�δ�����ֽ� 
							Delay1ms();
              addr >>= 1;                //����һλ 
			  Delay1ms();				 //��ӵ�
              SCLK = 1; 				 //���͵�ַʱSCLK�����ش���
			  Delay1ms();				 //��ӵ�
       } 
       //��ȡ���� 								 
       for ( i=8; i>0; i-- ) 
       { 
              SCLK = 1; 
				 Delay1ms();
		temp = temp >> 1;
			  Delay1ms();				 //��ӵ�
              SCLK = 0; 			     //��ȡ����ʱSCLK�½��ش���
			  Delay1ms();				 //��ӵ�
		if (DIO){temp |= 0x80;}   else{temp &= 0x7F;}
       }      
       CE=0; 
			 Delay1ms();
       return (temp); 
} 
/**************************************
           д���ʼʱ��
**************************************/
void Ds1302_Write_Time(unsigned char *buf)   
{
	Write1302(0x8e,0x00);			//�ر�д���� 
	delay40us();
	Write1302(0x80,buf[0]); //��
	delay40us();
	Write1302(0x82,buf[1]);//��
	delay40us();
	Write1302(0x84,buf[2]);//ʱ
	delay40us();
	Write1302(0x86,buf[3]);//��
	delay40us();
	Write1302(0x88,buf[4]);//��
	delay40us();
	Write1302(0x8a,buf[5]);//��
	delay40us();
	Write1302(0x8c,buf[6]);//��
	delay40us();
	Write1302(0x8e,0x80);			//��д���� 
	
}

/**************************************
           ��ȡ��ǰʱ��
**************************************/
void Ds1302_Read_Time(unsigned char *buf)		
{ 
	Read1302(0x00);
	delay40us();
	buf[6]=Read1302(0x8d);//��
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[5]=Read1302(0x8b);//��
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[4]=Read1302(0x89);//��
	Read1302(0x00);
	delay40us();
	buf[3]=Read1302(0x87);//��
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[2]=Read1302(0x85);//ʱ
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[1]=Read1302(0x83);//��
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[0]=Read1302(0x81);//��
}

/**************************************
��ʼ��DS1302
**************************************/
void Ds1302_Init(void)
{
    CE = 0;
    SCLK = 0;
    Write1302 (0x8e,0X00);        //��ֹд���� 
//    Write1302 (ds1302_charger_add, 0xab);   //һ�������ܣ�4K������
    Write1302 (0x8e,0x80);        //����д���� 
}