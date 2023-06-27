#ifndef __KEY_H__
#define __KEY_H__

#include "delay.h"
#include "lcd.h"
#include "intrins.h"

sbit key_h=P1^0;//升温按键
sbit key_l=P1^1;//降温按键
sbit alarm=P1^2;//警报器

int set_t=26;//设置温度初始为26C

void key(void );//检测按键状况调节设置温度

void warning(uint a);//报警器函数

void key()//检测按键状况调节设置温度
{
	if(key_h==0)
	{
		while(key_h==0);//等待按键释放
		set_t++;//设定温度+1
	}
	if(key_l==0)
	{
		
		while(key_l==0);//等待按键释放
		set_t--;//设定温度-1
	}
	
	write_com(0xc0+6);//第二行开始写
	write_data(set_t%100/10+0x30);//屏幕输出十位数
	write_data(set_t%10+0x30);//输出个位数
	write_data(0xDF);	
	write_data('C');//摄氏度符号
}

void warning(uint a)//警报函数
{
	uchar i;
	for(i=0;i<100;i++)
	{
		alarm=~alarm;
		delay_ms(a);
	}
	alarm=0;
}

#endif