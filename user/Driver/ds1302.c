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
	buf[0]='2'; //年
	buf[1]='0';
	buf[2]=(temp[6]>>4)+'0';
	buf[3]=(temp[6]&0x0f)+'0';
	buf[4]='/';
	buf[5]=(temp[4]>>4)+'0';//月
	buf[6]=(temp[4]&0x0f)+'0';
	buf[7]='/';
	buf[8]=(temp[3]>>4)+'0';//日
	buf[9]=(temp[3]&0x0f)+'0';
	buf[10]='/';
	buf[11]=(temp[2]>>4)+'0';//时
	buf[12]=(temp[2]&0x0f)+'0';
	buf[13]=':';
	buf[14]=(temp[1]>>4)+'0';//分
	buf[15]=(temp[1]&0x0f)+'0';
	buf[16]=':';
	buf[17]=(temp[0]>>4)+'0';//秒
	buf[18]=(temp[0]&0x0f)+'0';
	buf[19]='/';
	buf[20]=(temp[5]&0x0f)+'0';//周
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
往DS1302的某个地址写入数据
**************************************/
void Write1302 (unsigned char addr,unsigned char dat)
      { 
       unsigned char i,temp; 
       CE=0; 				//CE 引脚为低， 数据传送中止 
				Delay1ms();
       SCLK=0;                       //清零时钟总线 
				Delay1ms();
       CE = 1;                       //CE 引脚为高，逻辑控制有效 
	Delay1ms();                  //后加的
       for ( i=8; i>0; i-- )         //循环8次移位发送地址  
       {      
              SCLK = 0; 				  //sclk上升沿触发
							Delay1ms();
              temp = addr; 
              DIO = (bit)(temp&0x01);    //每次传输低字节 
							Delay1ms();
              addr >>= 1;                //右移一位 
			  Delay1ms();				 //后加的
              SCLK = 1; 
			 Delay1ms();				 //后加的
       } 
//发送数据 
       for ( i=8; i>0; i-- ) 
       {      
              SCLK = 0; 
							Delay1ms();
              temp = dat; 
              DIO = (bit)(temp&0x01);  
							Delay1ms();		         
              dat >>= 1;                    
			  Delay1ms();				 //后加的
              SCLK = 1; 
			  Delay1ms();				 //后加的
       } 
              CE = 0;          
			  } 
   									
/**************************************
读DS1302某地址的的数据
**************************************/
unsigned char Read1302 ( unsigned char addr ) 
{ 
       unsigned char i,temp; 	//	,dat1,dat2
       CE=0;  
				Delay1ms();
       SCLK=0; 
				Delay1ms();
       CE = 1;   
			  Delay1ms();				 //后加的
       //发送地址 
	for ( i=8; i>0; i-- )             //循环8次移位 
       {      
              SCLK = 0; 
							Delay1ms();
//              temp = addr; 
              DIO = (bit)(addr&0x01);    //每次传输低字节 
							Delay1ms();
              addr >>= 1;                //右移一位 
			  Delay1ms();				 //后加的
              SCLK = 1; 				 //发送地址时SCLK上升沿触发
			  Delay1ms();				 //后加的
       } 
       //读取数据 								 
       for ( i=8; i>0; i-- ) 
       { 
              SCLK = 1; 
				 Delay1ms();
		temp = temp >> 1;
			  Delay1ms();				 //后加的
              SCLK = 0; 			     //读取数据时SCLK下降沿触发
			  Delay1ms();				 //后加的
		if (DIO){temp |= 0x80;}   else{temp &= 0x7F;}
       }      
       CE=0; 
			 Delay1ms();
       return (temp); 
} 
/**************************************
           写入初始时间
**************************************/
void Ds1302_Write_Time(unsigned char *buf)   
{
	Write1302(0x8e,0x00);			//关闭写保护 
	delay40us();
	Write1302(0x80,buf[0]); //秒
	delay40us();
	Write1302(0x82,buf[1]);//分
	delay40us();
	Write1302(0x84,buf[2]);//时
	delay40us();
	Write1302(0x86,buf[3]);//日
	delay40us();
	Write1302(0x88,buf[4]);//月
	delay40us();
	Write1302(0x8a,buf[5]);//周
	delay40us();
	Write1302(0x8c,buf[6]);//年
	delay40us();
	Write1302(0x8e,0x80);			//打开写保护 
	
}

/**************************************
           读取当前时间
**************************************/
void Ds1302_Read_Time(unsigned char *buf)		
{ 
	Read1302(0x00);
	delay40us();
	buf[6]=Read1302(0x8d);//年
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[5]=Read1302(0x8b);//周
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[4]=Read1302(0x89);//月
	Read1302(0x00);
	delay40us();
	buf[3]=Read1302(0x87);//日
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[2]=Read1302(0x85);//时
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[1]=Read1302(0x83);//分
	delay40us();
	Read1302(0x00);
	delay40us();
	buf[0]=Read1302(0x81);//秒
}

/**************************************
初始化DS1302
**************************************/
void Ds1302_Init(void)
{
    CE = 0;
    SCLK = 0;
    Write1302 (0x8e,0X00);        //禁止写保护 
//    Write1302 (ds1302_charger_add, 0xab);   //一个二极管＋4K电阻充电
    Write1302 (0x8e,0x80);        //允许写保护 
}