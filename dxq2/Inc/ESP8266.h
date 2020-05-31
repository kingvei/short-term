#ifndef  _ESP8266_H_
#define	 _ESP8266_H_

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif
/* 类型定义 ------------------------------------------------------------------*/
/******************************* ESP8266 数据类型定义 ***************************/
typedef enum{
	STA,
  AP,
  STA_AP  
} ENUM_Net_ModeTypeDef;

typedef enum{
	 enumTCP,
	 enumUDP,
} ENUM_NetPro_TypeDef;

typedef enum{
	Multiple_ID_0 = 0,
	Multiple_ID_1 = 1,
	Multiple_ID_2 = 2,
	Multiple_ID_3 = 3,
	Multiple_ID_4 = 4,
	Single_ID_0 = 5,
} ENUM_ID_NO_TypeDef;
	
typedef enum{
	OPEN = 0,
	WEP = 1,
	WPA_PSK = 2,
	WPA2_PSK = 3,
	WPA_WPA2_PSK = 4,
} ENUM_AP_PsdMode_TypeDef;

#define RX_BUF_MAX_LEN    256                                     //最大接收缓存字节数

typedef struct                                    //串口数据帧的处理结构体
{
	char  Data_RX_BUF [ RX_BUF_MAX_LEN ];

    __IO uint16_t InfAll;
		  __IO uint16_t FramLength       :15;                               // 14:0 
     	
}STRUCT_USARTx_Fram;

/* 宏定义 --------------------------------------------------------------------*/

/******************************** ESP8266 连接引脚定义 ***********************************/
             
/*********************************************** ESP8266 函数宏定义 *******************************************/
#define ESP8266_Usart( fmt, ... )                      USART_printf (ESP8266_USARTx, fmt, ##__VA_ARGS__ ) 
#define PC_Usart( fmt, ... )                           printf ( fmt, ##__VA_ARGS__ )
//#define PC_Usart( fmt, ... )                



/* 扩展变量 ------------------------------------------------------------------*/
extern UART_HandleTypeDef husartx_esp8266;
extern STRUCT_USARTx_Fram strEsp8266_Fram_Record;
extern uint8_t esp8266_rxdata;
extern char Esp8266IPAddress[30];  // 模块IP地址
extern char Esp8266SSID[30];       // 模块SSID
extern char Esp8266PWD[30];           //模块热点的密钥

extern char User_ESP8266_ApSsid[30];  //要连接的热点的名称
extern char User_ESP8266_ApPwd[30];   //要连接的热点的密钥
extern char User_ESP8266_TcpServer_IP[4];    //要连接的服务器的 IP
extern char User_ESP8266_TcpServer_Port[10];  //要连接的服务器的端口

/* 函数声明 ------------------------------------------------------------------*/
void  ESP8266_Init( void );
void  ESP8266_stop( void );
void  ESP8266_Rst( void );
bool  ESP8266_Cmd( char * cmd, char * reply1, char * reply2, uint32_t waittime );
bool  ESP8266_AT_Test( void );
bool  ESP8266_Net_Mode_Choose( ENUM_Net_ModeTypeDef enumMode );
bool  ESP8266_JoinAP( char * pSSID, char * pPassWord );
bool  ESP8266_BuildAP( char * pSSID, char * pPassWord, ENUM_AP_PsdMode_TypeDef enunPsdMode );
bool  ESP8266_Enable_MultipleId( FunctionalState enumEnUnvarnishTx );
bool  ESP8266_Link_Server( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id);
bool  ESP8266_StartOrShutServer( FunctionalState enumMode, char * pPortNum, char * pTimeOver );
uint8_t ESP8266_Get_LinkStatus( void );
uint8_t ESP8266_Get_IdLinkStatus( void );
uint8_t ESP8266_Inquire_ApIp( char * pApIp, uint8_t ucArrayLength );
uint8_t ESP8266_Inquire_StaIp ( char * pStaIp, uint8_t ucArrayLength );
uint8_t ESP8266_Inquire_ApMac( char * pApMac, uint8_t ucArrayLength );
bool ESP8266_UnvarnishSend( void );
void ESP8266_ExitUnvarnishSend( void );
bool ESP8266_SendString( FunctionalState enumEnUnvarnishTx, char * pStr, uint32_t ulStrLength, ENUM_ID_NO_TypeDef ucId );
char * ESP8266_ReceiveString( FunctionalState enumEnUnvarnishTx );
uint8_t InitESP8266(void);
void  USART_printf(USART_TypeDef * USARTx, char * Data, ... );
int tcp_go(void);

#endif

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
