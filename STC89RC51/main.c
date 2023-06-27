#include "reg52.h"
#include "key.h"
#include "lcd.h"
#include "dt.h"
#include "motor.h"

sbit heater=P3^7;//控制加热器的开关接口开关

void main()
{
	lcd_init();  //初始化lcd屏幕
	write_string(0,0,"Ture:         ");//打印第一行
	write_string(0,1,"Set :		     	");//打印第二行

	while(1)
	{
		shows(Read_Data_From_DHT());//读取并显示DS18B20检测到的温度
		key();//按键状态检测
		if(T>set_t)//检测实时温度是否高于设置温度
		{
			if(T-set_t>2)//检测设置温度是否高于实时温度2
			{
				warning(1);//警报响起
			}
			motor_start();//启动风扇
		}
		else
		{
			motor_stop();//停止风扇
		}
		if(T<set_t)//检测实时温度是否 低于设置温度
		{
			if(set_t-T>2)//检测设置温度是否低于实时温度2
			{
				warning(2);//警报响起
			}
			heater=1;//开启加热器
		}
		else
		{
			heater=0;//关闭加热器
		}
	}
}




	
	