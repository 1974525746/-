#include <reg52.h>
#include "delay.h"
#include "intrins.h"
#include "math.h"
#include "lcd.h"

int T=0;				//实时温度
sbit DH= P3^4; 	// IO口连接DHT11

void DHT11_init();				//DHT11初始化启动函数
char Read_Data_From_DHT();//读取DHT11温度函数
void shows(char count); 	//将读取到的温度打印到屏幕上的函数
	
char datas[5];//用来记录从DHT11读出来的5个字节数据

void DHT11_init()//DHT11初始化启动函数
{
	DH = 1;
	DH = 0;
	delay_ms(30);//延时30ms
	DH = 1;
	while(DH);
	while(!DH);
	while(DH);
}


char Read_Data_From_DHT()//读取DHT11温度函数
{
	int i;//轮
	int j;//每一轮读多少次
	char tmp;
	char flag;
	DHT11_init();//DHT11初始化启动
	for(i= 0;i < 5;i++)
	{
		for(j=0;j<8;j++)
		{
			while(!DH);
			delay_us(15);//有效数据都是高电平，持续时间不一样
			if(DH == 1)
			{
				flag = 1;
				while(DH);
			}
			else
			{	
				flag = 0;
			} 
			tmp = tmp << 1;
			tmp |= flag;
		}
		datas[i] = tmp;
	}
	return datas[2];//所需要的温度整数位数据
}


void shows(char count) //将读取到的温度打印到屏幕上的函数
{
	  T=count;//记录实时温度
    
		datas[0]=count/10;//十位数
		datas[1]=count%10;//个位数
		
		write_com(0x80+6);//从第二行第6位开始写
		write_data(datas[0]+'0');//打印打屏幕上
		write_data(datas[1]+'0');//打印到屏幕上
    write_data(0xDF);	
		write_data('C');//打印摄氏度单位
}

