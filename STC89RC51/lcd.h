#ifndef __LCD_H__
#define __LCD_H__

#include "delay.h"
#include "intrins.h"


sbit RS=P2^0;       //RS引脚
sbit RW=P2^1;       //R/W引脚
sbit EN=P2^2;       //E引脚

void write_com(uchar com);   	//写指令函数
void write_data(uchar dat);  	//写数据函数
void lcd_init(void );        	//LCD初始化函数
void write_string(uchar x,uchar y,uchar *s);//显示字符串,x为列位置，y为行位置

void write_com(uchar com)//写指令函数
{
    RS=0;       //写入指令
    RW=0;       //允许写入
    P0=com;
    EN=1;
    _nop_();
    EN=0;
    delay_ms(5);
}

void write_data(uchar dat)//写数据函数
{
    RS=1;       	 //写入数据      
    RW=0;					//允许写入
    P0=dat;
    EN=1;
    _nop_();
    EN=0;
    delay_ms(5);
}

void lcd_init()//LCD初始化函数
{
    write_com(0x38);    //8位数据总线，2行显示，5*7点阵
    write_com(0x0c);    //显示开，光标关，闪烁关
    write_com(0x06);    //光标右移，字符不移动
}
	
void write_string(uchar x,uchar y,uchar *s)	//显示字符串,x为列位置，y为行位置
{
	if(y==0)
		write_com(0x80+x);//第一行显示
	else
		write_com(0xc0+x);//第二行显示
	while(*s)//循环至写完字符串
	{
		write_data(*s);//一个一个写入字符
		s++;//写下一个字符
	}
}

#endif