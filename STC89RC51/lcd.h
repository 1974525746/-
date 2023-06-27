#ifndef __LCD_H__
#define __LCD_H__

#include "delay.h"
#include "intrins.h"


sbit RS=P2^0;       //RS����
sbit RW=P2^1;       //R/W����
sbit EN=P2^2;       //E����

void write_com(uchar com);   	//дָ���
void write_data(uchar dat);  	//д���ݺ���
void lcd_init(void );        	//LCD��ʼ������
void write_string(uchar x,uchar y,uchar *s);//��ʾ�ַ���,xΪ��λ�ã�yΪ��λ��

void write_com(uchar com)//дָ���
{
    RS=0;       //д��ָ��
    RW=0;       //����д��
    P0=com;
    EN=1;
    _nop_();
    EN=0;
    delay_ms(5);
}

void write_data(uchar dat)//д���ݺ���
{
    RS=1;       	 //д������      
    RW=0;					//����д��
    P0=dat;
    EN=1;
    _nop_();
    EN=0;
    delay_ms(5);
}

void lcd_init()//LCD��ʼ������
{
    write_com(0x38);    //8λ�������ߣ�2����ʾ��5*7����
    write_com(0x0c);    //��ʾ�������أ���˸��
    write_com(0x06);    //������ƣ��ַ����ƶ�
}
	
void write_string(uchar x,uchar y,uchar *s)	//��ʾ�ַ���,xΪ��λ�ã�yΪ��λ��
{
	if(y==0)
		write_com(0x80+x);//��һ����ʾ
	else
		write_com(0xc0+x);//�ڶ�����ʾ
	while(*s)//ѭ����д���ַ���
	{
		write_data(*s);//һ��һ��д���ַ�
		s++;//д��һ���ַ�
	}
}

#endif