#ifndef __KEY_H__
#define __KEY_H__

#include "delay.h"
#include "lcd.h"
#include "intrins.h"

sbit key_h=P1^0;//���°���
sbit key_l=P1^1;//���°���
sbit alarm=P1^2;//������

int set_t=26;//�����¶ȳ�ʼΪ26C

void key(void );//��ⰴ��״�����������¶�

void warning(uint a);//����������

void key()//��ⰴ��״�����������¶�
{
	if(key_h==0)
	{
		while(key_h==0);//�ȴ������ͷ�
		set_t++;//�趨�¶�+1
	}
	if(key_l==0)
	{
		
		while(key_l==0);//�ȴ������ͷ�
		set_t--;//�趨�¶�-1
	}
	
	write_com(0xc0+6);//�ڶ��п�ʼд
	write_data(set_t%100/10+0x30);//��Ļ���ʮλ��
	write_data(set_t%10+0x30);//�����λ��
	write_data(0xDF);	
	write_data('C');//���϶ȷ���
}

void warning(uint a)//��������
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