//#include <reg52.h>
//#include "ucharuint.h"

//sbit DS=P2^2;           //定义中总线
//uint temp;             // 温度变量
//void delay(uint count)      //delay
//{
//  uint i;
//  while(count)
//  {
//    i=200;
//    while(i>0)
//    i--;
//    count--;
//  }
//}


//void dsreset(void)       //发送复位和初始化
//{
//  uint i;
//  DS=0;		              
//  i=103;				   //将总线拉低480us~960us
//  while(i>0)i--;
//  DS=1;					   //然后拉高总线，若DS18B20做出反应会将在15us~60us后将总线拉低
//  i=4;					   //15us~60us等待
//  while(i>0)i--;
//  //while(DS);
//}

//bit tmpreadbit(void)       //读取一个位数据
//{
//   uint i;
//   bit dat;
//   DS=0;i++;          //i++ for delay
//   DS=1;i++;i++;
//   dat=DS;
//   i=8;while(i>0)i--;
//   return (dat);
//}

//uchar tmpread(void)   //读取一个字节数据
//{
//  uchar i,j,dat;
//  dat=0;
//  for(i=1;i<=8;i++)
//  {
//    j=tmpreadbit();
//    dat=(j<<7)|(dat>>1);   //读出的数据最低位在最前面，这样刚好一个字节在DAT里
//  }
//  return(dat);
//}

//void tmpwritebyte(uchar dat)   //写入一个字节数据
//{
//  uint i;
//  uchar j;
//  bit testb;
//  for(j=1;j<=8;j++)
//  {
//    testb=dat&0x01;
//    dat=dat>>1;
//    if(testb)     //write 1
//    {
//      DS=0;
//      i++;i++;
//      DS=1;
//      i=8;while(i>0)i--;
//    }
//    else
//    {
//      DS=0;       //write 0
//      i=8;while(i>0)i--;
//      DS=1;
//      i++;i++;
//    }

//  }
//}

//void tmpchange(void)  //18b20开始转换温度
//{
//  dsreset();
//  delay(1);
//  tmpwritebyte(0xcc);  // 跳过ROM指令
//  tmpwritebyte(0x44);  //  启动温度读取指令
//  //delay(100);
//}

//uint tmp()               //读取温度
//{
//  float tt;
//  uchar a,b;
//  dsreset();
//  delay(1);
//  tmpwritebyte(0xcc);
//  tmpwritebyte(0xbe);
//  a=tmpread();
//  b=tmpread();
//  temp=b;
//  temp<<=8;             //将高低温两个直接组成一个
//  temp=temp|a;
//  tt=temp*0.0625;
//  temp=tt*10+0.5;
//  return temp;
//}

