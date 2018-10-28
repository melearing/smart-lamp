#ifndef __header_H__ 
#define __header_H__  
#include "ucharuint.h"

//wifi
extern ms_delay(int t);
extern us_delay(uchar t);
extern Delay(unsigned int t);
extern LED(void);
//extern WIFI_Init(void);
//temp
extern float tt;
extern uint temp;             // 温度变量
extern tmpchange(void);
extern uint tmp();           //读取温度

//usart
extern Uart_Init(void);
extern Send_ASCII(uchar *b);	//?????
#endif 