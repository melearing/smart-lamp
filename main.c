#include <reg52.h>
#include <string.h>
#include "header.h"
#include <stdlib.h>
#include "ucharuint.h"

sbit LED0=P1^0;
sbit LED1=P2^1;
sbit LED2=P2^2;
sbit LED3=P2^3;
sbit LED4=P1^4;
sbit LED5=P1^5;
sbit LED6=P1^6;
sbit LED7=P1^7;

uchar Recive_table[40]="";  //接收缓冲,最大20个字节
char Recive_state = 0;   //接收完成标志
char Op=0;
unsigned char PWM[3]="";//光度信号
unsigned char ssid[18]="";//WIFIssid号
unsigned char pwd[18]="";//WIFI密码,
char RT_state =0;
uchar sb[1];
uchar *str1,*str2;

unsigned char toASCII(unsigned char a)
{
    if(a<=9)
    {
        return a+0x30;
    }
    else 
    {
        return a+0x41;
    }
}

void empty(char arr[],int len)//清空数组
{
    int i=0;
    for(i=0;i<len;i++)
    {
        arr[i]='\0';
    }  
}

void Send_Uart(uchar value)
{
      ES=0;         //关闭串口中断
      TI=0;         //清发送完毕中断请求标志位
      SBUF=value;     //发送
      while(TI==0);   //等待发送完毕
      TI=0;         //清发送完毕中断请求标志位
      ES=1;         //允许串口中断
}

void ESP8266_Set(uchar *puf) // 数组指针*puf指向字符串数组               
{

      while(*puf!='\0')    //遇到空格跳出循环
      {
           Send_Uart(*puf);  //向WIFI模块发送控制指令。
           us_delay(5);
           puf++;      
      }
      us_delay(5);
      Send_Uart('\r');//回车
      us_delay(5);
      Send_Uart('\n');   //换行
      ms_delay(1000);
}

void ESP8266_Sent(uchar *puf,uchar i)      // 数组指针*puf指向字符串数组               
{
			uchar send[20]="";
			send[0]='A';send[1]='T';send[2]='+';send[3]='C';send[4]='I';send[5]='P';
			send[6]='S';send[7]='E';send[8]='N';send[9]='D';send[10]='=';send[12]=',';
			send[11]=sb[0];
			send[13]=toASCII(i/10);	
			send[14]=toASCII(i%10);	
			ESP8266_Set(send);
 
      while(*puf!='\0')    //遇到空格跳出循环
      {
           Send_Uart(*puf);   //向WIFI模块发送控制指令。
           us_delay(5);
           puf++;      
      }
      us_delay(5);
      Send_Uart('\n');   //换行
      ms_delay(10);
}   


/******************************************************************
函 数: void WIFI_Init(void)
功 能: wifi初始化(名字：esp8266；密码：1234567890)
参 数: 无
返回值: 无
*******************************************************************/
void WIFI_Init(void)
{
ES = 0;
TI = 1;  

ESP8266_Set("AT+RST");//重启
//LED();
	
ESP8266_Set("AT+CWMODE=2");//
//LED();
	
ESP8266_Set("AT+CIPMUX=1");//多连接模式
//LED(); 

ESP8266_Set("AT+CIPSERVER=1,8080");//服务器端口8080
//LED();

//while(!TI);
//TI = 0;
ES = 1;
}
 
int main (void)
{ 
	unsigned int CYCLE=600,PWM_LOW=0;//定义周期并赋值
//	unsigned int top=600,p=5;
/********************功能初始化***********************/
  Uart_Init();
//串口初始化，波特率为9600
	ms_delay(1000) ;
  WIFI_Init(); //wifi初始化
/****************************************************/

/**********************主循环************************/

for(;;)
{ 
	int WZ_state= 9;
	ms_delay(1000);
//	P=(int)PWM;
	
//	LED0=0;        //点亮LED 	
//	Delay(p);//延时长度，600次循环中从1加至599
//	LED0=1;        //熄灭LED
////	p=atoi(PWM);
////ESP8266_Set(PWM);
//	Delay(top - p);//延时长度，600次循环中从599减至1
			
//			LED0=1;
// Delay(60000);        //特意加延时，可以看到熄灭的过程
// for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++){ //PWM_LOW表示低
// //电平时间，这个循环中低电平时长从1累加到CYCLE（周期）的值，即600次

   		LED0=0;        //点亮LED  
   		Delay(PWM_LOW);//延时长度，600次循环中从1加至599
   		LED0=1;        //熄灭LED
  	    Delay(CYCLE-PWM_LOW);//延时长度，600次循环中从599减至1
//     
//   }
// LED0=0;
// for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--){ //与逐渐变亮相反的过程

//   		LED0=0;
//   		Delay(PWM_LOW);
//   		LED0=1;
//  	    Delay(CYCLE-PWM_LOW);
//     
//   }
//                     //主循环中添加其他需要一直工作的程序
	
  
		
                                                  

	if(Recive_state == 1)
		{ LED1=0;//实验
			ES=0;  //清空接收标志位 
			if((Recive_table[0]=='+')&&(Recive_table[1]=='I')&&(Recive_table[2]=='P'))
//接收到的字符串形式为+IPD,x,x:y
				{
					if((Recive_table[3]=='D')&&(Recive_table[6]==','))
						{   
							sb[0]=Recive_table[5];
							if(Recive_table[9]==':')
								WZ_state=10;
							
							if(Recive_table[WZ_state]=='0')
								{
									ESP8266_Sent("Reboot soon",11);
									WIFI_Init();
								}
							else if(Recive_table[WZ_state]=='1')
								{   //LED2=0;//实验
									LED1 = 0;
									//PWM_LOW=1;
									//empty(Recive_table,40);//修改1，清空--无效
									
									ESP8266_Sent("OPEN",4);
//									ESP8266_Sent("OPPEN_1",7);
								}
							else if(Recive_table[WZ_state]=='2')
								{
									LED1 = 1;
									//ESP8266_Sent("CLOSE_1",7);
								  //PWM_LOW=100;
									ESP8266_Sent("CLOSE",5);
									//PWM_LOW=100;
								}
							else if(Recive_table[WZ_state]=='3')
								{
									//LED5 = 0;
									//ESP8266_Sent("OPPEN_2",7);
									PWM_LOW=300;
									ESP8266_Sent("OK_3",4);
								}
							else if(Recive_table[WZ_state]=='4')
								{
									//LED5 = 1;
									//ESP8266_Sent("CLOSE_2",7);
								PWM_LOW=400;
									ESP8266_Sent("OK_4",4);
									
									
								}
//							else if(Recive_table[WZ_state]=='6')
//								{
//									//LED6 = 0;
//									//ESP8266_Sent("OPPEN_3",7);
//									PWM_LOW=599;
//									ESP8266_Sent("OK_2",5);
//									
//								}
//							else if(Recive_table[WZ_state]=='6')
//								{
//									LED1 = 1;
//									//ESP8266_Sent("CLOSE",5);
//									//PWM_LOW=0;
//									ESP8266_Sent("CLOSE",5);
//									
//								}
							
//								else if((Recive_table[WZ_state]=='4')&&(Recive_table[WZ_state+1]=='1'))
//								{
//									//LED7 = 0;
//									//ESP8266_Sent("OPPEN_4",7);
//									ESP8266_Sent("OK",2);
//									PWM_LOW=600;
//								}
//							else if((Recive_table[WZ_state]=='4')&&(Recive_table[WZ_state+1]=='0'))
//								{
//									//LED7 = 1;
//									//ESP8266_Sent("CLOSE_4",7);
//									ESP8266_Sent("RECOVER",7);
//									PWM_LOW=500;
//								}

//							else if(Recive_table[WZ_state]=='5')
//								{ LED3=0;//实验
//									int ss=WZ_state+1;
//									empty(PWM,3);		
//									if(Recive_table[WZ_state+1]=='+')							//检测开始标志位"+"
//									{
//											while(Recive_table[++ss]!='+')						//检测ssid读取结束标志位
//											{
//												PWM[ss-(WZ_state+2)]=Recive_table[ss];	//把ssid装进ssid[]数组
//											}											
//											PWM_LOW[0]=(PWM[0]-0x30)*100+(PWM[1]-0x30)*10+(PWM[2]-0x30);											
//											ESP8266_Sent("OK",2);
//									}else
//									ESP8266_Sent("5+PWM+",6);								//返回提示格式信息		
//						  	}								
								else if(Recive_table[WZ_state]=='5')						//6+ssid+pwd+
								{
									uchar index = 9;
									int ss=WZ_state+1,pp=0;
									empty(ssid,18);																//清空数组
									empty(pwd,18);																//清空数组
									if(Recive_table[WZ_state+1]=='+')							//检测开始标志位"+"
									{
											while(Recive_table[++ss]!='+')						//检测ssid读取结束标志位
											{
												ssid[ss-(WZ_state+2)]=Recive_table[ss];	//把ssid装进ssid[]数组
											}													
											str1=ssid;
											pp=ss;
											while(Recive_table[++ss]!='+')						//检测pwd读取结束标志位
											{
												pwd[ss-(pp+1)]=Recive_table[ss];				//把密码装进pwd[]数组
											}
											str2=pwd;										
											ESP8266_Set("AT+CWMODE=1");								//发送改变到Station模式命令
											empty(Recive_table,40);										//清空数组
																																//把AT+CWJAP="装进数组
											Recive_table[0]='A';Recive_table[1]='T';Recive_table[2]='+';
											Recive_table[3]='C';Recive_table[4]='W';Recive_table[5]='J';
											Recive_table[6]='A';Recive_table[7]='P';Recive_table[8]='=';Recive_table[9]='\"';
											while(*str1 != '\0')											//把ssid装进数组
											{
												Recive_table[++index] = *str1;
												str1++;		
											}
											Recive_table[++index] ='\"';
											Recive_table[++index] =',';
											Recive_table[++index] ='\"';
												while(*str2 != '\0')										//把pwd装进数组
											{
												Recive_table[++index] = *str2;
												str2++;		
											}
											Recive_table[++index] ='\"';
											ESP8266_Set(Recive_table);								//把拼接好的命令数组发送出去
									}else
									ESP8266_Sent("6+ssid+pwd+",11);								//返回提示格式信息			
								}
							else if(Recive_table[WZ_state]=='8')
								{
									LED4 = LED5 =LED6 =LED7 =1;
									ESP8266_Sent("CLOSE_ALL",9);
								}
							else if(Recive_table[WZ_state]=='9')
								{
									LED4 = LED5 =LED6 =LED7 =0;
									ESP8266_Sent("OPPEN_ALL",9);
								}
							else 
								{
									ESP8266_Sent("ERROR",5);
								}
						}
				}
			empty(Recive_table,40);

			Recive_state = 0;
			ES=1;  //打开接收标志位
			/*LED4=0;
			 while(1);//实验*/
		}
	}
}


/******************************************************************
函 数: void Uart_Interrupt() interrupt 4
功 能: 串口中断函数,将收到的字符存到Recive_table[]数组中
参 数: 无
返回值: 无
*******************************************************************/


void Uart_Interrupt() interrupt 4         
{   	
	static char i=0; 
	ES = 0;
	RI=0;        
	Recive_table[i]=SBUF;        
	i++; 
	if((Recive_table[i-1] == '\n')||(i==39))
	{ 
		Recive_table[i]='\0';
		i=0; 
	}
	Recive_state = 1;
	ES = 1;       
} 
